#include "B31.h"
#include "actuator.h"
#include "fan.h"

u16 g_AUTO_Flag=AUTO_TEMP_MASK;
Heat_Cap_TypeDef s_Heat_Cap={0};
TIME_LEFT_TypeDef s_Time_Left;


void B31_Test(void)
{
    uint8_t mode=0;
    uint8_t intake=0;
    uint8_t temp_co=0;
    uint8_t temp_pa=0;
    
//    uint8_t desc_intake=0;
    
    uint8_t pwm=0;
    
//    uint8_t front_fan_level=0;
//    uint8_t rear_fan_level=0;
    
    if(s_Heat_Cap.TAKE==REC_INTake)
    {
        intake=1;
    }
    else if(s_Heat_Cap.TAKE==REC_OUTTake)
    {
        intake=0;
    }
    Intake_Run(intake);//内外循环
    DES_ACT_Run(intake);//后内外循环
//    DES_ACT_Run();//后内外循环
    
    if(s_Heat_Cap.Mode_PPS==MODENULL)
    {
        mode=0;
    }
    else if(s_Heat_Cap.Mode_PPS==MODEFACE)
    {
        mode=0;
    }
    else if(s_Heat_Cap.Mode_PPS==MODEFAFE)
    {
        mode=1;
    }
    else if(s_Heat_Cap.Mode_PPS==MODEFEET)
    {
        mode=2;
    }
    else if(s_Heat_Cap.Mode_PPS==MODEFEDE)
    {
        mode=3;
    }
    else if(s_Heat_Cap.Mode_PPS==MODEFDEF)
    {
        mode=4;
    }
    Mode_Run(mode);//模式
    
    
    if(s_Heat_Cap.RDEF_STATUS==0) //先用内外循环测试
//    if(s_Heat_Cap.AC_IN_STATUS==0)
    {
        temp_co=0;
        temp_pa=0;
    }
    else
    {
        temp_co=1;
        temp_pa=1;
    }
    
    TempACT_CO_Run(temp_co);//冷，暖
    TempACT_PA_Run(temp_pa);//冷，暖
    
//    front_fan_level=rear_fan_level=s_Heat_Cap.Set_Fan;
//    front_fan_change_level(front_fan_level);//前风扇
//    rear_fan_change_level(rear_fan_level);//后风扇
    if(s_Heat_Cap.Tem_Outside/10>100)
    {
        pwm=100;
    }
    else if(s_Heat_Cap.Tem_Outside/10>=0)
    {
        pwm=(uint8_t)(s_Heat_Cap.Tem_Outside/10);
    }
    else
    {
        pwm=0;
    }
    fan_test(pwm);
}

//混风控制数据
const int16_t TabKBMixACON[10]= {//5V基准参数
  4460,//-160
  3600,//-140
  3078,//-120
  2900,//-100
  2750,//-80
  2590,//-60
  2436,//-40
  2359,//-20
  2256,//0
  2153,//20
};

const int16_t TabKBMixACOFF[10]= {//5V基准参数
  4460,//4460,//-160
  3650,//3650,//-140
  2960,//2960,//-120
  2512,//2512,//-100
  2216,//2216,//-80
  1900,//1900,//-60
  1604,//1544,//-40
  1270,//1170,//-20
  855, //755,//0
  300, //300,//20
};

////风量控制数据
//#define FANDATASEGNUM 10
//static float TabPXFan[FANDATASEGNUM-1] = {-17.0,-6.0,-2.0,1.5,3.5,7.5,9.5,11.5,19.5};//    0,   1,   2,  3,  4,  5,  6,   7,   8 
//static float TabKBFanVot[FANDATASEGNUM][2] = {
//  -0.333,2.333,
//  -0.136,5.682,
//  -0.325,4.550,
//  -0.114,4.971,
//  0.000,4.800,
//  0.100,4.450,
//  0.650,0.325,
//  0.700,-0.150,
//  0.163,6.031,
//  0.000,9.200
//};

//const float TabFanVol[8] = {//0-7档风机档位电压:风机端电压
//  0,3.8,5.2,6.5,7.9,9.2,10.6,13.5
//  //0,1  ,2  ,3  ,4  ,5  ,6   ,7
//};

