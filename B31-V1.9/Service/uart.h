#ifndef _UART_H__
#define _UART_H__

#include "common.h"
#include "S32K_uart.h"

#define RX_MAX_LEN 200

extern u8 UART1_Rx_Buf[RX_MAX_LEN];
extern u8 UART1_Rx_Len;
extern u8 UART1_Tx_Buf[8];

void Board_UART_Init(uint32_t UART_BaudRate);
void UART_SendChar(unsigned char chr);
unsigned char UART_GetChar(void);
u8 Uart2_RxData(void);
int WriteUART1 (u8* buffer, uint32_t count);

#endif /* _UART_H__ */
