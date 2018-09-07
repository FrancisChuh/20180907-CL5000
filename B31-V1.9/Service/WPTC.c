#include "WPTC.h"





//wptc��������������ӣ����뷢�ͻ���
void wptc_tx_cmd(WPTC *wptc, LINMsg *msg)
{
    if(wptc->cmd.enable)    //ʹ��
    {
        msg->data[0]=0x01;  
    }
    else
    {
        msg->data[0]=0;
    }
    
    msg->data[1]=wptc->cmd.TarTmp;
    msg->data[2]=wptc->cmd.TarPwr;
    
    if(wptc->cmd.HiVitRdy)//��ѹ����
    {
        msg->data[3]=0x01;
    }
    else
    {
        msg->data[3]=0x00;
    }
    
    if(wptc->cmd.LoVitRdy)//��ѹ����
    {
        msg->data[3]|=(1<<0x01);
    }
    else
    {
        msg->data[3]&=~(1<<0x01);;
    }
    
    msg->data[4]=0x00;
    msg->data[5]=0x00;
    msg->data[6]=0x00;
    msg->data[7]=0x00;
}

//wptc�������
void wptc_rx_status(WPTC *wptc,LINMsg *msg)
{
    uint8_t i;
    for(i=0;i<8;i++)
    {
        wptc->input_tmp[i]=msg->data[i];
    }
}


//wptcִ��:��ʱ����
void wptc_proc(WPTC *wptc)
{
    ;
}


void wptc_enable(WPTC *wptc, FunctionalState state)
{
    
    if(state==ENABLE)
    {
        wptc->cmd.enable=1;
    }
    else
    {
        wptc->cmd.enable=0;
    }
}

void wptc_set_TarTmp(WPTC *wptc, int16_t tar_tmp)
{
    tar_tmp+=40;
    tar_tmp/=10;
    if(tar_tmp<0 && tar_tmp>255)
    {
        ;//err
    }
    else
    {
        wptc->cmd.TarTmp=(uint8_t)(tar_tmp);
    }
}

void wptc_set_TarPwr(WPTC *wptc, uint16_t tar_pwr)
{
    tar_pwr/=50;
    if(tar_pwr>255)
    {
        ;//err
    }
    else
    {
        wptc->cmd.TarPwr=(uint8_t)(tar_pwr);
    }
}




