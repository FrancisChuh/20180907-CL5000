#ifndef __WPTC_H
#define __WPTC_H

#include <stdint.h>

#include "LIN.h"

typedef struct WPTC_CMD
{
    uint8_t enable;     //ʹ��
    uint8_t TarTmp;     //Ŀ���¶�
    uint8_t TarPwr;     //Ŀ�깦��
    uint8_t HiVitRdy;   //��ѹ���������can�����������ܿ�����������
    uint8_t LoVitRdy;   //��ѹ�;�������can�����������ܿ�����������
}WPTC_CMD;

typedef struct WPTC_STATUS
{
    uint8_t InltTmp;//��ˮ���¶�
    uint8_t OutltTmp;//��ˮ���¶�
    uint8_t ActlHiVlt;//��ѹ��ѹ
    uint8_t ActlHiVltCur;//��ѹ����
    uint8_t ActlLoVlt;//��ѹ��ѹ
    uint8_t ActuPwr;//ʵ�ʹ���
    uint8_t Flags[2];//����״̬��־
//    uint8_t Sts;//wptc״̬
//    uint8_t IGBTCircProtc;  //IGBT��·/��·
//    uint8_t LeakWtrProtc;//WPTC©ˮ����
//    uint8_t PCBTmpSnsrProtc;//PCB�¶ȴ��������ϱ���
//    uint8_t WPTCTmpSnsrProtc;//wptc�¶ȴ���������
//    uint8_t OvrCurtProtc;//wptc��������
//    uint8_t HiVltOvrVltProtc;//��ѹ��ѽ����
//    uint8_t HiVltUndrVltProtc;//��ѹǷѹ
//    uint8_t LoVltOvrVltProtc;//��ѹ��ѽ����
}WPTC_STATUS;

typedef struct WPTC
{
    WPTC_CMD            cmd;
    WPTC_STATUS         status;
    uint8_t             input_tmp[8];
}WPTC;


#endif
