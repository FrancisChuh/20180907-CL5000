#include "TJA1021T.h"


void TJA1021T_Init(TJA1021T *tja1021t);
void TJA1021T_Deinit(TJA1021T *tja1021t);

const TJA1021T tja1021t_0={
    .SLP=PTD15,
    .WAKE=PTE9,
    .init=&TJA1021T_Init,
    .deinit=&TJA1021T_Deinit,
};

void TJA1021T_Init(TJA1021T *tja1021t)
{
    Gpio_Init(tja1021t->SLP,GP_OUT,SET);
    Gpio_Init(tja1021t->WAKE,GP_OUT,SET);
}

void TJA1021T_Deinit(TJA1021T *tja1021t)
{
    Gpio_Init(tja1021t->SLP,GP_DIS,RESET);
    Gpio_Init(tja1021t->WAKE,GP_DIS,RESET);
}

