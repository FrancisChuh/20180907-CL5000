#ifndef _TEMPER_H__
#define _TEMPER_H__

#include "common.h"

int16_t convert_temper_EVA(u16 temper_hex);//ʮ�����Ƶ�ѹֵת10�����¶�ֵ
int16_t convert_Temper_OUT(u16 temper_hex);//ʮ�����Ƶ�ѹֵת10�����¶�ֵ
int16_t convert_Temper_IN(u16 temper_hex);//ʮ�����Ƶ�ѹֵת10�����¶�ֵ
int16_t convert_Temper_Pipe(u16 temper_hex);//��·�¶�
int16_t convert_Temper_wind(u16 temper_hex);//����¶�ʮ�����Ƶ�ѹֵת10�����¶�ֵ

#endif 
