#include "LCD.h"

u8 KEY_READ_REQUEST=0;
LCD_DIS_TypeDef LCD_RAM;

void LCD_Init(void)//��ʼ��ʾ
{
	s_Heat_Cap.AC_STATUS=0;//AC�ر�
	g_AUTO_Flag=AUTO_TEMP_MASK;//AUTO�ر�
	s_Heat_Cap.TAKE=REC_INTake;//��ѭ��
	s_Heat_Cap.Set_Fan=0;//����0
	s_Heat_Cap.Tem_Purpose=250;//�趨�¶�
	s_Heat_Cap.Mode_PPS=MODEFACE;//ģʽ����
	s_FDEF_Last.Mode_PPS_Last=MODEFACE;
	s_Heat_Cap.RDEF_STATUS=0;//�غ��˪
	s_Heat_Cap.SEATL_STATUS=0;//�ر������μ���
	s_Heat_Cap.SEATR_STATUS=0;//�ر������μ���
	s_Heat_Cap.FDEF2_STATUS=0;//�ر�ǰ������
	s_Heat_Cap.AC_ON_TEM=AC_ON_TEMP_default;//Ĭ����ͣ��
	s_Heat_Cap.AC_OFF_TEM=AC_OFF_TEMP_default;//Ĭ����ͣ��
	
//	LCD_RAM.D9_16 |=L5_MASK;//��ʾ����
//	LCD_RAM.D9_16 |=N3_MASK;//��ʾ����
//	LCD_RAM.D17_24 |=N4_MASK;//��ʾ����һ��
//	LCD_RAM.D17_24 |=N1_MASK;//��ʾ��ѭ��
//  LCD_RAM.D9_16 |=L4_MASK;//��ʾ�������
//  LCD_RAM.D17_24 |= M2_MASK; //OUTSIDE
//  LCD_RAM.D46_53 |= P1_MASK; //��
//  LCD_RAM.D25_32 |= G1_MASK; //--��
//  LCD_RAM.D38_45 |= G2_MASK; //--��
//	LCD_Display_Updata();
}

void LCD_REC_SHOWS(signed char rec_val)//����ѭ��
{
  if(rec_val==0)
  {
		LCD_RAM.D9_16  |=N3_MASK;//��ʾ����
		LCD_RAM.D17_24 |=N4_MASK;//��ʾ����һ��
    LCD_RAM.D17_24 &=~N1_MASK;//��ʾ��ѭ��
    LCD_RAM.D9_16  |= N2_MASK;//��ʾ��ѭ��
  }
  else
  {
		LCD_RAM.D9_16	 |=N3_MASK;//��ʾ����
		LCD_RAM.D17_24 |=N4_MASK;//��ʾ����һ��
    LCD_RAM.D17_24 |= N1_MASK;//��ʾ��ѭ��
    LCD_RAM.D9_16	 &=~N2_MASK;//��ʾ��ѭ��
  }
}

void LCD_FANSPEED_SHOWS(u8 level,FunctionalState NewState)//����
{
  if((NewState==DISABLE) || (level==0) )
  {
    LCD_RAM.D1_8 &= ~T1_MASK;
    LCD_RAM.D1_8 &= ~T2_MASK;
    LCD_RAM.D1_8 &= ~T3_MASK;
    LCD_RAM.D1_8 &= ~T4_MASK;
    LCD_RAM.D1_8 &= ~T5_MASK;
    LCD_RAM.D1_8 &= ~T6_MASK;
    LCD_RAM.D1_8 &= ~T7_MASK;
    LCD_RAM.D1_8 &= ~T8_MASK;
  }
  else
  {
    level=level/10;
    switch(level)
    {
      case 1:
        LCD_RAM.D1_8 |= T1_MASK;
        LCD_RAM.D1_8 &= ~T2_MASK;
        LCD_RAM.D1_8 &= ~T3_MASK;
        LCD_RAM.D1_8 &= ~T4_MASK;
        LCD_RAM.D1_8 &= ~T5_MASK;
        LCD_RAM.D1_8 &= ~T6_MASK;
        LCD_RAM.D1_8 &= ~T7_MASK;
        LCD_RAM.D1_8 &= ~T8_MASK;
        break;
      case 2:
        LCD_RAM.D1_8 |= T1_MASK;
        LCD_RAM.D1_8 |= T2_MASK;
        LCD_RAM.D1_8 &= ~T3_MASK;
        LCD_RAM.D1_8 &= ~T4_MASK;
        LCD_RAM.D1_8 &= ~T5_MASK;
        LCD_RAM.D1_8 &= ~T6_MASK;
        LCD_RAM.D1_8 &= ~T7_MASK;
        LCD_RAM.D1_8 &= ~T8_MASK;
        break;
      case 3:
        LCD_RAM.D1_8 |= T1_MASK;
        LCD_RAM.D1_8 |= T2_MASK;
        LCD_RAM.D1_8 |= T3_MASK;
        LCD_RAM.D1_8 &= ~T4_MASK;
        LCD_RAM.D1_8 &= ~T5_MASK;
        LCD_RAM.D1_8 &= ~T6_MASK;
        LCD_RAM.D1_8 &= ~T7_MASK;
        LCD_RAM.D1_8 &= ~T8_MASK;
        break;
      case 4:
        LCD_RAM.D1_8 |= T1_MASK;
        LCD_RAM.D1_8 |= T2_MASK;
        LCD_RAM.D1_8 |= T3_MASK;
        LCD_RAM.D1_8 |= T4_MASK;
        LCD_RAM.D1_8 &= ~T5_MASK;
        LCD_RAM.D1_8 &= ~T6_MASK;
        LCD_RAM.D1_8 &= ~T7_MASK;
        LCD_RAM.D1_8 &= ~T8_MASK;
        break;
      case 5:
        LCD_RAM.D1_8 |= T1_MASK;
        LCD_RAM.D1_8 |= T2_MASK;
        LCD_RAM.D1_8 |= T3_MASK;
        LCD_RAM.D1_8 |= T4_MASK;
        LCD_RAM.D1_8 |= T5_MASK;
        LCD_RAM.D1_8 &= ~T6_MASK;
        LCD_RAM.D1_8 &= ~T7_MASK;
        LCD_RAM.D1_8 &= ~T8_MASK;
        break;
      case 6:
        LCD_RAM.D1_8 |= T1_MASK;
        LCD_RAM.D1_8 |= T2_MASK;
        LCD_RAM.D1_8 |= T3_MASK;
        LCD_RAM.D1_8 |= T4_MASK;
        LCD_RAM.D1_8 |= T5_MASK;
        LCD_RAM.D1_8 |= T6_MASK;
        LCD_RAM.D1_8 &= ~T7_MASK;
        LCD_RAM.D1_8 &= ~T8_MASK;
        break;
      case 7:
        LCD_RAM.D1_8 |= T1_MASK;
        LCD_RAM.D1_8 |= T2_MASK;
        LCD_RAM.D1_8 |= T3_MASK;
        LCD_RAM.D1_8 |= T4_MASK;
        LCD_RAM.D1_8 |= T5_MASK;
        LCD_RAM.D1_8 |= T6_MASK;
        LCD_RAM.D1_8 |= T7_MASK;
        LCD_RAM.D1_8 &= ~T8_MASK;
        break;
      case 8:
        LCD_RAM.D1_8 |= T1_MASK;
        LCD_RAM.D1_8 |= T2_MASK;
        LCD_RAM.D1_8 |= T3_MASK;
        LCD_RAM.D1_8 |= T4_MASK;
        LCD_RAM.D1_8 |= T5_MASK;
        LCD_RAM.D1_8 |= T6_MASK;
        LCD_RAM.D1_8 |= T7_MASK;
        LCD_RAM.D1_8 |= T8_MASK;
        break;
      default://0-1������ʾ1����
        LCD_RAM.D1_8 |= T1_MASK;
        LCD_RAM.D1_8 &= ~T2_MASK;
        LCD_RAM.D1_8 &= ~T3_MASK;
        LCD_RAM.D1_8 &= ~T4_MASK;
        LCD_RAM.D1_8 &= ~T5_MASK;
        LCD_RAM.D1_8 &= ~T6_MASK;
        LCD_RAM.D1_8 &= ~T7_MASK;
        LCD_RAM.D1_8 &= ~T8_MASK;
        break;
    }
  }
}

