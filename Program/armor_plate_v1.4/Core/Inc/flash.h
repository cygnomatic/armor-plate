
#ifndef FLASH_H_
#define FLASH_H_

#include "main.h"
#include "struct_typedef.h"

#define Flash_Read16(addr) (*(__IO uint16_t*)(addr))
#define Flash_Read32(addr) (*(__IO uint32_t*)(addr))

extern void Flash_Erase(uint32_t addr);
extern void Flash_Write16(uint32_t addr, uint16_t data);
extern void Flash_Write32(uint32_t addr, uint32_t data);

#endif /* FLASH_H_ */

