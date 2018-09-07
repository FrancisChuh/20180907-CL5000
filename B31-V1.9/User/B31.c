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
    Intake_Run(intake);//����ѭ��
    DES_ACT_Run(intake);//������ѭ��
//    DES_ACT_Run();//������ѭ��
    
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
    Mode_Run(mode);//ģʽ
    
    
    if(s_Heat_Cap.RDEF_STATUS==0) //��������ѭ������
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
    
    TempACT_CO_Run(temp_co);//�䣬ů
    TempACT_PA_Run(temp_pa);//�䣬ů
    
//    front_fan_level=rear_fan_level=s_Heat_Cap.Set_Fan;
//    front_fan_change_level(front_fan_level);//ǰ����
//    rear_fan_change_level(rear_fan_level);//�����
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

//����������
const int16_t TabKBMixACON[10]= {//5V��׼����
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

const int16_t TabKBMixACOFF[10]= {//5V��׼����
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

////������������
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

//const float TabFanVol[8] = {//0-7�������λ��ѹ:����˵�ѹ
//  0,3.8,5.2,6.5,7.9,9.2,10.6,13.5
//  //0,1  ,2  ,3  ,4  ,5  ,6   ,7
//};

//const unsigned int TabFanPwm[8] = {//0-7���������PWMֵ
//  0,26500,/*26000,*/28500,31000,34000,39000,48000,60000//ʵ��ֵӦ��֤:FANSTEP..(65536-FANSTEP),��ֹ�˵����
//};
//#define MINFAN    0//�趨��ͷ���
//#define MAXFAN    7//�趨��߷���
//const float FanVolPWMkb[MAXFAN][2] = {
//  6842.105,0.000,
//  1785.714,19214.286,
//  1923.077,18500.000,
//  2142.857,17071.429,
//  3846.154,3615.385,
//  6428.571,-20142.857,
//  4137.931,4137.931 
//};
const int16_t TabMixVoltage[31] = {//�ֶ�ģʽ��� ��׼:5.0Vref;0.3..4.7����30�ȷ�
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

const u8 fan_table[13]={//�����㷨
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
 ���ܣ������������
 ���룺�����¶�(25.0*10)���趨�¶�(25.0*10)������ʪ��(0-100%)
 ��������������¶Ȳ�
************************************************************************************************/
int16_t Heat_Cap_PIDControl(Heat_Cap_TypeDef* s_Heat_Cap_Type)
{
	Heat_Cap_TypeDef s_Heat_Cap_Temp=*s_Heat_Cap_Type;
  static int16_t err_now,err_last,err_last2;
  float ratio;
  
  s_Heat_Cap_Temp.Tem_In_err=s_Heat_Cap_Temp.Tem_Inside-s_Heat_Cap_Temp.Tem_Purpose;//�趨�����²�
  s_Heat_Cap_Temp.Tem_Out_err=s_Heat_Cap_Temp.Tem_Outside-s_Heat_Cap_Temp.Tem_Purpose;//�趨�����²�
  s_Heat_Cap_Temp.Tem_Out_In_err=s_Heat_Cap_Temp.Tem_Outside-s_Heat_Cap_Temp.Tem_Inside;//���º����²�

  s_Heat_Cap_Temp.Tem_err_S=s_Heat_Cap_Temp.Tem_In_err+s_Heat_Cap_Temp.Tem_Out_err/10+s_Heat_Cap_Temp.SUN_Val/20;//�������
  
  ratio=1.0f+((float)s_Heat_Cap_Temp.Humidity_Inside-humidity_inside_std)*humidity_inside_prop;//����ʪ�Ƚ���
  err_now=s_Heat_Cap_Temp.Tem_err_S*ratio;//������������²�
  
	err_now=pid_a*err_now+pid_b*err_last+pid_c*err_last2; //PID�������軻����
	err_last2=err_last;
	err_last=err_now;
//	if(tem>100)    //��Χ�޶�
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
 ���ܣ�ѭ���Զ��㷨
 ���룺�����¶�(25.0*10)���趨�¶�(25.0*10)�������¶�(25.0*10)�����٣�50km/h��,
       �������������0���㣺5�-1err������ǰѭ��ģʽ��0-��ѭ�� 1-��ѭ����
 �����0-��ѭ�� 1-��ѭ��
************************************************************************************************/
int16_t TakeControl(Heat_Cap_TypeDef* s_Heat_Cap_Type)
{
	Heat_Cap_TypeDef s_Heat_Cap_Temp=*s_Heat_Cap_Type;
  static u8 REC_Dew_flag=0;

  if(g_AUTO_Flag & AUTO_TAKE_MASK)//����ѭ���Զ�
  {
    if(s_Heat_Cap_Temp.Air_Outside_qua>4)//���������ܲ�
    {
      s_Heat_Cap_Temp.TAKE = REC_INTake;//ǿ����ѭ��
    }
    else if(s_Heat_Cap_Temp.Air_Outside_qua<4)//���������еȼ�����
    {
			if(s_DEW_Point.FDEF_TEM-s_DEW_Point.DEW_TEM<40)//�Զ���˪��4��
			{
				REC_Dew_flag=1;
			}
			else if(s_DEW_Point.FDEF_TEM-s_DEW_Point.DEW_TEM>60)//����Զ���˪��6��
			{
				REC_Dew_flag=0;
			}
			if(REC_Dew_flag)
			{
				s_Heat_Cap_Temp.TAKE= REC_OUTTake;//����ѭ��
			}
			else
			{
				if(s_Heat_Cap_Temp.Tem_err_S <-10)//�����¶ȱ��趨�¶ȵ�1�����ϣ���Ҫ����
				{
          #if(Hi_Eff==1)
					if(s_Heat_Cap_Temp.Tem_Out_In_err>55)//���±����¸�5.5������
					{
						s_Heat_Cap_Temp.TAKE= REC_OUTTake;//����ѭ��
					}
					else if(s_Heat_Cap_Temp.Tem_Out_In_err<45)//ֻ��4.5������
					{
						s_Heat_Cap_Temp.TAKE= REC_INTake;//����ѭ��
					}
          #else
          s_Heat_Cap_Temp.TAKE= REC_INTake;//����ѭ��
          #endif
				}
				else if(s_Heat_Cap_Temp.Tem_err_S>10)//�����¶ȱ��趨�¶ȱȸ�1�����ϣ���Ҫ����
				{
          #if(Hi_Eff==1)
					if(s_Heat_Cap_Temp.Tem_Out_In_err<-55)//���±����µ�5.5������
					{
						s_Heat_Cap_Temp.TAKE= REC_OUTTake;//����ѭ��
					}
					else if(s_Heat_Cap_Temp.Tem_Out_In_err>-45)//ֻ��4.5������
					{
						s_Heat_Cap_Temp.TAKE= REC_INTake;//����ѭ��
					}
          #else
          s_Heat_Cap_Temp.TAKE= REC_INTake;//����ѭ��
          #endif
				}
			}
    }
    if(s_Heat_Cap_Temp.TAKE==REC_INTake)//����ѭ��
    {
      if(s_Time_Left.REC_Tip==0)//��һ�ν������Ϣʱ�䵽��
      {
        s_Time_Left.REC_Count=600;
      }
      if(s_Time_Left.REC_Count)//ʱ��û��
      {
        s_Time_Left.REC_Tip=10;
      }
      else//ʱ�䵽�ˣ�����ѭ��10s
      {
        s_Heat_Cap_Temp.TAKE=REC_OUTTake;
      }
    }
    else//��ѭ������ʱ�ر�
    {
      s_Time_Left.REC_Tip=0;
    }
  }
  else//���Զ�����ʱ���
  {
    s_Time_Left.REC_Tip=0;
  }
	return s_Heat_Cap_Temp.TAKE;
}

/***********************************************************************************************
 ���ܣ�AC�����ر��Զ��㷨
 ���룺�����¶�(25.0*10)���趨�¶�(25.0*10)�������¶�(25.0*10)�����٣�50km/h��,
 �����AC�ر��¶ȵ�(3.5-5.0*10)
************************************************************************************************/
int16_t AC_ON_OFF_Control(Heat_Cap_TypeDef* s_Heat_Cap_Type)
{
	Heat_Cap_TypeDef s_Heat_Cap_Temp=*s_Heat_Cap_Type;
//  static u8 AC_Dew_flag=0;
//  
//  if(g_AUTO_Flag & AUTO_AC_MASK)//�Զ�AC
//  {
//    if(s_DEW_Point.FDEF_TEM-s_DEW_Point.DEW_TEM<30)//�Զ���˪��3��
//    {
//      AC_Dew_flag=1;
//    }
//    else if(s_DEW_Point.FDEF_TEM-s_DEW_Point.DEW_TEM>50)//����Զ���˪��5��
//    {
//      AC_Dew_flag=0;
//    }
//    if(AC_Dew_flag)
//    {
//      s_Heat_Cap_Temp.AC_IN_STATUS= 1;
//    }
//    else
//    {
//      if(s_Heat_Cap_Temp.Tem_Purpose==MAX_TEMSET)//HIģʽ
//      {
//        s_Heat_Cap_Temp.AC_IN_STATUS=0;
//      }
//      else if(s_Heat_Cap_Temp.Tem_Purpose==MIN_TEMSET)//LOģʽ
//      {
//        s_Heat_Cap_Temp.AC_IN_STATUS=1;
//      }
//      else//����ģʽ
//      {
//        if(s_Heat_Cap_Temp.Tem_err_S>10)//��Ҫ����
//        {
//          if(s_Heat_Cap_Temp.TAKE==REC_OUTTake)//��ѭ��
//          {
//            #if(Hi_Eff==1)
//            if(s_Heat_Cap_Temp.Tem_Out_err<-100)//���±��趨��10�����ϣ�����Ҫ����
//            {
//              s_Heat_Cap_Temp.AC_IN_STATUS = 0;
//            }
//            else if(s_Heat_Cap_Temp.Tem_Out_err>-80)//��Χ���趨��8�����ڣ���Ҫ����
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
//        else if(s_Heat_Cap_Temp.Tem_err_S<-10)//��Ҫ����
//        {
//          s_Heat_Cap_Temp.AC_IN_STATUS= 0;
//        }
//      }
//    }
//  }
	return s_Heat_Cap_Temp.AC_IN_STATUS;
}


/***********************************************************************************************
 ���ܣ������¶Ȼ���㷨
 ���룺�����¶�(25.0*10)���趨�¶�(25.0*10)�������¶�(25.0*10)�����٣�50km/h��,
 ������¶ȵ�ѹ
************************************************************************************************/
int16_t MIX_Control(Heat_Cap_TypeDef* s_Heat_Cap_Type)
{
	Heat_Cap_TypeDef s_Heat_Cap_Temp=*s_Heat_Cap_Type;
  u16 MixVolValue;//���λ�õ�ѹֵ
//  float Paprm = s_Heat_Cap_Temp.Tem_err_S_H;//���������
  
  if(g_AUTO_Flag & AUTO_TEMP_MASK) //������:���ƻ��λ��ֵ
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
 ���ܣ������㷨
 ���룺�����¶�(25.0*10)���趨�¶�(25.0*10)�������¶�(25.0*10)�����٣�50km/h��,
 ��������ٵ�λ��ӦPWMֵ
************************************************************************************************/
int16_t FAN_Speed_Control(Heat_Cap_TypeDef* s_Heat_Cap_Type)
{
	Heat_Cap_TypeDef s_Heat_Cap_Temp=*s_Heat_Cap_Type;
  u8 i;
  
  if((g_AUTO_Flag & AUTO_FAN_MASK)&&(exit_FDEF!=1)) //�Զ�����:���Ʒ��PWMֵ
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
		if((s_DEW_Point.FDEF_TEM-s_DEW_Point.DEW_TEM<55) &&(s_Heat_Cap_Temp.Set_Fan<50))//�Զ���˪��6��
    {
			if(s_DEW_Point.FDEF_TEM-s_DEW_Point.DEW_TEM<20)//�Զ���˪��3��
			{
				s_Heat_Cap_Temp.Set_Fan=50;
			}
			else if(s_DEW_Point.FDEF_TEM-s_DEW_Point.DEW_TEM<40)//�Զ���˪��4��
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
 ���ܣ�ģʽ�㷨
 ���룺�����¶�(25.0*10)���趨�¶�(25.0*10)�������¶�(25.0*10)�����٣�50km/h��,
 �����ģʽ��λ
************************************************************************************************/
int16_t MODE_Control(Heat_Cap_TypeDef* s_Heat_Cap_Type)
{
	Heat_Cap_TypeDef s_Heat_Cap_Temp=*s_Heat_Cap_Type;
//  int32_t Tem_IN_err,Tem_out_err;
//  float Tem_err;
	static u8 MODE_Forced=0;
	static u8 MODE_Saved=MODEFACE;
	
  if(g_AUTO_Flag & AUTO_MODE_MASK)//ģʽ�Զ�
  {
		if(s_DEW_Point.FDEF_TEM-s_DEW_Point.DEW_TEM<20)//�Զ���˪��2��
    {
			MODE_Forced |= MODE_FDEF_FORCED_MASK;
    }
    else if(s_DEW_Point.FDEF_TEM-s_DEW_Point.DEW_TEM>40)//����Զ���˪��4��
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
			if(s_Heat_Cap_Temp.Tem_err_S < FaFeTOFeet)//����
			{
				s_Heat_Cap_Temp.Mode_PPS= MODEFEET;
			}
			else if(s_Heat_Cap_Temp.Tem_err_S > FaFeTOFace)//����
			{
				s_Heat_Cap_Temp.Mode_PPS= MODEFACE;
			}
			else if((s_Heat_Cap_Temp.Tem_err_S > FeetTOFaFe) && (s_Heat_Cap_Temp.Tem_err_S < FaceTOFaFe))
			{
				s_Heat_Cap_Temp.Mode_PPS= MODEFAFE;
			}
			if(s_Heat_Cap_Temp.Tem_Outside>280)//����,ǿ�ƴ���
			{
				MODE_Forced |= MODE_FACE_FORCED_MASK;
			}
			else if(s_Heat_Cap_Temp.Tem_Outside<260)
			{
				MODE_Forced &=~MODE_FACE_FORCED_MASK;
			}
			if(s_Heat_Cap_Temp.Tem_Outside<130)//������ǿ�ƴ���
			{
				MODE_Forced |= MODE_FEET_FORCED_MASK;
			}
			else if(s_Heat_Cap_Temp.Tem_Outside>150)//����
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
  Heat_Cap_PIDControl(&s_Heat_Cap);//����,�²����
  s_Heat_Cap.TAKE=TakeControl(&s_Heat_Cap);//����ѭ������
  s_Heat_Cap.AC_IN_STATUS=AC_ON_OFF_Control(&s_Heat_Cap);//AC�����ж�(�Զ�����)
  s_Heat_Cap.Set_Fan=FAN_Speed_Control(&s_Heat_Cap);//���ٿ���
  s_Heat_Cap.Mode_PPS=MODE_Control(&s_Heat_Cap);//ģʽ����

  s_Heat_Cap.MIX_Vol=MIX_Control(&s_Heat_Cap);//������
	
	
//  PTC_Mode_Control();  //PTC�����ж�
//  Refrige();//�����߼��ж�
//  ACFAN_Proc();//��������ת�ٷ���
}


void B31_Init(void)
{	
	s_Heat_Cap.Tem_Inside=250;       //�����¶�
	s_Heat_Cap.Tem_Purpose=0;      //�趨�¶�
	s_Heat_Cap.Tem_Slave_Purpose=0;	//�趨�¶�2
	s_Heat_Cap.DUAL_STATUS=0;				//dual״̬
	s_Heat_Cap.Humidity_Inside=0;  //����ʪ��
	s_Heat_Cap.Tem_Outside=0;      //�����¶�
	s_Heat_Cap.Air_Outside_qua=-1;  //�����������
	s_Heat_Cap.TAKE=0;             //��ǰѭ��ģʽ��0-��ѭ����1��ѭ��
	s_Heat_Cap.Mode_PPS=MODEFACE;         //Ŀ��ģʽ
	s_Heat_Cap.SUN_Val=200;          //�����ն�ֵ
	s_Heat_Cap.AC_IN_STATUS=0;     //����AC״̬
	s_Heat_Cap.AC_BAT_STATUS=0;    //���AC״̬   
	s_Heat_Cap.PTC_IN_STATUS=0;    //����PTC״̬
	s_Heat_Cap.PTC_BAT_STATUS=0;   //���PTC״̬
	s_Heat_Cap.FDEF2_STATUS=0;     //ǰ������״̬
	s_Heat_Cap.RDEF_STATUS=0;      //�󵵼���״̬
	s_Heat_Cap.MIX_Vol=0;          //����ѹ
	s_Heat_Cap.Tem_In_err=0;       //�����¶�-�趨�¶�
	s_Heat_Cap.Tem_Out_err=0;      //�����¶�-�趨�¶�
	s_Heat_Cap.Tem_Out_In_err=0;   //�����¶�-�����¶�
	s_Heat_Cap.Tem_err_S=0;        //�趨�²�У׼������������⣩
	s_Heat_Cap.Tem_err_S_H=0;      //�趨�²�У׼��������������ʪ�ȣ�
	s_Heat_Cap.Set_Fan=0;          //�趨������λ��00-80������1.5����15
	s_Heat_Cap.Set_Fan_Now=0;      //��ǰ����
	s_Heat_Cap.Heat_Cap=0;         //��������
	s_Heat_Cap.Break=0;            //ɲ���ź�
	s_Heat_Cap.AC_ON_TEM=20;        //AC�����¶ȵ�
	s_Heat_Cap.AC_OFF_TEM=-10;       //AC�ر��¶ȵ�
	s_Heat_Cap.Rapid_Speed_Up=0;   //������
	s_Heat_Cap.SEATL_STATUS=0;     //�����μ���״̬
	s_Heat_Cap.SEATR_STATUS=0;			//�����μ���״̬
	s_Heat_Cap.ESV_STATUS=0;				//��ֹ����ͨ״̬
	s_Heat_Cap.PM25_STATUS=0;			//PM25״̬
	s_Heat_Cap.Negativeion_STATUS=0;//������״̬

}
//end
