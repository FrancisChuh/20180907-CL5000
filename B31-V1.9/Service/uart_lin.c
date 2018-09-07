#include "uart_lin.h"



const LinUart lin_uart_1={
    .uart_init={.baudrate=19200, .tx_pin=PTB1, .rx_pin=PTB0, .irqn=LPUART1_RxTx_IRQn},
    .uartn=LPUART1,
};



void UartLIN_Init(LinUart lin_uart)
{
    UARTn uartn;
    if (lin_uart.uartn==LPUART0)
    {
        uartn=UART0;
    }
    else if(lin_uart.uartn==LPUART1)
    {
        uartn=UART1;
    }
    else if(lin_uart.uartn==LPUART2)
    {
        uartn=UART2;
    }
    
    Uart_Init(uartn,lin_uart.uart_init.baudrate);
    lin_uart.uartn->STAT |=LPUART_STAT_BRK13_MASK;     //13位断点
    lin_uart.uartn->STAT |=LPUART_STAT_LBKDE_MASK;     //开LIN断点检测
    lin_uart.uartn->BAUD |=LPUART_BAUD_LBKDIE_MASK;    //开断点检测中断
    NVIC_Init(lin_uart.uart_init.irqn,3);                            //中断优先级设置;
}

void UartLIN_Deinit(LinUart lin_uart)
{
    UARTn uartn;
    if (lin_uart.uartn==LPUART0)
    {
        uartn=UART0;
    }
    else if(lin_uart.uartn==LPUART1)
    {
        uartn=UART1;
    }
    else if(lin_uart.uartn==LPUART2)
    {
        uartn=UART2;
    }
    Uart_DeInit(uartn);
    NVIC_Init(lin_uart.uart_init.irqn,3); 
}


