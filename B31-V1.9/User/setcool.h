#ifndef _SETCOOL_H__
#define _SETCOOL_H__

#include <stdint.h>
#include <stdio.h>
#include "PID.h"
#include "E_MOTOR_DRIVE.h"

typedef struct
{
	uint16_t    MotorSpeed;//压缩机速度(只考虑乘员舱侧)  
	float       AC_power;//总功率
	float       AC_BAT_power;//电池功率(双蒸模式下监听)
	float       Temp_TEVA;//蒸发器实际温度与目标温度差值
}FUNCTION_SELECT;

#define			CAR_COOL 				0
#define			BATTERY_COOL 		1
#define			DOUBLE_COOL 		2

#define			NO_ENOUGH 		  0
#define			Y_ENOUGH 				1

#define			NORMAL_DRIVE 		0
#define			SLOW_CHARGE 		1
#define			FAST_CHARGE 		2

#define     MAX_AC_POWER    7000
void Refrige(void);
void AC_Stop_Mode(void);
void SlowChargeRequire(void);
void FastChargeRequire(void);
void NormalDrive(void);
void IncarCoolMode(void);
void BatteryCoolMode(void);
void DoubleCoolMode(void);
uint16_t TXV_POWER(void);
uint16_t FindListSpeed(void);
uint16_t Exa_Temper(void);
uint16_t Power_to_Step(void);
void ACFAN_Proc(void);//冷凝风扇转速发送

extern FUNCTION_SELECT MODE_judge;
extern u8 E_Moter_ControlFLAG;
extern u16 MAX_MOTOR_SPEED;
extern u16 MIN_MOTOR_SPEED;
extern int16_t s_AD_TM_TEVA;
extern u8 ACFAN_PWM_DUTY;

#endif
