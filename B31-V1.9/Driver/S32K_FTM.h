#ifndef _S32K_FTM_H_
#define _S32K_FTM_H_

#include "common.h"

typedef enum FTMn
{
	SFTM0,
	SFTM1,
	SFTM2,
	SFTM3
}FTMn;

typedef enum CHn
{
	//   --FTM0--  --FTM1--  --FTM2--
	CH0,   //     
	CH1,   //     
	CH2,   //     
	CH3,   //     
	CH4,   //     
	CH5,   //     
	CH6,   //     
	CH7    //     
	// ����ʾ������
}CHn;

typedef enum Input_cfg
{
	Rising,               //�����ز�׽
	Falling,              //�½��ز�׽
	Rising_or_Falling     //�����ز�׽
}Input_cfg;

/*********************** PWM **************************/
void FTM_PWM_init(FTMn, CHn, uint32_t freq, uint8_t duty);  //��ʼ��FTM��PWM���ܲ�����Ƶ�ʡ�ռ�ձȡ�����ͨ�����ռ�ձȡ�ͬһ��FTM����ͨ����PWMƵ����һ���ģ���3��FTM
void FTM_PWM_Duty(FTMn, CHn,uint8_t duty);    //����ͨ��ռ�ձ�,ռ�ձ�Ϊ ��duty * ���ȣ� % ����� FTM_PRECISON ����Ϊ 1000 ��duty = 100 ����ռ�ձ� 100*0.1%=10%
void Start_FTM(FTMn ftmn);
void FTM_Input_init(FTMn, CHn, Input_cfg);

#endif  //_FTM_H_
