#ifndef USB_H
#define	USB_H

#include <xc.h>
#include "usb_types.h"
#include "utils.h"

void usb_init(Usb_config* config);
void usb_task();

void usb_attach(bool state);
int usb_current_config();
void usb_enable_ep(Usb_ep_number ep, Usb_ep_direction dir,  bool state, bool isochornous);

#endif	/* USB_H */

