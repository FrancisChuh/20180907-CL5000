#include "PID.H"


/* R134a�����: �����¶ȡ�ѹ��������ϵʽϵ�� */
const double coefficient[5]={0.038437, -0.484217, 3.917882, 1.738455, -87.564043};

double Kp=8;			//����ϵ��
double Ki=0.04;            //����ϵ��
double Kd=0;            //΢��ϵ��

double Steady_max_err=2.0;		//��̬����������
//double Kp_efc=0.3;		//��̬����P����ϵ��
double Ki_efc=0.3;		//��̬����I����ϵ��
//double Kd_efc=1;		//��̬����D����ϵ��

double Init_out=270;
double PID_max=210;		//PID������ֵ
double PID_min=-210;		//PID��С���ֵ
const int16_t Max_increment=3;		//�����ŷ�����PID�������
int16_t Numb_in_steady=0;   //�����ȶ�����������
int16_t Last_Numb_in_steady=0;   //�����ȶ�����������
int16_t Min_numb_steady=600;   //�ȶ�������С������
double PID_out=0;

double E_MoterSTEP_F=E_MoterSTEP_Max;

u8 E_MoterFLAG = 0;        //EXV��ʼ����ϱ�־λ

void E_Moter_Pos_Init(void)
{
	if(E_MoterSTEP==E_MoterSTEP_PPS)
	{
		E_MoterFLAG = 1;
	}
}

void E_Moter_Control_Fun(void)
{	
	if(E_Moter_ControlFLAG) //ʹ��PID����EXV
	{
		PID_out=PID_Calcu(5.0, s_AD_Con.P_PRESSLOW,(float)s_AD_Con.T_TPRESSLOW/10);

		E_MoterSTEP_F=Init_out-PID_out;

		if(E_MoterSTEP_F>E_MoterSTEP_Max)
		{
			E_MoterSTEP_F=E_MoterSTEP_Max;
		}
		else if(E_MoterSTEP_F<E_MoterSTEP_Min)
		{
			E_MoterSTEP_F=E_MoterSTEP_Min;
		}
		E_MoterSTEP_PPS=(int16_t)E_MoterSTEP_F;
	
//    E_MoterSTEP_PPS=PID_Change();
//    E_MoterSTEP_PPS=30;
	}
}

double PID_Change(void)
{	
  static int32_t istep=1;            //�������ŷ����ڸ���  
	int Opened=0 ;
	int PID_out=0;
	
//	Opened=(istep-1200)/10000;
//	PID_out=60+Opened*40;
	
	PID_out=140+5+5;
	printf("%d,%d,%d\r\n",istep,Opened,PID_out);
	istep++;
	
	return PID_out;
}



//set_sh ���ȶ��趨ֵ
//P ����������ѹ��,��ѹ��ѹ��
//T �����������¶�
double ActualSH=0;                //�ȱ��Ͷ�ʵ��ֵ

