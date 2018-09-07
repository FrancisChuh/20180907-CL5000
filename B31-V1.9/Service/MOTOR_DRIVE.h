#ifndef _MOTOR_DRIVE_H__
#define _MOTOR_DRIVE_H__

#include "COMMON.h"

#include "TB9102.h"


void MODE_ACW(void);
void MODE_CW(void);
void Stop_Mode_Motor(void);

void REC_ACW(void);
void REC_CW(void);
void Stop_REC_Motor(void);


void DesACT_ACW(void);
void DesACT_CW(void);
void Stop_DesACT_Motor(void);


void TempCO_ACW(void);
void TempCO_CW(void);
void Stop_TempCO_Motor(void);


void TempPA_ACW(void);
void TempPA_CW(void);
void Stop_TempPA_Motor(void);



void TEMP_ACW(void);
void TEMP_CW(void);

void Stop_TEMP_Motor(void);
void Stop_Mode_Motor_P(void);
void Stop_TEMP_Motor_P(void);
void Stop_REC_Motor_P(void);


                            
void Moter_Ctrl(void);//Ö´ÐÐÆ÷Çý¶¯

#endif
