/*
 * dev_water.c
 *
 *  Created on: 2023年2月16日
 *      Author: 好
 */

#define LOG_TAG    "dev_water"
#include "../hardware/dev_water.h"

static int dev_water_fd = 0 ;

static int init_dev_water(const char *dev_name );
static int water_setting_shake_time(int smoke_shake_time);

int dev_water_init(void){
	 dev_water_fd= init_dev_water("/dev/dev_water_alarm");
	 water_setting_shake_time(10);       // 设备操作：设置电机运动限位检测消抖时间
	return dev_water_fd ;
}


uint8_t get_water_state( Get_Water_State_Typedef Get_Water_State){
	int ret = -1 ;
	int val = -1 ;

	if( MAX_WATER_STATE_NUMBER >Get_Water_State){
		switch(Get_Water_State){
		case GET_WATER_ALARM_STATE_NUMBER :
			ret = ioctl(dev_water_fd, GET_WATER_ALARM_STATE, &val);
		   if (ret < 0)
			{
				log_w("GET_WATER_ALARM_STATE error!! %d", ret);
				return ALARM_NOT_TRG_STATE ;
			}
		   if(val==ALARM_TRG_STATE)
			   return ALARM_TRG_STATE;
		   else
			   return ALARM_NOT_TRG_STATE ;
			break;
		case GET_WATER_ONLINE_STATE_NUMBER :
			ret = ioctl(dev_water_fd, GET_WATER_ONLINE_STATE, &val);
		   if (ret < 0)
			{
				log_w("GET_WATER_ONLINE_STATE error!! %d", ret);
				return ONLINE_STATE_ERROR ;
			}
		   if(val==ON_LINE_STATE)
			   return ON_LINE_STATE;
		   else
			   return NOT_ONLINE_STSTE ;
			break;
		default:
			log_w("scan water  error!!");
			return ONLINE_STATE_ERROR ;
			break;
		}
	}else{
		return ONLINE_STATE_ERROR ;
	}
}

static int init_dev_water(const char *dev_name ){
    int fd;
//    fd = open(tty_busy, O_RDWR|O_NONBLOCK);//O_RDWR|O_NONBLOCK
    fd = open(dev_name, O_RDWR);//O_RDWR|O_NONBLOCK
    if (fd < 0)
    {
		log_e("Initialize init_dev_water device %s failed!", dev_name);
		exit(EXIT_FAILURE);
    }
    log_d("open init_dev_water %s success!", dev_name);
    return fd ;
}

static int water_setting_shake_time(int smoke_shake_time){
	int ret = -1 ;
	ret = ioctl(dev_water_fd, SET_CHECK_WATER_DEBOUNCING_TIMER, &smoke_shake_time);
   if (ret < 0)
	{
		log_w("SET_CHECK_WATER_DEBOUNCING_TIMER error!! %d", ret);
	}
   return ret;
}
