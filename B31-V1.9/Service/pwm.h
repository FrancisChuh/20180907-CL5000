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
/*   程序文件名：PWM.h         										                        */
/*   Filename  ：PWM.h         			                        						  */
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
#ifndef _PWM_H__
#define _PWM_H__

#include "common.h"

#define REAR_FANPWM_FTM SFTM0                   
#define REAR_FANPWM_CHANNEL CH4
#define REAR_FANPWM_Frequency 1000

#define FRONT_FANPWM_FTM REAR_FANPWM_FTM
#define FRONT_FANPWM_CHANNEL CH3
#define FRONT_FANPWM_Frequency REAR_FANPWM_Frequency

//#define FANPWM_FTM FTM2
//#define FANPWM_CHANNEL CHANNEL0
//#define FANPWM_PIN FTM2_CHANNEL0_PH0
//#define FANPWM_Frequency PUMPPWM_Frequency

#define TWV_CW_DUTY 95
#define TWV_ACW_DUTY 5
#define TWV_STOP_DUTY 50


typedef struct
{
	uint16_t P_Count;
	uint16_t N_Count;
	uint32_t Total_Count;
	uint16_t Duty_Cycle;
}PWM_duty_Struct;

//#define PWMLCD_default 30
//#define PWMLCD_DarkMode 10

void Board_PWM_Init(void);
void TWV_CW(void);
void TWV_ACW(void);
void TWV_STOP(void);

extern PWM_duty_Struct s_PWM_Duty;

#endif
