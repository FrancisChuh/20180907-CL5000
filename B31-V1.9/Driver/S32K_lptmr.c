/***********************************************************
 * �ļ���       ��lptmr.c
 * ˵��         ���͹��Ķ�ʱģʽ
 * ����         ��landzo ������
 * �Ա���       ��http://landzo.taobao.com/
 * ��˾��վ     ��http://www.landzo.com/
 *��̳          ��http://www.landzo.cn
 * ��汾       ��V1.0
 *ʱ��          ��15.5.26
************************************************************/

#include "common.h"
#include "S32K_lptmr.h"



/*************************************************************************
*                             ������ӿƼ����޹�˾
*
*  �������ƣ�lptmr_counter_init
*  ����˵��������������
*  ����˵����LPT0_ALTn  PIN��ѡ��
*            count      �������
*            LPT_CFG    ������ʽ
*  �������أ�������
*  �޸�ʱ�䣺2015-5-15   �Ѳ���
*  ��    ע��
*************************************************************************/
void lptmr_counter_init(LPT0_ALTn altn, uint16_t count, LPT_CFG cfg)
{


    /* ����ģ��ʱ�� */
    PCC_LPTMR0 =   PCC_IP_CGC_MASK+PCC_IP_PCS(1) + PCC_IP_PR(0)  + PCC_IP_CGC(0);  //ʹ��LPTģ��ʱ��,��osc

    //��������ܽ�
    if(altn == LPT0_CH1)
      port_alt(LPT0_ALT1,ALT3) ;
    else if(altn == LPT0_CH2)
      port_alt(LPT0_ALT2,ALT3) ;
    else if((altn == LPT0_CH3))
    {
      if(LPT0_ALT3 == PTB0)
       port_alt(LPT0_ALT3,ALT4) ;
      else if(LPT0_ALT3 == PTE2)
        port_alt(LPT0_ALT3,ALT3) ;
    }


    // ��״̬�Ĵ���
    LPTMR0_CSR = 0x00 ;                                          //�ȹ���LPT��������������ʱ�ӷ�Ƶ,��ռ���ֵ��
    LPTMR0_PSR = 0x00 ;
    LPTMR0_CSR = 0x00 ;
    LPTMR0_CMR = 0X00 ; 
    
    // ״̬�Ĵ�������
    
    LPTMR0_PSR  =   (0
                     |LPTMR_PSR_PCS(0x00)
                     |LPTMR_PSR_PBYP_MASK
                     |LPTMR_PSR_PRESCALE(1)); 
    // �ܽ����á�ʹ���ж�
    LPTMR0_CMR = count ;
    LPTMR0_CSR  =  (0
                    | LPTMR_CSR_TPS(altn)       // ѡ������ܽ� ѡ��
                    | LPTMR_CSR_TMS_MASK        // ѡ��������� (ע���˱�ʾʱ�����ģʽ)
                    | ( cfg == LPT_Falling ?  LPTMR_CSR_TPP_MASK :   0  )  //���������������ʽѡ��0Ϊ�ߵ�ƽ��Ч�������ؼ�1
               //     | LPTMR_CSR_TEN_MASK        //ʹ��LPT(ע���˱�ʾ����)
                    | LPTMR_CSR_TIE_MASK        //�ж�ʹ��
                    //| LPTMR_CSR_TFC_MASK      //0:����ֵ���ڱȽ�ֵ�͸�λ��1�������λ��ע�ͱ�ʾ0��
                   );
     
    LPTMR0_CSR  |= LPTMR_CSR_TEN_MASK ; 
    NVIC_EnableIRQ(LPTMR0_IRQn) ;              //�����ŵ�IRQ�ж�
}


/*************************************************************************
*                             ������ӹ�����
*
*  �������ƣ�time_delay_ms
*  ����˵������ʱ������ʹ�ö����Ķ�ʱ����ʱ��׼ȷ
*  ����˵����ms   ��ʱʱ�䣬��λΪms
*  �������أ���
*  �޸�ʱ�䣺2012-1-20
*  ��    ע���ٷ������Դ�
*************************************************************************/
void time_delay_ms(uint32_t ms)
{
    /* Make sure the clock to the LPTMR is enabled */
    PCC_LPTMR0 =   PCC_IP_CGC_MASK+PCC_IP_PCS(1) + PCC_IP_PR(0)  + PCC_IP_CGC(0);  //ʹ��LPTģ��ʱ��,��osc

    /* Set the compare value to the number of ms to delay */
    LPTMR0_CMR = ms;

    /* Set up LPTMR to use 1kHz LPO with no prescaler as its clock source */
    LPTMR0_PSR = LPTMR_PSR_PCS(1) | LPTMR_PSR_PBYP_MASK;

    /* Start the timer */
    LPTMR0_CSR |= LPTMR_CSR_TEN_MASK;

    /* Wait for counter to reach compare value */
    while (!(LPTMR0_CSR & LPTMR_CSR_TCF_MASK));

    /* Clear Timer Compare Flag */
    LPTMR0_CSR &= ~LPTMR_CSR_TEN_MASK;

    return;
}


/*************************************************************************
*                             ������ӿƼ����޹�˾
*
*  �������ƣ�lptmr_pulse_get
*  ����˵��������������
*  ����˵����
*  �������أ�������
*  �޸�ʱ�䣺2015-5-15   �Ѳ���
*  ��    ע��
*************************************************************************/

uint16_t lptmr_pulse_get(void)
{
    uint16_t  LPTCOUNT = 0  ;
    LPTCOUNT = LPTMR0_CNR ;
    lptmr_counter_clean();
    return (uint16_t)LPTCOUNT;
}



