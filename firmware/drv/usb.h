#ifndef USB_H
#define	USB_H

#include <xc.h>
#include "usb_types.h"
#include "utils.h"

void usb_init(Usb_config* config);
void usb_task();

int usb_current_config();
bool usb_is_suspended();

void usb_enable_ep(Usb_ep_number ep, Usb_ep_direction dir,  bool state, bool isochornous);
void usb_stall_ep(Usb_ep_number ep, bool state);
Usb_rw_request usb_arm_ep(Usb_ep_number ep, Usb_ep_direction dir, void *buf, size_t size, unsigned data01);
void usb_ct_reply(Usb_ct_direction dir, void *buf, size_t size, Usb_ct_callback call_back);

#endif	/* USB_H */

