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
/*   �����ļ�����LINprotocol.c                                            */
/*   Filename  ��LINprotocol.c         			                        			*/
/*   ����      ��������								                        		        */
/*   Author    ��Jack									                        	    	    */
/*   ����      ��10/23/2017						                        				    */
/*   Date      ��10/23/2017						                        					  */
/*   ��ǰ�汾  ��1.0									                        				    */
/*   Version	 ��1.0                                                    */
/*   ʵ��Ŀ��  ��LINЭ����ϣ��������ݴ���                                */
/*   Purpose   ��                                                         */
/**************************************************************************/
/*   �޸ļ�¼  ����                                                       */
/*   ��� , MM/DD/YYYY,�汾���޸��ߣ��޸�����(������޸ļ�¼��������)     */
/*   Modi Report��                                                        */
/*   Index��Date��Version��Author, content                                */
/**************************************************************************/

#include "LINprotocol.h"
#include "B31.h"


typedef void LIN_TX_ISSUES(LIN*);


LINMsg LIN_RX_Msg;
LINMsg LIN_TX_Msg;

LINMsg LIN_RX_Msg_Panel_01;
LINMsg LIN_RX_Msg_PM25_01;
LINMsg LIN_RX_Msg_PM25_02;

void WPTC_01_TX(LINMsg* msg)
{
    msg->PID=PID_WPTC_01;
    msg->LEN=0;
}

void WPTC_01_CB(LINMsg *msg)
{
    ;
}

void APTC_01_TX(LINMsg* msg)
{
    msg->PID=PID_APTC_01;
    msg->LEN=0;
}

void APTC_01_CB(LINMsg* msg)
{
    ;
}

void COMP_01_TX(LINMsg *msg)
{
    msg->PID=PID_COMP_01;
    msg->LEN=0;
}

void COMP_01_CB(LINMsg *msg)
{
    ;
}
void CPC_01_TX(LINMsg *msg)         //������壬����
{
    msg->PID=PID_CPC_01;
    msg->LEN=0;
}

void CPC_01_CB(LINMsg *msg)
{
    if( msg->PID  == PID_CPC_01)
    {
        KeyUpdate(msg);//����ֵ
    }
}

void PM25_01_TX(LINMsg *msg)
{
    msg->PID=PID_PM25_01;
    msg->LEN=0;
}

void PM25_01_CB(LINMsg *msg)
{
    ;
}

void CLIM_01_TX(LINMsg *msg)    //ˮ��ptc����
{
    msg->PID=PID_CLIM_01;
    msg->LEN=CLIM_01_LEN;
    ;//��������
}

void CLIM_01_CB(LINMsg *msg)
{
    ;
}

void CLIM_02_TX(LINMsg *msg)     //����ptc����
{
    msg->PID=PID_CLIM_02;
    msg->LEN=CLIM_02_LEN;
    ;//��������
}

void CLIM_02_CB(LINMsg *msg)
{
    ;
}

void CLIM_03_TX(LINMsg *msg)        //ѹ��������
{
    msg->PID=PID_CLIM_03;
    msg->LEN=CLIM_03_LEN;
    ;//��������
}

void CLIM_03_CB(LINMsg *msg)
{
    ;
}


void LIN_Display_Process(LINMsg *msg);

void CLIM_04_TX(LINMsg *msg)        //������
{
    msg->PID=PID_CLIM_04;
    msg->LEN=CLIM_04_LEN;
    ;//��������
    LIN_Display_Process(msg);
}

void CLIM_04_CB(LINMsg *msg)
{
    ;
}

void CLIM_05_TX(LINMsg *msg)        //pm2.5����
{
    msg->PID=PID_CLIM_05;
    msg->LEN=CLIM_05_LEN;
    ;//��������
}

void CLIM_05_CB(LINMsg *msg)
{
    ;
}





