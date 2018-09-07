#ifndef _B31_H__
#define _B31_H__

#include "common.h"

#define Auto_Fdef 1
#define Hi_Eff 0

typedef struct
{
    int16_t Tem_Inside;       //车内温度
    int16_t Tem_Purpose;      //设定温度
	int16_t Tem_Slave_Purpose;	//设定温度2
    int16_t DUAL_STATUS;				//dual状态
    int16_t Humidity_Inside;  //车内湿度
    int16_t Tem_Outside;      //车外温度
    int16_t Air_Outside_qua;  //车外空气质量
    int16_t TAKE;             //当前循环模式，0-内循环，1外循环
    int16_t Mode_PPS;         //目标模式
    int16_t SUN_Val;          //阳光照度值
    int16_t AC_IN_STATUS;     //车内AC状态
    int16_t AC_BAT_STATUS;    //电池AC状态   
    int16_t PTC_IN_STATUS;    //车内PTC状态
    int16_t PTC_BAT_STATUS;   //电池PTC状态
    int16_t FDEF2_STATUS;     //前档加热状态
    int16_t RDEF_STATUS;      //后档加热状态
    int16_t MIX_Vol;          //混风电压
    int16_t Tem_In_err;       //车内温度-设定温度
    int16_t Tem_Out_err;      //车外温度-设定温度
    int16_t Tem_Out_In_err;   //车外温度-车内温度
    int16_t Tem_err_S;        //设定温差校准后参数（含阳光）
    int16_t Tem_err_S_H;      //设定温差校准后参数（含阳光和湿度）
    int16_t Set_Fan;          //设定风量档位（00-80，方便1.5档即15）
    int16_t Set_Fan_Now;      //当前风量
    int16_t Heat_Cap;         //车内热容
    int16_t Break;            //刹车信号
    int16_t AC_ON_TEM;        //AC开启温度点
    int16_t AC_OFF_TEM;       //AC关闭温度点
    int16_t Rapid_Speed_Up;   //急加速
    int16_t SEATL_STATUS;     //左座椅加热状态
    int16_t SEATR_STATUS;			//右座椅加热状态
    int16_t ESV_STATUS;				//截止阀导通状态
    int16_t PM25_STATUS;			//PM25状态
    int16_t Negativeion_STATUS;//负离子状态
}Heat_Cap_TypeDef;

typedef struct
{
  u16 REC_Tip;      //
  u16 REC_Count;
	u16 RDEF_Count;
//	u8 MOTER_REC_ACW_Count;
//	u8 MOTER_REC_CW_Count;
//	u8 MOTER_TEMP_ACW_Count;
//	u8 MOTER_TEMP_CW_Count;
//	u8 MOTER_MODE_ACW_Count;
//	u8 MOTER_MODE_CW_Count;
//	u8 TWV_CW_Count;
//	u8 TWV_ACW_Count;
//	u8 PM25_IN_Count;
//	u8 PM25_OUT_Count;
//	u8 PANEL_Lin_Count;
}TIME_LEFT_TypeDef;

#define REC_INTake	0
#define REC_OUTTake 1

#define MAX_TEMSET (310+5)
#define MIN_TEMSET (155-5)

#define AC_ON_TEMP_default  20
#define AC_OFF_TEMP_default -10

#define AC_ON_TEMP_break  -20
#define AC_OFF_TEMP_break -50

#define AC_ON_TEMP_SpUp  60
#define AC_OFF_TEMP_SpUp 30

/*定义g_AUTO_Flag*/
#define AUTO_TAKE_MASK  0x0001u  //循环自动标志位
#define AUTO_TAKE_SHIFT 0
#define AUTO_MODE_MASK  0x0002u  //模式自动标志位
#define AUTO_MODE_SHIFT 1
#define AUTO_FAN_MASK   0x0004u  //风量自动标志位
#define AUTO_FAN_SHIFT  2
#define AUTO_AC_MASK    0x0008u  //ac开启标志位
#define AUTO_AC_SHIFT   3
#define AUTO_TEMP_MASK  0x0010u  //自动混风标志位
#define AUTO_TEMP_SHIFT 4
#define AUTO_PTC_MASK   0x0020u  //自动PTC标志位
#define AUTO_PTC_SHIFT  5

