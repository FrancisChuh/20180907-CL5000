#include "S32_PIT.h" 

/*************************************************************************
*  �������ƣ�pit_init
*  ����˵����PITn��ʱ�ж�
*  ����˵����PITn        ģ��ţ�PIT0~PIT3��
             cnt         ��ʱʱ��(��λΪbusʱ������)
*  �������أ���
*  �޸�ʱ�䣺2012-1-24
*  ��    ע��
*************************************************************************/
void Pit_Init(PITn pitn, uint32_t cnt_us)	//������� = ����Ƶ�� * ʱ��
{
	cnt_us=CPU_XTAL_CLK_HZ/1000000*cnt_us;
	
	PCC->PCCn[PCC_LPIT_INDEX] &= ~PCC_PCCn_CGC_MASK ;		//ʱ�ӽ���	
  PCC->PCCn[PCC_LPIT_INDEX]  = PCC_PCCn_PCS(1) ;      //ѡ��SOSC��Ϊʱ��Դ 8M
	PCC->PCCn[PCC_LPIT_INDEX] |= PCC_PCCn_CGC_MASK ;    //ʹ��PITʱ��

//	LPIT0->MCR = LPIT_MCR_SW_RST_MASK ;//��λ���мĴ���
  LPIT0->MCR |= LPIT_MCR_M_CEN_MASK; 			//ʹ��PIT��ʱ��ʱ��
//							| LPIT_MCR_DOZE_EN_MASK;			//dozeģʽ��������
//							| LPIT_MCR_DBG_EN_MASK;     //����ģʽ�¼�������
////    while(LPIT0_MCR&LPIT_MCR_SW_RST_MASK){;}
  LPIT0->CLRTEN |= (1 << pitn);			//����

	LPIT0->TMR[pitn].TVAL  = cnt_us;   
	LPIT0->TMR[pitn].TCTRL |= LPIT_TMR_TCTRL_T_EN_MASK  //ʹ��
													|LPIT_TMR_TCTRL_MODE(0);		//32bit-Periodic Counter
//													|LPIT_TMR_TCTRL_TROT(1)		//reload
//													|LPIT_TMR_TCTRL_TRG_SEL(pitn)//����Դ
//													|LPIT_TMR_TCTRL_TRG_SRC(1);	//�ڲ�����
	LPIT0->MIER|= 1<< pitn ;      //�ж�ʹ��
	LPIT0->SETTEN |= (1 << pitn);	//ʹ��PIT
}
