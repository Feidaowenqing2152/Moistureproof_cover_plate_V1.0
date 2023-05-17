/*
 * dev_motor.c
 *
 *  Created on: 2023年2月15日
 *      Author: 好
 */

#define LOG_TAG    "dev_motor"

#include "../hardware/dev_motor.h"

static int init_dev_motor(const char *dev_name );
static int motor_setting_shake_time(int motor_shake_time);

static int dev_motor_fd = -1 ;

int dev_motor_init(int motor_shake_time){
	 struct led_pwm_param motor_config_t = {0}; ;
	dev_motor_fd= init_dev_motor("/dev/dev_motor");
	motor_setting_shake_time(motor_shake_time);       // 设备操作：设置电机运动限位检测消抖时间

	motor_config_t.duty = 0;
	motor_config_t.period_ns = MOTOR_FRQ;
	motor_config_t.polarity = MOTOR_POLARITY_INVERSED;
	motor_config_t.motor_direction = MOTOR_STOP;
	motor_config(&motor_config_t);
	return dev_motor_fd ;
}

void motor_config(struct led_pwm_param *motor_config){
	if(motor_config != NULL){
		 struct led_pwm_param dev_motor_config ;
		dev_motor_config.duty = motor_config->duty ;
		dev_motor_config.period_ns = motor_config->period_ns ;
		dev_motor_config.polarity=motor_config->polarity;
		dev_motor_config.motor_direction=motor_config->motor_direction ;
		write(dev_motor_fd, &dev_motor_config, sizeof(dev_motor_config));
	}
}


int get_motor_limit_state( Motor_Limit_Typedef Motor_Limit){
	int ret = -1 ;
	int motor_val = -1 ;

	if( MAX_LIMITTRG_NUMBER >Motor_Limit){
		switch(Motor_Limit){
		case FORWORD_LIMITTRG_NUMBER :
			ret = ioctl(dev_motor_fd, GET_MOTOR_CMD_FORWORD_LIMIT, &motor_val);
		   if (ret < 0)
			{
				log_w("GET_MOTOR_CMD_FORWORD_LIMIT error!! %d", ret);
				return MOTOR_LIMIT_ERROR ;
			}
		   if(motor_val==MOTOR_LIMIT_TRG)
			   return MOTOR_LIMIT_TRG;
		   else
			   return MOTOR_LIMIT_NULL_TRG ;
			break;
		case REVERSE_LIMITTRG_NUMBER :
			ret = ioctl(dev_motor_fd, GET_MOTOR_CMD_REVERSE_LIMIT, &motor_val);
		   if (ret < 0)
			{
				log_w("GET_MOTOR_CMD_REVERSE_LIMIT error!! %d", ret);
				return MOTOR_LIMIT_ERROR ;
			}
		   if(motor_val==MOTOR_LIMIT_TRG)
			   return MOTOR_LIMIT_TRG;
		   else
			   return MOTOR_LIMIT_NULL_TRG ;
			break;
		default:
			log_w("scan motor limit error!!");
			return MOTOR_LIMIT_ERROR ;
			break;
		}
	}else{
		return MOTOR_LIMIT_ERROR ;
	}
}


int dev_get_motor_motion_status(void){
	int ret = -1 ;
	int motor_status = -1;
	ret = ioctl(dev_motor_fd, GET_MOTOR_CMD_MOTION_STATUS, &motor_status);
   if (ret < 0)
	{
		log_w("GET_MOTOR_CMD_MOTION_STATUS error!! %d", ret);
		return MOTOR_STATUS_UNKNOWN ;
	}
   return motor_status ;
}


static int init_dev_motor(const char *dev_name ){
    int fd;
//    fd = open(tty_busy, O_RDWR|O_NONBLOCK);//O_RDWR|O_NONBLOCK
    fd = open(dev_name, O_RDWR);//O_RDWR|O_NONBLOCK
    if (fd < 0)
    {
		log_e("Initialize dev_motor device %s failed!", dev_name);
		exit(EXIT_FAILURE);
    }
    log_d("open dev_motor %s success!", dev_name);
    return fd ;
}



static int motor_setting_shake_time(int motor_shake_time){
	int ret = -1 ;
	ret = ioctl(dev_motor_fd, SET_CHECK_LIMIT_SHAKE_TIMER, &motor_shake_time);
   if (ret < 0)
	{
		log_w("SET_CHECK_KEY_DEBOUNCING_TIMER error!! %d", ret);
	}
   return ret;
}



