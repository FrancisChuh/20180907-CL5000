#ifndef _KEYFUNCTION_H__
#define _KEYFUNCTION_H__

#include "common.h"

typedef struct
{
	int16_t Set_Fan_Last;   //��˪�ָ�Ŀ�����
	int16_t Mode_PPS_Last;  //��˪�ָ�Ŀ��ģʽ
	u8 AC_IN_Status_Last;      //��˪�ָ�Ŀ��AC״̬
	u8 PTC_IN_Status_Last;      //��˪�ָ�Ŀ��PTC״̬
	u8 REC_Status_Last;     //��˪�ָ�Ŀ��ѭ��ģʽ
	u16 AUTO_Flag_Last;			//AUTO״̬
	
	int16_t Tem_Purpose;			//�¶Ȼ���
	int16_t Tem_Slave_Purpose;		//����ʻ�¶Ȼ���
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
extern signed char fanpwmduty_PPS;//Ŀ�����PWM
//extern signed char fanpwmduty_now;//���ڷ���PWM
extern FDEF_Last_TypeDef s_FDEF_Last;
extern u8 exit_FDEF;//�˳���˪��־
extern u8 Fan_manual;//��˪�ֶ�����

#endif
