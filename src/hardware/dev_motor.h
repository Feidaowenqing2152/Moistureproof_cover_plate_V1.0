/*
 * dev_motor.h
 *
 *  Created on: 2023年2月15日
 *      Author: 好
 */

#ifndef HARDWARE_DEV_MOTOR_H_
#define HARDWARE_DEV_MOTOR_H_

//#include "../common.h"
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

#define DEV_NAME "dev_motor"                    // 设备名称
#define FAN_LED_DTS_COMPATIBLE "motor-pwm,pwm3" /* 设备树节点匹配属性 compatible */
#define MAX_DUTY 100                            // 最大占空比
#define MIN_DUTY 0                              // 最小占空比
#define MOTOR_FRQ 40000                         // 25KHZ

typedef enum
{
    MOTOR_POLARITY_INVERSED = 1,                      // 翻转极性
    MOTOR_POLARITY_NORMAL = !MOTOR_POLARITY_INVERSED, // 正常极性
} Motor_Polarity;

typedef enum
{
    MOTOR_STOP = 0, // 电机立刻停止
    MOTOR_FORWORD,  // 前进
    MOTOR_RESERSE,  // 后退
} Control_Motor_Cmd;

typedef enum
{
    MOTOR_STATUS_UNKNOWN = 0, // 电机运动状态未知
    MOTOR_MOVING_STATUS,      // 电机正在运动状态
    MOTOR_STOP_STATUS,        // 电机停止状态
} Motor_Status;

struct led_pwm_param
{
    int duty;            // 占空比
    int period_ns;       // 周期
    int polarity;        // PWM极性
    int motor_direction; // 运动方向   0：停止 1：前进 2：后退
};

// 自定义的ioctl命令
#define MOTOR_TYPE 'm'                                         // 设备类型
#define MOTOR_CMD_SET_VELOCITY _IOW(MOTOR_TYPE, 0x1, int)      // 设备操作：设置电机运动速度
#define MOTOR_CMD_SET_MOTOR_DIR _IOW(MOTOR_TYPE, 0x2, int)     // 设备操作：设置电机运动方向
#define MOTOR_CMD_SET_PERIOD _IOW(MOTOR_TYPE, 0x3, int)        // 设备操作：设置风机PWM频率
#define MOTOR_PWM_CMD_SET_BOTH _IOW(MOTOR_TYPE, 0x4, int)      // 设备操作：设置风机PWM极性
#define SET_CHECK_LIMIT_SHAKE_TIMER _IOW(MOTOR_TYPE, 0x5, int) // 设备操作：设置电机运动限位检测消抖时间
#define GET_MOTOR_CMD_FORWORD_LIMIT _IOR(MOTOR_TYPE, 0x6, int) // 设备操作：读前进限位状态
#define GET_MOTOR_CMD_REVERSE_LIMIT _IOR(MOTOR_TYPE, 0x7, int) // 设备操作：读后退限位状态
#define GET_MOTOR_CMD_MOTION_STATUS _IOR(MOTOR_TYPE, 0x8, int) // 设备操作：电机运动状态
#define MOTORIOC_MAXNR 8

//按键枚举
typedef enum{
	FORWORD_LIMITTRG_NUMBER = 0,		//前进限位编号
	REVERSE_LIMITTRG_NUMBER ,			//后退限位编号
	
MAX_LIMITTRG_NUMBER}Motor_Limit_Typedef;

//按键枚举
typedef enum{
	MOTOR_LIMIT_NULL_TRG = 1,                         	/*!< (0)断开(无动作) */
	MOTOR_LIMIT_TRG = !MOTOR_LIMIT_NULL_TRG,            /*!< (1)闭合(有动作) */
	MOTOR_LIMIT_ERROR = 2							/*!< 按键状态获取错误 */
}Check_Motor_Limit_State;


int dev_motor_init(int motor_shake_time);
void motor_config(struct led_pwm_param *motor_config);
int get_motor_limit_state( Motor_Limit_Typedef Motor_Limit);
int dev_get_motor_motion_status(void);


#endif /* HARDWARE_DEV_MOTOR_H_ */
