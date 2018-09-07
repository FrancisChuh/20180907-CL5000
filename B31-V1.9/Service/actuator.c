#include "actuator.h"

#define ACT_ERROR 25
#define COUNT_DOWN

extern AD_Value_Convert_TypeDef s_AD_Con;

/*                  正反转执行器                     */
const int16_t IntakeACT_ANG[2]={
    OUTTAKE_ANG,
    INTAKE_ANG,
};

ACTUATOR IntakeACT={            //前内外循环
    .CW=&REC_CW,                //关联正转函数
    .ACW=&REC_ACW,              //关联反转函数
    .STOP=&Stop_REC_Motor,      //关联停转函数
    .ANG=&AD_IntakeACTFB.DATA,     //关联位置变量
    .ANG_LEVEL=IntakeACT_ANG,   //位置数据
    .ANG_ERROR=ACT_ERROR,              //位置误差
    .ANG_LEVEL_CNT=sizeof(IntakeACT_ANG)/sizeof(int16_t),  //位置数量
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

ACTUATOR DES_ACT={          //后内外循环
    .CW=&DesACT_ACW,
    .ACW=&DesACT_CW,
    .STOP=&Stop_DesACT_Motor,
    .ANG=&AD_DesACTFB_Rear.DATA,
    .ANG_LEVEL=RearIntakeACT_ANG,
    .ANG_ERROR=600,
    .ANG_LEVEL_CNT=sizeof(RearIntakeACT_ANG)/sizeof(int16_t),  //位置数量
};

void DES_ACT_Run(uint8_t level)
{
    actuator_run(&DES_ACT,level);
}

/*                  模式执行器                       */
const int16_t ModeACT_ANG[5]={
    MODE_01,
    MODE_02,
    MODE_03,
    MODE_04,
    MODE_05,
};

ACTUATOR ModeACT={
    .CW=&MODE_CW,                //关联正转函数
    .ACW=&MODE_ACW,              //关联反转函数
    .STOP=&Stop_Mode_Motor,      //关联停转函数
    .ANG=&AD_ModeACTFB.DATA,     //关联位置变量
    .ANG_LEVEL=ModeACT_ANG,   //位置数据
    .ANG_ERROR=ACT_ERROR,              //位置误差
    .ANG_LEVEL_CNT=sizeof(ModeACT_ANG)/sizeof(int16_t),  //位置数量
};

void Mode_Run(uint8_t level)
{
    actuator_run(&ModeACT,level);
}


/*                  温度执行器                       */
const int16_t Temp_ANG[2]={
    FULL_COOL,
    FULL_WARM,
};


ACTUATOR TempACT_CO={
    .CW=&TempCO_CW,                //关联正转函数
    .ACW=&TempCO_ACW,              //关联反转函数
    .STOP=&Stop_TempCO_Motor,      //关联停转函数
    .ANG=&AD_TempACTFB_CO.DATA,     //关联位置变量
    .ANG_LEVEL=Temp_ANG,   //位置数据
    .ANG_ERROR=ACT_ERROR,              //位置误差
    .ANG_LEVEL_CNT=sizeof(Temp_ANG)/sizeof(int16_t),  //位置数量
};


void TempACT_CO_Run(uint8_t level)
{
    actuator_run(&TempACT_CO,level);
}

ACTUATOR TempACT_PA={
    .CW=&TempPA_CW,                //关联正转函数
    .ACW=&TempPA_ACW,              //关联反转函数
    .STOP=&Stop_TempPA_Motor,      //关联停转函数
    .ANG=&AD_TempACTFB_PA.DATA,     //关联位置变量
    .ANG_LEVEL=Temp_ANG,   //位置数据
    .ANG_ERROR=ACT_ERROR,              //位置误差
    .ANG_LEVEL_CNT=sizeof(Temp_ANG)/sizeof(int16_t),  //位置数量
};

void TempACT_PA_Run(uint8_t level)
{
    actuator_run(&TempACT_PA,level);
}

/*                 执行器运行函数                  */
void actuator_run(ACTUATOR *actuator,uint8_t Level)
{
    if(actuator->count_down==0)
    {
        actuator->STOP();//停止
    }
    else
    {
        actuator->count_down--;
        if(Level<actuator->ANG_LEVEL_CNT)
        {
            if(*actuator->ANG>actuator->ANG_LEVEL[Level])    //当前角度比当前需要位置大
            {
                if( ( (*actuator->ANG) >(actuator->ANG_LEVEL[Level]-actuator->ANG_ERROR) ) 
                    && (*actuator->ANG<(actuator->ANG_LEVEL[Level]+actuator->ANG_ERROR)) )  //不在误差范围内
                {
                    actuator->STOP();//停止
                }
                else
                {
                    actuator->CW();//反转
                }
            }
            else
            {           //当前位置比需要位置小
                if( (*actuator->ANG) > (actuator->ANG_LEVEL[Level] - actuator->ANG_ERROR)
                    && (*actuator->ANG) < (actuator->ANG_LEVEL[Level] + actuator->ANG_ERROR) )  //不在误差范围内
                {
                    actuator->STOP();//停止
                }
                else
                {
                    actuator->ACW();//正转
                    
                }
            }
        }
    }
}



