/*
 * dev_smoke.c
 *
 *  Created on: 2023年2月16日
 *      Author: 好
 */

#define LOG_TAG    "dev_smoke"

#include "../hardware/dev_smoke.h"

static int dev_smoke_fd = 0 ;

static int init_dev_smoke(const char *dev_name );
static int smoke_setting_shake_time(int smoke_shake_time);

int dev_smoke_init(void){
	 dev_smoke_fd= init_dev_smoke("/dev/dev_smoke_alarm");
	 smoke_setting_shake_time(10);       // 设备操作：设置电机运动限位检测消抖时间
	return dev_smoke_fd ;
}


uint8_t get_smoke_state( Get_Smoke_State_Typedef Get_Smoke_State){
	int ret = -1 ;
	int val = -1 ;

	if( MAX_SMOKE_STATE_NUMBER >Get_Smoke_State){
		switch(Get_Smoke_State){
		case GET_SMOKE_ALARM_STATE_NUMBER :
			ret = ioctl(dev_smoke_fd, GET_SMOKE_ALARM_STATE, &val);
		   if (ret < 0)
			{
				log_w("GET_SMOKE_ALARM_STATE error!! %d", ret);
				return ALARM_NOT_TRG_STATE ;
			}
		   if(val==ALARM_TRG_STATE)
			   return ALARM_TRG_STATE;
		   else
			   return ALARM_NOT_TRG_STATE ;
			break;
		case GET_SMOKE_ONLINE_STATE_NUMBER :
			ret = ioctl(dev_smoke_fd, GET_SMOKE_ONLINE_STATE, &val);
		   if (ret < 0)
			{
				log_w("GET_SMOKE_ONLINE_STATE error!! %d", ret);
				return ONLINE_STATE_ERROR ;
			}
		   if(val==ON_LINE_STATE)
			   return ON_LINE_STATE;
		   else
			   return NOT_ONLINE_STSTE ;
			break;
		default:
			log_w("scan smoke  error!!");
			return ONLINE_STATE_ERROR ;
			break;
		}
	}else{
		return ONLINE_STATE_ERROR ;
	}
}

static int init_dev_smoke(const char *dev_name ){
    int fd;
//    fd = open(tty_busy, O_RDWR|O_NONBLOCK);//O_RDWR|O_NONBLOCK
    fd = open(dev_name, O_RDWR);//O_RDWR|O_NONBLOCK
    if (fd < 0)
    {
		log_e("Initialize dev_motor device %s failed!", dev_name);
		exit(EXIT_FAILURE);
    }
    log_d("open dev_smoke %s success!", dev_name);
    return fd ;
}

static int smoke_setting_shake_time(int smoke_shake_time){
	int ret = -1 ;
	ret = ioctl(dev_smoke_fd, SET_CHECK_SMOKE_DEBOUNCING_TIMER, &smoke_shake_time);
   if (ret < 0)
	{
		log_w("SET_CHECK_SMOKE_DEBOUNCING_TIMER error!! %d", ret);
	}
   return ret;
}


