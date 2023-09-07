#ifndef _transmit_h
#define _transmit_h

#define sizeof_Uart_buffer 255

#include <stdarg.h>

typedef xdata struct Uart_struct
{
    volatile unsigned char i;
    volatile unsigned char end;
    volatile unsigned char buffer[sizeof_Uart_buffer];
    volatile unsigned char timer_100us;
} Uart_type;

void init_UART(Uart_type *example);
void sendbyte_UART(Uart_type *example, unsigned char Data) reentrant;
void UART_Process_Send(Uart_type *example, unsigned char number_uart);
void UART_Process_Send_ITR(Uart_type *example, unsigned char number_uart) reentrant;
//----------------------------------------------------------------------------------------
void myprintf(Uart_type *uart_example, char *str, ...) reentrant;
void vmyprintf(Uart_type *uart_example, char *str, va_list ap) reentrant;

#endif
