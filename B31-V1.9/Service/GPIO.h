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
/*   程序文件名：GPIO.h         										                      */
/*   Filename  ：GPIO.h         			                        						*/
/*   作者      ：何晓东								                        		        */
/*   Author    ：Jack									                        	    	    */
/*   日期      ：10/23/2017						                        				    */
/*   Date      ：10/23/2017						                        					  */
/*   当前版本  ：1.0									                        				    */
/*   Version	 ：1.0                                                      */
/*   实现目的  ：I/O初始化									                        		  */
/*   Purpose   ：GPIO_Init                                                */
/**************************************************************************/
/*   修改记录  ：无                                                       */
/*   序号 , MM/DD/YYYY,版本，修改者，修改内容(最近的修改记录在最上面)     */
/*   Modi Report：                                                        */
/*   Index，Date，Version，Author, content                                */
/**************************************************************************/
        
#ifndef _GPIO_H_
#define _GPIO_H_

#include "common.h"

#define LIN_SLP2_OUT			PTE14 //17,预留LINsleep
#define LIN_WAKE2_OUT			PTE3  //18,预留
#define LIN_TX2						PTE12 //19
#define LIN_RX2						PTD17 //20

#define LIN_SLP1_OUT			PTD15 //22,预留LINsleep
#define LIN_WAKE1_OUT			PTE9  //23,预留
#define LIN_TX1						PTD14 //24
#define LIN_RX1						PTD13 //25

#define REAR_FANPWM				PTB4	//28
#define FRONT_FANPWM			PTC3	//29

#define CAN_TX_pin				PTB1	//53
#define CAN_RX_pin				PTB0	//54
#define CANSTB_OUT				PTC9	//55



#define M_PWM_RESERVED1		    PTA17	//62
#define M_PWM_RESERVED2		    PTB17	//63

#define M_POWER_EN_OUT		PTA12	//90

#define SWD_CLK						PTC4	//96
#define SWD_RESET					PTA5	//97
#define SWD_DIO						PTA4	//98


void Board_GPIO_Init(void);               //所有I/O口的初始化
void SW_PowerPM25(SW_STATUS new_status);  //PM2.5电源使能
void SW_ESV(SW_STATUS new_status);        //电磁阀电源开关
void SW_Negativeion(SW_STATUS new_status); //负离子电源开关
void SW_CANSTB(SW_STATUS new_status);     //CAN模块Standby
void SW_Power5V(SW_STATUS new_status);    //5V电源使能
void SW_EXP(SW_STATUS new_status); //电磁膨胀阀电源开关
void SW_LIN1_SLP(SW_STATUS new_status);//LIN模块SLEEP模式，低有效
void SW_LIN2_SLP(SW_STATUS new_status); //LIN模块SLEEP模式，低有效
void SW_TP9102(SW_STATUS new_status);
void SW_AQS(SW_STATUS new_status); //AQS电源使能


void Board_GPIO_OutL(void);

#endif /* GPIO_H_ */
