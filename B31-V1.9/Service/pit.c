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
/*   �����ļ�����PIT.c         										                        */
/*   Filename  ��PIT.c         			                        						  */
/*   ����      ��������								                        		        */
/*   Author    ��Jack									                        	    	    */
/*   ����      ��10/23/2017						                        				    */
/*   Date      ��10/23/2017						                        					  */
/*   ��ǰ�汾  ��1.0									                        				    */
/*   Version	 ��1.0                                                      */
/*   ʵ��Ŀ��  ��PIT��ʼ������ʱ15ms��50ms	                        		  */
/*   Purpose   ��PIT_Init                                                 */
/**************************************************************************/
/*   �޸ļ�¼  ����                                                       */
/*   ��� , MM/DD/YYYY,�汾���޸��ߣ��޸�����(������޸ļ�¼��������)     */
/*   Modi Report��                                                        */
/*   Index��Date��Version��Author, content                                */
/**************************************************************************/

#include "pit.h"

u16 time_ms_flag=0;

void Board_PIT_Init(void)//�������ڶ�ʱ
{
	Pit_Init(LPIT0_Ch0,1000);			//1ms�ж�
	NVIC_Init(LPIT0_Ch0_IRQn,5);
	Pit_Init(LPIT0_Ch1,10000);		//10ms�ж�
	NVIC_Init(LPIT0_Ch1_IRQn,6);
//	Pit_Init(LPIT0_Ch2,3000);		//3ms�ж�
//	NVIC_Init(LPIT0_Ch2_IRQn,7);
//	Pit_Init(LPIT0_Ch3,1000);		//1ms�ж�
//	NVIC_Init(LPIT0_Ch3_IRQn,8);
}

void LPIT0_Ch0_IRQHandler()//1ms//����
{
	static u8 time_1ms_count=0;

	LPIT0->MSR |= LPIT_MSR_TIF1_MASK;   //���жϱ�־λ
	time_1ms_count++;
	if(time_1ms_count>14)
	{
		time_ms_flag |= time_15ms_flag_MASK;
		time_1ms_count=0;
	}
	time_ms_flag |= time_1ms_flag_MASK;
}

void LPIT0_Ch1_IRQHandler()//10ms//����
{
  static u8 time_10ms_count=0;

	LPIT0->MSR |= LPIT_MSR_TIF0_MASK;   //���жϱ�־λ
  time_10ms_count++;
  if(time_10ms_count>99)
  {
    time_ms_flag |= time_1000ms_flag_MASK;
    time_10ms_count=0;
  }
  time_ms_flag |= time_10ms_flag_MASK;
  if(time_10ms_count%2==1)
  {
    time_ms_flag |= time_20ms_flag_MASK;
  }
  if(time_10ms_count%5==1)
  {
    time_ms_flag |= time_50ms_flag_MASK;
  }
  if(time_10ms_count%10==1)
  {
    time_ms_flag |= time_100ms_flag_MASK;
  }
  if(time_10ms_count%20==1)
  {
    time_ms_flag |= time_200ms_flag_MASK;
  }
  if(time_10ms_count%50==1)
  {
    time_ms_flag |= time_500ms_flag_MASK;
  }
}


//end
