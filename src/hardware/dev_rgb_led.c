/*
 * dev_rgb_led.c
 *
 *  Created on: 2023年2月16日
 *      Author: 好
 */
#define LOG_TAG    "dev_rgb_led"

#include "../hardware/dev_rgb_led.h"

static int init_dev_rgb_led(const char *dev_name );

static int dev_rgb_led_fd = -1 ;

int dev_rgb_led_init(void){
	dev_rgb_led_fd= init_dev_rgb_led("/dev/dev_rgb_led");
	return dev_rgb_led_fd ;
}


void dev_control_rgb_led( RGB_NUMBER led_number , RGB_CONTROL_STATE rgb_control_state){
	int ret =-1;
	if( MAX_LED_NUMBER>led_number ){
		switch (led_number) {
			case R_LED_NUMBER:
				ret = ioctl(dev_rgb_led_fd, SET_R_LEDS_ACTION, &rgb_control_state);
			   if (ret < 0){
					log_e("SET_R_LEDS_ACTION error!! %d", ret);
				}
				break;
			case G_LED_NUMBER:
				ret = ioctl(dev_rgb_led_fd, SET_G_LEDS_ACTION, &rgb_control_state);
			   if (ret < 0){
					log_e("SET_G_LEDS_ACTION error!! %d", ret);
				}
				break;
			case B_LED_NUMBER:
				ret = ioctl(dev_rgb_led_fd, SET_B_LEDS_ACTION, &rgb_control_state);
			   if (ret < 0){
					log_e("SET_B_LEDS_ACTION error!! %d", ret);
				}
				break;
			default:
				break;
		}
	}
}


static int init_dev_rgb_led(const char *dev_name ){
    int fd;
//    fd = open(tty_busy, O_RDWR|O_NONBLOCK);//O_RDWR|O_NONBLOCK
    fd = open(dev_name, O_RDWR);//O_RDWR|O_NONBLOCK
    if (fd < 0)
    {
		log_e("Initialize check_mode device %s failed!", dev_name);
		exit(EXIT_FAILURE);
    }
    log_d("open check_mode %s success!", dev_name);
    return fd ;
}
