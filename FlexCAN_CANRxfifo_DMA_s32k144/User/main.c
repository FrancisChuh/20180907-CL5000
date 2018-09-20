/*******************************************************************************
* NXP Semiconductors
* (c) Copyright 2016 NXP Semiconductors
* ALL RIGHTS RESERVED.
********************************************************************************
Services performed by NXP in this matter are performed AS IS and without any
warranty. CUSTOMER retains the final decision relative to the total design
and functionality of the end product. NXP neither guarantees nor will be held
liable by CUSTOMER for the success of this project.
NXP DISCLAIMS ALL WARRANTIES, EXPRESSED, IMPLIED OR STATUTORY INCLUDING,
BUT NOT LIMITED TO, IMPLIED WARRANTY OF MERCHANTABILITY OR FITNESS FOR
A PARTICULAR PURPOSE ON ANY HARDWARE, SOFTWARE ORE ADVISE SUPPLIED
TO THE PROJECT BY NXP, AND OR NAY PRODUCT RESULTING FROM NXP SERVICES.
IN NO EVENT SHALL NXP BE LIABLE FOR INCIDENTAL OR CONSEQUENTIAL DAMAGES ARISING
OUT OF THIS AGREEMENT.
CUSTOMER agrees to hold NXP harmless against any and all claims demands
or actions by anyone on account of any damage, or injury, whether commercial,
contractual, or tortuous, rising directly or indirectly as a result
of the advise or assistance supplied CUSTOMER in connection with product,
services or goods supplied under this Agreement.
********************************************************************************
* File:             main.c
* Owner:            Petr Stancik
* Version:          1.0
* Date:             Sep-4-2017
* Classification:   General Business Information
* Brief:            FlexCAN simple TX/RX using RXFIFO
* 					DMA used to read RXFIFO
********************************************************************************
********************************************************************************
* Detailed Description:
*
* Configures the FlexCAN 0 to transmit and receive message into RXFIFO.
* LOOPBACK mode is enabled.
* Two IDs are set into RXFIFO ID table.
* DMA is configured to read the message from RXFIFO.
* Within DMA major interrupt the new message is send according to
* which Identifier Acceptance Filter was hit.
*
* ------------------------------------------------------------------------------
* Test HW:         S32K144 EVB-Q100
* MCU:             PS32K144HFVLL 0N77P
* Fsys:            160MHz
* Debugger:        Lauterbach
* Target:          internal_FLASH
*
********************************************************************************
Revision History:
1.0     Sep-4-2017     Petr Stancik    Initial Version
*******************************************************************************/


#include "S32K144.h" /* include peripheral declarations S32K144 */

/*******************************************************************************
* Constants and macros
*******************************************************************************/

/*******************************************************************************
* External objects
*******************************************************************************/

/*******************************************************************************
* Global variables
*******************************************************************************/
uint32_t rxBuffer[4] __attribute__ ((aligned (32)));
/*******************************************************************************
* Local functions
*******************************************************************************/
void SCG_Init(void);
void GPIO_Init(void);
void WDOG_Disable(void);
void DMA_init(void);
void DMAMUX_Init(void);
void IRQs_Init(void);
void DMA0_IRQHandler(void);
void FLEXCAN0_init(void);
void FLEXCAN0_transmit_msg(uint8_t ext, uint32_t ID, uint8_t length);

