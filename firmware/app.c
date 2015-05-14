#include "app.h"
#include "drv/debug_uart.h"
#include "drv/utils.h"

inline void app_init()
{
    debug_uart_init();
    static char * run = "\n\rReseted\n\r";
    debug_uart_write(run);
}

inline void app_task()
{
    debug_uart_task();
}
