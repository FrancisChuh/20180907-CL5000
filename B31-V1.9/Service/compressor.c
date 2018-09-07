#include "compressor.h"
#include "CGW_Input.h"

extern VCU_Status vcu_status;

E_Comp  compressor={
    .cmd={
        .SetgSpd=0,                             //ת��
        .Enbl=1,                                //״̬�������ر�
        .HiVotRdy=&vcu_status.VhlCtrlSts,       //��ѹ����
        .LoVotRdy=&vcu_status.IGNPosn,          //��ѹ����
    },
    .status={
        .CurSpd=0,
        .InputCur=0,
        .InputPwr=0,
        .ECUTmp=0,
        .InputVlt=0,
        .RespErr=0,
    },
};




//�趨ѹ����ת��
//Spd��λ��1rmp/min
void compressor_set_Spd(E_Comp *comp, int16_t Spd)
{
    if(Spd>12700 || Spd <0)
    {
        Spd=0xff;
    }
    else
    {
        Spd/=50;
    }
    comp->cmd.SetgSpd=Spd;
}

//ѹ��������
void compressor_set_status(E_Comp *comp, E_CompStatus status)
{
    if(status==NormalOff)
    {
        comp->cmd.Enbl=1;
    }
    else if(status == FastOff)
    {
        comp->cmd.Enbl=2;
    }
    else if(status == On)
    {
        comp->cmd.Enbl=3;
    }
}

//
void compressor_txd_cmd(E_Comp *comp,LINMsg *msg)
{
    ;
}

//
void compressor_rxd_status(E_Comp *comp,LINMsg *msg)
{
    ;
}


void compressor_proc(E_Comp *comp)
{
    ;
}