/*******************************************************************************
Function Name : SOSC_Init
Engineer      : Petr Stancik
Date          : Oct-2-2016
Parameters    : NONE
Modifies      : NONE
Returns       : NONE
Notes         : Initialize XOSC (8MHz), SPLL (160MHz) and RUN mode
Issues        : NONE
*******************************************************************************/
void SCG_Init(void)
{
  // *** System OSC ***
  SCG->SOSCDIV=0x00000101;  /* SOSCDIV1 & SOSCDIV2 =1: divide by 1 */
  SCG->SOSCCFG=0x00000034;  /* Range=3: high freq (SOSC betw 8MHz-32MHz)*/
                            /* HGO=0:   Config xtal osc for low power */
                            /* EREFS=1: Input is external XTAL */
  while(SCG->SOSCCSR & SCG_SOSCCSR_LK_MASK); /* Ensure SOSCCSR unlocked */
  SCG->SOSCCSR=0x00000001;  /* LK=0:          SOSCCSR can be written */
                            /* SOSCCMRE=0:    OSC CLK monitor IRQ if enabled */
                            /* SOSCCM=0:      OSC CLK monitor disabled */
                            /* SOSCERCLKEN=0: Sys OSC 3V ERCLK output clk disabled */
                            /* SOSCLPEN=0:    Sys OSC disabled in VLP modes */
                            /* SOSCSTEN=0:    Sys OSC disabled in Stop modes */
                            /* SOSCEN=1:      Enable oscillator */
  while(!(SCG->SOSCCSR & SCG_SOSCCSR_SOSCVLD_MASK)); /* Wait for sys OSC clk valid */

  // *** System PLL ***
  SCG->SPLLDIV = 0x00000101;  /* SOSCPLL1 & SPLLDIV2 =1: divide by 1 */
  SCG->SPLLCFG = 0x00180000;  /* PREDIV=0: Divide SOSC_CLK by 0+1=1 */
                              /* MULT=24:  Multiply sys pll by 24+16=40 */
                              /* SPLL_CLK = 8MHz / 1 * 40 / 2 = 160 MHz */
  while(SCG->SPLLCSR & SCG_SPLLCSR_LK_MASK); /* Ensure SPLLCSR unlocked */
  SCG->SPLLCSR = 0x00000001; /* LK=0:        SPLLCSR can be written */
                             /* SPLLCMRE=0:  SPLL CLK monitor IRQ if enabled */
                             /* SPLLCM=0:    SPLL CLK monitor disabled */
                             /* SPLLSTEN=0:  SPLL disabled in Stop modes */
                             /* SPLLEN=1:    Enable SPLL */
  while(!(SCG->SPLLCSR & SCG_SPLLCSR_SPLLVLD_MASK)); /* Wait for SPLL valid */

  // *** MODE CONFIG ***
  SCG->RCCR=SCG_RCCR_SCS(6)  /* PLL as clock source*/
	    |SCG_RCCR_DIVCORE(0x01)  /* DIVCORE= 2, Core/Sys clock = 80 MHz*/
	    |SCG_RCCR_DIVBUS(0x02)   /* DIVBUS = 4, bus clock = 40 MHz*/
	    |SCG_RCCR_DIVSLOW(0x07); /* DIVSLOW = 8, SCG slow, flash clock= 20 MHz*/

  SMC->PMCTRL  = SMC_PMCTRL_RUNM(0x0);	//enter RUN
  if ((SCG->CSR & SCG_CSR_SCS_MASK >> SCG_CSR_SCS_SHIFT ) != 6) {}
                                   /* Wait for sys clk src = SPLL */

}
/*******************************************************************************
Function Name : GPIO_Init
Engineer      : Petr Stancik
Date          : Oct-2-2016
Parameters    : NONE
Modifies      : NONE
Returns       : NONE
Notes         : Initialize LED pins
Issues        : NONE
*******************************************************************************/
void GPIO_Init(void)
{
  PCC->PCCn[PCC_PORTD_INDEX] |= PCC_PCCn_CGC_MASK;  /* CGC=1: Clock enabled */

  PORTD->PCR[0]  |= PORT_PCR_MUX(1);  /* MUX=1: PTD15, ALT=1 as GPIO */
  PORTD->PCR[15] |= PORT_PCR_MUX(1);  /* MUX=1: PTD15, ALT=1 as GPIO */
  PORTD->PCR[16] |= PORT_PCR_MUX(1);  /* MUX=1: PTD15, ALT=1 as GPIO */

  PTD->PDDR |= 1<<0  |        /* Configure BLUE LED as an output */
               1<<15 |        /* Configure RED LED as an output */
               1<<16;         /* Configure GREEN LED as an output */

  PTD->PSOR |= 1<<0  |        /* Turn off BLUE */
               1<<15 |        /* Turn off RED */
               1<<16;         /* Turn off GREEN */

}

