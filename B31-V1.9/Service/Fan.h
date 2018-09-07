#ifndef __FAN_H
#define __FAN_H


#include "common.h"
#include "adc.h"
#include "TB9102.h"

typedef void FAN_PROC(uint8_t);

typedef struct FAN_Close{
    struct TB9102   *tb9102;
    uint8_t         tb9102_pin;
}FAN_Close;

typedef struct Fan{
    ADC_Proc            *fan_vol;
    uint8_t             level;
    FTMn                ftmn;
    CHn                 ch;
    struct FAN_Close    close;
}Fan;

void fan_update(void);
void fan_change_level(Fan *fan,uint8_t level);


void front_fan_change_level(uint8_t level);
void rear_fan_change_level(uint8_t level);

void fan_test(uint8_t level);

#endif
