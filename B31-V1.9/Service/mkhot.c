#include "mkhot.h"

//u16 PTC_Batt_ON_flag;             //读取电池功率标志位  用于模拟BMS输入
//u16 PTC_battery_power_Req = 2000; //电池需求的PTC功率  用于模拟BMS输入
//int8_t PTC_temperature = 0;        //PTC的出水温度  用于模拟从CAN接收到的PTC出水温度
u16 PTC_battery_power_Temp;
//u8 Batt_State = 0;                //读取电池充放电状态   0：行车放电   1：慢充    2：快充

u16 PTC_power;                    //设置PTC功率
u16 PTC_cabin_power_Req;          //乘员舱需求的PTC功率
u16 PTC_cabin_temperature_Req;    //乘员舱需求的温度
u16 PTC_cabin_power_O;            //乘员舱需求的PTC功率  用于输出给VCU

u8 Pumb_Start_flag = 3;           //用于提前开启水泵
u8 Pumb_Stop_flag = 0;            //用于延后关闭水泵

u16 TWV_Pos = 2500;               //三通阀上电初始位置

static u8 PUMPPWM_Duty = PUMP_STOP_DUTY;     //上电初始状态水泵关闭

const int16_t PTC_power_table[12][2]={
  { 5,0   },
  { 4,150 },
  { 3,400 },
  { 2,800 },
  { 1,1300},
  { 0,2000},
  {-1,2700},
  {-2,3600},
  {-3,4800},
  {-4,6000},
  {-5,6900},
  {-6,7000}
};

const int16_t T_PTC_table[9][2]={
  { 10,330 },
  {  0,350 },
  {-10,400 },
  {-20,470 },
  {-30,580 },
  {-40,690 },
  {-50,800 },
  {-60,850 },
  {-70,860 }
};

const float_t TWV_Pos_table[27][2]={
  { 5.72,1600},
  { 4.65,1700},
  { 3.76,1800},
  { 2.99,1900},
  { 2.45,2000},
  { 2.06,2100},
  { 1.78,2200},
  { 1.58,2300},
  { 1.44,2400},
  { 1.34,2500},
  { 1.23,2600},
  { 1.13,2700},
  { 1.01,2800},
  { 0.90,2900},
  { 0.78,3000},
  { 0.65,3100},
  { 0.53,3200},
  { 0.42,3300},
  { 0.33,3400},
  { 0.28,3500},
  { 0.23,3600},
  { 0.18,3700},
  { 0.17,3800},
  { 0.14,3900},
  { 0.12,4000},
  { 0.10,4100},
  { 0.09,4200}
};

void PTC_Mode_Control(void)
{
  if(g_AUTO_Flag & AUTO_PTC_MASK)
  {
    if(s_Heat_Cap.Tem_err_S < -10)       //当前需要制热
    {
      if(s_Heat_Cap.TAKE==REC_OUTTake)  //当前循环为外循环
      {
        #if(Hi_Eff==1)
        if(s_Heat_Cap.Tem_Out_In_err>100)  //车外比车内高10度以上
        {
         s_Heat_Cap.PTC_IN_STATUS = 0;      //不需要开PTC
        }
        else if(s_Heat_Cap.Tem_Out_In_err<80)   //车外比车内高8度以内
        {
         s_Heat_Cap.PTC_IN_STATUS= 1;      //需要开PTC
        }
        #else
        s_Heat_Cap.PTC_IN_STATUS= 1;
        #endif
      }
      else
      {
        s_Heat_Cap.PTC_IN_STATUS=1;
      }
    }
    else if(s_Heat_Cap.Tem_err_S > 10)
    {
      s_Heat_Cap.PTC_IN_STATUS=0;
    }
    if(s_Heat_Cap.Tem_Purpose==MIN_TEMSET)
    {
      s_Heat_Cap.PTC_IN_STATUS=0;
    }
  }
  
  if(CAN_RX_Info.BMSRequest.BMSWPTCPwrReq)
  {
    s_Heat_Cap.PTC_BAT_STATUS=1;
  }
  else
  {
    s_Heat_Cap.PTC_BAT_STATUS=0;
  }
//	if((g_Diog_Flag & VOL12V_OVERVOL_MASK)||(g_Diog_Flag & VOL12V_UNDERVOL_MASK))
//	{
//		s_Heat_Cap.PTC_BAT_STATUS = 0;
//		s_Heat_Cap.PTC_IN_STATUS = 0;	
//	}
  if(s_Heat_Cap.PTC_IN_STATUS && s_Heat_Cap.PTC_BAT_STATUS)
  {
    Both_Mode();
  }
  else if(s_Heat_Cap.PTC_IN_STATUS && (!s_Heat_Cap.PTC_BAT_STATUS))
  {
    Cabin_Mode();
  }
  else if((!s_Heat_Cap.PTC_IN_STATUS) && s_Heat_Cap.PTC_BAT_STATUS)
  {
    Battery_Mode();
  }
  else 
  {
    PTC_Stop_Mode();
  }
	if(s_Heat_Cap.PTC_IN_STATUS == 0)
	{
		PTC_cabin_power_O = 0;
	}
}