void LCD_MODE_SHOWS(signed char mode,FunctionalState NewState)//ģʽ��ʾ
{
  if(NewState==DISABLE)
  {
    LCD_RAM.D9_16 &= ~L5_MASK;//��ʾ����
    LCD_RAM.D9_16 &= ~L4_MASK;//����
    LCD_RAM.D9_16 &= ~L1_MASK;//ǰ��˪
    LCD_RAM.D9_16 &= ~L2_MASK;//����
  }
  else
  {
    LCD_RAM.D9_16 |= L5_MASK;//��ʾ����
    switch(mode)
    {
      case MODEFACE:
        LCD_RAM.D9_16 |= L4_MASK;//����
        LCD_RAM.D9_16 &= ~L1_MASK;//ǰ��˪
        LCD_RAM.D9_16 &= ~L2_MASK;//����
        break;
      case MODEFAFE:
        LCD_RAM.D9_16 |= L4_MASK;//����
        LCD_RAM.D9_16 &= ~L1_MASK;//ǰ��˪
        LCD_RAM.D9_16 |= L2_MASK;//����
        break;
      case MODEFEET:
        LCD_RAM.D9_16 &= ~L4_MASK;//����
        LCD_RAM.D9_16 &= ~L1_MASK;//ǰ��˪
        LCD_RAM.D9_16 |= L2_MASK;//����
        break;
      case MODEFEDE:
        LCD_RAM.D9_16 &= ~L4_MASK;//����
        LCD_RAM.D9_16 |= L1_MASK;//ǰ��˪
        LCD_RAM.D9_16 |= L2_MASK;//����
        break;
      case MODEDEF:
        LCD_RAM.D9_16 &= ~L4_MASK;//����
        LCD_RAM.D9_16 |= L1_MASK;//ǰ��˪
        LCD_RAM.D9_16 &= ~L2_MASK;//����
        break;
      default:
        break;
    }
  }
}

void LCD_AC_SHOWS(FunctionalState NewState)//ǰ��˪
{
  if(NewState==DISABLE)
  {
    LCD_RAM.D9_16 &=~L3_MASK;
  }
  else
  {
    LCD_RAM.D9_16 |= L3_MASK;
  }
}

void LCD_FDEF2_SHOWS(FunctionalState NewState)//ǰ��������ʾ
{
  if(NewState==DISABLE)
  {
    LCD_RAM.D17_24 &=~M4_MASK;
  }
  else
  {
    LCD_RAM.D17_24 |= M4_MASK;
  }
}

void LCD_RDEF_SHOWS(FunctionalState NewState)//�󵵼�����ʾ
{
  if(NewState==DISABLE)
  {
    LCD_RAM.D17_24 &=~M1_MASK;
  }
  else
  {
    LCD_RAM.D17_24 |= M1_MASK;
  }
}

void LCD_AUTO_SHOWS(FunctionalState NewState)//AUTO��ʾ
{
  if(NewState==DISABLE)
  {
    LCD_RAM.D17_24 &=~M3_MASK;
  }
  else
  {
    LCD_RAM.D17_24 |= M3_MASK;
  }
}

