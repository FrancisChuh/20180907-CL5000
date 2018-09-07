#ifndef __APTC_H
#define __APTC_H

#include <stdint.h>

#include "LIN.h"

typedef struct APTC_STATUS{
    uint8_t HvVlt;  //母线电压
    uint8_t HvCur;  //母线电流
    uint8_t ActlPwr;    //实际功率
    uint8_t LoVlt;      //低压电压
    uint8_t RiTmp;      //右侧本体温度
    uint8_t LeTmp;      //左侧本体温度
    uint8_t Flags[2];   //各个状态标识
}APTC_STATUS;

typedef struct APTC_CMD{
    uint8_t enable;//使能
    uint8_t RiTarTmp;//右侧目标温度
    uint8_t LeTarTmp;//左侧目标温度
    uint8_t RiTarPwr;//右侧目标功率
    uint8_t LeTarPwr;//左侧目标功率
    uint8_t HiVltRdy;//高压就绪
    uint8_t LoVltRdy;//低压就绪
}APTC_CMD;

typedef struct APTC{
    APTC_CMD            cmd;
    APTC_STATUS         status;
    uint8_t             input_tmp[8];
}APTC;

#endif