void PTC_Stop_Mode(void)
{
  PTC_power = 0;
  if(Pumb_Stop_flag == 0)
  {
    PUMPPWM_Duty=PUMP_STOP_DUTY;          //关闭水泵
		Pumb_Stop_flag = 0;
  }
  Pumb_Start_flag=3;
}

void Battery_Mode(void)
{
  TWV_Pos = SET_TO_BATTERY;
	if(g_Diog_Flag & MOTOR_TWV_ERR_MASK)
	{
//	用于停止水泵
//		s_Heat_Cap.PTC_IN_STATUS = 0;
//		s_Heat_Cap.PTC_BAT_STATUS = 0;
	}
	PUMPPWM_Duty=PUMP_FULL_DUTY;
//  if(Pumb_Start_flag == 0)
//  {
//    PTC_power = PTC_battery_power_Req;
//  }
  Pumb_Stop_flag=20;
}


void Cabin_Mode(void)
{ 
  TWV_Pos = SET_TO_CABIN;
	if(g_Diog_Flag & MOTOR_TWV_ERR_MASK)
	{
//	用于停止水泵
//		s_Heat_Cap.PTC_IN_STATUS = 0;
//		s_Heat_Cap.PTC_BAT_STATUS = 0;
	}
	PUMPPWM_Duty=PUMP_FULL_DUTY;
  if(Pumb_Start_flag == 0)
  {
    if(s_Heat_Cap.Tem_Purpose == MAX_TEMSET)
    {
      PTC_cabin_power_Req = PTC_POWER_MAX;
      PTC_power = PTC_cabin_power_Req;
      PTC_cabin_power_O = PTC_cabin_power_Req;			
    }
    else
    {
      PTC_cabin_temperature_Req = PTC_Temperature_FIND();
      PTC_cabin_power_Req = PTC_POWER_FIND(PTC_cabin_temperature_Req);
      PTC_power = PTC_cabin_power_Req;
      PTC_cabin_power_O = PTC_cabin_power_Req;
    }
  }
  Pumb_Stop_flag=20;
}

