#include  "S32K_FTM.h"

#define FTM_PRECISON 100u     //����ռ�ձȾ��ȣ�100������Ϊ1%��1000u�򾫶�Ϊ0.1%������ռ�ձ� duty �βδ��룬��ռ�ձ�Ϊ duty/FTM_PRECISON
#define FTM_CLK_DIV 7

volatile FTM_Type *FTMx[4] = {FTM0, FTM1, FTM2, FTM3}; //�����ĸ�ָ�����鱣�� FTMn �ĵ�ַ

/*************************************************************************
*  �������ƣ�FTM_PWM_init
*  ����˵������ʼ��FTM��PWM���ܲ�����Ƶ�ʡ�ռ�ձȡ�����ͨ�����ռ�ձȡ�
*  ����˵����FTMn        ģ��ţ�FTM0��  FTM1��  FTM2��
*            CHn         ͨ���ţ�CH0~CH7��
*            freq        Ƶ�ʣ���λΪHz��
*            duty        ռ�ձ�
*  �������أ���
*  �޸�ʱ�䣺2012-2-14
*  ��    ע��ͬһ��FTM����ͨ����PWMƵ����һ���ģ���3��FTM�����������3����ͬƵ��PWM
*************************************************************************/
void FTM_PWM_init(FTMn ftmn, CHn ch, uint32_t freq, uint8_t duty)
{
	uint16_t mod;
  /*       �����Ƶ����       */
  mod = (SystemCoreClock >> FTM_CLK_DIV) / freq;		//Ƶ����������,clk_hz = 625000
  switch(ftmn)
  {
    case SFTM0:
			PCC->PCCn[PCC_FTM0_INDEX]= PCC_PCCn_CGC_MASK+PCC_PCCn_PCS(6);   //ʹ��SPLLDIV1_CLK��Ϊʱ��Դ,80M
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
			PCC->PCCn[PCC_FTM1_INDEX]= PCC_PCCn_CGC_MASK+PCC_PCCn_PCS(6);  //ʹ��SPLLDIV1_CLK��Ϊʱ��Դ,80M
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
			PCC->PCCn[PCC_FTM2_INDEX]= PCC_PCCn_CGC_MASK+PCC_PCCn_PCS(6);    //ʹ��SPLLDIV1_CLK��Ϊʱ��Դ,80M
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
			PCC->PCCn[PCC_FTM3_INDEX]= PCC_PCCn_CGC_MASK+PCC_PCCn_PCS(6);  //ʹ��SPLLDIV1_CLK��Ϊʱ��Դ,80M
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
	FTMx[ftmn]->MODE |= FTM_MODE_WPDIS_MASK; //���д����
	
	/******************** ѡ�����ģʽΪ ���ض���PWM *******************/
	//ͨ��״̬���ƣ�����ģʽ��ѡ�� ���ػ��ƽ
	//	FTMx[ftmn]->CONTROLS[ch].CnSC &= ~FTM_CnSC_ELSA_MASK;
	FTMx[ftmn]->CONTROLS[ch].CnSC = FTM_CnSC_MSB_MASK | FTM_CnSC_ELSB_MASK; //����Ч
	//MSnB:MSnA = 1x
	// ELSnB:ELSnA = 10   High-true pulses  (clear Output on match)
	// ELSnB:ELSnA = 11   Low-true pulses   (set Output on match)
	// Edge-aligned PWM

	/******************** ����ʱ�Ӻͷ�Ƶ ********************/
	FTMx[ftmn]->SC |=  FTM_SC_PS(FTM_CLK_DIV) | FTM_SC_CLKS(0);  //128��Ƶ��625kHz
	FTMx[ftmn]->SC |= 1 << (FTM_SC_PWMEN0_SHIFT+ ch);	//ͨ��ʹ��
	FTMx[ftmn]->CNTIN = 0; 					 //��������ʼ��ֵ�������ȣ�(CnV - CNTIN).
	FTMx[ftmn]->MOD   = mod-1;				 //16bit, EPWM������Ϊ ��MOD - CNTIN + 0x0001
	FTMx[ftmn]->CONTROLS[ch].CnV = duty * mod / FTM_PRECISON;            //ռ�ձ���������
}

/*************************************************************************
*  �������ƣ�FTM_PWM_Duty
*  ����˵��������ͨ��ռ�ձ�
*  ����˵����FTMn        ģ��ţ�FTM0��  FTM1��  FTM2��
*            CHn         ͨ���ţ�CH0~CH7��
*            duty        ռ�ձ�
*  �������أ���
*  �޸�ʱ�䣺2012-2-14
*  ��    ע��
*************************************************************************/
void FTM_PWM_Duty(FTMn ftmn, CHn ch, uint8_t duty)
{
	uint32_t mod;
	//ռ�ձ� = (CnV-CNTIN)/(MOD-CNTIN+1)
	mod = FTMx[ftmn]->MOD + 1;        //��ȡ MOD ��ֵ
  FTMx[ftmn]->CONTROLS[ch].CnV= duty * mod / FTM_PRECISON;       // ����FTMͨ��ֵ
}

/*************************************************************************
*  �������ƣ�FTM_Input_init
*  ����˵�������벶׽��ʼ������
*  ����˵����FTMn        ģ��ţ�FTM0��  FTM1��  FTM2��
*            CHn         ͨ���ţ�CH0~CH7��
*            Input_cfg   ���벶׽���ã�Rising��Falling��Rising_or_Falling�������ز�׽���½��ز�׽�������ز�׽
*  �������أ���
*  �޸�ʱ�䣺2012-1-26
*  ��    ע��CH0~CH3����ʹ�ù�������δ����⹦��
*************************************************************************/
void FTM_Input_init(FTMn ftmn, CHn ch, Input_cfg cfg)
{
  switch(ftmn)
  {
    case SFTM0:
			PCC->PCCn[PCC_FTM0_INDEX]= PCC_PCCn_CGC_MASK+PCC_PCCn_PCS(6);   //ʹ��SPLLDIV1_CLK��Ϊʱ��Դ,80M
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
			PCC->PCCn[PCC_FTM1_INDEX]= PCC_PCCn_CGC_MASK+PCC_PCCn_PCS(6);  //ʹ��SPLLDIV1_CLK��Ϊʱ��Դ,80M
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
			PCC->PCCn[PCC_FTM2_INDEX]= PCC_PCCn_CGC_MASK+PCC_PCCn_PCS(6);    //ʹ��SPLLDIV1_CLK��Ϊʱ��Դ,80M
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
			PCC->PCCn[PCC_FTM3_INDEX]= PCC_PCCn_CGC_MASK+PCC_PCCn_PCS(6);  //ʹ��SPLLDIV1_CLK��Ϊʱ��Դ,80M
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
	FTMx[ftmn]->MODE |= FTM_MODE_WPDIS_MASK; //���д����
	switch(cfg)
	{
		case Rising:    //�����ش���
			FTMx[ftmn]->CONTROLS[ch].CnSC |=  ( FTM_CnSC_ELSA_MASK  | FTM_CnSC_CHIE_MASK | FTM_CnSC_ICRST_MASK);                   //��1
			FTMx[ftmn]->CONTROLS[ch].CnSC &= ~( FTM_CnSC_ELSB_MASK  | FTM_CnSC_MSB_MASK | FTM_CnSC_MSA_MASK); //��0
			break;

		case Falling:   //�½��ش���
	    FTMx[ftmn]->CONTROLS[ch].CnSC |= (FTM_CnSC_ELSB_MASK  | FTM_CnSC_CHIE_MASK | FTM_CnSC_ICRST_MASK);                    //��1
	    FTMx[ftmn]->CONTROLS[ch].CnSC &= ~( FTM_CnSC_ELSA_MASK | FTM_CnSC_MSB_MASK | FTM_CnSC_MSA_MASK); //��0
			break;

		case Rising_or_Falling: //�����ء��½��ض�����
	    FTMx[ftmn]->CONTROLS[ch].CnSC |=  ( FTM_CnSC_ELSB_MASK | FTM_CnSC_ELSA_MASK  | FTM_CnSC_CHIE_MASK | FTM_CnSC_ICRST_MASK); //��1
	    FTMx[ftmn]->CONTROLS[ch].CnSC &= ~( FTM_CnSC_MSB_MASK  | FTM_CnSC_MSA_MASK); //��0
			break;
	}
	FTMx[ftmn]->SC |=  FTM_SC_PS(FTM_CLK_DIV) | FTM_SC_CLKS(0) | FTM_SC_TOIE_MASK;  //128��Ƶ��625kHz
	
	FTMx[ftmn]->CNTIN = 0;//����������
}

void Start_FTM(FTMn ftmn)
{
	FTMx[ftmn]->SC |= FTM_SC_CLKS(1);
}
