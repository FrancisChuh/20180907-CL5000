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
	// ×表示不存在
}CHn;

typedef enum Input_cfg
{
	Rising,               //上升沿捕捉
	Falling,              //下降沿捕捉
	Rising_or_Falling     //跳变沿捕捉
}Input_cfg;

/*********************** PWM **************************/
void FTM_PWM_init(FTMn, CHn, uint32_t freq, uint8_t duty);  //初始化FTM的PWM功能并设置频率、占空比。设置通道输出占空比。同一个FTM，各通道的PWM频率是一样的，共3个FTM
void FTM_PWM_Duty(FTMn, CHn,uint8_t duty);    //设置通道占空比,占空比为 （duty * 精度） % ，如果 FTM_PRECISON 定义为 1000 ，duty = 100 ，则占空比 100*0.1%=10%
void Start_FTM(FTMn ftmn);
void FTM_Input_init(FTMn, CHn, Input_cfg);

#endif  //_FTM_H_
