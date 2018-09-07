#ifndef _PIN_CFG_H_
#define _PIN_CFG_H_


/**********************************  UART   ***************************************/

//      模块通道    端口          可选范围                          建议
#define UART0_RX    PTB0         //PTA2 PTB0 PTC2		(6 2 4)       
#define UART0_TX    PTB1         //PTA3 PTB1 PTC3		(6 2 4)
#define UART0_RTS   PTC9         //PTC9 PTA1				(6 6)
#define UART0_CTS   PTC8         //PTC8 PTA0				(6 6)

#define UART1_RX    PTD13        //PTC8 PTC6 PTD13	(2 2 3)
#define UART1_TX    PTD14        //PTC9 PTC7 PTD14	(2 2 3)
#define UART1_RTS   PTE6         //PTA7 PTE6				(6 6)
#define UART1_CTS   PTE2         //PTA6 PTE2				(6 6)

#define UART2_RX    PTD17        //PTD17 PTD6 PTA8		(3 2 2)
#define UART2_TX    PTE12        //PTE12 PTD7 PTA9		(3 2 2)


/**********************************  FTM    ***************************************/

//      模块通道    端口          可选范围              建议
#define FTM0_CH0    PTD15       //PTC0 PTB12 PTD15 （2 2 2）
#define FTM0_CH1    PTC1        //PTC1 PTB13 PTD16 （2 2 2）
#define FTM0_CH2    PTD0        //PTC2 PTB14 PTD0  （2 2 2）
#define FTM0_CH3    PTC3        //PTC3 PTB15 PTD1  （2 2 2）
#define FTM0_CH4    PTB4        //PTB4 PTB16				 （2 2）
#define FTM0_CH5    PTB5        //PTB5 PTB17				 （2 2）            
#define FTM0_CH6    PTE8        //PTE8 PTA17				 （2 2）            
#define FTM0_CH7    PTE9        //PTE9 PTE7 				 （2 2）           

//      模块通道    端口          可选范围              
#define FTM1_CH0    PTB2        //PTC4 PTB2				（2 2）
#define FTM1_CH1    PTB3        //PTA1 PTB3				（2 2）
#define FTM1_CH2    PTC14       //PTA15 PTC14			（2 2）
#define FTM1_CH3    PTC15       //PTA16 PTC15			（2 2）
#define FTM1_CH4    PTD8        //PTA10 PTD8				（2 6）
#define FTM1_CH5    PTD9        //PTA11 PTD9				（2 6）
#define FTM1_CH6    PTC0        //PTA12 PTC0				（2 6）
#define FTM1_CH7    PTC1        //PTA13 PTC1				（2 6）

//      模块通道    端口          可选范围              
#define FTM2_CH0    PTD0       	//PTD10 PTC5 PTD0 （2 2 4）
#define FTM2_CH1    PTD11       //PTA0 PTD11 PTD1	（2 2 4）
#define FTM2_CH2    PTD12       //PTD12 PTE4				（2 4）
#define FTM2_CH3    PTD5        //PTD5  PTE5				（2 4）
#define FTM2_CH4    PTD13       //PTD13 PTE10			（2 4）
#define FTM2_CH5    PTB5        //PTB5 PTE11				（2 4）
#define FTM2_CH6    PTC12       //PTC12 PTE15			（3 4）
#define FTM2_CH7    PTC13       //PTC13 PTE16			（3 4）

//      模块通道    端口          可选范围              
#define FTM3_CH0    PTB8        //PTA2 PTB8				（2 2）   
#define FTM3_CH1    PTB9        //PTA3 PTB9				（2 2）
#define FTM3_CH2    PTB10        //PTB10 PTC6			（2 4）
#define FTM3_CH3    PTB11        //PTB11 PTC7			（2 4）
#define FTM3_CH4    PTD2        //PTD2 PTC10			（2 2）
#define FTM3_CH5    PTC11        //PTD3 PTC11 			（2 2）           
#define FTM3_CH6    PTC12        //PTC12 PTE2			（2 4）             
#define FTM3_CH7    PTC13        //PTC13 PTE6			（2 4）           


/**********************************  I2C   ***************************************/

//      模块通道    端口          可选范围              建议
#define I2C0_SCL    PTB7        // PTA3 PTB7
#define I2C0_SDA    PTB6        // PTA2 PTB6

#define I2C1_SCL    PTE1       // PTD9 PTE1
#define I2C1_SDA    PTE0       // PTD8 PTE0

/**********************************  CAN    ***************************************/

//      模块通道    端口          可选范围              建议
#define CAN0_TX    PTB1        // PTE5 PTC3 PTB1		(5 3 5)
#define CAN0_RX    PTB0        // PTE4 PTC2 PTB0		(5 3 5)

#define CAN1_TX    PTA13        // PTA13 PTC7 			(3 3)
#define CAN1_RX    PTA12        // PTA12 PTC6 			(3 3)

#define CAN2_TX    PTB13        // PTB13 PTC17 			(4 3)
#define CAN2_RX    PTB12        // PTB12 PTC16 			(4 3)
/**********************************  LPTMR   ***************************************/
#define  LPT0_ALT1  PTE11     //PTE11
#define  LPT0_ALT2  PTD5      //PTD5 
#define  LPT0_ALT3  PTB0      //PTE2 PTB0
/**********************************  SPI   ***************************************/

//      模块通道    端口          可选范围              建议
#define SPI0_SIN    PTE1         // PTB3 PTE1
#define SPI0_SOUT   PTE2        // PTB4 PTB1 PTE2
#define SPI0_SCK    PTE0        // PTB2 PTE0
#define SPI0_PCS0   PTB0        // PTB0 
#define SPI0_PCS1   PTB5        // PTB5 
#define SPI0_PCS2   PTE6        // PTE6 
#define SPI0_PCS3   PTA15        // PTA15 


#define SPI1_SIN    PTD1        // PTB15 PTD1 
#define SPI1_SOUT   PTD2        // PTB16 PTD2 
#define SPI1_SCK    PTD0        // PTB14 PTD0 
#define SPI1_PCS0   PTD3        // PTD3 
#define SPI1_PCS1   PTA6        // PTA6 
#define SPI1_PCS2   PTA16        // PTA16 
#define SPI1_PCS3   PTB17        // PTB17 


#define SPI2_SIN    PTE16        // PTE16 
#define SPI2_SOUT   PTA8         // PTA8 
#define SPI2_SCK    PTE15        // PTE15 
#define SPI2_PCS0   PTA9         // PTA9 
#define SPI2_PCS1   PTE10        // PTE10 
#define SPI2_PCS2   PTE13        // PTE13 
#define SPI2_PCS3   PTA15        // PTA15 

#endif  //_FIRE_DRIVERS_CFG_H_


