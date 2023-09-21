# 快速建立 51 串口数据缓冲区

## 建立串口数据缓冲区

```c
Uart_type uart_use;//创建一个串口数据缓冲区对象。
init_UART(&uart_use);//初始化一个串口数据缓冲区对象
UART_Process_Send(&uart_use,1);//每100us调用一次，且此数据缓冲区和串口1相关联。
UART_Process_Send_ITR(&uart_use,1);//在串口中断服务程序中调用，用于发送数据,且此数据缓冲区和串口1相关联。
```

## 应用函数

```c
sendbyte_UART(&uart_use,0xff);//通过使用的串口发送一个值为0xff、大小为unsigned char的数据。
myprintf(&uart_use,"hello world!%d\r\n",32767);//通过使用的串口打印字符串，字符串的转换修饰符只支持%d:int。
vmyprintf(Uart_type *uart_example, char *str, va_list ap) reentrant;
void myprintf_setdigits(Uart_type *uart_example, char *str, ...) reentrant;
void vmyprintf_setdigits(Uart_type *uart_example, char *str, va_list ap) reentrant;
```
