#ifndef _S32_PIT_H_
#define _S32_PIT_H_

typedef enum
{
    LPIT0_Ch0=0,
    LPIT0_Ch1=1,
    LPIT0_Ch2=2,
    LPIT0_Ch3=3
}PITn;

#include "common.h"

void Pit_Init(PITn pitn, uint32_t cnt);             //初始化PITn，并设置定时时间(单位为bus时钟周期)

#endif  //_PIT_H_
