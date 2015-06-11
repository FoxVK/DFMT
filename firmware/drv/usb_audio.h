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