/*******************************************************************************
Function Name : FLEXCAN0_init
Engineer      : Petr Stancik
Date          : Sep-4-2017
Parameters    : NONE
Modifies      : NONE
Returns       : NONE
Notes         : FlexCAN0 init
Issues        : NONE
*******************************************************************************/
void FLEXCAN0_init(void)
{
#define MSG_BUF_SIZE  4    /* Msg Buffer Size. (CAN 2.0AB: 2 hdr +  2 data= 4 words) */
#define LOOPBACK 1
  uint32_t   i=0;

  PCC->PCCn[PCC_FlexCAN0_INDEX] |= PCC_PCCn_CGC_MASK; /* CGC=1: enable clock to FlexCAN0 */

  CAN0->MCR |= CAN_MCR_MDIS_MASK;         /* MDIS=1: Disable module before selecting clock */
  CAN0->CTRL1 &= ~CAN_CTRL1_CLKSRC_MASK;  /* CLKSRC=0: Clock Source = oscillator (8 MHz) */
  CAN0->MCR &= ~CAN_MCR_MDIS_MASK;        /* MDIS=0; Enable module config. (Sets FRZ, HALT)*/
  while (!((CAN0->MCR & CAN_MCR_FRZACK_MASK) >> CAN_MCR_FRZACK_SHIFT))  {}
  /* Good practice: wait for FRZACK=1 on freeze mode entry/exit */

#if LOOPBACK == 0
  /* Activate Clock for PORT */
  PCC->PCCn[PCC_PORTB_INDEX] |= PCC_PCCn_CGC_MASK;     /* CGC=1: Clock enabled */

  /* Configure Pin for FlexCAN0 */
  PORTB->PCR[1] |= PORT_PCR_MUX(5); /* MUX=5:  PTB1, ALT=5 as CAN0TX */
  PORTB->PCR[0] |= PORT_PCR_MUX(5); /* MUX=5:  PTB0, ALT=5 as CAN0RX */
#endif

  CAN0->MCR |= CAN_MCR_RFEN_MASK |  /* RXFIFO enabled */
		  	  //CAN_MCR_SRXDIS_MASK | /* Disable self reception */
		  	  CAN_MCR_IRMQ_MASK |	/* Individual mask register used */
			  CAN_MCR_DMA_MASK |	/* DMA enabled */
		  	  CAN_MCR_AEN_MASK |    /* AEN=1: Abort enabled */
              CAN_MCR_IDAM(0) | 	/* ID acceptance mode; 0..Format A */
  	  	  	  CAN_MCR_MAXMB(32);	/* 32 MB used */

  /* Configure for 500 KHz bit time, 16 time quanta, cpi_clk = 8MHz */
  CAN0->CTRL1 = CAN_CTRL1_PRESDIV(0) |
		  CAN_CTRL1_RJW(3) |
		  CAN_CTRL1_PSEG1(4) |
		  CAN_CTRL1_PSEG2(4) |
#if LOOPBACK == 1
		  CAN_CTRL1_LPB_MASK |	/* LOOPBACK enabled */
#endif
		  CAN_CTRL1_PROPSEG(4);

  for(i=32; i<128; i++ ) {   /* CAN0: clear 24 msg bufs x 4 words/msg buf = 96 words*/
    CAN0->RAMn[i] = 0;      /* Clear msg buf word */
  }
  for(i=0; i<32; i++ ) {          /* In FRZ mode, init CAN0 32 msg buf filters */
    CAN0->RXIMR[i] = 0xFFFFFFFF;  /* Check all ID bits for incoming messages */
  }
  //CAN0->RXMGMASK = 0xFFFFFFFF;  /* Global acceptance mask: check all ID bits */

  // set the ID Table, assuming CTRL2[RFFN=0]
  CAN0->RAMn[ 6*MSG_BUF_SIZE + 0] = ((0)<<30 | ((0x555)<<18) << 1);  // standard ID = 0x555
  CAN0->RAMn[ 6*MSG_BUF_SIZE + 1] = (1)<<30 | (0x12340000) << 1;	// extended ID = 0x12340000
  CAN0->RAMn[ 6*MSG_BUF_SIZE + 2] = 0;
  CAN0->RAMn[ 6*MSG_BUF_SIZE + 3] = 0;
  CAN0->RAMn[ 6*MSG_BUF_SIZE + 4] = 0;
  CAN0->RAMn[ 6*MSG_BUF_SIZE + 5] = 0;
  CAN0->RAMn[ 6*MSG_BUF_SIZE + 6] = 0;
  CAN0->RAMn[ 6*MSG_BUF_SIZE + 7] = 0;




  CAN0->MCR &= ~CAN_MCR_HALT_MASK;       /* Negate HALT bit */
  while ((CAN0->MCR & CAN_MCR_FRZACK_MASK) >> CAN_MCR_FRZACK_SHIFT)  {}
                 /* Good practice: wait for FRZACK to clear (not in freeze mode) */
  while ((CAN0->MCR & CAN_MCR_NOTRDY_MASK) >> CAN_MCR_NOTRDY_SHIFT)  {}
                 /* Good practice: wait for NOTRDY to clear (module ready)  */
}

