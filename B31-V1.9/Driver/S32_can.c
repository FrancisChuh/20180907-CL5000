#include "S32_can.h"

//�ڲ�ʹ�ú�������
uint8_t SetCANBand(uint8_t CANChannel,uint32_t baudrateKHz);

/*************************************************************************
*  �������ƣ�CANInit
*  ����˵����
*  ����˵����CANChannel��ģ���
//		   baudrateKHz: ������
//         selfLoop: ģʽѡ��(1=�ػ�ģʽ��0=����ģʽ)
//         idMask: ID����(1=ID���ˣ�0=ID������)
*  �������أ�1���ɹ���0��ʧ��
*  �޸�ʱ�䣺2012-1-20
*  ��    ע���ο����ݴ�ѧ������
*************************************************************************/
uint8_t CANInit(uint8_t CANChannel,uint32_t baudrateKHz,uint32_t rxID,uint8_t selfLoop,uint8_t idMask)
{
	uint8_t i;
  CAN_MemMapPtr CANBaseAdd;
  
  //ͨ��ģ���ѡ��ģ�����ַ
	if(CANChannel == 0)
	{
		CANBaseAdd = CAN0;
		PCC->PCCn[PCC_FlexCAN0_INDEX] =	PCC_PCCn_CGC_MASK;//BUSCLK
	}
	else if(CANChannel == 1)
	{
		CANBaseAdd = CAN1;
		PCC->PCCn[PCC_FlexCAN1_INDEX] = PCC_PCCn_CGC_MASK; //BUSCLK
	}
	else if(CANChannel == 2)
	{
		CANBaseAdd = CAN2;
		PCC->PCCn[PCC_FlexCAN2_INDEX] = PCC_PCCn_CGC_MASK ; //BUSCLK
	}
	else 
	{
		return 0;
	}
  
	//����PIN��
	if(CANChannel == 0)
	{
		if(CAN0_TX == PTC3 )
		{
     port_init(CAN0_TX, ALT3 + PORT_PCR_PE_MASK+PORT_PCR_PS_MASK);
    }
    else
		{
      port_init(CAN0_TX, ALT5 + PORT_PCR_PE_MASK+PORT_PCR_PS_MASK);
    }
		if(CAN0_RX == PTC2 )
		{
     port_init(CAN0_RX, ALT3 + PORT_PCR_PE_MASK+PORT_PCR_PS_MASK);
    }
    else
		{
      port_init(CAN0_RX, ALT5 + PORT_PCR_PE_MASK+PORT_PCR_PS_MASK);
    }
	}
	else if(CANChannel == 1)
	{
		port_init(CAN1_TX, ALT3 + PORT_PCR_PE_MASK+PORT_PCR_PS_MASK);
		port_init(CAN1_RX, ALT3 + PORT_PCR_PE_MASK+PORT_PCR_PS_MASK);
	}
	else if(CANChannel == 2)
	{
		if(CAN2_TX == PTB13 )
		{
			port_init(CAN2_TX, ALT4 + PORT_PCR_PE_MASK+PORT_PCR_PS_MASK );
    }
    else
		{
			port_init(CAN2_TX, ALT3 + PORT_PCR_PE_MASK+PORT_PCR_PS_MASK );
    }
		if(CAN2_RX == PTB12 )
		{
			port_init(CAN2_RX, ALT4 + PORT_PCR_PE_MASK+PORT_PCR_PS_MASK );
    }
    else
		{
			port_init(CAN2_RX, ALT3 + PORT_PCR_PE_MASK+PORT_PCR_PS_MASK );
    }
	}
	CANBaseAdd->MCR |= CAN_MCR_MDIS_MASK;//��ֹCAN
	//ѡ��ʱ��Դ
	CANBaseAdd->CTRL1 &= ~CAN_CTRL1_CLKSRC_MASK;//����ʱ��8MHz
	CANBaseAdd->MCR &= ~CAN_MCR_MDIS_MASK;//ʹ��CANģ��
//	//���붳��ģʽ
//	CANBaseAdd->MCR |= CAN_MCR_FDEN_MASK ;//ʹ��FDģʽ
//	CANBaseAdd->MCR |= CAN_MCR_HALT_MASK ;
	//�ȴ����붳��ģʽ 
	while(!(CAN_MCR_FRZACK_MASK & CANBaseAdd->MCR)){;}

	//��ʼ������Ĵ���
  if(1==idMask)//����ID
	{
		CANBaseAdd->RXMGMASK = 0x1FFFFFFF;
		CANBaseAdd->RX14MASK = 0x1FFFFFFF;
		CANBaseAdd->RX15MASK = 0x1FFFFFFF;
	}
	else//������ID
	{
		CANBaseAdd->RXMGMASK = 0x0;
		CANBaseAdd->RX14MASK = 0x0;
		CANBaseAdd->RX15MASK = 0x0;
	}
	//���ý��ջ���
	CANBaseAdd->MCR &= ~CAN_MCR_MAXMB_MASK ;
	CANBaseAdd->MCR |= CAN_MCR_MAXMB(NUMBER_OF_MB-1) ;   //����Ϊ32��MB
	//���������
	for(i = 0 ; i < 128 ;i ++ )
	{
		CANBaseAdd->RAMn[i] = 0x0 ;
	}
	CANBaseAdd->MCR |=CAN_MCR_PNET_EN_MASK;//ʹ��CAN����
	CANBaseAdd->CTRL1_PN |=CAN_CTRL1_PN_WUMF_MSK_MASK;//ʹ��CAN����
	//�����������IDE�Ƚϣ�RTR���Ƚ�
	CANBaseAdd->CTRL2 &= ~CAN_CTRL2_EACEN_MASK;
	//Զ������֡����
	CANBaseAdd->CTRL2 &= ~CAN_CTRL2_RRS_MASK;
	//�������ȴӽ���FIFO����ƥ��Ȼ������������ƥ��
	CANBaseAdd->CTRL2 &= ~CAN_CTRL2_MRP_MASK;

	//ʹ��һ��32λ������
	CANBaseAdd->MCR |= (CANBaseAdd->MCR & ~CAN_MCR_IDAM_MASK) | CAN_MCR_IDAM(0);
	//���ò�����
	SetCANBand(CANChannel,baudrateKHz);
	//ģʽѡ�񣺻ػ�ģʽ������ģʽ
	if(1==selfLoop)
	{
		CANBaseAdd->CTRL1 |= CAN_CTRL1_LPB_MASK;//ʹ�ûػ�ģʽ
	}
	//����������빦��ʹ�ܣ�Ϊÿ�����г�ʼ������������Ĵ���
	if(CANBaseAdd->MCR & CAN_MCR_IRMQ_MASK)
	{
		for(i = 0; i < NUMBER_OF_MB ; i++)
		{        
			CANBaseAdd->RXIMR[i] = 0x1FFFFFFFL;
		}
	}
	CANBaseAdd->RAMn[FLEXCAN_RX_MB*MSG_BUF_SIZE+0] = 0x04000000;//����Ϊ����
	CANBaseAdd->RAMn[FLEXCAN_RX_MB*MSG_BUF_SIZE+1] = FLEXCAN_MB_ID_IDSTD(rxID);//����ID����
	//ֻ���ڶ���ģʽ�²������ã��������Ƴ�����ģʽ
	CANBaseAdd->MCR &= ~(CAN_MCR_HALT_MASK);
	//�ȴ�ֱ���˳�����ģʽ
	while( CANBaseAdd->MCR & CAN_MCR_FRZACK_MASK){;}    
	//�ȵ����ڶ���ģʽ������ģʽ����ֹͣģʽ
	while((CANBaseAdd->MCR & CAN_MCR_NOTRDY_MASK)){;}
		
	CANBaseAdd->IMASK1 = (1<<(FLEXCAN_RX_MB));//ʹ�ܽ����ж�
	return 1;
}


