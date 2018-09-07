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
/*   程序文件名：RTC.c         										                        */
/*   Filename  ：RTC.c         			                        						  */
/*   作者      ：何晓东								                        		        */
/*   Author    ：Jack									                        	    	    */
/*   日期      ：10/23/2017						                        				    */
/*   Date      ：10/23/2017						                        					  */
/*   当前版本  ：1.0									                        				    */
/*   Version	 ：1.0                                                      */
/*   实现目的  ：RTC初始化									                        		  */
/*   Purpose   ：RTC_Init                                                 */
/**************************************************************************/
/*   修改记录  ：无                                                       */
/*   序号 , MM/DD/YYYY,版本，修改者，修改内容(最近的修改记录在最上面)     */
/*   Modi Report：                                                        */
/*   Index，Date，Version，Author, content                                */
/**************************************************************************/

#include "RTC.h"

u8 RTC_Flag=0;
u8 RTC_Sleep_Flag=0;

void Board_RTC_Init(void)
{
	SIM->SCGC	|= SIM_SCGC_RTC_MASK; //使能RTC时钟
	RTC->MOD = 10; //从0数到9复位
  if (RTC_Out)
	{
		SIM_PINSEL0 |=SIM_PINSEL_RTCPS_MASK;   //PTC5输出
		RTC->SC= RTC_SC_RTCO_MASK;     //输出使能
  }
  if (RTC_IntEn)
	{
		NVIC_Init(RTC_IRQn,3);
		RTC->SC |= RTC_SC_RTIE_MASK; //RTC中断使能
	}
	else
	{
		NVIC_DisableIRQ(RTC_IRQn);
		RTC->SC &= ~RTC_SC_RTIE_MASK; //RTC中断禁能
	}
	RTC->SC &= ~(RTC_SC_RTCLKS_MASK | RTC_SC_RTCPS_MASK);
	RTC->SC |= RTC_SC_RTCLKS(RTC_CLKSRC_1KHZ) | RTC_SC_RTCPS(RTC_CLK_PRESCALER_100); 
}

void Sleep_RTC_Init(void)
{
  RTC->MOD = 4000;//1小时，不准
	RTC->SC &= ~(RTC_SC_RTCLKS_MASK | RTC_SC_RTCPS_MASK);
	RTC->SC |= RTC_SC_RTCLKS(RTC_CLKSRC_1KHZ) | RTC_SC_RTCPS(RTC_CLK_PRESCALER_1000);
}

void Sleep_RTC_DeInit(void)
{
  RTC->MOD = 10;   //1秒钟，不准
	RTC->SC &= ~(RTC_SC_RTCLKS_MASK | RTC_SC_RTCPS_MASK);
	RTC->SC |= RTC_SC_RTCLKS(RTC_CLKSRC_1KHZ) | RTC_SC_RTCPS(RTC_CLK_PRESCALER_100);
}

void RTC_IRQHandler(void)
{
	RTC_SC |= RTC_SC_RTIF_MASK;
  
  if(RTC_Sleep_Flag)
  {
    RTC_Sleep_Flag=0;
  }
  else
  {
    RTC_Flag=1;
  }
}
//end
