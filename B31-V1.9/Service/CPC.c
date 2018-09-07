#include "cpc.h"


Key_Status  cpc_key_status={0,0,0,0,0,0,0,0,0,0,0,0,0,0,0};//���м�δ����
CPC_CMD     cpc_cmd={
    .CPCDUALIndcr=0,                //dualͼ��
    .CPCAUTOIndcr=0,                //autoͼ��
    .ACIndcr=0,                     //ACָʾ��
    .RECIndcr=0,                    //��ѭ��
    .FDEFIndcr=0,                   //ǰ��˪
    .RDEFIndcr=0,                   //���˪
    .AirModIndcr=0,                 //ģʽ
    .BlwSpdIndcr=0,                 //����
    .DrvrSetgTmpIndcr=0,            //����ʻ�趨�¶�
    .OutTmp=&AD_TsensorOUTCAR,      //�����¶�
    .PassSetgTmpIndcr=0             //����ʻ�趨�¶�
    };

CPC_Status  cpc_status={
    .DrvrSetgTmpIndcr=0,            //����ʻ�趨�¶�
    .PassSetgTmpIndcr=0,            //����ʻ�趨�¶�
    .BlwSpdIndcr=0,                 //����
    .AirModIndcr=0,                 //ģʽ
    .CompStatus=0,                  //ѹ����״̬
    .RECIndcr=0,                    //��ѭ��
    .FDEFIndcr=0,                   //ǰ��˪
    .RDEFIndcr=0,                   //���˪
    .AutoFan=0,             //�ķ�������Զ�
    .AutoMode=0,            //����ģʽ�Զ�
    .AutoIntake=0           //����ѭ���Զ�
    };

CPC cpc={
    .key=&cpc_key_status,
    .cmd=&cpc_cmd,
    .status=&cpc_status,
};


PanelStatus panel_status;


extern u32 g_Key_Value;
void KeyUpdate(LINMsg *msg)//���հ���ֵ
{
    g_Key_Value=msg->data[0];
    g_Key_Value|=msg->data[1]<<8;
    g_Key_Value|=msg->data[2]<<16;
}

void PanelUpdate(PanelStatus *status,LINMsg *msg)//�����������
{
    msg->data[0]=0;
	
  if(status->Dual)	//dual״̬
  {
    msg->data[0] |= DIS_DUAL_MASK; 
  }
  else
  {
    msg->data[0] &=~DIS_DUAL_MASK; 
  }
}

void Get_CPC_Status(void)//��B31����������ȡ����
{
    ;
}

void CPC_Proc_Update(void)//CPC���ڵ��ú���������ʵ�ָ��ֽ���Ч��
{
    ;
}
