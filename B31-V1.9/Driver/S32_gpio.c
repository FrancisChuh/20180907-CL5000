#include "S32_gpio.h"

static GPIO_MemMapPtr GPIOX[5] = {PTA, PTB, PTC, PTD, PTE}; 
PORT_MemMapPtr PTX[5] = {PORTA, PORTB, PORTC, PORTD, PORTE};

/*************************************************************************
*  函数名称：gpio_enable_port
*  功能说明：加载所有GPIO端口的时钟。 供高层驱动调用。
*  参数说明：
*  函数返回：无
*  修改时间：2015-5-15   已测试
*  备    注：
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
*  函数名称：gpio_Interrupt_init
*  功能说明：初始化GPIO中断源
*  参数说明：PTxn        端口号
*            GPIO_CFG    端口状态
*            mode        中断状态 
*  函数返回：无
*  修改时间：2015-5-15   已测试
*  备    注：
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
    GPIOX[px]->PDDR&= ~(1 << (ptxn&0x1f));  //设置端口方向为输入 
  }
}

/*************************************************************************
*  函数名称：gpio_init
*  功能说明：初始化gpio
*  参数说明：PTxn        端口号
*            GPIO_CFG    端口状态
*            uint8_t       引脚输出状态 1 ，0
*  函数返回：无
*  修改时间：2015-5-15   已测试
*  备    注：
*************************************************************************/
void Gpio_Init(PTxn ptxn, GPIO_CFG cfg, FlagStatus sata)
{ 
	vuint32 PCRcfg;

	if( (cfg  == GP_IN) || (cfg == GP_IN_UP) || (cfg == GP_IN_DOWN) )//端口方向控制输入
	{
		PCRcfg =cfg+ALT1 ;
		port_init(ptxn,PCRcfg);
		GPIOX[ptxn>> 5]->PDDR &= ~(1 << (ptxn&0x1f));  //设置端口方向为输入 
	}
    else if(cfg == GP_DIS)
    {
        port_init(ptxn,ALT0);
    }
	else
	{
		port_alt(ptxn,ALT1) ;        //设置端口方向为输出
    GPIOX[ptxn>> 5]->PDDR |= (1 << (ptxn&0x1f));        // GPIO PDDR 管脚号 置1，即对应管脚配置为端口方向输出
		//端口输出数据/        
		if(sata == RESET)
		{     
			GPIOX[ptxn>> 5]->PDOR &= ~(1 << (ptxn&0x1f));   // GPIO PDOR 管脚号 清0，即对应管脚配置为端口输出低电平
    }
		else
		{
			GPIOX[ptxn>> 5]->PDOR  |= (1 << (ptxn&0x1f));   // GPIO PDOR 管脚号 置1，即对应管脚配置为端口输出高电平
    }
  }
}



/*************************************************************************
*  函数名称：gpio_set
*  功能说明：设置引脚状态
*  参数说明：PTxn        端口号
*            uint8_t       引脚输出状态 1 ，0
*  函数返回：无
*  修改时间：2015-5-15   已测试
*  备    注：
*************************************************************************/
void Gpio_Set(PTxn ptxn,FlagStatus sata)
{
  if(sata)
	{
		GPIOX[ptxn>> 5]->PSOR |= (1 << (ptxn&0x1f));   // GPIO PDOR 管脚号 置1，即对应管脚配置为端口输出高电平
	}
  else
	{
		GPIOX[ptxn>> 5]->PCOR |= (1 << (ptxn&0x1f));   // GPIO PDOR 管脚号 清0，即对应管脚配置为端口输出低电平 
	}
}
/*************************************************************************
*  函数名称：gpio_turn
*  功能说明：引脚反转
*  参数说明：PTxn        端口号
*  函数返回：无
*  修改时间：2015-5-15   已测试
*  备    注：
*************************************************************************/
void Gpio_Toggle(PTxn ptxn)
{
	GPIOX[ptxn>> 5]->PTOR |= (1 << (ptxn&0x1f));   // GPIO PTOR 管脚号  
}

/*************************************************************************
*  函数名称：gpio_get
*  功能说明：引脚反转
*  参数说明：PTxn        端口号
*  函数返回：无
*  修改时间：2015-5-15   已测试
*  备    注：
*************************************************************************/
FlagStatus Gpio_Get(PTxn ptxn)
{
	if((GPIOX[ptxn>> 5]->PDIR>>(ptxn&0x1f)) &0x01)// GPIO PDIR 管脚号  
	{
		return SET;
	}
	else
	{
		return RESET;
	}
}
               
