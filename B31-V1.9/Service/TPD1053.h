#ifndef __TPD1053_H
#define __TPD1053_H

#include "S32_gpio.h"


typedef struct TPD1053{
    enum PTxn OUT;
    enum PTxn DIAG;
}TPD1053;


extern const TPD1053 tpd1053_list[];

#define M_EXP_Ctrl       tpd1053_list[0]
#define M_AQS_Ctrl       tpd1053_list[1]
#define M_PM25_Ctrl      tpd1053_list[2]
#define M_NE_Ctrl        tpd1053_list[3]
#define M_Valve_Ctrl     tpd1053_list[4]

#define TPD1053_On(tpd1053)         Gpio_Set(tpd1053.OUT,SET)
#define TPD1053_Off(tpd1053)        Gpio_Set(tpd1053.OUT,RESET)
#define TPD1053_Diag(tpd1053)       Gpio_Get(tpd1053.DIAG)


#define TPD1053_ALL_WAKE TPD1053_Init
void TPD1053_Init(void);
void TPD1053_ALL_Sleep(void);

#endif
