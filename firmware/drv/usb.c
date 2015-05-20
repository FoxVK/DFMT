#include "usb.h"
#include "debug_uart.h"
#include "utils.h"

#define USB_EP0_SIZE 64

typedef struct {
    unsigned int nothing:2;
    unsigned int BSTALL:1;
    unsigned int DTS:1;
    unsigned int NINC:1;
    unsigned int KEEP:1;
    unsigned int DATA01:1;
    unsigned int UOWN:1;
    unsigned short bytecount;
    unsigned int buf_ptr;
}BDCF_S2H;

typedef struct {
    unsigned int non:2;
    unsigned int PID:4;
    unsigned int DATA01:1;
    unsigned int UOWN:1;
    unsigned short bytecount;
    unsigned int buf_ptr;
}BDCF_H2S;

typedef union {
    BDCF_S2H w;
    BDCF_H2S r;
    unsigned long long all;
}BDT;


static volatile __U1EP0bits_t* ep_reg[] =
{(__U1EP0bits_t*)&U1EP0,  (__U1EP0bits_t*)&U1EP1,  (__U1EP0bits_t*)&U1EP2,
 (__U1EP0bits_t*)&U1EP3,  (__U1EP0bits_t*)&U1EP4,  (__U1EP0bits_t*)&U1EP5,
 (__U1EP0bits_t*)&U1EP6,  (__U1EP0bits_t*)&U1EP7,  (__U1EP0bits_t*)&U1EP8,
 (__U1EP0bits_t*)&U1EP9,  (__U1EP0bits_t*)&U1EP10, (__U1EP0bits_t*)&U1EP11,
 (__U1EP0bits_t*)&U1EP12, (__U1EP0bits_t*)&U1EP13, (__U1EP0bits_t*)&U1EP14,
 (__U1EP0bits_t*)&U1EP15};

typedef enum { EP_EVEN, EP_ODD, EP_PINGPONG_COUNT }EP_pingpong;

typedef enum { TOKEN_IN=0b1001, TOKEN_OUT=0b0001, TOKEN_SETUP=0b1101 } Token;

static enum { CT_IDLE, CT_DATA_TX, CT_DATA_RX, CT_STATUS_IN, CT_STATUS_OUT} ct_state;
static void *ct_data_current, *ct_data_end;
bool ct_data01;
Usb_ct_callback ct_call_back;

static EP_pingpong pp_to_use[USB_EP_COUNT][USB_EP_DIRECTION_COUNT];

static volatile BDT __attribute__((aligned(512))) bdt[USB_EP_COUNT][USB_EP_DIRECTION_COUNT][EP_PINGPONG_COUNT];

static uint8_t EP0_rx_buf[EP_PINGPONG_COUNT][USB_EP0_SIZE];
static void (*trasfer_callback[USB_EP_COUNT][USB_EP_DIRECTION_COUNT])(void*, size_t);


static Usb_config* settings; //USB settings
static int cur_cnf; //current configureation from host
static bool suspended;
static unsigned new_addr;


static void reset()
{
    cur_cnf = -1;
    U1ADDR = 0;
    new_addr = 0;
    ct_state = CT_IDLE;
    ct_call_back = NULL;
}

void usb_stall_ep(Usb_ep_number ep, bool state)
{
    if(ep==USB_EP00 && state==false)
        return;
    ep_reg[ep]->EPSTALL = state;
}

void usb_enable_ep(Usb_ep_number ep, Usb_ep_direction dir,  bool state, bool isochornous)
{
    ep_reg[ep]->EPHSHK = (isochornous) ? 0 : 1;
    if(dir == USB_EP_OUT)
        ep_reg[ep]->EPRXEN = state;
    else if(dir == USB_EP_IN)
        ep_reg[ep]->EPTXEN = state;
}

Usb_rw_request usb_arm_ep(Usb_ep_number ep, Usb_ep_direction dir, void *buf, size_t size, unsigned data01)
{
    volatile BDT *t = &bdt[ep][dir][pp_to_use[ep][dir]];

    if(t->r.UOWN == 1)
        return USB_RW_REQ_QFULL;

    t->all = 0;
    t->w.buf_ptr = virt2phy(buf);
    t->w.bytecount = size;
    t->w.DATA01 = data01;
    t->w.UOWN = 1;

    U1CONbits.PKTDIS = 0;

    pp_to_use[ep][dir] ^= 1;
    return USB_RW_REQ_OK;
}

