/**************************************************************************/
/*    ���쳬���߿Ƽ��ɷ����޹�˾          ��Ȩ����                        */
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
/*   �����ļ�����RTC.c         										                        */
/*   Filename  ��RTC.c         			                        						  */
/*   ����      ��������								                        		        */
/*   Author    ��Jack									                        	    	    */
/*   ����      ��10/23/2017						                        				    */
/*   Date      ��10/23/2017						                        					  */
/*   ��ǰ�汾  ��1.0									                        				    */
/*   Version	 ��1.0                                                      */
/*   ʵ��Ŀ��  ��RTC��ʼ��									                        		  */
/*   Purpose   ��RTC_Init                                                 */
/**************************************************************************/
/*   �޸ļ�¼  ����                                                       */
/*   ��� , MM/DD/YYYY,�汾���޸��ߣ��޸�����(������޸ļ�¼��������)     */
/*   Modi Report��                                                        */
/*   Index��Date��Version��Author, content                                */
/**************************************************************************/

#include "RTC.h"

u8 RTC_Flag=0;
u8 RTC_Sleep_Flag=0;

void Board_RTC_Init(void)
{
	SIM->SCGC	|= SIM_SCGC_RTC_MASK; //ʹ��RTCʱ��
	RTC->MOD = 10; //��0����9��λ
  if (RTC_Out)
	{
		SIM_PINSEL0 |=SIM_PINSEL_RTCPS_MASK;   //PTC5���
		RTC->SC= RTC_SC_RTCO_MASK;     //���ʹ��
  }
  if (RTC_IntEn)
	{
		NVIC_Init(RTC_IRQn,3);
		RTC->SC |= RTC_SC_RTIE_MASK; //RTC�ж�ʹ��
	}
	else
	{
		NVIC_DisableIRQ(RTC_IRQn);
		RTC->SC &= ~RTC_SC_RTIE_MASK; //RTC�жϽ���
	}
	RTC->SC &= ~(RTC_SC_RTCLKS_MASK | RTC_SC_RTCPS_MASK);
	RTC->SC |= RTC_SC_RTCLKS(RTC_CLKSRC_1KHZ) | RTC_SC_RTCPS(RTC_CLK_PRESCALER_100); 
}

void Sleep_RTC_Init(void)
{
  RTC->MOD = 4000;//1Сʱ����׼
	RTC->SC &= ~(RTC_SC_RTCLKS_MASK | RTC_SC_RTCPS_MASK);
	RTC->SC |= RTC_SC_RTCLKS(RTC_CLKSRC_1KHZ) | RTC_SC_RTCPS(RTC_CLK_PRESCALER_1000);
}

void Sleep_RTC_DeInit(void)
{
  RTC->MOD = 10;   //1���ӣ���׼
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
