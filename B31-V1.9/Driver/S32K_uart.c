#include "S32K_uart.h"

volatile LPUART_Type *UARTx[3] = {LPUART0, LPUART1, LPUART2}; //��������ָ�����鱣�� UARTx �ĵ�ַ


//
void LPUART_Init(UARTn uartn, uint32_t baud)
{
    ;
}

/*************************************************************************
*  �������ƣ�uart_init
*  ����˵������ʼ�����ڣ����ò�����
*  ����˵����UARTn       ģ��ţ�UART0~UART5��
*            baud        �����ʣ���9600��19200��56000��115200��
*  �������أ���
*  �޸�ʱ�䣺2012-1-20
*  ��    ע���ڹٷ��������޸�
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
        PCC->PCCn[PCC_LPUART0_INDEX] = PCC_PCCn_CGC_MASK+PCC_PCCn_PCS(1);   //ʹ���ⲿ����8M������Ϊʱ��Դ
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
        PCC->PCCn[PCC_LPUART1_INDEX] = PCC_PCCn_CGC_MASK+PCC_PCCn_PCS(1);   //ʹ���ⲿ����8M������Ϊʱ��Դ
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
        PCC->PCCn[PCC_LPUART2_INDEX] = PCC_PCCn_CGC_MASK +PCC_PCCn_PCS(1);    //ʹ���ⲿ����8M������Ϊʱ��Դ
    }

    
	//���� UART ����ͨѶ�����ʡ�ͨ������ UART ģ��Ĳ����ʼĴ���
	sbr = (uint16_t)(CPU_XTAL_CLK_HZ / (baud ));
	sbr /= 23 ;
	uartx->BAUD = LPUART_BAUD_OSR(22)+LPUART_BAUD_SBR(sbr);

	//����bit����
	uartx->BAUD &= ~LPUART_BAUD_M10_MASK ;//7-9bit
	//������żУ��
//	LPUART_CTRL_REG(UARTx[uratn]) |= LPUART_CTRL_PT_MASK + LPUART_CTRL_PE_MASK ;
//	LPUART_CTRL_REG(UARTx[uratn]) |= (LPUART_CTRL_TXINV_MASK  );
	uartx->CTRL |= (LPUART_CTRL_TE_MASK | LPUART_CTRL_RE_MASK );	/* �����ͺͽ��� */
	uartx->CTRL |= LPUART_CTRL_RIE_MASK ;//�������ж�
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
        PCC->PCCn[PCC_LPUART1_INDEX] = PCC_PCCn_CGC_MASK+PCC_PCCn_PCS(0);   //ʹ���ⲿ����8M������Ϊʱ��Դ
    }
    else if(uartn==UART2)
    {
        if(UART2_RX == PTD17)port_alt(UART2_RX,ALT0);
        else port_alt(UART2_RX,ALT2);
        if(UART2_TX == PTE12)port_alt(UART2_TX,ALT0);
        else port_alt(UART2_TX,ALT2);
        PCC->PCCn[PCC_LPUART2_INDEX] = PCC_PCCn_CGC_MASK +PCC_PCCn_PCS(0);    //ʹ���ⲿ����8M������Ϊʱ��Դ
    }
}
