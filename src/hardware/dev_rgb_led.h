/*
 * dev_rgb_led.h
 *
 *  Created on: 2023年2月16日
 *      Author: 好
 */

#ifndef HARDWARE_DEV_RGB_LED_H_
#define HARDWARE_DEV_RGB_LED_H_

#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>
#include <getopt.h>
#include <unistd.h>
#include <fcntl.h>
#include <string.h>
#include <sys/types.h>
#include <sys/ioctl.h>
#include <sys/stat.h>
#include <sys/time.h>
#include <sys/select.h>
#include <sys/socket.h>
#include <time.h>
#include <stdbool.h>
#include <pthread.h>
#include <errno.h>
#include <net/if.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <signal.h>


#include <elog.h>

//按键枚举
typedef enum{
	R_LED_NUMBER = 0,	
	G_LED_NUMBER ,		   
	B_LED_NUMBER,
	
MAX_LED_NUMBER}RGB_NUMBER;

typedef enum{
	RGB_LED_OFF = 1,
	RGB_LED_ON =!RGB_LED_OFF,
	RGB_LED_ERROR =2,

}RGB_CONTROL_STATE;

//#define RGB_LED_OFF 1
//#define RGB_LED_ON 0

//自定义的ioctl命令
#define DEV_RGB_LEDS_TYPE 'l'                               //设备类型
#define SET_R_LEDS_ACTION _IOW(DEV_RGB_LEDS_TYPE, 0x1, int) //设备操作：设置RLED
#define SET_G_LEDS_ACTION _IOW(DEV_RGB_LEDS_TYPE, 0x2, int)
#define SET_B_LEDS_ACTION _IOW(DEV_RGB_LEDS_TYPE, 0x3, int)
#define RGB_LEDS_IOC_MAXNR 3

int dev_rgb_led_init(void);
void dev_control_rgb_led( RGB_NUMBER led_number , RGB_CONTROL_STATE rgb_control_state);

#endif /* HARDWARE_DEV_RGB_LED_H_ */
