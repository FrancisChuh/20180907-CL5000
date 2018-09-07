#include "Fan.h"

extern ADC_Proc AD_12;

extern TB9102 tb9102_list[4];


Fan RearFan={
    .fan_vol = &AD_12,
    .level=0,
    .ftmn=REAR_FANPWM_FTM,
    .ch=REAR_FANPWM_CHANNEL,
    .close={.tb9102=&tb9102_list[1],.tb9102_pin=TB9102_OB2},
};

Fan FrontFan={
    .fan_vol = &AD_12,
    .level=0,
    .ftmn=FRONT_FANPWM_FTM,
    .ch=FRONT_FANPWM_CHANNEL,
    .close={.tb9102=&tb9102_list[1],.tb9102_pin=TB9102_OB1},
};

Fan *FanList[2]={&RearFan,&FrontFan};

const u8 FAN_PWM_LEVEL[9][8]={
 //9V,10V,11V,12V,13V,14V,15V,16V
    {48, 32, 28, 25, 20, 10, 1,  1 },   //PWM_LEVEL_0                            
    {56, 48, 41, 33, 26, 17, 1,  1 },   //PWM_LEVEL_1 //3.2V
    {65, 58, 51, 43, 35, 28, 20, 12},   //PWM_LEVEL_2 //4.5V
    {72, 64, 57, 49, 41, 34, 26, 19},   //PWM_LEVEL_3 //5.3V
    {81, 74, 67, 59, 52, 44, 37, 29},   //PWM_LEVEL_4 //6.6V
    {91, 83, 76, 68, 61, 54, 46, 39},   //PWM_LEVEL_5 //7.8V
    {100,100,89, 82, 75, 67, 59, 52},   //PWM_LEVEL_6 //9.5V
    {100,100,100,91, 83, 76, 68, 61},   //PWM_LEVEL_7 //10.7V
    {100,100,100,100,93 ,86, 78, 71},   //PWM_LEVEL_8 //12V
};


void tb9102_fan_close(FAN_Close *close)
{
    TB9102_OUTPUT_L(close->tb9102,close->tb9102_pin);
}

void tb9102_fan_open(FAN_Close *close)
{
    TB9102_OUTPUT_HZ(close->tb9102,close->tb9102_pin);
}



void Fan_Proc(Fan *fan)
{
    uint8_t line=0;
    uint8_t num=0;
    uint16_t vol=0;
    uint8_t  fan_pwm_level[9];
    uint8_t fan_pwm_duty=0;
    
    vol=fan->fan_vol->ADC_Res / 100;
    if(vol<90)
    {
        vol=90;
    }
    else if(vol>159)
    {
        vol=159;
    }
    line=vol/10-9;
    for(num=0;num<9;num++)
    {
        fan_pwm_level[num]=FAN_PWM_LEVEL[num][line]-(vol%10)*(FAN_PWM_LEVEL[num][line]-FAN_PWM_LEVEL[num][line+1])/10;
    }
    if(fan->level==0)
    {
        SW_FAN(SW_OFF);
        fan_pwm_duty=fan_pwm_level[0];
    }
    else if(fan->level==80)
    {
        SW_FAN(SW_ON);
        fan_pwm_duty=fan_pwm_level[8];
    }
    else
    {
        SW_FAN(SW_ON);
        num=fan->level/10;
        fan_pwm_duty=fan_pwm_level[num]+(fan->level%10)*(fan_pwm_level[num+1]-fan_pwm_level[num])/10;
    }
    FTM_PWM_Duty(fan->ftmn,fan->ch,fan_pwm_duty);//更新pwm占空比
}

void fan_update(void)
{
    uint8_t i;
    for(i=0;i<sizeof(FanList)/sizeof(Fan*);i++)
    {
        Fan_Proc((FanList)[i]);
    }
}

void fan_change_level(Fan *fan,uint8_t level)
{
    if(level==0)
    {
        tb9102_fan_close(&fan->close);
    }
    else
    {
        tb9102_fan_open(&fan->close);
    }
    fan->level=level;
}

void front_fan_change_level(uint8_t level)
{
    fan_change_level(&FrontFan,level);
}

void rear_fan_change_level(uint8_t level)
{
    fan_change_level(&RearFan,level);
}

void fan_test(uint8_t level)
{
    if(level==0)
    {
        tb9102_fan_close(&RearFan.close);
        tb9102_fan_close(&FrontFan.close);
    }
    else
    {
        tb9102_fan_open(&RearFan.close);
        tb9102_fan_open(&FrontFan.close);
    }

    FTM_PWM_Duty(RearFan.ftmn,RearFan.ch,level);
    FTM_PWM_Duty(FrontFan.ftmn,FrontFan.ch,level);
}

