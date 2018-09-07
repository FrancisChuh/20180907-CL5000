#include "LCD.h"

u8 KEY_READ_REQUEST=0;
LCD_DIS_TypeDef LCD_RAM;

void LCD_Init(void)//初始显示
{
	s_Heat_Cap.AC_STATUS=0;//AC关闭
	g_AUTO_Flag=AUTO_TEMP_MASK;//AUTO关闭
	s_Heat_Cap.TAKE=REC_INTake;//内循环
	s_Heat_Cap.Set_Fan=0;//风量0
	s_Heat_Cap.Tem_Purpose=250;//设定温度
	s_Heat_Cap.Mode_PPS=MODEFACE;//模式吹面
	s_FDEF_Last.Mode_PPS_Last=MODEFACE;
	s_Heat_Cap.RDEF_STATUS=0;//关后除霜
	s_Heat_Cap.SEATL_STATUS=0;//关闭左座椅加热
	s_Heat_Cap.SEATR_STATUS=0;//关闭右座椅加热
	s_Heat_Cap.FDEF2_STATUS=0;//关闭前挡加热
	s_Heat_Cap.AC_ON_TEM=AC_ON_TEMP_default;//默认启停点
	s_Heat_Cap.AC_OFF_TEM=AC_OFF_TEMP_default;//默认启停点
	
//	LCD_RAM.D9_16 |=L5_MASK;//显示人像
//	LCD_RAM.D9_16 |=N3_MASK;//显示车体
//	LCD_RAM.D17_24 |=N4_MASK;//显示车内一横
//	LCD_RAM.D17_24 |=N1_MASK;//显示外循环
//  LCD_RAM.D9_16 |=L4_MASK;//显示吹面符号
//  LCD_RAM.D17_24 |= M2_MASK; //OUTSIDE
//  LCD_RAM.D46_53 |= P1_MASK; //℃
//  LCD_RAM.D25_32 |= G1_MASK; //--℃
//  LCD_RAM.D38_45 |= G2_MASK; //--℃
//	LCD_Display_Updata();
}

void LCD_REC_SHOWS(signed char rec_val)//内外循环
{
  if(rec_val==0)
  {
		LCD_RAM.D9_16  |=N3_MASK;//显示车体
		LCD_RAM.D17_24 |=N4_MASK;//显示车内一横
    LCD_RAM.D17_24 &=~N1_MASK;//显示内循环
    LCD_RAM.D9_16  |= N2_MASK;//显示内循环
  }
  else
  {
		LCD_RAM.D9_16	 |=N3_MASK;//显示车体
		LCD_RAM.D17_24 |=N4_MASK;//显示车内一横
    LCD_RAM.D17_24 |= N1_MASK;//显示外循环
    LCD_RAM.D9_16	 &=~N2_MASK;//显示外循环
  }
}

void LCD_FANSPEED_SHOWS(u8 level,FunctionalState NewState)//风量
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
      default://0-1档风显示1档风
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

void LCD_MODE_SHOWS(signed char mode,FunctionalState NewState)//模式显示
{
  if(NewState==DISABLE)
  {
    LCD_RAM.D9_16 &= ~L5_MASK;//显示人像
    LCD_RAM.D9_16 &= ~L4_MASK;//吹面
    LCD_RAM.D9_16 &= ~L1_MASK;//前除霜
    LCD_RAM.D9_16 &= ~L2_MASK;//吹脚
  }
  else
  {
    LCD_RAM.D9_16 |= L5_MASK;//显示人像
    switch(mode)
    {
      case MODEFACE:
        LCD_RAM.D9_16 |= L4_MASK;//吹面
        LCD_RAM.D9_16 &= ~L1_MASK;//前除霜
        LCD_RAM.D9_16 &= ~L2_MASK;//吹脚
        break;
      case MODEFAFE:
        LCD_RAM.D9_16 |= L4_MASK;//吹面
        LCD_RAM.D9_16 &= ~L1_MASK;//前除霜
        LCD_RAM.D9_16 |= L2_MASK;//吹脚
        break;
      case MODEFEET:
        LCD_RAM.D9_16 &= ~L4_MASK;//吹面
        LCD_RAM.D9_16 &= ~L1_MASK;//前除霜
        LCD_RAM.D9_16 |= L2_MASK;//吹脚
        break;
      case MODEFEDE:
        LCD_RAM.D9_16 &= ~L4_MASK;//吹面
        LCD_RAM.D9_16 |= L1_MASK;//前除霜
        LCD_RAM.D9_16 |= L2_MASK;//吹脚
        break;
      case MODEDEF:
        LCD_RAM.D9_16 &= ~L4_MASK;//吹面
        LCD_RAM.D9_16 |= L1_MASK;//前除霜
        LCD_RAM.D9_16 &= ~L2_MASK;//吹脚
        break;
      default:
        break;
    }
  }
}

