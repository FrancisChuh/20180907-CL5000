#ifndef __COMPRESSOR_H
#define __COMPRESSOR_H

#include <stdint.h>


#include "LIN.h"

typedef enum E_CompStatus{
//    Reserved=0,
    NormalOff=1,
    FastOff=2,
    On=3,
}E_CompStatus;

typedef struct E_Comp_Status{
    uint8_t flags[2];
    uint8_t CurSpd;//当前转速
    uint8_t InputCur;//当前电流
    uint8_t InputPwr;//当前功率
    uint8_t ECUTmp;//压缩机控制器温度
    uint8_t InputVlt;//压缩机动力电池电压
    uint8_t RespErr;//ResponseError
}E_Comp_Status;

typedef struct E_Comp_CMD{
    uint8_t SetgSpd;//压缩机设定转速
    uint8_t Enbl;//压缩机使能运转信号
    uint8_t *HiVotRdy;//压缩机高压就绪信号
    uint8_t *LoVotRdy;//低压就绪信号
}E_Comp_CMD;

typedef struct E_Comp{
    E_Comp_Status status;
    E_Comp_CMD cmd;
}E_Comp;
#endif

