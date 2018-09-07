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
/*   程序文件名：LINprotocol.h         										                */
/*   Filename  ：LINprotocol.h         			                        			*/
/*   作者      ：何晓东								                        		        */
/*   Author    ：Jack									                        	    	    */
/*   日期      ：10/23/2017						                        				    */
/*   Date      ：10/23/2017						                        					  */
/*   当前版本  ：1.0									                        				    */
/*   Version	 ：1.0                                                      */
/*   实现目的  ：LIN协议符合，发送数据处理							                  */
/*   Purpose   ：                                                         */
/**************************************************************************/
/*   修改记录  ：无                                                       */
/*   序号 , MM/DD/YYYY,版本，修改者，修改内容(最近的修改记录在最上面)     */
/*   Modi Report：                                                        */
/*   Index，Date，Version，Author, content                                */
/**************************************************************************/

#ifndef _LINPROTOCLO_H__
#define _LINPROTOCLO_H__

#include <stdint.h>

#include "LIN.h"
#include "cpc.h"



#define ID2PID_1(ID)  (ID|(((ID^(ID>>1)^(ID>>2)^(ID>>4))&0x01)<<6))
#define ID2PID_2(ID)  (ID|((~((ID>>1)^(ID>>3)^(ID>>4)^(ID>>5))&0x01)<<7))
#define ID2PID(ID)    (ID2PID_2(ID2PID_1(ID))) 		//由id计算pid

//受保护ID
#define PID_WPTC_01	(ID2PID(ID_WPTC_01))          //水热ptc，返回数据
#define PID_APTC_01	(ID2PID(ID_APTC_01))          //风热ptc，返回数据
#define PID_COMP_01	(ID2PID(ID_COMP_01))          //电动压缩机，返回数据
#define PID_CPC_01	(ID2PID(ID_CPC_01 ))          //面板，返回数据
#define PID_PM25_01	(ID2PID(ID_PM25_01))          //pm2.5返回数据
                                       
#define PID_CLIM_01	(ID2PID(ID_CLIM_01))          //水热ptc控制
#define PID_CLIM_02	(ID2PID(ID_CLIM_02))          //空气ptc控制
#define PID_CLIM_03	(ID2PID(ID_CLIM_03))          //压缩机控制
#define PID_CLIM_04	(ID2PID(ID_CLIM_04))          //面板控制
#define PID_CLIM_05	(ID2PID(ID_CLIM_05))          //pm2.5控制
  
//ID
#define ID_WPTC_01	0x31
#define ID_APTC_01	0x32
#define ID_COMP_01  0x33
#define ID_CPC_01   0x34
#define ID_PM25_01  0x35
#define ID_CLIM_01  0x21
#define ID_CLIM_02	0x22
#define ID_CLIM_03  0x23
#define ID_CLIM_04  0x24
#define ID_CLIM_05  0x25

#define WPTC_01_LEN		8
#define APTC_01_LEN		8
#define COMP_01_LEN		8
#define CPC_01_LEN		8
#define PM25_01_LEN		8
#define CLIM_01_LEN		8
#define CLIM_02_LEN		8
#define CLIM_03_LEN		8
#define CLIM_04_LEN		8
#define CLIM_05_LEN		8

#define DIS_DUAL_MASK   0x01
#define DIS_AUTO_MASK   0x02
#define DIS_FDEF2_MASK  0x04
#define DIS_AC_MASK     0x08
#define DIS_PTC_MASK    0x10
#define DIS_REC_MASK    0x20
#define DIS_FDEF_MASK   0x40
#define DIS_RDEF_MASK   0x80




#endif
