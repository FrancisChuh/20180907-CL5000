#ifndef __AC_CORE_H
#define __AC_CORE_H

#include <stdint.h>
#include "fan.h"
#include "actuator.h"
#include "adc.h"


//������
typedef struct AC_Sensors{
    ADC_Proc *TsensorOUTCAR; //�����¶ȴ�����
    ADC_Proc *TsensorINCAR;  //�����¶ȴ�����
    ADC_Proc *TsensorEVA;    //�������¶ȴ�����
    ADC_Proc *TsensorFoot_CO;//�����¶ȴ�����������ʻ
    ADC_Proc *TsensorFace_CO;//�����¶ȴ�����������ʻ
    ADC_Proc *TsensorFoot_PA;//�����¶ȴ���������ʻ
    ADC_Proc *TsensorFace_PA;//�����¶ȴ���������ʻ
    ADC_Proc *WTsensor2;//���ˮ�´�����:ȷ��û���
    ADC_Proc *WTsensor1;//���ˮ�´�����:ȷ��û���
    ADC_Proc *P_TPsensor1;//��ѹѹ��������1
    
    
    //����ǿ�ȴ�����
    
    
 }AC_Sensors;

    
//ִ����
typedef struct AC_Actuators{
    ACTUATOR_PROC *Intake_Run;//����ѭ��
    ACTUATOR_PROC *Mode_Run;//ģʽִ����
    ACTUATOR_PROC *TempACT_CO_Run;//����ʻ�¶�ִ����
    ACTUATOR_PROC *TempACT_PA_Run;//��ʻ�¶�ִ����
    ACTUATOR_PROC *DES_ACT_Run;//��ģʽִ����
    
    
}AC_Actuators;

typedef struct AC_FANS{
    FAN_PROC *front_fan_proc;
    FAN_PROC *rear_fan_proc;
}AC_FANS;//�ķ��

typedef struct AC
{
    AC_Sensors *sensors;//���ִ�����
    
    AC_Actuators *actuators;//ִ����
    AC_FANS *fans;//�ķ��
    
    //PM2.5������
    //�綯ѹ����
    //����ptc
    //ˮ��ptc
    
    
    //�������
}AC;//�յ�



#endif