/*************************************************************************
*  �������ƣ�CANSendData
*  ����˵������������
*  ����˵����CANChannel��ģ���         
//          iMB����������
//	    id: ID��
//          length�����ݳ���
//	    Data[8]:�������ݻ�����
*  �������أ�0���ɹ���1��ʧ��
*  �޸�ʱ�䣺2015-5-15   �Ѳ���
*  ��    ע��
*************************************************************************/
uint8_t CANSendData(uint8_t CANChannel, uint32_t id,uint8_t length,uint8_t Data[])
{
	CAN_MemMapPtr CANBaseAdd;
	
	if(CANChannel == 0)
	{
		CANBaseAdd = CAN0;  
	}
	else if(CANChannel == 1)
	{
		CANBaseAdd = CAN1;
	}
	else if(CANChannel == 2)
	{
		CANBaseAdd = CAN2;
	}
	else
	{
		return 0;
	}
	
	if(length >8)	//�����������ݳ������ô���
	{
		return 0; //������Χ
	}
	CANBaseAdd->IFLAG1 |= 1<<FLEXCAN_TX_MB; //clear MB0 flag
	CANBaseAdd->RAMn[FLEXCAN_TX_MB*MSG_BUF_SIZE+2] = (Data[0]<<24) | (Data[1]<<16) | (Data[2]<< 8) |  Data[3];
	CANBaseAdd->RAMn[FLEXCAN_TX_MB*MSG_BUF_SIZE+3] = (Data[4]<<24) | (Data[5]<<16) | (Data[6]<< 8) |  Data[7];
	CANBaseAdd->RAMn[FLEXCAN_TX_MB*MSG_BUF_SIZE+1] =	FLEXCAN_MB_ID_IDSTD(id);
	CANBaseAdd->RAMn[FLEXCAN_TX_MB*MSG_BUF_SIZE+0] = 0x0C400000 | CAN_WMBn_CS_DLC(length);
	return 1;
}


