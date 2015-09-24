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

#include <xc.h>
#include "app_config.h"
#include "app.h"
#include "drv/debug_uart.h"
#include "drv/utils.h"



void main(void)
{
    app_config();

    //start delay
    int i,j;
    for(i=0; i<100000;i++)
        for(j=0; j<80;j++)
            _nop();

    app_init();

    while (1)
    {
        app_task();
    }
}














void _general_exception_handler (unsigned cause, unsigned status)
{
    static unsigned int _excep_addr = 0;
    asm volatile("mfc0 %0,$14" : "=r" (_excep_addr));

    char str[]="exception @ addr xxxxxx";
    uint2hex( _excep_addr, str+17, 6);
    str[23]=0;
    debug_uart_write(str);

    switch((cause & 0x7c)>>2)
    {
        case 0 : debug_uart_write("interrupt"); break;
        case 4 : debug_uart_write("address error exception (load or ifetch)"); break;
        case 5 : debug_uart_write("address error exception (store)"); break;
        case 6 : debug_uart_write("bus error (ifetch)"); break;
        case 7 : debug_uart_write("bus error (load/store)"); break;
        case 8 : debug_uart_write("syscall"); break;
        case 9 : debug_uart_write("breakpoint"); break;
        case 10: debug_uart_write("reserved instruction"); break;
        case 11: debug_uart_write("coprocessor unusable"); break;
        case 12: debug_uart_write("arithmetic overflow"); break;
        case 13: debug_uart_write("trap (possible divide by zero)"); break;
        case 16: debug_uart_write("implementation specfic 1"); break;
        case 17: debug_uart_write("CorExtend Unuseable"); break;
        case 18: debug_uart_write("coprocessor 2"); break;
        default: debug_uart_write("Unknown reason"); break;
    }

    _nop();
    while(true)
        debug_uart_task();
}