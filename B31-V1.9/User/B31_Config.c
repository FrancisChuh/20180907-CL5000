#include "B31_Config.h"


/*������*/
AC_Sensors B31_Sensors={
    .TsensorOUTCAR  = &AD_TsensorOUTCAR   , //�����¶ȴ�����
    .TsensorINCAR   = &AD_TsensorINCAR    ,  //�����¶ȴ�����
    .TsensorEVA     = &AD_TsensorEVA      ,    //�������¶ȴ�����
    .TsensorFoot_CO = &AD_TsensorFoot_CO  ,//�����¶ȴ�����������ʻ
    .TsensorFace_CO = &AD_TsensorFace_CO  ,//�����¶ȴ�����������ʻ
    .TsensorFoot_PA = &AD_TsensorFoot_PA  ,//�����¶ȴ���������ʻ
    .TsensorFace_PA = &AD_TsensorFace_PA  ,//�����¶ȴ���������ʻ
    .WTsensor2      = &AD_WTsensor2       ,//���ˮ�´�����:ȷ��û���
    .WTsensor1      = &AD_WTsensor1       ,//���ˮ�´�����:ȷ��û���
    .P_TPsensor1    = &AD_P_TPsensor1     ,//��ѹѹ��������1
    //���մ�����
};

/*ִ����*/
AC_Actuators B31_Acutators={
    .Intake_Run     =&Intake_Run,       //����ѭ��
    .Mode_Run       =&Mode_Run,         //ģʽִ����
    .TempACT_CO_Run =&TempACT_CO_Run,   //����ʻ�¶�ִ����
    .TempACT_PA_Run =&TempACT_PA_Run,   //��ʻ�¶�ִ����
    .DES_ACT_Run    =&DES_ACT_Run,      //��ģʽִ����
};

/*�ķ��*/
AC_FANS B31_Fans={
    .front_fan_proc=&front_fan_change_level,
    .rear_fan_proc =&rear_fan_change_level,
};

/**/

/*�ܳ�*/
AC B31={
    .sensors=&B31_Sensors,
    .actuators=&B31_Acutators,
    .fans=&B31_Fans,
    
    //
    
    //�������
};