void usb_init(Usb_config* config)
{
    reset();
    suspended = false;
    settings = config;

    while(U1PWRCbits.USBBUSY);
        //wait for USB module
    U1PWRCbits.USBPWR = 1; //power on USB;

    unsigned bdp_phy_addr = virt2phy(bdt);
    U1BDTP1 = bdp_phy_addr>>(8*1);
    U1BDTP2 = bdp_phy_addr>>(8*2);
    U1BDTP3 = bdp_phy_addr>>(8*3);

    int ep, dir, pp;
    for (ep=0; ep<USB_EP_COUNT; ep++)
    {
        
        for (dir = 0; dir<USB_EP_DIRECTION_COUNT; dir++)
        {
            pp_to_use[ep][dir] = EP_EVEN;
            trasfer_callback[ep][dir] = NULL;
            for (pp=0; pp<EP_PINGPONG_COUNT; pp++)
                bdt[ep][dir][pp].all=0l;
        }
    }

    U1CONbits.USBEN = 1;

    usb_arm_ep(USB_EP00, USB_EP_OUT, EP0_rx_buf[0], USB_EP0_SIZE, 0);
    usb_enable_ep(USB_EP00, USB_EP_OUT, true, false);
    usb_enable_ep(USB_EP00, USB_EP_IN, true, false);
}


static bool ct_task(Usb_ep_direction dir)
{
    switch(ct_state)
    {
        case CT_IDLE:
            return 0;
            break;

        case CT_DATA_TX:
            if(ct_data_current < ct_data_end)
            {
                size_t size;
                if(ct_data_current + USB_EP0_SIZE < ct_data_end)
                    size = USB_EP0_SIZE;
                else
                    size = ct_data_end - ct_data_current;
                usb_arm_ep(USB_EP00, USB_EP_IN, ct_data_current, size, ct_data01);

                ct_data_current += size;
                ct_data01 ^= 1;
            }
            else
            {
                ct_state = CT_STATUS_OUT;
                usb_arm_ep(USB_EP00, USB_EP_OUT, NULL, 0, 1);
            }
            break;

        case CT_DATA_RX:
            if(ct_data_current < ct_data_end)
            {
                size_t size;
                if(ct_data_current + USB_EP0_SIZE < ct_data_end)
                    size = USB_EP0_SIZE;
                else
                    size = ct_data_end - ct_data_current;
                usb_arm_ep(USB_EP00, USB_EP_OUT, ct_data_current, size, ct_data01);

                ct_data_current += size;
                ct_data01 ^= 1;
            }
            else
            {
                ct_state = CT_STATUS_IN;
                usb_arm_ep(USB_EP00, USB_EP_IN, NULL, 0, 1);
            }
            break;

        case CT_STATUS_IN:
            if(dir == USB_EP_IN)
            {
                ct_state = CT_IDLE;
                usb_arm_ep(USB_EP00, USB_EP_OUT, EP0_rx_buf[0], USB_EP0_SIZE, 0);
                if(ct_call_back)
                    ct_call_back();
            }
            break;
        case CT_STATUS_OUT:
            if(dir == USB_EP_OUT)
            {
                ct_state = CT_IDLE;
                usb_arm_ep(USB_EP00, USB_EP_OUT, EP0_rx_buf[0], USB_EP0_SIZE, 0);
                if(ct_call_back)
                    ct_call_back();
            }
            break;


    }
    return 1;
}

void usb_ct_reply(Usb_ct_direction dir, void *buf, size_t size, Usb_ct_callback call_back)
{
    ct_state = (dir==USB_CT_WRITE) ? CT_DATA_RX : CT_DATA_TX;
    ct_call_back = call_back;
    ct_data_current = buf;
    ct_data_end = buf + size;
    ct_data01 = 1;

    ct_task( (dir==USB_CT_WRITE)?USB_EP_OUT:USB_EP_IN );
}

static void set_adress_callback()
{
    U1ADDR = new_addr;
}

