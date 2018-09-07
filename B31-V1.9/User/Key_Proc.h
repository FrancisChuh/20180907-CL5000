#ifndef _KEY_PROC_H__
#define _KEY_PROC_H__

#include "PROCESS.H"

#define ECO_Mode_mask

#define ECO_MODE_MASK   0x01u  //ECO模式
#define ECO_MODE_SHIFT  0
#define ECO_AC_MASK     0x02u  //模式自动标志位
#define ECO_AC_SHIFT    1
#define ECO_PTC_MASK    0x04u  //风量自动标志位
#define ECO_PTC_SHIFT   2

//#define AUTO_AC_MASK    0x0008u  //ac开启标志位
//#define AUTO_AC_SHIFT   3
//#define AUTO_TEMP_MASK  0x0010u  //自动混风标志位
//#define AUTO_TEMP_SHIFT 4
//#define AUTO_PTC_MASK   0x0020u  //自动PTC标志位
//#define AUTO_PTC_SHIFT  5

void change_fan_slowly(u8 level);
void Key_Process(void);

#endif
