#ifndef _PARA_H__
#define _PARA_H__

#include <stdint.h>
#include "SKEAZ1284.h"
#include <stdio.h>
#include "process.h"

typedef struct
{
	u16 EE_Flag;//状态有效位，0xAA55表示存储数据有效
  u16 E_MoterSTEP_SAVED;  //电子膨胀阀位置信息
	u16 Crruent_Mid;  //中间值500左右
  u16 Temper_OUT_Set ;  //恒定温度设定
	
	u16 EE2_Flag;//状态有效位，0xAA55表示存储数据有效
  u16 E_M2oterSTEP_SAVED;  //电子膨胀阀位置信息
	u16 Crrue2nt_Mid;  //中间值500左右
  u16 Tempe2r_OUT_Set ;  //恒定温度设定
	
}Para_data_TypeDef;

#define Para_data_Length 16 //8*1

#define EEPROM_KEY 0xAA55

u8 Board_Para_Read(void);
void Save_Para(void);

extern Para_data_TypeDef s_Para_Data;


#endif