//const unsigned int TabFanPwm[8] = {//0-7档风机风量PWM值
//  0,26500,/*26000,*/28500,31000,34000,39000,48000,60000//实际值应保证:FANSTEP..(65536-FANSTEP),防止端点溢出
//};
//#define MINFAN    0//设定最低风量
//#define MAXFAN    7//设定最高风量
//const float FanVolPWMkb[MAXFAN][2] = {
//  6842.105,0.000,
//  1785.714,19214.286,
//  1923.077,18500.000,
//  2142.857,17071.429,
//  3846.154,3615.385,
//  6428.571,-20142.857,
//  4137.931,4137.931 
//};
const int16_t TabMixVoltage[31] = {//手动模式混风 基准:5.0Vref;0.3..4.7均分30等分
  300 ,//17.0 
  447 ,//17.5 
  593 ,//18.0 
  740 ,//18.5 
  887 , 
  1033 ,  
  1180 ,//20.0 
  1327 ,//20.5
  1473 ,//21.0 
  1620 ,//21.5  
  1767 ,//22.0
  1913 ,//22.5
  2060 ,
  2207 ,
  2353 ,
  2500 ,
  2647 ,
  2793 ,
  2940 ,
  3087 ,
  3233 ,
  3380 ,
  3527 ,
  3673 ,
  3820 ,
  3967 ,
  4113 ,
  4260 ,
  4407 ,
  4553 ,
  4700 
};

const u8 fan_table[13]={//风速算法
  70,//18
  70,//15
  70,//12
  40,//9
  25,//6
  15,//3
  10,//0
  15,//
  25,//
  40,//
  70,//
  70,//
  70 //
};

/***********************************************************************************************
 功能：换热需求计算
 输入：车内温度(25.0*10)，设定温度(25.0*10)，车内湿度(0-100%)
 输出：换热需求温度差
************************************************************************************************/
int16_t Heat_Cap_PIDControl(Heat_Cap_TypeDef* s_Heat_Cap_Type)
{
	Heat_Cap_TypeDef s_Heat_Cap_Temp=*s_Heat_Cap_Type;
  static int16_t err_now,err_last,err_last2;
  float ratio;
  
  s_Heat_Cap_Temp.Tem_In_err=s_Heat_Cap_Temp.Tem_Inside-s_Heat_Cap_Temp.Tem_Purpose;//设定和内温差
  s_Heat_Cap_Temp.Tem_Out_err=s_Heat_Cap_Temp.Tem_Outside-s_Heat_Cap_Temp.Tem_Purpose;//设定和外温差
  s_Heat_Cap_Temp.Tem_Out_In_err=s_Heat_Cap_Temp.Tem_Outside-s_Heat_Cap_Temp.Tem_Inside;//外温和内温差

  s_Heat_Cap_Temp.Tem_err_S=s_Heat_Cap_Temp.Tem_In_err+s_Heat_Cap_Temp.Tem_Out_err/10+s_Heat_Cap_Temp.SUN_Val/20;//阳光矫正
  
  ratio=1.0f+((float)s_Heat_Cap_Temp.Humidity_Inside-humidity_inside_std)*humidity_inside_prop;//计算湿度矫正
  err_now=s_Heat_Cap_Temp.Tem_err_S*ratio;//矫正后的内外温差
  
	err_now=pid_a*err_now+pid_b*err_last+pid_c*err_last2; //PID计算所需换热量
	err_last2=err_last;
	err_last=err_now;
//	if(tem>100)    //范围限定
//	{
//		tem=100;
//	}
//	else if(tem<-100)
//	{
//		tem=-100;
//	}
  s_Heat_Cap.Tem_In_err=s_Heat_Cap_Temp.Tem_In_err;
  s_Heat_Cap.Tem_Out_err=s_Heat_Cap_Temp.Tem_Out_err;
  s_Heat_Cap.Tem_Out_In_err=s_Heat_Cap_Temp.Tem_Out_In_err;
  s_Heat_Cap.Tem_err_S=s_Heat_Cap_Temp.Tem_err_S;
	return err_now;
}


