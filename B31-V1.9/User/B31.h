#ifndef _B31_H__
#define _B31_H__

#include "common.h"

#define Auto_Fdef 1
#define Hi_Eff 0

typedef struct
{
    int16_t Tem_Inside;       //�����¶�
    int16_t Tem_Purpose;      //�趨�¶�
	int16_t Tem_Slave_Purpose;	//�趨�¶�2
    int16_t DUAL_STATUS;				//dual״̬
    int16_t Humidity_Inside;  //����ʪ��
    int16_t Tem_Outside;      //�����¶�
    int16_t Air_Outside_qua;  //�����������
    int16_t TAKE;             //��ǰѭ��ģʽ��0-��ѭ����1��ѭ��
    int16_t Mode_PPS;         //Ŀ��ģʽ
    int16_t SUN_Val;          //�����ն�ֵ
    int16_t AC_IN_STATUS;     //����AC״̬
    int16_t AC_BAT_STATUS;    //���AC״̬   
    int16_t PTC_IN_STATUS;    //����PTC״̬
    int16_t PTC_BAT_STATUS;   //���PTC״̬
    int16_t FDEF2_STATUS;     //ǰ������״̬
    int16_t RDEF_STATUS;      //�󵵼���״̬
    int16_t MIX_Vol;          //����ѹ
    int16_t Tem_In_err;       //�����¶�-�趨�¶�
    int16_t Tem_Out_err;      //�����¶�-�趨�¶�
    int16_t Tem_Out_In_err;   //�����¶�-�����¶�
    int16_t Tem_err_S;        //�趨�²�У׼������������⣩
    int16_t Tem_err_S_H;      //�趨�²�У׼��������������ʪ�ȣ�
    int16_t Set_Fan;          //�趨������λ��00-80������1.5����15��
    int16_t Set_Fan_Now;      //��ǰ����
    int16_t Heat_Cap;         //��������
    int16_t Break;            //ɲ���ź�
    int16_t AC_ON_TEM;        //AC�����¶ȵ�
    int16_t AC_OFF_TEM;       //AC�ر��¶ȵ�
    int16_t Rapid_Speed_Up;   //������
    int16_t SEATL_STATUS;     //�����μ���״̬
    int16_t SEATR_STATUS;			//�����μ���״̬
    int16_t ESV_STATUS;				//��ֹ����ͨ״̬
    int16_t PM25_STATUS;			//PM25״̬
    int16_t Negativeion_STATUS;//������״̬
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

/*����g_AUTO_Flag*/
#define AUTO_TAKE_MASK  0x0001u  //ѭ���Զ���־λ
#define AUTO_TAKE_SHIFT 0
#define AUTO_MODE_MASK  0x0002u  //ģʽ�Զ���־λ
#define AUTO_MODE_SHIFT 1
#define AUTO_FAN_MASK   0x0004u  //�����Զ���־λ
#define AUTO_FAN_SHIFT  2
#define AUTO_AC_MASK    0x0008u  //ac������־λ
#define AUTO_AC_SHIFT   3
#define AUTO_TEMP_MASK  0x0010u  //�Զ�����־λ
#define AUTO_TEMP_SHIFT 4
#define AUTO_PTC_MASK   0x0020u  //�Զ�PTC��־λ
#define AUTO_PTC_SHIFT  5

/*����g_Diog_Flag*/
#define MOTER_TEMP_ERR_MASK       0x00000001u  //�¶�ִ������
#define MOTER_TEMP_ERR_SHIFT      0 
#define MOTER_REC_ERR_MASK        0x00000002u  //ѭ��ִ������
#define MOTER_REC_ERR_SHIFT       1 
#define MOTER_MODE_ERR_MASK       0x00000004u  //ģʽִ������
#define MOTER_MODE_ERR_SHIFT      2 
#define TSENSOR_EVA_OPEN_MASK     0x00000008u  //�������¶ȴ�������·
#define TSENSOR_EVA_OPEN_SHIFT    3 
#define TSENSOR_EVA_SHORT_MASK    0x00000010u  //�������¶ȴ�������·
#define TSENSOR_EVA_SHORT_SHIFT   4 
#define TSENSOR_OUT_OPEN_MASK     0x00000020u  //���´�������·
#define TSENSOR_OUT_OPEN_SHIFT    5
#define TSENSOR_OUT_SHORT_MASK    0x00000040u  //���´�������·
#define TSENSOR_OUT_SHORT_SHIFT   6
#define TSENSOR_IN_OPEN_MASK      0x00000080u  //���´�������·
#define TSENSOR_IN_OPEN_SHIFT     7
#define TSENSOR_IN_SHORT_MASK     0x00000100u  //���´�������·
#define TSENSOR_IN_SHORT_SHIFT    8
#define TWindshield_OPEN_MASK     0x00000200u  //���粣���¶ȿ�·//
#define TWindshield_OPEN_SHIFT    9
#define TWindshield_SHORT_MASK    0x00000400u  //���粣���¶ȶ�·//
#define TWindshield_SHORT_SHIFT   10
#define RHWindshield_OPEN_MASK    0x00000800u  //���粣��ʪ�ȿ�·//
#define RHWindshield_OPEN_SHIFT   11
#define RHWindshield_SHORT_MASK   0x00001000u  //���粣��ʪ�ȶ�·//
#define RHWindshield_SHORT_SHIFT  12
#define TPRESSLOW_OPEN_MASK       0x00002000u  //��ѹ�¶ȿ�·
#define TPRESSLOW_OPEN_SHIFT      13
#define TPRESSLOW_SHORT_MASK      0x00004000u  //��ѹ�¶ȶ�·//
#define TPRESSLOW_SHORT_SHIFT     14
#define PRESSLOW_OPEN_MASK        0x00008000u  //��ѹѹ����·//
#define PRESSLOW_OPEN_SHIFT    	  15
#define PRESSLOW_SHORT_MASK       0x00010000u  //��ѹѹ����·//
#define PRESSLOW_SHORT_SHIFT      16
#define SENSOR_PHOTO_OPEN_MASK    0x00020000u  //���⿪·//
#define SENSOR_PHOTO_OPEN_SHIFT   17
#define SENSOR_PHOTO_SHORT_MASK   0x00040000u  //�����·
#define SENSOR_PHOTO_SHORT_SHIFT  18
#define MOTOR_TWV_ERR_MASK        0x00080000u  //��ͨ����
#define MOTOR_TWV_ERR_SHIFT       19
#define VOL12V_OVERVOL_MASK       0x00100000u  //��ص�ѹ��ѹ
#define VOL12V_OVERVOL_SHIFT      20
#define VOL12V_UNDERVOL_MASK      0x00200000u  //��ص�ѹǷѹ
#define VOL12V_UNDERVOL_SHIFT     21
#define PM25_IN_SENSOR_ERR_MASK   0x00400000u	 //PM2.5���ڴ�������//
#define PM25_IN_SENSOR_ERR_SHIFT  22
#define PM25_OUT_SENSOR_ERR_MASK  0x00800000u	 //PM2.5���⴫������//
#define PM25_OUT_SENSOR_ERR_SHIFT 23
#define PM25_IN_NACK_ERR_MASK			0x01000000u	 //PM2.5������ͨ��//
#define PM25_IN_NACK_ERR_SHIFT		24 
#define PM25_OUT_NACK_ERR_MASK		0x02000000u	 //PM2.5������ͨ��// 
#define PM25_OUT_NACK_ERR_SHIFT		25
#define PANEL_NACK_ERR_MASK				0x04000000u	 //���LIN������ͨ��// 
#define PANEL_NACK_ERR_SHIFT			26
#define CAN_OVERTIME_ERR_MASK			0x08000000u	 //CAN������ͨ��// 
#define CAN_OVERTIME_ERR_SHIFT		27

//ģʽ
#define MODENULL  0//ģʽδ֪
#define MODEFACE  1//����
#define MODEFAFE  2//���洵��
#define MODEFEET  3//����
#define MODEFEDE  4//���ų�˪
#define MODEFDEF  5//��˪

//ģʽ��������
#define FaFeTOFeet	-30//���洵�ŵ�����
#define FeetTOFaFe	-5//���浽���洵��
#define FaceTOFaFe  10//���ŵ����洵��
#define FaFeTOFace	35//���洵�ŵ�����

#define MODE_FACE_FORCED_MASK 0x01
#define MODE_FEET_FORCED_MASK 0x02
#define MODE_FDEF_FORCED_MASK 0x04

#define humidity_inside_std 50//�����׼ʪ��
#define humidity_inside_prop 0.04f//ʪ�����²�����е�Ȩ��

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
