/**************************************************************************/
/*    重庆超力高科技股份有限公司          版权所有                        */
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
/*   程序文件名：main.c         										                      */
/*   Filename  ：main.c         			                        						*/
/*   作者      ：何晓东								                        		        */
/*   Author    ：Jack									                        	    	    */
/*   日期      ：06/08/2018						                        				    */
/*   Date      ：06/08/2018						                        					  */
/*   当前版本  ：1.0									                        				    */
/*   Version	 ：1.0                                                      */
/*   实现目的  ：主函数											                        		  */
/*   Purpose   ：Main Function                                            */
/**************************************************************************/
/*   修改记录  ：无                                                       */
/*   序号 , MM/DD/YYYY,版本，修改者，修改内容(最近的修改记录在最上面)     */
/*   Modi Report：                                                        */
/*   Index，Date，Version，Author, content                                */
/**************************************************************************/

#include "main.h"
#include "TB9102.h"
#include "modules_switch.h"
#include "can.h"

int main(void)
{
    SystemCoreClockConfigure();   /* configure system core clock */
    delay_ms(50);
    FLASH_Init();							//FLASH初始化，使用EEPROM必须调用
    FlexRam_Init();						//EEPROM初始化
    Board_GPIO_Init();				//IO初始化	
    Board_PIT_Init();					//周期定时器
    Board_LIN_Init(LIN_bps);	//Lin初始化
    Board_ADC_Init();					//ADC初始化
    Board_PWM_Init();         //输出PWM波,PWM读取,读取和输出不要同一个FTM
    Board_CAN_Init(); 				//初始化CAN
    Board_WDOG_Init();        //看门狗初始化
    
    _5VR_On();//开启温度，位置传感器电源
    
    B31_Init();
    
    IRQ_init();               //低功耗模式
    
    while(1)
    {
        Process();			  //主循环
    }
}
//end
