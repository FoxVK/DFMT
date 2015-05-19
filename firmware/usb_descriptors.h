#ifndef USB_DESCRIPTORS_H
#define	USB_DESCRIPTORS_H

#include <inttypes.h>
#include "drv/usb.h"

extern const Usb_descriptor_device usb_desc_device;
extern const void* usb_desc_conf1;
extern const void* usb_desc_str[];

#endif	/* USB_DESCRIPTORS_H */

