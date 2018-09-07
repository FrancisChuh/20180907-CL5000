#ifndef _COMMON_H_
#define _COMMON_H_

#if 0
typedef char			     int8_t;   //  8 bits 
typedef short int	       	     int16_t;  // 16 bits
typedef int		       	     int32;  // 32 bits

typedef volatile int8_t		     vint8;  //  8 bits
typedef volatile int16_t	     vint16; // 16 bits
typedef volatile int32	     vint32; // 32 bits

typedef volatile uint8_t	     vuint8;  //  8 bits
typedef volatile uint16_t	     vuint16; // 16 bits
typedef volatile uint32_t            vuint32; // 32 bits
typedef volatile float            vfloat ; // 
typedef void(func)         (void) ;
#endif

#include <stdint.h>
#include "math.h"

#include "me_type.h"                  //额外的变量定义

#include "device_registers.h"           // Device header
#include "RTE_Components.h"             // Component selection
#include "system_S32K144.h"             // Keil::Device:Startup
#include "S32K144.h"




#include "port.h"
#include "pin_cfg.h"
#include "S32_gpio.h"
#include "S32_can.h"
#include "S32_PIT.h" 

#include "S32K_FTM.h"
#include "S32K_adc.h"

#include "pit.h"
#include "GPIO.h"
#include "uart.h"
//#include "adc.h"
#include "delay.h"



#include "pwm.h"
#include "wdog.h"
#include "process.h"
#include "spi.h"
#include "irq.h"
#include "flexram.h"
#include "can_proc.h"
#include "flash.h"
#include "temper.h"
#include "E_MOTOR_DRIVE.h"
#include "Fan_Temp_Mode.h"
#include "key.h"
#include "Key_Proc.h"
#include "KeyFunction.h"
#include "MOTOR_DRIVE.h"

#include "PM25.h"
#include "Tem_Hum.h"
#include "B31.h"




#if HW_TEST
	#include "hw_test.h"
#endif

#endif 
