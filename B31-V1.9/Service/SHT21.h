#ifndef _SHT21_H__
#define _SHT21_H__

#include "process.h"
#include "math.h"

typedef struct
{
  int16_t FDEF_TEM;			//自动除霜温度
	int16_t FDEF_HUM;       //自动除霜湿度
  int16_t DEW_TEM;      //露点温度
}AUTO_FDEF_TypeDef;


#define CLR_SCL()   GPIO_ResetBits(HUM_SCL_Port, HUM_SCL_Pin)//PTM_PTM3=0
#define SET_SCL()   GPIO_SetBits(HUM_SCL_Port, HUM_SCL_Pin)//PTM_PTM3=1
#define CLR_SDA()   GPIO_ResetBits(HUM_SDA_Port, HUM_SDA_Pin)//DDRM_DDRM4=1;PTM_PTM4=0 
#define SET_SDA()   GPIO_SetBits(HUM_SDA_Port, HUM_SDA_Pin)//DDRM_DDRM4=1;PTM_PTM4=1
#define READ_SDA()  GPIO_ReadInputDataBit(HUM_SDA_Port,HUM_SDA_Pin)//PTIM_PTIM4==1 

#define ACK 0 //应答
#define NACK 1 //非应答

//void I2CDelay (unsigned char);
//void I2CInit(void);
void I2CStart(void);
void I2CStop(void);
unsigned char I2CWriteByte(unsigned char);
unsigned char I2CReadByte(unsigned char);


#define SHT21ADDR 0x80 //SHT21 的 IIC 地址

//void Delay(unsigned int);
//void SHT21Init(void);
int Sht21Work(unsigned char);
void SHT21_Get(void);
int16_t Tem_Dew(AUTO_FDEF_TypeDef* s_AUTO_FDEF_TypeDef);

extern AUTO_FDEF_TypeDef s_DEW_Point;


#endif
