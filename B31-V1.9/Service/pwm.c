/**************************************************************************/
/*    重庆超力高科技股份有限公司          版权所有                        */
/**************************************************************************/
/*   @@BEGAIN_INTERNAL_LEGAL@@                                            */
/*                                                                        */
/*                   Copyright(C) Description                          	  */
/*     CHONGQING CHAOLI HI-TECH Co.,Ltd. Chongqing, China   				      */
/*     Unpublished work-rights reserved under the China Copyright Act.  	*/
/*     Use,duplication, or disclosure by the government is subject to   	*/
/*     restrictions set forth in the CDTT commercial license agreement. 	*/
/*																		                                    */
/*   @@END_INTERNAL_LEGAL@@												                        */
/**************************************************************************/
/*   程序文件名：PWM.c         										                        */
/*   Filename  ：PWM.c         			                        						  */
/*   作者      ：何晓东								                        		        */
/*   Author    ：Jack									                        	    	    */
/*   日期      ：10/23/2017						                        				    */
/*   Date      ：10/23/2017						                        					  */
/*   当前版本  ：1.0									                        				    */
/*   Version	 ：1.0                                                      */
/*   实现目的  ：PWM初始化									                        		  */
/*   Purpose   ：PWM_Init                                                 */
/**************************************************************************/
/*   修改记录  ：无                                                       */
/*   序号 , MM/DD/YYYY,版本，修改者，修改内容(最近的修改记录在最上面)     */
/*   Modi Report：                                                        */
/*   Index，Date，Version，Author, content                                */
/**************************************************************************/

#include "pwm.h"

PWM_duty_Struct s_PWM_Duty;

void Board_PWM_Init(void)
{	
	FTM_PWM_init(FRONT_FANPWM_FTM,FRONT_FANPWM_CHANNEL,FRONT_FANPWM_Frequency,80);
	FTM_PWM_init(REAR_FANPWM_FTM,REAR_FANPWM_CHANNEL,REAR_FANPWM_Frequency,80);
	Start_FTM(REAR_FANPWM_FTM);
	
//	FTM_Input_init(SFTM0,CH3,Rising_or_Falling); //采集只能采集频率比自身高的
//	NVIC_Init(FTM0_Ovf_Reload_IRQn,14);
//	NVIC_Init(FTM0_Ch2_Ch3_IRQn,13);
//	Start_FTM(SFTM0);
}

void Board_PWM_Deinit(void)
{
    
}
#if 0
void TWV_CW(void) //
{
  FTM_PWM_set_duty_N(TWVPWM_FTM,TWVPWM_CHANNEL,TWV_CW_DUTY);
}

void TWV_ACW(void)
{
  FTM_PWM_set_duty_N(TWVPWM_FTM,TWVPWM_CHANNEL,TWV_ACW_DUTY);
}

void TWV_STOP(void)
{
  FTM_PWM_set_duty_N(TWVPWM_FTM,TWVPWM_CHANNEL,TWV_STOP_DUTY);
}
#endif

void FTM0_Ch2_Ch3_IRQHandler(void)
{	
	if(FTM0->CONTROLS[3].CnSC & FTM_CnSC_CHF_MASK)
	{
		FTM0->CONTROLS[3].CnSC &=~FTM_CnSC_CHF_MASK;
		if(FTM0->CONTROLS[3].CnSC & FTM_CnSC_CHIS_MASK)//上升沿
		{
			s_PWM_Duty.N_Count=FTM0->CONTROLS[3].CnV+1;
		}
		else
		{
			s_PWM_Duty.P_Count=FTM0->CONTROLS[3].CnV+1;
		}
		s_PWM_Duty.Total_Count=s_PWM_Duty.P_Count+s_PWM_Duty.N_Count;
		s_PWM_Duty.Duty_Cycle=s_PWM_Duty.P_Count*1000/s_PWM_Duty.Total_Count;
	}
}

void FTM0_Ovf_Reload_IRQHandler(void)
{
	if(FTM0->SC & FTM_SC_TOF_MASK)
	{
		FTM0->SC &=~FTM_SC_TOF_MASK;
		s_PWM_Duty.Total_Count=0;
		s_PWM_Duty.Duty_Cycle=0;
	}
}

//end
