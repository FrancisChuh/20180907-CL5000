#ifndef __S32_GPIO_H__
#define __S32_GPIO_H__

//#include "common.h"
#include "S32K144.h"
#include "port.h"
#include "me_type.h"                  //额外的变量定义

typedef enum PTxn
{
    /*  PTA端口    */ //0~31
    PTA0 = 0,
    PTA1 = 1,
    PTA2 = 2,
    PTA3 = 3,
    PTA4 = 4,
    PTA5 = 5,
    PTA6 = 6,
    PTA7 = 7,
    PTA8 = 8,
    PTA9 = 9,
    PTA10 = 10 ,
    PTA11 = 11 ,
    PTA12 = 12 ,
    PTA13 = 13 ,
    PTA14 = 14 ,
    PTA15 = 15 ,
    PTA16 = 16 ,
    PTA17 = 17 ,
    PTA18 = 18 ,
    PTA19 = 19 ,
    PTA20 = 20 ,
    PTA21 = 21 ,
    PTA22 = 22 ,
    PTA23 = 23 ,
    PTA24 = 24 ,
    PTA25 = 25 ,
    PTA26 = 26 ,
    PTA27 = 27 ,
    PTA28 = 28 ,
    PTA29 = 29 ,
    PTA30 = 30 ,
    PTA31 = 31 ,

    /*  PTB端口    */   //32~63
    PTB0 = 0+32,
    PTB1 = 1+32,
    PTB2 = 2+32,
    PTB3 = 3+32,
    PTB4 = 4+32,
    PTB5 = 5+32,
    PTB6 = 6+32,
    PTB7 = 7+32,
    PTB8 = 8+32,
    PTB9 = 9+32,
    PTB10 = 10+32 ,
    PTB11 = 11+32 ,
    PTB12 = 12+32 ,
    PTB13 = 13+32 ,
    PTB14 = 14+32 ,
    PTB15 = 15+32 ,
    PTB16 = 16+32 ,
    PTB17 = 17+32 ,
    PTB18 = 18+32 ,
    PTB19 = 19+32 ,
    PTB20 = 20+32 ,
    PTB21 = 21+32 ,
    PTB22 = 22+32 ,
    PTB23 = 23+32 ,
    PTB24 = 24+32 ,
    PTB25 = 25+32 ,
    PTB26 = 26+32 ,
    PTB27 = 27+32 ,
    PTB28 = 28+32 ,
    PTB29 = 29+32 ,
    PTB30 = 30+32 ,
    PTB31 = 31+32 ,

    /*  PTC端口    */
    PTC0 = 0+64,
    PTC1 = 1+64,
    PTC2 = 2+64,
    PTC3 = 3+64,
    PTC4 = 4+64,
    PTC5 = 5+64,
    PTC6 = 6+64,
    PTC7 = 7+64,
    PTC8 = 8+64,
    PTC9 = 9+64,
    PTC10 = 10+64 ,
    PTC11 = 11+64 ,
    PTC12 = 12+64 ,
    PTC13 = 13+64 ,
    PTC14 = 14+64 ,
    PTC15 = 15+64 ,
    PTC16 = 16+64 ,
    PTC17 = 17+64 ,
    PTC18 = 18+64 ,
    PTC19 = 19+64 ,
    PTC20 = 20+64 ,
    PTC21 = 21+64 ,
    PTC22 = 22+64 ,
    PTC23 = 23+64 ,
    PTC24 = 24+64 ,
    PTC25 = 25+64 ,
    PTC26 = 26+64 ,
    PTC27 = 27+64 ,
    PTC28 = 28+64 ,
    PTC29 = 29+64 ,
    PTC30 = 30+64 ,
    PTC31 = 31+64 ,

    /*  PTD端口    */
    PTD0 = 0+96,
    PTD1 = 1+96,
    PTD2 = 2+96,
    PTD3 = 3+96,
    PTD4 = 4+96,
    PTD5 = 5+96,
    PTD6 = 6+96,
    PTD7 = 7+96,
    PTD8 = 8+96,
    PTD9 = 9+96,
    PTD10 = 10+96 ,
    PTD11 = 11+96 ,
    PTD12 = 12+96 ,
    PTD13 = 13+96 ,
    PTD14 = 14+96 ,
    PTD15 = 15+96 ,
    PTD16 = 16+96 ,
    PTD17 = 17+96 ,
    PTD18 = 18+96 ,
    PTD19 = 19+96 ,
    PTD20 = 20+96 ,
    PTD21 = 21+96 ,
    PTD22 = 22+96 ,
    PTD23 = 23+96 ,
    PTD24 = 24+96 ,
    PTD25 = 25+96 ,
    PTD26 = 26+96 ,
    PTD27 = 27+96 ,
    PTD28 = 28+96 ,
    PTD29 = 29+96 ,
    PTD30 = 30+96 ,
    PTD31 = 31+96 ,

    /*  PTE端口    */
    PTE0 = 0+128,
    PTE1 = 1+128,
    PTE2 = 2+128,
    PTE3 = 3+128,
    PTE4 = 4+128,
    PTE5 = 5+128,
    PTE6 = 6+128,
    PTE7 = 7+128,
    PTE8 = 8+128,
    PTE9 = 9+128,
    PTE10 = 10+128 ,
    PTE11 = 11+128 ,
    PTE12 = 12+128 ,
    PTE13 = 13+128 ,
    PTE14 = 14+128 ,
    PTE15 = 15+128 ,
    PTE16 = 16+128 ,
    PTE17 = 17+128 ,
    PTE18 = 18+128 ,
    PTE19 = 19+128 ,
    PTE20 = 20+128 ,
    PTE21 = 21+128 ,
    PTE22 = 22+128 ,
    PTE23 = 23+128 ,
    PTE24 = 24+128 ,
    PTE25 = 25+128 ,
    PTE26 = 26+128 ,
    PTE27 = 27+128 ,
    PTE28 = 28+128 ,
    PTE29 = 29+128 ,
    PTE30 = 30+128 ,
    PTE31 = 31+128 ,

} PTxn;


