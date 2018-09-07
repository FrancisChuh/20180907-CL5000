#ifndef _KEY_H__
#define _KEY_H__

#include "COMMON.H"

//定义按键
#define KEYAC_Pressed_MASK      0x00000001u  //AC按钮
#define KEYAC_Pressed_SHIFT     0
#define KEYMODE_Pressed_MASK    0x00000002u  //MODE按钮
#define KEYMODE_Pressed_SHIFT   1
//#define KEYPTC_Pressed_MASK     0x00000004u  //PTC按钮
//#define KEYPTC_Pressed_SHIFT    2
#define KEYFDEF_Pressed_MASK    0x00000008u  //FDEF按钮
#define KEYFDEF_Pressed_SHIFT   3
#define KEYREC_Pressed_MASK     0x00000010u  //REC按钮
#define KEYREC_Pressed_SHIFT    4
#define KEYRDEF_Pressed_MASK    0x00000020u  //RDEF按钮
#define KEYRDEF_Pressed_SHIFT   5
#define KEYAUTO_Pressed_MASK    0x00000040u  //AUTO按钮
#define KEYAUTO_Pressed_SHIFT   6
#define KEYOFF_Pressed_MASK     0x00000080u  //OFF按钮
#define KEYOFF_Pressed_SHIFT    7
#define KEYFAN_L_Pressed_MASK   0x00000100u  //风量减低
#define KEYFAN_L_Pressed_SHIFT  8
#define KEYFAN_H_Pressed_MASK   0x00000200u  //风量增加
#define KEYFAN_H_Pressed_SHIFT  9
#define KEYTEMP_L_Pressed_MASK  0x00000400u  //温度减低
#define KEYTEMP_L_Pressed_SHIFT 10
#define KEYTEMP_H_Pressed_MASK  0x00000800u  //温度增加
#define KEYTEMP_H_Pressed_SHIFT 11
#define KEYSEATL_Pressed_MASK   0x00001000u  //左座椅加热
#define KEYSEATL_Pressed_SHIFT  12
#define KEYSEATR_Pressed_MASK   0x00002000u  //右座椅加热
#define KEYSEATR_Pressed_SHIFT  13
//#define KEYFDEF2_Pressed_MASK   0x00004000u  //FDEF2
//#define KEYFDEF2_Pressed_SHIFT  14
//#define KEYDULE_Pressed_MASK    0x00008000u  //DULE
//#define KEYDULE_Pressed_SHIFT   15
#define KEYTEMP_SLAVE_L_Pressed_MASK    0x00010000u  //副驾驶温度降低
#define KEYTEMP_SLAVE_L_Pressed_SHIFT   16
#define KEYTEMP_SLAVE_H_Pressed_MASK    0x00020000u  //副驾驶温度增加
#define KEYTEMP_SLAVE_H_Pressed_SHIFT   17
#define KEYDULE_Pressed_MASK    0x00040000u  //DULE
#define KEYDULE_Pressed_SHIFT   18
//#define KEYDULE_Pressed_MASK    0x00080000u  //DULE
//#define KEYDULE_Pressed_SHIFT   19


extern u32 g_Key_Value;

#endif
