#include "SHT21.h"

AUTO_FDEF_TypeDef s_DEW_Point={250,0,0};

void SDA_Out(void)
{
	GPIO_InitTypeDef GPIO_InitStructure;
  
  GPIO_InitStructure.GPIOx = HUM_SDA_Port;      //34
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_OUT; //输出
	GPIO_InitStructure.GPIO_Pin = HUM_SDA_Pin;    //湿度传感器IIC数据
	GPIO_InitStructure.GPIO_InitState = Bit_SET;  //高电平使能
	GPIO_Init(&GPIO_InitStructure);
}

void SDA_In(void)
{
	GPIO_InitTypeDef GPIO_InitStructure;

  GPIO_InitStructure.GPIOx = HUM_SDA_Port;      //34
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPU; //上拉输入
	GPIO_InitStructure.GPIO_Pin = HUM_SDA_Pin;    //湿度传感器IIC数据
	GPIO_InitStructure.GPIO_InitState = Bit_SET;  //高电平使能
	GPIO_Init(&GPIO_InitStructure);
}

/*================================================================
【名 称】 void I2CDelay (unsigned char t)
【功 能】模拟 IIC 用的短延时
================================================================*/
void I2CDelay (unsigned char t)
{
	while(t--);
}
///*================================================================
//【名 称】 void I2CInit(void)
//【功 能】 I2C 初始化，空闲状态
//================================================================*/
//void I2CInit(void)
//{
//	SDA = 1;
//	SCL = 1;
//}
/*================================================================
【名 称】 void I2CStart(void)
【功 能】 I2C 启动信号
【备 注】 SCL 、 SDA 同为高， SDA 跳变成低之后， SCL 跳变成低
================================================================*/
void I2CStart(void)
{  
  SDA_Out();
	
	SET_SDA();
	SET_SCL();
	I2CDelay(10);
	CLR_SDA();
	I2CDelay(10);
	CLR_SCL();
}
/*================================================================
【名 称】 void I2CStop(void)
【功 能】 I2C 停止信号
【备 注】 SCL 、 SDA 同为低， SCL 跳变成高之后， SDA 跳变成高
================================================================*/
void I2CStop(void)
{
	SDA_Out();
  
	CLR_SCL();
	CLR_SDA(); 
	I2CDelay(10);
	SET_SCL();
	I2CDelay(10);
	SET_SDA();	
}
/*================================================================
【名 称】 unsigned char I2CWRByte(unsigned char WriteData)
【功 能】 I2C 写一个字节数据，返回 ACK 或者 NACK
【备 注】从高到低，依次发送
================================================================*/
unsigned char I2CWriteByte(unsigned char WriteData)
{
  unsigned char i;
  
	SDA_Out();//设置为输出
	CLR_SCL();
  for(i = 0;i < 8;i++)
  {
    if(WriteData & 0x80)
		{
			SET_SDA();
		}
    else
		{
			CLR_SDA();
		}
    I2CDelay(10);
		SET_SCL(); //输出 SDA 稳定后，拉高 SCL 给出上升沿，从机检测到后进行数据采样
    I2CDelay(10);
		CLR_SCL();
    I2CDelay(10);
    WriteData = WriteData<<1;
  }
	SDA_In();
	SET_SCL();
  I2CDelay(10);
  if(READ_SDA() == 1) //SDA 为高，收到 NACK
  {
    CLR_SCL();
    I2CDelay(10);
    return NACK;
  }
  else //SDA 为低，收到 ACK
  {
    CLR_SCL();
    I2CDelay(10);
    return ACK;
  }
}
/*================================================================
【名 称】 unsigned char I2CRDByte(unsigned char AckValue)
【功 能】 I2C 读一个字节数据，入口参数用于控制应答状态， ACK 或者 NACK
【备 注】从高到低，依次接收
================================================================*/
unsigned char I2CReadByte(unsigned char AckValue)
{
  unsigned char i,ReadData = 0;

  SDA_In();
  CLR_SCL();
  I2CDelay(10);
  for(i = 0;i < 8;i++)
  {
    ReadData <<= 1;
    SET_SCL(); //给出上升沿
    I2CDelay(10); // 延时等待信号稳定
    if(READ_SDA() == 1) //采样获取数据
    {
      ReadData |= 0x01;
    }
    CLR_SCL(); //下降沿，从机给出下一位值
    I2CDelay(10);
  }
  SDA_Out();
  if(AckValue) //应答状态
  {
    SET_SDA();
  }
  else
  {
    CLR_SDA();
  }
  I2CDelay(10);
	SET_SCL();
  I2CDelay(10);
  CLR_SCL();
  return ReadData;
}