/*******************************************************************************
Function Name : TransmitMsg
Engineer      : Petr Stancik
Date          : Sep-4-2017
Parameters    : ext ... 0-standard ID, 1-extended ID
                ID ... ID to be sent
                length ... number of bytes to be sent
Modifies      : NONE
Returns       : NONE
Notes         : Transmit message once using MB8
Issues        : NONE
*******************************************************************************/
void FLEXCAN0_transmit_msg(uint8_t ext, uint32_t ID, uint8_t length)
{
	/* Assumption:  Message buffer CODE is INACTIVE */
	static uint8_t i=0;
	//uint8_t	dlc;
	uint32_t txID;

	if (ext==0) txID = ID<<18;
	else txID = ID;

	CAN0->RAMn[ 8*MSG_BUF_SIZE + 1] = txID; /* MB8 word 1: Tx msg with given ID */

	CAN0->RAMn[ 8*MSG_BUF_SIZE + 2] = i<<24 | 0x00112233; /* MB0 word 2: data word 0 */
	CAN0->RAMn[ 8*MSG_BUF_SIZE + 3] = 0x44556677; /* MB0 word 3: data word 1 */

	CAN0->RAMn[ 8*MSG_BUF_SIZE + 0] = ( 0  /* MB0 word 0 */
										| CAN_WMBn_CS_CODE(0xC) /* CODE=0xC: Activate msg buf to transmit */
										| CAN_WMBn_CS_SRR(1)	/* SRR=1 Tx frame (not req'd for std ID) */
										| CAN_WMBn_CS_IDE(ext)	/* standart or extended ID */
										| CAN_WMBn_CS_RTR(0)	/* RTR = 0: data, not remote tx request frame*/
										| CAN_WMBn_CS_DLC(length));/* DLC as needed */

	while (!(CAN0->IFLAG1 & 0x100)) {};  /* Wait for CAN 0 MB 8 flag */
	CAN0->IFLAG1 = 0x00000100;       /* Clear CAN 0 MB 8 flag without clearing others*/

	i++;
}

