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
/*   程序文件名：CAN.c         										                        */
/*   Filename  ：CAN.c         			                        						  */
/*   作者      ：何晓东								                        		        */
/*   Author    ：Jack									                        	    	    */
/*   日期      ：10/23/2017						                        				    */
/*   Date      ：10/23/2017						                        					  */
/*   当前版本  ：1.0									                        				    */
/*   Version	 ：1.0                                                      */
/*   实现目的  ：CAN初始化									                        		  */
/*   Purpose   ：CAN_Init                                                 */
/**************************************************************************/
/*   修改记录  ：无                                                       */
/*   序号 , MM/DD/YYYY,版本，修改者，修改内容(最近的修改记录在最上面)     */
/*   Modi Report：                                                        */
/*   Index，Date，Version，Author, content                                */
/**************************************************************************/

#include "can.h"
#include "CAN_Protocol.h"

//11bit最大7FF
#define RX_NODE_ID	0x3E9

#define TX_NODE_ID	0x123//

#if (RX_NODE_ID>0x7ff || TX_NODE_ID>0x7ff )
	#error "11bit的ID最大0x7FF"
#endif

CANMsg CAN_RX_Msg;

u8 CAN_RX_Flag=0;

void Board_CAN_Init(void)
{
	CANInit(CAN0CH,500,RX_NODE_ID,0,1);
	NVIC_Init(CAN0_ORed_0_15_MB_IRQn,1);
	NVIC_Init(CAN0_Wake_Up_IRQn,15);
}

void CAN_TX(CANMsg *TxData)
{
	CANSendData(CAN0CH,TxData->ID,TxData->len,TxData->data);
}

void CAN_RX_Proc(void)          //接收处理,实时调用
{
    if(CAN_RX_Flag==1)
    {
        CAN_Proc_RX(&CAN_RX_Msg);
        CAN_RX_Flag=0;
    }
}

void CAN0_ORed_0_15_MB_IRQHandler(void)
{
	if(CANRecData(CAN0CH,&CAN_RX_Msg))
	{
		CAN_RX_Flag=1;
	}
}

void CAN0_Wake_Up_IRQHandler(void)
{
	if(CANRecDataPN(CAN0CH,&CAN_RX_Msg))
	{
		CAN_RX_Flag=1;
	}
}
//end of file

