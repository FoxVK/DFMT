// <editor-fold defaultstate="collapsed" desc="Copyright">
/*
    This program is free software: you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation, either version 3 of the License, or
    (at your option) any later version.

    This program is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.

    You should have received a copy of the GNU General Public License
    along with this program.  If not, see <http://www.gnu.org/licenses/>.
 
    Copyright: Pavel Kovar 2015 <pavel.kovar@vsetin.org>.
 */
// </editor-fold>

#ifndef USB_H
#define	USB_H

#include <xc.h>
#include "usb_types.h"
#include "utils.h"

void usb_init(Usb_config* config);
void usb_task();

int usb_current_config();
bool usb_is_suspended();
unsigned usb_queued_bufs(Usb_ep_number ep, Usb_ep_direction dir);

void usb_set_transfer_callback(Usb_ep_number ep, Usb_ep_direction dir, void(*callback)(void*, size_t, void*), void* usr_data);

void usb_enable_ep(Usb_ep_number ep, Usb_ep_direction dir,  bool state, bool isochornous);
void usb_stall_ep(Usb_ep_number ep, bool state);
Usb_rw_request usb_arm_ep(Usb_ep_number ep, Usb_ep_direction dir, void *buf, size_t size, unsigned data01);
void usb_ct_reply(Usb_ct_direction dir, void *buf, size_t size, Usb_ct_callback call_back);

#endif	/* USB_H */

