/*
 * dev_fan_motor.c
 *
 *  Created on: 2023年2月15日
 *      Author: 好
 */
#define LOG_TAG    "dev_fan_motor"

#include "../hardware/dev_fan_motor.h"

#define DEV_NAME "dev_fan"                     // 设备名称
#define FAN_LED_DTS_COMPATIBLE "fan_pwm1,pwm1" /* 设备树节点匹配属性 compatible */
#define MAX_DUTY 100                           // 最大占空比
#define MIN_DUTY 0                             // 最小占空比

static int init_dev_fan_motor(const char *dev_name );
static int fan_motor_setting_sampling_time(int sampling_time);

static int dev_fan_motor_fd = -1 ;

int dev_fan_motor_init(int sampling_time){
	 struct fan_pwm_param fan_motor_config_t;
	 dev_fan_motor_fd= init_dev_fan_motor("/dev/dev_fan");
	 fan_motor_setting_sampling_time(sampling_time);       // 设置风机速度采样周期时间

	fan_motor_config_t.duty = 0;
	fan_motor_config_t.period_ns = 50000;
	fan_motor_config_t.velocity_sampling_period_S = sampling_time;
	fan_motor_config_t.polarity = FAN_POLARITY_NORMAL;
	fan_motor_config(&fan_motor_config_t);
	return dev_fan_motor_fd ;
}


void fan_motor_config(struct fan_pwm_param *fan_motor_config){
	if(fan_motor_config == NULL ){
		log_e("fan_motor_config intput error!!! \r");
		return ;
	}
	 struct fan_pwm_param dev_fan_motor_config={
			 .duty = 0 ,
			 .fan_velocity_rps = 0 ,
			 .period_ns = 0 ,
			 .polarity = 0 ,
			 .velocity_sampling_period_S = 0
	 };

	 dev_fan_motor_config.duty = fan_motor_config->duty ;
	 dev_fan_motor_config.period_ns = fan_motor_config->period_ns ;
	 dev_fan_motor_config.velocity_sampling_period_S = fan_motor_config->velocity_sampling_period_S;
	 dev_fan_motor_config.polarity=fan_motor_config->polarity;
	write(dev_fan_motor_fd, &dev_fan_motor_config, sizeof(dev_fan_motor_config));
}


void set_fan_enbale_an_disable(int fan_enable_flag){
	int ret = -1 ;
	int val  ;
	val = fan_enable_flag ;
	ret=ioctl(dev_fan_motor_fd, FAN_PWM_CMD_SET_ENABLE, &val);
   if (ret < 0)
	{
		log_w("FAN_PWM_CMD_SET_ENABLE error!! %d", ret);
	}
}

void fan_motor_set_rotate(int fan_motor_rotate){
	int ret = -1 ;
	int val  ;
	val = 1;
	ret=ioctl(dev_fan_motor_fd, FAN_PWM_CMD_SET_ENABLE, &val);
   if (ret < 0)
	{
		log_w("FAN_PWM_CMD_SET_ENABLE error!! %d", ret);
	}
   val = fan_motor_rotate ;
	ret=ioctl(dev_fan_motor_fd, FAN_PWM_CMD_SET_DUTY, &val);
  if (ret < 0)
	{
		log_w("FAN_PWM_CMD_SET_DUTY error!! %d", ret);
	}
}

int get_fan_motor_velocity_rpm(void){
	int fan_cnts = 0;
	int ret = -1 ;
	ret=ioctl(dev_fan_motor_fd, GET_FAN_CMD_VELOCITY, &fan_cnts);
   if (ret < 0)
	{
		log_w("GET_FAN_CMD_VELOCITY error!! %d", ret);
	}
   return fan_cnts;
}


static int init_dev_fan_motor(const char *dev_name ){
    int fd;
//    fd = open(tty_busy, O_RDWR|O_NONBLOCK);//O_RDWR|O_NONBLOCK
    fd = open(dev_name, O_RDWR | O_NONBLOCK); // | O_NONBLOCK
    if (fd < 0)
    {
		log_e("Initialize dev_fan_motor device %s failed!", dev_name);
		exit(EXIT_FAILURE);
    }
    log_d("open dev_fan_motor %s success!", dev_name);
    return fd ;
}

static int fan_motor_setting_sampling_time(int sampling_time){
	int ret = -1 ;
	ret = ioctl(dev_fan_motor_fd, SET_VELOCITY_SAMPLING_PERIOD, &sampling_time);
   if (ret < 0)
	{
		log_w("SET_VELOCITY_SAMPLING_PERIOD error!! %d", ret);
		 return 0;
	}
   return ret;
}




