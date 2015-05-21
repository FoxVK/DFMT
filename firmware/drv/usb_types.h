#ifndef USB_TYPES_H
#define	USB_TYPES_H

#include <xc.h>
#include <inttypes.h>

#include "config.h"
#include "utils.h"

typedef enum
{
    USB_EV_POWERED, USB_EV_UNPOWERED, USB_EV_CONFIGURED, USB_EV_DECONFIGURED, USB_EV_RESET, USB_EV_SUSPENDED, USB_EV_RESUMED
}Usb_event;

typedef struct{
    uint8_t     bLength;            //Size of this descriptor in bytes
    uint8_t     bDescriptorType;    //DEVICE Descriptor Type
    uint16_t    bcdUSB;             //USB Specification Release Number in Binary-Coded Decimal (i.e., 2.10 is 210H).
    uint8_t     bDeviceClass;       //If this field is set to FFH, the device class is vendor-specific.
    uint8_t     bDeviceSubClass;    //
    uint8_t     bDeviceProtocol;    //If this field is set to FFH, the device uses a vendor-specific protocol on a device basis.
    uint8_t     bMaxPacketSize0;    //Maximum packet size for endpoint zero(only 8, 16, 32, or 64 are valid)
    uint16_t    idVendor;
    uint16_t    idProduct;
    uint16_t    bcdDevice;          //Device release number in binary-coded decimal
    uint8_t     iManufacturer;      //string index
    uint8_t     iProduct;           //string index
    uint8_t     iSerialNumber;      //string index
    uint8_t     bNumConfigurations; //Number of possible configurations

}Usb_descriptor_device;  //usb spec p262

typedef struct{
    union{
        struct {
            union {
                uint8_t     bmRequestType;
                struct {
                    char recipient:5;
                    char type:2;
                    char data_stg_dir:1;
                }ReqType_bits;
            };
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
}Usb_ct_request;

typedef struct{
    const Usb_descriptor_device* device_desc;
    const void* configuration_desc[USB_CONFIGURATION_COUNT];
    const void* string_descs[USB_STRING_COUNT];
          void (*event_callback)(Usb_event);
          bool (*ct_request_callback)(Usb_ct_request*);
}Usb_config;

typedef enum {
//<editor-fold defaultstate="collapsed" desc="USB_EPXX enum">

#if USB_USED_ENDPOINS<1
  #error "USB_USEUSB_USED_ENDPOINS must be at least 1 (EP00 is mandatory)."
#elif USB_USED_ENDPOINS>16
  #error "USB_USEUSB_USED_ENDPOINS > 16. You cannot have more than 16 endpoints."
#endif

  USB_EP00,
#if USB_USED_ENDPOINS>1
  USB_EP01,
#endif
#if USB_USED_ENDPOINS>2
  USB_EP02,
#endif
#if USB_USED_ENDPOINS>3
  USB_EP03,
#endif
#if USB_USED_ENDPOINS>4
  USB_EP04,
#endif
#if USB_USED_ENDPOINS>5
  USB_EP05,
#endif
#if USB_USED_ENDPOINS>6
  USB_EP06,
#endif
#if USB_USED_ENDPOINS>7
  USB_EP07,
#endif
#if USB_USED_ENDPOINS>8
  USB_EP08,
#endif
#if USB_USED_ENDPOINS>9
  USB_EP09,
#endif
#if USB_USED_ENDPOINS>10
  USB_EP10,
#endif
#if USB_USED_ENDPOINS>11
  USB_EP11,
#endif
#if USB_USED_ENDPOINS>12
  USB_EP12,
#endif
#if USB_USED_ENDPOINS>13
  USB_EP13,
#endif
#if USB_USED_ENDPOINS>14
  USB_EP14,
#endif
#if USB_USED_ENDPOINS>15
  USB_EP15,
#endif
// </editor-fold>
  USB_EP_COUNT}Usb_ep_number;
                
typedef enum { USB_EP_OUT, USB_EP_IN, USB_EP_DIRECTION_COUNT  }Usb_ep_direction;

typedef enum { USB_RW_REQ_OK, USB_RW_REQ_QFULL } Usb_rw_request;

typedef enum { USB_CT_WRITE, USB_CT_READ } Usb_ct_direction;
typedef  void(*Usb_ct_callback)();

#endif	/* USB_TYPES_H */

