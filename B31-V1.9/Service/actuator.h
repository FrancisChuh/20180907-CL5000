#ifndef ACTUATOR_H
#define ACTUATOR_H

#include "common.h"

#include "MOTOR_DRIVE.h"
#include "adc.h"


#define INTAKE_ANG  210
#define OUTTAKE_ANG 3885

#define REAR_INTAKE_ANG 1180
#define REAR_OUTTAKE_ANG 2048

#define FULL_COOL    498
#define FULL_WARM    3604


#define MODE_01      409
#define MODE_02      1228
#define MODE_03      2048
#define MODE_04      2867
#define MODE_05      3686


typedef void ACTUATOR_PROC(uint8_t);

typedef void ACTUATOR_FUNC(void);

typedef struct ACTUATOR
{
    ACTUATOR_FUNC *CW;  //正转
    ACTUATOR_FUNC *ACW; //反转
    ACTUATOR_FUNC *STOP;
    int16_t       *ANG; //角度
    const int16_t *ANG_LEVEL;
    int16_t        ANG_ERROR;
    int8_t        ANG_LEVEL_CNT;
    uint16_t      count_down;      //倒计时
}ACTUATOR;


void Intake_Run(uint8_t level);
void DES_ACT_Run(uint8_t level);
void Mode_Run(uint8_t level);
void TempACT_CO_Run(uint8_t level);
void TempACT_PA_Run(uint8_t level);



void actuator_run(ACTUATOR *actuator,uint8_t Level);
#endif

