#ifndef __CPC_H
#define __CPC_H

#include <stdint.h>
#include "lin.h"
#include "adc.h"

typedef struct Key_Status
{
    uint16_t ACPsd:1;           //AC������
    uint16_t ModPsd:1;          //mode������
    uint16_t FDEFPsd:1;         //ǰ��˪������
    uint16_t RECPsd:1;          //REC����ѭ������
    uint16_t RDEFPsd:1;         //���˪����
    uint16_t AUTOPsd:1;         //auto����
    uint16_t OFFPsd:1;          //�ػ���
    uint16_t FANDecPsd:1;       //������
    uint16_t FANIncPsd:1;       //������
    uint16_t DrvrTmpDesPsd:1;   //���¶ȼ�
    uint16_t DrvrTmpIncPsd:1;   //���¶ȼ�
    uint16_t PassTmpDecPsd:1;   //���¶ȼ�
    uint16_t PassTmpIncPsd:1;   //���¶ȼ�
    uint16_t DUALPsd:1;         //����
    uint8_t  RespErr;           //�ظ��źŴ���
}Key_Status;

typedef struct CPC_CMD{
    uint8_t CPCDUALIndcr:1;     //DUAL
    uint8_t CPCAUTOIndcr:1;     //AUTO
    uint8_t ACIndcr:1;          //ACָʾ��
    uint8_t RECIndcr:1;         //��ѭ��
    uint8_t FDEFIndcr:1;        //ǰ��˪
    uint8_t RDEFIndcr:1;        //���˪
    uint8_t AirModIndcr:1;      //ģʽ
    uint8_t BlwSpdIndcr:1;      //����
    uint8_t DrvrSetgTmpIndcr;   //����ʻ�趨�¶�
    ADC_Proc *OutTmp;             //�����¶�
    uint8_t PassSetgTmpIndcr;   //����ʻ�趨�¶�
}CPC_CMD;

typedef struct CPC_Status{
    uint8_t DrvrSetgTmpIndcr;   //����ʻ�趨�¶�
    uint8_t PassSetgTmpIndcr;   //����ʻ�趨�¶�
    uint8_t BlwSpdIndcr;        //����
    uint8_t AirModIndcr;        //ģʽ
    uint8_t CompStatus:1;       //ѹ����״̬
    uint8_t RECIndcr:1;         //��ѭ��
    uint8_t FDEFIndcr:1;        //ǰ��˪
    uint8_t RDEFIndcr:1;        //���˪
    uint8_t AutoFan:1;      //�ķ�������Զ�
    uint8_t AutoMode:1;     //����ģʽ�Զ�
    uint8_t AutoIntake:1;   //����ѭ���Զ�
}CPC_Status;

typedef struct PanelStatus{
    uint8_t Dual;               //����
    uint8_t Mode_PPS;           //ģʽ
    uint8_t AUTO;               //�Զ�
    uint8_t TempPA;             //��ʻ���趨�¶�
    uint8_t TempCO;             //����ʻ�趨�¶�
    uint8_t Comp_Status;        //ѹ����״̬
    uint8_t FDEF;               //ǰ��˪״̬
    uint8_t RDEF;               //���˪״̬
    uint8_t Fanlevel;           //����
    uint8_t TempOutcar;         //�����¶�
    uint8_t Intake;             //ѭ��ģʽ
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
