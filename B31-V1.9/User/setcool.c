#include "setcool.h"

FUNCTION_SELECT MODE_judge;

u8 E_Moter_ControlFLAG=0;//调用PID控过热度标志位
u16 MAX_MOTOR_SPEED = 6000;
u16 MIN_MOTOR_SPEED = 2000;
int16_t s_AD_TM_TEVA = 0;//初始化蒸发器目标温度

u8 ACFAN_PWM_DUTY=0;
static u8 ACFAN_OFF_Count;


//uc16 ACFAN_RPM_TABLE[13][2]={//查表计算压缩机转速
//  {1230,64},
//	{1430,83},
//	{1490,89},
//};

sc16 c_CCM_RPM[13][2]={//查表计算压缩机转速
  {-40,2000},
	{-30,2000},
	{-20,2000},
	{-10,2000},
  {0	,2000},
  {10	,2000},
  {20	,2300},
  {30	,2850},
  {40	,4100},
  {50	,5000},
  {60	,5550},
  {70	,5900},
  {80	,6000}
};

sc8  EVA_TEM[10][2]={ //蒸发器目标温度
  {-10,105},
  {0,  102},
  {10, 92 },
  {20, 77 },
  {30, 60 },
  {40, 35 },
  {50, 18 },
  {60, 8 },
  {70, 2 },
  {80, 0 } 
};

float CHILLER_Power[10]={//EXV开度
	646.5  ,//40
	1418.5 ,//60
  1771.1 ,//80
	2084.8 ,//100
	2476.4 ,//120
	2852.2 ,//140
	3241.6 ,//160
	3517.9 ,
	3752.9 ,
	4154.1
};

void Refrige(void)
{
	E_Moter_ControlFLAG = 0;
  
	if(E_MoterFLAG)  //EXV初始化完毕
	{
		if(g_AUTO_Flag & AUTO_AC_MASK)        //自动模式
		{
			if(s_Heat_Cap.Tem_err_S>10)         //需要制冷
			{
				 if(s_Heat_Cap.TAKE==REC_OUTTake)//当前为外循环
         {
					 #if(Hi_Eff==1)
					 if(s_Heat_Cap.Tem_Out_In_err<-100)  //车外温度比车内温度低10℃以上，不需开启乘员舱制冷 
					 {
						 s_Heat_Cap.AC_IN_STATUS = 0;
					 }
					 else if(s_Heat_Cap.Tem_Out_In_err>-80)//车外温度比车内温度低8℃以内，需要开启乘员舱制冷
					 {
						 s_Heat_Cap.AC_IN_STATUS= 1;
					 }
					 #else
           s_Heat_Cap.AC_IN_STATUS= 1;
           #endif
         }
				 else
				 {
					 s_Heat_Cap.AC_IN_STATUS = 1;
				 }
			}
			else if(s_Heat_Cap.Tem_err_S < -10)//车内温度比设定温度低，不开制冷(偏差1℃)
			{
				s_Heat_Cap.AC_IN_STATUS = 0;
			}
			if(s_Heat_Cap.Tem_Purpose==MAX_TEMSET)
			{
				s_Heat_Cap.AC_IN_STATUS=0;
			}
		}
		if(CAN_RX_Info.BMSRequest.ComprSpdReq)//电池制冷
		{
			s_Heat_Cap.AC_BAT_STATUS = 1;
		}
		else
		{
			s_Heat_Cap.AC_BAT_STATUS = 0;
		}
//		if((g_Diog_Flag & VOL12V_OVERVOL_MASK)||(g_Diog_Flag & VOL12V_UNDERVOL_MASK))
//		{
//			s_Heat_Cap.AC_IN_STATUS = 0;
//			s_Heat_Cap.AC_BAT_STATUS = 0;	
//		}
		if(s_Heat_Cap.AC_IN_STATUS && s_Heat_Cap.AC_BAT_STATUS)//双蒸模式
		{
			DoubleCoolMode();
		}
		else if(s_Heat_Cap.AC_IN_STATUS && (!s_Heat_Cap.AC_BAT_STATUS))//乘员舱单冷
		{
			IncarCoolMode();
		}
		else if((!s_Heat_Cap.AC_IN_STATUS) && s_Heat_Cap.AC_BAT_STATUS)//电池单冷
		{
			BatteryCoolMode();
		}
		else
		{
			AC_Stop_Mode();//不制冷时，停止压缩机
		}

		if(s_Heat_Cap.AC_IN_STATUS ==0) //乘员舱不制冷，
		{
			MODE_judge.MotorSpeed = 0;
		}
		
		//限定EXV开度范围和压缩机转速范围
    if((E_MoterSTEP_PPS<E_MoterSTEP_Min)&&(E_MoterSTEP_PPS!=0))
    {
      E_MoterSTEP_PPS=E_MoterSTEP_Min;
    }
    else if(E_MoterSTEP_PPS>E_MoterSTEP_Max)
    {
      E_MoterSTEP_PPS=E_MoterSTEP_Max;
    }
    
    if(MODE_judge.MotorSpeed > MAX_MOTOR_SPEED)
    {
      MODE_judge.MotorSpeed=MAX_MOTOR_SPEED;
    }
    else if((MODE_judge.MotorSpeed < MIN_MOTOR_SPEED)&&(MODE_judge.MotorSpeed!=0))
    {
      MODE_judge.MotorSpeed=MIN_MOTOR_SPEED;
    }
	}
  else
  {
    AC_Stop_Mode();//EXV初始化完毕前，停止压缩机
  }
}