/*************************************************************************
*  �������ƣ���������
*  ����˵����ʹ�ܽ��ջ�����
*  ����˵����CANChannel��CANģ���
//          iMB����������
//	    id: ID��
//	    lenght�����ݳ���
//	    Data[8]: �ͽ������ݻ�����
*  �������أ�0���ɹ���1��ʧ��
*  �޸�ʱ�䣺2015-5-15   �Ѳ���
*  ��    ע�����ݴ�ѧ������
*************************************************************************/
uint8_t CANRecData(uint8_t CANChannel,CANMsg *RxData)
{
	uint32_t temp;
	CAN_MemMapPtr CANBaseAdd;
	
	if(CANChannel == 0)
	{
		CANBaseAdd = CAN0;  
	}
	else if(CANChannel == 1)
	{
		CANBaseAdd = CAN1;
	}
	else if(CANChannel == 2)
	{
		CANBaseAdd = CAN2;
	}
	RxData->ID=(CANBaseAdd->RAMn[FLEXCAN_RX_MB*MSG_BUF_SIZE+1] & FLEXCAN_MB_ID_STD_MASK)>>FLEXCAN_MB_ID_STD_BIT_NO;
	RxData->len=(CANBaseAdd->RAMn[FLEXCAN_RX_MB*MSG_BUF_SIZE+0] & CAN_WMBn_CS_DLC_MASK)>>CAN_WMBn_CS_DLC_SHIFT;
	temp=CANBaseAdd->RAMn[FLEXCAN_RX_MB*MSG_BUF_SIZE+2];
	RxData->data[0]=temp>>24;
	RxData->data[1]=temp>>16;
	RxData->data[2]=temp>>8;
	RxData->data[3]=temp>>0;
	temp=CANBaseAdd->RAMn[FLEXCAN_RX_MB*MSG_BUF_SIZE+3];
	RxData->data[4]=temp>>24;
	RxData->data[5]=temp>>16;
	RxData->data[6]=temp>>8;
	RxData->data[7]=temp>>0;
	temp=CANBaseAdd->TIMER;
	CANBaseAdd->IFLAG1 |= 1<<FLEXCAN_RX_MB;//����жϱ�־
	return 1;
}

