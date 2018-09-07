#ifndef FLASH_H_
#define FLASH_H_

#include "common.h"

void Flash_LaunchCommand(void);
void FLASH_Init(void);
void FLASH_EraseSector(uint32_t u24NVMTargetAddress);
uint32_t FLASH_Read(uint32_t u32NVMTargetAddress);
uint8_t FLASH_Program(uint32_t u24NVMTargetAddress, uint8_t *pData, uint16_t u16SizeBytes);

#endif /* FLASH_H_ */