/***********************************************************************************************
 功能：循环自动算法
 输入：车内温度(25.0*10)，设定温度(25.0*10)，车外温度(25.0*10)，车速（50km/h）,
       车外空气质量（0优秀：5差，-1err），当前循环模式（0-内循环 1-外循环）
 输出：0-内循环 1-外循环
************************************************************************************************/
int16_t TakeControl(Heat_Cap_TypeDef* s_Heat_Cap_Type)
{
	Heat_Cap_TypeDef s_Heat_Cap_Temp=*s_Heat_Cap_Type;
  static u8 REC_Dew_flag=0;

  if(g_AUTO_Flag & AUTO_TAKE_MASK)//内外循环自动
  {
    if(s_Heat_Cap_Temp.Air_Outside_qua>4)//空气质量很差
    {
      s_Heat_Cap_Temp.TAKE = REC_INTake;//强制内循环
    }
    else if(s_Heat_Cap_Temp.Air_Outside_qua<4)//空气质量中等及以上
    {
			if(s_DEW_Point.FDEF_TEM-s_DEW_Point.DEW_TEM<40)//自动除霜，4℃
			{
				REC_Dew_flag=1;
			}
			else if(s_DEW_Point.FDEF_TEM-s_DEW_Point.DEW_TEM>60)//解除自动除霜，6℃
			{
				REC_Dew_flag=0;
			}
			if(REC_Dew_flag)
			{
				s_Heat_Cap_Temp.TAKE= REC_OUTTake;//开外循环
			}
			else
			{
				if(s_Heat_Cap_Temp.Tem_err_S <-10)//车内温度比设定温度低1度以上，需要加热
				{
          #if(Hi_Eff==1)
					if(s_Heat_Cap_Temp.Tem_Out_In_err>55)//外温比内温高5.5℃以上
					{
						s_Heat_Cap_Temp.TAKE= REC_OUTTake;//开外循环
					}
					else if(s_Heat_Cap_Temp.Tem_Out_In_err<45)//只高4.5度以内
					{
						s_Heat_Cap_Temp.TAKE= REC_INTake;//开内循环
					}
          #else
          s_Heat_Cap_Temp.TAKE= REC_INTake;//开内循环
          #endif
				}
				else if(s_Heat_Cap_Temp.Tem_err_S>10)//车内温度比设定温度比高1度以上，需要制冷
				{
          #if(Hi_Eff==1)
					if(s_Heat_Cap_Temp.Tem_Out_In_err<-55)//外温比内温低5.5℃以上
					{
						s_Heat_Cap_Temp.TAKE= REC_OUTTake;//开外循环
					}
					else if(s_Heat_Cap_Temp.Tem_Out_In_err>-45)//只低4.5度以内
					{
						s_Heat_Cap_Temp.TAKE= REC_INTake;//开内循环
					}
          #else
          s_Heat_Cap_Temp.TAKE= REC_INTake;//开内循环
          #endif
				}
			}
    }
    if(s_Heat_Cap_Temp.TAKE==REC_INTake)//开内循环
    {
      if(s_Time_Left.REC_Tip==0)//第一次进入或休息时间到了
      {
        s_Time_Left.REC_Count=600;
      }
      if(s_Time_Left.REC_Count)//时间没到
      {
        s_Time_Left.REC_Tip=10;
      }
      else//时间到了，该外循环10s
      {
        s_Heat_Cap_Temp.TAKE=REC_OUTTake;
      }
    }
    else//外循环，计时关闭
    {
      s_Time_Left.REC_Tip=0;
    }
  }
  else//非自动，计时清空
  {
    s_Time_Left.REC_Tip=0;
  }
	return s_Heat_Cap_Temp.TAKE;
}

