#include "TB9102.h"

TB9102 tb9102_list[4]=
{
    {.CSB_pin=SPI_CS1_OUT,.SEL_pin=TB9102_SEL_PIN,.MOD_pin=TB9102_MODE_PIN,.input_buf=0,.output_buf=0,},  //u11
    {.CSB_pin=SPI_CS2_OUT,.SEL_pin=TB9102_SEL_PIN,.MOD_pin=TB9102_MODE_PIN,.input_buf=0,.output_buf=0,},  //u12
    {.CSB_pin=SPI_CS3_OUT,.SEL_pin=TB9102_SEL_PIN,.MOD_pin=TB9102_MODE_PIN,.input_buf=0,.output_buf=0,},  //u13
    {.CSB_pin=SPI_CS4_OUT,.SEL_pin=TB9102_SEL_PIN,.MOD_pin=TB9102_MODE_PIN,.input_buf=0,.output_buf=0,},  //u14
};



void TB9102_OUTPUT_H(TB9102 *tb9102,uint16_t pin)
{
    tb9102->output_buf|=(1<<pin);
    tb9102->output_buf&=~(1<<(pin+1));
}

void TB9102_OUTPUT_HZ(TB9102 *tb9102,uint16_t pin)
{
    tb9102->output_buf&=~(1<<pin);
    tb9102->output_buf&=~(1<<(pin+1));
}

void TB9102_OUTPUT_L(TB9102 *tb9102,uint16_t pin)
{
    tb9102->output_buf&=~(1<<pin);
    tb9102->output_buf|=(1<<(pin+1));
}


void tb9102_update(TB9102 *tb9102)
{
    Gpio_Set(tb9102->CSB_pin,RESET);
    tb9102->input_buf=V_SPI_RW(tb9102->output_buf);
    Gpio_Set(tb9102->CSB_pin,SET);
    if(tb9102->input_buf & 0xE000)
    {
        ;//异常
    }
}

void TB9102_Sleep(TB9102 *tb9102) //进入休眠模式
{
    Gpio_Init(tb9102->CSB_pin,GP_DIS,RESET);
	Gpio_Set(tb9102->SEL_pin,RESET);//低电平，休眠
	Gpio_Set(tb9102->MOD_pin,RESET);//低电平，休眠
}

void TB9102_All_Sleep(void)
{
    uint8_t i;
    for(i=0;i<sizeof(tb9102_list)/sizeof(TB9102);i++)
    {
        TB9102_Sleep(&tb9102_list[i]);
        Gpio_Set(tb9102_list[i].CSB_pin,SET);
    }
}

void TB9102_Wake(TB9102 *tb9102)      //退出休眠模式
{
	Gpio_Set(tb9102->MOD_pin,SET);//高电平，唤醒
}

void TB9102_All_Wake(void)
{
    uint8_t i;
    for(i=0;i<sizeof(tb9102_list)/sizeof(TB9102);i++)
    {
        TB9102_Wake(&tb9102_list[i]);
    }
}

void TB9102_Init(void)
{
    uint8_t i;
    for(i=0;i<sizeof(tb9102_list)/sizeof(TB9102);i++)
    {
        Gpio_Init(tb9102_list[i].CSB_pin,GP_OUT,SET);			//9102片选
        Gpio_Init(tb9102_list[i].SEL_pin,GP_OUT,SET);			//9102休眠，高电平正常
        Gpio_Init(tb9102_list[i].MOD_pin,GP_OUT,SET);		//9102模式选择，高电平正常，低电平制动
    }
}