void AC_Stop_Mode(void)
{
	MODE_judge.MotorSpeed =	0;
  s_Heat_Cap.ESV_STATUS = 0;
	E_MoterSTEP_PPS = 0;
}

void IncarCoolMode(void)//乘员舱单冷模式控制
{		
  s_Heat_Cap.ESV_STATUS=0;    //0代表导通
  E_MoterSTEP_PPS=0;					//EXV关闭
	MODE_judge.MotorSpeed = TXV_POWER();//计算乘员舱工作的压缩机转速
}

void BatteryCoolMode(void)//电池单冷模式控制
{
  if(s_Heat_Cap.ESV_STATUS==0)//截止阀导通
  {
    if(E_MoterSTEP>=E_MoterSTEP_Min)
    {
      s_Heat_Cap.ESV_STATUS=1;    //1代表截止
    }
    else
    {
      E_MoterSTEP_PPS=E_MoterSTEP_Min;
      if(E_MoterSTEP>=E_MoterSTEP_Min)
      {
        s_Heat_Cap.ESV_STATUS=1;    //1代表截止
      }
    }
  }
  else
  {
		E_Moter_ControlFLAG=1;//电子膨胀阀PID控过热度	 
  }
}

void DoubleCoolMode(void)//双蒸模式函数
{
	s_Heat_Cap.ESV_STATUS=0;    //0代表导通
	if(E_MoterSTEP_PPS>=E_MoterSTEP_Min)
	{
		ActualSH=CalcuSH(s_AD_Con.P_PRESSLOW,(float)s_AD_Con.T_TPRESSLOW/10);
		if(ActualSH < 3)
		{
			E_MoterSTEP_PPS -= 10;//EXV关10步
			MODE_judge.MotorSpeed = TXV_POWER();//计算乘员舱工作的压缩机转速
		}
		else
		{
			MODE_judge.AC_power = CAN_RX_Info.BMSRequest.ComprSpdReq + MODE_judge.MotorSpeed;
			
			if(CAN_RX_Info.BMSRequest.HVBatThrmlMdReq == SC_Chiller_Cooling)//电池慢充
			{
				SlowChargeRequire();
			}
			else if(CAN_RX_Info.BMSRequest.HVBatThrmlMdReq == FC_Chiller_Cooling)//电池快充
			{
				FastChargeRequire();
			}
			else if(CAN_RX_Info.BMSRequest.HVBatThrmlMdReq == Discharge_Chiller_Cooling)//电池正常行车放电
			{
				NormalDrive();
			}
			else
			{
				SlowChargeRequire();
			}
		}
	}
	else
	{
		E_MoterSTEP_PPS=E_MoterSTEP_Min;//EXV调整为初始开度
	}
}
	
