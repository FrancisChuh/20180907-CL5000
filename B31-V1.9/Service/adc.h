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
/*   �����ļ�����ADC.h         										                        */
/*   Filename  ��ADC.h         			                        						  */
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

#ifndef __ADC_H
#define __ADC_H

#include <stdint.h>

#include "S32K_adc.h"


typedef struct
{
	int16_t T_TIN;           //����
  int16_t T_TOUT;          //����
  int16_t V_MODEFB;        //ģʽ����
  int16_t V_RECFB;         //����ѭ������
	int16_t T_TEVA;          //�������¶�
	int16_t	T_TEVA_REAR;			//���������¶�
  int16_t V_VOL12V;        //12V��ѹ
	int16_t T_FOOT_MASTER;		//��ʻ�����¶�
	int16_t T_FACE_MASTER;		//��ʻ�����¶�
	int16_t	T_FOOT_SLAVE;		//�˿ʹ����¶�
	int16_t	T_FACE_SLAVE;		//�˿ʹ����¶�	
	int16_t	T_FOOT_RESERVED; //����Ԥ��
	int16_t	T_FACE_RESERVED;	//����Ԥ��
	int16_t	T_TMP_RESERVED1;	//�¶�Ԥ��
	int16_t	T_TMP_RESERVED2;	//�¶�Ԥ��
	int16_t	T_WATER_TMP1;		//ˮ��1
	int16_t	T_WATER_TMP2;		//ˮ��2
	int16_t	T_PIPE_TEM1;	//��·�¶�1
	int16_t	T_PIPE_TEM2; //��·�¶�2
	int16_t	T_PIPE_TEM3;	//��·�¶�3
	int16_t	V_MIX_MASTER_FB;	//�¶ȷ��ŷ�������ʻ
	int16_t	V_MIX_SLAVE_FB;	//�¶ȷ��ŷ������˿�
	int16_t	V_MIX_REAR_FB;		//�¶ȷ��ŷ���������
	float		P_PIPE_PRES1;		//��·ѹ��1
	float		P_PIPE_PRES2;		//��·ѹ��2
	float		P_PIPE_PRES3;		//��·ѹ��3
	int16_t	V_ENABLE_REAR_FB;//���ŷ�����ط���
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




/*      ADC0�б�        */
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
                                
/*      ADC1�б�        */      
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