void Both_Mode(void)
{
  float_t twv_cabin_battery;
  if(g_Diog_Flag & MOTOR_TWV_ERR_MASK)
	{
//	用于停止水泵
//		s_Heat_Cap.PTC_IN_STATUS = 0;
//		s_Heat_Cap.PTC_BAT_STATUS = 0;
	}
	PUMPPWM_Duty=PUMP_FULL_DUTY;
  if(Pumb_Start_flag==0)
  {
    switch(CAN_RX_Info.BMSRequest.HVBatThrmlMdReq)
    {
      case Discharge_PTC_Heatings ://行车放电
      {
        PTC_battery_power_Temp = CAN_RX_Info.BMSRequest.BMSWPTCPwrReq;
        if(s_Heat_Cap.Tem_Purpose == MAX_TEMSET)
        {
          TWV_Pos = SET_TO_CABIN;
          PTC_cabin_power_Req = PTC_POWER_MAX;
          PTC_power = PTC_cabin_power_Req;
          PTC_cabin_power_O = PTC_cabin_power_Req;
          PTC_battery_power_Temp = 0;
        }
        else
        {
          PTC_cabin_temperature_Req = PTC_Temperature_FIND();
          PTC_cabin_power_Req = PTC_POWER_FIND(PTC_cabin_temperature_Req);
          PTC_cabin_power_O = PTC_cabin_power_Req;
          if(PTC_cabin_power_Req == PTC_POWER_MAX)
          {
            TWV_Pos = SET_TO_CABIN;
            PTC_cabin_power_Req = PTC_POWER_MAX;
            PTC_power = PTC_cabin_power_Req;
          }
          else
          {
            PTC_power = PTC_cabin_power_Req + PTC_battery_power_Temp;
            if(PTC_power > PTC_POWER_MAX)
            {
              PTC_power = PTC_POWER_MAX;
              PTC_battery_power_Temp = PTC_power - PTC_cabin_power_Req;
            }
            twv_cabin_battery = (float_t)PTC_cabin_power_Req / PTC_battery_power_Temp;
            TWV_Pos = TWV_Pos_FIND(twv_cabin_battery);
          }
        }
        break;
      }
      case SC_PTC_Heating://慢充
      {
          PTC_battery_power_Temp = CAN_RX_Info.BMSRequest.BMSWPTCPwrReq;
          if(s_Heat_Cap.Tem_Purpose == MAX_TEMSET)
          {
            PTC_cabin_power_Req = PTC_POWER_MAX;
            PTC_cabin_power_O = PTC_cabin_power_Req;
            PTC_battery_power_Temp = 0;
          }
          else
          {
            PTC_cabin_temperature_Req = PTC_Temperature_FIND();
            PTC_cabin_power_Req = PTC_POWER_FIND(PTC_cabin_temperature_Req);
            PTC_cabin_power_O = PTC_cabin_power_Req;
          }
          if(CAN_RX_Info.BMSRequest.BMSWPTCPwrReq > PTC_POWER_MAX)
          {
            TWV_Pos = SET_TO_BATTERY;
            PTC_power = PTC_POWER_MAX;
          }
          else
          {
            PTC_power = PTC_cabin_power_Req + PTC_battery_power_Temp;
              
            if(PTC_power > PTC_POWER_MAX)
            {
              PTC_power = PTC_POWER_MAX;
              PTC_cabin_power_Req = PTC_power - PTC_battery_power_Temp;
            }
            twv_cabin_battery = (float_t)PTC_cabin_power_Req / PTC_battery_power_Temp;
            TWV_Pos = TWV_Pos_FIND(twv_cabin_battery);
          }
        break;          
      }
      case Default://默认=慢充
      {
          PTC_battery_power_Temp = CAN_RX_Info.BMSRequest.BMSWPTCPwrReq;
          if(s_Heat_Cap.Tem_Purpose == MAX_TEMSET)
          {
            PTC_cabin_power_Req = PTC_POWER_MAX;
            PTC_cabin_power_O = PTC_cabin_power_Req;
            PTC_battery_power_Temp = 0;
          }
          else
          {
            PTC_cabin_temperature_Req = PTC_Temperature_FIND();
            PTC_cabin_power_Req = PTC_POWER_FIND(PTC_cabin_temperature_Req);
            PTC_cabin_power_O = PTC_cabin_power_Req;
          }
          if(CAN_RX_Info.BMSRequest.BMSWPTCPwrReq > PTC_POWER_MAX)
          {
            TWV_Pos = SET_TO_BATTERY;
            PTC_power = PTC_POWER_MAX;
          }
          else
          {
            PTC_power = PTC_cabin_power_Req + PTC_battery_power_Temp;
              
            if(PTC_power > PTC_POWER_MAX)
            {
              PTC_power = PTC_POWER_MAX;
              PTC_cabin_power_Req = PTC_power - PTC_battery_power_Temp;
            }
            twv_cabin_battery = (float_t)PTC_cabin_power_Req / PTC_battery_power_Temp;
            TWV_Pos = TWV_Pos_FIND(twv_cabin_battery);
          }
        break;          
      }
      case FC_PTC_Heating://快充
      {
        PTC_battery_power_Temp = CAN_RX_Info.BMSRequest.BMSWPTCPwrReq;
        PTC_cabin_temperature_Req = PTC_Temperature_FIND();
        PTC_cabin_power_Req = PTC_POWER_FIND(PTC_cabin_temperature_Req);
        PTC_cabin_power_O = PTC_cabin_power_Req;
        
        PTC_power = PTC_cabin_power_Req + PTC_battery_power_Temp;
        if(PTC_power > PTC_POWER_MAX)
        {
          PTC_power = PTC_POWER_MAX;
          if(PTC_battery_power_Temp > 2800)
          {
            PTC_battery_power_Temp = 2800;
          }
          PTC_cabin_power_Req = PTC_power - PTC_battery_power_Temp;
        }
        twv_cabin_battery = (float_t)PTC_cabin_power_Req / PTC_battery_power_Temp;
        TWV_Pos = TWV_Pos_FIND(twv_cabin_battery);
        break;
      }
      default:
        break;        
    }
  }
  Pumb_Stop_flag=20;
}

