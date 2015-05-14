#ifndef USB_TYPES_H
#define	USB_TYPES_H

#include <xc.h>
#include <inttypes.h>


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

typedef uint8_t* Usb_descriptor_configuraton; //TODO check it !!
typedef uint8_t* Usb_descriptor_string;       //TODO check it !!

typedef struct{
    Usb_descriptor_device* device_desc;
    Usb_descriptor_configuraton* configuration_desc;
    Usb_descriptor_string* string_descs;
}Usb_config;

#endif	/* USB_TYPES_H */

