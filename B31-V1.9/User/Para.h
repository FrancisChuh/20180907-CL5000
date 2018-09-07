#ifndef _PARA_H__
#define _PARA_H__

#include <stdint.h>
#include "SKEAZ1284.h"
#include <stdio.h>
#include "process.h"

typedef struct
{
	u16 EE_Flag;//״̬��Чλ��0xAA55��ʾ�洢������Ч
  u16 E_MoterSTEP_SAVED;  //�������ͷ�λ����Ϣ
	u16 Crruent_Mid;  //�м�ֵ500����
  u16 Temper_OUT_Set ;  //�㶨�¶��趨
	
	u16 EE2_Flag;//״̬��Чλ��0xAA55��ʾ�洢������Ч
  u16 E_M2oterSTEP_SAVED;  //�������ͷ�λ����Ϣ
	u16 Crrue2nt_Mid;  //�м�ֵ500����
  u16 Tempe2r_OUT_Set ;  //�㶨�¶��趨
	
}Para_data_TypeDef;

#define Para_data_Length 16 //8*1

#define EEPROM_KEY 0xAA55

u8 Board_Para_Read(void);
void Save_Para(void);

extern Para_data_TypeDef s_Para_Data;


#endif
