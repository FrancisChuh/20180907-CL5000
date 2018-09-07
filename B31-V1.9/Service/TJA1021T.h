#ifndef __TJA1021T_H
#define __TJA1021T_H


#include "S32_gpio.h"

typedef struct TJA1021T{
    enum PTxn   SLP;
    enum PTxn   WAKE;
    void *init;
    void *deinit;
}TJA1021T;

typedef void TJA1021T_INIT(TJA1021T*);

#endif
