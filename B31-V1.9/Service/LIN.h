/**************************************************************************/
/*    重庆超力高科技股份有限公司          版权所有                        */
/**************************************************************************/
/*   @@BEGAIN_INTERNAL_LEGAL@@                                            */
/*                                                                        */
/*                   Copyright(C) Description                          	  */
/*     CHONGQING CHAOLI HI-TECH Co.,Ltd. Chongqing, China                 */
/*     Unpublished work-rights reserved under the China Copyright Act.    */
/*     Use,duplication, or disclosure by the government is subject to   	*/
/*     restrictions set forth in the CDTT commercial license agreement. 	*/
/*																		                                    */
/*   @@END_INTERNAL_LEGAL@@												                        */
/**************************************************************************/
/*   程序文件名：LIN.h         										                        */
/*   Filename  ：LIN.h         			                        						  */
/*   作者      ：何晓东								                        		        */
/*   Author    ：Jack									                        	    	    */
/*   日期      ：10/23/2017						                        				    */
/*   Date      ：10/23/2017						                        					  */
/*   当前版本  ：1.0									                        				    */
/*   Version	 ：1.0                                                      */
/*   实现目的  ：LIN初始化，接收和发送									                  */
/*   Purpose   ：LIN_Init                                                 */
/**************************************************************************/
/*   修改记录  ：无                                                       */
/*   序号 , MM/DD/YYYY,版本，修改者，修改内容(最近的修改记录在最上面)     */
/*   Modi Report：                                                        */
/*   Index，Date，Version，Author, content                                */
/**************************************************************************/
#ifndef _LIN_H__
#define _LIN_H__

#include <stdint.h>

#include "me_type.h"

#include "TJA1021T.h"
#include "uart_lin.h"

//#include "LINprotocol.h"

#define LIN_bps 19200

//LIN_state
#define LIN_IDLE      0
#define LIN_BREAK     1
#define LIN_SYNBYTE   2
#define LIN_TRANSMIT  3
#define LIN_RECEIVE   4
#define LIN_CHECKSUM  5


typedef enum LIN_Type
{
    MASTER,
    SLAVE,
}LIN_Type;

typedef struct LIN LIN;

typedef struct
{
    uint8_t PID;
    uint8_t LEN;
    uint8_t data[8];
    uint8_t check_sum;
} LINMsg;

typedef void LIN_ISSUE_Proc(LINMsg*);

typedef struct LIN_ISSUE{
		LIN_ISSUE_Proc *proc;
		LIN_ISSUE_Proc *call_back;
}LIN_ISSUE;

typedef void LIN_TR(LINMsg *msg);

typedef struct LIN{
    const void      *LinTransceiver;  //LIN收发器
    const LinUart   *lin_uart;  //LIN的串口
    LIN_Type        lin_type;   //这个LIN时Master还是Slave
    LIN_ISSUE_Proc  *issue_cb;      
    LINMsg          tx_msg;
    LINMsg          rx_msg;
    uint8_t         rx_state;
    uint8_t         rx_cnt;
    uint8_t         rx_tmp[11];
    uint8_t         tx_cnt;
    uint8_t         tx_tmp[11];
}LIN;

#include "LINprotocol.h"

void Board_LIN_Sleep(void);
void Board_LIN_Init(uint32_t UART_BaudRate);
void LIN_TX(LIN *lin,u8* buf,u8 len,u8 PID);

void LIN_ALL_Init(void);
void LIN_ALL_Deinit(void);
void LIN_Proc(void);

void LIN_Task(void);


extern u8 LIN_RX_Flag;

#endif
