#ifndef _SPI_H__
#define _SPI_H__

#include "common.h"


#define SPI_CLK_OUT				PTA11	//91
#define SPI_MOSI_OUT			PTA10	//92
#define SPI_MISO_IN				PTE1	//93


#define MOSI_H()  Gpio_Set(SPI_MOSI_OUT,SET)
#define MOSI_L()  Gpio_Set(SPI_MOSI_OUT,RESET)
#define CLK_H()   Gpio_Set(SPI_CLK_OUT,SET)
#define CLK_L()   Gpio_Set(SPI_CLK_OUT,RESET)
#define MISO()    Gpio_Get(SPI_MISO_IN)

#define CSB1_H()  Gpio_Set(SPI_CS1_OUT,SET)
#define CSB1_L()  Gpio_Set(SPI_CS1_OUT,RESET)
#define CSB2_H()  Gpio_Set(SPI_CS2_OUT,SET)
#define CSB2_L()  Gpio_Set(SPI_CS2_OUT,RESET)
#define CSB3_H()  Gpio_Set(SPI_CS3_OUT,SET)
#define CSB3_L()  Gpio_Set(SPI_CS3_OUT,RESET)
#define CSB4_H()  Gpio_Set(SPI_CS4_OUT,SET)
#define CSB4_L()  Gpio_Set(SPI_CS4_OUT,RESET)

u16 V_SPI_RW(u16 data);
void SPI_IO_Init(void);

#endif
