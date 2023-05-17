/*
 * dev_buttons.c
 *
 *  Created on: 2023年2月10日
 *      Author: 好
 */

#define LOG_TAG    "dev_buttons"

#include "../hardware/dev_buttons.h"

static int init_dev_buttons(const char *dev_name );
static int buttons_setting_shake_time(int shake_time);

static int dev_buttons_fd = -1 ;

int init_buttons(int shake_time){

	dev_buttons_fd= init_dev_buttons("/dev/dev_buttons");
	buttons_setting_shake_time(shake_time);
	return dev_buttons_fd ;
}


static int init_dev_buttons(const char *dev_name ){

    int fd;
//    fd = open(tty_busy, O_RDWR|O_NONBLOCK);//O_RDWR|O_NONBLOCK
    fd = open(dev_name, O_RDWR);//O_RDWR|O_NONBLOCK
    if (fd < 0)
    {
		log_e("Initialize dev_buttons device %s failed!", dev_name);
		exit(EXIT_FAILURE);
    }
    log_d("open dev_buttons %s success!", dev_name);
    return fd ;
}

static int buttons_setting_shake_time(int shake_time){
	int ret = -1 ;
	ret = ioctl(dev_buttons_fd, SET_CHECK_KEY_DEBOUNCING_TIMER, &shake_time);
   if (ret < 0)
	{
		log_e("SET_CHECK_KEY_DEBOUNCING_TIMER error!! %d", ret);
	}
   return ret;
}

 uint8_t get_buttons_state( key_Input_Number_Typedef buttons_number){
	int ret = -1 ;
	int buttons_val = -1 ;

	if( MAX_KEY_NUMBER >buttons_number){
		switch(buttons_number){
		case KEY_UP_TRG_NUMBER :
			ret = ioctl(dev_buttons_fd, GET_KEY_UP_STATE, &buttons_val);
		   if (ret < 0)
			{
				log_e("GET_KEY_UP_STATE error!! %d", ret);
				return IO_KEY_ERROR ;
			}
		   if(buttons_val==IO_KEY_ON)
			   return IO_KEY_ON;
		   else
			   return IO_KEY_OFF ;
			break;
		case KEY_ENTER_TRG_NUMBER :
			ret = ioctl(dev_buttons_fd, GET_KEY_ENTER_STATE, &buttons_val);
		   if (ret < 0)
			{
				log_e("GET_KEY_ENTER_STATE error!! %d", ret);
				return IO_KEY_ERROR ;
			}
		   if(buttons_val==IO_KEY_ON)
			   return IO_KEY_ON;
		   else
			   return IO_KEY_OFF ;
			break;
		case KEY_DOWN_TRG_NUMBER :
			ret = ioctl(dev_buttons_fd, GET_KEY_DOWN_STATE, &buttons_val);
		   if (ret < 0)
			{
				log_e("GET_KEY_DOWN_STATE error!! %d", ret);
				return IO_KEY_ERROR ;
			}
		   if(buttons_val==IO_KEY_ON)
			   return IO_KEY_ON;
		   else
			   return IO_KEY_OFF ;
			break;
		default:
			log_e("scan buttons error!!");
			return IO_KEY_ERROR ;
			break;
		}
	}else{
		return IO_KEY_ERROR ;
	}
}













