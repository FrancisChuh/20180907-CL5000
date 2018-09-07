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
/*   程序文件名：GPIO.c         										                      */
/*   Filename  ：GPIO.c         			                        						*/
/*   作者      ：何晓东								                        		        */
/*   Author    ：Jack									                        	    	    */
/*   日期      ：10/23/2017						                        				    */
/*   Date      ：10/23/2017						                        					  */
/*   当前版本  ：1.0									                        				    */
/*   Version	 ：1.0                                                      */
/*   实现目的  ：I/O初始化									                        		  */
/*   Purpose   ：GPIO_Init                                                */
/**************************************************************************/
/*   修改记录  ：无                                                       */
/*   序号 , MM/DD/YYYY,版本，修改者，修改内容(最近的修改记录在最上面)     */
/*   Modi Report：                                                        */
/*   Index，Date，Version，Author, content                                */
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

void Board_GPIO_Init(void)  //所有I/O口的初始化
{
//    uint8_t i;
	Gpio_Enable_Port();//时钟使能
    
    TPD1053_Init();//电磁膨胀阀，pm2.5开关，负离子，AQS，电磁阀开关初始化
    Switch_Init();//5V开关
    TB9102_Init();//4个9102的引脚
    
    SPI_IO_Init();//虚拟spi接口
    
	Gpio_Init(LIN_SLP2_OUT,GP_OUT,SET);			//LIN2sleep，低电平有效
	Gpio_Init(LIN_WAKE2_OUT,GP_DIS,SET);		//LIN2wake，低电平有效
	Gpio_Init(LIN_SLP1_OUT,GP_OUT,SET);			//LIN1sleep，低电平有效
	Gpio_Init(LIN_WAKE1_OUT,GP_DIS,SET);		//LIN1wake，低电平有效
    
	Gpio_Init(CANSTB_OUT,GP_OUT,RESET);			//CANstandby，高电平有效

//	for(i=0;i<sizeof(reserved_pins)/sizeof(PTxn);i++)//未使用的gpio设置为输出，并clear
//    {
//        Gpio_Init(reserved_pins[i],GP_DIS,RESET);
//    }
}

void SW_EXP(SW_STATUS new_status) //电磁膨胀阀电源开关
{
  if(new_status==SW_ON)
  {
//		Gpio_Set(M_EXP_CTRL_OUT,SET);//高电平，截止阀截止
      
  }
  else
  {
//      Gpio_Set(M_EXP_CTRL_OUT,RESET);     //低电平，截止阀导通；
  }
}

void SW_ESV(SW_STATUS new_status) //电磁阀电源开关
{
  if(new_status==SW_ON)
  {
//		Gpio_Set(M_VALVE_CTRL_OUT,SET);//高电平，截止阀截止 
  }
  else
  {
//    Gpio_Set(M_VALVE_CTRL_OUT,RESET);     //低电平，截止阀导通；
  }
}

void SW_Negativeion(SW_STATUS new_status) //负离子电源开关
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

void SW_CANSTB(SW_STATUS new_status) //CAN模块Standby
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
  
void SW_LIN1_SLP(SW_STATUS new_status) //LIN模块SLEEP模式，低有效
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

void SW_LIN2_SLP(SW_STATUS new_status) //LIN模块SLEEP模式，低有效
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

void SW_Power5V(SW_STATUS new_status) //5V电源使能
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

void SW_PowerPM25(SW_STATUS new_status) //PM2.5电源使能
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

void SW_AQS(SW_STATUS new_status) //AQS电源使能
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
