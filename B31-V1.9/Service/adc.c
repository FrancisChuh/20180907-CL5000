/**************************************************************************/
/*    重庆超力高科技股份有限公司          版权所有                        */
/**************************************************************************/
/*   @@BEGAIN_INTERNAL_LEGAL@@                                            */
/*                                                                        */
/*                   Copyright(C) Description                          	  */
/*     CHONGQING CHAOLI HI-TECH Co.,Ltd. Chongqing, China   				      */
/*     Unpublished work-rights reserved under the China Copyright Act.  	*/
/*     Use,duplication, or disclosure by the government is subject to   	*/
/*     restrictions set forth in the CDTT commercial license agreement. 	*/
/*																		                                    */
/*   @@END_INTERNAL_LEGAL@@												                        */
/**************************************************************************/
/*   程序文件名：ADC.c         										                        */
/*   Filename  ：ADC.c         			                        						  */
/*   作者      ：何晓东								                        		        */
/*   Author    ：Jack									                        	    	    */
/*   日期      ：10/23/2017						                        				    */
/*   Date      ：10/23/2017						                        					  */
/*   当前版本  ：1.0									                        				    */
/*   Version	 ：1.0                                                      */
/*   实现目的  ：ADC初始化									                        		  */
/*   Purpose   ：ADC_Init                                                 */
/**************************************************************************/
/*   修改记录  ：无                                                       */
/*   序号 , MM/DD/YYYY,版本，修改者，修改内容(最近的修改记录在最上面)     */
/*   Modi Report：                                                        */
/*   Index，Date，Version，Author, content                                */
/**************************************************************************/

#include "adc.h"
#include "modules_switch.h"

AD_Value_Convert_TypeDef s_AD_Con;


/*      ADC0列表        */
ADC_Proc AD_TsensorFoot_CO      ={.ch=AD10,.adc_n=SADC0,.prev=0};                       //PTC2:ADC0_SE10
ADC_Proc AD_TsensorFace_CO      ={.ch=AD9 ,.adc_n=SADC0,.prev=&AD_TsensorFoot_CO};      //PTC1:ADC0_SE9
ADC_Proc AD_TsensorFoot_PA      ={.ch=AD8 ,.adc_n=SADC0,.prev=&AD_TsensorFace_CO};      //PTC0:ADC0_SE8
ADC_Proc AD_TsensorFace_PA      ={.ch=AD15,.adc_n=SADC0,.prev=&AD_TsensorFoot_PA}; //PTC17:ADC0_SE15
ADC_Proc AD_TsensorEVA          ={.ch=AD14,.adc_n=SADC0,.prev=&AD_TsensorFace_PA}; //PTC16:ADC0_SE14
ADC_Proc AD_IntakeACTFB         ={.ch=AD13,.adc_n=SADC0,.prev=&AD_TsensorEVA};     //PTC15:ADC0_SE13
ADC_Proc AD_TempACTFB_PA        ={.ch=AD12,.adc_n=SADC0,.prev=&AD_IntakeACTFB};    //PTC14:ADC0_SE12
ADC_Proc AD_ModeACTFB           ={.ch=AD7 ,.adc_n=SADC0,.prev=&AD_TempACTFB_PA};   //PTB3:ADC0_SE7
ADC_Proc AD_TempACTFB_CO        ={.ch=AD6 ,.adc_n=SADC0,.prev=&AD_ModeACTFB};      //PTB2:ADC0_SE6
ADC_Proc AD_T_TPsensor2         ={.ch=AD1 ,.adc_n=SADC0,.prev=&AD_TempACTFB_CO};      //PTA1:ADC0_SE1
ADC_Proc AD_T_TPsensor1         ={.ch=AD0 ,.adc_n=SADC0,.prev=&AD_T_TPsensor2};    //PTA0:ADC0_SE0
ADC_Proc AD_TsensorFace_3       ={.ch=AD9 ,.adc_n=SADC0,.prev=&AD_T_TPsensor1};    //PTB14:ADC1_SE9/ADC0_SE9
ADC_Proc AD_Tsensor_RE1         ={.ch=AD8 ,.adc_n=SADC0,.prev=&AD_TsensorFace_3};  //PTB13:ADC1_SE8/ADC0_SE8

