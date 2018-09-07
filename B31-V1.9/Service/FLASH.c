#include "flash.h"

void FLASH_Init(void)
{
	PCC->PCCn[PCC_FTFC_INDEX]=  PCC_PCCn_CGC_MASK;
	LMEM->PCCCR = 0x85000001; /* Invalidate cache & enable write buffer, cache */
	MSCM->OCMDR[0] = 0x00000020; /* Bit 5 = 1: Enable program flash prefetch buffer */
	MSCM->OCMDR[1] = 0x00000020; /* Bit 5 = 1: Enable data flash prefetch buffer */
}

//__attribute__((section("RAMCODE")))
void Flash_LaunchCommand(void)
{
	__disable_irq();
	FTFC->FSTAT |= FTFC_FSTAT_CCIF_MASK;//launch command
	while(!(FTFC->FSTAT & FTFC_FSTAT_CCIF_MASK)){;}
	__enable_irq();
}

void FLASH_Program2LongWord(uint32_t u24NVMTargetAddress, uint64_t u64DwData)
{
	while((FTFC->FSTAT & FTFC_FSTAT_CCIF_MASK) == 0);   //wait if operation in progress 
	FTFC->FSTAT = FTFC_FSTAT_FPVIOL_MASK | FTFC_FSTAT_ACCERR_MASK | FTFC_FSTAT_FPVIOL_MASK; 
	FTFC->FCCOB[3] = 0x07;  //Program Phrase command (0x07) 
	FTFC->FCCOB[2] = (u24NVMTargetAddress>>16) & 0xff;  //Flash address [23:16] 
	FTFC->FCCOB[1] = (u24NVMTargetAddress>>8) & 0xff;   //Flash address [15:08] 
	FTFC->FCCOB[0] = (u24NVMTargetAddress>>0) & 0xff;   //Flash address [7:0]   
	FTFC->FCCOB[7] = (u64DwData>>0) & 0xff;  //data[0]
	FTFC->FCCOB[6] = (u64DwData>>8) & 0xff;  //data
	FTFC->FCCOB[5] = (u64DwData>>16) & 0xff;  //data
	FTFC->FCCOB[4] = (u64DwData>>24) & 0xff;  //data;  
	FTFC->FCCOB[11]= (u64DwData>>32) & 0xff;  //data; 
	FTFC->FCCOB[10]= (u64DwData>>40) & 0xff;  //data; 
	FTFC->FCCOB[9] = (u64DwData>>48) & 0xff;  //data;  
	FTFC->FCCOB[8] = (u64DwData>>56) & 0xff;  //data[7];  

	Flash_LaunchCommand();
}

uint8_t FLASH_Program(uint32_t u24NVMTargetAddress, uint8_t *pData, uint16_t u16SizeBytes)
{
	uint16_t u16w2LongWordCount = u16SizeBytes>>3;
	uint64_t *pDwData = (uint64_t*)pData;
	uint16_t  i;
	
	// Check address to see if it is aligned to 4 bytes
	// Global address [1:0] must be 00.
	if(u24NVMTargetAddress & 0x07)
	{
		return 0;
	}
	if(u16SizeBytes & 0x07)//”– £”‡
	{
		u16w2LongWordCount++;
	}
	// Loop for the two longwords (8 bytes) programming
	for(i = 0; i < u16w2LongWordCount; i++)
	{
		FLASH_Program2LongWord(u24NVMTargetAddress, *pDwData++);
		u24NVMTargetAddress += 8;
	}
	return 1;
}

//*****************************************************************************//*!
//  *
//  * @brief erase flash sector, each flash sector is of 512 bytes long.
//  *      
//  *        
//  * @param[in]   u32NVMTargetAddress erase sector address.
//  *
//  * @return error status.
//  *
//  * @ Pass/ Fail criteria: none.
//*****************************************************************************/
void FLASH_EraseSector(uint32_t u24NVMTargetAddress)
{
	//erase 4KB flash sector (the smallest entity that can be erased)
	while((FTFC->FSTAT & FTFC_FSTAT_CCIF_MASK) == 0);   //wait if operation in progress
	FTFC->FSTAT = FTFC_FSTAT_FPVIOL_MASK | FTFC_FSTAT_ACCERR_MASK | FTFC_FSTAT_FPVIOL_MASK; //clear flags if set
	FTFC->FCCOB[3] = 0x09;  //Erase Flash Sector command (0x09) 
	FTFC->FCCOB[2] = (u24NVMTargetAddress>>16) & 0xff;  //Flash address [23:16] 
	FTFC->FCCOB[1] = (u24NVMTargetAddress>>8) & 0xff;  //Flash address [15:08] 
	FTFC->FCCOB[0] = (u24NVMTargetAddress>>0) & 0xff; //Flash address [7:0]   

	Flash_LaunchCommand();
}

uint32_t FLASH_Read(uint32_t u32NVMTargetAddress)
{
  uint32_t tem;
  tem=*(volatile uint32_t*)(u32NVMTargetAddress);
  return tem;
}
//end
