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
/*   程序文件名：PM25.h         										                        */
/*   Filename  ：PM25.h         			                        						  */
/*   作者      ：何晓东								                        		        */
/*   Author    ：Jack									                        	    	    */
/*   日期      ：10/23/2017						                        				    */
/*   Date      ：10/23/2017						                        					  */
/*   当前版本  ：1.0									                        				    */
/*   Version	 ：1.0                                                      */
/*   实现目的  ：         									                        		  */
/*   Purpose   ：                                                         */
/**************************************************************************/
/*   修改记录  ：无                                                       */
/*   序号 , MM/DD/YYYY,版本，修改者，修改内容(最近的修改记录在最上面)     */
/*   Modi Report：                                                        */
/*   Index，Date，Version，Author, content                                */
/**************************************************************************/

#ifndef _PM25_H__
#define _PM25_H__


#include <stdint.h>
#include "LIN.h"


typedef struct{
  uint16_t PM25_DENSITY;
  uint8_t ERROR_status;
	uint8_t MsgRollingCount;
  uint8_t Response_Error;
} PM25_Struct;

extern PM25_Struct s_PM25_IN;
extern PM25_Struct s_PM25_OUT;




/*       PM2.5相关操作            */
/*       */
typedef struct PM25_Status{
    uint8_t InDnst;
    uint8_t ErrSts;
    uint8_t MassgRolgCnt;
    uint8_t RespErr;
}PM25_Status;

typedef struct PM25_CMD{
    uint8_t PM25Swch;
}PM25_CMD;



//typedef struct PM25_Swicht{
//    
//}PM25_Switch;

typedef struct PM25
{
    PM25_Status status;
    PM25_CMD    cmd;
    uint8_t     input_tmp[8];
}PM25;
#endif
