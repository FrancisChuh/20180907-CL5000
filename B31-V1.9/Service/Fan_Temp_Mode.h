#ifndef _Fan_Temp_Mode_H__
#define _Fan_Temp_Mode_H__

#include "COMMON.h"

//////#define INTAKE_VOL  4724//
////#define INTAKE_VOL 4600
//////#define OUTTAKE_VOL 276
////#define OUTTAKE_VOL 300
#define INTAKE_VOL 3000
#define OUTTAKE_VOL 2500

#define MODE_FACE_VOL 780
#define MODE_FAFE_VOL 1640
#define MODE_FEET_VOL 2500
#define MODE_FEDE_VOL 3360
#define MODE_FDEF_VOL 4220
#define MODE_VOL_ERR  50

#define TEMP_LO_VOL   608
#define TEMP_MID_VOL  2379
#define TEMP_HI_VOL   4403
#define TEMP_VOL_ERR  50

//#define PWM_LEVEL_1 25
//#define PWM_LEVEL_2 33
//#define PWM_LEVEL_3 40
//#define PWM_LEVEL_4 50
//#define PWM_LEVEL_5 61
//#define PWM_LEVEL_6 74
//#define PWM_LEVEL_7 85
//#define PWM_LEVEL_8 100

#define TWV_LO_VOL   300
#define TWV_MID_VOL  2500
#define TWV_HI_VOL   4700


void SC_TEMP_PPS(int16_t SC_TEMP);
void SC_MODE_PPS(u8 SC_MODE);
void SC_FANSPEED_PPS(u8 level);//level*10
void SC_REC_PPS(u8 SC_REC);
void PWM_FAN_CHANGE(void);
void E_MoterSTEP_CHANGE(void);//电子膨胀阀改变
void SC_LCDLight_PWM(u8 DARK);
void TWV_Process(void);

#endif
