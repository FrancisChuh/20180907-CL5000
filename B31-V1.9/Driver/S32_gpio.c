#include "S32_gpio.h"

static GPIO_MemMapPtr GPIOX[5] = {PTA, PTB, PTC, PTD, PTE}; 
PORT_MemMapPtr PTX[5] = {PORTA, PORTB, PORTC, PORTD, PORTE};

/*************************************************************************
*  �������ƣ�gpio_enable_port
*  ����˵������������GPIO�˿ڵ�ʱ�ӡ� ���߲��������á�
*  ����˵����
*  �������أ���
*  �޸�ʱ�䣺2015-5-15   �Ѳ���
*  ��    ע��
*************************************************************************/
void Gpio_Enable_Port (void)
{
	PCC->PCCn[PCC_PORTA_INDEX]=  PCC_PCCn_CGC_MASK;
	PCC->PCCn[PCC_PORTB_INDEX]=  PCC_PCCn_CGC_MASK;
	PCC->PCCn[PCC_PORTC_INDEX]=  PCC_PCCn_CGC_MASK;
	PCC->PCCn[PCC_PORTD_INDEX]=  PCC_PCCn_CGC_MASK;
	PCC->PCCn[PCC_PORTE_INDEX]=  PCC_PCCn_CGC_MASK;
}
/*************************************************************************
*  �������ƣ�gpio_Interrupt_init
*  ����˵������ʼ��GPIO�ж�Դ
*  ����˵����PTxn        �˿ں�
*            GPIO_CFG    �˿�״̬
*            mode        �ж�״̬ 
*  �������أ���
*  �޸�ʱ�䣺2015-5-15   �Ѳ���
*  ��    ע��
*************************************************************************/

void Gpio_Interrupt_Init(PTxn ptxn, GPIO_CFG cfg, port_pcr mode) 
{
  uint8_t  px;
  uint32_t altcfg ;
  if((cfg == GP_IN)||(cfg == GP_IN_DOWN)||(cfg == GP_IN_UP))
	{
    px = ptxn>> 5 ;   
    altcfg= cfg + ALT1 + mode ;
    port_init(ptxn,altcfg);
    GPIOX[px]->PDDR&= ~(1 << (ptxn&0x1f));  //���ö˿ڷ���Ϊ���� 
  }
}

/*************************************************************************
*  �������ƣ�gpio_init
*  ����˵������ʼ��gpio
*  ����˵����PTxn        �˿ں�
*            GPIO_CFG    �˿�״̬
*            uint8_t       �������״̬ 1 ��0
*  �������أ���
*  �޸�ʱ�䣺2015-5-15   �Ѳ���
*  ��    ע��
*************************************************************************/
void Gpio_Init(PTxn ptxn, GPIO_CFG cfg, FlagStatus sata)
{ 
	vuint32 PCRcfg;

	if( (cfg  == GP_IN) || (cfg == GP_IN_UP) || (cfg == GP_IN_DOWN) )//�˿ڷ����������
	{
		PCRcfg =cfg+ALT1 ;
		port_init(ptxn,PCRcfg);
		GPIOX[ptxn>> 5]->PDDR &= ~(1 << (ptxn&0x1f));  //���ö˿ڷ���Ϊ���� 
	}
    else if(cfg == GP_DIS)
    {
        port_init(ptxn,ALT0);
    }
	else
	{
		port_alt(ptxn,ALT1) ;        //���ö˿ڷ���Ϊ���
    GPIOX[ptxn>> 5]->PDDR |= (1 << (ptxn&0x1f));        // GPIO PDDR �ܽź� ��1������Ӧ�ܽ�����Ϊ�˿ڷ������
		//�˿��������/        
		if(sata == RESET)
		{     
			GPIOX[ptxn>> 5]->PDOR &= ~(1 << (ptxn&0x1f));   // GPIO PDOR �ܽź� ��0������Ӧ�ܽ�����Ϊ�˿�����͵�ƽ
    }
		else
		{
			GPIOX[ptxn>> 5]->PDOR  |= (1 << (ptxn&0x1f));   // GPIO PDOR �ܽź� ��1������Ӧ�ܽ�����Ϊ�˿�����ߵ�ƽ
    }
  }
}



/*************************************************************************
*  �������ƣ�gpio_set
*  ����˵������������״̬
*  ����˵����PTxn        �˿ں�
*            uint8_t       �������״̬ 1 ��0
*  �������أ���
*  �޸�ʱ�䣺2015-5-15   �Ѳ���
*  ��    ע��
*************************************************************************/
void Gpio_Set(PTxn ptxn,FlagStatus sata)
{
  if(sata)
	{
		GPIOX[ptxn>> 5]->PSOR |= (1 << (ptxn&0x1f));   // GPIO PDOR �ܽź� ��1������Ӧ�ܽ�����Ϊ�˿�����ߵ�ƽ
	}
  else
	{
		GPIOX[ptxn>> 5]->PCOR |= (1 << (ptxn&0x1f));   // GPIO PDOR �ܽź� ��0������Ӧ�ܽ�����Ϊ�˿�����͵�ƽ 
	}
}
/*************************************************************************
*  �������ƣ�gpio_turn
*  ����˵�������ŷ�ת
*  ����˵����PTxn        �˿ں�
*  �������أ���
*  �޸�ʱ�䣺2015-5-15   �Ѳ���
*  ��    ע��
*************************************************************************/
void Gpio_Toggle(PTxn ptxn)
{
	GPIOX[ptxn>> 5]->PTOR |= (1 << (ptxn&0x1f));   // GPIO PTOR �ܽź�  
}

/*************************************************************************
*  �������ƣ�gpio_get
*  ����˵�������ŷ�ת
*  ����˵����PTxn        �˿ں�
*  �������أ���
*  �޸�ʱ�䣺2015-5-15   �Ѳ���
*  ��    ע��
*************************************************************************/
FlagStatus Gpio_Get(PTxn ptxn)
{
	if((GPIOX[ptxn>> 5]->PDIR>>(ptxn&0x1f)) &0x01)// GPIO PDIR �ܽź�  
	{
		return SET;
	}
	else
	{
		return RESET;
	}
}
               
