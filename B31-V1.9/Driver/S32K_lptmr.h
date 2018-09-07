/***********************************************************
 * �ļ���       ��main.c
 * ˵��         ���û�Ӧ�ó���
 * ����         ��landzo ������
 * �Ա���       ��http://landzo.taobao.com/
 * ��˾��վ     ��http://www.landzo.com/
 *��̳          ��http://www.landzo.cn
 * ��汾       ��V1.0
 *ʱ��          ��15.5.26
************************************************************/

#ifndef __S32K_LPTMR_H__
#define __S32K_LPTMR_H__

/********************************************************************/


typedef enum LPT0_ALTn
{
    LPT0_CH1 = 1,      // 
    LPT0_CH2 = 2,      // 
    LPT0_CH3 = 3       // 
      
} LPT0_ALTn;

typedef enum LPT_CFG
{
    LPT_Rising  = 0,    //�����ش���
    LPT_Falling = 1     //�½��ش���
} LPT_CFG;


#define  lptmr_counter_clean()     LPTMR_CSR_REG(LPTMR0_BASE_PTR)  &= ~LPTMR_CSR_TEN_MASK;\
                                    LPTMR_CSR_REG(LPTMR0_BASE_PTR)  |=LPTMR_CSR_TEN_MASK  ;          //������������0

/*          ������ʱ         */

void time_delay_ms(uint32_t ms);      //��ʱ

/*       �����������        */

void lptmr_counter_init(LPT0_ALTn, uint16_t count,  LPT_CFG);                           //��������ʼ������
uint16_t lptmr_pulse_get(void) ;




/********************************************************************/

#endif /* __LPTMR_H__ */
