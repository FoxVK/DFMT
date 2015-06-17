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

#include "usb_audio.h"

static void enable_ep(Usb_audio_iface *iface, bool enabled)
{
    int ep, dir;
    for(ep=0; ep<USB_EP_COUNT; ep++)
    {
        for(dir=0; dir<USB_EP_DIRECTION_COUNT; dir++)
        {
            if(iface->ep[ep][dir].claimed)
            {
                usb_enable_ep(ep, dir, enabled, true);
                usb_set_transfer_callback(ep, dir, (enabled) ? iface->ep[ep][dir].callback : NULL, NULL);
            }
        }
    }
}

void usb_audio_init(Usb_audio_iface *iface, unsigned iface_number, void(*event_callback)(Usb_audio_event))
{
    iface->claimed = false;
    iface->iface_num = iface_number;
    iface->current_iface = 0;
    iface->event_callback = event_callback;
    
    int ep, dir;
    for(ep=0; ep<USB_EP_COUNT; ep++)
    {
        for(dir=0; dir<USB_EP_DIRECTION_COUNT; dir++)
        {
            iface->ep[ep][dir].callback = NULL;
            iface->ep[ep][dir].claimed = false;
        }
    }
}

bool usb_audio_ct_handler(Usb_audio_iface *iface, Usb_ct_request *request)
{
    if(!iface->claimed)
        return 0;

    if(request->ReqType_bits.recipient == 0x01 && request->wIndex == iface->iface_num)
    {
        //ct is for us
        if(request->wValue < 2 && request->request == 0x0b01) //usb audio manual pg 129 (in http://www.beyondlogic.org/usbnutshell/usb6.shtml is a mistake)
        {
            usb_ct_reply(USB_CT_WRITE, NULL, 0, NULL);
            
            iface->current_iface = request->wValue;

            enable_ep(iface, request->wValue);

            if (iface->event_callback)
                iface->event_callback(USB_AUDIO_EV_SET_IFACE);
        }
        else
            usb_stall_ep(USB_EP00, true);
        return 1;
    }
    else
        return 0;
}

void usb_audio_claim(Usb_audio_iface *iface)
{
    iface->claimed = true;
}

void usb_audio_release(Usb_audio_iface *iface)
{
    iface->claimed = false;
    enable_ep(iface, false);
}

void Usb_audio_add_ep(Usb_audio_iface *iface, Usb_ep_number ep, Usb_ep_direction dir, void(*transfer_done_callback)(void*, size_t, void*))
{
    iface->ep[ep][dir].claimed = true;
    iface->ep[ep][dir].callback = transfer_done_callback;

    if(iface->claimed)
    {
        usb_set_transfer_callback(ep, dir, (iface->current_iface) ? transfer_done_callback : NULL, NULL);
        usb_enable_ep(ep, dir, iface->current_iface, true);
    }
}

Usb_rw_request Usb_audio_send(Usb_audio_iface *iface, Usb_ep_number ep, void*buf, size_t size)
{
    return usb_arm_ep(ep, USB_EP_IN, buf, size, 0);
}

Usb_rw_request Usb_audio_receive(Usb_audio_iface *iface, Usb_ep_number ep, void*buf, size_t size)
{
    return usb_arm_ep(ep, USB_EP_OUT, buf, size, 0);
}

bool usb_audio_can_play(Usb_audio_iface *iface)
{
    return iface->current_iface;
}