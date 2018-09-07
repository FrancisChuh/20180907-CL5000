#include "SPI.h"

void delay_nop(uint16_t nops)
{
    unsigned char i;
    while(--nops>0)
    {
        for(i=0;i<1;i++);
    }
}

void spi_sleep(void)
{
    ;
}

u16 V_SPI_RW(u16 data)  //进入前,CLK应置低
{
    delay_nop(100);
	u8 i;
	for(i=0;i<16;i++)     //数据16位
	{
		CLK_H();          //上升沿采样
        delay_nop(10);
		if(data&0x8000)     //大端模式
		{
			MOSI_H();	
		}
		else
		{
			MOSI_L();	
		}
		data = data<<1;		//左移1位
        delay_nop(20);
		CLK_L();		       //CLK置低
        delay_nop(5);        
		if(MISO()==1)			
		{	
			data |=0x0001;   //大端模式
		}
        delay_nop(5);
	}
	return data;
}


//void SPI1_Write(u8 addr,u8* buf,u8 len)
//{
//  u8 i;
//  CSB1_L();
//  V_SPI_RW( addr | 0x80 );
//  for( i = 0; i < len; i++ )
//  {
//    V_SPI_RW( buf[i] );
//  }
//  SEL1_H();
//}


//void SPI1_Read( u8 addr, u8 *buf, u8 len)
//{
//  u8 i;
//  SEL1_L();
//  V_SPI_RW( addr & 0x7F );

//  for( i = 0; i < len; i++ )
//  {
//    buf[i] = V_SPI_RW(0xFF);
//  }
//  SEL1_H();
//}


void SPI_IO_Init(void)
{
    Gpio_Init(SPI_CLK_OUT,GP_OUT,RESET);			//SPI时钟，初始低电平
	Gpio_Init(SPI_MOSI_OUT,GP_OUT,RESET);				//SPI输出，初始低电平
	Gpio_Init(SPI_MISO_IN,GP_IN,SET);					//SPI输入，硬件有下拉电阻
}
//end
