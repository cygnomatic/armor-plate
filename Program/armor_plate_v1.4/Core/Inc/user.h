
#ifndef USER_H
#define USER_H

#include "struct_typedef.h"

#define CHANGE_COLOR_PRESS_TIME_MS 3000
#define SET_CANID_PRESS_TIME_MS 8000
#define UP_TIME_MS 1000
#define SETTING_MAX_TIME_MS 20000
#define FLASH_SAVE_ADDR 0x8007C00 //注意地址需要为4的整数
#define BLINK_LED_TIME_MS 250
#define STOP_BLINK_LED_TIME_MS 1000

typedef enum
{
	STANDBY = 0,
	PRESSING,
	PRESS_UP,
	SETTING
}Mode_e;

extern uint8_t can_id;
extern void User_Task(void);

#endif //USER_H
