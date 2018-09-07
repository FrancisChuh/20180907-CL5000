#include "S32_PIT.h" 

/*************************************************************************
*  函数名称：pit_init
*  功能说明：PITn定时中断
*  参数说明：PITn        模块号（PIT0~PIT3）
             cnt         延时时间(单位为bus时钟周期)
*  函数返回：无
*  修改时间：2012-1-24
*  备    注：
*************************************************************************/
void Pit_Init(PITn pitn, uint32_t cnt_us)	//溢出计数 = 总线频率 * 时间
{
	cnt_us=CPU_XTAL_CLK_HZ/1000000*cnt_us;
	
	PCC->PCCn[PCC_LPIT_INDEX] &= ~PCC_PCCn_CGC_MASK ;		//时钟禁能	
  PCC->PCCn[PCC_LPIT_INDEX]  = PCC_PCCn_PCS(1) ;      //选择SOSC作为时钟源 8M
	PCC->PCCn[PCC_LPIT_INDEX] |= PCC_PCCn_CGC_MASK ;    //使能PIT时钟

//	LPIT0->MCR = LPIT_MCR_SW_RST_MASK ;//复位所有寄存器
  LPIT0->MCR |= LPIT_MCR_M_CEN_MASK; 			//使能PIT定时器时钟
//							| LPIT_MCR_DOZE_EN_MASK;			//doze模式继续运行
//							| LPIT_MCR_DBG_EN_MASK;     //调试模式下继续运行
////    while(LPIT0_MCR&LPIT_MCR_SW_RST_MASK){;}
  LPIT0->CLRTEN |= (1 << pitn);			//禁能

	LPIT0->TMR[pitn].TVAL  = cnt_us;   
	LPIT0->TMR[pitn].TCTRL |= LPIT_TMR_TCTRL_T_EN_MASK  //使能
													|LPIT_TMR_TCTRL_MODE(0);		//32bit-Periodic Counter
//													|LPIT_TMR_TCTRL_TROT(1)		//reload
//													|LPIT_TMR_TCTRL_TRG_SEL(pitn)//触发源
//													|LPIT_TMR_TCTRL_TRG_SRC(1);	//内部触发
	LPIT0->MIER|= 1<< pitn ;      //中断使能
	LPIT0->SETTEN |= (1 << pitn);	//使能PIT
}