/*定义g_Diog_Flag*/
#define MOTER_TEMP_ERR_MASK       0x00000001u  //温度执行器坏
#define MOTER_TEMP_ERR_SHIFT      0 
#define MOTER_REC_ERR_MASK        0x00000002u  //循环执行器坏
#define MOTER_REC_ERR_SHIFT       1 
#define MOTER_MODE_ERR_MASK       0x00000004u  //模式执行器坏
#define MOTER_MODE_ERR_SHIFT      2 
#define TSENSOR_EVA_OPEN_MASK     0x00000008u  //蒸发器温度传感器开路
#define TSENSOR_EVA_OPEN_SHIFT    3 
#define TSENSOR_EVA_SHORT_MASK    0x00000010u  //蒸发器温度传感器短路
#define TSENSOR_EVA_SHORT_SHIFT   4 
#define TSENSOR_OUT_OPEN_MASK     0x00000020u  //外温传感器开路
#define TSENSOR_OUT_OPEN_SHIFT    5
#define TSENSOR_OUT_SHORT_MASK    0x00000040u  //外温传感器短路
#define TSENSOR_OUT_SHORT_SHIFT   6
#define TSENSOR_IN_OPEN_MASK      0x00000080u  //内温传感器开路
#define TSENSOR_IN_OPEN_SHIFT     7
#define TSENSOR_IN_SHORT_MASK     0x00000100u  //内温传感器短路
#define TSENSOR_IN_SHORT_SHIFT    8
#define TWindshield_OPEN_MASK     0x00000200u  //挡风玻璃温度开路//
#define TWindshield_OPEN_SHIFT    9
#define TWindshield_SHORT_MASK    0x00000400u  //挡风玻璃温度短路//
#define TWindshield_SHORT_SHIFT   10
#define RHWindshield_OPEN_MASK    0x00000800u  //挡风玻璃湿度开路//
#define RHWindshield_OPEN_SHIFT   11
#define RHWindshield_SHORT_MASK   0x00001000u  //挡风玻璃湿度短路//
#define RHWindshield_SHORT_SHIFT  12
#define TPRESSLOW_OPEN_MASK       0x00002000u  //低压温度开路
#define TPRESSLOW_OPEN_SHIFT      13
#define TPRESSLOW_SHORT_MASK      0x00004000u  //低压温度短路//
#define TPRESSLOW_SHORT_SHIFT     14
#define PRESSLOW_OPEN_MASK        0x00008000u  //低压压力开路//
#define PRESSLOW_OPEN_SHIFT    	  15
#define PRESSLOW_SHORT_MASK       0x00010000u  //低压压力短路//
#define PRESSLOW_SHORT_SHIFT      16
#define SENSOR_PHOTO_OPEN_MASK    0x00020000u  //阳光开路//
#define SENSOR_PHOTO_OPEN_SHIFT   17
#define SENSOR_PHOTO_SHORT_MASK   0x00040000u  //阳光短路
#define SENSOR_PHOTO_SHORT_SHIFT  18
#define MOTOR_TWV_ERR_MASK        0x00080000u  //三通阀坏
#define MOTOR_TWV_ERR_SHIFT       19
#define VOL12V_OVERVOL_MASK       0x00100000u  //电池电压过压
#define VOL12V_OVERVOL_SHIFT      20
#define VOL12V_UNDERVOL_MASK      0x00200000u  //电池电压欠压
#define VOL12V_UNDERVOL_SHIFT     21
#define PM25_IN_SENSOR_ERR_MASK   0x00400000u	 //PM2.5车内传感器损坏//
#define PM25_IN_SENSOR_ERR_SHIFT  22
#define PM25_OUT_SENSOR_ERR_MASK  0x00800000u	 //PM2.5车外传感器损坏//
#define PM25_OUT_SENSOR_ERR_SHIFT 23
#define PM25_IN_NACK_ERR_MASK			0x01000000u	 //PM2.5车内无通信//
#define PM25_IN_NACK_ERR_SHIFT		24 
#define PM25_OUT_NACK_ERR_MASK		0x02000000u	 //PM2.5车外无通信// 
#define PM25_OUT_NACK_ERR_SHIFT		25
#define PANEL_NACK_ERR_MASK				0x04000000u	 //面板LIN总线无通信// 
#define PANEL_NACK_ERR_SHIFT			26
#define CAN_OVERTIME_ERR_MASK			0x08000000u	 //CAN总线无通信// 
#define CAN_OVERTIME_ERR_SHIFT		27

//模式
#define MODENULL  0//模式未知
#define MODEFACE  1//吹面
#define MODEFAFE  2//吹面吹脚
#define MODEFEET  3//吹脚
#define MODEFEDE  4//吹脚除霜
#define MODEFDEF  5//除霜

//模式控制数据
#define FaFeTOFeet	-30//吹面吹脚到吹脚
#define FeetTOFaFe	-5//吹面到吹面吹脚
#define FaceTOFaFe  10//吹脚到吹面吹脚
#define FaFeTOFace	35//吹面吹脚到吹面

#define MODE_FACE_FORCED_MASK 0x01
#define MODE_FEET_FORCED_MASK 0x02
#define MODE_FDEF_FORCED_MASK 0x04

#define humidity_inside_std 50//计算标准湿度
#define humidity_inside_prop 0.04f//湿度在温差计算中的权重

#define pid_a 0.81f
#define pid_b 0.15f
#define pid_c 0.04f


int16_t Heat_Cap_PIDControl(Heat_Cap_TypeDef* s_Heat_Cap_Type);
int16_t TakeControl(Heat_Cap_TypeDef* s_Heat_Cap_Type);
int16_t AC_ON_OFF_Control(Heat_Cap_TypeDef* s_Heat_Cap_Type);
int16_t MIX_Control(Heat_Cap_TypeDef* s_Heat_Cap_Type);
int16_t FAN_Speed_Control(Heat_Cap_TypeDef* s_Heat_Cap_Type);
int16_t MODE_Control(Heat_Cap_TypeDef* s_Heat_Cap_Type);
void AUTO_RUN(void);
void B31_Init(void);

extern u16 g_AUTO_Flag;
extern Heat_Cap_TypeDef s_Heat_Cap;
extern TIME_LEFT_TypeDef s_Time_Left;


void B31_Test(void);

#endif
