#include "KeyFunction.h"

u8 Fan_manual=0;//��˪�ֶ�����

signed char fanpwmduty_PPS=0;//Ŀ�����PWM
//signed char fanpwmduty_now=0;//���ڷ���PWM

FDEF_Last_TypeDef s_FDEF_Last={0};
u8 exit_FDEF=0;//�˳���˪��־

void AC_ON_OFF(u8 NewState)
{
//  if(NewState==0)//�ر�AC
//  {
//		GPIO_SetBits(LED_AC_Port,LED_AC_Pin);//��LED
//		GPIO_ResetBits(M_AC_Port,M_AC_Pin);//�ؼ̵���
//  }
//  else//��AC
//  {
//    GPIO_ResetBits(LED_AC_Port,LED_AC_Pin);//��LED
//		if(s_AD_Val.ADVal_TEVA>s_Heat_Cap.AC_ON_TEM)//�¶ȸ���
//		{
//			GPIO_SetBits(M_AC_Port,M_AC_Pin);//���̵���
//		}
//		else if(s_AD_Val.ADVal_TEVA<s_Heat_Cap.AC_OFF_TEM)//�¶Ⱥܵ���
//		{
//			GPIO_ResetBits(M_AC_Port,M_AC_Pin);//�ؼ̵���
//		}
//  }
}

void INTake_ON_OFF(u8 NewState)
{
//  if(NewState==REC_OUTTake)
//  {
//    GPIO_SetBits(LED_INTAKE_Port,LED_INTAKE_Pin);//��LED
//  }
//  else
//  {
//    GPIO_ResetBits(LED_INTAKE_Port,LED_INTAKE_Pin);//��LED
//  }
}

void RDEF_ON_OFF(u8 NewState)
{
//	if(NewState==0)
//  {
//		GPIO_ResetBits(M_RDEF_Port,M_RDEF_Pin);//�غ��˪
//		GPIO_SetBits(LED_RDEF_Port,LED_RDEF_Pin);//��LED
//	}
//  else
//  {
//		GPIO_SetBits(M_RDEF_Port,M_RDEF_Pin);
//		GPIO_ResetBits(LED_RDEF_Port,LED_RDEF_Pin);//��LED 
//  }
}

void FDEF_ON_OFF(u8 NewState)
{
//	if(NewState==5)
//	{
//		GPIO_ResetBits(LED_FDEF_Port,LED_FDEF_Pin);//��LED 
//	}
//	else
//	{
//		GPIO_SetBits(LED_FDEF_Port,LED_FDEF_Pin);//��LED 
//	}
}

void SEATL_ON_OFF(u8 NewState)
{
//	if(NewState==0)
//	{
//		GPIO_ResetBits(M_SEATL_Port,M_SEATL_Pin);//�رռ���
//		GPIO_SetBits(LED_SEATL_Port,LED_SEATL_Pin);//��LED 
//	}
//	else
//	{
//		GPIO_SetBits(M_SEATL_Port,M_SEATL_Pin);//ʹ�ܼ���
//		GPIO_ResetBits(LED_SEATL_Port,LED_SEATL_Pin);//��LED 
//	}
}

void SEATR_ON_OFF(u8 NewState)
{
//	if(NewState==0)
//	{
//		GPIO_ResetBits(M_SEATR_Port,M_SEATR_Pin);//�رռ���
//		GPIO_SetBits(LED_SEATR_Port,LED_SEATR_Pin);//��LED 
//	}
//	else
//	{
//		GPIO_SetBits(M_SEATR_Port,M_SEATR_Pin);//ʹ�ܼ���
//		GPIO_ResetBits(LED_SEATR_Port,LED_SEATR_Pin);//��LED 
//	}
}

void ESV_Process(void)
{
  if(s_Heat_Cap.ESV_STATUS)
  {    
    SW_ESV(SW_ON);
  }
  else
  {
    SW_ESV(SW_OFF);
  }
}
  
void PM25_Process(void)
{
	if(s_Heat_Cap.PM25_STATUS)
	{
		if(s_PM25_IN.PM25_DENSITY>75)
		{
			SW_Negativeion(SW_ON);
			s_Heat_Cap.Negativeion_STATUS=1;
		}
		else if(s_PM25_IN.PM25_DENSITY<50)
		{
			SW_Negativeion(SW_OFF);
			s_Heat_Cap.Negativeion_STATUS=0;
		}
	}
	else
	{
		SW_Negativeion(SW_OFF);
		s_Heat_Cap.Negativeion_STATUS=0;		
	}
}

void FDEF2_ON_OFF(u8 NewState)
{
//	{
//		GPIO_ResetBits(M_FDEF_Port,M_FDEF_Pin);//�رռ���
//	}
//	else
//	{
//		GPIO_SetBits(M_FDEF_Port,M_FDEF_Pin);//ʹ�ܼ���
//	}
}


void FDEF_FANCHANGE(void)//��˪��������
{
  if((s_Heat_Cap.Mode_PPS==MODEFDEF)&&(s_Heat_Cap.Set_Fan!=50)&&(Fan_manual!=1))//�����˪���䣬����5����*10��
	{
		if(s_Heat_Cap.Set_Fan>50)
		{
			s_Heat_Cap.Set_Fan--;
		}
		else if(s_Heat_Cap.Set_Fan<50)
		{
			s_Heat_Cap.Set_Fan++;
		}
	}
	
	if((s_Heat_Cap.Set_Fan!=s_FDEF_Last.Set_Fan_Last)&&(exit_FDEF==1))//�˳���˪
	{
		if(s_Heat_Cap.Set_Fan>s_FDEF_Last.Set_Fan_Last)
		{
			s_Heat_Cap.Set_Fan--;
		}
		else if(s_Heat_Cap.Set_Fan<s_FDEF_Last.Set_Fan_Last)
		{
			s_Heat_Cap.Set_Fan++;
		}
		if(s_Heat_Cap.Set_Fan==s_FDEF_Last.Set_Fan_Last)
		{
			exit_FDEF=0;//�˳���˪���
		}
	}
}
//end
