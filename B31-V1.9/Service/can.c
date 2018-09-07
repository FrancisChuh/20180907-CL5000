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
/*   �����ļ�����CAN.c         										                        */
/*   Filename  ��CAN.c         			                        						  */
/*   ����      ��������								                        		        */
/*   Author    ��Jack									                        	    	    */
/*   ����      ��10/23/2017						                        				    */
/*   Date      ��10/23/2017						                        					  */
/*   ��ǰ�汾  ��1.0									                        				    */
/*   Version	 ��1.0                                                      */
/*   ʵ��Ŀ��  ��CAN��ʼ��									                        		  */
/*   Purpose   ��CAN_Init                                                 */
/**************************************************************************/
/*   �޸ļ�¼  ����                                                       */
/*   ��� , MM/DD/YYYY,�汾���޸��ߣ��޸�����(������޸ļ�¼��������)     */
/*   Modi Report��                                                        */
/*   Index��Date��Version��Author, content                                */
/**************************************************************************/

#include "can.h"
#include "CAN_Protocol.h"

//11bit���7FF
#define RX_NODE_ID	0x3E9

#define TX_NODE_ID	0x123//

#if (RX_NODE_ID>0x7ff || TX_NODE_ID>0x7ff )
	#error "11bit��ID���0x7FF"
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

void CAN_RX_Proc(void)          //���մ���,ʵʱ����
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

