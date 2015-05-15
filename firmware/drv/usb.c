#include "usb.h"

//#define USB_EP0_SIZE 64

typedef struct {
    unsigned int nothing:2;
    unsigned int BSTALL:1;
    unsigned int DTS:1;
    unsigned int NINC:1;
    unsigned int KEEP:1;
    unsigned int DATA01:1;
    unsigned int UOWN:1;
    unsigned short bytecount;
    void * buf_ptr;
}BDCF_S2H;

typedef struct {
    unsigned int non:2;
    unsigned int PID:4;
    unsigned int DATA01:1;
    unsigned int UOWN:1;
    unsigned short bytecount;
    void * buf_ptr;
}BDCF_H2S;

typedef union {
    BDCF_S2H w;
    BDCF_H2S r;
    unsigned long long all;
}BDT;


typedef struct{
    union{
        struct {
            uint8_t     bmRequestType;
            uint8_t     bRequest;
        };
        uint16_t    request;
     };
     union {
         struct {
             uint8_t desc_index;
             uint8_t desc_type;
         };
         uint16_t    wValue;
     };

    uint16_t    wIndex;
    uint16_t    wLength;
}Request;


typedef enum {EP00, EP01, EP02, EP03, EP04, EP05, EP06, EP07, EP08, EP09, EP10,
                EP11, EP12, EP13, EP14, EP15, EP_COUNT  }EP_number;
typedef enum {EP_RX, EP_TX, EP_DIRECTION_COUNT          }EP_direction;
typedef enum {EP_EVEN, EP_ODD, EP_PINGPONG_COUNT        }EP_pingpong;

static BDT __attribute__((aligned(512))) bdt[EP_COUNT][EP_DIRECTION_COUNT][EP_PINGPONG_COUNT];

static uint8_t EP0_receive_buf[EP_PINGPONG_COUNT];

void usb_init(Usb_config* config)
{
    unsigned bdp_phy_addr = virt2phy(bdt);
    U1BDTP1 = bdp_phy_addr>>(8*1);
    U1BDTP2 = bdp_phy_addr>>(8*2);
    U1BDTP3 = bdp_phy_addr>>(8*3);
}

void usb_task()
{

}

void usb_attach(bool state)
{
    
}