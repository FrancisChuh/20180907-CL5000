#include "B31_Config.h"


/*传感器*/
AC_Sensors B31_Sensors={
    .TsensorOUTCAR  = &AD_TsensorOUTCAR   , //车外温度传感器
    .TsensorINCAR   = &AD_TsensorINCAR    ,  //车内温度传感器
    .TsensorEVA     = &AD_TsensorEVA      ,    //蒸发器温度传感器
    .TsensorFoot_CO = &AD_TsensorFoot_CO  ,//吹脚温度传感器，副驾驶
    .TsensorFace_CO = &AD_TsensorFace_CO  ,//吹面温度传感器，副驾驶
    .TsensorFoot_PA = &AD_TsensorFoot_PA  ,//吹脚温度传感器，驾驶
    .TsensorFace_PA = &AD_TsensorFace_PA  ,//吹面温度传感器，驾驶
    .WTsensor2      = &AD_WTsensor2       ,//电池水温传感器:确定没搞错？
    .WTsensor1      = &AD_WTsensor1       ,//电机水温传感器:确定没搞错？
    .P_TPsensor1    = &AD_P_TPsensor1     ,//高压压力传感器1
    //日照传感器
};

/*执行器*/
AC_Actuators B31_Acutators={
    .Intake_Run     =&Intake_Run,       //内外循环
    .Mode_Run       =&Mode_Run,         //模式执行器
    .TempACT_CO_Run =&TempACT_CO_Run,   //副驾驶温度执行器
    .TempACT_PA_Run =&TempACT_PA_Run,   //驾驶温度执行器
    .DES_ACT_Run    =&DES_ACT_Run,      //后模式执行器
};

/*鼓风机*/
AC_FANS B31_Fans={
    .front_fan_proc=&front_fan_change_level,
    .rear_fan_proc =&rear_fan_change_level,
};

/**/

/*总成*/
AC B31={
    .sensors=&B31_Sensors,
    .actuators=&B31_Acutators,
    .fans=&B31_Fans,
    
    //
    
    //控制面板
};




