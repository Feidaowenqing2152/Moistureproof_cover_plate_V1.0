/*
 * rgb_led.c
 *
 *  Created on: 2023年4月20日
 *      Author: 好
 */

#define LOG_TAG    "rgb_led"

#include "../drive/rgb_led.h"


void rgb_led_init(void){
	dev_rgb_led_init();
	clear_time_cnt(SHOW_MODE_RGB_LED_BLINK_TIMER_NUMBER);
	dev_control_rgb_led(R_LED_NUMBER,RGB_LED_OFF);
	dev_control_rgb_led(G_LED_NUMBER,RGB_LED_OFF);
	dev_control_rgb_led(B_LED_NUMBER,RGB_LED_OFF);
}



void Show_Rgb_Led_Main(uint8_t rgb_led_mode){
	static uint8_t blink_flag =0 ;
	switch(rgb_led_mode){
	case RGB_WORK_MODE:
		dev_control_rgb_led(R_LED_NUMBER,RGB_LED_OFF);
		dev_control_rgb_led(G_LED_NUMBER,RGB_LED_ON);
		dev_control_rgb_led(B_LED_NUMBER,RGB_LED_OFF);
		blink_flag = 0 ;
		break;
	case RGB_CHECK_MODE:
		if(check_time_arrive(SHOW_MODE_RGB_LED_BLINK_TIMER_NUMBER,RGB_BLINK_TIMER)){
			blink_flag =!blink_flag;
			dev_control_rgb_led(R_LED_NUMBER,blink_flag);
			dev_control_rgb_led(G_LED_NUMBER,RGB_LED_OFF);
			dev_control_rgb_led(B_LED_NUMBER,RGB_LED_OFF);
			clear_time_cnt(SHOW_MODE_RGB_LED_BLINK_TIMER_NUMBER);
		}
		break;
	case RGB_REMOTE_MODE:
		if(check_time_arrive(SHOW_MODE_RGB_LED_BLINK_TIMER_NUMBER,RGB_BLINK_TIMER)){
			blink_flag =!blink_flag;
			dev_control_rgb_led(R_LED_NUMBER,RGB_LED_OFF);
			dev_control_rgb_led(G_LED_NUMBER,RGB_LED_OFF);
			dev_control_rgb_led(B_LED_NUMBER,blink_flag);
			clear_time_cnt(SHOW_MODE_RGB_LED_BLINK_TIMER_NUMBER);
		}
		break;
	case RGB_SYS_ERROR:
		dev_control_rgb_led(R_LED_NUMBER,RGB_LED_ON);
		dev_control_rgb_led(G_LED_NUMBER,RGB_LED_OFF);
		dev_control_rgb_led(B_LED_NUMBER,RGB_LED_OFF);
		blink_flag = 0 ;
		break;
	default:
		dev_control_rgb_led(R_LED_NUMBER,RGB_LED_OFF);
		dev_control_rgb_led(G_LED_NUMBER,RGB_LED_OFF);
		dev_control_rgb_led(B_LED_NUMBER,RGB_LED_OFF);
		break;

	}
}

