#ifndef _IRQ_H__
#define _IRQ_H__

#include "common.h"


#define M_IG_IN_IRQ				PTC8    //56

void IRQ_init(void);
void Sleep_Process(void);
void Sleep_MCU(void);

void Sleep_Direct(void);

#endif
