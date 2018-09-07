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
/*   程序文件名：ADC.h         										                        */
/*   Filename  ：ADC.h         			                        						  */
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

#ifndef __ADC_H
#define __ADC_H

#include <stdint.h>

#include "S32K_adc.h"


typedef struct
{
	int16_t T_TIN;           //内温
  int16_t T_TOUT;          //外温
  int16_t V_MODEFB;        //模式反馈
  int16_t V_RECFB;         //内外循环反馈
	int16_t T_TEVA;          //蒸发器温度
	int16_t	T_TEVA_REAR;			//后蒸发器温度
  int16_t V_VOL12V;        //12V电压
	int16_t T_FOOT_MASTER;		//驾驶吹脚温度
	int16_t T_FACE_MASTER;		//驾驶吹面温度
	int16_t	T_FOOT_SLAVE;		//乘客吹脚温度
	int16_t	T_FACE_SLAVE;		//乘客吹面温度	
	int16_t	T_FOOT_RESERVED; //吹脚预留
	int16_t	T_FACE_RESERVED;	//吹面预留
	int16_t	T_TMP_RESERVED1;	//温度预留
	int16_t	T_TMP_RESERVED2;	//温度预留
	int16_t	T_WATER_TMP1;		//水温1
	int16_t	T_WATER_TMP2;		//水温2
	int16_t	T_PIPE_TEM1;	//管路温度1
	int16_t	T_PIPE_TEM2; //管路温度2
	int16_t	T_PIPE_TEM3;	//管路温度3
	int16_t	V_MIX_MASTER_FB;	//温度风门反馈，驾驶
	int16_t	V_MIX_SLAVE_FB;	//温度风门反馈，乘客
	int16_t	V_MIX_REAR_FB;		//温度风门反馈，后排
	float		P_PIPE_PRES1;		//管路压力1
	float		P_PIPE_PRES2;		//管路压力2
	float		P_PIPE_PRES3;		//管路压力3
	int16_t	V_ENABLE_REAR_FB;//后排风道开关反馈
}AD_Value_Convert_TypeDef;

#define ADVAL_ERR_FLAG_TAMB_MASK  0x01
#define ADVAL_ERR_FLAG_TIN_MASK   0x02
#define ADVAL_ERR_FLAG_PHOTO_MASK 0x04

typedef enum WR{
    w=0,
    r=1,
}WR;

typedef void adc_data_proc(enum WR wr,int16_t *ad);

typedef struct ADC_Proc{
    struct ADC_Proc     *prev;
    enum ADC_Ch         ch;
    enum ADCn           adc_n;
    int16_t             ADC_Res;
    adc_data_proc       *data_proc;
    int16_t             DATA;
}ADC_Proc;




/*      ADC0列表        */
extern ADC_Proc AD_TsensorFoot_CO      ;
extern ADC_Proc AD_TsensorFace_CO      ;
extern ADC_Proc AD_TsensorFoot_PA      ;
extern ADC_Proc AD_TsensorFace_PA      ;
extern ADC_Proc AD_TsensorEVA          ;
extern ADC_Proc AD_IntakeACTFB         ;
extern ADC_Proc AD_TempACTFB_PA        ;
extern ADC_Proc AD_ModeACTFB           ;
extern ADC_Proc AD_TempACTFB_CO        ;
extern ADC_Proc AD_T_TPsensor2         ;
extern ADC_Proc AD_T_TPsensor1         ;
extern ADC_Proc AD_TsensorFace_3       ;
extern ADC_Proc AD_Tsensor_RE1         ;
                                
/*      ADC1列表        */      
extern ADC_Proc AD_TsensorFoot_3       ;
extern ADC_Proc AD_Tsensor_RE2         ;
extern ADC_Proc AD_R_TsensorEVA        ;
extern ADC_Proc AD_TsensorOUTCAR       ;
extern ADC_Proc AD_TsensorINCAR        ;
extern ADC_Proc AD_WTsensor2           ;
extern ADC_Proc AD_T_TPsensor3         ;
extern ADC_Proc AD_WTsensor1           ;
extern ADC_Proc AD_DesACTFB_Rear       ;
extern ADC_Proc AD_P_TPsensor3         ;
extern ADC_Proc AD_TempACTFB_Rear      ;
extern ADC_Proc AD_P_TPsensor1         ;
extern ADC_Proc AD_P_TPsensor2         ;
extern ADC_Proc AD_12                  ;



void Board_ADC_Init(void);
void AD_Scan(void);
void AD_OutTem_Read(void);
void AD_PHOTO_Read(void);

extern uint8_t ADVAL_ERR_FLAG;
extern AD_Value_Convert_TypeDef s_AD_Con;

#endif /* _ADC_H__ */
