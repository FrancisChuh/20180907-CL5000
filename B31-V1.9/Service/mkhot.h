#include <stdint.h>
#include "SKEAZ1284.h"
#include <stdio.h>
#include "process.h"

#define SET_TO_BATTERY  4600 	//��ͨ����������ز� ��ͨ
#define SET_TO_CABIN    505		//��ͨ����������Ա�� ��ͨ
#define SET_VOL_ERR  50
#define PTC_POWER_MAX 7000		//PTC���������

#define QUICK_CHARGE 2        //���
#define SLOW_CHARGE 1         //����
#define ON_ROAD 0             //�г��ŵ�
#define T_OFFSET 5            //�趨�¶�ƫ����

#define PUMP_STOP_DUTY 95 //100-95=5,ˮ��<10ͣת
#define PUMP_FULL_DUTY 10 //100-10=90,ˮ��90%��ת��

void PTC_Mode_Control(void);	//ģʽ�ж�
void Battery_Mode(void);	//�����ģʽ
void Cabin_Mode(void);		//��Ա��ģʽ
void Both_Mode(void);		//˫��ģʽ
void PTC_Stop_Mode(void); 

//void TriTap_State_Set(u16 tritap_state);		//������ͨ��״̬

u16 PTC_Power_Set(u16 temperature_set, u16 temperature_get);	 //����PTC�������
u16 Heat_Request(u16 get_cabin_power, u16 get_battery_power);	 //�������ȹ���������
//u16 TriTap_State_Get(u16 get_cabin_power, u16 get_battery_power);//������ͨ������
void Pump_Process(void);
u16 PTC_POWER_FIND(u16 T_PTC_set);
u16 TWV_Pos_FIND(float twv_cabin_battery_t );
u16 PTC_Temperature_FIND(void);


extern u16 PTC_cabin_power_O;            //��Ա�������PTC����  ���������VCU

extern u16 TWV_Pos;

extern u8 Pumb_Start_flag ;
extern u8 Pumb_Stop_flag ;
//extern int8_t PTC_temperature;