void LCD_SET_SHOWS(u16 temper,FunctionalState NewState)//�趨�¶���ʾ���¶�*10
{
  if(NewState==DISABLE)
  {
    LCD_RAM.D83_90 &= ~P4_MASK;//С����
    LCD_RAM.D75_82 &= ~P3_MASK;//��
    
    LCD_RAM.D54_61 &= ~A3_MASK;
    LCD_RAM.D54_61 &= ~B3_MASK;
    LCD_RAM.D62_69 &= ~C3_MASK;
    LCD_RAM.D54_61 &= ~D3_MASK;
    LCD_RAM.D54_61 &= ~E3_MASK;
    LCD_RAM.D46_53 &= ~F3_MASK;
    LCD_RAM.D54_61 &= ~G3_MASK;
    
    LCD_RAM.D62_69 &= ~A4_MASK;
    LCD_RAM.D70_74 &= ~B4_MASK;
    LCD_RAM.D70_74 &= ~C4_MASK;
    LCD_RAM.D70_74 &= ~D4_MASK;
    LCD_RAM.D62_69 &= ~E4_MASK;
    LCD_RAM.D62_69 &= ~F4_MASK;
    LCD_RAM.D70_74 &= ~G4_MASK;
                      
    LCD_RAM.D83_90 &= ~A5_MASK;
    LCD_RAM.D83_90 &= ~B5_MASK;
    LCD_RAM.D83_90 &= ~C5_MASK;
    LCD_RAM.D83_90 &= ~D5_MASK;
    LCD_RAM.D75_82 &= ~E5_MASK;
    LCD_RAM.D75_82 &= ~F5_MASK;
    LCD_RAM.D83_90 &= ~G5_MASK;
  }
  else
  {
    if(temper>=MAX_TEMSET)
    {
      LCD_RAM.D83_90 &= ~P4_MASK;//С����
      LCD_RAM.D75_82 &= ~P3_MASK;//��
      
      LCD_RAM.D54_61 &=~A3_MASK;//H
      LCD_RAM.D54_61 |= B3_MASK;
      LCD_RAM.D62_69 |= C3_MASK;
      LCD_RAM.D54_61 &=~D3_MASK;
      LCD_RAM.D54_61 |= E3_MASK;
      LCD_RAM.D46_53 |= F3_MASK;
      LCD_RAM.D54_61 |= G3_MASK;

      LCD_RAM.D62_69 &=~A4_MASK;//1
      LCD_RAM.D70_74 |= B4_MASK;
      LCD_RAM.D70_74 |= C4_MASK;
      LCD_RAM.D70_74 &=~D4_MASK;
      LCD_RAM.D62_69 &=~E4_MASK;
      LCD_RAM.D62_69 &=~F4_MASK;
      LCD_RAM.D70_74 &=~G4_MASK;

      LCD_RAM.D83_90 &=~A5_MASK;//��
      LCD_RAM.D83_90 &=~B5_MASK;
      LCD_RAM.D83_90 &=~C5_MASK;
      LCD_RAM.D83_90 &=~D5_MASK;
      LCD_RAM.D75_82 &=~E5_MASK;
      LCD_RAM.D75_82 &=~F5_MASK;
      LCD_RAM.D83_90 &=~G5_MASK;
    }
    else if(temper<=MIN_TEMSET)
    {
      LCD_RAM.D83_90 &= ~P4_MASK;//С����
      LCD_RAM.D75_82 &= ~P3_MASK;//��
      
      LCD_RAM.D54_61 &=~A3_MASK;//L
      LCD_RAM.D54_61 &=~B3_MASK;
      LCD_RAM.D62_69 &=~C3_MASK;
      LCD_RAM.D54_61 |= D3_MASK;
      LCD_RAM.D54_61 |= E3_MASK;
      LCD_RAM.D46_53 |= F3_MASK;
      LCD_RAM.D54_61 &=~G3_MASK;
      
      LCD_RAM.D62_69 &=~A4_MASK;//o
      LCD_RAM.D70_74 &=~B4_MASK;
      LCD_RAM.D70_74 |= C4_MASK;
      LCD_RAM.D70_74 |= D4_MASK;
      LCD_RAM.D62_69 |= E4_MASK;
      LCD_RAM.D62_69 &=~F4_MASK;
      LCD_RAM.D70_74 |= G4_MASK;
    
      LCD_RAM.D83_90 &=~A5_MASK;//��
      LCD_RAM.D83_90 &=~B5_MASK;
      LCD_RAM.D83_90 &=~C5_MASK;
      LCD_RAM.D83_90 &=~D5_MASK;
      LCD_RAM.D75_82 &=~E5_MASK;
      LCD_RAM.D75_82 &=~F5_MASK;
      LCD_RAM.D83_90 &=~G5_MASK;
    }
    else
    {
      LCD_RAM.D75_82 |= P3_MASK;//��
      LCD_RAM.D83_90 |= P4_MASK;//С����
      switch (temper/100%10)
      {
        case 0:
          LCD_RAM.D54_61 |= A3_MASK;
          LCD_RAM.D54_61 |= B3_MASK;
          LCD_RAM.D62_69 |= C3_MASK;
          LCD_RAM.D54_61 |= D3_MASK;
          LCD_RAM.D54_61 |= E3_MASK;
          LCD_RAM.D46_53 |= F3_MASK;
          LCD_RAM.D54_61 &=~G3_MASK;      
          break;
        case 1: 
          LCD_RAM.D54_61 &=~A3_MASK;
          LCD_RAM.D54_61 |= B3_MASK;
          LCD_RAM.D62_69 |= C3_MASK;
          LCD_RAM.D54_61 &=~D3_MASK;
          LCD_RAM.D54_61 &=~E3_MASK;
          LCD_RAM.D46_53 &=~F3_MASK;
          LCD_RAM.D54_61 &=~G3_MASK;
          break;
        case 2:
          LCD_RAM.D54_61 |= A3_MASK;
          LCD_RAM.D54_61 |= B3_MASK;
          LCD_RAM.D62_69 &=~C3_MASK;
          LCD_RAM.D54_61 |= D3_MASK;
          LCD_RAM.D54_61 |= E3_MASK;
          LCD_RAM.D46_53 &=~F3_MASK;
          LCD_RAM.D54_61 |= G3_MASK;
          break;
        case 3:
          LCD_RAM.D54_61 |= A3_MASK;
          LCD_RAM.D54_61 |= B3_MASK;
          LCD_RAM.D62_69 |= C3_MASK;
          LCD_RAM.D54_61 |= D3_MASK;
          LCD_RAM.D54_61 &=~E3_MASK;
          LCD_RAM.D46_53 &=~F3_MASK;
          LCD_RAM.D54_61 |= G3_MASK;
          break;
        case 4:
          LCD_RAM.D54_61 &=~A3_MASK;
          LCD_RAM.D54_61 |= B3_MASK;
          LCD_RAM.D62_69 |= C3_MASK;
          LCD_RAM.D54_61 &=~D3_MASK;
          LCD_RAM.D54_61 &=~E3_MASK;
          LCD_RAM.D46_53 |= F3_MASK;
          LCD_RAM.D54_61 |= G3_MASK;
          break;
        case 5:
          LCD_RAM.D54_61 |= A3_MASK;
          LCD_RAM.D54_61 &=~B3_MASK;
          LCD_RAM.D62_69 |= C3_MASK;
          LCD_RAM.D54_61 |= D3_MASK;
          LCD_RAM.D54_61 &=~E3_MASK;
          LCD_RAM.D46_53 |= F3_MASK;
          LCD_RAM.D54_61 |= G3_MASK;
          break;
        case 6:
          LCD_RAM.D54_61 |= A3_MASK;
          LCD_RAM.D54_61 &=~B3_MASK;
          LCD_RAM.D62_69 |= C3_MASK;
          LCD_RAM.D54_61 |= D3_MASK;
          LCD_RAM.D54_61 |= E3_MASK;
          LCD_RAM.D46_53 |= F3_MASK;
          LCD_RAM.D54_61 |= G3_MASK;
          break;
        case 7:
          LCD_RAM.D54_61 |= A3_MASK;
          LCD_RAM.D54_61 |= B3_MASK;
          LCD_RAM.D62_69 |= C3_MASK;
          LCD_RAM.D54_61 &=~D3_MASK;
          LCD_RAM.D54_61 &=~E3_MASK;
          LCD_RAM.D46_53 &=~F3_MASK;
          LCD_RAM.D54_61 &=~G3_MASK;
          break;
        case 8:
          LCD_RAM.D54_61 |= A3_MASK;
          LCD_RAM.D54_61 |= B3_MASK;
          LCD_RAM.D62_69 |= C3_MASK;
          LCD_RAM.D54_61 |= D3_MASK;
          LCD_RAM.D54_61 |= E3_MASK;
          LCD_RAM.D46_53 |= F3_MASK;
          LCD_RAM.D54_61 |= G3_MASK;
          break;
        case 9:
          LCD_RAM.D54_61 |= A3_MASK;
          LCD_RAM.D54_61 |= B3_MASK;
          LCD_RAM.D62_69 |= C3_MASK;
          LCD_RAM.D54_61 |= D3_MASK;
          LCD_RAM.D54_61 &=~E3_MASK;
          LCD_RAM.D46_53 |= F3_MASK;
          LCD_RAM.D54_61 |= G3_MASK;
          break;
        default:
          break;
      }
      switch(temper/10%10)
      {
        case 0:
          LCD_RAM.D62_69 |= A4_MASK;
          LCD_RAM.D70_74 |= B4_MASK;
          LCD_RAM.D70_74 |= C4_MASK;
          LCD_RAM.D70_74 |= D4_MASK;
          LCD_RAM.D62_69 |= E4_MASK;
          LCD_RAM.D62_69 |= F4_MASK;
          LCD_RAM.D70_74 &=~G4_MASK;       
          break; 
        case 1:  
          LCD_RAM.D62_69 &=~A4_MASK;
          LCD_RAM.D70_74 |= B4_MASK;
          LCD_RAM.D70_74 |= C4_MASK;
          LCD_RAM.D70_74 &=~D4_MASK;
          LCD_RAM.D62_69 &=~E4_MASK;
          LCD_RAM.D62_69 &=~F4_MASK;
          LCD_RAM.D70_74 &=~G4_MASK;
          break; 
        case 2:  
          LCD_RAM.D62_69 |= A4_MASK;
          LCD_RAM.D70_74 |= B4_MASK;
          LCD_RAM.D70_74 &=~C4_MASK;
          LCD_RAM.D70_74 |= D4_MASK;
          LCD_RAM.D62_69 |= E4_MASK;
          LCD_RAM.D62_69 &=~F4_MASK;
          LCD_RAM.D70_74 |= G4_MASK;
          break; 
        case 3:  
          LCD_RAM.D62_69 |= A4_MASK;
          LCD_RAM.D70_74 |= B4_MASK;
          LCD_RAM.D70_74 |= C4_MASK;
          LCD_RAM.D70_74 |= D4_MASK;
          LCD_RAM.D62_69 &=~E4_MASK;
          LCD_RAM.D62_69 &=~F4_MASK;
          LCD_RAM.D70_74 |= G4_MASK;
          break; 
        case 4:  
          LCD_RAM.D62_69 &=~A4_MASK;
          LCD_RAM.D70_74 |= B4_MASK;
          LCD_RAM.D70_74 |= C4_MASK;
          LCD_RAM.D70_74 &=~D4_MASK;
          LCD_RAM.D62_69 &=~E4_MASK;
          LCD_RAM.D62_69 |= F4_MASK;
          LCD_RAM.D70_74 |= G4_MASK;
          break; 
        case 5:  
          LCD_RAM.D62_69 |= A4_MASK;
          LCD_RAM.D70_74 &=~B4_MASK;
          LCD_RAM.D70_74 |= C4_MASK;
          LCD_RAM.D70_74 |= D4_MASK;
          LCD_RAM.D62_69 &=~E4_MASK;
          LCD_RAM.D62_69 |= F4_MASK;
          LCD_RAM.D70_74 |= G4_MASK;
          break;         
        case 6:          
          LCD_RAM.D62_69 |= A4_MASK;
          LCD_RAM.D70_74 &=~B4_MASK;
          LCD_RAM.D70_74 |= C4_MASK;
          LCD_RAM.D70_74 |= D4_MASK;
          LCD_RAM.D62_69 |= E4_MASK;
          LCD_RAM.D62_69 |= F4_MASK;
          LCD_RAM.D70_74 |= G4_MASK;
          break; 
        case 7:  
          LCD_RAM.D62_69 |= A4_MASK;
          LCD_RAM.D70_74 |= B4_MASK;
          LCD_RAM.D70_74 |= C4_MASK;
          LCD_RAM.D70_74 &=~D4_MASK;
          LCD_RAM.D62_69 &=~E4_MASK;
          LCD_RAM.D62_69 &=~F4_MASK;
          LCD_RAM.D70_74 &=~G4_MASK;
          break; 
        case 8:  
          LCD_RAM.D62_69 |= A4_MASK;
          LCD_RAM.D70_74 |= B4_MASK;
          LCD_RAM.D70_74 |= C4_MASK;
          LCD_RAM.D70_74 |= D4_MASK;
          LCD_RAM.D62_69 |= E4_MASK;
          LCD_RAM.D62_69 |= F4_MASK;
          LCD_RAM.D70_74 |= G4_MASK;
          break; 
        case 9:  
          LCD_RAM.D62_69 |= A4_MASK;
          LCD_RAM.D70_74 |= B4_MASK;
          LCD_RAM.D70_74 |= C4_MASK;
          LCD_RAM.D70_74 |= D4_MASK;
          LCD_RAM.D62_69 &=~E4_MASK;
          LCD_RAM.D62_69 |= F4_MASK;
          LCD_RAM.D70_74 |= G4_MASK;
          break;
        default:
          break;
      }
      switch(temper%10)
      {
        case 0:
          LCD_RAM.D83_90 |= A5_MASK;
          LCD_RAM.D83_90 |= B5_MASK;
          LCD_RAM.D83_90 |= C5_MASK;
          LCD_RAM.D83_90 |= D5_MASK;
          LCD_RAM.D75_82 |= E5_MASK;
          LCD_RAM.D75_82 |= F5_MASK;
          LCD_RAM.D83_90 &=~G5_MASK;       
          break; 
        case 1:  
          LCD_RAM.D83_90 &=~A5_MASK;
          LCD_RAM.D83_90 |= B5_MASK;
          LCD_RAM.D83_90 |= C5_MASK;
          LCD_RAM.D83_90 &=~D5_MASK;
          LCD_RAM.D75_82 &=~E5_MASK;
          LCD_RAM.D75_82 &=~F5_MASK;
          LCD_RAM.D83_90 &=~G5_MASK;
          break; 
        case 2:  
          LCD_RAM.D83_90 |= A5_MASK;
          LCD_RAM.D83_90 |= B5_MASK;
          LCD_RAM.D83_90 &=~C5_MASK;
          LCD_RAM.D83_90 |= D5_MASK;
          LCD_RAM.D75_82 |= E5_MASK;
          LCD_RAM.D75_82 &=~F5_MASK;
          LCD_RAM.D83_90 |= G5_MASK;
          break; 
        case 3:  
          LCD_RAM.D83_90 |= A5_MASK;
          LCD_RAM.D83_90 |= B5_MASK;
          LCD_RAM.D83_90 |= C5_MASK;
          LCD_RAM.D83_90 |= D5_MASK;
          LCD_RAM.D75_82 &=~E5_MASK;
          LCD_RAM.D75_82 &=~F5_MASK;
          LCD_RAM.D83_90 |= G5_MASK;
          break; 
        case 4:  
          LCD_RAM.D83_90 &=~A5_MASK;
          LCD_RAM.D83_90 |= B5_MASK;
          LCD_RAM.D83_90 |= C5_MASK;
          LCD_RAM.D83_90 &=~D5_MASK;
          LCD_RAM.D75_82 &=~E5_MASK;
          LCD_RAM.D75_82 |= F5_MASK;
          LCD_RAM.D83_90 |= G5_MASK;
          break; 
        case 5:  
          LCD_RAM.D83_90 |= A5_MASK;
          LCD_RAM.D83_90 &=~B5_MASK;
          LCD_RAM.D83_90 |= C5_MASK;
          LCD_RAM.D83_90 |= D5_MASK;
          LCD_RAM.D75_82 &=~E5_MASK;
          LCD_RAM.D75_82 |= F5_MASK;
          LCD_RAM.D83_90 |= G5_MASK;
          break;         
        case 6:          
          LCD_RAM.D83_90 |= A5_MASK;
          LCD_RAM.D83_90 &=~B5_MASK;
          LCD_RAM.D83_90 |= C5_MASK;
          LCD_RAM.D83_90 |= D5_MASK;
          LCD_RAM.D75_82 |= E5_MASK;
          LCD_RAM.D75_82 |= F5_MASK;
          LCD_RAM.D83_90 |= G5_MASK;
          break; 
        case 7:  
          LCD_RAM.D83_90 |= A5_MASK;
          LCD_RAM.D83_90 |= B5_MASK;
          LCD_RAM.D83_90 |= C5_MASK;
          LCD_RAM.D83_90 &=~D5_MASK;
          LCD_RAM.D75_82 &=~E5_MASK;
          LCD_RAM.D75_82 &=~F5_MASK;
          LCD_RAM.D83_90 &=~G5_MASK;
          break; 
        case 8:  
          LCD_RAM.D83_90 |= A5_MASK;
          LCD_RAM.D83_90 |= B5_MASK;
          LCD_RAM.D83_90 |= C5_MASK;
          LCD_RAM.D83_90 |= D5_MASK;
          LCD_RAM.D75_82 |= E5_MASK;
          LCD_RAM.D75_82 |= F5_MASK;
          LCD_RAM.D83_90 |= G5_MASK;
          break; 
        case 9:  
          LCD_RAM.D83_90 |= A5_MASK;
          LCD_RAM.D83_90 |= B5_MASK;
          LCD_RAM.D83_90 |= C5_MASK;
          LCD_RAM.D83_90 |= D5_MASK;
          LCD_RAM.D75_82 &=~E5_MASK;
          LCD_RAM.D75_82 |= F5_MASK;
          LCD_RAM.D83_90 |= G5_MASK;
          break;
        default:
          break;
      }
    }
  }
}

