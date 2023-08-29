
#include "user.h"
#include "hx711.h"
#include "sk6812.h"
#include "cmsis_os.h"
#include <stdio.h>
#include "usart.h"
#include "flash.h"

/*private variables*/
uint16_t press_cnt;
uint16_t up_cnt;
uint16_t setting_cnt;
uint8_t mode;
uint8_t can_id = 0;
uint8_t state = 0;
uint16_t time_cnt = 0; 

void User_Task(void)
{
	mode = STANDBY;
	can_id = (Flash_Read16(FLASH_SAVE_ADDR)>>8)&0xFF;
	color = Flash_Read16(FLASH_SAVE_ADDR)&0xFF;
	osDelay(1000);
	while(1)
	{
		//按键模式转换
		switch(mode)
		{
			case STANDBY:
				press_cnt = 0;
				up_cnt = 0;
				setting_cnt = 0;
				light_on = 1;
				if(ALL_PRESS)mode = PRESSING;  //检测到按压则进入PRESSING模式
				break;
			
			case PRESSING:
				press_cnt++;
				if(!ALL_PRESS)
					mode = PRESS_UP;
				if(press_cnt>SET_CANID_PRESS_TIME_MS) //长按一定时间，进入设置canid模式
				{	
					can_id = 0;
					mode = SETTING;
				}
				break;
				
			case PRESS_UP:
				up_cnt++;
				if(ALL_PRESS)
					mode = PRESSING;
				if(up_cnt>UP_TIME_MS) //消抖 超过秒数后返回默认模式
					mode = STANDBY;
				//按住一定秒数后放开
				if(press_cnt<SET_CANID_PRESS_TIME_MS && press_cnt>CHANGE_COLOR_PRESS_TIME_MS && up_cnt>UP_TIME_MS)
				{
					color = (color+1)%COLOR_COUNT; //改变颜色
					uint16_t tmp = (color | (can_id << 8));
					Flash_Write16(FLASH_SAVE_ADDR,tmp); //保存颜色值至flash
				}
				break;
			
			//设置can id
			case SETTING:
				light_on = 0; //进入设置模式后关闭灯
				setting_cnt++;
				if(ALL_HIT)
				{
					can_id++; //敲一下canid加一
					uint16_t tmp = (color | (can_id << 8));
					Flash_Write16(FLASH_SAVE_ADDR,tmp); //保存can_id至flash
					osDelay(200); //等待闪烁，且消抖
				}
				if(setting_cnt>SETTING_MAX_TIME_MS) //超过秒数后返回默认模式
					mode = STANDBY;
				break;
		}
	
#ifdef DEBUG_USER
		char buf[30];
		sprintf(buf,"m:%05d,%05d,%05d\n",press_cnt,up_cnt,setting_cnt>SETTING_MAX_TIME);
		HAL_UART_Transmit(&huart1,(uint8_t*)buf,20,0xFFFF);
#endif
		
		//板子上的灯的闪烁，闪的次数表示can_id
		uint16_t blink_cnt = BLINK_LED_TIME_MS*can_id*2;
		if(++time_cnt%BLINK_LED_TIME_MS==0 && time_cnt<=blink_cnt)
			state = !state & 0x1;
		//保存常亮一段时间，超过时间则归零
		else if(time_cnt>blink_cnt+STOP_BLINK_LED_TIME_MS)
			time_cnt = 0;
		HAL_GPIO_WritePin(LED_GPIO_Port,LED_Pin,(GPIO_PinState)state);
		
		osDelay(1); //限制更新时间，确保计时准确
	}
}
