#include "cpc.h"


Key_Status  cpc_key_status={0,0,0,0,0,0,0,0,0,0,0,0,0,0,0};//所有键未按下
CPC_CMD     cpc_cmd={
    .CPCDUALIndcr=0,                //dual图标
    .CPCAUTOIndcr=0,                //auto图标
    .ACIndcr=0,                     //AC指示灯
    .RECIndcr=0,                    //内循环
    .FDEFIndcr=0,                   //前除霜
    .RDEFIndcr=0,                   //后除霜
    .AirModIndcr=0,                 //模式
    .BlwSpdIndcr=0,                 //风量
    .DrvrSetgTmpIndcr=0,            //主驾驶设定温度
    .OutTmp=&AD_TsensorOUTCAR,      //车外温度
    .PassSetgTmpIndcr=0             //副驾驶设定温度
    };

CPC_Status  cpc_status={
    .DrvrSetgTmpIndcr=0,            //主驾驶设定温度
    .PassSetgTmpIndcr=0,            //副驾驶设定温度
    .BlwSpdIndcr=0,                 //风量
    .AirModIndcr=0,                 //模式
    .CompStatus=0,                  //压缩机状态
    .RECIndcr=0,                    //内循环
    .FDEFIndcr=0,                   //前除霜
    .RDEFIndcr=0,                   //后除霜
    .AutoFan=0,             //鼓风机风量自动
    .AutoMode=0,            //出风模式自动
    .AutoIntake=0           //内外循环自动
    };

CPC cpc={
    .key=&cpc_key_status,
    .cmd=&cpc_cmd,
    .status=&cpc_status,
};


PanelStatus panel_status;


extern u32 g_Key_Value;
void KeyUpdate(LINMsg *msg)//接收按键值
{
    g_Key_Value=msg->data[0];
    g_Key_Value|=msg->data[1]<<8;
    g_Key_Value|=msg->data[2]<<16;
}

void PanelUpdate(PanelStatus *status,LINMsg *msg)//发送面板数据
{
    msg->data[0]=0;
	
  if(status->Dual)	//dual状态
  {
    msg->data[0] |= DIS_DUAL_MASK; 
  }
  else
  {
    msg->data[0] &=~DIS_DUAL_MASK; 
  }
}

void Get_CPC_Status(void)//给B31主处理函数获取数据
{
    ;
}

void CPC_Proc_Update(void)//CPC周期调用函数，用来实现各种渐变效果
{
    ;
}