uint8_t CANRecDataPN(uint8_t CANChannel,CANMsg *RxData)
{
	uint32_t temp;
	CAN_MemMapPtr CANBaseAdd=CAN0;
	
	if(CANChannel != 0)
	{
		return 0;  
	}
	RxData->ID=(CANBaseAdd->WMB[0].WMBn_ID & FLEXCAN_MB_ID_STD_MASK)>>FLEXCAN_MB_ID_STD_BIT_NO;
	RxData->len=(CANBaseAdd->WMB[0].WMBn_CS & CAN_WMBn_CS_DLC_MASK)>>CAN_WMBn_CS_DLC_SHIFT;
	temp=CANBaseAdd->WMB[0].WMBn_D03;
	RxData->data[0]=temp>>24;
	RxData->data[1]=temp>>16;
	RxData->data[2]=temp>>8;
	RxData->data[3]=temp>>0;
	temp=CANBaseAdd->WMB[0].WMBn_D47;
	RxData->data[4]=temp>>24;
	RxData->data[5]=temp>>16;
	RxData->data[6]=temp>>8;
	RxData->data[7]=temp>>0;
	CANBaseAdd->WU_MTC |= CAN_WU_MTC_WUMF_MASK;//����жϱ�־
	return 1;
}

/*************************************************************************
*  �������ƣ�SetCANBand
*  ����˵��������CAN�Ĳ�����
*  ����˵����CANChannel:CANģ���
//          baudrateKHz:������
*  �������أ�0:���óɹ� 1�����óɹ�
*  �޸�ʱ�䣺2015-5-15   �Ѳ���
*  ��    ע�����ݴ�ѧ������
*************************************************************************/

