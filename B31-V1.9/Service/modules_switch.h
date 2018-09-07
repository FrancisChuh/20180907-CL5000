#ifndef __MODULES_SWITCH
#define __MODULES_SWITCH

#include "S32_gpio.h"

#include "TPD1053.h"

typedef struct Switch{
    enum PTxn Output;
}Switch;

#define PowerOn(Switch) Gpio_Set(Switch.Output,SET)
#define PowerOff(Switch) Gpio_Set(Switch.Output,RESET)


/*5V��������Դ����*/
extern const Switch _5VR;
#define _5VR_On() PowerOn(_5VR)
#define _5VR_Off() PowerOff(_5VR)

/*������ͷ�*/
#define M_EXP_On()      TPD1053_On(M_EXP_Ctrl)
#define M_EXP_Off()     TPD1053_Off(M_EXP_Ctrl)

/*AQS:Ԥ��*/
#define M_AQS_On()      TPD1053_On(M_AQS_Ctrl);
#define M_AQS_Off()     TPD1053_Off(M_AQS_Ctrl);

/*PM2.5ģ��*/
#define M_PM25_On()     TPD1053_On(M_PM25_Ctrl)
#define M_PM25_Off()    TPD1053_Off(M_PM25_Ctrl)

/*�����ӿ���*/
#define M_NE_On()       TPD1053_On(M_NE_Ctrl)
#define M_NE_Off()      TPD1053_Off(M_NE_Ctrl)

/*��ŷ�*/
#define M_Valve_On()    TPD1053_On(M_Valve_Ctrl)
#define M_Valve_Off()   TPD1053_Off(M_Valve_Ctrl)

void Switch_Init(void);

#endif
