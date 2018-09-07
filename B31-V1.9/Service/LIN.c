/**************************************************************************/
/*    ���쳬���߿Ƽ��ɷ����޹�˾          ��Ȩ����                        */
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
/*   �����ļ�����LIN.c                                                    */
/*   Filename  ��LIN.c                                                    */
/*   ����      ��������                                                   */
/*   Author    ��Jack                                                     */
/*   ����      ��10/23/2017                                               */
/*   Date      ��10/23/2017                                               */
/*   ��ǰ�汾  ��1.0                                                      */
/*   Version     ��1.0                                                    */
/*   ʵ��Ŀ��  ��LIN��ʼ�������պͷ���                                    */
/*   Purpose   ��LIN_Init                                                 */
/**************************************************************************/
/*   �޸ļ�¼  ����                                                       */
/*   ��� , MM/DD/YYYY,�汾���޸��ߣ��޸�����(������޸ļ�¼��������)     */
/*   Modi Report��                                                        */
/*   Index��Date��Version��Author, content                                */
/**************************************************************************/
#include "LIN.h"



//static u8 LIN_TX_Buf[11];     //0x55+id+8+1
//static u8 *pLIN_TX_Buf;
//static u8 LIN_TX_Len=0;
u8 LIN_RX_Flag=0;


//extern LINMsg LIN_RX_Msg;
//extern LINMsg LIN_TX_Msg;


#define LinTransceiverInit TJA1021T_INIT  //�����շ�����ʼ����ȥ��ʼ������
#define LinTR TJA1021T  //�����շ�������
extern const TJA1021T tja1021t_0;   //�շ���ʵ����


extern const LinUart lin_uart_1;    //lin_uart


LIN lin1={
    .LinTransceiver=&tja1021t_0, //�շ�����
    .lin_uart=&lin_uart_1,        //uart_lin
    .lin_type=MASTER,               //lin����
};


void Lin1_Init(void)    
{
    ;
}

void Lin_Init(LIN *lin)  //lin��ʼ��
{
    /*�շ�����ʼ��*/
    LinTR *lin_tr;
    LinTransceiverInit * init;
    lin_tr=(LinTR *)lin->LinTransceiver;
    init=(LinTransceiverInit *)lin_tr->init;
    init(lin_tr);
}

void Lin_Deinit(LIN *lin)   //linȥ��ʼ��
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
    LPUART1->STAT |=LPUART_STAT_BRK13_MASK;     //13λ�ϵ�
    LPUART1->STAT |=LPUART_STAT_LBKDE_MASK;     //��LIN�ϵ���
    LPUART1->BAUD |=LPUART_BAUD_LBKDIE_MASK;    //���ϵ����ж�
    NVIC_Init(LPUART1_RxTx_IRQn,3);                            //�ж����ȼ�����
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

