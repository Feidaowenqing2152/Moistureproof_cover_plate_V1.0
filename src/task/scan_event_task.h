/*
 * scan_event_task.h
 *
 *  Created on: 2023年2月21日
 *      Author: 好
 */

#ifndef TASK_SCAN_EVENT_TASK_H_
#define TASK_SCAN_EVENT_TASK_H_


#include "../common.h"

#define SCAN_MENU_TASK_TIME    10 //菜单任务心跳时间
#define SACN_BUTTONS_TASK_TIME 10  //扫描获取按键状态
#define SCAN_MOTOR_LIMIT_STATE_TIME  100 //电机获取限位状态时间100ms

#define SCAN_SMOKE_STATE_TIME 1000  //烟雾报警状态扫描周期 1s
#define SCAN_WATER_STATE_TIME 1000  //水浸报警状态扫描周期 1s
#define SCAN_CHECK_MODE_STATE_TIME 100  //检测工作模式周期
#define GET_EX_HUMITURE_TIME       1000   //获取外界温湿度时间间隔
#define GET_Ex_SLEET_TIME          1000   //获取外界温雨雪时间间隔
#define GET_Ex_ILLUMINATION_TIME   1000   //获取外界光照强度时间间隔
#define GET_IN_HUMITURE_TIME       1000   //获取内部温湿度时间间隔

void create_get_scan_event_pthread_init(void);

void* scan_event_task(void *arg);


#endif /* TASK_SCAN_EVENT_TASK_H_ */
