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
/*   程序文件名：PWT.c         										                        */
/*   Filename  ：PWT.c         			                        						  */
/*   作者      ：何晓东								                        		        */
/*   Author    ：Jack									                        	    	    */
/*   日期      ：10/23/2017						                        				    */
/*   Date      ：10/23/2017						                        					  */
/*   当前版本  ：1.0									                        				    */
/*   Version	 ：1.0                                                      */
/*   实现目的  ：PWT初始化									                        		  */
/*   Purpose   ：PWT_Init                                                 */
/**************************************************************************/
/*   修改记录  ：无                                                       */
/*   序号 , MM/DD/YYYY,版本，修改者，修改内容(最近的修改记录在最上面)     */
/*   Modi Report：                                                        */
/*   Index，Date，Version，Author, content                                */
/**************************************************************************/

#include "pwt.h"

float PWM_Duty_Read=0;

void Board_PWT_Init(void)
{
	SIM_SCGC |= SIM_SCGC_PWT_MASK;              //使能PWT时钟
	PWT->R1 &=(~PWT_R1_PCLKS_MASK);             //选择BUSclk
	PWT->R1 |=PWT_R1_PINSEL(1);                 //选择PWT_IN1
	PWT->R1 |=PWT_R1_EDGE(1);                   //
	PWT->R1 |=PWT_R1_PRE(7);//128分频，3Hz-1500Hz
	PWT->R1 |=PWT_R1_PWTIE_MASK;//使能PWT中断
	PWT->R1 |=PWT_R1_PRDYIE_MASK;//使能PWT读取中断
  PWT_R1|=PWT_R1_POVIE_MASK;	 	//使能PWT溢出中断
	PWT->R1 |=PWT_R1_PWTEN_MASK;//模块使能
  NVIC_Init(PWT_IRQn,3);	
}

float Board_PWT_Read(void)
{
	u16 PPW,NPW;

	if(PWT->R1 & PWT_R1_PWTRDY_MASK)//采集完毕
  {
    PWT->R1 &= ~PWT_R1_PWTRDY_MASK;//清零
    PPW=(PWT->R1>>16)&0xffff;
    NPW=(PWT->R2)&0xffff;
  }
  else if(PWT->R1 & PWT_R1_PWTOV_MASK)//溢出
  {
    PWT->R1 &= ~PWT_R1_PWTOV_MASK;//清零
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