double PID_Calcu(double set_sh, double P, double T)
{  
  double Err=0;                        //���ȶ�ƫ��ֵ
  static double Err_last=0;            //��һ�����ȶ�ƫ��ֵ
  double PID_out=0;                    //PID���������
  static double LastPID_out=0;         //��һ��PID���������ֵ  
  static double Integral=0;           //������� 
  double PD_out=0;           //����+΢����� 
  static int32_t istep=1;            //�������ŷ����ڸ���       
		
	double CalSH=0;		
	static double CalSH_19=0;
	static double CalSH_18=0;
	static double CalSH_17=0;
	static double CalSH_16=0;
	static double CalSH_15=0;
	static double CalSH_14=0;
	static double CalSH_13=0;
	static double CalSH_12=0;
	static double CalSH_11=0;
	static double CalSH_10=0;
	static double CalSH_9=0;
	static double CalSH_8=0;
	static double CalSH_7=0;
	static double CalSH_6=0;
	static double CalSH_5=0;
	static double CalSH_4=0;
	static double CalSH_3=0;
	static double CalSH_2=0;
	static double CalSH_1=0;
	static double CalSH_0=0;	
	static double dErr=0;	
	
	static int16_t Err_cross_0=0;	           //��������� 
	static int32_t Step_errcross_0=1;	           //������ʱ�̣�������������
	static int16_t MaxOpen=E_MoterSTEP_Min;
	static int16_t MinOpen=E_MoterSTEP_Max;
	static int16_t MaxSH=-30;
	static int16_t MinSH=30;
	static int16_t ChangeInitFlag=0;
	
  CalSH=CalcuSH(P, T);		
	dErr=CalSH_19-CalSH;
	if (istep==1)
	{		
		CalSH_19=CalSH;
		CalSH_18=CalSH;
		CalSH_17=CalSH;
		CalSH_16=CalSH;
		CalSH_15=CalSH;
		CalSH_14=CalSH;
		CalSH_13=CalSH;
		CalSH_12=CalSH;
		CalSH_11=CalSH;
		CalSH_10=CalSH;
		CalSH_9=CalSH;
		CalSH_8=CalSH;
		CalSH_7=CalSH;
		CalSH_6=CalSH;
		CalSH_5=CalSH;
		CalSH_4=CalSH;
		CalSH_3=CalSH;
		CalSH_2=CalSH;
		CalSH_1=CalSH;
		CalSH_0=CalSH;
	}
	else
	{		
		CalSH_19=CalSH_18;
		CalSH_18=CalSH_17;
		CalSH_17=CalSH_16;
		CalSH_16=CalSH_15;
		CalSH_15=CalSH_14;
		CalSH_14=CalSH_13;
		CalSH_13=CalSH_12;
		CalSH_12=CalSH_11;
		CalSH_11=CalSH_10;
		CalSH_10=CalSH_9;
		CalSH_9=CalSH_8;
		CalSH_8=CalSH_7;
		CalSH_7=CalSH_6;
		CalSH_6=CalSH_5;
		CalSH_5=CalSH_4;
		CalSH_4=CalSH_3;
		CalSH_3=CalSH_2;
		CalSH_2=CalSH_1;
		CalSH_1=CalSH_0;
		CalSH_0=CalSH;		
	}
	
	ActualSH=(CalSH_19+CalSH_18+CalSH_17+CalSH_16+CalSH_15+CalSH_14+CalSH_13+CalSH_12+CalSH_11+CalSH_10+CalSH_9+CalSH_8+CalSH_7+CalSH_6+CalSH_5+CalSH_4+CalSH_3+CalSH_2+CalSH_1+CalSH_0)/20;	
  Err=set_sh-ActualSH; 
		
	if (fabs(Err)<Steady_max_err)
	{
		Numb_in_steady+=1;
	}
	else
	{
		Numb_in_steady=0;
	}			
	if (Numb_in_steady>Min_numb_steady)
	{		
		Integral += Ki_efc*Ki*(Err+Err_last)/2;
		PD_out=Kp*Err+Kd*dErr;
		PID_out=PD_out+Integral;	
	}
	else if((Numb_in_steady>0) && (fabs(Err)<fabs(Err_last)))
	{
		Integral += -0.1*Ki*(Err+Err_last)/2;
		PD_out=Kp*Err+Kd*dErr;
		PID_out=PD_out+Integral;	
	}
	else 
	{
		Integral += Ki*(Err+Err_last)/2;
		PD_out=Kp*Err+Kd*dErr;
		PID_out=PD_out+Integral;	
	}		
	
	if ((Last_Numb_in_steady>Min_numb_steady) && (Numb_in_steady==0))
	{
		Err_cross_0=0;
		Step_errcross_0=istep;
		MaxOpen=E_MoterSTEP_Min;
		MinOpen=E_MoterSTEP_Max;
	}	
	if (!(Numb_in_steady>Min_numb_steady))
	{
		if ((!(Err*Err_last>0)) && (istep>100+Step_errcross_0))
		{
			Err_cross_0+=1;	           //��������� 
			Step_errcross_0=istep;	           //������ʱ�̣�������������		
		}	
		if (Err_cross_0==2 || Err_cross_0==3)
		{
			if (E_MoterSTEP>MaxOpen)
			{
				MaxOpen=E_MoterSTEP;
			}
			if (E_MoterSTEP<MinOpen)
			{
				MinOpen=E_MoterSTEP;
			}
						
			if (ActualSH>MaxSH)
			{
				MaxSH=ActualSH;
			}
			if (ActualSH<MinSH)
			{
				MinSH=ActualSH;
			}						
		}
		if (Err_cross_0==4)
		{
//			if ((MaxSH-set_sh)>1 && (MinSH-set_sh)<-1)
			{
				Init_out=(MaxOpen+MinOpen)/2;
				PID_min=Init_out-E_MoterSTEP_Max;
				PID_max=Init_out-E_MoterSTEP_Min;
				Integral=0;		
				ChangeInitFlag=1;
			}
//			else
//			{
//				ChangeInitFlag=0;	
//			}
		
			Err_cross_0=2;
			Step_errcross_0=istep;
			MaxOpen=E_MoterSTEP_Min;
			MinOpen=E_MoterSTEP_Max;
		}
	}
	
	if (Integral>PID_max)
	{
		Integral=PID_max;
	}
	else if (Integral<PID_min)
	{
		Integral=PID_min;
	}	
	if (PID_out>(LastPID_out+Max_increment))
  {
		PID_out=LastPID_out+Max_increment;
  }
  if (PID_out<(LastPID_out-Max_increment))
  {
    PID_out=LastPID_out-Max_increment;
  }
	if (PID_out>PID_max)
  {
		PID_out=PID_max;
  }
  if (PID_out<PID_min)
  {
    PID_out=PID_min;
  }	
	
	if (ChangeInitFlag==1) 
	{
		if (fabs(Init_out-E_MoterSTEP)>Max_increment)
		{
			PID_out=0;
			Integral=0;
		}
		else
		{
			ChangeInitFlag=0;
		}
	}
		
	//ÿ�ε��ú���Ҫ���� istep��P��T��SetSH,ActualSH��PID_out��ֵ��ÿ�ν���ú�������һ��  
//  printf("%d,%.01f,%.01f,%.d,%.02f,%.01f,%.01f\r\n",istep,Integral,PD_out,E_MoterSTEP,ActualSH,P,T);
  //printf("%.02f,%d,%d,%d,%d,%.02f,%.02f\r\n",Init_out,Numb_in_steady,ChangeInitFlag,Err_cross_0,Step_errcross_0,PID_max,PID_min);

  istep++;
	Last_Numb_in_steady=Numb_in_steady;
	Err_last=Err;
	LastPID_out=PID_out;
  
  return PID_out;
}

/* ����ʵ�ʹ��ȶ� */
double CalcuSH(double P, double T)
{
  double LnP=0;
  double Tb=0;
  double SH=0;
  
  LnP=log(P);
	//Tb:�����¶�
  Tb=coefficient[0]*LnP*LnP*LnP*LnP+coefficient[1]*LnP*LnP*LnP+coefficient[2]*LnP*LnP+coefficient[3]*LnP+coefficient[4];
  SH=T-Tb; 
	return SH;
}
