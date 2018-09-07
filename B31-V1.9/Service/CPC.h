#ifndef __CPC_H
#define __CPC_H

#include <stdint.h>
#include "lin.h"
#include "adc.h"

typedef struct Key_Status
{
    uint16_t ACPsd:1;           //AC键按下
    uint16_t ModPsd:1;          //mode键按下
    uint16_t FDEFPsd:1;         //前除霜键按下
    uint16_t RECPsd:1;          //REC内外循环按键
    uint16_t RDEFPsd:1;         //后除霜按键
    uint16_t AUTOPsd:1;         //auto按键
    uint16_t OFFPsd:1;          //关机键
    uint16_t FANDecPsd:1;       //风量减
    uint16_t FANIncPsd:1;       //风量加
    uint16_t DrvrTmpDesPsd:1;   //主温度减
    uint16_t DrvrTmpIncPsd:1;   //主温度加
    uint16_t PassTmpDecPsd:1;   //副温度减
    uint16_t PassTmpIncPsd:1;   //副温度加
    uint16_t DUALPsd:1;         //跟随
    uint8_t  RespErr;           //回复信号错误
}Key_Status;

typedef struct CPC_CMD{
    uint8_t CPCDUALIndcr:1;     //DUAL
    uint8_t CPCAUTOIndcr:1;     //AUTO
    uint8_t ACIndcr:1;          //AC指示灯
    uint8_t RECIndcr:1;         //内循环
    uint8_t FDEFIndcr:1;        //前除霜
    uint8_t RDEFIndcr:1;        //后除霜
    uint8_t AirModIndcr:1;      //模式
    uint8_t BlwSpdIndcr:1;      //风量
    uint8_t DrvrSetgTmpIndcr;   //主驾驶设定温度
    ADC_Proc *OutTmp;             //车外温度
    uint8_t PassSetgTmpIndcr;   //副驾驶设定温度
}CPC_CMD;

typedef struct CPC_Status{
    uint8_t DrvrSetgTmpIndcr;   //主驾驶设定温度
    uint8_t PassSetgTmpIndcr;   //副驾驶设定温度
    uint8_t BlwSpdIndcr;        //风量
    uint8_t AirModIndcr;        //模式
    uint8_t CompStatus:1;       //压缩机状态
    uint8_t RECIndcr:1;         //内循环
    uint8_t FDEFIndcr:1;        //前除霜
    uint8_t RDEFIndcr:1;        //后除霜
    uint8_t AutoFan:1;      //鼓风机风量自动
    uint8_t AutoMode:1;     //出风模式自动
    uint8_t AutoIntake:1;   //内外循环自动
}CPC_Status;

typedef struct PanelStatus{
    uint8_t Dual;               //跟随
    uint8_t Mode_PPS;           //模式
    uint8_t AUTO;               //自动
    uint8_t TempPA;             //驾驶舱设定温度
    uint8_t TempCO;             //副驾驶设定温度
    uint8_t Comp_Status;        //压缩机状态
    uint8_t FDEF;               //前除霜状态
    uint8_t RDEF;               //后除霜状态
    uint8_t Fanlevel;           //风量
    uint8_t TempOutcar;         //车外温度
    uint8_t Intake;             //循环模式
}PanelStatus;

typedef struct CPC{
    Key_Status  *key;
    CPC_CMD     *cmd;
    PanelStatus *PanelStatus;
    CPC_Status  *status;
}CPC;

void KeyUpdate(LINMsg *msg);
void PanelUpdate(PanelStatus *status,LINMsg *msg);
void Get_CPC_Status(void);
void CPC_Proc_Update(void);

#endif
