#include "uart.h"

u8 UART1_Rx_Buf[RX_MAX_LEN]={0};
u8 UART1_Rx_Len=0;
u8 UART1_Tx_Buf[8]={0};

void Board_UART_Init(uint32_t UART_BaudRate)
{
    Uart_Init(UART2,UART_BaudRate);
	NVIC_Init(LPUART2_RxTx_IRQn,3);
}

void UART2_IRQHandler()
{
	u8 tem;
  if(LPUART2->STAT & LPUART_STAT_OR_MASK)//溢出
  {
    tem=LPUART2->DATA;
  }
	else if(LPUART0->STAT & LPUART_STAT_RDRF_MASK)  //接收中断
	{
    tem=LPUART2->DATA;
		if(UART1_Rx_Len<RX_MAX_LEN)
		{
			UART1_Rx_Buf[UART1_Rx_Len++]=tem;
		}
	}
}




//int fputc(int ch, FILE *f)
//{
//	UART_SendChar(ch);
//	return (ch);
//}

//int fputc(int ch,FILE *f)
//{
//	UART_SendData(UART1,(u8)ch);  
//	return ch; 		
//}

//int GetKey(void)
//{

//}

//int InitializeUART()
//{
//	return 0;
//}

//int ReadUARTN()
//{
//	return 0; 	
//}
//end
