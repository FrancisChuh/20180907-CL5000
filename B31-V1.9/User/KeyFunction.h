#ifndef _KEYFUNCTION_H__
#define _KEYFUNCTION_H__

#include "common.h"

typedef struct
{
	int16_t Set_Fan_Last;   //除霜恢复目标风量
	int16_t Mode_PPS_Last;  //除霜恢复目标模式
	u8 AC_IN_Status_Last;      //除霜恢复目标AC状态
	u8 PTC_IN_Status_Last;      //除霜恢复目标PTC状态
	u8 REC_Status_Last;     //除霜恢复目标循环模式
	u16 AUTO_Flag_Last;			//AUTO状态
	
	int16_t Tem_Purpose;			//温度缓存
	int16_t Tem_Slave_Purpose;		//副驾驶温度缓存
}FDEF_Last_TypeDef;


void AC_ON_OFF(u8 NewState);
void FDEF_FANCHANGE(void);
void INTake_ON_OFF(u8 NewState);
void RDEF_ON_OFF(u8 NewState);
void FDEF_ON_OFF(u8 NewState);
void SEATL_ON_OFF(u8 NewState);
void SEATR_ON_OFF(u8 NewState);
void FDEF2_ON_OFF(u8 NewState);
void ESV_Process(void);
void PM25_Process(void);

extern u8 AC_STATUS;
extern u8 PTC_STATUS;
extern signed char fanpwmduty_PPS;//目标风量PWM
//extern signed char fanpwmduty_now;//现在风量PWM
extern FDEF_Last_TypeDef s_FDEF_Last;
extern u8 exit_FDEF;//退出除霜标志
extern u8 Fan_manual;//除霜手动风量

#endif
