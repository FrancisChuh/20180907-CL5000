#include "LCD.h"

u8 KEY_READ_REQUEST=0;
LCD_DIS_TypeDef LCD_RAM;

void LCD_Init(void)//³õÊ¼ÏÔÊ¾
{
	s_Heat_Cap.AC_STATUS=0;//AC¹Ø±Õ
	g_AUTO_Flag=AUTO_TEMP_MASK;//AUTO¹Ø±Õ
	s_Heat_Cap.TAKE=REC_INTake;//ÄÚÑ­»·
	s_Heat_Cap.Set_Fan=0;//·çÁ¿0
	s_Heat_Cap.Tem_Purpose=250;//Éè¶¨ÎÂ¶È
	s_Heat_Cap.Mode_PPS=MODEFACE;//Ä£Ê½´µÃæ
	s_FDEF_Last.Mode_PPS_Last=MODEFACE;
	s_Heat_Cap.RDEF_STATUS=0;//¹Øºó³ýËª
	s_Heat_Cap.SEATL_STATUS=0;//¹Ø±Õ×ó×ùÒÎ¼ÓÈÈ
	s_Heat_Cap.SEATR_STATUS=0;//¹Ø±ÕÓÒ×ùÒÎ¼ÓÈÈ
	s_Heat_Cap.FDEF2_STATUS=0;//¹Ø±ÕÇ°µ²¼ÓÈÈ
	s_Heat_Cap.AC_ON_TEM=AC_ON_TEMP_default;//Ä¬ÈÏÆôÍ£µã
	s_Heat_Cap.AC_OFF_TEM=AC_OFF_TEMP_default;//Ä¬ÈÏÆôÍ£µã
	
//	LCD_RAM.D9_16 |=L5_MASK;//ÏÔÊ¾ÈËÏñ
//	LCD_RAM.D9_16 |=N3_MASK;//ÏÔÊ¾³µÌå
//	LCD_RAM.D17_24 |=N4_MASK;//ÏÔÊ¾³µÄÚÒ»ºá
//	LCD_RAM.D17_24 |=N1_MASK;//ÏÔÊ¾ÍâÑ­»·
//  LCD_RAM.D9_16 |=L4_MASK;//ÏÔÊ¾´µÃæ·ûºÅ
//  LCD_RAM.D17_24 |= M2_MASK; //OUTSIDE
//  LCD_RAM.D46_53 |= P1_MASK; //¡æ
//  LCD_RAM.D25_32 |= G1_MASK; //--¡æ
//  LCD_RAM.D38_45 |= G2_MASK; //--¡æ
//	LCD_Display_Updata();
}

void LCD_REC_SHOWS(signed char rec_val)//ÄÚÍâÑ­»·
{
  if(rec_val==0)
  {
		LCD_RAM.D9_16  |=N3_MASK;//ÏÔÊ¾³µÌå
		LCD_RAM.D17_24 |=N4_MASK;//ÏÔÊ¾³µÄÚÒ»ºá
    LCD_RAM.D17_24 &=~N1_MASK;//ÏÔÊ¾ÄÚÑ­»·
    LCD_RAM.D9_16  |= N2_MASK;//ÏÔÊ¾ÄÚÑ­»·
  }
  else
  {
		LCD_RAM.D9_16	 |=N3_MASK;//ÏÔÊ¾³µÌå
		LCD_RAM.D17_24 |=N4_MASK;//ÏÔÊ¾³µÄÚÒ»ºá
    LCD_RAM.D17_24 |= N1_MASK;//ÏÔÊ¾ÍâÑ­»·
    LCD_RAM.D9_16	 &=~N2_MASK;//ÏÔÊ¾ÍâÑ­»·
  }
}

void LCD_FANSPEED_SHOWS(u8 level,FunctionalState NewState)//·çÁ¿
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
      default://0-1µµ·çÏÔÊ¾1µµ·ç
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

