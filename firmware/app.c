#include "app.h"
#include "drv/debug_uart.h"
#include "drv/utils.h"
#include "drv/usb.h"
#include "drv/usb_audio.h"

extern Usb_config config;

static Usb_audio_iface *audio_if;

static int16_t test_audio_buf[48][2];

void init_test_audio()
{
    int t;
    for(t=0; t<48; t++)
        test_audio_buf[t][0] = test_audio_buf[t][1] = (t>48/2) ? 32000:-32000;
}

void usb_event(Usb_event ev)
{
    switch(ev)
    {
        case USB_EV_CONFIGURED:
        {
            static char* line = "configured\r\n";
            debug_uart_write(line);
            
            if(usb_current_config() == 1)
                usb_audio_claim(audio_if);
            else
                usb_audio_release(audio_if);
        }
            break;
        case USB_EV_RESET:
        {
            static char* line = "usb reset\r\n";
            debug_uart_write(line);
        }
            break;
        case USB_EV_SUSPENDED:
        {
            static char* line = "suspended\r\n";
            debug_uart_write(line);
        }
            break;
        case USB_EV_RESUMED:
        {
            static char* line = "RESUMED\r\n";
            debug_uart_write(line);
        }
            break;
        default:
            break;
    }
}

bool app_usb_ct_handler(Usb_ct_request *rq)
{
    return usb_audio_ct_handler(audio_if, rq);
}

inline void app_init()
{
    debug_uart_init();
    static char * run = "\n\rReseted\n\r";
    debug_uart_write(run);

    config.event_callback = usb_event;
    config.ct_request_callback = &app_usb_ct_handler;
    usb_init(&config);

    static Usb_audio_iface uai;
    audio_if = &uai;
    usb_audio_init(audio_if, 1, NULL);
    Usb_audio_add_ep(audio_if, USB_EP01, USB_EP_IN, NULL);

    init_test_audio();
}

inline void app_task()
{
    debug_uart_task();
    usb_task();
    
    if(usb_audio_can_play(audio_if))
        Usb_audio_send(audio_if, USB_EP01, test_audio_buf, sizeof(test_audio_buf));
}