/*================================================================
【名 称】 void Delay(unsigned int t)
【功 能】延时长
================================================================*/
//void Delay(unsigned int t)
//{
//  unsigned char i;
//  while(t--)
//  {
//    for(i = 0;i < 200;i++);
//  }
//}
/*================================================================
【名 称】 void SHT21Init(void)
【功 能】 SHT21 初始化函数
================================================================*/
//void SHT21Init(void)
//{
//  I2CStart(); //启动 I2C
//  I2CWriteByte(SHT21ADDR&0xfe); //写 SHT21 的 I2C 地址
//  I2CWriteByte(0xfe);
//  I2CStop(); //停止 I2C
//  Delay(600); //短延时
//}
/*================================================================
【名 称】 long Sht21Work(unsigned char order)
【功 能】 Sht21 测量温湿度
================================================================*/
int Sht21Work(unsigned char order)
{
  I2CStart();
  if(I2CWriteByte(SHT21ADDR & 0xFE) == ACK)
  {
    if(I2CWriteByte(order) == ACK)
    {
      return 1;
    }
  }
  return 0;
}

int Sht21Read(unsigned char order)
{
  float temp = 0;
  u8 MSB,LSB;
  int output=-999;

  I2CStart();
  if(I2CWriteByte(SHT21ADDR | 0x01) == ACK)
  {
    MSB = I2CReadByte(ACK);
    LSB = I2CReadByte(NACK);
    //I2CRDByte(NACK);
    I2CStop();
    LSB &= 0xfc;
    temp = (MSB<<8) + LSB;
    if (order == 0xf3)
    {
      temp=(175.72)*temp/65536-46.85;
    }
    else
    {
      temp = (temp*125)/65536-6;
    }
    output = temp*10;
  }
  return output;
}

void SHT21_Get(void)
{
  static u8 turns=0;
  int16_t temp=0;
  
  switch(turns)
  {
    case 0:
      if(Sht21Work(0xF3)== ACK);//温度测量
      {
        turns+=1;
      }
      break;
    case 1:
      temp=Sht21Read(0xF3);//温度读取
      if(temp==-999)
      {
        turns=0;
      }
      else
      {
        s_DEW_Point.FDEF_TEM=temp ;
        turns+=1;
      }
      break;
    case 2:
      if(Sht21Work(0xF5)== ACK);//湿度测量
      {
        turns+=1;
      }
      break;
    case 3:
      temp=Sht21Read(0xF5);//温度读取
      if(temp<0)
      {
        turns=2;
      }
      else
      {
        s_DEW_Point.FDEF_HUM=temp;//湿度读取
        turns=0;
        s_DEW_Point.DEW_TEM= Tem_Dew(&s_DEW_Point);
      }
      break;
    default:
      turns=0;
      break;
  }
}

int16_t Tem_Dew(AUTO_FDEF_TypeDef* s_AUTO_FDEF_TypeDef)
{
  AUTO_FDEF_TypeDef s_AUTO_FDEF=*s_AUTO_FDEF_TypeDef;
  int16_t Temp_Dew_Point;
  double a,b;
  
  if(s_AUTO_FDEF.FDEF_TEM>0)
  {
    a=log((double)s_AUTO_FDEF.FDEF_HUM/1000)+(17.62*s_AUTO_FDEF.FDEF_TEM/10)/(243.12+s_AUTO_FDEF.FDEF_TEM/10);
    b=17.62-log((double)s_AUTO_FDEF.FDEF_HUM/1000)-(17.62*s_AUTO_FDEF.FDEF_TEM/10)/(243.12+s_AUTO_FDEF.FDEF_TEM/10);
    Temp_Dew_Point=2431.2*a/b;
  }
  else
  {
    a=log((double)s_AUTO_FDEF.FDEF_HUM/1000)+(22.46*s_AUTO_FDEF.FDEF_TEM/10)/(272.62+s_AUTO_FDEF.FDEF_TEM/10);
    b=22.46-log((double)s_AUTO_FDEF.FDEF_HUM/1000)-(22.46*s_AUTO_FDEF.FDEF_TEM/10)/(272.62+s_AUTO_FDEF.FDEF_TEM/10);
    Temp_Dew_Point=2726.2*a/b;
  }
  return Temp_Dew_Point;
}
