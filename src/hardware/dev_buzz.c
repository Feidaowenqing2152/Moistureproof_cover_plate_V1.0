/*
 * dev_buzz.c
 *
 *  Created on: 2023年2月17日
 *      Author: 好
 */

#define LOG_TAG    "dev_buzz"

#include "../hardware/dev_buzz.h"


static int init_dev_buzz(const char *dev_name );

static int dev_buzz_fd = -1 ;

int dev_buzz_init(void){
	dev_buzz_fd= init_dev_buzz("/dev/dev_buzz");
	return dev_buzz_fd ;
}


void dev_control_buzz_state( ControlBuzzStateType_t buzz_type , ControlBuzzState_t buzz_state){
	int ret =-1;
	ret = ioctl(dev_buzz_fd, ENABLE_BUZZ_BLINK, &buzz_type);
   if (ret < 0){
		log_e("ENABLE_BUZZ_BLINK error!! %d", ret);
	}
	if(buzz_type == BUZZ_BLINK_DISABLE ){
		ret = ioctl(dev_buzz_fd, SET_BUZZ_ACTION, &buzz_state);
	   if (ret < 0){
			log_e("SET_BUZZ_ACTION error!! %d", ret);
		}
	}
}


void dev_set_buzz_frq( int buzz_frq_ms){	//设置buzz频率
	int ret =-1;
	ret = ioctl(dev_buzz_fd, SET_BUZZ_FRQ, &buzz_frq_ms);
   if (ret < 0){
		log_e("SET_BUZZ_FRQ error!! %d", ret);
	}
}



static int init_dev_buzz(const char *dev_name ){
    int fd;
//    fd = open(tty_busy, O_RDWR|O_NONBLOCK);//O_RDWR|O_NONBLOCK
    fd = open(dev_name, O_RDWR);//O_RDWR|O_NONBLOCK
    if (fd < 0)
    {
		log_e("Initialize dev_buzz device %s failed!", dev_name);
		exit(EXIT_FAILURE);
    }
    log_d("open dev_buzz %s success!", dev_name);
    return fd ;
}














