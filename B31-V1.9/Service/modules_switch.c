#include "modules_switch.h"


const Switch _5VR={.Output=PTA12};


void Switch_Init(void)
{
    Gpio_Init(_5VR.Output,GP_OUT,RESET);
    _5VR_Off();
}
