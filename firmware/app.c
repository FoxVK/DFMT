#include "app.h"
#include "drv/debug_uart.h"
#include "drv/utils.h"
#include "drv/usb.h"

extern Usb_config config;

void usb_event(Usb_event ev)
{
    switch(ev)
    {
        case USB_EV_CONFIGURED:
        {
            static char* line = "configured\r\n";
            debug_uart_write(line);
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

inline void app_init()
{
    debug_uart_init();
    static char * run = "\n\rReseted\n\r";
    debug_uart_write(run);

    config.event_callback = usb_event;
    config.ct_request_callback = NULL;
    usb_init(&config);
}

inline void app_task()
{
    debug_uart_task();
    usb_task();
}