void Pump_Process(void)
{
  FTM_PWM_set_duty_N(PUMPPWM_FTM,PUMPPWM_CHANNEL,PUMPPWM_Duty);
}

u16 PTC_POWER_FIND(u16 T_PTC_set)
{
  u8 num=0;
  int16_t err_t;
	T_PTC_set = T_PTC_set/10;
  err_t = CAN_RX_Info.WPTCOtltTem - T_PTC_set;
  if(CAN_RX_Info.WPTCOtltTem < (T_PTC_set - T_OFFSET))
  {
    return PTC_POWER_MAX;
  }
  else if(CAN_RX_Info.WPTCOtltTem > (T_PTC_set + T_OFFSET))
  {
    return 0;
  }
  else
  {
    num=1;
    while(err_t < PTC_power_table[num][0])
    {
      num++;
    }
    return (PTC_power_table[num][1]-PTC_power_table[num-1][1])*(err_t - PTC_power_table[num-1][0]) / (PTC_power_table[num][0] - PTC_power_table[num-1][0]) + PTC_power_table[num-1][1]; 
  }
}

u16 TWV_Pos_FIND(float_t twv_cabin_battery_t)
{
  u8 num=0;

  if(twv_cabin_battery_t > TWV_Pos_table[0][0])
  {
    return TWV_Pos_table[0][1];
  }
  else if(twv_cabin_battery_t < TWV_Pos_table[26][0])
  {
    return TWV_Pos_table[26][1];
  }
  num=1;
  while(twv_cabin_battery_t < TWV_Pos_table[num][0])
  {
    num++;
  }
  return (TWV_Pos_table[num][1]-TWV_Pos_table[num-1][1])*(twv_cabin_battery_t - TWV_Pos_table[num-1][0]) / (TWV_Pos_table[num][0] - TWV_Pos_table[num-1][0]) + TWV_Pos_table[num-1][1];
}


u16 PTC_Temperature_FIND(void)
{
  u8 num=0;

  if(s_Heat_Cap.Tem_err_S>T_PTC_table[0][0])
  {
    return T_PTC_table[0][1];
  }
  else if(s_Heat_Cap.Tem_err_S < T_PTC_table[8][0])
  {
    return T_PTC_table[8][1];
  }
  num=1;
  while(s_Heat_Cap.Tem_err_S<T_PTC_table[num][0])
  {
    num++;
  }
  return (T_PTC_table[num][1]-T_PTC_table[num-1][1])*(s_Heat_Cap.Tem_err_S-T_PTC_table[num-1][0])/(T_PTC_table[num][0]-T_PTC_table[num-1][0])+T_PTC_table[num-1][1];
}