/*LIN�������ݴ���*/
void LIN_Master_TX(LIN *lin)
{
    u8 i;
    u16 sum;
    LINMsg *msg=&lin->tx_msg;
    
    LIN_MASTER_TX_BreakF();//������������ַ��������ϴ��ڹ���
    
    if(msg->LEN==0)
    {
        lin->tx_tmp[1]=0x55;             //ͬ����
        //ID = ID2PID(ID);//����pid
        lin->tx_tmp[0]=msg->PID;             //PID
        lin->tx_cnt=2;
    }
    else       //�����ݷ���
    {
        lin->tx_tmp[msg->LEN+2]=0x55;             //ͬ����
        //ID = ID2PID(ID);//����pid
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
    /*�����ͼĴ���Ϊ���ж�:shift�Ĵ���Ϊ��ʱ��װ��Tx_Buffer*/
    LPUART1->CTRL |= LPUART_CTRL_TIE_MASK;
}


void Lin_RX_Reset(LIN *lin);
void Lin_Got_BK(LIN *lin);

void Lin_RX_Byte(LIN *lin ,uint8_t byte)//�����ֽ�
{
    static uint16_t sum=0;
    if(lin->rx_cnt==0)
    {
        if(byte==0x55)
        {
            lin->rx_cnt++;
            ;//������һ�׶�
        }
        else
        {
            Lin_RX_Reset(lin);
        }
    }
    else if(lin->rx_cnt==1) //����pid
    {
        lin->rx_msg.PID=byte;
        lin->rx_cnt++;
        sum=lin->rx_msg.PID;
        if(lin->lin_type==SLAVE) //�����slave�����Ƿ�Ҫ��������
        {
            ;//�ж�pid�����Ƿ��ͣ����ǻظ�
        }
    }
    else if(lin->rx_cnt>1 && lin->rx_cnt<10) //��������
    {
        lin->rx_msg.data[lin->rx_cnt-2]=byte;
        sum+=byte;
        lin->rx_cnt++;
        if(sum>0xff)
        {
            sum-=0xff;
        }
    }
    else if(lin->rx_cnt==10) //����У���
    {
        lin->rx_msg.check_sum=byte;
        sum=(~sum)&0xff;
        if(lin->rx_msg.check_sum==sum)
        {
            if(lin->issue_cb!=0)
            {
                lin->issue_cb(&lin->rx_msg);//���ô������ص�����
                lin->issue_cb=0;            //����ص�����
            }
            Lin_RX_Reset(lin);
        }
        else    //У��ʹ���
        {
            Lin_RX_Reset(lin);;
        }
    }
    else    //������̫��,�������ᵽ������
    {
        Lin_RX_Reset(lin);
    }
}

void Lin_RX_BK(LIN *lin) //�յ��ϵ��ַ�
{
    lin->rx_state=LIN_BREAK;
    lin->rx_cnt=0;
}

void Lin_RX_Reset(LIN *lin)//��λ
{
    lin->rx_state=LIN_IDLE;
    lin->rx_cnt=0;
    lin->lin_uart->uartn->STAT |= LPUART_STAT_LBKDE_MASK;
}

void LIN_LPUART_RxTx_IRQHandler(LIN *lin)
{
    LPUART_Type *lp_uart=lin->lin_uart->uartn;
    if(lp_uart->STAT & LPUART_STAT_TDRE_MASK)//�����жϱ�־
    {
        if(lin->tx_cnt)
        {
            lin->tx_cnt--;
            lp_uart->DATA=lin->tx_tmp[lin->tx_cnt];
        }
        else
        {
            lp_uart->CTRL &= ~LPUART_CTRL_TIE_MASK;//���͹��ж�
        }
    }
    
    if(lp_uart->STAT & LPUART_STAT_OR_MASK) //�������:�ֽ�δ��ʱ����
    {
        (void)lp_uart->DATA;
        Lin_RX_Reset(lin);//lin�������״̬
    }
    else
    {
        if(lp_uart->STAT & LPUART_STAT_LBKDIF_MASK) //�յ�lin�Ķϵ��ַ�
        {
            lp_uart->STAT |= LPUART_STAT_LBKDIF_MASK;//����ϵ��־
            lp_uart->STAT &= ~LPUART_STAT_LBKDE_MASK;//�رնϵ���
            
            Lin_RX_BK(lin);//����lin break
            
        }
        if(lp_uart->STAT & LPUART_STAT_RDRF_MASK)   //�����ж�
        {
            if(lp_uart->STAT & LPUART_STAT_FE_MASK) //ֹͣλ����
            {
                if(lp_uart->DATA==0x00)//����ǰ���û����Ӧ
                {
                    Lin_RX_BK(lin);//����lin break������һ֡��ë��������£��������һ��֧
                }
                else
                {
                    Lin_RX_Reset(lin);//����idle
                }
            }
            else    //�յ�һ��byte����
            {
                Lin_RX_Byte(lin,lp_uart->DATA);
            }
        }
    }
}

void LPUART1_RxTx_IRQHandler()//�жϺ���
{
    LIN_LPUART_RxTx_IRQHandler(&lin1);
}

extern const LIN_ISSUE lin_1_iussues[2];

uint16_t lin1_err_cnt=0;

/*LIN1���ͺ���*/
void Master_LIN_1_Proc(void)
{
    static unsigned char num=0;
    if(lin1.issue_cb!=NULL)
    {
        lin1_err_cnt++;//��¼һ�δ���
    }
    lin_1_iussues[num].proc(&lin1.tx_msg);//���з���
    LIN_Master_TX(&lin1);
    lin1.issue_cb=lin_1_iussues[num].call_back;//װ����պ���
    if(++num>=(sizeof(lin_1_iussues)/sizeof(LIN_ISSUE)))
    {
        num=0;
    }
}

/*LIN���ͺ���*/
void LIN_Task(void)
{
    Master_LIN_1_Proc();
}
