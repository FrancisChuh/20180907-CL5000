#ifndef _TEM_HUM_H__
#define _TEM_HUM_H__

#include "process.h"
#include "math.h"

typedef struct
{
    int16_t FDEF_TEM;			//自动除霜温度
    int16_t FDEF_HUM;       //自动除霜湿度
    int16_t DEW_TEM;      //露点温度
}AUTO_FDEF_TypeDef;

int16_t Tem_Dew(AUTO_FDEF_TypeDef* s_AUTO_FDEF_TypeDef);
void Get_Tem_Hum(void);

extern AUTO_FDEF_TypeDef s_DEW_Point;


#endif
