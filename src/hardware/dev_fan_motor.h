/*
 * dev_fan_motor.h
 *
 *  Created on: 2023年2月15日
 *      Author: 好
 */

#ifndef HARDWARE_DEV_FAN_MOTOR_H_
#define HARDWARE_DEV_FAN_MOTOR_H_

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

#include <elog.h>

#define FAN_MOTOR_FRQ 50000                    // 风机频率  // 20KHZ

struct fan_pwm_param
{
    int duty;                       // 占空比
    int period_ns;                  // 周期
    int velocity_sampling_period_S; // 速度采样周期
    int fan_velocity_rps;           // 速度
    int polarity;                   // PWM极性
    // int sampling_reriod_timer_enable; // 速度采样时钟使能/失能
};

typedef enum
{
    FAN_POLARITY_INVERSED = 0,                    // 翻转极性
    FAN_POLARITY_NORMAL = !FAN_POLARITY_INVERSED, // 正常极性
} Fan_Motor_Polarity;

// 自定义的ioctl命令
#define FAN_TYPE 'f'                                                  // 设备类型
#define FAN_PWM_CMD_SET_DUTY _IOW(FAN_TYPE, 0x1, int)                 // 设备操作：设置风机速度占空比
#define FAN_PWM_CMD_SET_PERIOD _IOW(FAN_TYPE, 0x2, int)               // 设备操作：设置风机PWM频率
#define FAN_PWM_CMD_SET_BOTH _IOW(FAN_TYPE, 0x3, int)                 // 设备操作：设置风机PWM极性
#define FAN_PWM_CMD_SET_ENABLE _IOW(FAN_TYPE, 0x4, int)               // 设备操作：设置风机PWM使能/失能
#define SET_VELOCITY_SAMPLING_PERIOD _IOW(FAN_TYPE, 0x5, int)         // 设备操作：设置风机速度采样周期时间
#define GET_FAN_CMD_VELOCITY _IOR(FAN_TYPE, 0x6, int)                 // 设备操作：读风机速度
#define SET_FAN_SAMPLING_PERIOD_TIMER_ENABLE _IOW(FAN_TYPE, 0x7, int) // 设备操作：设置速度采样时钟使能/失能
#define FAN_IOC_MAXNR 7

int dev_fan_motor_init(int sampling_time);
void fan_motor_config(struct fan_pwm_param *fan_motor_config);
void set_fan_enbale_an_disable(int fan_enable_flag);
void fan_motor_set_rotate(int fan_motor_rotate);
int get_fan_motor_velocity_rpm(void);

#endif /* HARDWARE_DEV_FAN_MOTOR_H_ */