void LCD_AC_SHOWS(FunctionalState NewState)//前除霜
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

void LCD_FDEF2_SHOWS(FunctionalState NewState)//前档加热显示
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

void LCD_RDEF_SHOWS(FunctionalState NewState)//后档加热显示
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

void LCD_AUTO_SHOWS(FunctionalState NewState)//AUTO显示
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

void LCD_SET_SHOWS(u16 temper,FunctionalState NewState)//设定温度显示，温度*10
{
  if(NewState==DISABLE)
  {
    LCD_RAM.D83_90 &= ~P4_MASK;//小数点
    LCD_RAM.D75_82 &= ~P3_MASK;//℃
    
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
      LCD_RAM.D83_90 &= ~P4_MASK;//小数点
      LCD_RAM.D75_82 &= ~P3_MASK;//℃
      
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

      LCD_RAM.D83_90 &=~A5_MASK;//关
      LCD_RAM.D83_90 &=~B5_MASK;
      LCD_RAM.D83_90 &=~C5_MASK;
      LCD_RAM.D83_90 &=~D5_MASK;
      LCD_RAM.D75_82 &=~E5_MASK;
      LCD_RAM.D75_82 &=~F5_MASK;
      LCD_RAM.D83_90 &=~G5_MASK;
    }
    else if(temper<=MIN_TEMSET)
    {
      LCD_RAM.D83_90 &= ~P4_MASK;//小数点
      LCD_RAM.D75_82 &= ~P3_MASK;//℃
      
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
    
      LCD_RAM.D83_90 &=~A5_MASK;//关
      LCD_RAM.D83_90 &=~B5_MASK;
      LCD_RAM.D83_90 &=~C5_MASK;
      LCD_RAM.D83_90 &=~D5_MASK;
      LCD_RAM.D75_82 &=~E5_MASK;
      LCD_RAM.D75_82 &=~F5_MASK;
      LCD_RAM.D83_90 &=~G5_MASK;
    }
    else
    {
      LCD_RAM.D75_82 |= P3_MASK;//℃
      LCD_RAM.D83_90 |= P4_MASK;//小数点
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

void LCD_OUTSIDE_SHOWS(int16_t temper,FunctionalState NewState)//外温显示
{
  if(NewState==DISABLE)
  {
    LCD_RAM.D17_24 &= ~M2_MASK;//OUTSIDE
    LCD_RAM.D25_32 &= ~P2_MASK;//负号
    LCD_RAM.D46_53 &= ~P1_MASK;//℃
    
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
    LCD_RAM.D46_53 |= P1_MASK; //℃
    
    if((temper<-99) || (temper>99))
    {
      LCD_RAM.D25_32 &= ~P2_MASK;//负号
      
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
        LCD_RAM.D25_32 |= P2_MASK;//负号
				temper=0-temper;
      }
      else
      {
        LCD_RAM.D25_32 &= ~P2_MASK;//负号
      }
      switch(temper/10%10)
      {
        case 0: //外温十位 0
          LCD_RAM.D25_32 |= A1_MASK;
          LCD_RAM.D33_37 |= B1_MASK;
          LCD_RAM.D33_37 |= C1_MASK;
          LCD_RAM.D25_32 |= D1_MASK;
          LCD_RAM.D25_32 |= E1_MASK;
          LCD_RAM.D25_32 |= F1_MASK;
          LCD_RAM.D25_32 &= ~G1_MASK;
          break;
        case 1://外温十位 1  
          LCD_RAM.D25_32 &= ~A1_MASK;
          LCD_RAM.D33_37 |= B1_MASK;
          LCD_RAM.D33_37 |= C1_MASK;
          LCD_RAM.D25_32 &= ~D1_MASK;
          LCD_RAM.D25_32 &= ~E1_MASK;
          LCD_RAM.D25_32 &= ~F1_MASK;
          LCD_RAM.D25_32 &= ~G1_MASK;
          break;
        case 2://外温十位 2 
          LCD_RAM.D25_32 |= A1_MASK;
          LCD_RAM.D33_37 |= B1_MASK;
          LCD_RAM.D33_37 &= ~C1_MASK;
          LCD_RAM.D25_32 |= D1_MASK;
          LCD_RAM.D25_32 |= E1_MASK;
          LCD_RAM.D25_32 &= ~F1_MASK;
          LCD_RAM.D25_32 |= G1_MASK;
          break;
        case 3://外温十位 3 
          LCD_RAM.D25_32 |= A1_MASK;
          LCD_RAM.D33_37 |= B1_MASK;
          LCD_RAM.D33_37 |= C1_MASK;
          LCD_RAM.D25_32 |= D1_MASK;
          LCD_RAM.D25_32 &= ~E1_MASK;
          LCD_RAM.D25_32 &= ~F1_MASK;
          LCD_RAM.D25_32 |= G1_MASK;
          break;
        case 4://外温十位4
          LCD_RAM.D25_32 &= ~A1_MASK;
          LCD_RAM.D33_37 |= B1_MASK;
          LCD_RAM.D33_37 |= C1_MASK;
          LCD_RAM.D25_32 &= ~D1_MASK;
          LCD_RAM.D25_32 &= ~E1_MASK;
          LCD_RAM.D25_32 |= F1_MASK;
          LCD_RAM.D25_32 |= G1_MASK;
          break;
        case 5://外温十位5
          LCD_RAM.D25_32 |= A1_MASK;
          LCD_RAM.D33_37 &=~B1_MASK;
          LCD_RAM.D33_37 |= C1_MASK;
          LCD_RAM.D25_32 |= D1_MASK;
          LCD_RAM.D25_32 &=~E1_MASK;
          LCD_RAM.D25_32 |= F1_MASK;
          LCD_RAM.D25_32 |= G1_MASK;
          break;         
        case 6: //外温十�
          LCD_RAM.D25_32 |= A1_MASK;
          LCD_RAM.D33_37 &=~B1_MASK;
          LCD_RAM.D33_37 |= C1_MASK;
          LCD_RAM.D25_32 |= D1_MASK;
          LCD_RAM.D25_32 |= E1_MASK;
          LCD_RAM.D25_32 |= F1_MASK;
          LCD_RAM.D25_32 |= G1_MASK;
          break;
        case 7://外温十位7
          LCD_RAM.D25_32 |= A1_MASK;
          LCD_RAM.D33_37 |= B1_MASK;
          LCD_RAM.D33_37 |= C1_MASK;
          LCD_RAM.D25_32 &= ~D1_MASK;
          LCD_RAM.D25_32 &= ~E1_MASK;
          LCD_RAM.D25_32 &= ~F1_MASK;
          LCD_RAM.D25_32 &= ~G1_MASK;
          break;
        case 8://外温十位8
          LCD_RAM.D25_32 |= A1_MASK;
          LCD_RAM.D33_37 |= B1_MASK;
          LCD_RAM.D33_37 |= C1_MASK;
          LCD_RAM.D25_32 |= D1_MASK;
          LCD_RAM.D25_32 |= E1_MASK;
          LCD_RAM.D25_32 |= F1_MASK;
          LCD_RAM.D25_32 |= G1_MASK;
          break;
        case 9: //外温十位9
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
       case 0: //外温个位 0
          LCD_RAM.D38_45 |= A2_MASK;
          LCD_RAM.D38_45 |= B2_MASK;
          LCD_RAM.D46_53 |= C2_MASK;
          LCD_RAM.D38_45 |= D2_MASK;
          LCD_RAM.D38_45 |= E2_MASK;
          LCD_RAM.D33_37 |= F2_MASK;
          LCD_RAM.D38_45 &=~G2_MASK;
          break;
        case 1://外温个位 1  
          LCD_RAM.D38_45 &=~A2_MASK;
          LCD_RAM.D38_45 |= B2_MASK;
          LCD_RAM.D46_53 |= C2_MASK;
          LCD_RAM.D38_45 &=~D2_MASK;
          LCD_RAM.D38_45 &=~E2_MASK;
          LCD_RAM.D33_37 &=~F2_MASK;
          LCD_RAM.D38_45 &=~G2_MASK;
          break;
        case 2://外温个位 2 
          LCD_RAM.D38_45 |= A2_MASK;
          LCD_RAM.D38_45 |= B2_MASK;
          LCD_RAM.D46_53 &=~C2_MASK;
          LCD_RAM.D38_45 |= D2_MASK;
          LCD_RAM.D38_45 |= E2_MASK;
          LCD_RAM.D33_37 &=~F2_MASK;
          LCD_RAM.D38_45 |= G2_MASK;
          break;
        case 3://外温个位 3 
          LCD_RAM.D38_45 |= A2_MASK;
          LCD_RAM.D38_45 |= B2_MASK;
          LCD_RAM.D46_53 |= C2_MASK;
          LCD_RAM.D38_45 |= D2_MASK;
          LCD_RAM.D38_45 &=~E2_MASK;
          LCD_RAM.D33_37 &=~F2_MASK;
          LCD_RAM.D38_45 |= G2_MASK;
          break;
        case 4://外温个位4
          LCD_RAM.D38_45 &=~A2_MASK;
          LCD_RAM.D38_45 |= B2_MASK;
          LCD_RAM.D46_53 |= C2_MASK;
          LCD_RAM.D38_45 &=~D2_MASK;
          LCD_RAM.D38_45 &=~E2_MASK;
          LCD_RAM.D33_37 |= F2_MASK;
          LCD_RAM.D38_45 |= G2_MASK;
          break;
        case 5://外温个位5
          LCD_RAM.D38_45 |= A2_MASK;
          LCD_RAM.D38_45 &=~B2_MASK;
          LCD_RAM.D46_53 |= C2_MASK;
          LCD_RAM.D38_45 |= D2_MASK;
          LCD_RAM.D38_45 &=~E2_MASK;
          LCD_RAM.D33_37 |= F2_MASK;
          LCD_RAM.D38_45 |= G2_MASK;
          break;         
        case 6: //外温个�
          LCD_RAM.D38_45 |= A2_MASK;
          LCD_RAM.D38_45 &=~B2_MASK;
          LCD_RAM.D46_53 |= C2_MASK;
          LCD_RAM.D38_45 |= D2_MASK;
          LCD_RAM.D38_45 |= E2_MASK;
          LCD_RAM.D33_37 |= F2_MASK;
          LCD_RAM.D38_45 |= G2_MASK;
          break;
        case 7://外温个位7
          LCD_RAM.D38_45 |= A2_MASK;
          LCD_RAM.D38_45 |= B2_MASK;
          LCD_RAM.D46_53 |= C2_MASK;
          LCD_RAM.D38_45 &=~D2_MASK;
          LCD_RAM.D38_45 &=~E2_MASK;
          LCD_RAM.D33_37 &=~F2_MASK;
          LCD_RAM.D38_45 &=~G2_MASK;
          break;
        case 8://外温个位8
          LCD_RAM.D38_45 |= A2_MASK;
          LCD_RAM.D38_45 |= B2_MASK;
          LCD_RAM.D46_53 |= C2_MASK;
          LCD_RAM.D38_45 |= D2_MASK;
          LCD_RAM.D38_45 |= E2_MASK;
          LCD_RAM.D33_37 |= F2_MASK;
          LCD_RAM.D38_45 |= G2_MASK;
          break;
        case 9: //外温个位9
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

void LCD_Display_Updata(void)//LCD刷新显示
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
	LCD_V_SPI_RW(0x0F);//频率530Hz
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

void Key_Input_Scan(void)//按键输入
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
    
    LCD_SEL_H();//进入省电模式解除按键扫描
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
    LCD_V_SPI_RW(0x0F);//频率530Hz
    LCD_V_SPI_RW(0x38);//省电模式
    
    LCD_V_SPI_RW(LCD_RAM.D1_8);
    LCD_V_SPI_RW(LCD_RAM.D9_16);
    LCD_V_SPI_RW(LCD_RAM.D17_24);
    LCD_V_SPI_RW(LCD_RAM.D25_32);
    LCD_V_SPI_RW(LCD_RAM.D33_37);

    LCD_V_SPI_RW(0x00);//S23 KS2 KS3 KS4 KS5 of Input key
    LCD_V_SPI_RW(0x01);
    LCD_V_SPI_RW(0x0F);//频率530Hz
    LCD_V_SPI_RW(0x00);//正常模式
    
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
	LCD_V_SPI_RW(0x0F);//频率530Hz
	LCD_V_SPI_RW(0x3C);
  
  LCD_SEL_L();
}
//end
