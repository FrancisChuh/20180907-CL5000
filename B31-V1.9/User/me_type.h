#ifndef __EXTRA_INT_H
#define __EXTRA_INT_H


//类型别名宏定义
typedef unsigned char				u8;  // 8 bits
typedef unsigned short int	u16; // 16 bits
typedef unsigned long int		u32; // 32 bits

typedef volatile signed				char	vint8;  //  8 bits
typedef volatile signed short	int		vint16; // 16 bits
typedef volatile signed				int		vint32; // 32 bits

typedef volatile unsigned				char	vuint8;  //  8 bits
typedef volatile unsigned short	int		vuint16; // 16 bits
typedef volatile unsigned				int		vuint32; // 32 bits
typedef volatile float								vfloat ; // 

typedef enum {SW_OFF = 0, SW_ON = !SW_OFF} SW_STATUS;
typedef enum {DISABLE = 0, ENABLE = !DISABLE} FunctionalState;

#define NULL    0


#endif