void LCD_OUTSIDE_SHOWS(int16_t temper,FunctionalState NewState)//������ʾ
{
  if(NewState==DISABLE)
  {
    LCD_RAM.D17_24 &= ~M2_MASK;//OUTSIDE
    LCD_RAM.D25_32 &= ~P2_MASK;//����
    LCD_RAM.D46_53 &= ~P1_MASK;//��
    
    LCD_RAM.D25_32 &= ~A1_MASK;//??
    LCD_RAM.D33_37 &= ~B1_MASK;
    LCD_RAM.D33_37 &= ~C1_MASK;//??
    LCD_RAM.D25_32 &= ~D1_MASK;
    LCD_RAM.D25_32 &= ~E1_MASK;
    LCD_RAM.D25_32 &= ~F1_MASK;
    LCD_RAM.D25_32 &= ~G1_MASK;
    
    LCD_RAM.D38_45 &= ~A2_MASK;
    LCD_RAM.D38_45 &= ~B2_MASK;
    LCD_RAM.D46_53 &= ~C2_MASK;
    LCD_RAM.D38_45 &= ~D2_MASK;
    LCD_RAM.D38_45 &= ~E2_MASK;
    LCD_RAM.D33_37 &= ~F2_MASK;
    LCD_RAM.D38_45 &= ~G2_MASK;
  }
  else
  {
		if(temper>0)
		{
			if(temper%10 >4)
			{
				temper=temper/10+1;
			}
			else
			{
				temper=temper/10;
			}
		}
		else
		{
			if(temper%10 <-4)
			{
				temper=temper/10-1;
			}
			else
			{
				temper=temper/10;
			}
		}
    LCD_RAM.D17_24 |= M2_MASK; //OUTSIDE
    LCD_RAM.D46_53 |= P1_MASK; //��
    
    if((temper<-99) || (temper>99))
    {
      LCD_RAM.D25_32 &= ~P2_MASK;//����
      
      LCD_RAM.D25_32 &= ~A1_MASK;//??
      LCD_RAM.D33_37 &= ~B1_MASK;
      LCD_RAM.D33_37 &= ~C1_MASK;//??
      LCD_RAM.D25_32 &= ~D1_MASK;
      LCD_RAM.D25_32 &= ~E1_MASK;
      LCD_RAM.D25_32 &= ~F1_MASK;
      LCD_RAM.D25_32 |=  G1_MASK;
      
      LCD_RAM.D38_45 &= ~A2_MASK;
      LCD_RAM.D38_45 &= ~B2_MASK;
      LCD_RAM.D46_53 &= ~C2_MASK;
      LCD_RAM.D38_45 &= ~D2_MASK;
      LCD_RAM.D38_45 &= ~E2_MASK;
      LCD_RAM.D33_37 &= ~F2_MASK;
      LCD_RAM.D38_45 |=  G2_MASK;
    }
    else
    {
      if(temper<0)
      {
        LCD_RAM.D25_32 |= P2_MASK;//����
				temper=0-temper;
      }
      else
      {
        LCD_RAM.D25_32 &= ~P2_MASK;//����
      }
      switch(temper/10%10)
      {
        case 0: //����ʮλ 0
          LCD_RAM.D25_32 |= A1_MASK;
          LCD_RAM.D33_37 |= B1_MASK;
          LCD_RAM.D33_37 |= C1_MASK;
          LCD_RAM.D25_32 |= D1_MASK;
          LCD_RAM.D25_32 |= E1_MASK;
          LCD_RAM.D25_32 |= F1_MASK;
          LCD_RAM.D25_32 &= ~G1_MASK;
          break;
        case 1://����ʮλ 1  
          LCD_RAM.D25_32 &= ~A1_MASK;
          LCD_RAM.D33_37 |= B1_MASK;
          LCD_RAM.D33_37 |= C1_MASK;
          LCD_RAM.D25_32 &= ~D1_MASK;
          LCD_RAM.D25_32 &= ~E1_MASK;
          LCD_RAM.D25_32 &= ~F1_MASK;
          LCD_RAM.D25_32 &= ~G1_MASK;
          break;
        case 2://����ʮλ 2 
          LCD_RAM.D25_32 |= A1_MASK;
          LCD_RAM.D33_37 |= B1_MASK;
          LCD_RAM.D33_37 &= ~C1_MASK;
          LCD_RAM.D25_32 |= D1_MASK;
          LCD_RAM.D25_32 |= E1_MASK;
          LCD_RAM.D25_32 &= ~F1_MASK;
          LCD_RAM.D25_32 |= G1_MASK;
          break;
        case 3://����ʮλ 3 
          LCD_RAM.D25_32 |= A1_MASK;
          LCD_RAM.D33_37 |= B1_MASK;
          LCD_RAM.D33_37 |= C1_MASK;
          LCD_RAM.D25_32 |= D1_MASK;
          LCD_RAM.D25_32 &= ~E1_MASK;
          LCD_RAM.D25_32 &= ~F1_MASK;
          LCD_RAM.D25_32 |= G1_MASK;
          break;
        case 4://����ʮλ4
          LCD_RAM.D25_32 &= ~A1_MASK;
          LCD_RAM.D33_37 |= B1_MASK;
          LCD_RAM.D33_37 |= C1_MASK;
          LCD_RAM.D25_32 &= ~D1_MASK;
          LCD_RAM.D25_32 &= ~E1_MASK;
          LCD_RAM.D25_32 |= F1_MASK;
          LCD_RAM.D25_32 |= G1_MASK;
          break;
        case 5://����ʮλ5
          LCD_RAM.D25_32 |= A1_MASK;
          LCD_RAM.D33_37 &=~B1_MASK;
          LCD_RAM.D33_37 |= C1_MASK;
          LCD_RAM.D25_32 |= D1_MASK;
          LCD_RAM.D25_32 &=~E1_MASK;
          LCD_RAM.D25_32 |= F1_MASK;
          LCD_RAM.D25_32 |= G1_MASK;
          break;         
        case 6: //����ʮ�
          LCD_RAM.D25_32 |= A1_MASK;
          LCD_RAM.D33_37 &=~B1_MASK;
          LCD_RAM.D33_37 |= C1_MASK;
          LCD_RAM.D25_32 |= D1_MASK;
          LCD_RAM.D25_32 |= E1_MASK;
          LCD_RAM.D25_32 |= F1_MASK;
          LCD_RAM.D25_32 |= G1_MASK;
          break;
        case 7://����ʮλ7
          LCD_RAM.D25_32 |= A1_MASK;
          LCD_RAM.D33_37 |= B1_MASK;
          LCD_RAM.D33_37 |= C1_MASK;
          LCD_RAM.D25_32 &= ~D1_MASK;
          LCD_RAM.D25_32 &= ~E1_MASK;
          LCD_RAM.D25_32 &= ~F1_MASK;
          LCD_RAM.D25_32 &= ~G1_MASK;
          break;
        case 8://����ʮλ8
          LCD_RAM.D25_32 |= A1_MASK;
          LCD_RAM.D33_37 |= B1_MASK;
          LCD_RAM.D33_37 |= C1_MASK;
          LCD_RAM.D25_32 |= D1_MASK;
          LCD_RAM.D25_32 |= E1_MASK;
          LCD_RAM.D25_32 |= F1_MASK;
          LCD_RAM.D25_32 |= G1_MASK;
          break;
        case 9: //����ʮλ9
          LCD_RAM.D25_32 |= A1_MASK;
          LCD_RAM.D33_37 |= B1_MASK;
          LCD_RAM.D33_37 |= C1_MASK;
          LCD_RAM.D25_32 |= D1_MASK;
          LCD_RAM.D25_32 &= ~E1_MASK;
          LCD_RAM.D25_32 |= F1_MASK;
          LCD_RAM.D25_32 |= G1_MASK;
          break;
        default:
          break;
      }
      switch(temper%10)
      {
       case 0: //���¸�λ 0
          LCD_RAM.D38_45 |= A2_MASK;
          LCD_RAM.D38_45 |= B2_MASK;
          LCD_RAM.D46_53 |= C2_MASK;
          LCD_RAM.D38_45 |= D2_MASK;
          LCD_RAM.D38_45 |= E2_MASK;
          LCD_RAM.D33_37 |= F2_MASK;
          LCD_RAM.D38_45 &=~G2_MASK;
          break;
        case 1://���¸�λ 1  
          LCD_RAM.D38_45 &=~A2_MASK;
          LCD_RAM.D38_45 |= B2_MASK;
          LCD_RAM.D46_53 |= C2_MASK;
          LCD_RAM.D38_45 &=~D2_MASK;
          LCD_RAM.D38_45 &=~E2_MASK;
          LCD_RAM.D33_37 &=~F2_MASK;
          LCD_RAM.D38_45 &=~G2_MASK;
          break;
        case 2://���¸�λ 2 
          LCD_RAM.D38_45 |= A2_MASK;
          LCD_RAM.D38_45 |= B2_MASK;
          LCD_RAM.D46_53 &=~C2_MASK;
          LCD_RAM.D38_45 |= D2_MASK;
          LCD_RAM.D38_45 |= E2_MASK;
          LCD_RAM.D33_37 &=~F2_MASK;
          LCD_RAM.D38_45 |= G2_MASK;
          break;
        case 3://���¸�λ 3 
          LCD_RAM.D38_45 |= A2_MASK;
          LCD_RAM.D38_45 |= B2_MASK;
          LCD_RAM.D46_53 |= C2_MASK;
          LCD_RAM.D38_45 |= D2_MASK;
          LCD_RAM.D38_45 &=~E2_MASK;
          LCD_RAM.D33_37 &=~F2_MASK;
          LCD_RAM.D38_45 |= G2_MASK;
          break;
        case 4://���¸�λ4
          LCD_RAM.D38_45 &=~A2_MASK;
          LCD_RAM.D38_45 |= B2_MASK;
          LCD_RAM.D46_53 |= C2_MASK;
          LCD_RAM.D38_45 &=~D2_MASK;
          LCD_RAM.D38_45 &=~E2_MASK;
          LCD_RAM.D33_37 |= F2_MASK;
          LCD_RAM.D38_45 |= G2_MASK;
          break;
        case 5://���¸�λ5
          LCD_RAM.D38_45 |= A2_MASK;
          LCD_RAM.D38_45 &=~B2_MASK;
          LCD_RAM.D46_53 |= C2_MASK;
          LCD_RAM.D38_45 |= D2_MASK;
          LCD_RAM.D38_45 &=~E2_MASK;
          LCD_RAM.D33_37 |= F2_MASK;
          LCD_RAM.D38_45 |= G2_MASK;
          break;         
        case 6: //���¸��
          LCD_RAM.D38_45 |= A2_MASK;
          LCD_RAM.D38_45 &=~B2_MASK;
          LCD_RAM.D46_53 |= C2_MASK;
          LCD_RAM.D38_45 |= D2_MASK;
          LCD_RAM.D38_45 |= E2_MASK;
          LCD_RAM.D33_37 |= F2_MASK;
          LCD_RAM.D38_45 |= G2_MASK;
          break;
        case 7://���¸�λ7
          LCD_RAM.D38_45 |= A2_MASK;
          LCD_RAM.D38_45 |= B2_MASK;
          LCD_RAM.D46_53 |= C2_MASK;
          LCD_RAM.D38_45 &=~D2_MASK;
          LCD_RAM.D38_45 &=~E2_MASK;
          LCD_RAM.D33_37 &=~F2_MASK;
          LCD_RAM.D38_45 &=~G2_MASK;
          break;
        case 8://���¸�λ8
          LCD_RAM.D38_45 |= A2_MASK;
          LCD_RAM.D38_45 |= B2_MASK;
          LCD_RAM.D46_53 |= C2_MASK;
          LCD_RAM.D38_45 |= D2_MASK;
          LCD_RAM.D38_45 |= E2_MASK;
          LCD_RAM.D33_37 |= F2_MASK;
          LCD_RAM.D38_45 |= G2_MASK;
          break;
        case 9: //���¸�λ9
          LCD_RAM.D38_45 |= A2_MASK;
          LCD_RAM.D38_45 |= B2_MASK;
          LCD_RAM.D46_53 |= C2_MASK;
          LCD_RAM.D38_45 |= D2_MASK;
          LCD_RAM.D38_45 &=~E2_MASK;
          LCD_RAM.D33_37 |= F2_MASK;
          LCD_RAM.D38_45 |= G2_MASK;
          break;
        default:
          break;
      }
    }
  }
}

