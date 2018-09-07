#ifndef _WDOG_H__
#define _WDOG_H__

#include "S32K144.h"


#define WDOG_CLK_BUS	0   /*!< clock source is bus clock 40M*/
#define WDOG_CLK_LPO	1   /*!< clock source is internal LPO 128 KHz */
#define WDOG_CLK_SOSC	2   /*!< clock source is internal oscillator 8 MHz (ICSIRCLK) */
#define WDOG_CLK_SIRC 3   /*!< clock source is external clock 8M*/

/* WDOG default values */
#define WDOG_CS1_DEFAULT_VALUE      0x80
#define WDOG_CS2_DEFAULT_VALUE      0x01
#define WDOG_TOVAL_DEFAULT_VALUE    0x0400
#define WDOG_WIN_DEFAULT_VALUE      0x0000
    
void Board_WDOG_Init(void);
void Board_WDOG_Feed(void);
void Board_WDOG_Disable(void);

#endif
