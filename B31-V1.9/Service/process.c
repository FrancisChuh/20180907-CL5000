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
//  if(s_Heat_Cap.RDEF_STATUS)//后除霜自动关闭
//  {
//    s_RTC_Left.RDEF_Count++;
//  }
//  else
//  {
//    s_RTC_Left.RDEF_Count=0;
//  }
//  if(s_RTC_Left.RDEF_Count>720)//后除霜12min自动关闭
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
  if(time_ms_flag & time_1ms_flag_MASK)//1ms周期
  {
    time_ms_flag &=~time_1ms_flag_MASK;
		AD_Scan();//读取adc的结果，并开启adc
  }
  if(time_ms_flag & time_10ms_flag_MASK)//10ms周期
  {
    time_ms_flag &=~time_10ms_flag_MASK;
//		LIN_TX_Proc();			//lin调度表
      LIN_Task();               //
  }
  if(time_ms_flag & time_15ms_flag_MASK)//15ms周期
  {
    time_ms_flag &=~time_15ms_flag_MASK;
//    E_MoterSTEP_CHANGE();//电子膨胀阀改变
  }
  
  if(time_ms_flag & time_20ms_flag_MASK)//20ms周期
  {
        time_ms_flag &=~time_20ms_flag_MASK;
		Key_Process();      //按键消息处理
      
        B31_Test();
      
      Moter_Ctrl();
  }
  if(time_ms_flag & time_50ms_flag_MASK)//50ms周期
  {
    time_ms_flag &=~time_50ms_flag_MASK;
    Sleep_Process();//休眠
  }
  if(time_ms_flag & time_100ms_flag_MASK)//100ms周期
  {
    time_ms_flag &=~time_100ms_flag_MASK;
//    FDEF_FANCHANGE();//除霜风量显示渐变
//		PWM_FAN_CHANGE();//风量渐变
//		CAN_INFO_DEAL();//CAN信息处理
//    SC_LCDLight_PWM(GPIO_ReadInputDataBit(M_ILL_Port,M_ILL_Pin));//背光亮度调节
  }
  if(time_ms_flag & time_200ms_flag_MASK)//200ms周期
  {
    time_ms_flag &=~time_200ms_flag_MASK;
//  #if(Auto_Fdef==1)   
//    Get_Tem_Hum();//自动除雾
//  #endif
//    SHT21_Get();
  }
  if(time_ms_flag & time_500ms_flag_MASK)//500ms周期
  {
	  
    time_ms_flag &=~time_500ms_flag_MASK;
	  
//    AUTO_RUN();               //自动计算
  }
  if(time_ms_flag & time_1000ms_flag_MASK)//1000ms周期
  {
    time_ms_flag &=~time_1000ms_flag_MASK;
	
      
	change_fan_slowly(0xff);	//一格一格改变风量
//    CAN_TX_Proc();
//		Gpio_Set(M_ESV_Port,SET);
//	*FlexRam_addr=0x12345678;
//	while(!(FTFC->FSTAT & FTFC_FSTAT_CCIF_MASK)){;}
//		Gpio_Set(M_ESV_Port,RESET);
		
		Board_WDOG_Feed();        //看门狗喂狗
//    AD_OutTem_Read();         //车外温度读取
//    AD_PHOTO_Read();          //阳光读取
//    Time_Count_Proc();        //时间计数
  }
}

void Main_Process(void)
{
	
//  CAN_Process();      //CAN接收信息
//  LIN_Process();      //Lin接收信息
//	IO_Process();       //I/O口执行变化
//  Motor_Process();    //执行器电机控制
//  TWV_Process();      //三通阀动作执行
//  Display_Process();  //显示更新
}

void Process(void)
{
	Main_Process(); //主循环,一直运行
	Time_Process(); //时间循环，定时运行
	
	#if HW_TEST
	hw_test_proc();
	#endif
}
//end
