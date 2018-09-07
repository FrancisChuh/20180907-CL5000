/***********************************************************
 * 文件名       ：main.c
 * 说明         ：用户应用程序
 * 作者         ：landzo 蓝电子
 * 淘宝店       ：http://landzo.taobao.com/
 * 公司网站     ：http://www.landzo.com/
 *论坛          ：http://www.landzo.cn
 * 库版本       ：V1.0
 *时间          ：15.5.26
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
    LPT_Rising  = 0,    //上升沿触发
    LPT_Falling = 1     //下降沿触发
} LPT_CFG;


#define  lptmr_counter_clean()     LPTMR_CSR_REG(LPTMR0_BASE_PTR)  &= ~LPTMR_CSR_TEN_MASK;\
                                    LPTMR_CSR_REG(LPTMR0_BASE_PTR)  |=LPTMR_CSR_TEN_MASK  ;          //计数器计数清0

/*          用于延时         */

void time_delay_ms(uint32_t ms);      //延时

/*       用于脉冲计数        */

void lptmr_counter_init(LPT0_ALTn, uint16_t count,  LPT_CFG);                           //计数器初始化设置
uint16_t lptmr_pulse_get(void) ;




/********************************************************************/

#endif /* __LPTMR_H__ */
