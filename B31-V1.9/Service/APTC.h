#ifndef __APTC_H
#define __APTC_H

#include <stdint.h>

#include "LIN.h"

typedef struct APTC_STATUS{
    uint8_t HvVlt;  //ĸ�ߵ�ѹ
    uint8_t HvCur;  //ĸ�ߵ���
    uint8_t ActlPwr;    //ʵ�ʹ���
    uint8_t LoVlt;      //��ѹ��ѹ
    uint8_t RiTmp;      //�Ҳ౾���¶�
    uint8_t LeTmp;      //��౾���¶�
    uint8_t Flags[2];   //����״̬��ʶ
}APTC_STATUS;

typedef struct APTC_CMD{
    uint8_t enable;//ʹ��
    uint8_t RiTarTmp;//�Ҳ�Ŀ���¶�
    uint8_t LeTarTmp;//���Ŀ���¶�
    uint8_t RiTarPwr;//�Ҳ�Ŀ�깦��
    uint8_t LeTarPwr;//���Ŀ�깦��
    uint8_t HiVltRdy;//��ѹ����
    uint8_t LoVltRdy;//��ѹ����
}APTC_CMD;

typedef struct APTC{
    APTC_CMD            cmd;
    APTC_STATUS         status;
    uint8_t             input_tmp[8];
}APTC;

#endif
