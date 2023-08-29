
#include "flash.h"

void Flash_Erase(uint32_t addr)
{
	FLASH_EraseInitTypeDef My_Flash;  //声明FLASH_EraseInitTypeDef 结构体为 My_Flash
	HAL_FLASH_Unlock(); //解锁Flash
            
	My_Flash.TypeErase = FLASH_TYPEERASE_PAGES;  //标明Flash执行页面只做擦除操作
	My_Flash.PageAddress = addr;  //声明要擦除的地址
	My_Flash.NbPages = 1; //说明要擦除的页数，此参数必须是Min_Data = 1和Max_Data =(最大页数-初始页的值)之间的值
					
	uint32_t PageError = 0;  //设置PageError,如果出现错误这个变量会被设置为出错的FLASH地址
	HAL_FLASHEx_Erase(&My_Flash, &PageError);  //调用擦除函数擦除
	HAL_FLASH_Lock();
}

void Flash_Write16(uint32_t addr, uint16_t data)
{
	HAL_FLASH_Unlock(); //解锁Flash
	FLASH_EraseInitTypeDef My_Flash;  //声明FLASH_EraseInitTypeDef 结构体为 My_Flash
            
	My_Flash.TypeErase = FLASH_TYPEERASE_PAGES;  //标明Flash执行页面只做擦除操作
	My_Flash.PageAddress = addr;  //声明要擦除的地址
	My_Flash.NbPages = 1; //说明要擦除的页数，此参数必须是Min_Data = 1和Max_Data =(最大页数-初始页的值)之间的值
					
	uint32_t PageError = 0;  //设置PageError,如果出现错误这个变量会被设置为出错的FLASH地址
	HAL_FLASHEx_Erase(&My_Flash, &PageError);  //调用擦除函数擦除
	HAL_FLASH_Program(FLASH_TYPEPROGRAM_HALFWORD, addr, data); //对Flash进行烧写
	HAL_FLASH_Lock(); //锁住Flash
}

void Flash_Write32(uint32_t addr, uint32_t data)
{
	HAL_FLASH_Unlock(); //解锁Flash
	FLASH_EraseInitTypeDef My_Flash;  //声明FLASH_EraseInitTypeDef 结构体为 My_Flash
            
	My_Flash.TypeErase = FLASH_TYPEERASE_PAGES;  //标明Flash执行页面只做擦除操作
	My_Flash.PageAddress = addr;  //声明要擦除的地址
	My_Flash.NbPages = 1; //说明要擦除的页数，此参数必须是Min_Data = 1和Max_Data =(最大页数-初始页的值)之间的值
					
	uint32_t PageError = 0;  //设置PageError,如果出现错误这个变量会被设置为出错的FLASH地址
	HAL_FLASHEx_Erase(&My_Flash, &PageError);  //调用擦除函数擦除
	HAL_FLASH_Program(FLASH_TYPEPROGRAM_WORD, addr, data); //对Flash进行烧写
	HAL_FLASH_Lock(); //锁住Flash
}
