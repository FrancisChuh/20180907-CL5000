#include "Fan_Temp_Mode.h"

#include "actuator.h"


const u8 c_FAN_PWM_LEVEL[9][8]={
 //9V,10V,11V,12V,13V,14V,15V,16V
  {52, 45, 38, 31, 24, 19, 13,  2},    //PWM_LEVEL_0
  {60, 53, 46, 39, 32, 27, 21, 10},    //PWM_LEVEL_1 //3.5V
  {70, 63, 56, 48, 41, 34, 27, 20},   //PWM_LEVEL_2 //4.9V
  {81, 74, 67, 59, 51, 44, 37, 30},   //PWM_LEVEL_3 //6.3V
  {90, 83, 77, 70, 62, 55, 47, 40},   //PWM_LEVEL_4 //7.7V
  {100, 93, 86, 80, 73, 65, 58, 50},   //PWM_LEVEL_5 //9.1V
  {100,100,97, 89, 82, 76, 69, 61},   //PWM_LEVEL_6 //10.5V
  {100,100,100,100,100, 100, 90, 82},   //PWM_LEVEL_7 //13.5V
  {100,100,100,100,100,100,100,100}   //PWM_LEVEL_8
};


void SC_TEMP_PPS(int16_t SC_TEMP)
{
	switch(SC_TEMP)
	{			
		case MIN_TEMSET:
			if(s_AD_Con.V_MIX_MASTER_FB<TEMP_LO_VOL+TEMP_VOL_ERR)
			{
				Stop_TEMP_Motor();
			}
			else
			{
				#if(Tem_Mix_Err==1)
				TEMP_CW();
				#else
				TEMP_ACW();
				#endif
			}
			break;
		case MAX_TEMSET:
			if(s_AD_Con.V_MIX_MASTER_FB>TEMP_HI_VOL-TEMP_VOL_ERR)
			{
				Stop_TEMP_Motor();
			}
			else
			{
			#if(Tem_Mix_Err==1)
				TEMP_ACW();
			#else
				TEMP_CW();
			#endif
			}
			break;
		default:
			if((s_AD_Con.V_MIX_MASTER_FB>s_Heat_Cap.MIX_Vol-TEMP_VOL_ERR) && s_AD_Con.V_MIX_MASTER_FB<(s_Heat_Cap.MIX_Vol+TEMP_VOL_ERR))
			{
				Stop_TEMP_Motor();
			}
			else
			{
				if(s_AD_Con.V_MIX_MASTER_FB>s_Heat_Cap.MIX_Vol)
				{
#if(Tem_Mix_Err==1)
					TEMP_CW();
#else
					TEMP_ACW();
#endif
				}
				else
				{
#if(Tem_Mix_Err==1)
					TEMP_ACW();
#else
					TEMP_CW();
#endif
				}
			}
			break;
	}
}

extern ACTUATOR ModeACT;
void SC_MODE_PPS(u8 SC_MODE)
{
	actuator_run(&ModeACT,SC_MODE);
}

void SC_FANSPEED_PPS(u8 level)//level*10
{
  u8 num=0,line=0;
  u16 FANVOL=0;
  u8 FAN_PWM_LEVEL[9];

  FANVOL=s_AD_Con.V_VOL12V/100;  //只需精确到0.1V
  if(FANVOL<90)
  {
    FANVOL=90;
  }
  else if(FANVOL>159)
  {
    FANVOL=159;
  }
  line=FANVOL/10-9;
  
  for(num=0;num<9;num++)
  {
    FAN_PWM_LEVEL[num]=c_FAN_PWM_LEVEL[num][line]-(FANVOL%10)*(c_FAN_PWM_LEVEL[num][line]-c_FAN_PWM_LEVEL[num][line+1])/10;
  }
  if(level==0)
  {
    SW_FAN(SW_OFF);
    fanpwmduty_PPS=FAN_PWM_LEVEL[0];
  }
  else if(level>=80)
  {
    SW_FAN(SW_ON);
    fanpwmduty_PPS=FAN_PWM_LEVEL[8];
  }
  else
  {
    SW_FAN(SW_ON);
    num=level/10;
    fanpwmduty_PPS=FAN_PWM_LEVEL[num]+(level%10)*(FAN_PWM_LEVEL[num+1]-FAN_PWM_LEVEL[num])/10;
  }
  FTM_PWM_Duty(FRONT_FANPWM_FTM,FRONT_FANPWM_CHANNEL,fanpwmduty_PPS);//设置风量
}


extern ACTUATOR IntakeACT;
void SC_REC_PPS(u8 SC_REC)
{
    actuator_run(&IntakeACT,SC_REC);
}


void PWM_FAN_CHANGE(void)
{
  if(s_Heat_Cap.Set_Fan_Now<s_Heat_Cap.Set_Fan)
  {
    s_Heat_Cap.Set_Fan_Now++;
  }
  else if(s_Heat_Cap.Set_Fan_Now>s_Heat_Cap.Set_Fan)
  {
    s_Heat_Cap.Set_Fan_Now--;
  }
}

void E_MoterSTEP_CHANGE(void)//电子膨胀阀改变
{
  if(E_MoterSTEP <E_MoterSTEP_PPS)
  {
    E_Moter_CW_CCW(ENABLE);//正转
    E_MoterSTEP++;
  }
  else if(E_MoterSTEP >E_MoterSTEP_PPS)
  {
    E_Moter_CW_CCW(DISABLE);//反转
    E_MoterSTEP--;
  }
  else
  {
    E_Moter_Stop();//降低功耗
  }
}

void SC_LCDLight_PWM(u8 light)
{
//  if(light)
//  {
//    FTM_PWM_set_duty_N(PWMLCD_FTM,PWMLCD_CHANNEL,PWMLCD_default);//设置LCD背光亮
//  }
//  else
//  {
//    FTM_PWM_set_duty_N(PWMLCD_FTM,PWMLCD_CHANNEL,PWMLCD_DarkMode);//设置LCD背光暗
//  }
}


//void TWV_Process(void)
//{
//  if((s_AD_Con.V_TWVfb>(TWV_Pos-SET_VOL_ERR)) && (s_AD_Con.V_TWVfb<(TWV_Pos+SET_VOL_ERR)))
//  {
//    TWV_STOP();
//  }
//  else
//  {
//    if(s_AD_Con.V_TWVfb>TWV_Pos)
//    {
//      TWV_CW();
//    }
//    else
//    {
//      TWV_ACW();
//    }
//  }
//}

//end
