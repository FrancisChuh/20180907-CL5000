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
/*   程序文件名：RTC.h         										                        */
/*   Filename  ：RTC.h         			                        						  */
/*   作者      ：何晓东								                        		        */
/*   Author    ：Jack									                        	    	    */
/*   日期      ：10/23/2017						                        				    */
/*   Date      ：10/23/2017						                        					  */
/*   当前版本  ：1.0									                        				    */
/*   Version	 ：1.0                                                      */
/*   实现目的  ：RTC初始化									                        		  */
/*   Purpose   ：RTC_Init                                                 */
/**************************************************************************/
/*   修改记录  ：无                                                       */
/*   序号 , MM/DD/YYYY,版本，修改者，修改内容(最近的修改记录在最上面)     */
/*   Modi Report：                                                        */
/*   Index，Date，Version，Author, content                                */
/**************************************************************************/

#ifndef _RTC_H__
#define _RTC_H__

#include <stdint.h>
#include "SKEAZ1284.h"
#include "process.h"

#define RTC_OUTPUT_ENABLE           1	/*!< enable RTCO pin  */ 
#define RTC_INTERRUPT_ENABLE        1	/*!< enable RTC interrupt  */ 
#define RTC_CLKSRC_EXTERNAL         0	/*!< select external clock as RTC clock source  */
#define RTC_CLKSRC_1KHZ             1	/*!< select LPO as RTC clock source  */
#define RTC_CLKSRC_IREF             2	/*!< select internal reference clock as RTC clock source  */
#define RTC_CLKSRC_BUS              3	/*!< select bus clock as RTC clock source  */
#define RTC_CLK_PRESCALER_128       1	/*!< presalcer is 1 or 128 according to RTCLKS bits */
#define RTC_CLK_PRESCALER_256       2	/*!< presalcer is 2 or 256 according to RTCLKS bits */
#define RTC_CLK_PRESCALER_512       3	/*!< presalcer is 4 or 512 according to RTCLKS bits */
#define RTC_CLK_PRESCALER_1024      4	/*!< presalcer is 8 or 1024 according to RTCLKS bits */
#define RTC_CLK_PRESCALER_2048      5	/*!< presalcer is 16 or 2048 according to RTCLKS bits */
#define RTC_CLK_PRESCALER_100       6	/*!< presalcer is 32 or 100 according to RTCLKS bits */
#define RTC_CLK_PRESCALER_1000      7	/*!< presalcer is 64 or 1000 according to RTCLKS bits */

#define RTC_Out		0 //PTC5输出
#define RTC_IntEn	1

void Board_RTC_Init(void);
void Sleep_RTC_Init(void);
void Sleep_RTC_DeInit(void);

extern u8 RTC_Sleep_Flag;
extern u8 RTC_Flag;




#endif
