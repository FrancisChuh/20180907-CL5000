/***********************************************************
 * 文件名       ：isr.c
 * 说明         ：中断功能模块
 * 作者         ：landzo 蓝电子
 * 淘宝店       ：http://landzo.taobao.com/
 * 公司网站     ：http://www.landzo.com/
 *论坛          ：http://www.landzo.cn
 * 库版本       ：V1.0
 *时间          ：15.5.26
************************************************************/

//#include "isr.h"
#include  "include.h"


extern uint8 TIME0flag_5ms   ;
extern uint8 TIME0flag_10ms  ;
extern uint8 TIME0flag_20ms  ;
extern uint8 TIME0flag_50ms  ;
extern uint8 TIME0flag_80ms  ;
extern uint8 TIME0flag_100ms ;
extern uint8 TIME1flag_20ms  ;
uint8  TimeCount = 0 ;



/*************************************************************************
*                             蓝宙电子工作室
*
*  函数名称：USART1_IRQHandler
*  功能说明：串口1 中断 接收 服务函数
*  参数说明：无
*  函数返回：无
*  修改时间：2012-2-14    已测试
*  备    注：
*************************************************************************/


void USART1_IRQHandler(void)
{
  uint8 ch;
  
  DisableInterrupts;		    //关总中断
  

  
  EnableInterrupts;		    //开总中断
}


/*************************************************************************
*                             蓝宙电子工作室
*
*  函数名称：PIT0_IRQHandler
*  功能说明：PIT0 定时中断服务函数
*  参数说明：无
*  函数返回：无
*  修改时间：2012-2-18    已测试
*  备    注：
*************************************************************************/



void LPIT0_IRQHandler(void)
{
  uint8 n ;
  n=0;
  
  if(LPIT0_MSR&(1<<n))
    LPIT0_MSR |= 1<<n ;
  {
      TimeCount ++ ;
      
      if(TimeCount%1 == 0 )
      {
        TIME0flag_5ms = 1;
      } 
      if(TimeCount%2 == 0 )
      {
        TIME0flag_10ms = 1;    
      }   
      if(TimeCount%4 == 0 )
      {
        TIME0flag_20ms = 1;
      }
      if(TimeCount%10 == 0 )
      {
        TIME0flag_50ms = 1;
      }
      if(TimeCount%16 == 0 )
      {
        TIME0flag_80ms = 1;
      }  
      if(TimeCount%20 == 0 )
      {
        TIME0flag_100ms = 1;
        TimeCount = 0 ;
      }  
  }
}

/*************************************************************************
*                             蓝宙电子工作室
*
*  函数名称：HardFault_Handler
*  功能说明：硬件上访中断服务函数
*  参数说明：无
*  函数返回：无
*  修改时间：2012-2-4    已测试
*  备    注：可以用LED闪烁来指示发生了硬件上访
*************************************************************************/
void HardFault_Handler(void)
{
  while (1)
  {
    //printf("\n****硬件上访错误!!!*****\r\n\n");
  }
}

/*************************************************************************
*                             蓝宙电子工作室
*
*  函数名称：PORTD_IRQHandler
*  功能说明：PORTD端口中断服务函数
*  参数说明：无
*  函数返回：无
*  修改时间：2012-1-25    已测试
*  备    注：引脚号需要自己初始化来清除
*************************************************************************/
uint8  rebufer[32] ;

void PORTD_IRQHandler()
{
  if(PORTD_ISFR & 0x80)            //PTD13触发中断，采集的行中断
  { 
    PORTD_ISFR  |= 0x80;         //写1清中断标志位

  }
  
 
  
}

/*************************************************************************
*                             蓝宙电子工作室
*
*  函数名称：PORTA_IRQHandler
*  功能说明：PORTA端口中断服务函数
*  参数说明：无
*  函数返回：无
*  修改时间：2012-1-25    已测试
*  备    注：引脚号需要根据自己初始化来修改
*************************************************************************/
void PORTA_IRQHandler()
{
  uint8_t  n = 0;    //引脚号
  n = 19;
  if(PORTA_ISFR & (1 << n))         //PTB0触发中断
  {
    PORTA_ISFR  |= (1 << n);        //写1清中断标志位
    
  }
  
  
}

/*************************************************************************
*                             蓝宙电子工作室
*
*  函数名称：LPTMR0_IRQHandler
*  功能说明：LPTMR0端口中断服务函数
*  参数说明：无
*  函数返回：无
*  修改时间：2012-1-25    已测试
*  备    注：引脚号需要根据自己初始化来修改
*************************************************************************/
volatile uint8_t LPT_INT_count = 0;
void  LPTMR0_IRQHandler(void)
{
  LPTMR0_CSR |= LPTMR_CSR_TCF_MASK;   //清除LPTMR比较标志
  LPT_INT_count++;                    //中断溢出加1
}