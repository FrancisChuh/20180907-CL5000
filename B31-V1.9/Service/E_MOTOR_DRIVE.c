#include "E_MOTOR_DRIVE.h"

u16 E_MoterSTEP=480;
u16 E_MoterSTEP_PPS=0;

static u16 E_Moter_Status=0;
static u16 E_Moter_Buf=0;

void E_Moter_Stop(void)
{
  PHASE_A1_L();
  PHASE_B1_L();
  PHASE_A2_L();
  PHASE_B2_L();
}

void E_Moter_CW_CCW(FunctionalState CW)//电子膨胀阀转动一步
{
  static u8 PHACE_NOW=0;
  switch(PHACE_NOW)
  {
    case 1:
      if(CW)
      {
        PHASE_A1_H();    
        PHASE_B1_H();
        PHASE_A2_L();
        PHASE_B2_L();
        PHACE_NOW=2;
      }
      else
      {
        PHASE_A1_H();    
        PHASE_B1_L();
        PHASE_A2_L();
        PHASE_B2_H();
        PHACE_NOW=8;
      }
      break;
    case 2:
      if(CW)
      {
        PHASE_A1_L();    
        PHASE_B1_H();
        PHASE_A2_L();
        PHASE_B2_L();
        PHACE_NOW=3;
      }
      else
      {
        PHASE_A1_H();    
        PHASE_B1_L();
        PHASE_A2_L();
        PHASE_B2_L();
        PHACE_NOW=1;
      }
      break;
    case 3:
      if(CW)
      {
        PHASE_A1_L();    
        PHASE_B1_H();
        PHASE_A2_H();
        PHASE_B2_L();
        PHACE_NOW=4;
      }
      else
      {
        PHASE_A1_H();    
        PHASE_B1_H();
        PHASE_A2_L();
        PHASE_B2_L();
        PHACE_NOW=2;
      }
      break;
    case 4:
      if(CW)
      {
        PHASE_A1_L();    
        PHASE_B1_L();
        PHASE_A2_H();
        PHASE_B2_L();
        PHACE_NOW=5;
      }
      else
      {
        PHASE_A1_L();    
        PHASE_B1_H();
        PHASE_A2_L();
        PHASE_B2_L();
        PHACE_NOW=3;
      }
      break;
    case 5:
      if(CW)
      {
        PHASE_A1_L();    
        PHASE_B1_L();
        PHASE_A2_H();
        PHASE_B2_H();
        PHACE_NOW=6;
      }
      else
      {
        PHASE_A1_L();    
        PHASE_B1_H();
        PHASE_A2_H();
        PHASE_B2_L();
        PHACE_NOW=4;
      }
      break;
    case 6:
      if(CW)
      {
        PHASE_A1_L();    
        PHASE_B1_L();
        PHASE_A2_L();
        PHASE_B2_H();
        PHACE_NOW=7;
      }
      else
      {
        PHASE_A1_L();    
        PHASE_B1_L();
        PHASE_A2_H();
        PHASE_B2_L();
        PHACE_NOW=5;
      }
      break;
    case 7:
      if(CW)
      {
        PHASE_A1_H();    
        PHASE_B1_L();
        PHASE_A2_L();
        PHASE_B2_H();
        PHACE_NOW=8;
      }
      else
      {
        PHASE_A1_L();    
        PHASE_B1_L();
        PHASE_A2_H();
        PHASE_B2_H();
        PHACE_NOW=6;
      }
      break;
    case 8:
      if(CW)
      {
        PHASE_A1_H();    
        PHASE_B1_L();
        PHASE_A2_L();
        PHASE_B2_L();
        PHACE_NOW=1;
      }
      else
      {
        PHASE_A1_L();    
        PHASE_B1_L();
        PHASE_A2_L();
        PHASE_B2_H();
        PHACE_NOW=7;
      }
      break;
    default:
      PHASE_A1_H();    
      PHASE_B1_L();
      PHASE_A2_L();
      PHASE_B2_L();
      PHACE_NOW=1;
      break;
  }
}

void E_Moter_Ctrl(void)//执行器驱动
{
	CSB1_L();
	E_Moter_Status=V_SPI_RW(E_Moter_Buf);
	CSB1_H();
  if(E_Moter_Status & 0xE000)
  {
   ;
  }
}

void PHASE_A1_H(void)//A+置高，A2置高
{
	E_Moter_Buf |= (1<<3);//A2高边开启
	E_Moter_Buf &=~(1<<4);//A2低边关闭，高电平
}

void PHASE_A1_L(void)//A+置低,A2低电平
{
	E_Moter_Buf &=~(1<<3);//A2高边关闭
	E_Moter_Buf |= (1<<4);//A2低边开启，低电平
}

void PHASE_A2_H(void)//A-置高，B2高电平
{
	E_Moter_Buf |= (1<<7);//B2高边开启
	E_Moter_Buf &=~(1<<8);//B2低边关闭，高电平
}

void PHASE_A2_L(void)//A-置低，B2低电平
{
	E_Moter_Buf &=~(1<<7);//B2高边关闭
	E_Moter_Buf |= (1<<8);//B2低边开启，低电平
}

void PHASE_B1_H(void)//B+置高,B1高电平
{
	E_Moter_Buf |= (1<<5);//B1高边开启
	E_Moter_Buf &=~(1<<6);//B1低边关闭，高电平
}

void PHASE_B1_L(void)//B+置低，B1低电平
{
	E_Moter_Buf &=~(1<<5);//B1高边关闭
	E_Moter_Buf |= (1<<6);//B1低边开启，低电平
}

void PHASE_B2_H(void)//B-置高，A1高电平
{
	E_Moter_Buf |= (1<<1);//A1高边开启
	E_Moter_Buf &=~(1<<2);//A1低边关闭，高电平
}

void PHASE_B2_L(void)//B-置低，A1低电平
{
	E_Moter_Buf &=~(1<<1);//A1高边关闭
	E_Moter_Buf |= (1<<2);//A1低边开启，低电平
}

void SW_FAN(SW_STATUS new_status)
{
  if(new_status==SW_OFF) //置低关闭,C1低电平
  {
    E_Moter_Buf &=~(1<<9);  //C1高边关闭
    E_Moter_Buf |= (1<<10); //C1低边开启，低电平
  }
  else                  //高阻态开启,C1高阻态
  {
    E_Moter_Buf &=~(1<<9);  //C1高边关闭
    E_Moter_Buf &=~(1<<10); //C1低边关闭，高阻态
  }
}

void SW_REARDEF(SW_STATUS new_status)
{
  if(new_status==SW_OFF)  //置低关闭,C2低电平
  {
    E_Moter_Buf &=~(1<<11); //C2高边关闭
    E_Moter_Buf |= (1<<12); //C2低边开启，低电平
  }
  else                    //高阻态开启,C2高电平
  {
    E_Moter_Buf |= (1<<11); //C2高边开启
    E_Moter_Buf &=~(1<<12); //C2低边关闭，高电平
  }
}

//end
