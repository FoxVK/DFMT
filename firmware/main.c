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



void main(void)
{
    app_config();

    //start delay
    int i,j;
    for(i=0; i<300000;i++)
        for(j=0; j<80;j++)
            _nop();

    app_init();

    while (1)
    {
        app_task();
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