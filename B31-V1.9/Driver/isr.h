/******************** (C) COPYRIGHT 2011 ������ӹ����� ********************
 * �ļ���       ��isr.h
 * ����         ������ģ��ʵ��
 *
 * ʵ��ƽ̨     ��landzo���ӿ�����
 * ��汾       ��
 * Ƕ��ϵͳ     ��
 *
 * ����         ��landzo ������
 * �Ա���       ��http://landzo.taobao.com/

**********************************************************************************/



#ifndef __ISR_H
#define __ISR_H 1
#include  "common.h"

//
//#undef  VECTOR_003
//#define VECTOR_003    HardFault_Handler   //����Ӳ���Ϸ� �����ǳ����ܷ��ˣ�     �Ƽ����Գ���ʱ���ø�LED��ʾ��ָʾ�����ܷ���
//
//
//
#undef  VECTOR_16
#define VECTOR_16    DMA_CH0_Handler

//#undef  VECTOR_020
//#define VECTOR_020    DMA_CH4_Handler
//
//#undef  VECTOR_078
//#define VECTOR_078    FTM0_IRQHandler     //FTM0���벶׽�ж� 
//
//#undef  VECTOR_079
//#define VECTOR_079    FTM1_IRQHandler     //FTM0���벶׽�ж�
//
//#undef  VECTOR_84
//#define VECTOR_84   PIT0_IRQHandler     //���¶���84���ж�ΪPIT0_IRQHandler�ж�

//#undef  VECTOR_085
//#define VECTOR_085    PIT1_IRQHandler     //���¶���85���ж�ΪPIT1_IRQHandler�ж�
//
//#undef  VECTOR_103
//#define VECTOR_103    PORTA_IRQHandler    //PORTA�ж�
//#undef  VECTOR_104
//#define VECTOR_104    PORTB_IRQHandler    //PORTB�ж�
//#undef  VECTOR_106
//#define VECTOR_106    PORTD_IRQHandler    //PORTD�ж�
//
//
//
//
void HardFault_Handler(void);      //����Ӳ���Ϸã������ܷɣ�
void PIT0_IRQHandler(void);            //PIT0 ��ʱ�жϷ�����
void PIT1_IRQHandler(void);            //PIT1 ��ʱ�жϷ�����
void PORTA_IRQHandler(void);           //PORTA�жϷ�����
void PORTB_IRQHandler(void);           //PORTB�жϷ�����
void PORTD_IRQHandler(void);           //PORTD�жϷ�����
void FTM0_IRQHandler(void);            //FTM0���벶׽�ж�
void FTM1_IRQHandler(void);            //FTM0���벶׽�ж�
void LPT_Handler(void);           //LPT�����ж�
void DMA_CH0_Handler(void);
void DMA_CH4_Handler(void);              //DMAͨ��4���жϷ�����

__RAMFUN void setIRQadrr(IRQInterruptIndex IRQnum,void IRQAdrr(void) ) ;

#endif  //__ISR_H

/* End of "isr.h" */