/***********************************************************************************************
 功能：AC开启关闭自动算法
 输入：车内温度(25.0*10)，设定温度(25.0*10)，车外温度(25.0*10)，车速（50km/h）,
 输出：AC关闭温度点(3.5-5.0*10)
************************************************************************************************/
int16_t AC_ON_OFF_Control(Heat_Cap_TypeDef* s_Heat_Cap_Type)
{
	Heat_Cap_TypeDef s_Heat_Cap_Temp=*s_Heat_Cap_Type;
//  static u8 AC_Dew_flag=0;
//  
//  if(g_AUTO_Flag & AUTO_AC_MASK)//自动AC
//  {
//    if(s_DEW_Point.FDEF_TEM-s_DEW_Point.DEW_TEM<30)//自动除霜，3℃
//    {
//      AC_Dew_flag=1;
//    }
//    else if(s_DEW_Point.FDEF_TEM-s_DEW_Point.DEW_TEM>50)//解除自动除霜，5℃
//    {
//      AC_Dew_flag=0;
//    }
//    if(AC_Dew_flag)
//    {
//      s_Heat_Cap_Temp.AC_IN_STATUS= 1;
//    }
//    else
//    {
//      if(s_Heat_Cap_Temp.Tem_Purpose==MAX_TEMSET)//HI模式
//      {
//        s_Heat_Cap_Temp.AC_IN_STATUS=0;
//      }
//      else if(s_Heat_Cap_Temp.Tem_Purpose==MIN_TEMSET)//LO模式
//      {
//        s_Heat_Cap_Temp.AC_IN_STATUS=1;
//      }
//      else//正常模式
//      {
//        if(s_Heat_Cap_Temp.Tem_err_S>10)//需要制冷
//        {
//          if(s_Heat_Cap_Temp.TAKE==REC_OUTTake)//外循环
//          {
//            #if(Hi_Eff==1)
//            if(s_Heat_Cap_Temp.Tem_Out_err<-100)//外温比设定低10度以上，不需要制冷
//            {
//              s_Heat_Cap_Temp.AC_IN_STATUS = 0;
//            }
//            else if(s_Heat_Cap_Temp.Tem_Out_err>-80)//外围比设定低8度以内，需要制冷
//            {
//              s_Heat_Cap_Temp.AC_IN_STATUS= 1;
//            }
//            #else
//            s_Heat_Cap_Temp.AC_IN_STATUS= 1;
//            #endif
//          }
//          else
//          {
//            s_Heat_Cap_Temp.AC_IN_STATUS= 1;
//          }
//        }
//        else if(s_Heat_Cap_Temp.Tem_err_S<-10)//需要加热
//        {
//          s_Heat_Cap_Temp.AC_IN_STATUS= 0;
//        }
//      }
//    }
//  }
	return s_Heat_Cap_Temp.AC_IN_STATUS;
}


/***********************************************************************************************
 功能：出风温度混风算法
 输入：车内温度(25.0*10)，设定温度(25.0*10)，车外温度(25.0*10)，车速（50km/h）,
 输出：温度电压
************************************************************************************************/
int16_t MIX_Control(Heat_Cap_TypeDef* s_Heat_Cap_Type)
{
	Heat_Cap_TypeDef s_Heat_Cap_Temp=*s_Heat_Cap_Type;
  u16 MixVolValue;//混风位置电压值
//  float Paprm = s_Heat_Cap_Temp.Tem_err_S_H;//含阳光矫正
  
  if(g_AUTO_Flag & AUTO_TEMP_MASK) //混风计算:控制混风位置值
  {
    if((s_Heat_Cap_Temp.AC_IN_STATUS) && (s_Heat_Cap_Temp.PTC_IN_STATUS)) //A/C ON,PTC ON
    {
      MixVolValue= TEMP_HI_VOL;
    }
    else if(s_Heat_Cap_Temp.AC_IN_STATUS)
    {
      MixVolValue=TEMP_LO_VOL;
    }
    else if(s_Heat_Cap_Temp.PTC_IN_STATUS)
    {
      MixVolValue=TEMP_HI_VOL;
    }
    else
    {
      MixVolValue= TEMP_MID_VOL;
    }
  }
  return MixVolValue;
}


/***********************************************************************************************
 功能：风速算法
 输入：车内温度(25.0*10)，设定温度(25.0*10)，车外温度(25.0*10)，车速（50km/h）,
 输出：风速档位对应PWM值
************************************************************************************************/
int16_t FAN_Speed_Control(Heat_Cap_TypeDef* s_Heat_Cap_Type)
{
	Heat_Cap_TypeDef s_Heat_Cap_Temp=*s_Heat_Cap_Type;
  u8 i;
  
  if((g_AUTO_Flag & AUTO_FAN_MASK)&&(exit_FDEF!=1)) //自动计算:控制风机PWM值
  {
		if(s_Heat_Cap_Temp.Tem_err_S>=180 || s_Heat_Cap_Temp.Tem_err_S<=-180 || s_Heat_Cap_Temp.Tem_Purpose==MIN_TEMSET || s_Heat_Cap_Temp.Tem_Purpose==MAX_TEMSET)
		{
			s_Heat_Cap_Temp.Set_Fan=80;
		}
		else
		{
			i=s_Heat_Cap_Temp.Tem_err_S/(-30)+6;
			if(s_Heat_Cap_Temp.Tem_err_S>=0)
			{
				s_Heat_Cap_Temp.Set_Fan=fan_table[i]+(s_Heat_Cap_Temp.Tem_err_S%30)*(fan_table[i-1]-fan_table[i])/30;
			}
			else
			{
				s_Heat_Cap_Temp.Set_Fan=fan_table[i]+(s_Heat_Cap_Temp.Tem_err_S%30)*(fan_table[i]-fan_table[i+1])/30;
			}
		}
    if(((s_Heat_Cap_Temp.Tem_Outside<100) )//&& (CAN_RX_Info.EngCoolantTemperatureValid==TRUE) && (CAN_RX_Info.EngCoolantTemperature-s_Heat_Cap_Temp.Tem_Inside<100))
      || (s_AD_Con.T_TEVA>300))
    {
      s_Heat_Cap_Temp.Set_Fan=10;
    }
		if((s_DEW_Point.FDEF_TEM-s_DEW_Point.DEW_TEM<55) &&(s_Heat_Cap_Temp.Set_Fan<50))//自动除霜，6℃
    {
			if(s_DEW_Point.FDEF_TEM-s_DEW_Point.DEW_TEM<20)//自动除霜，3℃
			{
				s_Heat_Cap_Temp.Set_Fan=50;
			}
			else if(s_DEW_Point.FDEF_TEM-s_DEW_Point.DEW_TEM<40)//自动除霜，4℃
			{
				s_Heat_Cap_Temp.Set_Fan+=20;
			}
			else
			{
	      s_Heat_Cap_Temp.Set_Fan+=10;
			}
			if(s_Heat_Cap_Temp.Set_Fan>50)
			{
				s_Heat_Cap_Temp.Set_Fan=50;
			}
		}
	}
	return s_Heat_Cap_Temp.Set_Fan;
}

