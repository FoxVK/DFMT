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

#ifndef USB_AUDIO_H
#define	USB_AUDIO_H

#include <inttypes.h>
#include "utils.h"
#include "usb.h"

typedef enum
{
    USB_AUDIO_EV_SET_IFACE,
}Usb_audio_event;

typedef struct
{
    struct{
      bool claimed;
      void* callback_usr_ptr;
      void(*callback)(void*, size_t, void*);
    }ep[USB_EP_COUNT][USB_EP_DIRECTION_COUNT];

    unsigned iface_num;
    bool claimed;
    void (*event_callback)(Usb_audio_event);
    unsigned current_iface;
}Usb_audio_iface;

void usb_audio_init(Usb_audio_iface *iface, unsigned iface_number, void(*event_callback)(Usb_audio_event));

bool usb_audio_ct_handler(Usb_audio_iface *iface, Usb_ct_request *request);

void usb_audio_claim(Usb_audio_iface *iface);
void usb_audio_release(Usb_audio_iface *iface);

void Usb_audio_add_ep(Usb_audio_iface *iface, Usb_ep_number ep, Usb_ep_direction dir, void(*transfer_done_callback)(void*, size_t, void*));

Usb_rw_request Usb_audio_send(Usb_audio_iface *iface, Usb_ep_number ep, void*buf, size_t size);
Usb_rw_request Usb_audio_receive(Usb_audio_iface *iface, Usb_ep_number ep, void*buf, size_t size);

unsigned usb_audio_can_play(Usb_audio_iface *iface);

#endif	/* USB_AUDIO_H */

