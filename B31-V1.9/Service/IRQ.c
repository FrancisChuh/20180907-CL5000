#include "IRQ.h"

#include "TB9102.h"
#include "modules_switch.h"
#include "GPIO.h"
#include "LIN.h"

static uint8_t Sleep_Flag=0;

void IRQ_init(void)
{
    Gpio_Interrupt_Init(M_IG_IN_IRQ,GP_IN,IRQ_ZERO);
    NVIC_Init(PORTC_IRQn,9);
}

void per_dev_sleep(void)
{
    SPI_IO_Init();
    
    TB9102_All_Sleep();
    TPD1053_ALL_Sleep();

    _5VR_Off();
    M_EXP_Off();
    M_AQS_Off();
    M_PM25_Off();
    M_NE_Off();
    M_Valve_Off();
    
    Board_LIN_Sleep();
    
    SW_LIN1_SLP(SW_ON);
    SW_LIN2_SLP(SW_ON);
    SW_CANSTB(SW_ON);
}

void per_dev_wake(void)
{
    TB9102_All_Wake();
    TPD1053_ALL_WAKE();
    
    _5VR_On();
    M_EXP_On();
    M_AQS_On();
    M_PM25_On();
    M_NE_On();
    M_Valve_On();
    
    Board_LIN_Init(LIN_bps);
    
    SW_LIN1_SLP(SW_OFF);
    SW_LIN2_SLP(SW_OFF);
    SW_CANSTB(SW_OFF);
}


void NVIC_Off(void)
{
    NVIC_DisableIRQ(LPUART2_RxTx_IRQn);
    NVIC_DisableIRQ(LPIT0_Ch0_IRQn);
    NVIC_DisableIRQ(LPUART1_RxTx_IRQn);
    NVIC_DisableIRQ(LPIT0_Ch1_IRQn);
    NVIC_DisableIRQ(CAN0_ORed_0_15_MB_IRQn);
//    NVIC_DisableIRQ(CAN0_Wake_Up_IRQn);
    NVIC_DisableIRQ(ADC0_IRQn);
    NVIC_DisableIRQ(ADC1_IRQn);
}

void NVIC_On(void)
{
    NVIC_EnableIRQ(LPUART2_RxTx_IRQn);
    NVIC_EnableIRQ(LPIT0_Ch0_IRQn);
    NVIC_EnableIRQ(LPUART1_RxTx_IRQn);
    NVIC_EnableIRQ(LPIT0_Ch1_IRQn);
    NVIC_EnableIRQ(CAN0_ORed_0_15_MB_IRQn);
//    NVIC_EnableIRQ(CAN0_Wake_Up_IRQn);
    NVIC_EnableIRQ(ADC0_IRQn);
    NVIC_EnableIRQ(ADC1_IRQn);
}


void Sleep_Direct(void)
{
    per_dev_sleep();
    NVIC_Off();
    __WFI();
}

void Sleep_MCU(void)
{
    per_dev_sleep();
    NVIC_Off();
    __WFI();
    per_dev_wake();
    NVIC_On();
}

void Sleep_Process(void)
{
  if(Sleep_Flag)
  {
    Sleep_MCU();
  }
}

void PORTC_IRQHandler(void)
{
	if((PORTC->PCR[M_IG_IN_IRQ%32] & PORT_PCR_IRQC_MASK)==IRQ_ONE)//高电平休眠
	{
		Sleep_Flag=1;
		PORTC->PCR[M_IG_IN_IRQ%32] &= ~PORT_PCR_IRQC_MASK;
		PORTC->PCR[M_IG_IN_IRQ%32] |= IRQ_ZERO;
	}
	else//低电平唤醒
	{
		Sleep_Flag=0;
		PORTC->PCR[M_IG_IN_IRQ%32] &= ~PORT_PCR_IRQC_MASK;
		PORTC->PCR[M_IG_IN_IRQ%32] |= IRQ_ONE;
	}
	PORTC->ISFR = PORTC->ISFR;
}


//end
