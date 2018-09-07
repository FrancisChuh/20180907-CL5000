#ifndef __CAN_PROTOCOL_H
#define __CAN_PROTOCOL_H


#include <stdint.h>
#include "S32_can.h"


#define CAN_TIMEOUT     5       //can超时：单位多少个周期

#define CGWBodyCAN_1    0x210
#define CGWBodyCAN_2    0x211
#define ClimBodyCAN1    0x221
#define ClimBodyCAN2    0x222
#define ClimBodyCAN3    0x223
#define ClimBodyCAN4    0x224
#define ClimBodyCAN5    0x225
#define ClimBodyCAN6    0x226
#define ClimBodyCAN7    0x227


typedef struct __MSB_BITS_8{
    uint8_t BIT0:1;
    uint8_t BIT1:1;
    uint8_t BIT2:1;
    uint8_t BIT3:1;
    uint8_t BIT4:1;
    uint8_t BIT5:1;
    uint8_t BIT6:1;
    uint8_t BIT7:1;
}__MSB_BITS_8;

typedef struct MSB_BITS_8{
    __MSB_BITS_8    bits;
    uint8_t         byte;
}MSB_BITS_8;

typedef void can_tr_proc(CANMsg*);

typedef struct CAN_ISSUE
{
    const  uint32_t     id;
    can_tr_proc         *proc;
    CANMsg              msg;
    uint16_t            cycle;          //单位:1ms
    uint16_t            timeout;        //单位:1ms
}CAN_ISSUE;


void CAN_Pro_TX(CANMsg *msg);        //100ms调用
void CAN_Proc_RX(CANMsg *msg);       //接收处理

#endif
