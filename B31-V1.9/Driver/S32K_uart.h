#ifndef __S32K_UART_H__
#define __S32K_UART_H__

#include <stdint.h>

#include "port.h"
#include "pin_cfg.h"
#include "S32_gpio.h"

typedef enum  UARTn
{
	//初始化默认配置       --TXD--      --RXD--     可以复用其他通道，请在<<pin_cfg.h>>自行修改 uart_init
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

void Uart_Init(UARTn uratn, uint32_t baud);//初始化uartx模块
void Uart_DeInit(UARTn uartn);//去初始化：完成引脚复用和时钟
/********************************************************************/

#endif /* __UART_H__ */
