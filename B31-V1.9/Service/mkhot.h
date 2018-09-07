#include <stdint.h>
#include "SKEAZ1284.h"
#include <stdio.h>
#include "process.h"

#define SET_TO_BATTERY  4600 	//三通阀调整到电池侧 右通
#define SET_TO_CABIN    505		//三通阀调整到乘员舱 左通
#define SET_VOL_ERR  50
#define PTC_POWER_MAX 7000		//PTC最大功率请求

#define QUICK_CHARGE 2        //快充
#define SLOW_CHARGE 1         //慢充
#define ON_ROAD 0             //行车放电
#define T_OFFSET 5            //设定温度偏移量

#define PUMP_STOP_DUTY 95 //100-95=5,水泵<10停转
#define PUMP_FULL_DUTY 10 //100-10=90,水泵90%满转速

void PTC_Mode_Control(void);	//模式判断
void Battery_Mode(void);	//单电池模式
void Cabin_Mode(void);		//乘员舱模式
void Both_Mode(void);		//双热模式
void PTC_Stop_Mode(void); 

//void TriTap_State_Set(u16 tritap_state);		//设置三通阀状态

u16 PTC_Power_Set(u16 temperature_set, u16 temperature_get);	 //设置PTC输出功率
u16 Heat_Request(u16 get_cabin_power, u16 get_battery_power);	 //计算制热功率总需求
//u16 TriTap_State_Get(u16 get_cabin_power, u16 get_battery_power);//计算三通阀比例
void Pump_Process(void);
u16 PTC_POWER_FIND(u16 T_PTC_set);
u16 TWV_Pos_FIND(float twv_cabin_battery_t );
u16 PTC_Temperature_FIND(void);


extern u16 PTC_cabin_power_O;            //乘员舱需求的PTC功率  用于输出给VCU

extern u16 TWV_Pos;

extern u8 Pumb_Start_flag ;
extern u8 Pumb_Stop_flag ;
//extern int8_t PTC_temperature;