void SlowChargeRequire(void)//电池慢充情况处理
{
	if(MODE_judge.AC_power > MAX_MOTOR_SPEED)//总功率大于AC最大功率
	{
		if(CAN_RX_Info.BMSRequest.ComprSpdReq > MAX_MOTOR_SPEED)//电池需求功率大于最大功率
		{
			MODE_judge.AC_BAT_power = MAX_AC_POWER;//电池制冷功率为最大
		}
		else//电池需求功率不大于最大功率时，计算EXV开度
		{
			MODE_judge.AC_BAT_power = CAN_RX_Info.BMSRequest.ComprSpdReq;
		}
		E_MoterSTEP_PPS = Power_to_Step();
	}
	else//总功率小于AC最大功率时，计算EXV开度
	{
		MODE_judge.AC_BAT_power = CAN_RX_Info.BMSRequest.ComprSpdReq;
		E_MoterSTEP_PPS = Power_to_Step();
	}
	MODE_judge.MotorSpeed=TXV_POWER();//计算乘员舱需求转速
}

void FastChargeRequire(void)//电池快充情况处理
{
	if(MODE_judge.AC_power > MAX_MOTOR_SPEED)//总功率大于最大功率
	{
		if(CAN_RX_Info.BMSRequest.ComprSpdReq < 3300)//电池需求功率小于3.3KW
		{
			MODE_judge.AC_BAT_power = CAN_RX_Info.BMSRequest.ComprSpdReq;
		}
		else
		{
			MODE_judge.AC_BAT_power = 3300;//保证电池需求功率为3.3KW，计算EXV开度
		}
		E_MoterSTEP_PPS = Power_to_Step();
	}
	else
	{
		MODE_judge.AC_BAT_power = CAN_RX_Info.BMSRequest.ComprSpdReq;//保证电池需求功率为3.3KW，计算EXV开度
		E_MoterSTEP_PPS = Power_to_Step();
	}
	MODE_judge.MotorSpeed=TXV_POWER();//计算乘员舱需求转速
}	

void NormalDrive(void)//电池正常行车放电情况处理
{
	if(MODE_judge.AC_power > MAX_MOTOR_SPEED)//总功率大于最大功率
	{
		if(CAN_RX_Info.BMSRequest.ComprSpdReq < 1000)//电池需求功率小于1KW时，增加EXV开度
		{
			MODE_judge.AC_BAT_power = CAN_RX_Info.BMSRequest.ComprSpdReq;
		} 
		else
		{
			MODE_judge.AC_BAT_power = 1000;//保证电池需求功率为1KW，计算EXV开度
		}
		E_MoterSTEP_PPS = Power_to_Step();
	}
	else
	{
		MODE_judge.AC_BAT_power = CAN_RX_Info.BMSRequest.ComprSpdReq;
		E_MoterSTEP_PPS = Power_to_Step();
	}
	MODE_judge.MotorSpeed=TXV_POWER();//计算乘员舱需求转速	
}

uint16_t TXV_POWER(void) //计算压缩机转速
{
  static u8 EAV_OFF_Flag=0;//蒸发器温度低于0℃时置1
	uint16_t output;
  
  
	s_AD_TM_TEVA = Exa_Temper();      //查表算出蒸发器目标温度s_AD_TM_TEVA
	MODE_judge.Temp_TEVA = s_AD_Con.T_TEVA - s_AD_TM_TEVA;      
	output = FindListSpeed();         //查表得出压缩机转速
  if(s_AD_Con.T_TEVA<0)
  {
    EAV_OFF_Flag=1;
  }
  else if(s_AD_Con.T_TEVA>10)
  {
    EAV_OFF_Flag=0;
  }
  if(EAV_OFF_Flag) 
  {
    output=0;
  }
  if(s_AD_Con.T_TEVA>800)//温度大于80℃，认为传感器短路，停止压缩机
  {
    output=0;
  }
  if(output>2000)
  {
    if(MODE_judge.MotorSpeed<2000)
    {
      output=2000;
    }
    else if(output-MODE_judge.MotorSpeed>40)
    {
      output=MODE_judge.MotorSpeed+40;
    }
  }

	return output;
}