void LCD_MODE_SHOWS(signed char mode,FunctionalState NewState)//Ä£Ê½ÏÔÊ¾
{
  if(NewState==DISABLE)
  {
    LCD_RAM.D9_16 &= ~L5_MASK;//ÏÔÊ¾ÈËÏñ
    LCD_RAM.D9_16 &= ~L4_MASK;//´µÃæ
    LCD_RAM.D9_16 &= ~L1_MASK;//Ç°³ýËª
    LCD_RAM.D9_16 &= ~L2_MASK;//´µ½Å
  }
  else
  {
    LCD_RAM.D9_16 |= L5_MASK;//ÏÔÊ¾ÈËÏñ
    switch(mode)
    {
      case MODEFACE:
        LCD_RAM.D9_16 |= L4_MASK;//´µÃæ
        LCD_RAM.D9_16 &= ~L1_MASK;//Ç°³ýËª
        LCD_RAM.D9_16 &= ~L2_MASK;//´µ½Å
        break;
      case MODEFAFE:
        LCD_RAM.D9_16 |= L4_MASK;//´µÃæ
        LCD_RAM.D9_16 &= ~L1_MASK;//Ç°³ýËª
        LCD_RAM.D9_16 |= L2_MASK;//´µ½Å
        break;
      case MODEFEET:
        LCD_RAM.D9_16 &= ~L4_MASK;//´µÃæ
        LCD_RAM.D9_16 &= ~L1_MASK;//Ç°³ýËª
        LCD_RAM.D9_16 |= L2_MASK;//´µ½Å
        break;
      case MODEFEDE:
        LCD_RAM.D9_16 &= ~L4_MASK;//´µÃæ
        LCD_RAM.D9_16 |= L1_MASK;//Ç°³ýËª
        LCD_RAM.D9_16 |= L2_MASK;//´µ½Å
        break;
      case MODEDEF:
        LCD_RAM.D9_16 &= ~L4_MASK;//´µÃæ
        LCD_RAM.D9_16 |= L1_MASK;//Ç°³ýËª
        LCD_RAM.D9_16 &= ~L2_MASK;//´µ½Å
        break;
      default:
        break;
    }
  }
}

void LCD_AC_SHOWS(FunctionalState NewState)//Ç°³ýËª
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

void LCD_FDEF2_SHOWS(FunctionalState NewState)//Ç°µµ¼ÓÈÈÏÔÊ¾
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

void LCD_RDEF_SHOWS(FunctionalState NewState)//ºóµµ¼ÓÈÈÏÔÊ¾
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

void LCD_AUTO_SHOWS(FunctionalState NewState)//AUTOÏÔÊ¾
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

