#ifndef __COMPRESSOR_H
#define __COMPRESSOR_H

#include <stdint.h>


#include "LIN.h"

typedef enum E_CompStatus{
//    Reserved=0,
    NormalOff=1,
    FastOff=2,
    On=3,
}E_CompStatus;

typedef struct E_Comp_Status{
    uint8_t flags[2];
    uint8_t CurSpd;//��ǰת��
    uint8_t InputCur;//��ǰ����
    uint8_t InputPwr;//��ǰ����
    uint8_t ECUTmp;//ѹ�����������¶�
    uint8_t InputVlt;//ѹ����������ص�ѹ
    uint8_t RespErr;//ResponseError
}E_Comp_Status;

typedef struct E_Comp_CMD{
    uint8_t SetgSpd;//ѹ�����趨ת��
    uint8_t Enbl;//ѹ����ʹ����ת�ź�
    uint8_t *HiVotRdy;//ѹ������ѹ�����ź�
    uint8_t *LoVotRdy;//��ѹ�����ź�
}E_Comp_CMD;

typedef struct E_Comp{
    E_Comp_Status status;
    E_Comp_CMD cmd;
}E_Comp;
#endif

