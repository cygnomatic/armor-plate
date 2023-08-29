/*
*/

#include "hx711.h"
#include "main.h"
#include "usart.h"
#include "cmsis_os.h"
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

/*public variables*/
int32_t hx711_data[4];
uint8_t hx711_hit[4];
uint8_t hx711_press[4];

/*private variables*/
int32_t hit_data[4];
int32_t last_data[4];
char buf[100];

uint32_t HX711_Read(uint8_t id)
{
	while(HX711_DOUT(id));
	
	uint32_t count = 0;
  for(uint8_t i=0; i<24; i++)
	{
			HX711_SCK_HIGH(id);
			count=count<<1;
			HX711_SCK_LOW(id);
			if(HX711_DOUT(id))
					count++;
	}
	HX711_SCK_HIGH(id);
	count=count^0x800000;//第25个脉冲下降沿来时，转换数据
	HX711_SCK_LOW(id);
	return count;
}

void HX711_Task(void)
{
	while(1)
	{
		//处理数据
		for(uint8_t i=0;i<4;i++)
		{
			hx711_data[i] = HX711_Read(i+1)>>(24-17);
			hx711_hit[i] = last_data[i] < (hx711_data[i]-(HX711_1KG*HIT_KG)); //检测击打
			hx711_press[i] = hx711_data[i]<(hit_data[i]-(HX711_1KG*PRESS_KG)); //检测按压
			last_data[i] = hx711_data[i];
		}
		
		if(ALL_HIT)
		{
			// 初始化时，hx711_hit默认都为1，hit_data会保存为初始化数值
			for(uint8_t i=0;i<4;i++)
				hit_data[i] = hx711_data[i];			
		}                                         
		
//#define DEBUG_HX711
#ifdef DEBUG_HX711
		//sprintf(buf,"s:%d,%d,%d,%d\n",hx711_hit[0],hx711_hit[1],hx711_hit[2],hx711_hit[3]);
		//sprintf(buf,"s:%d,%d,%d,%d\n",hx711_press[0],hx711_press[1],hx711_press[2],hx711_press[3]);
		sprintf(buf,"s:%d,%d,%d,%d\n",hx711_data[0],hx711_data[1],hx711_data[2],hx711_data[3]);
		HAL_UART_Transmit(&huart1,(uint8_t*)buf,strlen(buf),0xFFFF);
#endif
		osDelay(1);
	}
}
