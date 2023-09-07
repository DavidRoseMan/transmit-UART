#include "transmit.h"
#include "variable.h"

void init_UART(Uart_type *example)
{
    example->i = 0;
    example->end = 0;
    example->timer_100us = 0;
}

void sendbyte_UART(Uart_type *example, unsigned char Data) reentrant
{
    if (example->end >= example->i)
    {
        if (example->end < (sizeof_Uart_buffer - 1))
        {
            example->end++;
        }
        else
        {
            while (example->i == 0)
                ;
            example->end = 0;
        }
    }
    else
    {
        while (example->i == example->end + 1)
            ;
        example->end++;
    }
    example->buffer[example->end] = Data;
}

void UART_Process_Send(Uart_type *example, unsigned char number_uart)
{
    if (example->timer_100us != 255)
        example->timer_100us++;
    else if (example->i != example->end)
    {
        if (number_uart == 1)
            SCON |= 0x02;
        else if (number_uart == 2)
            S2CON |= 0x02;
        else if (number_uart == 3)
            S3CON |= 0x02;
        else if (number_uart == 4)
            S4CON |= 0x02;
    }
}

void UART_Process_Send_ITR(Uart_type *example, unsigned char number_uart) reentrant
{
    unsigned char a;

    if (number_uart == 1)
        a = SCON;
    else if (number_uart == 2)
        a = S2CON;
    else if (number_uart == 3)
        a = S3CON;
    else if (number_uart == 4)
        a = S4CON;

    if (a & 0x02)
    {
        if (number_uart == 1)
            SCON &= ~0x02;
        else if (number_uart == 2)
            S2CON &= ~0x02;
        else if (number_uart == 3)
            S3CON &= ~0x02;
        else if (number_uart == 4)
            S4CON &= ~0x02;
        example->timer_100us = 0;
        if (example->i != example->end)
        {
            if (example->i < (sizeof_Uart_buffer - 1))
                example->i++;
            else
                example->i = 0;
            if (number_uart == 1)
                SBUF = example->buffer[example->i];
            else if (number_uart == 2)
                S2BUF = example->buffer[example->i];
            else if (number_uart == 3)
                S3BUF = example->buffer[example->i];
            else if (number_uart == 4)
                S4BUF = example->buffer[example->i];
        }
        else
        {
            example->timer_100us = 255;
        }
    }
}

void myprintf(Uart_type *uart_example, char *str, ...) reentrant
{
    char *char_temp;
    va_list ap;
    int i;
    int number_get;
    unsigned char head_flag; // print start from the number's head_value which is not zero.

    char_temp = str;
    va_start(ap, str);
    while (*char_temp != '\0')
    {
        if (*char_temp != '%')
        {
            sendbyte_UART(uart_example, (unsigned char)*char_temp);
            char_temp++;
        }
        else
        {
            char_temp++;
            if (*char_temp == '\0')
            {
                sendbyte_UART(uart_example, (unsigned char)'%');
                break;
            }
            else if (*char_temp != 'd')
            {
                sendbyte_UART(uart_example, (unsigned char)'%');
                sendbyte_UART(uart_example, (unsigned char)*char_temp);
                char_temp++;
                continue;
            }
            number_get = va_arg(ap, int);
            if (number_get == 0)
            {
                sendbyte_UART(uart_example, (unsigned char)'0');
            }
            else
            {
                if (number_get < 0)
                {
                    i = -10000;
                    sendbyte_UART(uart_example, (unsigned char)'-');
                }
                else
                {
                    i = 10000;
                }
                head_flag = 1;
                while (i)
                {
                    if (head_flag == 1 && number_get / i != 0)
                        head_flag = 0;
                    if (!head_flag)
                        sendbyte_UART(uart_example, (unsigned char)('0' + number_get / i));
                    number_get %= i;
                    i /= 10;
                }
            }
            char_temp++;
        }
    }
    va_end(ap);
    // sendbyte_UART(uart_example, (unsigned char)'\0');
}

void vmyprintf(Uart_type *uart_example, char *str, va_list ap) reentrant
{
    char *char_temp;
    int i;
    int number_get;
    unsigned char head_flag; // print start from the number's head_value which is not zero.

    char_temp = str;
    while (*char_temp != '\0')
    {
        if (*char_temp != '%')
        {
            sendbyte_UART(uart_example, (unsigned char)*char_temp);
            char_temp++;
        }
        else
        {
            char_temp++;
            if (*char_temp == '\0')
            {
                sendbyte_UART(uart_example, (unsigned char)'%');
                break;
            }
            else if (*char_temp != 'd')
            {
                sendbyte_UART(uart_example, (unsigned char)'%');
                sendbyte_UART(uart_example, (unsigned char)*char_temp);
                char_temp++;
                continue;
            }
            number_get = va_arg(ap, int);
            if (number_get == 0)
            {
                sendbyte_UART(uart_example, (unsigned char)'0');
            }
            else
            {
                if (number_get < 0)
                {
                    i = -10000;
                    sendbyte_UART(uart_example, (unsigned char)'-');
                }
                else
                {
                    i = 10000;
                }
                head_flag = 1;
                while (i)
                {
                    if (head_flag == 1 && number_get / i != 0)
                        head_flag = 0;
                    if (!head_flag)
                        sendbyte_UART(uart_example, (unsigned char)('0' + number_get / i));
                    number_get %= i;
                    i /= 10;
                }
            }
            char_temp++;
        }
    }
    // va_end(ap);
    // sendbyte_UART(uart_example, (unsigned char)'\0');
}
