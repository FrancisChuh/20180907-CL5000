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
/*   �����ļ�����PWT.c         										                        */
/*   Filename  ��PWT.c         			                        						  */
/*   ����      ��������								                        		        */
/*   Author    ��Jack									                        	    	    */
/*   ����      ��10/23/2017						                        				    */
/*   Date      ��10/23/2017						                        					  */
/*   ��ǰ�汾  ��1.0									                        				    */
/*   Version	 ��1.0                                                      */
/*   ʵ��Ŀ��  ��PWT��ʼ��									                        		  */
/*   Purpose   ��PWT_Init                                                 */
/**************************************************************************/
/*   �޸ļ�¼  ����                                                       */
/*   ��� , MM/DD/YYYY,�汾���޸��ߣ��޸�����(������޸ļ�¼��������)     */
/*   Modi Report��                                                        */
/*   Index��Date��Version��Author, content                                */
/**************************************************************************/

#include "pwt.h"

float PWM_Duty_Read=0;

void Board_PWT_Init(void)
{
	SIM_SCGC |= SIM_SCGC_PWT_MASK;              //ʹ��PWTʱ��
	PWT->R1 &=(~PWT_R1_PCLKS_MASK);             //ѡ��BUSclk
	PWT->R1 |=PWT_R1_PINSEL(1);                 //ѡ��PWT_IN1
	PWT->R1 |=PWT_R1_EDGE(1);                   //
	PWT->R1 |=PWT_R1_PRE(7);//128��Ƶ��3Hz-1500Hz
	PWT->R1 |=PWT_R1_PWTIE_MASK;//ʹ��PWT�ж�
	PWT->R1 |=PWT_R1_PRDYIE_MASK;//ʹ��PWT��ȡ�ж�
  PWT_R1|=PWT_R1_POVIE_MASK;	 	//ʹ��PWT����ж�
	PWT->R1 |=PWT_R1_PWTEN_MASK;//ģ��ʹ��
  NVIC_Init(PWT_IRQn,3);	
}

float Board_PWT_Read(void)
{
	u16 PPW,NPW;

	if(PWT->R1 & PWT_R1_PWTRDY_MASK)//�ɼ����
  {
    PWT->R1 &= ~PWT_R1_PWTRDY_MASK;//����
    PPW=(PWT->R1>>16)&0xffff;
    NPW=(PWT->R2)&0xffff;
  }
  else if(PWT->R1 & PWT_R1_PWTOV_MASK)//���
  {
    PWT->R1 &= ~PWT_R1_PWTOV_MASK;//����
    PPW=0;
    NPW=0;
  }
  return PPW/(NPW+PPW);
}

void PWT_IRQHandler(void)
{
  PWM_Duty_Read=Board_PWT_Read();
}

//end
