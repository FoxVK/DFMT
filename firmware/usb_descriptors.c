#include <inttypes.h>

#include "drv/usb.h"
#include "drv/config.h"
#include "shared.h"

typedef enum {
USB_DSC_DEVICE = 0x01,
USB_DSC_CONFIGURATION = 0x02,
USB_DSC_STRING = 0x03,
USB_DSC_INTERFACE = 0x04,
USB_DSC_ENDPOINT = 0x05,
}USB_descriptor_types;


const static Usb_descriptor_device usb_desc_device =
{
    .bLength            = sizeof(Usb_descriptor_device),
    .bDescriptorType    = USB_DSC_DEVICE,
    .bcdUSB             = 0x0200, //2.0
    .bDeviceClass       = 0x00,
    .bDeviceSubClass    = 0x00,
    .bDeviceProtocol    = 0x00,
    .bMaxPacketSize0    = 64,
    .idVendor           = USB_VID,
    .idProduct          = USB_PID,
    .bcdDevice          = 0x0003,
    .iManufacturer      = 1,
    .iProduct           = 2,
    .iSerialNumber      = 0,
    .bNumConfigurations = 1
};

const static uint8_t usb_desc_conf[] = {
    0x09,//sizeof(USB_CFG_DSC),     // Size of this descriptor in bytes
    0x02,   // CONFIGURATION descriptor type
    0x09,0x00,                      // Total length of data for this cfg
    0,                              // Number of interfaces in this cfg
    1,                              // Index value of this configuration
    0,                              // Configuration string index
    0b11000000,          // Attributes, see usb_device.h
    50,                             // Max power consumption (2X mA) //FIXME:
};
const void * usb_desc_conf1 = usb_desc_conf;
/*******************************************
 *  Language code string descriptor
 *******************************************/
const static struct
{
    uint8_t bLength;
    uint8_t bDscType;
    uint16_t string[1];
}usb_desc_str000=
{
    sizeof(usb_desc_str000),
    USB_DSC_STRING,
    {0x0409}
};

/*******************************************
 *  Manufacturer string descriptor
 *******************************************/
const static struct
{
    uint8_t bLength;
    uint8_t bDscType;
    uint16_t string[15];
}usb_desc_str001=
{
    sizeof(usb_desc_str001),
    USB_DSC_STRING,
    {
        'V','S','B','-','T','U','O',' ','D','i','p','l','o','m','a'}
};

/*******************************************
 *  Product string descriptor
 *******************************************/
const static struct
{
    uint8_t bLength;
    uint8_t bDscType;
    uint16_t string[13];
}usb_desc_str002=
{
    sizeof(usb_desc_str002),
    USB_DSC_STRING,
    {
        'D','u','a','l',' ','F','M',' ','T','u','n','e','r'
    }
};


Usb_config config =
{
  .configuration_desc[0] = (const void*)usb_desc_conf,
  .device_desc           = &usb_desc_device,
  .string_descs          = {
                            (void*) &usb_desc_str000,
                            (void*) &usb_desc_str001,
                            (void*) &usb_desc_str002
                            },
};