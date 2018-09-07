#include "actuator.h"

#define ACT_ERROR 25
#define COUNT_DOWN

extern AD_Value_Convert_TypeDef s_AD_Con;

/*                  ����תִ����                     */
const int16_t IntakeACT_ANG[2]={
    OUTTAKE_ANG,
    INTAKE_ANG,
};

ACTUATOR IntakeACT={            //ǰ����ѭ��
    .CW=&REC_CW,                //������ת����
    .ACW=&REC_ACW,              //������ת����
    .STOP=&Stop_REC_Motor,      //����ͣת����
    .ANG=&AD_IntakeACTFB.DATA,     //����λ�ñ���
    .ANG_LEVEL=IntakeACT_ANG,   //λ������
    .ANG_ERROR=ACT_ERROR,              //λ�����
    .ANG_LEVEL_CNT=sizeof(IntakeACT_ANG)/sizeof(int16_t),  //λ������
    .count_down=0,
};

void Intake_Run(uint8_t level)
{
    actuator_run(&IntakeACT,level);
}


const int16_t RearIntakeACT_ANG[2]={
    REAR_INTAKE_ANG,
    REAR_OUTTAKE_ANG,
};

ACTUATOR DES_ACT={          //������ѭ��
    .CW=&DesACT_ACW,
    .ACW=&DesACT_CW,
    .STOP=&Stop_DesACT_Motor,
    .ANG=&AD_DesACTFB_Rear.DATA,
    .ANG_LEVEL=RearIntakeACT_ANG,
    .ANG_ERROR=600,
    .ANG_LEVEL_CNT=sizeof(RearIntakeACT_ANG)/sizeof(int16_t),  //λ������
};

void DES_ACT_Run(uint8_t level)
{
    actuator_run(&DES_ACT,level);
}

/*                  ģʽִ����                       */
const int16_t ModeACT_ANG[5]={
    MODE_01,
    MODE_02,
    MODE_03,
    MODE_04,
    MODE_05,
};

ACTUATOR ModeACT={
    .CW=&MODE_CW,                //������ת����
    .ACW=&MODE_ACW,              //������ת����
    .STOP=&Stop_Mode_Motor,      //����ͣת����
    .ANG=&AD_ModeACTFB.DATA,     //����λ�ñ���
    .ANG_LEVEL=ModeACT_ANG,   //λ������
    .ANG_ERROR=ACT_ERROR,              //λ�����
    .ANG_LEVEL_CNT=sizeof(ModeACT_ANG)/sizeof(int16_t),  //λ������
};

void Mode_Run(uint8_t level)
{
    actuator_run(&ModeACT,level);
}


/*                  �¶�ִ����                       */
const int16_t Temp_ANG[2]={
    FULL_COOL,
    FULL_WARM,
};


ACTUATOR TempACT_CO={
    .CW=&TempCO_CW,                //������ת����
    .ACW=&TempCO_ACW,              //������ת����
    .STOP=&Stop_TempCO_Motor,      //����ͣת����
    .ANG=&AD_TempACTFB_CO.DATA,     //����λ�ñ���
    .ANG_LEVEL=Temp_ANG,   //λ������
    .ANG_ERROR=ACT_ERROR,              //λ�����
    .ANG_LEVEL_CNT=sizeof(Temp_ANG)/sizeof(int16_t),  //λ������
};


void TempACT_CO_Run(uint8_t level)
{
    actuator_run(&TempACT_CO,level);
}

ACTUATOR TempACT_PA={
    .CW=&TempPA_CW,                //������ת����
    .ACW=&TempPA_ACW,              //������ת����
    .STOP=&Stop_TempPA_Motor,      //����ͣת����
    .ANG=&AD_TempACTFB_PA.DATA,     //����λ�ñ���
    .ANG_LEVEL=Temp_ANG,   //λ������
    .ANG_ERROR=ACT_ERROR,              //λ�����
    .ANG_LEVEL_CNT=sizeof(Temp_ANG)/sizeof(int16_t),  //λ������
};

void TempACT_PA_Run(uint8_t level)
{
    actuator_run(&TempACT_PA,level);
}

/*                 ִ�������к���                  */
void actuator_run(ACTUATOR *actuator,uint8_t Level)
{
    if(actuator->count_down==0)
    {
        actuator->STOP();//ֹͣ
    }
    else
    {
        actuator->count_down--;
        if(Level<actuator->ANG_LEVEL_CNT)
        {
            if(*actuator->ANG>actuator->ANG_LEVEL[Level])    //��ǰ�Ƕȱȵ�ǰ��Ҫλ�ô�
            {
                if( ( (*actuator->ANG) >(actuator->ANG_LEVEL[Level]-actuator->ANG_ERROR) ) 
                    && (*actuator->ANG<(actuator->ANG_LEVEL[Level]+actuator->ANG_ERROR)) )  //������Χ��
                {
                    actuator->STOP();//ֹͣ
                }
                else
                {
                    actuator->CW();//��ת
                }
            }
            else
            {           //��ǰλ�ñ���Ҫλ��С
                if( (*actuator->ANG) > (actuator->ANG_LEVEL[Level] - actuator->ANG_ERROR)
                    && (*actuator->ANG) < (actuator->ANG_LEVEL[Level] + actuator->ANG_ERROR) )  //������Χ��
                {
                    actuator->STOP();//ֹͣ
                }
                else
                {
                    actuator->ACW();//��ת
                    
                }
            }
        }
    }
}