/*******************************************************************************
Function Name : DMA_init
Engineer      : Petr Stancik
Date          : Sep-4-2017
Parameters    : NONE
Modifies      : NONE
Returns       : NONE
Notes         : Transfer Control Descriptor 0 : HW start --> FlexCAN0 RXFIFO to Memory
Issues        : NONE
*******************************************************************************/
void DMA_init(void)
{

  //PCC->PCCn[PCC_DMA0_INDEX] |= PCC_PCCn_CGC_MASK;          	// CGC=1: Clock enabled for DMA0

  SIM->PLATCGC |= SIM_PLATCGC_CGCDMA_MASK;
    
  DMA->TCD[0].CSR &= 0xFFFFFFFF ^ DMA_TCD_CSR_DONE_MASK;  					// Clear Channel Done flag
  DMA->TCD[0].SADDR = DMA_TCD_SADDR_SADDR(&(CAN0->RAMn[0]));  				// Source Address
  DMA->TCD[0].SOFF = DMA_TCD_SOFF_SOFF(4);                					// Source Offset
  DMA->TCD[0].ATTR = DMA_TCD_ATTR_SMOD(0)  |              					// Source address modulo feature is disabled
                    DMA_TCD_ATTR_SSIZE(2) |              					// Source data transfer size: 1: 16-bit, 2=32-bit
                    DMA_TCD_ATTR_DMOD(0)  |              					// Destination address modulo feature: 0=disabled, x= x power of 2 buffer[DMOD=4->buffer of 16bytes]
                    DMA_TCD_ATTR_DSIZE(2);               					// Destination data transfer size: 1: 16-bit, 2=32-bit
  DMA->TCD[0].NBYTES.MLOFFNO = DMA_TCD_NBYTES_MLNO_NBYTES(16); 				// Minor Byte Transfer Count is 4-bytes
  DMA->TCD[0].SLAST = DMA_TCD_SLAST_SLAST(-16);             					// Last Source Address Adjustment is -16
  DMA->TCD[0].DADDR = DMA_TCD_DADDR_DADDR(&(rxBuffer[0]));     			// Destination Address of Buffer
  DMA->TCD[0].DOFF = DMA_TCD_DOFF_DOFF(4);                					// Destination Address Signed Offset is 4
  DMA->TCD[0].CITER.ELINKNO = DMA_TCD_CITER_ELINKNO_CITER(1)  				// Current Major Iteration Count is 4
                                     | DMA_TCD_CITER_ELINKNO_ELINK(0);  	// The channel-to-channel linking is disabled
  DMA->TCD[0].DLASTSGA = DMA_TCD_DLASTSGA_DLASTSGA(-16);    					// Destination last address adjustment is -16
  DMA->TCD[0].BITER.ELINKNO = DMA_TCD_BITER_ELINKNO_BITER(1) | 				// Starting major iteration count is 4
                                       DMA_TCD_BITER_ELINKNO_ELINK(0);  	// The minor channel-to-channel linking is disabled
  DMA->TCD[0].CSR = DMA_TCD_CSR_BWC(0)         |         					// BWC=0: No eDMA engine stalls - full bandwidth
                    DMA_TCD_CSR_MAJORELINK(0)  |        					// The channel-to-channel linking is disabled
                    DMA_TCD_CSR_MAJORLINKCH(0) |       						// channel 1 will be called from ch0
                    DMA_TCD_CSR_ESG(0)         |         					// The current channel?fs TCD is normal format - No scatter/gather
                    DMA_TCD_CSR_DREQ(0)        |         					// The channel's ERQ bit is not affected
                    DMA_TCD_CSR_INTHALF(0)     |         					// The half-point interrupt is disabled
                    DMA_TCD_CSR_INTMAJOR(1)    |         					// The end-of-major loop interrupt is enabled
                    DMA_TCD_CSR_START(0);                					// The channel is not explicitly started

  DMA->SERQ = 0;	// enable DMA channel 0 HW trigger
}

