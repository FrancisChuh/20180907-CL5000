#include "CAN_Protocol.h"


#include "CGW_Input.h"




extern VCU_Status vcu_status;

//can��������
void CGWBodyCAN_1_Proc(CANMsg *msg)
{
    MSB_BITS_8 data[8];
    uint8_t i;
    if(msg==NULL)//��ʱ��
    {
        ;
    }
    else            //�յ�����
    {
        for(i=0;i<8;i++)    //ת��Ϊintel MSB
        {
            data[7-i].byte=msg->data[i];
        }
//        vcu_status.ChillerSwchSts=(data[6].bits.BIT7)|(data[7].bits.BIT0);
//        vcu_status.PrmtClimMasPwr=msg->data[0]&0x7f;
//        vcu_status.PwrLmtReason=((msg->data[6]&0x60)>>5);
//        vcu_status.CoolgFanDutyRat=((msg->data[1]&0x80)>>1)|((msg->data[2]&0x3f)>>2);
//        vcu_status.CoolgFanFtSts=((msg->data[6]&0x06)>>1);
    }
}

void CGWBodyCAN_2_Proc(CANMsg *msg)
{
    if(msg==NULL)       //��ʱ��
    {
        ;
    }
    else                //�յ�����
    {
        ;
    }
}



CAN_ISSUE CAN_RX_ISSUES[]={
    {.id=CGWBodyCAN_1,.proc=&CGWBodyCAN_1_Proc,.cycle=100,.timeout=0},
    {.id=CGWBodyCAN_2,.proc=&CGWBodyCAN_2_Proc,.cycle=100,.timeout=0},
};

//can ��������
void ClimBodyCAN1_Proc(CANMsg *msg)
{
    ;
}
void ClimBodyCAN2_Proc(CANMsg *msg)
{
    ;
}
void ClimBodyCAN3_Proc(CANMsg *msg)
{
    ;
}
void ClimBodyCAN4_Proc(CANMsg *msg)
{
    ;
}
void ClimBodyCAN5_Proc(CANMsg *msg)
{
    ;
}
void ClimBodyCAN6_Proc(CANMsg *msg)
{
    ;
}
void ClimBodyCAN7_Proc(CANMsg *msg)
{
    ;
}


CAN_ISSUE CAN_TX_ISSUES[]={
    {.id=ClimBodyCAN1,.proc=&ClimBodyCAN1_Proc,.cycle=100,.timeout=0},
    {.id=ClimBodyCAN2,.proc=&ClimBodyCAN2_Proc,.cycle=100,.timeout=0},
    {.id=ClimBodyCAN3,.proc=&ClimBodyCAN3_Proc,.cycle=100,.timeout=0},
    {.id=ClimBodyCAN4,.proc=&ClimBodyCAN4_Proc,.cycle=200,.timeout=0},
    {.id=ClimBodyCAN5,.proc=&ClimBodyCAN5_Proc,.cycle=200,.timeout=0},
    {.id=ClimBodyCAN6,.proc=&ClimBodyCAN6_Proc,.cycle=200,.timeout=0},
    {.id=ClimBodyCAN7,.proc=&ClimBodyCAN7_Proc,.cycle=200,.timeout=0},
};

void CAN_Pro_TX(CANMsg *msg)        //100ms����
{
    uint8_t i=0;
    for(i=0;i<sizeof(CAN_TX_ISSUES)/sizeof(CAN_ISSUE);i++)      //�������¼�
    {
        if(CAN_TX_ISSUES[i].timeout>100)
        {
            CAN_TX_ISSUES[i].timeout-=100;
        }
        
        if(CAN_TX_ISSUES[i].timeout<100)
        {
            CAN_TX_ISSUES[i].timeout=100;
        }
        
        if(CAN_TX_ISSUES[i].timeout==0)
        {
            CAN_TX_ISSUES[i].proc(msg);//�������¼�
            CAN_TX_ISSUES[i].timeout=CAN_TX_ISSUES[i].cycle;
        }
    }
    
    for(i=0;i<sizeof(CAN_RX_ISSUES)/sizeof(CAN_ISSUE);i++)  //������ճ�ʱ
    {
        if(CAN_RX_ISSUES[i].timeout<100)
        {
            CAN_RX_ISSUES[i].proc(NULL);
        }
        else
        {
            CAN_RX_ISSUES[i].timeout-=100;
            if(CAN_RX_ISSUES[i].timeout<100)
            {
                CAN_RX_ISSUES[i].proc(NULL);
            }
        }
    }
}

void CAN_Proc_RX(CANMsg *msg)
{
    uint8_t i;
    for(i=0;i<sizeof(CAN_RX_ISSUES)/sizeof(CAN_ISSUE);i++)
    {
        if(CAN_RX_ISSUES[i].id==msg->ID)
        {
            CAN_RX_ISSUES[i].proc(msg);
            CAN_RX_ISSUES[i].timeout=CAN_RX_ISSUES[i].timeout*CAN_TIMEOUT;
        }
    }
}












