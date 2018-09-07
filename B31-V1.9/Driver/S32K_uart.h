#ifndef __S32K_UART_H__
#define __S32K_UART_H__

#include <stdint.h>

#include "port.h"
#include "pin_cfg.h"
#include "S32_gpio.h"

typedef enum  UARTn
{
	//��ʼ��Ĭ������       --TXD--      --RXD--     ���Ը�������ͨ��������<<pin_cfg.h>>�����޸� uart_init
	UART0,    //           
	UART1,    //           
	UART2    //                    
}UARTn;


typedef struct UART_INIT{
    uint32_t baudrate;
    PTxn    tx_pin;
    PTxn    rx_pin;
    IRQn_Type irqn;
}UART_INIT;


/********************************************************************/

void Uart_Init(UARTn uratn, uint32_t baud);//��ʼ��uartxģ��
void Uart_DeInit(UARTn uartn);//ȥ��ʼ����������Ÿ��ú�ʱ��
/********************************************************************/

#endif /* __UART_H__ */
