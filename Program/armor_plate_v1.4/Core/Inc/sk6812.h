
#ifndef SK6812_H
#define SK6812_H

#include "struct_typedef.h"

#define SK6812_LOW 23	// 23*(1/800kHz)=2.875us
#define SK6812_HIGH 45
#define SK6812_LEDS_NUM 9
#define RGB 24
#define RESET_TIME 90	// 80us/(1/800kHz)=64
#define SK6812_BUFFER_SIZE (RGB*SK6812_LEDS_NUM+RESET_TIME)
#define SK6812_RGB(r,g,b) ((g << 16) | (r << 8) | b)
#define SK6812_RGB_BIT(i,r,g,b) ((SK6812_RGB(r,g,b) << i) & 0x800000)

typedef struct
{
	uint16_t RESET_Buffer[RESET_TIME];
	uint16_t LEDS_Buffer[SK6812_LEDS_NUM][RGB];
}SK6812_Buffer_s;

#define LIGHTNESS (float)0xFF
#define MAX_LIGHT (float)0xFF

typedef enum
{
	BLUE = 0,
	RED, 
	CYAN,//青色
	ORAN, //橙色
	PURPLE, //紫色
	WHITE,
	COLOR_COUNT
}Color_e;

#define BLUE_R 0x0
#define BLUE_G 0x0
#define BLUE_B LIGHTNESS
#define RED_R LIGHTNESS
#define RED_G 0x0
#define RED_B 0x0
#define CYAN_R 0x00*(LIGHTNESS/MAX_LIGHT)
#define CYAN_G 0x60*(LIGHTNESS/MAX_LIGHT)
#define CYAN_B 0x43*(LIGHTNESS/MAX_LIGHT)
#define ORAN_R 0x7F*(LIGHTNESS/MAX_LIGHT)
#define ORAN_G 0x20*(LIGHTNESS/MAX_LIGHT)
#define ORAN_B 0x00*(LIGHTNESS/MAX_LIGHT)
#define PURPLE_R LIGHTNESS
#define PURPLE_G 0x0
#define PURPLE_B LIGHTNESS

#define WHITE_R LIGHTNESS
#define WHITE_G LIGHTNESS
#define WHITE_B LIGHTNESS
#define COLOR_RGB(__COLOR__,__ID__)\
	((__COLOR__ == BLUE) ? ((__ID__==0)?BLUE_R:(__ID__==1)?BLUE_G: BLUE_B):\
   (__COLOR__ == RED)  ? ((__ID__==0)?RED_R: (__ID__==1)?RED_G:  RED_B) :\
   (__COLOR__ == CYAN) ? ((__ID__==0)?CYAN_R:(__ID__==1)?CYAN_G: CYAN_B):\
   (__COLOR__ == ORAN) ? ((__ID__==0)?ORAN_R:(__ID__==1)?ORAN_G: ORAN_B) :\
	 (__COLOR__ == PURPLE) ? ((__ID__==0)?PURPLE_R:(__ID__==1)?PURPLE_G: PURPLE_B) :\
	((__ID__==0)?WHITE_R:(__ID__==1)?WHITE_G: WHITE_B))
#define COLOR_NAME(__COLOR__)\
	((__COLOR__==BLUE) ? "BLUE":\
	(__COLOR__==RED) ? "RED":\
	(__COLOR__==CYAN) ? "CYAN":\
	(__COLOR__==ORAN) ?"ORANGE":\
	(__COLOR__==PURPLE) ?"PURPLE":\
			"WHITE")

extern uint8_t color;
extern uint8_t light_on;
extern void SK6812_LEDS_Reset(void);
extern void SK6812_LEDS_Set(void);
extern void SK6812_LEDS_Blink(void);

#endif //SK6812_H
