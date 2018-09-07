#include  "S32K_FTM.h"

#define FTM_PRECISON 100u     //定义占空比精度，100即精度为1%，1000u则精度为0.1%，用于占空比 duty 形参传入，即占空比为 duty/FTM_PRECISON
#define FTM_CLK_DIV 7

volatile FTM_Type *FTMx[4] = {FTM0, FTM1, FTM2, FTM3}; //定义四个指针数组保存 FTMn 的地址

/*************************************************************************
*  函数名称：FTM_PWM_init
*  功能说明：初始化FTM的PWM功能并设置频率、占空比。设置通道输出占空比。
*  参数说明：FTMn        模块号（FTM0、  FTM1、  FTM2）
*            CHn         通道号（CH0~CH7）
*            freq        频率（单位为Hz）
*            duty        占空比
*  函数返回：无
*  修改时间：2012-2-14
*  备    注：同一个FTM，各通道的PWM频率是一样的，共3个FTM，即可以输出3个不同频率PWM
*************************************************************************/
void FTM_PWM_init(FTMn ftmn, CHn ch, uint32_t freq, uint8_t duty)
{
	uint16_t mod;
  /*       计算分频因子       */
  mod = (SystemCoreClock >> FTM_CLK_DIV) / freq;		//频率设置因子,clk_hz = 625000
  switch(ftmn)
  {
    case SFTM0:
			PCC->PCCn[PCC_FTM0_INDEX]= PCC_PCCn_CGC_MASK+PCC_PCCn_PCS(6);   //使用SPLLDIV1_CLK作为时钟源,80M
			switch(ch)
			{
        case CH0:
					port_alt(FTM0_CH0,ALT2) ;
					break;

        case CH1:
          port_alt(FTM0_CH1,ALT2) ;
          break;

        case CH2:
          port_alt(FTM0_CH2,ALT2) ;
          break;

        case CH3:
					port_alt(FTM0_CH3,ALT2) ;
					break;

        case CH4:
          port_alt(FTM0_CH4,ALT2) ;
					break;

        case CH5:
					port_alt(FTM0_CH5,ALT2) ;
					break;

        case CH6:
					port_alt(FTM0_CH6,ALT2) ;
					break;

        case CH7:
					port_alt(FTM0_CH7,ALT2) ;
          break;
        default:
					break;
      }
      break;

    case SFTM1:
			PCC->PCCn[PCC_FTM1_INDEX]= PCC_PCCn_CGC_MASK+PCC_PCCn_PCS(6);  //使用SPLLDIV1_CLK作为时钟源,80M
			switch(ch)
			{
        case CH0:
          port_alt(FTM1_CH0,ALT2) ;
          break;

        case CH1:
          port_alt(FTM1_CH1,ALT2) ;           
          break;
          
        case CH2:
          port_alt(FTM1_CH2,ALT2) ;           
          break;
        
        case CH3:
          port_alt(FTM1_CH3,ALT2) ;           
          break;

        case CH4:
          if(FTM1_CH4 == PTD8)
					{
						port_alt(FTM1_CH4,ALT6) ;
					}
          else if(FTM1_CH4 == PTA10)
          {
						port_alt(FTM1_CH4,ALT2) ;
          }
          break;
          
        case CH5:
          if(FTM1_CH5 == PTD9)
					{
						port_alt(FTM1_CH5,ALT6) ;
					}
          else if(FTM1_CH5 == PTA11)
					{
						port_alt(FTM1_CH5,ALT2) ;
					}
          break;
          
				case CH6:
					if(FTM1_CH6 == PTC0)
					{
						port_alt(FTM1_CH6,ALT6) ;
					}
          else if(FTM1_CH6 == PTA12)
					{
						port_alt(FTM1_CH6,ALT2) ;
					}
          break;
         
         case CH7:
          if(FTM1_CH7 == PTC1)
					{
						port_alt(FTM1_CH7,ALT6) ;
					}
          else if(FTM1_CH7 == PTA13)
					{
						port_alt(FTM1_CH7,ALT2) ;
					}
          break ;
          
        default:
					break;
			}
			break;
        
    case SFTM2:
			PCC->PCCn[PCC_FTM2_INDEX]= PCC_PCCn_CGC_MASK+PCC_PCCn_PCS(6);    //使用SPLLDIV1_CLK作为时钟源,80M
			switch(ch)
			{
        case CH0:
          if(FTM2_CH0 == PTD10)
					{
						port_alt(FTM2_CH0,ALT2) ;
					}
          else if(FTM2_CH0 == PTC5)
          {
						port_alt(FTM2_CH0,ALT2) ;
          }
          else if(FTM2_CH0 == PTD0)
          {
						port_alt(FTM2_CH0,ALT4) ;
          }
					break;

        case CH1:
          if(FTM2_CH1 == PTA0)
					{
						port_alt(FTM2_CH1,ALT2) ;
					}
          else if(FTM2_CH1 == PTD11)
          {
						port_alt(FTM2_CH1,ALT2) ;
          }
          else if(FTM2_CH1 == PTD1)
          {
						port_alt(FTM2_CH1,ALT4) ;
          }
          break;
          
        case CH2:
					if(FTM2_CH2 == PTD12)
          {
						port_alt(FTM2_CH2,ALT2) ;
          }
          else if(FTM2_CH2 == PTE4)
          {
						port_alt(FTM2_CH2,ALT4) ;
          }
					break;
        
        case CH3:
					if(FTM2_CH3 == PTD5)
          {
						port_alt(FTM2_CH3,ALT2) ;
          }
          else if(FTM2_CH3 == PTE5)
          {
						port_alt(FTM2_CH3,ALT4) ;
          }           
          break;

        case CH4:
					if(FTM2_CH4 == PTD13)
          {
						port_alt(FTM2_CH4,ALT2) ;
          }
          else if(FTM2_CH4 == PTE10)
          {
						port_alt(FTM2_CH4,ALT4) ;
          }  
          break;
          
        case CH5:
					if(FTM2_CH5 == PTB5)
          {
						port_alt(FTM2_CH5,ALT2) ;
          }
          else if(FTM2_CH5 == PTE11)
          {
						port_alt(FTM2_CH5,ALT4) ;
          } 
          break;
          
				case CH6:
					if(FTM2_CH6 == PTC12)
          {
						port_alt(FTM2_CH6,ALT3) ;
          }
          else if(FTM2_CH6 == PTE15)
          {
						port_alt(FTM2_CH6,ALT4) ;
          } 
          break;
         
         case CH7:
					if(FTM2_CH7 == PTC13)
          {
						port_alt(FTM2_CH7,ALT3) ;
          }
          else if(FTM2_CH7 == PTE16)
          {
						port_alt(FTM2_CH7,ALT4) ;
          } 
          break ;

        default:
					break;
			}
			break;
			
		case SFTM3:
			PCC->PCCn[PCC_FTM3_INDEX]= PCC_PCCn_CGC_MASK+PCC_PCCn_PCS(6);  //使用SPLLDIV1_CLK作为时钟源,80M
			switch(ch)
			{
        case CH0:
          port_alt(FTM3_CH0,ALT2) ;
          break;

        case CH1:
          port_alt(FTM3_CH1,ALT2) ;           
          break;
          
        case CH2:
					if(FTM3_CH2 == PTB10)
					{
						port_alt(FTM3_CH2,ALT2) ;
					}
          else if(FTM3_CH2 == PTC6)
					{
						port_alt(FTM3_CH2,ALT4) ;
					}       
          break;
        
        case CH3:
					if(FTM3_CH3 == PTB11)
					{
						port_alt(FTM3_CH3,ALT2) ;
					}
          else if(FTM3_CH3 == PTC7)
					{
						port_alt(FTM3_CH3,ALT4) ;
					}          
          break;

        case CH4:
					port_alt(FTM3_CH4,ALT2) ;
          break;
          
        case CH5:
					port_alt(FTM3_CH5,ALT2) ;
          break;
          
				case CH6:
					if(FTM3_CH6 == PTC12)
					{
						port_alt(FTM3_CH6,ALT2) ;
					}
          else if(FTM3_CH6 == PTE2)
					{
						port_alt(FTM3_CH6,ALT4) ;
					}
          break;
         
         case CH7:
					if(FTM3_CH7 == PTC13)
					{
						port_alt(FTM3_CH7,ALT2) ;
					}
          else if(FTM3_CH7 == PTE6)
					{
						port_alt(FTM3_CH7,ALT4) ;
					}
          break ;
          
        default:
					break;
			}
			break;
			
    default:
        break;
  }
	FTMx[ftmn]->MODE |= FTM_MODE_WPDIS_MASK; //解除写保护
	
	/******************** 选择输出模式为 边沿对齐PWM *******************/
	//通道状态控制，根据模式来选择 边沿或电平
	//	FTMx[ftmn]->CONTROLS[ch].CnSC &= ~FTM_CnSC_ELSA_MASK;
	FTMx[ftmn]->CONTROLS[ch].CnSC = FTM_CnSC_MSB_MASK | FTM_CnSC_ELSB_MASK; //高有效
	//MSnB:MSnA = 1x
	// ELSnB:ELSnA = 10   High-true pulses  (clear Output on match)
	// ELSnB:ELSnA = 11   Low-true pulses   (set Output on match)
	// Edge-aligned PWM

	/******************** 配置时钟和分频 ********************/
	FTMx[ftmn]->SC |=  FTM_SC_PS(FTM_CLK_DIV) | FTM_SC_CLKS(0);  //128分频，625kHz
	FTMx[ftmn]->SC |= 1 << (FTM_SC_PWMEN0_SHIFT+ ch);	//通道使能
	FTMx[ftmn]->CNTIN = 0; 					 //计数器初始化值。脉冲宽度：(CnV - CNTIN).
	FTMx[ftmn]->MOD   = mod-1;				 //16bit, EPWM的周期为 ：MOD - CNTIN + 0x0001
	FTMx[ftmn]->CONTROLS[ch].CnV = duty * mod / FTM_PRECISON;            //占空比设置因子
}

