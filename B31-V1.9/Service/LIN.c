/**************************************************************************/
/*    重庆超力高科技股份有限公司          版权所有                        */
/**************************************************************************/
/*   @@BEGAIN_INTERNAL_LEGAL@@                                            */
/*                                                                        */
/*                   Copyright(C) Description                             */
/*     CHONGQING CHAOLI HI-TECH Co.,Ltd. Chongqing, China                 */
/*     Unpublished work-rights reserved under the China Copyright Act.    */
/*     Use,duplication, or disclosure by the government is subject to     */
/*     restrictions set forth in the CDTT commercial license agreement.   */
/*                                                                        */
/*   @@END_INTERNAL_LEGAL@@                                               */
/**************************************************************************/
/*   程序文件名：LIN.c                                                    */
/*   Filename  ：LIN.c                                                    */
/*   作者      ：何晓东                                                   */
/*   Author    ：Jack                                                     */
/*   日期      ：10/23/2017                                               */
/*   Date      ：10/23/2017                                               */
/*   当前版本  ：1.0                                                      */
/*   Version     ：1.0                                                    */
/*   实现目的  ：LIN初始化，接收和发送                                    */
/*   Purpose   ：LIN_Init                                                 */
/**************************************************************************/
/*   修改记录  ：无                                                       */
/*   序号 , MM/DD/YYYY,版本，修改者，修改内容(最近的修改记录在最上面)     */
/*   Modi Report：                                                        */
/*   Index，Date，Version，Author, content                                */
/**************************************************************************/
#include "LIN.h"



//static u8 LIN_TX_Buf[11];     //0x55+id+8+1
//static u8 *pLIN_TX_Buf;
//static u8 LIN_TX_Len=0;
u8 LIN_RX_Flag=0;


//extern LINMsg LIN_RX_Msg;
//extern LINMsg LIN_TX_Msg;


#define LinTransceiverInit TJA1021T_INIT  //定义收发器初始化，去初始化类型
#define LinTR TJA1021T  //定义收发器类型
extern const TJA1021T tja1021t_0;   //收发器实例化


extern const LinUart lin_uart_1;    //lin_uart


LIN lin1={
    .LinTransceiver=&tja1021t_0, //收发器绑定
    .lin_uart=&lin_uart_1,        //uart_lin
    .lin_type=MASTER,               //lin类型
};


void Lin1_Init(void)    
{
    ;
}

void Lin_Init(LIN *lin)  //lin初始化
{
    /*收发器初始化*/
    LinTR *lin_tr;
    LinTransceiverInit * init;
    lin_tr=(LinTR *)lin->LinTransceiver;
    init=(LinTransceiverInit *)lin_tr->init;
    init(lin_tr);
}

void Lin_Deinit(LIN *lin)   //lin去初始化
{
    LinTR *lin_tr;
    LinTransceiverInit * deinit;
    lin_tr=(LinTR *)lin->LinTransceiver;
    deinit=(LinTransceiverInit *)lin_tr->deinit;
    deinit(lin_tr);
}

void Board_LIN_Init(uint32_t UART_BaudRate)
{
    Uart_Init(UART1,UART_BaudRate);
    LPUART1->STAT |=LPUART_STAT_BRK13_MASK;     //13位断点
    LPUART1->STAT |=LPUART_STAT_LBKDE_MASK;     //开LIN断点检测
    LPUART1->BAUD |=LPUART_BAUD_LBKDIE_MASK;    //开断点检测中断
    NVIC_Init(LPUART1_RxTx_IRQn,3);                            //中断优先级设置
}

void Board_LIN_Sleep(void)
{
    Uart_DeInit(UART1);
}

void LIN_Init(LIN *lin)
{
    ;
}

void LIN_Deinit(LIN *lin)
{
    ;
}

/*LIN发送数据代码*/
void LIN_Master_TX(LIN *lin)
{
    u8 i;
    u16 sum;
    LINMsg *msg=&lin->tx_msg;
    
    LIN_MASTER_TX_BreakF();//间隔场：特殊字符，不符合串口规则
    
    if(msg->LEN==0)
    {
        lin->tx_tmp[1]=0x55;             //同步场
        //ID = ID2PID(ID);//计算pid
        lin->tx_tmp[0]=msg->PID;             //PID
        lin->tx_cnt=2;
    }
    else       //有数据发送
    {
        lin->tx_tmp[msg->LEN+2]=0x55;             //同步场
        //ID = ID2PID(ID);//计算pid
        lin->tx_tmp[msg->LEN+1]=msg->PID;             //PID
        sum=msg->PID;
        for(i=0; i< msg->LEN; i++)
        {
            lin->tx_tmp[8-i] = msg->data[i];
            sum+=msg->data[i];
            if(sum>0xff)
            {
                sum -= 0xff;
            }
        }
        sum = (~sum) & 0xff;
        lin->tx_tmp[8-msg->LEN]=sum;
        lin->tx_cnt=msg->LEN+3;
    }
    /*开发送寄存器为空中断:shift寄存器为空时，装入Tx_Buffer*/
    LPUART1->CTRL |= LPUART_CTRL_TIE_MASK;
}