/*******************************************************************************
Function Name : DMAMUX_init
Engineer      : Petr Stancik
Date          : Sep-4-2017
Parameters    : NONE
Modifies      : NONE
Returns       : NONE
Notes         : configure DMAMUX ch 0 for FlexCAN0 trigger source
Issues        : NONE
*******************************************************************************/
void DMAMUX_Init (void)
{
	  PCC->PCCn[PCC_DMAMUX_INDEX] |= PCC_PCCn_CGC_MASK;    // CGC=1: Clock enabled for DMAMUX0

	  DMAMUX->CHCFG[0] &= ~ DMAMUX_CHCFG_ENBL(1);         // Disabling the DMA channel
	  DMAMUX->CHCFG[0] |= DMAMUX_CHCFG_SOURCE(54);        // FlexCAN0 is the source of the DMA0 channel
	  DMAMUX->CHCFG[0] |= DMAMUX_CHCFG_ENBL(1);           // Enabling the DMA channel
}

/*******************************************************************************
Function Name : WDOG_Disable
Engineer      : Petr Stancik
Date          : Oct-2-2016
Parameters    : NONE
Modifies      : NONE
Returns       : NONE
Notes         : Disable watchdog
Issues        : NONE
*******************************************************************************/
void WDOG_Disable(void)
{
	WDOG->CNT=0xD928C520; 			/*Unlock watchdog*/
	WDOG->CS &= ~WDOG_CS_EN_MASK;  	/*Disable watchdog*/
}

/*******************************************************************************
Function Name : IRQs_Init
Engineer      : Petr Stancik
Date          : Sep-4-2017
Parameters    : NONE
Modifies      : NONE
Returns       : NONE
Notes         : enable interrupt from DMA ch0
Issues        : NONE
*******************************************************************************/
void IRQs_Init (void)
{
	S32_NVIC->ICPR[0] = 1 << (0 % 32);  /* IRQ0-DMA ch0: clr any pending IRQ*/
	S32_NVIC->ISER[0] = 1 << (0 % 32);  /* IRQ0-DMA ch0: enable IRQ */
 	S32_NVIC->IP[0] = 0xA;              /* IRQ0-DMA ch0: priority 10 of 0-15*/
}

/*******************************************************************************
Function Name : DMA0_IRQHandler
Engineer      : Petr Stancik
Date          : Sep-4-2017
Parameters    : NONE
Modifies      : NONE
Returns       : NONE
Notes         : DMA ch0 interrupt routine
Issues        : NONE
*******************************************************************************/
void DMA0_IRQHandler(void)
{
	uint16_t ID_hit;

	DMA->CINT = 0; // clear DMA channel 0 interrupt flag

	// check, which Identifier Acceptance Filter was hit
	ID_hit = (rxBuffer[0] & 0xFF800000)>>23;

	if(ID_hit == 0) FLEXCAN0_transmit_msg (1,0x12340000,8);/* Transmit extended ID=0x12340000 */
	if(ID_hit == 1) FLEXCAN0_transmit_msg (0,0x555,8);     /* Transmit standard ID=0x555 */
}


int main(void)
{
#define COUNTER_LIMIT 100

	int counter = 0;

	WDOG_Disable();
	SCG_Init();
	GPIO_Init();
	FLEXCAN0_init();
	DMA_init();
	DMAMUX_Init();

	IRQs_Init();

	FLEXCAN0_transmit_msg (0,0x555,8);     /* Transmit message using MB8, standard ID=0x555, 8 bytes */

	for(;;)
	{
		counter++;

		if(counter > COUNTER_LIMIT)
		{
			counter = 0;
		}

	}

    /* to avoid the warning message for GHS and IAR: statement is unreachable*/
#if defined (__ghs__)
#pragma ghs nowarning 111
#endif
#if defined (__ICCARM__)
#pragma diag_suppress=Pe111
#endif
//	return 0;
}
