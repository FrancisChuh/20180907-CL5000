#include "compressor.h"
#include "CGW_Input.h"

extern VCU_Status vcu_status;

E_Comp  compressor={
    .cmd={
        .SetgSpd=0,                             //转速
        .Enbl=1,                                //状态：正常关闭
        .HiVotRdy=&vcu_status.VhlCtrlSts,       //高压就绪
        .LoVotRdy=&vcu_status.IGNPosn,          //低压就绪
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




//设定压缩机转速
//Spd单位：1rmp/min
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

//压缩机开关
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

