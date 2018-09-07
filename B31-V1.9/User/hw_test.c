#include "hw_test.h"
#include "MOTOR_DRIVE.h"
#include "modules_switch.h"


void tb9102_test(void)  //每隔10ms量级调用一次
{
    static unsigned char i;
    if(i==0)
    {
        
        
//        MODE_ACW();
        REC_ACW();
        TempCO_ACW();
        TempPA_ACW();
        
        
        i=1;
    }
    else if (i==1)
    {
        
        
//        MODE_CW();
        REC_CW();
        TempCO_CW();
        TempPA_CW();
        
        i=2;
    }
    else if(i==2)
    {
//        Stop_Mode_Motor();
        Stop_REC_Motor();
        Stop_TempCO_Motor();
        Stop_TempPA_Motor();
        i=0;
    }
    
    Moter_Ctrl();
}

void Actuator_ModeTest(uint8_t mode)
{
    if(mode==0)
    {
        Stop_Mode_Motor();
    }
    else if(mode==1)
    {
        _5VR_On();
        
        M_EXP_On();
        M_AQS_On();
        M_PM25_On();
        M_NE_On();
        M_Valve_On();
        
        
        MODE_ACW();
    }
    else if(mode==2)
    {
        _5VR_Off();
        
        M_EXP_Off();
        M_AQS_Off();
        M_PM25_Off();
        M_NE_Off();
        M_Valve_Off();
        
        
        MODE_CW();
    }
}

void motor_process_test(int16_t TAKE,
						int16_t ModePPS,
						int16_t Tem_Purpose,
						int16_t SetFanNow
){
	SC_REC_PPS(TAKE);  //内外
	SC_MODE_PPS(ModePPS); //模式
	SC_TEMP_PPS(Tem_Purpose);  //温度风门
	Moter_Ctrl(); //执行器动作

	//SC_FANSPEED_PPS(SetFanNow);  //风量调整
//	E_Moter_Ctrl();//电子膨胀阀动作
}



