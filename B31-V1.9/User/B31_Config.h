#ifndef __AC_CORE_H
#define __AC_CORE_H

#include <stdint.h>
#include "fan.h"
#include "actuator.h"
#include "adc.h"


//传感器
typedef struct AC_Sensors{
    ADC_Proc *TsensorOUTCAR; //车外温度传感器
    ADC_Proc *TsensorINCAR;  //车内温度传感器
    ADC_Proc *TsensorEVA;    //蒸发器温度传感器
    ADC_Proc *TsensorFoot_CO;//吹脚温度传感器，副驾驶
    ADC_Proc *TsensorFace_CO;//吹面温度传感器，副驾驶
    ADC_Proc *TsensorFoot_PA;//吹脚温度传感器，驾驶
    ADC_Proc *TsensorFace_PA;//吹面温度传感器，驾驶
    ADC_Proc *WTsensor2;//电池水温传感器:确定没搞错？
    ADC_Proc *WTsensor1;//电机水温传感器:确定没搞错？
    ADC_Proc *P_TPsensor1;//高压压力传感器1
    
    
    //日照强度传感器
    
    
 }AC_Sensors;

    
//执行器
typedef struct AC_Actuators{
    ACTUATOR_PROC *Intake_Run;//内外循环
    ACTUATOR_PROC *Mode_Run;//模式执行器
    ACTUATOR_PROC *TempACT_CO_Run;//副驾驶温度执行器
    ACTUATOR_PROC *TempACT_PA_Run;//驾驶温度执行器
    ACTUATOR_PROC *DES_ACT_Run;//后模式执行器
    
    
}AC_Actuators;

typedef struct AC_FANS{
    FAN_PROC *front_fan_proc;
    FAN_PROC *rear_fan_proc;
}AC_FANS;//鼓风机

typedef struct AC
{
    AC_Sensors *sensors;//各种传感器
    
    AC_Actuators *actuators;//执行器
    AC_FANS *fans;//鼓风机
    
    //PM2.5传感器
    //电动压缩机
    //风热ptc
    //水热ptc
    
    
    //控制面板
}AC;//空调



#endif
