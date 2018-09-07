#include "S32_can.h"

//内部使用函数声明
uint8_t SetCANBand(uint8_t CANChannel,uint32_t baudrateKHz);

/*************************************************************************
*  函数名称：CANInit
*  功能说明：
*  参数说明：CANChannel：模块号
//		   baudrateKHz: 波特率
//         selfLoop: 模式选择(1=回环模式；0=正常模式)
//         idMask: ID过滤(1=ID过滤；0=ID不过滤)
*  函数返回：1：成功；0：失败
*  修改时间：2012-1-20
*  备    注：参考苏州大学的例程
*************************************************************************/
uint8_t CANInit(uint8_t CANChannel,uint32_t baudrateKHz,uint32_t rxID,uint8_t selfLoop,uint8_t idMask)
{
	uint8_t i;
  CAN_MemMapPtr CANBaseAdd;
  
  //通过模块号选择模块基地址
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
  
	//配置PIN脚
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
	CANBaseAdd->MCR |= CAN_MCR_MDIS_MASK;//禁止CAN
	//选择时钟源
	CANBaseAdd->CTRL1 &= ~CAN_CTRL1_CLKSRC_MASK;//外设时钟8MHz
	CANBaseAdd->MCR &= ~CAN_MCR_MDIS_MASK;//使能CAN模块
//	//进入冻结模式
//	CANBaseAdd->MCR |= CAN_MCR_FDEN_MASK ;//使能FD模式
//	CANBaseAdd->MCR |= CAN_MCR_HALT_MASK ;
	//等待进入冻结模式 
	while(!(CAN_MCR_FRZACK_MASK & CANBaseAdd->MCR)){;}

	//初始化掩码寄存器
  if(1==idMask)//屏蔽ID
	{
		CANBaseAdd->RXMGMASK = 0x1FFFFFFF;
		CANBaseAdd->RX14MASK = 0x1FFFFFFF;
		CANBaseAdd->RX15MASK = 0x1FFFFFFF;
	}
	else//不屏蔽ID
	{
		CANBaseAdd->RXMGMASK = 0x0;
		CANBaseAdd->RX14MASK = 0x0;
		CANBaseAdd->RX15MASK = 0x0;
	}
	//设置接收缓存
	CANBaseAdd->MCR &= ~CAN_MCR_MAXMB_MASK ;
	CANBaseAdd->MCR |= CAN_MCR_MAXMB(NUMBER_OF_MB-1) ;   //设置为32个MB
	//清除缓冲区
	for(i = 0 ; i < 128 ;i ++ )
	{
		CANBaseAdd->RAMn[i] = 0x0 ;
	}
	CANBaseAdd->MCR |=CAN_MCR_PNET_EN_MASK;//使能CAN唤醒
	CANBaseAdd->CTRL1_PN |=CAN_CTRL1_PN_WUMF_MSK_MASK;//使能CAN唤醒
	//接收邮箱过滤IDE比较，RTR不比较
	CANBaseAdd->CTRL2 &= ~CAN_CTRL2_EACEN_MASK;
	//远程请求帧产生
	CANBaseAdd->CTRL2 &= ~CAN_CTRL2_RRS_MASK;
	//邮箱首先从接收FIFO队列匹配然后再在邮箱中匹配
	CANBaseAdd->CTRL2 &= ~CAN_CTRL2_MRP_MASK;

	//使用一个32位过滤器
	CANBaseAdd->MCR |= (CANBaseAdd->MCR & ~CAN_MCR_IDAM_MASK) | CAN_MCR_IDAM(0);
	//设置波特率
	SetCANBand(CANChannel,baudrateKHz);
	//模式选择：回环模式或正常模式
	if(1==selfLoop)
	{
		CANBaseAdd->CTRL1 |= CAN_CTRL1_LPB_MASK;//使用回环模式
	}
	//如果单独掩码功能使能，为每个队列初始化单独的掩码寄存器
	if(CANBaseAdd->MCR & CAN_MCR_IRMQ_MASK)
	{
		for(i = 0; i < NUMBER_OF_MB ; i++)
		{        
			CANBaseAdd->RXIMR[i] = 0x1FFFFFFFL;
		}
	}
	CANBaseAdd->RAMn[FLEXCAN_RX_MB*MSG_BUF_SIZE+0] = 0x04000000;//设置为接收
	CANBaseAdd->RAMn[FLEXCAN_RX_MB*MSG_BUF_SIZE+1] = FLEXCAN_MB_ID_IDSTD(rxID);//接收ID设置
	//只有在冻结模式下才能配置，配置完推出冻结模式
	CANBaseAdd->MCR &= ~(CAN_MCR_HALT_MASK);
	//等待直到退出冻结模式
	while( CANBaseAdd->MCR & CAN_MCR_FRZACK_MASK){;}    
	//等到不在冻结模式，休眠模式或者停止模式
	while((CANBaseAdd->MCR & CAN_MCR_NOTRDY_MASK)){;}
		
	CANBaseAdd->IMASK1 = (1<<(FLEXCAN_RX_MB));//使能接收中断
	return 1;
}


/*************************************************************************
*  函数名称：CANSendData
*  功能说明：发送数据
*  参数说明：CANChannel：模块号         
//          iMB：缓冲区号
//	    id: ID号
//          length：数据长度
//	    Data[8]:发送数据缓冲区
*  函数返回：0：成功，1：失败
*  修改时间：2015-5-15   已测试
*  备    注：
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
	
	if(length >8)	//缓冲区和数据长度设置错误
	{
		return 0; //超出范围
	}
	CANBaseAdd->IFLAG1 |= 1<<FLEXCAN_TX_MB; //clear MB0 flag
	CANBaseAdd->RAMn[FLEXCAN_TX_MB*MSG_BUF_SIZE+2] = (Data[0]<<24) | (Data[1]<<16) | (Data[2]<< 8) |  Data[3];
	CANBaseAdd->RAMn[FLEXCAN_TX_MB*MSG_BUF_SIZE+3] = (Data[4]<<24) | (Data[5]<<16) | (Data[6]<< 8) |  Data[7];
	CANBaseAdd->RAMn[FLEXCAN_TX_MB*MSG_BUF_SIZE+1] =	FLEXCAN_MB_ID_IDSTD(id);
	CANBaseAdd->RAMn[FLEXCAN_TX_MB*MSG_BUF_SIZE+0] = 0x0C400000 | CAN_WMBn_CS_DLC(length);
	return 1;
}


/*************************************************************************
*  函数名称：接收数据
*  功能说明：使能接收缓冲区
*  参数说明：CANChannel：CAN模块号
//          iMB：缓冲区号
//	    id: ID号
//	    lenght：数据长度
//	    Data[8]: 和接收数据缓冲区
*  函数返回：0：成功，1：失败
*  修改时间：2015-5-15   已测试
*  备    注：苏州大学的例程
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
	CANBaseAdd->IFLAG1 |= 1<<FLEXCAN_RX_MB;//清除中断标志
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
	CANBaseAdd->WU_MTC |= CAN_WU_MTC_WUMF_MASK;//清除中断标志
	return 1;
}

/*************************************************************************
*  函数名称：SetCANBand
*  功能说明：设置CAN的波特率
*  参数说明：CANChannel:CAN模块号
//          baudrateKHz:波特率
*  函数返回：0:配置成功 1：配置成功
*  修改时间：2015-5-15   已测试
*  备    注：苏州大学的例程
*************************************************************************/

uint8_t SetCANBand(uint8_t CANChannel,uint32_t baudrateKHz)
{    
	CAN_MemMapPtr CANBaseAdd;
    
	//通过模块号选择模块基地址
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
