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
#include <sys/attribs.h>

#include "config.h"


#ifndef DEBUG_UART_QUEUE_SIZE
#error "DEBUG_UART_QUEUE_SIZE not defined"
#elif DEBUG_UART_QUEUE_SIZE < 0
#error "DEBUG_UART_QUEUE_SIZE can not be lower than zero."
#endif

static volatile char* queue[DEBUG_UART_QUEUE_SIZE];
static volatile int head, tail;

void debug_uart_init()
{
    head = tail = 0;

    U1MODEbits.ON = 1;
    U1BRG = 21; //115 200
    U1MODEbits.RTSMD = 1;
    U1STAbits.UTXSEL = 2; //interrupt when empty;

    U1STAbits.UTXEN = 1;
}



void debug_uart_task()
{
    while(!U1STAbits.UTXBF)
    {
        if(head == tail)
            break;
        
        char ch = *queue[head];
        if(ch == '\0')
        {
            head++;
            if(head>=DEBUG_UART_QUEUE_SIZE)
                head = 0;
        }
        else
        {
            U1TXREG = ch;
            queue[head] += 1;
        }
    }
}

int debug_uart_write( char* static_buffer)
{
    int t = tail +1;
    if(t >= DEBUG_UART_QUEUE_SIZE)
        t -= DEBUG_UART_QUEUE_SIZE;
    
    if(t == head)
        return 0;
    
    queue[tail] = static_buffer;
    tail = t;
    
    debug_uart_task();    
}

void __ISR (_UART1_VECTOR, IPL4AUTO) uart(void)
{
    debug_uart_task();
}