/*      ADC1列表        */
ADC_Proc AD_TsensorFoot_3       ={.ch=AD15,.adc_n=SADC1,.prev=&AD_Tsensor_RE1};   //PTB16:ADC1_SE15
ADC_Proc AD_Tsensor_RE2         ={.ch=AD14,.adc_n=SADC1,.prev=&AD_TsensorFoot_3};  //PTB15:ADC1_SE14
ADC_Proc AD_R_TsensorEVA        ={.ch=AD7 ,.adc_n=SADC1,.prev=&AD_Tsensor_RE2};    //PTB12:ADC1_SE7
ADC_Proc AD_TsensorOUTCAR       ={.ch=AD6 ,.adc_n=SADC1,.prev=&AD_R_TsensorEVA};   //PTD4:ADC1_SE6
ADC_Proc AD_TsensorINCAR        ={.ch=AD3 ,.adc_n=SADC1,.prev=&AD_TsensorOUTCAR};  //PTD3:ADC1_SE3
ADC_Proc AD_WTsensor2           ={.ch=AD2 ,.adc_n=SADC1,.prev=&AD_TsensorINCAR};   //PTD2:ADC1_SE2
ADC_Proc AD_T_TPsensor3         ={.ch=AD1 ,.adc_n=SADC1,.prev=&AD_WTsensor2};      //PTA3:ADC1_SE1
ADC_Proc AD_WTsensor1           ={.ch=AD0 ,.adc_n=SADC1,.prev=&AD_T_TPsensor3};    //PTA2:ADC1_SE0
ADC_Proc AD_DesACTFB_Rear       ={.ch=AD5 ,.adc_n=SADC1,.prev=&AD_WTsensor1};    //PTC7:ADC1_SE5
ADC_Proc AD_P_TPsensor3         ={.ch=AD4 ,.adc_n=SADC1,.prev=&AD_DesACTFB_Rear};  //PTC6:ADC1_SE4
ADC_Proc AD_TempACTFB_Rear      ={.ch=AD13,.adc_n=SADC1,.prev=&AD_P_TPsensor3};    //PTA16:ADC1_SE13
ADC_Proc AD_P_TPsensor1         ={.ch=AD12,.adc_n=SADC1,.prev=&AD_TempACTFB_Rear}; //PTA15:ADC1_SE12
ADC_Proc AD_P_TPsensor2         ={.ch=AD11,.adc_n=SADC1,.prev=&AD_P_TPsensor1};    //PTE6:ADC1_SE11
ADC_Proc AD_12                  ={.ch=AD10,.adc_n=SADC1,.prev=&AD_P_TPsensor2};    //PTE2:ADC1_SE10




#define LAST_AD             AD_12               //最后一个AD
#define Last_AD1_CH         LAST_AD             //adc1的末尾
#define First_AD1_CH        AD_TsensorFoot_3    //adc1的开始
#define First_AD0_CH        AD_TsensorFoot_CO   //adc0的开始
#define Last_AD0_CH         AD_Tsensor_RE1      //adc0的末尾


//采样结束的标志
#define ADC0_OVER_FLAG 0x01
#define ADC1_OVER_FLAG 0x02

static u8 ADC_OVER_FLAG = ADC0_OVER_FLAG | ADC1_OVER_FLAG;

u8 ADVAL_ERR_FLAG=ADVAL_ERR_FLAG_TAMB_MASK | ADVAL_ERR_FLAG_TIN_MASK |ADVAL_ERR_FLAG_PHOTO_MASK;



void Board_ADC_Init(void)
{
    ADC_Proc *ad;
    ad=&LAST_AD;
	while(1)
    {
        if(ad->prev==0)break;
        else{
            Adc_Init(ad->adc_n,ad->ch);
            ad=ad->prev;
        }
    }

    ADC_AutoCalibration(SADC0);
    ADC_AutoCalibration(SADC1);

	NVIC_Init(ADC0_IRQn,12);
	NVIC_Init(ADC1_IRQn,12);
}



void adc0_start(void)
{
    static ADC_Proc *ad;
    if(ad==0)               //刚刚开始采样
    {
        ad=&Last_AD0_CH;    //放入最后一个通道的ad
        adc_start(ad->adc_n,ad->ch);//开始采样
    }
    else if(ad==&First_AD0_CH)//最后一个已经采完
    {
        ad->ADC_Res=ADC0->R[0];//放入之前采样的数据
        ad=0;               //清除ad
        ADC_OVER_FLAG|=ADC0_OVER_FLAG;//采样完成标志
    }
    else  //采样中
    {
        ad->ADC_Res=ADC0->R[0];//放入之前采样的数据
        ad=ad->prev;//放入下一个要采样的通道
        adc_start(ad->adc_n,ad->ch);
    }
}

void adc1_start(void)
{
    static ADC_Proc *ad;
    if(ad==0)               //刚刚开始采样
    {
        ad=&Last_AD1_CH;    //放入最后一个通道的ad
        adc_start(ad->adc_n,ad->ch);//开始采样
    }
    else if(ad==&First_AD1_CH)//最后一个已经采完
    {
        ad->ADC_Res=ADC1->R[0];//放入之前采样的数据
        ad=0;               //清除ad
        ADC_OVER_FLAG|=ADC1_OVER_FLAG;//采样完成标志
    }
    else  //采样中
    {
        ad->ADC_Res=ADC1->R[0];//放入之前采样的数据
        ad=ad->prev;//放入下一个要采样的通道
        adc_start(ad->adc_n,ad->ch);
    }
}

void AD_Scan(void)
{
    ADC_Proc *ad;
	if(ADC_OVER_FLAG & ADC1_OVER_FLAG)
	{
		////ADC1采样结束，处理数据
        ad=&Last_AD1_CH;
        while(1)
        {
//            ad->data_proc(w,&ad->ADC_Res);
            ad->DATA=ad->ADC_Res;
            if(ad==&First_AD1_CH)break;
            else ad=ad->prev;
        }
        ADC_OVER_FLAG &=~ADC1_OVER_FLAG;
        adc1_start();
	}
	if(ADC_OVER_FLAG & ADC0_OVER_FLAG)
	{
        ////ADC0采样结束，处理数据
        ad=&Last_AD0_CH;
        while(1)
        {
//            ad->data_proc(w,&ad->ADC_Res);
            ad->DATA=ad->ADC_Res;
            if(ad==&First_AD0_CH)break;
            else ad=ad->prev;
        }
        ADC_OVER_FLAG &=~ADC0_OVER_FLAG;
		adc0_start();
	}
}

void AD_PHOTO_Read(void)
{
    ;
}

void AD_OutTem_Read(void)
{
    ;
}

void ADC0_IRQHandler(void)
{
	adc0_start();
}

void ADC1_IRQHandler(void)
{
	adc1_start();
}
//end
