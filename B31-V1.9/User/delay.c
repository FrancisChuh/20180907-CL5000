#include "delay.h"

static unsigned int SysTick_ms;

void SysTick_Handler(void)
{
	if(SysTick_ms > 0)
	{ 
		SysTick_ms--;
	}
}

void delay_ms(unsigned int ms)
{
	SysTick_ms = ms;
	SysTick_Config(SystemCoreClock / 1000);	
  while(SysTick_ms != 0);
	SysTick->CTRL =0x00;
}
