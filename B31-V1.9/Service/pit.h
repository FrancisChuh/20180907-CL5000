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
/*   程序文件名：PIT.h         										                        */
/*   Filename  ：PIT.h         			                        						  */
/*   作者      ：何晓东								                        		        */
/*   Author    ：Jack									                        	    	    */
/*   日期      ：10/23/2017						                        				    */
/*   Date      ：10/23/2017						                        					  */
/*   当前版本  ：1.0									                        				    */
/*   Version	 ：1.0                                                      */
/*   实现目的  ：PIT初始化									                        		  */
/*   Purpose   ：PIT_Init                                                 */
/**************************************************************************/
/*   修改记录  ：无                                                       */
/*   序号 , MM/DD/YYYY,版本，修改者，修改内容(最近的修改记录在最上面)     */
/*   Modi Report：                                                        */
/*   Index，Date，Version，Author, content                                */
/**************************************************************************/

#ifndef _PIT_H__
#define _PIT_H__

#include "common.h"

#define time_15ms_flag_MASK     0x01 //15mS
#define time_15ms_flag_SHIFT    0
#define time_50ms_flag_MASK     0x02 //50mS
#define time_50ms_flag_SHIFT    1
#define time_100ms_flag_MASK    0x04 //100mS
#define time_100ms_flag_SHIFT   2
#define time_200ms_flag_MASK    0x08 //200mS
#define time_200ms_flag_SHIFT   3
#define time_500ms_flag_MASK    0x10 //500mS
#define time_500ms_flag_SHIFT   4
#define time_1000ms_flag_MASK   0x20 //1000mS
#define time_1000ms_flag_SHIFT  5
#define time_10ms_flag_MASK     0x40 //1000mS
#define time_10ms_flag_SHIFT    6
#define time_20ms_flag_MASK     0x80 //1000mS
#define time_20ms_flag_SHIFT    7
#define time_1ms_flag_MASK     	0x0100 //1mS
#define time_1ms_flag_SHIFT    	8



void Board_PIT_Init(void);

extern u16 time_ms_flag;

#endif
