#ifndef _PID_H__
#define _PID_H__


#include "PROCESS.H"
#include "E_MOTOR_DRIVE.h"

#define E_MoterSTEP_Max 480
#define E_MoterSTEP_Min 30

double PID_Calcu(double set_sh, double P, double T);
double CalcuSH(double P, double T);
void E_Moter_Control_Fun(void);

double PID_Change(void);
void E_Moter_Pos_Init(void);

extern u8 E_MoterFLAG;
extern double ActualSH;
#endif
