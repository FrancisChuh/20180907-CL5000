#ifndef _PWT_H__
#define _PWT_H__

#include <stdint.h>
#include "SKEAZ1284.h"
#include "kea128_ftm.h"
#include "stdio.h"
#include "RTC.H"

void Board_PWT_Init(void);

extern float PWM_Duty_Read;

#endif