uint16_t FindListSpeed(void)//根据温差查表得出压缩机转速
{
  u8 num=0;
  uint16_t output;
  
  if(MODE_judge.Temp_TEVA<c_CCM_RPM[0][0])
  {
    output = c_CCM_RPM[0][1];
  }
  else if(MODE_judge.Temp_TEVA>c_CCM_RPM[12][0])
  {
    output = c_CCM_RPM[12][1];
  }
  else
  {
    num=1;
    while(MODE_judge.Temp_TEVA>c_CCM_RPM[num][0])
    {
      num++;
    }
    output = (c_CCM_RPM[num][1]-c_CCM_RPM[num-1][1])*(MODE_judge.Temp_TEVA-c_CCM_RPM[num-1][0])/(c_CCM_RPM[num][0]-c_CCM_RPM[num-1][0])+c_CCM_RPM[num-1][1];
  }
  return output;
}

uint16_t Exa_Temper(void)
{
	u8 num=0;
	uint16_t output;
	
	if(s_Heat_Cap.Tem_err_S<EVA_TEM[0][0])
  {
    output = EVA_TEM[0][1];
  }
	else if(s_Heat_Cap.Tem_err_S>EVA_TEM[9][0])
  {
    output = EVA_TEM[9][1];
  }
	else
	{
		num=1;
		while(s_Heat_Cap.Tem_err_S>EVA_TEM[num][0])
		{
			num++;
		}
		output = (EVA_TEM[num][1]-EVA_TEM[num-1][1])*(s_Heat_Cap.Tem_err_S-EVA_TEM[num-1][0])/(EVA_TEM[num][0]-EVA_TEM[num-1][0])+EVA_TEM[num-1][1];
	}
	return output;
}

uint16_t Power_to_Step(void)
{
	u8 num=0;
	uint16_t output;
	
	if(MODE_judge.AC_BAT_power<CHILLER_Power[0])
  {
    output = 40;
  }
	else if(MODE_judge.AC_BAT_power>CHILLER_Power[9])
  {
    output = 220;
  }
	else
	{
		num=1;
		while(MODE_judge.AC_BAT_power>CHILLER_Power[num])
		{
			num++;
		}
		output = 20*(MODE_judge.AC_BAT_power-CHILLER_Power[num-1])/(CHILLER_Power[num]-CHILLER_Power[num-1])+((num-1)*20+40);
	}
	return output;
}

u8 Find_ACFAN_Speed(void)
{
  u8 output=0;
  if(CAN_RX_Info.AirCoditnrLinePrs<1240)
  {
    output=63;
  }
  else if(CAN_RX_Info.AirCoditnrLinePrs>1490)
  {
    output=92;
  }
  else
  {
    output=(CAN_RX_Info.AirCoditnrLinePrs/10-124)+64;
  }
  return output;
}

void ACFAN_Proc(void)//冷凝风扇转速发送,
{
  if(s_Heat_Cap.AC_IN_STATUS)
  {
    ACFAN_OFF_Count=20; //500ms*20=10s
  }
  else if(ACFAN_OFF_Count)
  {
    ACFAN_OFF_Count--;
  }
  if(ACFAN_OFF_Count>0)
  {
    ACFAN_PWM_DUTY=Find_ACFAN_Speed();
  }
  else
  {
    ACFAN_PWM_DUTY=0;
  }
}
