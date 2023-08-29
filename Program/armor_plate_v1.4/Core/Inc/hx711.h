
#ifndef HX711_H
#define HX711_H

#include "struct_typedef.h"

#define HX711_DOUT(__ID__) \
	((__ID__ == 1) ? HAL_GPIO_ReadPin(GPIOA,GPIO_PIN_2)==GPIO_PIN_SET :\
   (__ID__ == 2) ? HAL_GPIO_ReadPin(GPIOA,GPIO_PIN_4)==GPIO_PIN_SET :\
   (__ID__ == 3) ? HAL_GPIO_ReadPin(GPIOA,GPIO_PIN_15)==GPIO_PIN_SET :\
   HAL_GPIO_ReadPin(GPIOB,GPIO_PIN_4)==GPIO_PIN_SET)

#define HX711_SCK(__ID__,__STATE__) \
	((__ID__ == 1) ? HAL_GPIO_WritePin(GPIOA,GPIO_PIN_3,__STATE__) :\
   (__ID__ == 2) ? HAL_GPIO_WritePin(GPIOA,GPIO_PIN_5,__STATE__) :\
   (__ID__ == 3) ? HAL_GPIO_WritePin(GPIOB,GPIO_PIN_3,__STATE__) :\
   HAL_GPIO_WritePin(GPIOB,GPIO_PIN_5,__STATE__))
	 
#define HX711_SCK_HIGH(__ID__) HX711_SCK(__ID__,GPIO_PIN_SET)
#define HX711_SCK_LOW(__ID__) HX711_SCK(__ID__,GPIO_PIN_RESET)

extern int32_t hx711_data[4];
extern uint8_t hx711_hit[4];
extern uint8_t hx711_press[4];
#define HX711_1KG 600.0
#define HIT_KG (1/35.0)
#define PRESS_KG (1/8.0)
#define ALL_HIT (hx711_hit[0]&&hx711_hit[1]&&hx711_hit[2]&&hx711_hit[3])
#define ALL_PRESS (hx711_press[0]&&hx711_press[1]&&hx711_press[2]&&hx711_press[3])

extern uint32_t HX711_Read(uint8_t id);
extern void HX711_Task(void);

#endif //HX711_H
