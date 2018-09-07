/**************************************************************************/
/*    ���쳬���߿Ƽ��ɷ����޹�˾          ��Ȩ����                        */
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
/*   �����ļ�����ADC.c         										                        */
/*   Filename  ��ADC.c         			                        						  */
/*   ����      ��������								                        		        */
/*   Author    ��Jack									                        	    	    */
/*   ����      ��10/23/2017						                        				    */
/*   Date      ��10/23/2017						                        					  */
/*   ��ǰ�汾  ��1.0									                        				    */
/*   Version	 ��1.0                                                      */
/*   ʵ��Ŀ��  ��ADC��ʼ��									                        		  */
/*   Purpose   ��ADC_Init                                                 */
/**************************************************************************/
/*   �޸ļ�¼  ����                                                       */
/*   ��� , MM/DD/YYYY,�汾���޸��ߣ��޸�����(������޸ļ�¼��������)     */
/*   Modi Report��                                                        */
/*   Index��Date��Version��Author, content                                */
/**************************************************************************/

#include "adc.h"
#include "modules_switch.h"

AD_Value_Convert_TypeDef s_AD_Con;


/*      ADC0�б�        */
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

/*      ADC1�б�        */
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




#define LAST_AD             AD_12               //���һ��AD
#define Last_AD1_CH         LAST_AD             //adc1��ĩβ
#define First_AD1_CH        AD_TsensorFoot_3    //adc1�Ŀ�ʼ
#define First_AD0_CH        AD_TsensorFoot_CO   //adc0�Ŀ�ʼ
#define Last_AD0_CH         AD_Tsensor_RE1      //adc0��ĩβ


//���������ı�־
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
    if(ad==0)               //�ոտ�ʼ����
    {
        ad=&Last_AD0_CH;    //�������һ��ͨ����ad
        adc_start(ad->adc_n,ad->ch);//��ʼ����
    }
    else if(ad==&First_AD0_CH)//���һ���Ѿ�����
    {
        ad->ADC_Res=ADC0->R[0];//����֮ǰ����������
        ad=0;               //���ad
        ADC_OVER_FLAG|=ADC0_OVER_FLAG;//������ɱ�־
    }
    else  //������
    {
        ad->ADC_Res=ADC0->R[0];//����֮ǰ����������
        ad=ad->prev;//������һ��Ҫ������ͨ��
        adc_start(ad->adc_n,ad->ch);
    }
}

void adc1_start(void)
{
    static ADC_Proc *ad;
    if(ad==0)               //�ոտ�ʼ����
    {
        ad=&Last_AD1_CH;    //�������һ��ͨ����ad
        adc_start(ad->adc_n,ad->ch);//��ʼ����
    }
    else if(ad==&First_AD1_CH)//���һ���Ѿ�����
    {
        ad->ADC_Res=ADC1->R[0];//����֮ǰ����������
        ad=0;               //���ad
        ADC_OVER_FLAG|=ADC1_OVER_FLAG;//������ɱ�־
    }
    else  //������
    {
        ad->ADC_Res=ADC1->R[0];//����֮ǰ����������
        ad=ad->prev;//������һ��Ҫ������ͨ��
        adc_start(ad->adc_n,ad->ch);
    }
}

void AD_Scan(void)
{
    ADC_Proc *ad;
	if(ADC_OVER_FLAG & ADC1_OVER_FLAG)
	{
		////ADC1������������������
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
        ////ADC0������������������
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
