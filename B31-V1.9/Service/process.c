#include "process.h"
#include "hw_test.h"
#include "fan.h"
#include "LINprotocol.h"

void IO_Process(void)
{
//	AC_ON_OFF(s_Heat_Cap.AC_STATUS);
//	RDEF_ON_OFF(s_Heat_Cap.RDEF_STATUS);
//	INTake_ON_OFF(s_Heat_Cap.TAKE);
//	FDEF_ON_OFF(s_Heat_Cap.Mode_PPS);
//	SEATL_ON_OFF(s_Heat_Cap.SEATL_STATUS);
//	SEATR_ON_OFF(s_Heat_Cap.SEATR_STATUS);
//	FDEF2_ON_OFF(s_Heat_Cap.FDEF2_STATUS);
}

void Time_Count_Proc(void)
{
//  if(s_RTC_Left.break_count)
//  {
//    s_RTC_Left.break_count--;
//  }
//  if(s_RTC_Left.break_tip)
//  {
//    s_RTC_Left.break_tip--;
//  }
//  if(s_RTC_Left.SpUp_count)
//  {
//    s_RTC_Left.SpUp_count--;
//  }
//  if(s_RTC_Left.SpUp_tip)
//  {
//    s_RTC_Left.SpUp_tip--;
//  }
//  if(s_Heat_Cap.RDEF_STATUS)//���˪�Զ��ر�
//  {
//    s_RTC_Left.RDEF_Count++;
//  }
//  else
//  {
//    s_RTC_Left.RDEF_Count=0;
//  }
//  if(s_RTC_Left.RDEF_Count>720)//���˪12min�Զ��ر�
//  {
//    s_Heat_Cap.RDEF_STATUS=0;
//  }
//  if(s_RTC_Left.REC_Count)
//  {
//    s_RTC_Left.REC_Count--;
//  }
//  if(s_RTC_Left.REC_Tip)
//  {
//    s_RTC_Left.REC_Tip--;
//  }
}

void Time_Process(void)
{
  if(time_ms_flag & time_1ms_flag_MASK)//1ms����
  {
    time_ms_flag &=~time_1ms_flag_MASK;
		AD_Scan();//��ȡadc�Ľ����������adc
  }
  if(time_ms_flag & time_10ms_flag_MASK)//10ms����
  {
    time_ms_flag &=~time_10ms_flag_MASK;
//		LIN_TX_Proc();			//lin���ȱ�
      LIN_Task();               //
  }
  if(time_ms_flag & time_15ms_flag_MASK)//15ms����
  {
    time_ms_flag &=~time_15ms_flag_MASK;
//    E_MoterSTEP_CHANGE();//�������ͷ��ı�
  }
  
  if(time_ms_flag & time_20ms_flag_MASK)//20ms����
  {
        time_ms_flag &=~time_20ms_flag_MASK;
		Key_Process();      //������Ϣ����
      
        B31_Test();
      
      Moter_Ctrl();
  }
  if(time_ms_flag & time_50ms_flag_MASK)//50ms����
  {
    time_ms_flag &=~time_50ms_flag_MASK;
    Sleep_Process();//����
  }
  if(time_ms_flag & time_100ms_flag_MASK)//100ms����
  {
    time_ms_flag &=~time_100ms_flag_MASK;
//    FDEF_FANCHANGE();//��˪������ʾ����
//		PWM_FAN_CHANGE();//��������
//		CAN_INFO_DEAL();//CAN��Ϣ����
//    SC_LCDLight_PWM(GPIO_ReadInputDataBit(M_ILL_Port,M_ILL_Pin));//�������ȵ���
  }
  if(time_ms_flag & time_200ms_flag_MASK)//200ms����
  {
    time_ms_flag &=~time_200ms_flag_MASK;
//  #if(Auto_Fdef==1)   
//    Get_Tem_Hum();//�Զ�����
//  #endif
//    SHT21_Get();
  }
  if(time_ms_flag & time_500ms_flag_MASK)//500ms����
  {
	  
    time_ms_flag &=~time_500ms_flag_MASK;
	  
//    AUTO_RUN();               //�Զ�����
  }
  if(time_ms_flag & time_1000ms_flag_MASK)//1000ms����
  {
    time_ms_flag &=~time_1000ms_flag_MASK;
	
      
	change_fan_slowly(0xff);	//һ��һ��ı����
//    CAN_TX_Proc();
//		Gpio_Set(M_ESV_Port,SET);
//	*FlexRam_addr=0x12345678;
//	while(!(FTFC->FSTAT & FTFC_FSTAT_CCIF_MASK)){;}
//		Gpio_Set(M_ESV_Port,RESET);
		
		Board_WDOG_Feed();        //���Ź�ι��
//    AD_OutTem_Read();         //�����¶ȶ�ȡ
//    AD_PHOTO_Read();          //�����ȡ
//    Time_Count_Proc();        //ʱ�����
  }
}

void Main_Process(void)
{
	
//  CAN_Process();      //CAN������Ϣ
//  LIN_Process();      //Lin������Ϣ
//	IO_Process();       //I/O��ִ�б仯
//  Motor_Process();    //ִ�����������
//  TWV_Process();      //��ͨ������ִ��
//  Display_Process();  //��ʾ����
}

void Process(void)
{
	Main_Process(); //��ѭ��,һֱ����
	Time_Process(); //ʱ��ѭ������ʱ����
	
	#if HW_TEST
	hw_test_proc();
	#endif
}
//end
