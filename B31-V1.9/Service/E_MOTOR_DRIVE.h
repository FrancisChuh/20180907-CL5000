#ifndef _E_MOTOR_DRIVE_H__
#define _E_MOTOR_DRIVE_H__

#include "common.h"


void E_Moter_Ctrl(void);//电子膨胀阀动作
void PHASE_A1_H(void);
void PHASE_A1_L(void);
void PHASE_A2_H(void);
void PHASE_A2_L(void);
void PHASE_B1_H(void);
void PHASE_B1_L(void);
void PHASE_B2_H(void);
void PHASE_B2_L(void);
void E_Moter_CW_CCW(FunctionalState CW);//转动一步
void E_Moter_Stop(void);
void SW_FAN(SW_STATUS new_status);

extern u16 E_MoterSTEP;
extern u16 E_MoterSTEP_PPS;

#endif