uint8_t SetCANBand(uint8_t CANChannel,uint32_t baudrateKHz)
{    
	CAN_MemMapPtr CANBaseAdd;
    
	//ͨ��ģ���ѡ��ģ�����ַ
	if(CANChannel == 0)
	{
		CANBaseAdd = CAN0;
	}
	else if(CANChannel == 1)
	{
		CANBaseAdd = CAN1;
	}
	else if(CANChannel == 2)
	{
		CANBaseAdd = CAN2;
	} 

	switch(baudrateKHz)
	{
		case (125):	// 125K
			if(CANBaseAdd->CTRL1 & CAN_CTRL1_CLKSRC_MASK)
			{
				CANBaseAdd->CTRL1 = CAN_CTRL1_PROPSEG(6) // PROPSEG+1 = 7, LOM = 0x0, LBUF = 0x0, TSYNC = 0x0
													| CAN_CTRL1_CLKSRC_MASK	//80Mhz
													| CAN_CTRL1_RJW(2)			//RJW = 3
													| CAN_CTRL1_PSEG1(3)		//PSEG1+1 = 4
													| CAN_CTRL1_PSEG2(3)		//PSEG2+1 = 4
													| CAN_CTRL1_PRESDIV(39); //PRESDIV = 40 ,80/40= 2M sclock,16
			}
			else
			{
				CANBaseAdd->CTRL1 = CAN_CTRL1_PROPSEG(6) 
													| CAN_CTRL1_RJW(2)			//RJW = 3
													| CAN_CTRL1_PSEG1(3)		//PSEG1+1 = 4
													| CAN_CTRL1_PSEG2(3)		//PSEG2+1 = 4
													| CAN_CTRL1_PRESDIV(3); //PRESDIV = 4 ,80/3= 2M sclock,16
			}
			break;
			
		case (250):
			if(CANBaseAdd->CTRL1 & CAN_CTRL1_CLKSRC_MASK)
			{
				CANBaseAdd->CTRL1 = CAN_CTRL1_PROPSEG(6) // PROPSEG+1 = 7, LOM = 0x0, LBUF = 0x0, TSYNC = 0x0
													| CAN_CTRL1_CLKSRC_MASK	//80Mhz
													| CAN_CTRL1_RJW(2)			//RJW = 3
													| CAN_CTRL1_PSEG1(3)		//PSEG1+1 = 4
													| CAN_CTRL1_PSEG2(3)		//PSEG2+1 = 4
													| CAN_CTRL1_PRESDIV(19); //PRESDIV = 20 ,80/20= 4M sclock,16
			}
			else
			{
				CANBaseAdd->CTRL1 = CAN_CTRL1_PROPSEG(6) 
													| CAN_CTRL1_RJW(2)			//RJW = 3
													| CAN_CTRL1_PSEG1(3)		//PSEG1+1 = 4
													| CAN_CTRL1_PSEG2(3)		//PSEG2+1 = 4
													| CAN_CTRL1_PRESDIV(1); //PRESDIV = 2 ,8/2= 4M sclock,16
			}
			break;
			
		case (500):
			if(CANBaseAdd->CTRL1 & CAN_CTRL1_CLKSRC_MASK)
			{
				CANBaseAdd->CTRL1 = CAN_CTRL1_PROPSEG(6) // PROPSEG+1 = 7, LOM = 0x0, LBUF = 0x0, TSYNC = 0x0
													| CAN_CTRL1_CLKSRC_MASK	//80Mhz
													| CAN_CTRL1_RJW(2)			//RJW = 3
													| CAN_CTRL1_PSEG1(3)		//PSEG1+1 = 4
													| CAN_CTRL1_PSEG2(3)		//PSEG2+1 = 4
													| CAN_CTRL1_PRESDIV(9); //PRESDIV = 10 ,80/10= 8M sclock,16
			}
			else
			{
				CANBaseAdd->CTRL1 = CAN_CTRL1_PROPSEG(6) 
													| CAN_CTRL1_RJW(2)			//RJW = 3
													| CAN_CTRL1_PSEG1(3)		//PSEG1+1 = 4
													| CAN_CTRL1_PSEG2(3)		//PSEG2+1 = 4
													| CAN_CTRL1_PRESDIV(0); //PRESDIV = 1 ,8/1= 8M sclock,16
			}
			break;
		case (1000):
			if(CANBaseAdd->CTRL1 & CAN_CTRL1_CLKSRC_MASK)
			{
				CANBaseAdd->CTRL1 = CAN_CTRL1_PROPSEG(6) // PROPSEG+1 = 7, LOM = 0x0, LBUF = 0x0, TSYNC = 0x0
													| CAN_CTRL1_CLKSRC_MASK	//80Mhz
													| CAN_CTRL1_RJW(2)			//RJW = 3
													| CAN_CTRL1_PSEG1(3)		//PSEG1+1 = 4
													| CAN_CTRL1_PSEG2(3)		//PSEG2+1 = 4
													| CAN_CTRL1_PRESDIV(4); //PRESDIV = 5 ,80/5= 16M sclock,16
			}
			else
			{
				CANBaseAdd->CTRL1 = CAN_CTRL1_PROPSEG(1) // PROPSEG+1 = 2
													| CAN_CTRL1_RJW(0)			//RJW = 1
													| CAN_CTRL1_PSEG1(1)		//PSEG1+1 = 2
													| CAN_CTRL1_PSEG2(2)		//PSEG2+1 = 3
													| CAN_CTRL1_PRESDIV(0); //PRESDIV = 1 ,8/1= 8M sclock,8
			}
			break;
		default: 
      break;
  }
  return 1;
}
