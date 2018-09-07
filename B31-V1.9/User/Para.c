#include "para.h"
#include "absacc.h"

Para_data_TypeDef s_Para_Data __at (0x1FFFF000);
u8 cha[123]={0};

u8 Board_Para_Read(void)
{
  u8 EEPROM_KEY_OK;
  u16 tem;
  
  __disable_irq();
  tem=FLASH_Read(VERIFIED_SECTOR*FLASH_SECTOR_SIZE);
  if(tem==EEPROM_KEY)
  {
    s_Para_Data.EE_Flag=EEPROM_KEY;       //状态有效位，0xAA55表示存储数据有效
    s_Para_Data.E_MoterSTEP_SAVED=FLASH_Read(VERIFIED_SECTOR*FLASH_SECTOR_SIZE+2);    //每1代表的电流值
    EEPROM_KEY_OK=1;                                                                            
  }                                                                                        
  else                                                                                     
  {                                                                                        
//   s_Para_Data.EE_Flag=tem;//预设值
//   s_Para_Data.Crruent_Per=AD_CRRUENT_PER;
//    s_Para_Data.Crruent_Mid=AD_CRRUENT_MIDDLE;
//    s_Para_Data.Temper_IN_OFS=0;
    EEPROM_KEY_OK=0;
  }
  __enable_irq();
   return EEPROM_KEY_OK;
}

void Save_Para(void)
{
	if(s_Para_Data.E_MoterSTEP_SAVED!=E_MoterSTEP)
	{
		__disable_irq();
		s_Para_Data.EE_Flag=EEPROM_KEY;
		s_Para_Data.E_MoterSTEP_SAVED=E_MoterSTEP;
		FLASH_Init(SystemBusClock);
		FLASH_EraseSector(VERIFIED_SECTOR*FLASH_SECTOR_SIZE);
		FLASH_Program(VERIFIED_SECTOR*FLASH_SECTOR_SIZE,(u8*)&s_Para_Data,Para_data_Length);  /* write data to erased sector */
		__enable_irq();
	}
}
//end
