#include "drv/debug_uart.h"
#include "app_config.h"

void main(void)
{
    app_config();
    debug_uart_init();

    static char* test = "Running\r\n";

    debug_uart_write(test);
    debug_uart_write(test);
    debug_uart_write(test);
    debug_uart_write(test);

    while (1)
    {
        debug_uart_task();
    }
}













/*
void _general_exception_handler (unsigned cause, unsigned status)
{
    static unsigned int _excep_addr = 0;
    asm volatile("mfc0 %0,$14" : "=r" (_excep_addr));

    char str[30];
    sprintf(str, "\r\n Exception @0x%x: ", _excep_addr);
    SYS_DEBUG_Message(str);

    switch((cause & 0x7c)>>2)
    {
        case 0 : SYS_DEBUG_Message("interrupt"); break;
        case 4 : SYS_DEBUG_Message("address error exception (load or ifetch)"); break;
        case 5 : SYS_DEBUG_Message("address error exception (store)"); break;
        case 6 : SYS_DEBUG_Message("bus error (ifetch)"); break;
        case 7 : SYS_DEBUG_Message("bus error (load/store)"); break;
        case 8 : SYS_DEBUG_Message("syscall"); break;
        case 9 : SYS_DEBUG_Message("breakpoint"); break;
        case 10: SYS_DEBUG_Message("reserved instruction"); break;
        case 11: SYS_DEBUG_Message("coprocessor unusable"); break;
        case 12: SYS_DEBUG_Message("arithmetic overflow"); break;
        case 13: SYS_DEBUG_Message("trap (possible divide by zero)"); break;
        case 16: SYS_DEBUG_Message("implementation specfic 1"); break;
        case 17: SYS_DEBUG_Message("CorExtend Unuseable"); break;
        case 18: SYS_DEBUG_Message("coprocessor 2"); break;
        default: SYS_DEBUG_Message("Unknown reason"); break;
    }

    _nop();
    while(true);
}*/