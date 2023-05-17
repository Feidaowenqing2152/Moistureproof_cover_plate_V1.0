/*
 * rgb_led.h
 *
 *  Created on: 2023年4月20日
 *      Author: 好
 */

#ifndef DRIVE_RGB_LED_H_
#define DRIVE_RGB_LED_H_

#include "../common.h"

typedef enum {
	RGB_INIT_MODE = 0 ,    	//全灭
	RGB_WORK_MODE ,			//绿色常亮
	RGB_CHECK_MODE ,		//红色闪烁
	RGB_REMOTE_MODE ,		//黄灯闪烁
	RGB_SYS_ERROR  ,		//红色常亮
}Rgb_Led_Mode_Type;

#define RGB_BLINK_TIMER  500

void rgb_led_init(void);

void Show_Rgb_Led_Main(uint8_t rgb_led_mode);

#endif /* DRIVE_RGB_LED_H_ */
