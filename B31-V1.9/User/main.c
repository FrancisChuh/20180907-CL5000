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
/*   �����ļ�����main.c         										                      */
/*   Filename  ��main.c         			                        						*/
/*   ����      ��������								                        		        */
/*   Author    ��Jack									                        	    	    */
/*   ����      ��06/08/2018						                        				    */
/*   Date      ��06/08/2018						                        					  */
/*   ��ǰ�汾  ��1.0									                        				    */
/*   Version	 ��1.0                                                      */
/*   ʵ��Ŀ��  ��������											                        		  */
/*   Purpose   ��Main Function                                            */
/**************************************************************************/
/*   �޸ļ�¼  ����                                                       */
/*   ��� , MM/DD/YYYY,�汾���޸��ߣ��޸�����(������޸ļ�¼��������)     */
/*   Modi Report��                                                        */
/*   Index��Date��Version��Author, content                                */
/**************************************************************************/

#include "main.h"
#include "TB9102.h"
#include "modules_switch.h"
#include "can.h"

int main(void)
{
    SystemCoreClockConfigure();   /* configure system core clock */
    delay_ms(50);
    FLASH_Init();							//FLASH��ʼ����ʹ��EEPROM�������
    FlexRam_Init();						//EEPROM��ʼ��
    Board_GPIO_Init();				//IO��ʼ��	
    Board_PIT_Init();					//���ڶ�ʱ��
    Board_LIN_Init(LIN_bps);	//Lin��ʼ��
    Board_ADC_Init();					//ADC��ʼ��
    Board_PWM_Init();         //���PWM��,PWM��ȡ,��ȡ�������Ҫͬһ��FTM
    Board_CAN_Init(); 				//��ʼ��CAN
    Board_WDOG_Init();        //���Ź���ʼ��
    
    _5VR_On();//�����¶ȣ�λ�ô�������Դ
    
    B31_Init();
    
    IRQ_init();               //�͹���ģʽ
    
    while(1)
    {
        Process();			  //��ѭ��
    }
}
//end
