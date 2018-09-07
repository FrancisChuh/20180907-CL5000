#include "S32K_uart.h"

volatile LPUART_Type *UARTx[3] = {LPUART0, LPUART1, LPUART2}; //定义三个指针数组保存 UARTx 的地址


//
void LPUART_Init(UARTn uartn, uint32_t baud)
{
    ;
}

/*************************************************************************
*  函数名称：uart_init
*  功能说明：初始化串口，设置波特率
*  参数说明：UARTn       模块号（UART0~UART5）
*            baud        波特率，如9600、19200、56000、115200等
*  函数返回：无
*  修改时间：2012-1-20
*  备    注：在官方例程上修改
*************************************************************************/
void Uart_Init(UARTn uratn, uint32_t baud)
{
	register uint16_t sbr;	//brfa;
    LPUART_Type *uartx=0;
    
    if(uratn==UART0)
    {
        uartx=LPUART0;
    }
    else if(uratn==UART1)
    {
        uartx=LPUART1;
    }
    else if(uratn==UART1)
    {
        uartx=LPUART2;
    }

    if(uartx== LPUART0)
    {
        if(UART0_RX == PTA2)
        {
            port_alt(UART0_RX,ALT6);
        }
        else if(UART0_RX == PTB0)
        {
            port_alt(UART0_RX,ALT2);
        }
        else
        {
            port_alt(UART0_RX,ALT4);
        }
        if(UART0_TX == PTA3)
        {
            port_alt(UART0_TX,ALT6);
        }
        else if(UART0_TX == PTB1)
        {
            port_alt(UART0_TX,ALT2);
        }
        else
        {
            port_alt(UART0_TX,ALT4);
        }
        PCC->PCCn[PCC_LPUART0_INDEX] = PCC_PCCn_CGC_MASK+PCC_PCCn_PCS(1);   //使用外部晶振8M晶振作为时钟源
    }
    else if (uartx== LPUART1)
    {
        if(UART1_TX == PTD14)
        {
            port_alt(UART1_TX,ALT3);
        }
        else
        {
            port_alt(UART1_TX,ALT2);
        }
        if(UART1_RX == PTD13)
        {
            port_alt(UART1_RX,ALT3);
        }
        else
        {
            port_alt(UART1_RX,ALT2);
        }
        PCC->PCCn[PCC_LPUART1_INDEX] = PCC_PCCn_CGC_MASK+PCC_PCCn_PCS(1);   //使用外部晶振8M晶振作为时钟源
    }
    else if(uartx == LPUART2)
    {
        if(UART2_RX == PTD17)
        {
            port_alt(UART2_RX,ALT3);
        }
        else
        {
            port_alt(UART2_RX,ALT2);
        }
        if(UART2_TX == PTE12)
        {
            port_alt(UART2_TX,ALT3);
        }
        else
        {
            port_alt(UART2_TX,ALT2);
        }
        PCC->PCCn[PCC_LPUART2_INDEX] = PCC_PCCn_CGC_MASK +PCC_PCCn_PCS(1);    //使用外部晶振8M晶振作为时钟源
    }

    
	//设置 UART 数据通讯波特率。通过设置 UART 模块的波特率寄存器
	sbr = (uint16_t)(CPU_XTAL_CLK_HZ / (baud ));
	sbr /= 23 ;
	uartx->BAUD = LPUART_BAUD_OSR(22)+LPUART_BAUD_SBR(sbr);

	//设置bit个数
	uartx->BAUD &= ~LPUART_BAUD_M10_MASK ;//7-9bit
	//设置奇偶校验
//	LPUART_CTRL_REG(UARTx[uratn]) |= LPUART_CTRL_PT_MASK + LPUART_CTRL_PE_MASK ;
//	LPUART_CTRL_REG(UARTx[uratn]) |= (LPUART_CTRL_TXINV_MASK  );
	uartx->CTRL |= (LPUART_CTRL_TE_MASK | LPUART_CTRL_RE_MASK );	/* 允许发送和接收 */
	uartx->CTRL |= LPUART_CTRL_RIE_MASK ;//开接收中断
}

void Uart_DeInit(UARTn uartn)
{
    if(uartn==UART0)
    {
        if(UART0_RX == PTA2)port_alt(UART0_RX,ALT0);
        else if(UART0_RX == PTB0)port_alt(UART0_RX,ALT0);
        else port_alt(UART0_RX,ALT0);
        if(UART0_TX == PTA3)port_alt(UART0_TX,ALT0);
        else if(UART0_TX == PTB1)port_alt(UART0_TX,ALT0);
		else port_alt(UART0_TX,ALT0);
        PCC->PCCn[PCC_LPUART0_INDEX] = PCC_PCCn_CGC_MASK+PCC_PCCn_PCS(0);
    }
    else if(uartn==UART1)
    {
        if(UART1_TX == PTD14)port_alt(UART1_TX,ALT0);
        else port_alt(UART1_TX,ALT0);
        if(UART1_RX == PTD13)port_alt(UART1_RX,ALT0);
        else port_alt(UART1_RX,ALT0);
        PCC->PCCn[PCC_LPUART1_INDEX] = PCC_PCCn_CGC_MASK+PCC_PCCn_PCS(0);   //使用外部晶振8M晶振作为时钟源
    }
    else if(uartn==UART2)
    {
        if(UART2_RX == PTD17)port_alt(UART2_RX,ALT0);
        else port_alt(UART2_RX,ALT2);
        if(UART2_TX == PTE12)port_alt(UART2_TX,ALT0);
        else port_alt(UART2_TX,ALT2);
        PCC->PCCn[PCC_LPUART2_INDEX] = PCC_PCCn_CGC_MASK +PCC_PCCn_PCS(0);    //使用外部晶振8M晶振作为时钟源
    }
}