typedef enum GPIO_CFG
{
	GP_IN				= 0,         //定义管脚输入方向,GPIOx_PDDRn里,0表示输入,1表示输出
	GP_OUT			    = 1,         //定义管脚输出方向
	GP_IN_DOWN	        = PULLDOWN,  //输入下拉              
	GP_IN_UP		    = PULLUP,    //输入上拉 
    GP_DIS              = 4
}GPIO_CFG;

typedef enum {RESET = 0, SET = !RESET} FlagStatus, ITStatus;


typedef enum
{
	DISABLED   = IRQ_DISABLED,    //中断禁止
	DMARING    = DMA_RISING,     //DMA上升沿触发
	DMAFALLING = DMA_FALLING,     //DMA下降沿触发	
	DMAEITHER  = DMA_EITHER,     //DMA跳变沿触发	
	ZERO       = IRQ_ZERO,        //低电平触发	
	RING       = IRQ_RISING,      //上升沿触发	
	FALLING    = IRQ_FALLING,    //下降沿触发	
	EITHER     = IRQ_EITHER,    //跳变沿触发	
	ONE        = IRQ_ONE         //高电平触发
}GPIO_INT;

void Gpio_Init(PTxn ptxn, GPIO_CFG cfg, FlagStatus sata);
void Gpio_Set(PTxn ptxn,FlagStatus sata);
void Gpio_Toggle(PTxn ptxn) ;
FlagStatus Gpio_Get(PTxn ptxn);
void Gpio_Enable_Port (void);
void Gpio_Interrupt_Init(PTxn ptxn, GPIO_CFG cfg, port_pcr mode);

#endif      
