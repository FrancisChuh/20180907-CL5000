#include "TPD1053.h"


const TPD1053 tpd1053_list[]={
    {.OUT=PTD0 ,.DIAG=PTE11},
    {.OUT=PTE10,.DIAG=PTE13},
    {.OUT=PTC13,.DIAG=PTC12},
    {.OUT=PTC11,.DIAG=PTC10},
    {.OUT=PTE5 ,.DIAG=PTE4 },
};

void TPD1053_Init(void)
{
    uint8_t i;
    
    for(i=0;i<(sizeof(tpd1053_list)/sizeof(TPD1053));i++)
    {
        Gpio_Init(tpd1053_list[i].OUT,GP_OUT,RESET);
        Gpio_Init(tpd1053_list[i].DIAG,GP_IN,RESET);
        TPD1053_Off(tpd1053_list[i]);
    }
}

void TPD1053_ALL_Sleep(void)
{
    uint8_t i;
    for(i=0;i<(sizeof(tpd1053_list)/sizeof(TPD1053));i++)
    {
        Gpio_Set(tpd1053_list[i].OUT,RESET);
        Gpio_Init(tpd1053_list[i].DIAG,GP_DIS,RESET);
    }
}

