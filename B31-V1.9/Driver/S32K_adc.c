#include "common.h"
#include "S32K_adc.h"
#include "port.h"

ADC_MemMapPtr ADCx[2] = {ADC0, ADC1}; //定义两个指针数组保存 ADCx 的地址

/*************************************************************************
*  函数名称：adc_init
*  功能说明：初始化PIN为AD模式
*  参数说明：ADCn      AD模块（AD0，AD1)
*            ADC_Ch    AD通道（1 2 3 ......)
*  函数返回：无
*  修改时间：2012-5-15   已测试
*  备    注：
*************************************************************************/
void Adc_Init(ADCn adcn, ADC_Ch ch)
{
	if(adcn== SADC0)      /*   ADC0  */
	{
		PCC->PCCn[PCC_ADC0_INDEX]=PCC_PCCn_CGC_MASK+PCC_PCCn_PCS(6);//使用SPLLDIV2_CLK作为时钟源
		switch(ch)
		{
			case AD0:  //ADC0_SE0-- PTA0
				port_alt(PTA0,ALT0);
				break; 
			case AD1:  //ADC0_SE1-- PTA1
				port_alt(PTA1,ALT0);
				break;
			case AD2:  //ADC0_SE2-- PTA6
				port_alt(PTA6,ALT0);
				break;
			case AD3:  //ADC0_SE3-- PTA7
				port_alt(PTA7,ALT0);
				break;
			case AD4:  //ADC0_SE4-- PTB0
				port_alt(PTB0,ALT0);
				break;
			case AD5:  //ADC0_SE5 -- PTB1
				port_alt(PTB1,ALT0);
				break;
			case AD6:  //ADC0_SE6 -- PTB2
				port_alt(PTB2,ALT0);
				break;
			case AD7:  //ADC0_SE7 -- PTB3
				port_alt(PTB3,ALT0);
				break;
			case AD8:   //ADC0_SE8 -- PTC0
				port_alt(PTC0,ALT0);
				break;
			case AD9:   //ADC0_SE9 -- PTC1
				port_alt(PTC1,ALT0);
				break;
			case AD10:  //ADC0_SE10 -- PTC2
				port_alt(PTC2,ALT0);
				break;
			case AD11:  //ADC0_SE11 -- PTC3
				port_alt(PTC3,ALT0);
				break;
			case AD12:  //ADC0_SE12 -- PTC14
				port_alt(PTC14,ALT0);
				break;
			case AD13:  //ADC0_SE13 -- PTC15
				port_alt(PTC15,ALT0);
				break;
			case AD14:  //ADC0_SE14 -- PTC16
				port_alt(PTC16,ALT0);
				break;
			case AD15:  //ADC0_SE15 -- PTC17
				port_alt(PTC17,ALT0);
				break;
			default:
				break;
		}
	}
	else// SADC1:       /*   ADC1    */
	{
		PCC->PCCn[PCC_ADC1_INDEX]=PCC_PCCn_CGC_MASK+PCC_PCCn_PCS(6);//使用SPLLDIV2_CLK作为时钟源
		switch(ch)
		{
			case AD0:  //ADC1_SE0-- PTA2
				port_alt(PTA2,ALT0);
				break; 
			case AD1:  //ADC1_SE1-- PTA3
				port_alt(PTA3,ALT0);
				break;
			case AD2:  //ADC1_SE2-- PTD2
				port_alt(PTD2,ALT0);
				break;
			case AD3:  //ADC1_SE3-- PTD3
				port_alt(PTD3,ALT0);
				break;  
			case AD4:   //ADC1_SE4   -- PTC6
				port_alt(PTC6,ALT0);
				break;
			case AD5:   //ADC1_SE5   -- PTC7
				port_alt(PTC7,ALT0);
				break;
			case AD6:   //ADC1_SE6   -- PTD4
				port_alt(PTD4,ALT0);
				break;
			case AD7:   //ADC1_SE7   -- PTB12
				port_alt(PTB12,ALT0);
				break;
			case AD8:  //ADC1_SE8 -- PTB13
				port_alt(PTB13,ALT0);
				break;
			case AD9:  //ADC1_SE9 -- PTB14
				port_alt(PTB14,ALT0);
				break;
			case AD10:  //ADC1_SE10 -- PTE2
				port_alt(PTE2,ALT0);
				break;
			case AD11:  //ADC1_SE11 -- PTE6
				port_alt(PTE6,ALT0);
				break;
			case AD12:  //ADC1_SE12 -- PTA15
				port_alt(PTA15,ALT0);
				break;
			case AD13:  //ADC1_SE13 -- PTA16
				port_alt(PTA16,ALT0);
				break;
			case AD14:  //ADC1_SE14 -- PTB15
				port_alt(PTB15,ALT0);
				break;
			case AD15:  //ADC1_SE15 -- PTB16
				port_alt(PTB16,ALT0);
				break;
			default:
				break;
		}
  }
	ADCx[adcn]->CFG1  = ADC_CFG1_ADIV(ADIV_1)				//1分频
										| ADC_CFG1_MODE(ADC_12bit)		//12bit
										| ADC_CFG1_ADICLK(ADICLK_BUS);//SPLLDIV2_CLK，40mHz时钟
	ADCx[adcn]->CFG2  =  ADC_CFG2_SMPLTS(100);//101个时钟周期采集完毕
	ADCx[adcn]->SC1[0] |= ADC_SC1_AIEN_MASK;//中断使能
}

void adc_start(ADCn adcn, ADC_Ch ch)
{
	ADCx[adcn]->SC1[0] =(ADCx[adcn]->SC1[0] & ~ADC_SC1_ADCH_MASK) | ADC_SC1_ADCH(ch);//只有0可以软触发
}

void ADC_AutoCalibration(ADCn adcn)
{
    ADCx[adcn]->SC3 |= ADC_SC3_AVGS(ADC_AVERAGE_32);
    ADCx[adcn]->SC3 |= ADC_SC3_AVGE_MASK;
    ADCx[adcn]->SC2 &= ~(ADC_SC2_ADTRG_MASK);

    ADCx[adcn]->CLPS = 0x00u;
    ADCx[adcn]->CLP3 = 0x00u;
    ADCx[adcn]->CLP2 = 0x00u;
    ADCx[adcn]->CLP1 = 0x00u;
    ADCx[adcn]->CLP0 = 0x00u;
    ADCx[adcn]->CLPX = 0x00u;
    ADCx[adcn]->CLP9 = 0x00u;

    /* start calibration */
    ADCx[adcn]->SC3 |= ADC_SC3_CAL_MASK;
    while (ADCx[adcn]->SC3 & ADC_SC3_CAL_MASK)
    {
        __NOP();/* Wait for calibration to finish */
    }

    /* restore hardware average and trigger settings*/
		ADCx[adcn]->SC3 &= ~ADC_SC3_AVGS_MASK;
		ADCx[adcn]->SC3 &= ~ADC_SC3_AVGE_MASK;
		ADCx[adcn]->SC2 &= ~(ADC_SC2_ADTRG_MASK);
}

