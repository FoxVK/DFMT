//TODO GNU

#include "tuner_com.h"
#include "drv/usb.h"
#include "drv/utils.h"
#include "shared.h"

#define MSG_COUNT 6

enum {ST_READY, ST_REQUEST_COMES, ST_WAITNG_FOR_I2C}state;
static Tunnel_msg msg[MSG_COUNT];
static Queue msg_queue;
static void *queue_array[MSG_COUNT];

static Tunnel_msg *request;
static size_t request_size;

static inline void send(Tunnel_msg *msg, size_t size)
{
    usb_arm_ep(TUNNEL_EP, USB_EP_IN, (void*)msg, size, 0);
}

static void callback_in(void *buf, size_t size, void * usrptr)
{   //reply was sent
    (void) usrptr;
    (void) size;
    queue_push(&msg_queue, buf);
}

static void callback_out(void *buf, size_t size, void * usrptr)
{   //request comes
    (void) usrptr;
    (void) size;
    
    if(state = ST_READY)
    {
        ((Tunnel_msg*)buf)->in.error = TUNNEL_ERROR_REQINPORGRESS;
        send(buf, size);
    }
    request = buf;
    request_size = size;
    state = ST_REQUEST_COMES;
    
    usb_arm_ep(TUNNEL_EP, USB_EP_OUT, queue_pop(&msg_queue), sizeof(Tunnel_msg), 1);
}

void tunnel_init()
{
    int i;
    state = ST_READY;
    
    queue_init(&msg_queue, queue_array, MSG_COUNT);
    
    for(i=0; i<MSG_COUNT; i++)
        queue_push(&msg_queue, &msg[i]);
    
    request = NULL;
    
    usb_set_transfer_callback(TUNNEL_EP, USB_EP_IN, callback_in,  NULL);
    usb_set_transfer_callback(TUNNEL_EP, USB_EP_IN, callback_out, NULL);
    usb_enable_ep(TUNNEL_EP, USB_EP_IN,  true, false);
    usb_enable_ep(TUNNEL_EP, USB_EP_OUT, true, false);
    
    usb_arm_ep(TUNNEL_EP, USB_EP_OUT, queue_pop(&msg_queue), sizeof(Tunnel_msg), 1);
    usb_arm_ep(TUNNEL_EP, USB_EP_OUT, queue_pop(&msg_queue), sizeof(Tunnel_msg), 1);  
}

void tunnel_task()
{
    
    switch(state)
    {
        case ST_READY:
            break;
        case ST_REQUEST_COMES:
            switch(request->out.type)
            {
                case TUNNEL_REQ_PING:
                    break;
                case TUNNEL_REQ_READ:
                case TUNNEL_REQ_WRITE:
                    if(tuner_com_state()==TUNER_COM_BUSY)
                    {
                        request->in.error=TUNNEL_ERROR_I2CBUSY;
                        send(request, request_size);
                        state = ST_READY;
                    }
                    else
                    {
                        if(request->out.type == TUNNEL_REQ_READ)
                        {
                            int tuner = request->out.tuner;
                            size_t read_size = request->out.rw_size;
                            
                            if(read_size > sizeof(Tuner_read_reply) || tuner > 1)
                            {
                                request->in.error=TUNNEL_ERROR;
                                send(request, request_size);
                                state = ST_READY;
                            }
                            else
                            {                                
                                tuner_read(tuner, &request->in.reply, read_size);
                                state = ST_WAITNG_FOR_I2C;
                            }
                        }
                        else
                        {
                            int tuner = request->out.tuner;
                            size_t write_size = request->out.rw_size;
                            
                            if(write_size > 16 || tuner > 1)
                            {
                                request->in.error=TUNNEL_ERROR;
                                send(request, request_size);
                                state = ST_READY;
                            }
                            else
                            {
                            
                                tuner_write(tuner, request->out.cmd, write_size);
                                state = ST_READY;

                                Tunnel_msg *ok_msg = (Tunnel_msg *)queue_pop(&msg_queue);
                                ok_msg->in.error=TUNNEL_ERROR_OK;
                                ok_msg->id = request->id;
                                send(ok_msg, request_size);
                            }
                        }
                    }
                    break;
                default:
                    request->in.error = TUNNEL_ERROR_BADTYPE;
                    send(request, request_size);
                    state = ST_READY;
            }
            break;
        case ST_WAITNG_FOR_I2C:
            state = ST_READY;
            switch(tuner_com_state())
            {
                case TUNER_COM_BUSY:
                    state = ST_WAITNG_FOR_I2C;
                    break;
                
                case TUNER_COM_IDLE:
                case TUNER_COM_DEV_BUSY:
                    request->in.error = TUNNEL_ERROR_OK;
                    send(request, request_size);
                    break;
                    
                default:
                    request->in.error = TUNNEL_ERROR_I2C;
                    send(request, request_size);
                    break;
            }
            break;
    }
}
