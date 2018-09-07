#ifndef _KEY_H__
#define _KEY_H__

#include "COMMON.H"

//���尴��
#define KEYAC_Pressed_MASK      0x00000001u  //AC��ť
#define KEYAC_Pressed_SHIFT     0
#define KEYMODE_Pressed_MASK    0x00000002u  //MODE��ť
#define KEYMODE_Pressed_SHIFT   1
//#define KEYPTC_Pressed_MASK     0x00000004u  //PTC��ť
//#define KEYPTC_Pressed_SHIFT    2
#define KEYFDEF_Pressed_MASK    0x00000008u  //FDEF��ť
#define KEYFDEF_Pressed_SHIFT   3
#define KEYREC_Pressed_MASK     0x00000010u  //REC��ť
#define KEYREC_Pressed_SHIFT    4
#define KEYRDEF_Pressed_MASK    0x00000020u  //RDEF��ť
#define KEYRDEF_Pressed_SHIFT   5
#define KEYAUTO_Pressed_MASK    0x00000040u  //AUTO��ť
#define KEYAUTO_Pressed_SHIFT   6
#define KEYOFF_Pressed_MASK     0x00000080u  //OFF��ť
#define KEYOFF_Pressed_SHIFT    7
#define KEYFAN_L_Pressed_MASK   0x00000100u  //��������
#define KEYFAN_L_Pressed_SHIFT  8
#define KEYFAN_H_Pressed_MASK   0x00000200u  //��������
#define KEYFAN_H_Pressed_SHIFT  9
#define KEYTEMP_L_Pressed_MASK  0x00000400u  //�¶ȼ���
#define KEYTEMP_L_Pressed_SHIFT 10
#define KEYTEMP_H_Pressed_MASK  0x00000800u  //�¶�����
#define KEYTEMP_H_Pressed_SHIFT 11
#define KEYSEATL_Pressed_MASK   0x00001000u  //�����μ���
#define KEYSEATL_Pressed_SHIFT  12
#define KEYSEATR_Pressed_MASK   0x00002000u  //�����μ���
#define KEYSEATR_Pressed_SHIFT  13
//#define KEYFDEF2_Pressed_MASK   0x00004000u  //FDEF2
//#define KEYFDEF2_Pressed_SHIFT  14
//#define KEYDULE_Pressed_MASK    0x00008000u  //DULE
//#define KEYDULE_Pressed_SHIFT   15
#define KEYTEMP_SLAVE_L_Pressed_MASK    0x00010000u  //����ʻ�¶Ƚ���
#define KEYTEMP_SLAVE_L_Pressed_SHIFT   16
#define KEYTEMP_SLAVE_H_Pressed_MASK    0x00020000u  //����ʻ�¶�����
#define KEYTEMP_SLAVE_H_Pressed_SHIFT   17
#define KEYDULE_Pressed_MASK    0x00040000u  //DULE
#define KEYDULE_Pressed_SHIFT   18
//#define KEYDULE_Pressed_MASK    0x00080000u  //DULE
//#define KEYDULE_Pressed_SHIFT   19


extern u32 g_Key_Value;

#endif
