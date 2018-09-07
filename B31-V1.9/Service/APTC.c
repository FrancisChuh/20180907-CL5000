#include "APTC.h"


void aptc_tx_cmd(APTC *aptc,LINMsg *msg)
{
    if(aptc->cmd.enable)
    {
        msg->data[0]=0x01;
    }
    else
    {
        msg->data[0]=0x00;
    }
    
    msg->data[1]=aptc->cmd.RiTarTmp;
    msg->data[2]=aptc->cmd.LeTarTmp;
    msg->data[3]=aptc->cmd.RiTarPwr;
    msg->data[4]=aptc->cmd.LeTarPwr;
    
    if(aptc->cmd.HiVltRdy)  //高压正常
    {
        msg->data[5]=0x01;
    }
    else
    {
        msg->data[5]=0x00;
    }
    
    if(aptc->cmd.LoVltRdy)//低压正常
    {
        msg->data[5]|=(1<<0x01);
    }
    else
    {
        msg->data[5]&=~(1<<0x01);
    }
    
    msg->data[6]=0x00;
    msg->data[7]=0x00;
}


void aptc_rx_status(APTC *aptc, LINMsg *msg)
{
    uint8_t i;
    for(i=0;i<8;i++)
    {
        aptc->input_tmp[i]=msg->data[i];
    }
}

void aptc_proc(APTC *aptc)
{
    ;
}



void aptc_set_enable(APTC *aptc, SW_STATUS sw)
{
    if(sw==SW_ON)
    {
        aptc->cmd.enable=1;
    }
    else
    {
        aptc->cmd.enable=0;
    }
}

void aptc_set_RiTarTmp(APTC *aptc, int16_t tar_tmp)
{
    tar_tmp+=40;
    tar_tmp/=10;
    if(tar_tmp<0 && tar_tmp>255)
    {
        ;//err
    }
    else
    {
        aptc->cmd.RiTarTmp=(uint8_t)(tar_tmp);
    }
}

void aptc_setLeTarTmp(APTC *aptc, int16_t tar_tmp)
{
    tar_tmp+=40;
    tar_tmp/=10;
    if(tar_tmp<0 && tar_tmp>255)
    {
        ;//err
    }
    else
    {
        aptc->cmd.LeTarTmp=(uint8_t)(tar_tmp);
    }
}

void aptc_setRiTarPwr(APTC *aptc, uint16_t tar_pwr)
{
    tar_pwr/=50;
    if(tar_pwr>255)
    {
        ;//err
    }
    else
    {
        aptc->cmd.RiTarPwr=(uint8_t)(tar_pwr);
    }
}

void aptc_setLeTarPwr(APTC *aptc, uint16_t tar_pwr)
{
    tar_pwr/=50;
    if(tar_pwr>255)
    {
        ;//err
    }
    else
    {
        aptc->cmd.LeTarPwr=(uint8_t)(tar_pwr);
    }
}



