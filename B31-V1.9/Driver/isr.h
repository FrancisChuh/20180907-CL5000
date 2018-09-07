/******************** (C) COPYRIGHT 2011 蓝宙电子工作室 ********************
 * 文件名       ：isr.h
 * 描述         ：工程模版实验
 *
 * 实验平台     ：landzo电子开发版
 * 库版本       ：
 * 嵌入系统     ：
 *
 * 作者         ：landzo 蓝电子
 * 淘宝店       ：http://landzo.taobao.com/

**********************************************************************************/



#ifndef __ISR_H
#define __ISR_H 1
#include  "common.h"

//
//#undef  VECTOR_003
//#define VECTOR_003    HardFault_Handler   //发生硬件上访 （就是程序跑飞了）     推荐调试程序时，用个LED显示来指示程序跑飞了
//
//
//
#undef  VECTOR_16
#define VECTOR_16    DMA_CH0_Handler

//#undef  VECTOR_020
//#define VECTOR_020    DMA_CH4_Handler
//
//#undef  VECTOR_078
//#define VECTOR_078    FTM0_IRQHandler     //FTM0输入捕捉中断 
//
//#undef  VECTOR_079
//#define VECTOR_079    FTM1_IRQHandler     //FTM0输入捕捉中断
//
//#undef  VECTOR_84
//#define VECTOR_84   PIT0_IRQHandler     //重新定义84号中断为PIT0_IRQHandler中断

//#undef  VECTOR_085
//#define VECTOR_085    PIT1_IRQHandler     //重新定义85号中断为PIT1_IRQHandler中断
//
//#undef  VECTOR_103
//#define VECTOR_103    PORTA_IRQHandler    //PORTA中断
//#undef  VECTOR_104
//#define VECTOR_104    PORTB_IRQHandler    //PORTB中断
//#undef  VECTOR_106
//#define VECTOR_106    PORTD_IRQHandler    //PORTD中断
//
//
//
//
void HardFault_Handler(void);      //发生硬件上访（程序跑飞）
void PIT0_IRQHandler(void);            //PIT0 定时中断服务函数
void PIT1_IRQHandler(void);            //PIT1 定时中断服务函数
void PORTA_IRQHandler(void);           //PORTA中断服务函数
void PORTB_IRQHandler(void);           //PORTB中断服务函数
void PORTD_IRQHandler(void);           //PORTD中断服务函数
void FTM0_IRQHandler(void);            //FTM0输入捕捉中断
void FTM1_IRQHandler(void);            //FTM0输入捕捉中断
void LPT_Handler(void);           //LPT脉冲中断
void DMA_CH0_Handler(void);
void DMA_CH4_Handler(void);              //DMA通道4的中断服务函数

__RAMFUN void setIRQadrr(IRQInterruptIndex IRQnum,void IRQAdrr(void) ) ;

#endif  //__ISR_H

/* End of "isr.h" */