/***********************************************************************************************
 功能：模式算法
 输入：车内温度(25.0*10)，设定温度(25.0*10)，车外温度(25.0*10)，车速（50km/h）,
 输出：模式档位
************************************************************************************************/
int16_t MODE_Control(Heat_Cap_TypeDef* s_Heat_Cap_Type)
{
	Heat_Cap_TypeDef s_Heat_Cap_Temp=*s_Heat_Cap_Type;
//  int32_t Tem_IN_err,Tem_out_err;
//  float Tem_err;
	static u8 MODE_Forced=0;
	static u8 MODE_Saved=MODEFACE;
	
  if(g_AUTO_Flag & AUTO_MODE_MASK)//模式自动
  {
		if(s_DEW_Point.FDEF_TEM-s_DEW_Point.DEW_TEM<20)//自动除霜，2℃
    {
			MODE_Forced |= MODE_FDEF_FORCED_MASK;
    }
    else if(s_DEW_Point.FDEF_TEM-s_DEW_Point.DEW_TEM>40)//解除自动除霜，4℃
    {
			MODE_Forced &=~MODE_FDEF_FORCED_MASK;
    }
    if(MODE_Forced & MODE_FDEF_FORCED_MASK)
    {
			if(s_Heat_Cap_Temp.Mode_PPS!=MODEFDEF)
			{
				s_Heat_Cap_Temp.Mode_PPS= MODEFDEF;
				Fan_manual=1;
			}
    }
    else
    {
			s_Heat_Cap_Temp.Mode_PPS=MODE_Saved;
			if(s_Heat_Cap_Temp.Tem_err_S < FaFeTOFeet)//制热
			{
				s_Heat_Cap_Temp.Mode_PPS= MODEFEET;
			}
			else if(s_Heat_Cap_Temp.Tem_err_S > FaFeTOFace)//制冷
			{
				s_Heat_Cap_Temp.Mode_PPS= MODEFACE;
			}
			else if((s_Heat_Cap_Temp.Tem_err_S > FeetTOFaFe) && (s_Heat_Cap_Temp.Tem_err_S < FaceTOFaFe))
			{
				s_Heat_Cap_Temp.Mode_PPS= MODEFAFE;
			}
			if(s_Heat_Cap_Temp.Tem_Outside>280)//待定,强制吹面
			{
				MODE_Forced |= MODE_FACE_FORCED_MASK;
			}
			else if(s_Heat_Cap_Temp.Tem_Outside<260)
			{
				MODE_Forced &=~MODE_FACE_FORCED_MASK;
			}
			if(s_Heat_Cap_Temp.Tem_Outside<130)//待定，强制吹脚
			{
				MODE_Forced |= MODE_FEET_FORCED_MASK;
			}
			else if(s_Heat_Cap_Temp.Tem_Outside>150)//待定
			{
				MODE_Forced &=~MODE_FEET_FORCED_MASK;
			}
			if(MODE_Forced & MODE_FACE_FORCED_MASK)
			{
				s_Heat_Cap_Temp.Mode_PPS= MODEFACE;
			}
			if(MODE_Forced & MODE_FEET_FORCED_MASK)
			{
				s_Heat_Cap_Temp.Mode_PPS= MODEFEET;
			}
			if(((s_Heat_Cap_Temp.Tem_Outside<100) )//&& (CAN_RX_Info.EngCoolantTemperatureValid==TRUE) && (CAN_RX_Info.EngCoolantTemperature-s_Heat_Cap_Temp.Tem_Inside<100))
				|| (s_AD_Con.T_TEVA>300))
			{
				s_Heat_Cap_Temp.Mode_PPS= MODEFDEF;
				Fan_manual=1;
			}
			MODE_Saved=s_Heat_Cap_Temp.Mode_PPS;
		}
  }
  return s_Heat_Cap_Temp.Mode_PPS;
}

