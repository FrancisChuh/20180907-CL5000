/**************************************************************************/
/*    ���쳬���߿Ƽ��ɷ����޹�˾          ��Ȩ����                        */
/**************************************************************************/
/*   @@BEGAIN_INTERNAL_LEGAL@@                                            */
/*                                                                        */
/*                   Copyright(C) Description                          	  */
/*     CHONGQING CHAOLI HI-TECH Co.,Ltd. Chongqing, China   				      */
/*     Unpublished work-rights reserved under the China Copyright Act.  	*/
/*     Use,duplication, or disclosure by the government is subject to   	*/
/*     restrictions set forth in the CDTT commercial license agreement. 	*/
/*																		                                    */
/*   @@END_INTERNAL_LEGAL@@												                        */
/**************************************************************************/
/*   �����ļ�����GPIO.c         										                      */
/*   Filename  ��GPIO.c         			                        						*/
/*   ����      ��������								                        		        */
/*   Author    ��Jack									                        	    	    */
/*   ����      ��10/23/2017						                        				    */
/*   Date      ��10/23/2017						                        					  */
/*   ��ǰ�汾  ��1.0									                        				    */
/*   Version	 ��1.0                                                      */
/*   ʵ��Ŀ��  ��I/O��ʼ��									                        		  */
/*   Purpose   ��GPIO_Init                                                */
/**************************************************************************/
/*   �޸ļ�¼  ����                                                       */
/*   ��� , MM/DD/YYYY,�汾���޸��ߣ��޸�����(������޸ļ�¼��������)     */
/*   Modi Report��                                                        */
/*   Index��Date��Version��Author, content                                */
/**************************************************************************/

#include "GPIO.h"

#include "TPD1053.h"
#include "modules_switch.h"
#include "TB9102.h"
#


const enum PTxn reserved_pins[]={
    PTE16,
    PTE15,
    PTD1,
    PTD16,
    PTE8,
    PTB5,
    PTD7,
    PTD6,
    PTD5,
    PTD12,
    PTD11,
    PTD10,
    PTD9,
    PTD8,
    PTA7,
    PTA6,
    PTA14,
    PTA13,
    PTA9,
    PTA8,
};

void Board_GPIO_Init(void)  //����I/O�ڵĳ�ʼ��
{
//    uint8_t i;
	Gpio_Enable_Port();//ʱ��ʹ��
    
    TPD1053_Init();//������ͷ���pm2.5���أ������ӣ�AQS����ŷ����س�ʼ��
    Switch_Init();//5V����
    TB9102_Init();//4��9102������
    
    SPI_IO_Init();//����spi�ӿ�
    
	Gpio_Init(LIN_SLP2_OUT,GP_OUT,SET);			//LIN2sleep���͵�ƽ��Ч
	Gpio_Init(LIN_WAKE2_OUT,GP_DIS,SET);		//LIN2wake���͵�ƽ��Ч
	Gpio_Init(LIN_SLP1_OUT,GP_OUT,SET);			//LIN1sleep���͵�ƽ��Ч
	Gpio_Init(LIN_WAKE1_OUT,GP_DIS,SET);		//LIN1wake���͵�ƽ��Ч
    
	Gpio_Init(CANSTB_OUT,GP_OUT,RESET);			//CANstandby���ߵ�ƽ��Ч

//	for(i=0;i<sizeof(reserved_pins)/sizeof(PTxn);i++)//δʹ�õ�gpio����Ϊ�������clear
//    {
//        Gpio_Init(reserved_pins[i],GP_DIS,RESET);
//    }
}

void SW_EXP(SW_STATUS new_status) //������ͷ���Դ����
{
  if(new_status==SW_ON)
  {
//		Gpio_Set(M_EXP_CTRL_OUT,SET);//�ߵ�ƽ����ֹ����ֹ
      
  }
  else
  {
//      Gpio_Set(M_EXP_CTRL_OUT,RESET);     //�͵�ƽ����ֹ����ͨ��
  }
}

void SW_ESV(SW_STATUS new_status) //��ŷ���Դ����
{
  if(new_status==SW_ON)
  {
//		Gpio_Set(M_VALVE_CTRL_OUT,SET);//�ߵ�ƽ����ֹ����ֹ 
  }
  else
  {
//    Gpio_Set(M_VALVE_CTRL_OUT,RESET);     //�͵�ƽ����ֹ����ͨ��
  }
}

void SW_Negativeion(SW_STATUS new_status) //�����ӵ�Դ����
{
  if(new_status==SW_ON)
  {
//    Gpio_Set(M_NEG_CTRL_OUT,SET);
  }
  else
  {
//    Gpio_Set(M_NEG_CTRL_OUT,RESET);
  }
}

void SW_CANSTB(SW_STATUS new_status) //CANģ��Standby
{
  if(new_status==SW_ON)
  {
    Gpio_Set(CANSTB_OUT,SET);
  }
  else
  {
    Gpio_Set(CANSTB_OUT,RESET);
  }
}
  
void SW_LIN1_SLP(SW_STATUS new_status) //LINģ��SLEEPģʽ������Ч
{
  if(new_status==SW_ON)
  {
    Gpio_Set(LIN_SLP1_OUT,RESET);
  }
  else
  {
    Gpio_Set(LIN_SLP1_OUT,SET);
  }
}

void SW_LIN2_SLP(SW_STATUS new_status) //LINģ��SLEEPģʽ������Ч
{
  if(new_status==SW_ON)
  {
    Gpio_Set(LIN_SLP2_OUT,RESET);
  }
  else
  {
    Gpio_Set(LIN_SLP2_OUT,SET);
  }
}

void SW_TB9102(SW_STATUS new_status) 
{
  if(new_status==SW_ON)
  {
		Gpio_Set(TB9102_MODE_OUT,SET);
		Gpio_Set(TB9102_SEL_OUT,SET);
  }           
  else        
  {           
		Gpio_Set(TB9102_SEL_OUT,RESET);
    Gpio_Set(TB9102_MODE_OUT,RESET);
  }
}

void SW_Power5V(SW_STATUS new_status) //5V��Դʹ��
{
  if(new_status==SW_ON)
  {
    Gpio_Set(M_POWER_EN_OUT,SET);
  }
  else
  {
    Gpio_Set(M_POWER_EN_OUT,RESET);
  }
}

void SW_PowerPM25(SW_STATUS new_status) //PM2.5��Դʹ��
{
  if(new_status==SW_ON)
  {
//    Gpio_Set(M_PM25_CTRL_OUT,SET);
  }
  else
  {
//    Gpio_Set(M_PM25_CTRL_OUT,RESET);
  }
}

void SW_AQS(SW_STATUS new_status) //AQS��Դʹ��
{
  if(new_status==SW_ON)
  {
//    Gpio_Set(M_AQS_CTRL_OUT,SET);
  }
  else
  {
//    Gpio_Set(M_AQS_CTRL_OUT,RESET);
  }
}

//end
