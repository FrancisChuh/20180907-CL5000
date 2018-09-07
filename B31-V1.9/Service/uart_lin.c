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
    lin_uart.uartn->STAT |=LPUART_STAT_BRK13_MASK;     //13λ�ϵ�
    lin_uart.uartn->STAT |=LPUART_STAT_LBKDE_MASK;     //��LIN�ϵ���
    lin_uart.uartn->BAUD |=LPUART_BAUD_LBKDIE_MASK;    //���ϵ����ж�
    NVIC_Init(lin_uart.uart_init.irqn,3);                            //�ж����ȼ�����;
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


