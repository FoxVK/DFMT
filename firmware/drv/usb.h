#ifndef USB_H
#define	USB_H

#include <xc.h>
#include "usb_types.h"
#include "utils.h"

void usb_init(Usb_config* config);
void usb_task();

void usb_attach(bool state);

#endif	/* USB_H */

