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
/*   程序文件名：PM25.c         										                        */
/*   Filename  ：PM25.c         			                        						  */
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

#include "PM25.h"

PM25_Struct s_PM25_IN;
PM25_Struct s_PM25_OUT;


void pm25_txd_cmd(PM25 *pm25,LINMsg *msg)
{
    if(pm25->cmd.PM25Swch==0)
    {
        msg->data[0]=0;
    }
    else
    {
        msg->data[0]=1;
    }
    
    msg->data[1]=0;
    msg->data[2]=0;
    msg->data[3]=0;
    msg->data[4]=0;
    msg->data[5]=0;
    msg->data[6]=0;
    msg->data[7]=0;
}

void pm25_rxd_status(PM25 *pm25,LINMsg *msg)
{
    uint8_t i;
    for(i=0;i<8;i++)
    {
        pm25->input_tmp[i]=msg->data[i];
    }
}

void pm25_proc(PM25 *pm25)
{
    ;
}
//end