void Lin_RX_Reset(LIN *lin);
void Lin_Got_BK(LIN *lin);

void Lin_RX_Byte(LIN *lin ,uint8_t byte)//接收字节
{
    static uint16_t sum=0;
    if(lin->rx_cnt==0)
    {
        if(byte==0x55)
        {
            lin->rx_cnt++;
            ;//进入下一阶段
        }
        else
        {
            Lin_RX_Reset(lin);
        }
    }
    else if(lin->rx_cnt==1) //接收pid
    {
        lin->rx_msg.PID=byte;
        lin->rx_cnt++;
        sum=lin->rx_msg.PID;
        if(lin->lin_type==SLAVE) //如果是slave，则看是否要发送数据
        {
            ;//判断pid，看是发送，还是回复
        }
    }
    else if(lin->rx_cnt>1 && lin->rx_cnt<10) //接收数据
    {
        lin->rx_msg.data[lin->rx_cnt-2]=byte;
        sum+=byte;
        lin->rx_cnt++;
        if(sum>0xff)
        {
            sum-=0xff;
        }
    }
    else if(lin->rx_cnt==10) //接收校验和
    {
        lin->rx_msg.check_sum=byte;
        sum=(~sum)&0xff;
        if(lin->rx_msg.check_sum==sum)
        {
            if(lin->issue_cb!=0)
            {
                lin->issue_cb(&lin->rx_msg);//调用处理流回掉函数
                lin->issue_cb=0;            //清除回调函数
            }
            Lin_RX_Reset(lin);
        }
        else    //校验和错误
        {
            Lin_RX_Reset(lin);;
        }
    }
    else    //数据量太多,按道理不会到这里来
    {
        Lin_RX_Reset(lin);
    }
}

void Lin_RX_BK(LIN *lin) //收到断点字符
{
    lin->rx_state=LIN_BREAK;
    lin->rx_cnt=0;
}

void Lin_RX_Reset(LIN *lin)//复位
{
    lin->rx_state=LIN_IDLE;
    lin->rx_cnt=0;
    lin->lin_uart->uartn->STAT |= LPUART_STAT_LBKDE_MASK;
}

void LIN_LPUART_RxTx_IRQHandler(LIN *lin)
{
    LPUART_Type *lp_uart=lin->lin_uart->uartn;
    if(lp_uart->STAT & LPUART_STAT_TDRE_MASK)//发送中断标志
    {
        if(lin->tx_cnt)
        {
            lin->tx_cnt--;
            lp_uart->DATA=lin->tx_tmp[lin->tx_cnt];
        }
        else
        {
            lp_uart->CTRL &= ~LPUART_CTRL_TIE_MASK;//发送关中断
        }
    }
    
    if(lp_uart->STAT & LPUART_STAT_OR_MASK) //接收溢出:字节未及时处理
    {
        (void)lp_uart->DATA;
        Lin_RX_Reset(lin);//lin进入空闲状态
    }
    else
    {
        if(lp_uart->STAT & LPUART_STAT_LBKDIF_MASK) //收到lin的断点字符
        {
            lp_uart->STAT |= LPUART_STAT_LBKDIF_MASK;//清零断点标志
            lp_uart->STAT &= ~LPUART_STAT_LBKDE_MASK;//关闭断点检测
            
            Lin_RX_BK(lin);//进入lin break
            
        }
        if(lp_uart->STAT & LPUART_STAT_RDRF_MASK)   //接收中断
        {
            if(lp_uart->STAT & LPUART_STAT_FE_MASK) //停止位错误
            {
                if(lp_uart->DATA==0x00)//由于前面的没得响应
                {
                    Lin_RX_BK(lin);//进入lin break：在上一帧右毛病的情况下，会进入这一分支
                }
                else
                {
                    Lin_RX_Reset(lin);//进入idle
                }
            }
            else    //收到一个byte数据
            {
                Lin_RX_Byte(lin,lp_uart->DATA);
            }
        }
    }
}

void LPUART1_RxTx_IRQHandler()//中断函数
{
    LIN_LPUART_RxTx_IRQHandler(&lin1);
}

extern const LIN_ISSUE lin_1_iussues[2];

uint16_t lin1_err_cnt=0;

/*LIN1发送函数*/
void Master_LIN_1_Proc(void)
{
    static unsigned char num=0;
    if(lin1.issue_cb!=NULL)
    {
        lin1_err_cnt++;//记录一次错误
    }
    lin_1_iussues[num].proc(&lin1.tx_msg);//运行发送
    LIN_Master_TX(&lin1);
    lin1.issue_cb=lin_1_iussues[num].call_back;//装入接收函数
    if(++num>=(sizeof(lin_1_iussues)/sizeof(LIN_ISSUE)))
    {
        num=0;
    }
}

/*LIN发送函数*/
void LIN_Task(void)
{
    Master_LIN_1_Proc();
}
