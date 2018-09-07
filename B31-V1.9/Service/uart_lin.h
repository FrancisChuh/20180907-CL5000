#ifndef __UART_LIN_H
#define __UART_LIN_H

#include <stdint.h>

#include "S32K_uart.h"

typedef struct LinUart{
    UART_INIT       uart_init;
    LPUART_Type     *uartn;
}LinUart;

#define LIN_MASTER_TX_BreakF() 	LPUART1->CTRL |= LPUART_CTRL_SBK_MASK,\
																LPUART1->CTRL &=~LPUART_CTRL_SBK_MASK;

#endif

