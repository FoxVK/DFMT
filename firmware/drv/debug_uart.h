#ifndef DEBUG_UART_H
#define	DEBUG_UART_H

void debug_uart_init();
void debug_uart_task();
int debug_uart_write( char* static_buffer);

#endif	/* DEBUG_UART_H */

