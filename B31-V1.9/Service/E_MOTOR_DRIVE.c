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

void E_Moter_CW_CCW(FunctionalState CW)//�������ͷ�ת��һ��
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

void E_Moter_Ctrl(void)//ִ��������
{
	CSB1_L();
	E_Moter_Status=V_SPI_RW(E_Moter_Buf);
	CSB1_H();
  if(E_Moter_Status & 0xE000)
  {
   ;
  }
}

void PHASE_A1_H(void)//A+�øߣ�A2�ø�
{
	E_Moter_Buf |= (1<<3);//A2�߱߿���
	E_Moter_Buf &=~(1<<4);//A2�ͱ߹رգ��ߵ�ƽ
}

void PHASE_A1_L(void)//A+�õ�,A2�͵�ƽ
{
	E_Moter_Buf &=~(1<<3);//A2�߱߹ر�
	E_Moter_Buf |= (1<<4);//A2�ͱ߿������͵�ƽ
}

void PHASE_A2_H(void)//A-�øߣ�B2�ߵ�ƽ
{
	E_Moter_Buf |= (1<<7);//B2�߱߿���
	E_Moter_Buf &=~(1<<8);//B2�ͱ߹رգ��ߵ�ƽ
}

void PHASE_A2_L(void)//A-�õͣ�B2�͵�ƽ
{
	E_Moter_Buf &=~(1<<7);//B2�߱߹ر�
	E_Moter_Buf |= (1<<8);//B2�ͱ߿������͵�ƽ
}

void PHASE_B1_H(void)//B+�ø�,B1�ߵ�ƽ
{
	E_Moter_Buf |= (1<<5);//B1�߱߿���
	E_Moter_Buf &=~(1<<6);//B1�ͱ߹رգ��ߵ�ƽ
}

void PHASE_B1_L(void)//B+�õͣ�B1�͵�ƽ
{
	E_Moter_Buf &=~(1<<5);//B1�߱߹ر�
	E_Moter_Buf |= (1<<6);//B1�ͱ߿������͵�ƽ
}

void PHASE_B2_H(void)//B-�øߣ�A1�ߵ�ƽ
{
	E_Moter_Buf |= (1<<1);//A1�߱߿���
	E_Moter_Buf &=~(1<<2);//A1�ͱ߹رգ��ߵ�ƽ
}

void PHASE_B2_L(void)//B-�õͣ�A1�͵�ƽ
{
	E_Moter_Buf &=~(1<<1);//A1�߱߹ر�
	E_Moter_Buf |= (1<<2);//A1�ͱ߿������͵�ƽ
}

void SW_FAN(SW_STATUS new_status)
{
  if(new_status==SW_OFF) //�õ͹ر�,C1�͵�ƽ
  {
    E_Moter_Buf &=~(1<<9);  //C1�߱߹ر�
    E_Moter_Buf |= (1<<10); //C1�ͱ߿������͵�ƽ
  }
  else                  //����̬����,C1����̬
  {
    E_Moter_Buf &=~(1<<9);  //C1�߱߹ر�
    E_Moter_Buf &=~(1<<10); //C1�ͱ߹رգ�����̬
  }
}

void SW_REARDEF(SW_STATUS new_status)
{
  if(new_status==SW_OFF)  //�õ͹ر�,C2�͵�ƽ
  {
    E_Moter_Buf &=~(1<<11); //C2�߱߹ر�
    E_Moter_Buf |= (1<<12); //C2�ͱ߿������͵�ƽ
  }
  else                    //����̬����,C2�ߵ�ƽ
  {
    E_Moter_Buf |= (1<<11); //C2�߱߿���
    E_Moter_Buf &=~(1<<12); //C2�ͱ߹رգ��ߵ�ƽ
  }
}

//end