void LCD_Display_Updata(void)//LCDˢ����ʾ
{
  LCD_SEL_H();
	LCD_SEL_L();
	LCD_V_SPI_RW(0x46);//Device code
  LCD_SEL_H();
  
	LCD_V_SPI_RW(LCD_RAM.D1_8);
	LCD_V_SPI_RW(LCD_RAM.D9_16);
	LCD_V_SPI_RW(LCD_RAM.D17_24);
	LCD_V_SPI_RW(LCD_RAM.D25_32);
	LCD_V_SPI_RW(LCD_RAM.D33_37);

	LCD_V_SPI_RW(0x00);//S23 KS2 KS3 KS4 KS5 of Input key
	LCD_V_SPI_RW(0x01);
	LCD_V_SPI_RW(0x0F);//Ƶ��530Hz
	LCD_V_SPI_RW(0x00);

	LCD_SEL_L();
	LCD_V_SPI_RW(0x46);
  LCD_SEL_H();
  
	LCD_V_SPI_RW(LCD_RAM.D38_45);
	LCD_V_SPI_RW(LCD_RAM.D46_53);
	LCD_V_SPI_RW(LCD_RAM.D54_61);
	LCD_V_SPI_RW(LCD_RAM.D62_69);
	LCD_V_SPI_RW(LCD_RAM.D70_74);
	
	LCD_V_SPI_RW(0x00);
	LCD_V_SPI_RW(0x00);
	LCD_V_SPI_RW(0x00);
	LCD_V_SPI_RW(0x80);

	LCD_SEL_L();
	LCD_V_SPI_RW(0x46);
  LCD_SEL_H();
	
	LCD_V_SPI_RW(LCD_RAM.D75_82);
	LCD_V_SPI_RW(LCD_RAM.D83_90);
	LCD_V_SPI_RW(LCD_RAM.D91_98);
	LCD_V_SPI_RW(LCD_RAM.D99_106);
	LCD_V_SPI_RW(LCD_RAM.D107_111);
  
	LCD_V_SPI_RW(0x00);
	LCD_V_SPI_RW(0x00);
	LCD_V_SPI_RW(0x00);
	LCD_V_SPI_RW(0x40);

	LCD_SEL_L();
}

