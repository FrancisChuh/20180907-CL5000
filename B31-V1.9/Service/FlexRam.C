#include "flexram.h"

u32 *FlexRam_addr=(u32 *)(0x14000000);

void FlexRam_Init(void) 
{
	if((SIM->FCFG1 & SIM_FCFG1_DEPART_MASK) == SIM_FCFG1_DEPART_MASK)//没有配置
	{
		//配置EE大小
		FTFC->FCCOB[3] =0x80; 
		FTFC->FCCOB[2] =0x00; 
		FTFC->FCCOB[1] =0x00; 
		FTFC->FCCOB[0] =0x00; 
		
		FTFC->FCCOB[7] =0x02; //4KB的EEPROM
		FTFC->FCCOB[6] =0x04; //64K的Eflash，实际存储
		
		Flash_LaunchCommand();
		
		FTFC->FCCOB[3] =0x81; 
		FTFC->FCCOB[2] =0x00;
		Flash_LaunchCommand();
		while(!(FTFC->FCNFG & FTFC_FCNFG_EEERDY_MASK)){;}
	}
	else if(!(FTFC->FCNFG & FTFC_FCNFG_EEERDY_MASK))
	{
		FTFC->FCCOB[3] =0x81; 
		FTFC->FCCOB[2] =0x00;
		Flash_LaunchCommand();
		while(!(FTFC->FCNFG & FTFC_FCNFG_EEERDY_MASK)){;}
	}
}
