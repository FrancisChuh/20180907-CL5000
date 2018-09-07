#include "CAN_Proc.h"

CANMsg CAN_RX_Msg_ID1;
CANMsg CAN_TX_Msg_ID1;

void CAN_RX_Proc(void)
{
//	u16 tem=0;
	if(CAN_RX_Flag)
	{
		CAN_RX_Flag=0;
		switch(CAN_RX_Msg.ID)
		{
			default:break;
		}
	}
}

void CAN_TX_Proc(void)
{
    u32 tem;
    
    CAN_TX_Msg_ID1.ID=0x001;
    CAN_TX_Msg_ID1.len=8;
    
    tem=*FlexRam_addr;
    CAN_TX_Msg_ID1.data[0]=(tem>>24)&0xff;
    CAN_TX_Msg_ID1.data[1]=(tem>>16)&0xff;
    CAN_TX_Msg_ID1.data[2]=(tem>> 8)&0xff;
    CAN_TX_Msg_ID1.data[3]=(tem>> 0)&0xff;
    CAN_TX_Msg_ID1.data[0]=s_PWM_Duty.Duty_Cycle/10;

    tem=*(FlexRam_addr+1);
    CAN_TX_Msg_ID1.data[4]=(tem>>24)&0xff;
    CAN_TX_Msg_ID1.data[5]=(tem>>16)&0xff;
    CAN_TX_Msg_ID1.data[6]=(tem>> 8)&0xff;
    CAN_TX_Msg_ID1.data[7]=(tem>> 0)&0xff;
    CAN_TX(&CAN_TX_Msg_ID1);
}
  
//end
