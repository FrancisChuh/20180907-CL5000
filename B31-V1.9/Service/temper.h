#ifndef _TEMPER_H__
#define _TEMPER_H__

#include "common.h"

int16_t convert_temper_EVA(u16 temper_hex);//十六进制电压值转10进制温度值
int16_t convert_Temper_OUT(u16 temper_hex);//十六进制电压值转10进制温度值
int16_t convert_Temper_IN(u16 temper_hex);//十六进制电压值转10进制温度值
int16_t convert_Temper_Pipe(u16 temper_hex);//管路温度
int16_t convert_Temper_wind(u16 temper_hex);//风道温度十六进制电压值转10进制温度值

#endif 
