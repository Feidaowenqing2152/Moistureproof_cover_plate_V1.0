/*
 * dev_check_mode.c
 *
 *  Created on: 2023年2月16日
 *      Author: 好
 */
#define LOG_TAG    "dev_check_mode"

#include "../hardware/dev_check_mode.h"

static int init_dev_check_mode(const char *dev_name );
static int check_mode_setting_shake_time(int check_mode_shake_time);
static int setting_check_mode_enable(int check_mode_enable);

static int dev_check_mode_fd = 0 ;


int dev_check_mode_init(void){
	dev_check_mode_fd= init_dev_check_mode("/dev/dev_check_mode");
	setting_check_mode_enable(WORK_MODE);            //使能检测
	check_mode_setting_shake_time(10);       //设置检测工作模式管脚消抖时间
	return dev_check_mode_fd ;
}


//设备操作：读工作模式管脚状态
uint8_t get_work_mode_state(void){
	int state = -1 ;
	int ret = -1 ;
	ret = ioctl(dev_check_mode_fd, GET_CHECK_MODE_STATE, &state);
   if (ret < 0)
	{
		log_w("GET_CHECK_MODE_STATE error!! %d", ret);
	}
   if( state == WORK_MODE ){
	   return WORK_MODE ;
   }else{
	   return FIX_MODE ;
   }
}


static int init_dev_check_mode(const char *dev_name ){
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
//设置检测工作模式管脚消抖时间
static int check_mode_setting_shake_time(int check_mode_shake_time){
	int ret = -1 ;
	ret = ioctl(dev_check_mode_fd, SET_CHECK_MODE_DEBOUNCING_TIMER, &check_mode_shake_time);
   if (ret < 0)
	{
		log_w("SET_CHECK_MODE_DEBOUNCING_TIMER error!! %d", ret);
	}
   return ret;
}

//设置是否使能检测工作模式功能
static int setting_check_mode_enable(int check_mode_enable){
	int ret = -1 ;
	ret = ioctl(dev_check_mode_fd, ENABLE_CHECK_MODE_FUNCTION, &check_mode_enable);
   if (ret < 0)
	{
		log_w("ENABLE_CHECK_MODE_FUNCTION error!! %d", ret);
	}
   return ret;
}