/*************************************************************************
*  函数名称：FTM_PWM_Duty
*  功能说明：设置通道占空比
*  参数说明：FTMn        模块号（FTM0、  FTM1、  FTM2）
*            CHn         通道号（CH0~CH7）
*            duty        占空比
*  函数返回：无
*  修改时间：2012-2-14
*  备    注：
*************************************************************************/
void FTM_PWM_Duty(FTMn ftmn, CHn ch, uint8_t duty)
{
	uint32_t mod;
	//占空比 = (CnV-CNTIN)/(MOD-CNTIN+1)
	mod = FTMx[ftmn]->MOD + 1;        //读取 MOD 的值
  FTMx[ftmn]->CONTROLS[ch].CnV= duty * mod / FTM_PRECISON;       // 配置FTM通道值
}

/*************************************************************************
*  函数名称：FTM_Input_init
*  功能说明：输入捕捉初始化函数
*  参数说明：FTMn        模块号（FTM0、  FTM1、  FTM2）
*            CHn         通道号（CH0~CH7）
*            Input_cfg   输入捕捉配置（Rising、Falling、Rising_or_Falling）上升沿捕捉、下降沿捕捉、跳变沿捕捉
*  函数返回：无
*  修改时间：2012-1-26
*  备    注：CH0~CH3可以使用过滤器，未添加这功能
*************************************************************************/
void FTM_Input_init(FTMn ftmn, CHn ch, Input_cfg cfg)
{
  switch(ftmn)
  {
    case SFTM0:
			PCC->PCCn[PCC_FTM0_INDEX]= PCC_PCCn_CGC_MASK+PCC_PCCn_PCS(6);   //使用SPLLDIV1_CLK作为时钟源,80M
			switch(ch)
			{
        case CH0:
					port_alt(FTM0_CH0,ALT2) ;
					break;

        case CH1:
          port_alt(FTM0_CH1,ALT2) ;
          break;

        case CH2:
          port_alt(FTM0_CH2,ALT2) ;
          break;

        case CH3:
					port_alt(FTM0_CH3,ALT2) ;
					break;

        case CH4:
          port_alt(FTM0_CH4,ALT2) ;
					break;

        case CH5:
					port_alt(FTM0_CH5,ALT2) ;
					break;

        case CH6:
					port_alt(FTM0_CH6,ALT2) ;
					break;

        case CH7:
					port_alt(FTM0_CH7,ALT2) ;
          break;
        default:
					break;
      }
      break;

    case SFTM1:
			PCC->PCCn[PCC_FTM1_INDEX]= PCC_PCCn_CGC_MASK+PCC_PCCn_PCS(6);  //使用SPLLDIV1_CLK作为时钟源,80M
			switch(ch)
			{
        case CH0:
          port_alt(FTM1_CH0,ALT2) ;
          break;

        case CH1:
          port_alt(FTM1_CH1,ALT2) ;           
          break;
          
        case CH2:
          port_alt(FTM1_CH2,ALT2) ;           
          break;
        
        case CH3:
          port_alt(FTM1_CH3,ALT2) ;           
          break;

        case CH4:
          if(FTM1_CH4 == PTD8)
					{
						port_alt(FTM1_CH4,ALT6) ;
					}
          else if(FTM1_CH4 == PTA10)
          {
						port_alt(FTM1_CH4,ALT2) ;
          }
          break;
          
        case CH5:
          if(FTM1_CH5 == PTD9)
					{
						port_alt(FTM1_CH5,ALT6) ;
					}
          else if(FTM1_CH5 == PTA11)
					{
						port_alt(FTM1_CH5,ALT2) ;
					}
          break;
          
				case CH6:
					if(FTM1_CH6 == PTC0)
					{
						port_alt(FTM1_CH6,ALT6) ;
					}
          else if(FTM1_CH6 == PTA12)
					{
						port_alt(FTM1_CH6,ALT2) ;
					}
          break;
         
         case CH7:
          if(FTM1_CH7 == PTC1)
					{
						port_alt(FTM1_CH7,ALT6) ;
					}
          else if(FTM1_CH7 == PTA13)
					{
						port_alt(FTM1_CH7,ALT2) ;
					}
          break ;
          
        default:
					break;
			}
			break;
        
    case SFTM2:
			PCC->PCCn[PCC_FTM2_INDEX]= PCC_PCCn_CGC_MASK+PCC_PCCn_PCS(6);    //使用SPLLDIV1_CLK作为时钟源,80M
			switch(ch)
			{
        case CH0:
          if(FTM2_CH0 == PTD10)
					{
						port_alt(FTM2_CH0,ALT2) ;
					}
          else if(FTM2_CH0 == PTC5)
          {
						port_alt(FTM2_CH0,ALT2) ;
          }
          else if(FTM2_CH0 == PTD0)
          {
						port_alt(FTM2_CH0,ALT4) ;
          }
					break;

        case CH1:
          if(FTM2_CH1 == PTA0)
					{
						port_alt(FTM2_CH1,ALT2) ;
					}
          else if(FTM2_CH1 == PTD11)
          {
						port_alt(FTM2_CH1,ALT2) ;
          }
          else if(FTM2_CH1 == PTD1)
          {
						port_alt(FTM2_CH1,ALT4) ;
          }
          break;
          
        case CH2:
					if(FTM2_CH2 == PTD12)
          {
						port_alt(FTM2_CH2,ALT2) ;
          }
          else if(FTM2_CH2 == PTE4)
          {
						port_alt(FTM2_CH2,ALT4) ;
          }
					break;
        
        case CH3:
					if(FTM2_CH3 == PTD5)
          {
						port_alt(FTM2_CH3,ALT2) ;
          }
          else if(FTM2_CH3 == PTE5)
          {
						port_alt(FTM2_CH3,ALT4) ;
          }           
          break;

        case CH4:
					if(FTM2_CH4 == PTD13)
          {
						port_alt(FTM2_CH4,ALT2) ;
          }
          else if(FTM2_CH4 == PTE10)
          {
						port_alt(FTM2_CH4,ALT4) ;
          }  
          break;
          
        case CH5:
					if(FTM2_CH5 == PTB5)
          {
						port_alt(FTM2_CH5,ALT2) ;
          }
          else if(FTM2_CH5 == PTE11)
          {
						port_alt(FTM2_CH5,ALT4) ;
          } 
          break;
          
				case CH6:
					if(FTM2_CH6 == PTC12)
          {
						port_alt(FTM2_CH6,ALT3) ;
          }
          else if(FTM2_CH6 == PTE15)
          {
						port_alt(FTM2_CH6,ALT4) ;
          } 
          break;
         
         case CH7:
					if(FTM2_CH7 == PTC13)
          {
						port_alt(FTM2_CH7,ALT3) ;
          }
          else if(FTM2_CH7 == PTE16)
          {
						port_alt(FTM2_CH7,ALT4) ;
          } 
          break ;

        default:
					break;
			}
			break;
			
		case SFTM3:
			PCC->PCCn[PCC_FTM3_INDEX]= PCC_PCCn_CGC_MASK+PCC_PCCn_PCS(6);  //使用SPLLDIV1_CLK作为时钟源,80M
			switch(ch)
			{
        case CH0:
          port_alt(FTM3_CH0,ALT2) ;
          break;

        case CH1:
          port_alt(FTM3_CH1,ALT2) ;           
          break;
          
        case CH2:
					if(FTM3_CH2 == PTB10)
					{
						port_alt(FTM3_CH2,ALT2) ;
					}
          else if(FTM3_CH2 == PTC6)
					{
						port_alt(FTM3_CH2,ALT4) ;
					}       
          break;
        
        case CH3:
					if(FTM3_CH3 == PTB11)
					{
						port_alt(FTM3_CH3,ALT2) ;
					}
          else if(FTM3_CH3 == PTC7)
					{
						port_alt(FTM3_CH3,ALT4) ;
					}          
          break;

        case CH4:
					port_alt(FTM3_CH4,ALT2) ;
          break;
          
        case CH5:
					port_alt(FTM3_CH5,ALT2) ;
          break;
          
				case CH6:
					if(FTM3_CH6 == PTC12)
					{
						port_alt(FTM3_CH6,ALT2) ;
					}
          else if(FTM3_CH6 == PTE2)
					{
						port_alt(FTM3_CH6,ALT4) ;
					}
          break;
         
         case CH7:
					if(FTM3_CH7 == PTC13)
					{
						port_alt(FTM3_CH7,ALT2) ;
					}
          else if(FTM3_CH7 == PTE6)
					{
						port_alt(FTM3_CH7,ALT4) ;
					}
          break ;
          
        default:
					break;
			}
			break;
			
    default:
        break;
  }
	FTMx[ftmn]->MODE |= FTM_MODE_WPDIS_MASK; //解除写保护
	switch(cfg)
	{
		case Rising:    //上升沿触发
			FTMx[ftmn]->CONTROLS[ch].CnSC |=  ( FTM_CnSC_ELSA_MASK  | FTM_CnSC_CHIE_MASK | FTM_CnSC_ICRST_MASK);                   //置1
			FTMx[ftmn]->CONTROLS[ch].CnSC &= ~( FTM_CnSC_ELSB_MASK  | FTM_CnSC_MSB_MASK | FTM_CnSC_MSA_MASK); //清0
			break;

		case Falling:   //下降沿触发
	    FTMx[ftmn]->CONTROLS[ch].CnSC |= (FTM_CnSC_ELSB_MASK  | FTM_CnSC_CHIE_MASK | FTM_CnSC_ICRST_MASK);                    //置1
	    FTMx[ftmn]->CONTROLS[ch].CnSC &= ~( FTM_CnSC_ELSA_MASK | FTM_CnSC_MSB_MASK | FTM_CnSC_MSA_MASK); //清0
			break;

		case Rising_or_Falling: //上升沿、下降沿都触发
	    FTMx[ftmn]->CONTROLS[ch].CnSC |=  ( FTM_CnSC_ELSB_MASK | FTM_CnSC_ELSA_MASK  | FTM_CnSC_CHIE_MASK | FTM_CnSC_ICRST_MASK); //置1
	    FTMx[ftmn]->CONTROLS[ch].CnSC &= ~( FTM_CnSC_MSB_MASK  | FTM_CnSC_MSA_MASK); //清0
			break;
	}
	FTMx[ftmn]->SC |=  FTM_SC_PS(FTM_CLK_DIV) | FTM_SC_CLKS(0) | FTM_SC_TOIE_MASK;  //128分频，625kHz
	
	FTMx[ftmn]->CNTIN = 0;//计数器清零
}

void Start_FTM(FTMn ftmn)
{
	FTMx[ftmn]->SC |= FTM_SC_CLKS(1);
}