void Key_Input_Scan(void)//��������
{
  u8 data_read=0;
  if(KEY_READ_REQUEST)
  {
    KEY_READ_REQUEST=0;
    LCD_SEL_L();
    LCD_V_SPI_RW(0x43);//Device code
    LCD_SEL_H();
    
    data_read=LCD_V_SPI_RW(0x00);
    if(data_read & (1<<5))
    {
      Key_Value |=KEYAUTO_Pressed_MASK;
    }
    if(data_read & (1<<6))
    {
      Key_Value |=KEYFDEF_Pressed_MASK;
    }
    if(data_read & (1<<7))
    {
      Key_Value |=KEYAC_Pressed_MASK;
    }
    
    data_read=LCD_V_SPI_RW(0x00);
    if(data_read & (1<<0))
    {
      Key_Value |=KEYFDEF2_Pressed_MASK;
    }
    if(data_read & (1<<1))
    {
      Key_Value |=KEYSEATL_Pressed_MASK;
    }
    if(data_read & (1<<2))
    {
      Key_Value |=KEYMODE_Pressed_MASK;
    }
    if(data_read & (1<<4))
    {
      Key_Value |=KEYSEATR_Pressed_MASK;
    }
    if(data_read & (1<<5))
    {
      Key_Value |=KEYRDEF_Pressed_MASK;
    }
    if(data_read & (1<<6))
    {
      Key_Value |=KEYREC_Pressed_MASK;
    }
    if(data_read & (1<<7))
    {
      Key_Value |=KEYOFF_Pressed_MASK;
    }
    
    data_read=LCD_V_SPI_RW(0x00);
    if(data_read & (1<<0))
    {
      Key_Value |=KEYDULE_Pressed_MASK;
    }
    
    LCD_SEL_H();//����ʡ��ģʽ�������ɨ��
    LCD_SEL_L();
    LCD_V_SPI_RW(0x46);//Device code
    LCD_SEL_H();
    
    LCD_V_SPI_RW(LCD_RAM.D1_8);
    LCD_V_SPI_RW(LCD_RAM.D9_16);
    LCD_V_SPI_RW(LCD_RAM.D17_24);
    LCD_V_SPI_RW(LCD_RAM.D25_32);
    LCD_V_SPI_RW(LCD_RAM.D33_37);

    LCD_V_SPI_RW(0x00);//S23 KS2 KS3 KS4 KS5 of Input key
    LCD_V_SPI_RW(0x01);
    LCD_V_SPI_RW(0x0F);//Ƶ��530Hz
    LCD_V_SPI_RW(0x38);//ʡ��ģʽ
    
    LCD_V_SPI_RW(LCD_RAM.D1_8);
    LCD_V_SPI_RW(LCD_RAM.D9_16);
    LCD_V_SPI_RW(LCD_RAM.D17_24);
    LCD_V_SPI_RW(LCD_RAM.D25_32);
    LCD_V_SPI_RW(LCD_RAM.D33_37);

    LCD_V_SPI_RW(0x00);//S23 KS2 KS3 KS4 KS5 of Input key
    LCD_V_SPI_RW(0x01);
    LCD_V_SPI_RW(0x0F);//Ƶ��530Hz
    LCD_V_SPI_RW(0x00);//����ģʽ
    
    LCD_SEL_L();
    KBI1_PE |= KBI_PE_KBIPE(1u<<LCD_SPI_MISO_KBI); // Enable KBI1
  }
}

void LCD_Sleep(void)
{
  LCD_SEL_H();
	LCD_SEL_L();
	LCD_V_SPI_RW(0x46);//Device code
  LCD_SEL_H();
  
	LCD_V_SPI_RW(LCD_RAM.D1_8);
	LCD_V_SPI_RW(LCD_RAM.D9_16);
	LCD_V_SPI_RW(LCD_RAM.D17_24);
	LCD_V_SPI_RW(LCD_RAM.D25_32);
	LCD_V_SPI_RW(LCD_RAM.D33_37);

	LCD_V_SPI_RW(0xC0);//S23 KS2 KS3 KS4 KS5 of Input key
	LCD_V_SPI_RW(0x01);
	LCD_V_SPI_RW(0x0F);//Ƶ��530Hz
	LCD_V_SPI_RW(0x3C);
  
  LCD_SEL_L();
}
//end
