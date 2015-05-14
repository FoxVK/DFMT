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