static void control_transfer(void * buf, size_t size)
{
    static char* dbg = "Setup ";
    static char dbg_type[] = "0000\r\n";
    debug_uart_write(dbg);

    Usb_ct_request * req = (Usb_ct_request*)buf;

    uint2hex(req->request, dbg_type, 4);
    debug_uart_write(dbg_type);
    bool stall_it = true;

    if(req->ReqType_bits.type == 0)
    {
        

        switch(req->bRequest)
        {
            case 0x00: //GET_STATUS
                break;
            case 0x01: //CLEAR_FEATURE
                break;
            case 0x03: //SET_FEATURE
                break;
            case 0x05: //SET_ADDRESS
                new_addr = req->wValue;
                stall_it = false;
                usb_ct_reply(USB_CT_WRITE, NULL, 0, &set_adress_callback);
                break;
            case 0x06: //GET_DESCRIPTOR
            {
                const void * desc = NULL;
                size_t dsize;
                switch(req->desc_type)
                {
                    case 0x01:
                        desc = settings->device_desc;
                        dsize = *(uint8_t*)desc;
                        break;
                    case 0x02:
                        if(req->desc_index < USB_CONFIGURATION_COUNT)
                        {
                            desc = settings->configuration_desc[req->desc_index]; //TODO check it
                            dsize = ((uint16_t*)desc)[1];
                        }
                        break;
                    case 0x03:
                        if(req->desc_index < USB_STRING_COUNT)
                        {
                            desc = settings->string_descs[req->desc_index]; //TODO check it
                            dsize = *(uint8_t*)desc;
                        }
                        break;
                }
                if(desc)
                {
                    stall_it = false;
                    if(dsize > req->wLength)
                        dsize = req->wLength;
                    usb_ct_reply(USB_CT_READ, (void*)desc, dsize, NULL);
                }
            }
                break;
            case 0x07: //SET_DESCRIPTOR
                break;
            case 0x08: //GET_CONFIGURATION
                break;
            case 0x09: //SET_CONFIGURATION
                cur_cnf = req->wValue;
                usb_ct_reply(USB_CT_WRITE, NULL, 0, &set_adress_callback);
                stall_it = false;
                settings->event_callback(USB_EV_CONFIGURED);
                break;
            default:
                break;
        }
    }
    else
    {
        if(settings->ct_request_callback)
            stall_it = !settings->ct_request_callback(req);
    }

    if(stall_it)
    {
        usb_stall_ep(USB_EP00, true);
        //static char *dbg = "STALL\r\n";
        //debug_uart_write(dbg);
        usb_arm_ep(USB_EP00, USB_EP_OUT,EP0_rx_buf[0],USB_EP0_SIZE,0);
    }
}


static void token(__U1STATbits_t stat)
{
   volatile BDT *bt = &bdt[stat.ENDPT][stat.DIR][stat.PPBI];

   //static char *in = "TOK IN\r\n", *out = "TOK OUT\r\n", *setup = "TOK SETUP\r\n";

    if(stat.ENDPT == USB_EP00)
    {
        if(bt->r.PID == TOKEN_SETUP)
        {
            //debug_uart_write(setup);
            control_transfer(phy2virt(bt->r.buf_ptr), bt->r.bytecount);
            U1CONbits.PKTDIS = 0;
        }
        else
        {
            /*if(bt->r.PID == TOKEN_IN)
                debug_uart_write(in);
            else
                debug_uart_write(out);*/
            
            ct_task(stat.DIR);
        }
    }
    else
    {
        unsigned e=stat.ENDPT, d=stat.DIR;
        if(trasfer_callback[e][d])
        {
            BDT *b = (BDT*)&bdt[e][d][stat.PPBI];
            trasfer_callback[e][d](phy2virt(b->r.buf_ptr), b->r.bytecount);
        }
    }
        
}

void usb_task()
{
    /*
    int eps = bdt[USB_EP00][USB_EP_OUT][EP_EVEN].r.UOWN + bdt[USB_EP00][USB_EP_OUT][EP_ODD].r.UOWN;
    static int leps = 0;
    if(leps != eps)
    {
        leps = eps;
        static char* str[] = {"0/2\r\n","1/2\r\n","2/2\r\n"};
        debug_uart_write(str[eps]);
    }*/

    
    if(U1IRbits.RESUMEIF)
    {
        U1IRbits.RESUMEIF = 1;
        if(suspended)
        {
            suspended = false;
            settings->event_callback(USB_EV_RESUMED);
        }
    }

    if(U1IRbits.IDLEIF)
    {
        U1IRbits.IDLEIF = 1;
        if(!suspended)
        {
            suspended = true;
            settings->event_callback(USB_EV_SUSPENDED);
        }
    }

    if(U1IRbits.URSTIF)
    {
        U1IRbits.URSTIF = 1;
        reset();
        settings->event_callback(USB_EV_RESET);
    }

    if(U1IRbits.STALLIF)
    {
        U1IRbits.STALLIF = 1;
    }

    if(U1IRbits.TRNIF)
    {
        __U1STATbits_t stat = U1STATbits;
        U1IRbits.TRNIF = 1;
        token(stat);
    }
}

void usb_set_transfer_callback(Usb_ep_number ep, Usb_ep_direction dir, void(*callback)(void*, size_t))
{
    trasfer_callback[ep][dir] = callback;
}

int usb_current_config()
{
    // -1 means we are not configured
    return cur_cnf;
}

bool usb_is_suspended()
{
    return suspended;
}

unsigned usb_queued_bufs(Usb_ep_number ep, Usb_ep_direction dir)
{
    return bdt[ep][dir][EP_EVEN].r.UOWN + bdt[ep][dir][EP_ODD].r.UOWN;
}