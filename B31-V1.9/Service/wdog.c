#include "wdog.h"

//CS1
#define WDOG_IntEnable		0 //看门狗中断使能
#define WDOG_WaitEnable		0	//wait模式使能
#define WDOG_StopEnable		0	//停止模式使能
#define WDOG_DebugEnable	0 //调试模式使能
#define WDOG_UpdateEnable	1	//修改wdog值使能

//CS2
#define WDOG_WinEnable	0
#define WDOG_Pres				1				// 256分频
#define WDOG_ClkSrc			WDOG_CLK_LPO

#define WDOG_TimeOut		1000  /*< 256*1000/128000,2秒*/
#define WDOG_WinTime		0

void Board_WDOG_Init(void)
{
	uint32_t cs1=WDOG_CS_EN_MASK |WDOG_CS_CMD32EN_MASK;
	
	__disable_irq();
	if(WDOG_IntEnable)
	{
		cs1 |= WDOG_CS_INT_MASK;
  }
	if(WDOG_StopEnable)
	{
		cs1  |= WDOG_CS_STOP_MASK;
	}
	if(WDOG_DebugEnable)
	{
		cs1  |= WDOG_CS_DBG_MASK;
	}
	if(WDOG_WaitEnable)
	{
		cs1  |= WDOG_CS_WAIT_MASK;
	}
	if(WDOG_UpdateEnable)
	{
		cs1 |= WDOG_CS_UPDATE_MASK;
	}
	if(WDOG_WinEnable)
	{
		cs1 |= WDOG_CS_WIN_MASK;
	}
	if(WDOG_Pres)
	{
		cs1 |= WDOG_CS_PRES_MASK;
	}
	cs1	|= WDOG_CS_CLK(WDOG_ClkSrc);
	
	/* write regisers */
	WDOG->CNT = 0xD928C520   ;            /* unlock watchdog first */
	while(!(WDOG->CS & WDOG_CS_ULK_MASK)){;}

//	WDOG->CS2   = cs2;
	WDOG->TOVAL = WDOG_TimeOut ;
	
	WDOG->WIN=WDOG_WinTime;
	
	WDOG->CS   = cs1;  /* enable WDOG */
	while(!(WDOG->CS & WDOG_CS_RCS_MASK)){;}
	__enable_irq();
}

void Board_WDOG_Feed(void)
{
	__disable_irq();
	WDOG->CNT = 0xB480A602; // write the 1st refresh word
	__enable_irq();
}

void Board_WDOG_Disable(void)
{
	__disable_irq();
	WDOG->CNT = 0xD928C520   ;            /* unlock watchdog first */
	while(!(WDOG->CS & WDOG_CS_ULK_MASK)){;}
	WDOG->CS &= ~WDOG_CS_EN_MASK;
	while(!(WDOG->CS & WDOG_CS_RCS_MASK)){;}
	__enable_irq();
}
//end