void LCD_SET_SHOWS(u16 temper,FunctionalState NewState)//Éè¶¨ÎÂ¶ÈÏÔÊ¾£¬ÎÂ¶È*10
{
  if(NewState==DISABLE)
  {
    LCD_RAM.D83_90 &= ~P4_MASK;//Ð¡Êýµã
    LCD_RAM.D75_82 &= ~P3_MASK;//¡æ
    
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
      LCD_RAM.D83_90 &= ~P4_MASK;//Ð¡Êýµã
      LCD_RAM.D75_82 &= ~P3_MASK;//¡æ
      
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

      LCD_RAM.D83_90 &=~A5_MASK;//¹Ø
      LCD_RAM.D83_90 &=~B5_MASK;
      LCD_RAM.D83_90 &=~C5_MASK;
      LCD_RAM.D83_90 &=~D5_MASK;
      LCD_RAM.D75_82 &=~E5_MASK;
      LCD_RAM.D75_82 &=~F5_MASK;
      LCD_RAM.D83_90 &=~G5_MASK;
    }
    else if(temper<=MIN_TEMSET)
    {
      LCD_RAM.D83_90 &= ~P4_MASK;//Ð¡Êýµã
      LCD_RAM.D75_82 &= ~P3_MASK;//¡æ
      
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
    
      LCD_RAM.D83_90 &=~A5_MASK;//¹Ø
      LCD_RAM.D83_90 &=~B5_MASK;
      LCD_RAM.D83_90 &=~C5_MASK;
      LCD_RAM.D83_90 &=~D5_MASK;
      LCD_RAM.D75_82 &=~E5_MASK;
      LCD_RAM.D75_82 &=~F5_MASK;
      LCD_RAM.D83_90 &=~G5_MASK;
    }
    else
    {
      LCD_RAM.D75_82 |= P3_MASK;//¡æ
      LCD_RAM.D83_90 |= P4_MASK;//Ð¡Êýµã
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

void LCD_OUTSIDE_SHOWS(int16_t temper,FunctionalState NewState)//ÍâÎÂÏÔÊ¾
{
  if(NewState==DISABLE)
  {
    LCD_RAM.D17_24 &= ~M2_MASK;//OUTSIDE
    LCD_RAM.D25_32 &= ~P2_MASK;//¸ººÅ
    LCD_RAM.D46_53 &= ~P1_MASK;//¡æ
    
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
    LCD_RAM.D46_53 |= P1_MASK; //¡æ
    
    if((temper<-99) || (temper>99))
    {
      LCD_RAM.D25_32 &= ~P2_MASK;//¸ººÅ
      
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
        LCD_RAM.D25_32 |= P2_MASK;//¸ººÅ
				temper=0-temper;
      }
      else
      {
        LCD_RAM.D25_32 &= ~P2_MASK;//¸ººÅ
      }
      switch(temper/10%10)
      {
        case 0: //ÍâÎÂÊ®Î» 0
          LCD_RAM.D25_32 |= A1_MASK;
          LCD_RAM.D33_37 |= B1_MASK;
          LCD_RAM.D33_37 |= C1_MASK;
          LCD_RAM.D25_32 |= D1_MASK;
          LCD_RAM.D25_32 |= E1_MASK;
          LCD_RAM.D25_32 |= F1_MASK;
          LCD_RAM.D25_32 &= ~G1_MASK;
          break;
        case 1://ÍâÎÂÊ®Î» 1  
          LCD_RAM.D25_32 &= ~A1_MASK;
          LCD_RAM.D33_37 |= B1_MASK;
          LCD_RAM.D33_37 |= C1_MASK;
          LCD_RAM.D25_32 &= ~D1_MASK;
          LCD_RAM.D25_32 &= ~E1_MASK;
          LCD_RAM.D25_32 &= ~F1_MASK;
          LCD_RAM.D25_32 &= ~G1_MASK;
          break;
        case 2://ÍâÎÂÊ®Î» 2 
          LCD_RAM.D25_32 |= A1_MASK;
          LCD_RAM.D33_37 |= B1_MASK;
          LCD_RAM.D33_37 &= ~C1_MASK;
          LCD_RAM.D25_32 |= D1_MASK;
          LCD_RAM.D25_32 |= E1_MASK;
          LCD_RAM.D25_32 &= ~F1_MASK;
          LCD_RAM.D25_32 |= G1_MASK;
          break;
        case 3://ÍâÎÂÊ®Î» 3 
          LCD_RAM.D25_32 |= A1_MASK;
          LCD_RAM.D33_37 |= B1_MASK;
          LCD_RAM.D33_37 |= C1_MASK;
          LCD_RAM.D25_32 |= D1_MASK;
          LCD_RAM.D25_32 &= ~E1_MASK;
          LCD_RAM.D25_32 &= ~F1_MASK;
          LCD_RAM.D25_32 |= G1_MASK;
          break;
        case 4://ÍâÎÂÊ®Î»4
          LCD_RAM.D25_32 &= ~A1_MASK;
          LCD_RAM.D33_37 |= B1_MASK;
          LCD_RAM.D33_37 |= C1_MASK;
          LCD_RAM.D25_32 &= ~D1_MASK;
          LCD_RAM.D25_32 &= ~E1_MASK;
          LCD_RAM.D25_32 |= F1_MASK;
          LCD_RAM.D25_32 |= G1_MASK;
          break;
        case 5://ÍâÎÂÊ®Î»5
          LCD_RAM.D25_32 |= A1_MASK;
          LCD_RAM.D33_37 &=~B1_MASK;
          LCD_RAM.D33_37 |= C1_MASK;
          LCD_RAM.D25_32 |= D1_MASK;
          LCD_RAM.D25_32 &=~E1_MASK;
          LCD_RAM.D25_32 |= F1_MASK;
          LCD_RAM.D25_32 |= G1_MASK;
          break;         
        case 6: //ÍâÎÂÊ®Î
          LCD_RAM.D25_32 |= A1_MASK;
          LCD_RAM.D33_37 &=~B1_MASK;
          LCD_RAM.D33_37 |= C1_MASK;
          LCD_RAM.D25_32 |= D1_MASK;
          LCD_RAM.D25_32 |= E1_MASK;
          LCD_RAM.D25_32 |= F1_MASK;
          LCD_RAM.D25_32 |= G1_MASK;
          break;
        case 7://ÍâÎÂÊ®Î»7
          LCD_RAM.D25_32 |= A1_MASK;
          LCD_RAM.D33_37 |= B1_MASK;
          LCD_RAM.D33_37 |= C1_MASK;
          LCD_RAM.D25_32 &= ~D1_MASK;
          LCD_RAM.D25_32 &= ~E1_MASK;
          LCD_RAM.D25_32 &= ~F1_MASK;
          LCD_RAM.D25_32 &= ~G1_MASK;
          break;
        case 8://ÍâÎÂÊ®Î»8
          LCD_RAM.D25_32 |= A1_MASK;
          LCD_RAM.D33_37 |= B1_MASK;
          LCD_RAM.D33_37 |= C1_MASK;
          LCD_RAM.D25_32 |= D1_MASK;
          LCD_RAM.D25_32 |= E1_MASK;
          LCD_RAM.D25_32 |= F1_MASK;
          LCD_RAM.D25_32 |= G1_MASK;
          break;
        case 9: //ÍâÎÂÊ®Î»9
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
       case 0: //ÍâÎÂ¸öÎ» 0
          LCD_RAM.D38_45 |= A2_MASK;
          LCD_RAM.D38_45 |= B2_MASK;
          LCD_RAM.D46_53 |= C2_MASK;
          LCD_RAM.D38_45 |= D2_MASK;
          LCD_RAM.D38_45 |= E2_MASK;
          LCD_RAM.D33_37 |= F2_MASK;
          LCD_RAM.D38_45 &=~G2_MASK;
          break;
        case 1://ÍâÎÂ¸öÎ» 1  
          LCD_RAM.D38_45 &=~A2_MASK;
          LCD_RAM.D38_45 |= B2_MASK;
          LCD_RAM.D46_53 |= C2_MASK;
          LCD_RAM.D38_45 &=~D2_MASK;
          LCD_RAM.D38_45 &=~E2_MASK;
          LCD_RAM.D33_37 &=~F2_MASK;
          LCD_RAM.D38_45 &=~G2_MASK;
          break;
        case 2://ÍâÎÂ¸öÎ» 2 
          LCD_RAM.D38_45 |= A2_MASK;
          LCD_RAM.D38_45 |= B2_MASK;
          LCD_RAM.D46_53 &=~C2_MASK;
          LCD_RAM.D38_45 |= D2_MASK;
          LCD_RAM.D38_45 |= E2_MASK;
          LCD_RAM.D33_37 &=~F2_MASK;
          LCD_RAM.D38_45 |= G2_MASK;
          break;
        case 3://ÍâÎÂ¸öÎ» 3 
          LCD_RAM.D38_45 |= A2_MASK;
          LCD_RAM.D38_45 |= B2_MASK;
          LCD_RAM.D46_53 |= C2_MASK;
          LCD_RAM.D38_45 |= D2_MASK;
          LCD_RAM.D38_45 &=~E2_MASK;
          LCD_RAM.D33_37 &=~F2_MASK;
          LCD_RAM.D38_45 |= G2_MASK;
          break;
        case 4://ÍâÎÂ¸öÎ»4
          LCD_RAM.D38_45 &=~A2_MASK;
          LCD_RAM.D38_45 |= B2_MASK;
          LCD_RAM.D46_53 |= C2_MASK;
          LCD_RAM.D38_45 &=~D2_MASK;
          LCD_RAM.D38_45 &=~E2_MASK;
          LCD_RAM.D33_37 |= F2_MASK;
          LCD_RAM.D38_45 |= G2_MASK;
          break;
        case 5://ÍâÎÂ¸öÎ»5
          LCD_RAM.D38_45 |= A2_MASK;
          LCD_RAM.D38_45 &=~B2_MASK;
          LCD_RAM.D46_53 |= C2_MASK;
          LCD_RAM.D38_45 |= D2_MASK;
          LCD_RAM.D38_45 &=~E2_MASK;
          LCD_RAM.D33_37 |= F2_MASK;
          LCD_RAM.D38_45 |= G2_MASK;
          break;         
        case 6: //ÍâÎÂ¸öÎ
          LCD_RAM.D38_45 |= A2_MASK;
          LCD_RAM.D38_45 &=~B2_MASK;
          LCD_RAM.D46_53 |= C2_MASK;
          LCD_RAM.D38_45 |= D2_MASK;
          LCD_RAM.D38_45 |= E2_MASK;
          LCD_RAM.D33_37 |= F2_MASK;
          LCD_RAM.D38_45 |= G2_MASK;
          break;
        case 7://ÍâÎÂ¸öÎ»7
          LCD_RAM.D38_45 |= A2_MASK;
          LCD_RAM.D38_45 |= B2_MASK;
          LCD_RAM.D46_53 |= C2_MASK;
          LCD_RAM.D38_45 &=~D2_MASK;
          LCD_RAM.D38_45 &=~E2_MASK;
          LCD_RAM.D33_37 &=~F2_MASK;
          LCD_RAM.D38_45 &=~G2_MASK;
          break;
        case 8://ÍâÎÂ¸öÎ»8
          LCD_RAM.D38_45 |= A2_MASK;
          LCD_RAM.D38_45 |= B2_MASK;
          LCD_RAM.D46_53 |= C2_MASK;
          LCD_RAM.D38_45 |= D2_MASK;
          LCD_RAM.D38_45 |= E2_MASK;
          LCD_RAM.D33_37 |= F2_MASK;
          LCD_RAM.D38_45 |= G2_MASK;
          break;
        case 9: //ÍâÎÂ¸öÎ»9
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

void LCD_Display_Updata(void)//LCDË¢ÐÂÏÔÊ¾
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
	LCD_V_SPI_RW(0x0F);//ÆµÂÊ530Hz
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

void Key_Input_Scan(void)//°´¼üÊäÈë
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
    
    LCD_SEL_H();//½øÈëÊ¡µçÄ£Ê½½â³ý°´¼üÉ¨Ãè
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
    LCD_V_SPI_RW(0x0F);//ÆµÂÊ530Hz
    LCD_V_SPI_RW(0x38);//Ê¡µçÄ£Ê½
    
    LCD_V_SPI_RW(LCD_RAM.D1_8);
    LCD_V_SPI_RW(LCD_RAM.D9_16);
    LCD_V_SPI_RW(LCD_RAM.D17_24);
    LCD_V_SPI_RW(LCD_RAM.D25_32);
    LCD_V_SPI_RW(LCD_RAM.D33_37);

    LCD_V_SPI_RW(0x00);//S23 KS2 KS3 KS4 KS5 of Input key
    LCD_V_SPI_RW(0x01);
    LCD_V_SPI_RW(0x0F);//ÆµÂÊ530Hz
    LCD_V_SPI_RW(0x00);//Õý³£Ä£Ê½
    
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
	LCD_V_SPI_RW(0x0F);//ÆµÂÊ530Hz
	LCD_V_SPI_RW(0x3C);
  
  LCD_SEL_L();
}
//end