void AUTO_RUN(void)
{
  Heat_Cap_PIDControl(&s_Heat_Cap);//热容,温差计算
  s_Heat_Cap.TAKE=TakeControl(&s_Heat_Cap);//内外循环控制
  s_Heat_Cap.AC_IN_STATUS=AC_ON_OFF_Control(&s_Heat_Cap);//AC开启判断(自动除雾)
  s_Heat_Cap.Set_Fan=FAN_Speed_Control(&s_Heat_Cap);//风速控制
  s_Heat_Cap.Mode_PPS=MODE_Control(&s_Heat_Cap);//模式控制

  s_Heat_Cap.MIX_Vol=MIX_Control(&s_Heat_Cap);//混风控制
	
	
//  PTC_Mode_Control();  //PTC制热判断
//  Refrige();//制冷逻辑判断
//  ACFAN_Proc();//冷凝风扇转速发送
}


void B31_Init(void)
{	
	s_Heat_Cap.Tem_Inside=250;       //车内温度
	s_Heat_Cap.Tem_Purpose=0;      //设定温度
	s_Heat_Cap.Tem_Slave_Purpose=0;	//设定温度2
	s_Heat_Cap.DUAL_STATUS=0;				//dual状态
	s_Heat_Cap.Humidity_Inside=0;  //车内湿度
	s_Heat_Cap.Tem_Outside=0;      //车外温度
	s_Heat_Cap.Air_Outside_qua=-1;  //车外空气质量
	s_Heat_Cap.TAKE=0;             //当前循环模式，0-内循环，1外循环
	s_Heat_Cap.Mode_PPS=MODEFACE;         //目标模式
	s_Heat_Cap.SUN_Val=200;          //阳光照度值
	s_Heat_Cap.AC_IN_STATUS=0;     //车内AC状态
	s_Heat_Cap.AC_BAT_STATUS=0;    //电池AC状态   
	s_Heat_Cap.PTC_IN_STATUS=0;    //车内PTC状态
	s_Heat_Cap.PTC_BAT_STATUS=0;   //电池PTC状态
	s_Heat_Cap.FDEF2_STATUS=0;     //前档加热状态
	s_Heat_Cap.RDEF_STATUS=0;      //后档加热状态
	s_Heat_Cap.MIX_Vol=0;          //混风电压
	s_Heat_Cap.Tem_In_err=0;       //车内温度-设定温度
	s_Heat_Cap.Tem_Out_err=0;      //车外温度-设定温度
	s_Heat_Cap.Tem_Out_In_err=0;   //车外温度-车内温度
	s_Heat_Cap.Tem_err_S=0;        //设定温差校准后参数（含阳光）
	s_Heat_Cap.Tem_err_S_H=0;      //设定温差校准后参数（含阳光和湿度）
	s_Heat_Cap.Set_Fan=0;          //设定风量档位（00-80，方便1.5档即15
	s_Heat_Cap.Set_Fan_Now=0;      //当前风量
	s_Heat_Cap.Heat_Cap=0;         //车内热容
	s_Heat_Cap.Break=0;            //刹车信号
	s_Heat_Cap.AC_ON_TEM=20;        //AC开启温度点
	s_Heat_Cap.AC_OFF_TEM=-10;       //AC关闭温度点
	s_Heat_Cap.Rapid_Speed_Up=0;   //急加速
	s_Heat_Cap.SEATL_STATUS=0;     //左座椅加热状态
	s_Heat_Cap.SEATR_STATUS=0;			//右座椅加热状态
	s_Heat_Cap.ESV_STATUS=0;				//截止阀导通状态
	s_Heat_Cap.PM25_STATUS=0;			//PM25状态
	s_Heat_Cap.Negativeion_STATUS=0;//负离子状态

}
//end
