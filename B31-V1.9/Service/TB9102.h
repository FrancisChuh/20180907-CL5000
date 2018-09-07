#ifndef _TB9102_H__
#define _TB9102_H__


//#include "common.h"
#include "S32_gpio.h"
#include "common.h"

#define TB9102_SEL_PIN  PTE0
#define TB9102_MODE_PIN PTC5


#define TB9102_OA1   0x0001 //OA1_H
#define TB9102_OA2   0x0003 //OA2_H
#define TB9102_OB1   0x0005 //OB1_H
#define TB9102_OB2   0x0007 //OB2_H
#define TB9102_OC1   0x0009 //OC1_H
#define TB9102_OC2   0x000B //OC2_H

//#define TB9102_OUTPUT_H(tb9102,output_pin)  *tb9102.output_buf|=(1<<output_pin), \
//                                            *tb9102.output_buf&=~(1<<(output_pin+1));
//#define TB9102_OUTPUT_L(tb9102,output_pin)  *tb9102.output_buf&=~(1<<output_pin),\
//                                            *tb9102.output_buf|=(1<<(output_pin+1));


typedef struct TB9102{
    enum PTxn   CSB_pin;
    enum PTxn   SEL_pin;
    enum PTxn   MOD_pin;
    uint16_t    output_buf;          //���
    uint16_t    input_buf;           //����
}TB9102;



#define SPI_CS1_OUT				    PTB10	//74
#define SPI_CS2_OUT				    PTB11	//75
#define SPI_CS4_OUT				    PTB9	//76
#define SPI_CS3_OUT				    PTB8	//77

#define TB9102_SEL_OUT		PTE0	//94
#define TB9102_MODE_OUT		PTC5	//95


void TB9102_OUTPUT_H(TB9102 *tb9102,uint16_t pin);
void TB9102_OUTPUT_L(TB9102 *tb9102,uint16_t pin);
void TB9102_OUTPUT_HZ(TB9102 *tb9102,uint16_t pin);


void tb9102_update(TB9102 *tb9102);   //��д�Ĵ���
void TB9102_Sleep(TB9102 *tb9102);    //��������ģʽ
void TB9102_All_Sleep(void);          //���н�������
void TB9102_Wake(TB9102 *tb9102);     //�˳�����ģʽ
void TB9102_All_Wake(void);           //�����˳�����


void TB9102_Init(void);//��ʼ��
#endif