const LIN_ISSUE lin_1_iussues[]={
//    {&WPTC_01_TX,&WPTC_01_CB},
//    {&APTC_01_TX,&APTC_01_CB},
//    {&COMP_01_TX,&COMP_01_CB},
    {&CPC_01_TX ,&CPC_01_CB },
//    {&PM25_01_TX,&PM25_01_CB},
//    {&CLIM_01_TX,&CLIM_01_CB},
//    {&CLIM_02_TX,&CLIM_02_CB},
//    {&CLIM_03_TX,&CLIM_03_CB},
    {&CLIM_04_TX,&CLIM_04_CB},
//    {&CLIM_05_TX,&CLIM_05_CB},
};

const uint8_t LIN_ISSUE_CNT=2;

void LIN_Display_Process(LINMsg *msg)
{
	msg->data[0]=0;
	
  if(s_Heat_Cap.DUAL_STATUS)	//dual״̬
  {
    msg->data[0] |= DIS_DUAL_MASK; 
  }
  else
  {
    msg->data[0] &=~DIS_DUAL_MASK; 
  }

  if(s_Heat_Cap.Mode_PPS==MODEFDEF) //ǰ��˪
  {
    msg->data[0] |= DIS_FDEF_MASK; 
  }
  else
  {
    msg->data[0] &=~DIS_FDEF_MASK; 
  }
  
  if(g_AUTO_Flag ==(AUTO_TAKE_MASK //AUTO
    | AUTO_MODE_MASK
    | AUTO_FAN_MASK 
    | AUTO_AC_MASK 
    | AUTO_TEMP_MASK
		| AUTO_PTC_MASK	))
  {
    msg->data[0] |= DIS_AUTO_MASK; 
  }
  else
  {
    msg->data[0] &=~DIS_AUTO_MASK; 
  }
  
  if(s_Heat_Cap.AC_IN_STATUS)			//ACָʾ��
  {
    msg->data[0] |= DIS_AC_MASK; 
  }
  else
  {
    msg->data[0] &=~DIS_AC_MASK; 
  }
  
  if(s_Heat_Cap.PTC_IN_STATUS)			//PTCָʾ��
  {
    msg->data[0] |= DIS_PTC_MASK; 
  }
  else
  {
    msg->data[0] &=~DIS_PTC_MASK; 
  }
  
  if(s_Heat_Cap.FDEF2_STATUS)		//ǰ������
  {
    msg->data[0] |= DIS_FDEF2_MASK; 
  }
  else
  {
    msg->data[0] &=~DIS_FDEF2_MASK; 
  }
  if(s_Heat_Cap.RDEF_STATUS)		//�󵵼���
  {
    msg->data[0] |= DIS_RDEF_MASK; 
  }
  else
  {
    msg->data[0] &=~DIS_RDEF_MASK; 
  }

  if(s_Heat_Cap.TAKE==REC_INTake)	//����ѭ��
  {
    msg->data[0] |= DIS_REC_MASK; 
  }
  else
  {
    msg->data[0] &=~DIS_REC_MASK; 
  }
  
  msg->data[1]=0;
  msg->data[1] |=s_Heat_Cap.Mode_PPS;
  msg->data[1] |=(s_Heat_Cap.Set_Fan/10)<<4;
  msg->data[2]  =(s_Heat_Cap.Tem_Purpose-150)/5;
	
	msg->data[4] = (s_Heat_Cap.Tem_Slave_Purpose-150)/5;
  
  if(s_Heat_Cap.Tem_Outside>0)		////�����¶�
  {
    if(s_Heat_Cap.Tem_Outside%10 >10)
    {
      msg->data[3]=s_Heat_Cap.Tem_Outside/10+41;
    }
    else
    {
      msg->data[3]=s_Heat_Cap.Tem_Outside/10+40;
    }
  }
  else
  {
	if(s_Heat_Cap.Tem_Outside==-9999)
	{
		msg->data[3]=0;
	}
    else if(s_Heat_Cap.Tem_Outside%10 <-4)
    {
      msg->data[3]=s_Heat_Cap.Tem_Outside/10+39;
    }
    else
    {
      msg->data[3]=s_Heat_Cap.Tem_Outside/10+40;
    }
  }
//  LIN_TX_Msg.data[2]=0x6E;
//  LIN_TX_Msg.data[2]=0x6E;
//  LIN_TX_Msg.data[3]=0x01;
}

//END
