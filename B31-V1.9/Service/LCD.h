#ifndef _LCD_H__
#define _LCD_H__

#include <stdint.h>
#include "SKEAZ1284.h"
#include "stdio.h"
#include "process.H"

typedef struct
{
	u8 D1_8;  
  u8 D9_16; 
	u8 D17_24;
	u8 D25_32;
  u8 D33_37;
            
  u8 D38_45;
  u8 D46_53;
	u8 D54_61;
	u8 D62_69;
  u8 D70_74;
              
  u8 D75_82;  
  u8 D83_90;  
	u8 D91_98;  
	u8 D99_106; 
  u8 D107_111;
              
  u8 D112_119;
  u8 D120_127;
	u8 D128_135;
	u8 D136_143;
  u8 D144_148;
}LCD_DIS_TypeDef;

//D1_8
#define T4_MASK  0x01u
#define T3_MASK  0x02u
#define T2_MASK  0x04u
#define T1_MASK  0x08u
#define T5_MASK  0x10u
#define T6_MASK  0x20u
#define T7_MASK  0x40u
#define T8_MASK  0x80u

//D9_16
#define L1_MASK  0x01u
#define L2_MASK  0x02u
#define L3_MASK  0x04u
#define L4_MASK  0x10u
#define L5_MASK  0x20u
#define N2_MASK  0x40u
#define N3_MASK  0x80u

//D17_24;
#define N1_MASK  0x02u
#define N4_MASK  0x04u
#define M4_MASK  0x10u
#define M1_MASK  0x20u
#define M2_MASK  0x40u
#define M3_MASK  0x80u

//D25_32;
#define F1_MASK  0x01u
#define E1_MASK  0x02u
#define P2_MASK  0x04u
#define A1_MASK  0x10u
#define G1_MASK  0x20u
#define D1_MASK  0x40u

//D33_37;
#define B1_MASK  0x01u
#define C1_MASK  0x02u
#define F2_MASK  0x10u

//D38_45;
#define E2_MASK  0x01u
#define A2_MASK  0x08u
#define G2_MASK  0x10u
#define D2_MASK  0x20u
#define B2_MASK  0x80u

//D46_53;
#define C2_MASK  0x01u
#define P1_MASK  0x08u
#define F3_MASK  0x80u

//D54_61;
#define E3_MASK  0x01u
#define A3_MASK  0x08u
#define G3_MASK  0x10u
#define D3_MASK  0x20u
#define B3_MASK  0x80u

//D62_69;
#define C3_MASK  0x01u
#define F4_MASK  0x08u
#define E4_MASK  0x10u
#define A4_MASK  0x80u

//D70_74;
#define G4_MASK  0x01u
#define D4_MASK  0x02u
#define B4_MASK  0x08u
#define C4_MASK  0x10u

//D75_82;  
#define P3_MASK  0x04u
#define F5_MASK  0x40u
#define E5_MASK  0x80u

//D83_90;
#define P4_MASK  0x01u
#define A5_MASK  0x04u
#define G5_MASK  0x08u
#define D5_MASK  0x10u
#define B5_MASK  0x40u
#define C5_MASK  0x80u

//D91_98;
//D99_106; 
//D107_111;

void LCD_Init(void);//初始显示
void LCD_FANSPEED_SHOWS(u8 level,FunctionalState NewState);//风量
void LCD_MODE_SHOWS(signed char mode,FunctionalState NewState);//模式显示
void LCD_AC_SHOWS(FunctionalState NewState);//前除霜
void LCD_FDEF2_SHOWS(FunctionalState NewState);//前档加热显示
void LCD_RDEF_SHOWS(FunctionalState NewState);//后档加热显示
void LCD_AUTO_SHOWS(FunctionalState NewState);//AUTO显示
void LCD_SET_SHOWS(u16 temper,FunctionalState NewState);//设定温度显示，温度*10
void LCD_OUTSIDE_SHOWS(int16_t temper,FunctionalState NewState);//外温显示
void LCD_Display_Updata(void);//LCD刷新显示
void LCD_REC_SHOWS(signed char rec_val);//内外循环
void LCD_Sleep(void);

extern u8 KEY_READ_REQUEST;
extern LCD_DIS_TypeDef LCD_RAM;

#endif
