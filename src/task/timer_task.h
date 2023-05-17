/*
 * timer_task.h
 *
 *  Created on: 2022��6��15��
 *      Author: ��
 */

#ifndef TASK_TIMER_TASK_H_
#define TASK_TIMER_TASK_H_

#include "../common.h"

#define RUN_PRINTF_TIMER_TASK_TIMER 10000 //500msanimation
#define SYSTEM_RUNNING_CUMULATIVE_TIMER 60000   //1min

enum user_timer_register{
	REFERSH_DW_DISPLAY_TIME_NUMBER ,         /* 刷新迪文显示时间 */
	SEND_GET_TRANSDUCER_CMD_TIMER_NUMBER,     /* 发送温湿度获取命令时间编号 */
	CHECK_ETH_CONNECT_STATE_TIMER_NUMBER,   /* 检测网口状态时间编号 */
	KEY_TRIGGER_TIMER_NUMBER ,       		/* 按键消抖时间编号 */
	KEY_LONG_PRESS_TIME_NUMBER ,     		/* 按键长按时间阀值时间编号 */
	SACN_BUTTONS_TASK_TIME_NUMBER ,        /*   扫描按键状态任务时间编号*/
	SCAN_MENU_TASK_TIME_NUMBER,            /*  扫描菜单任务时间编号*/
	MOISTUREPROOF_ANIMATION_TIMER_NUMBER ,  /*  盖板每帧动画时间编号*/
	FAN_MOTOR_REFRESH_VELOCITY_TIMER_NUMBER , /*  风机相关图标刷新时间编号*/
	SCAN_MOTOR_LIMIT_STATE_TIME_NUMBER,      /*  电机扫描获取限位状态时间编号*/
	SCAN_SMOKE_STATE_TIME_NUMBER,			 /*  烟雾报警状态扫描时间编号*/
	SCAN_WATER_STATE_TIME_NUMBER,			 /*  水浸报警状态扫描时间编号*/
	SCAN_CHECK_MODE_STATE_TIME_NUMBER,		 /*  工作模式状态扫描时间编号*/
	CHECK_EX_HUMITURE_ONLINE_TIMEOUT_TIMER_NUMBER ,   /*  检测外界温湿度不在线超时时间编号*/
	CHECK_IN_HUMITURE_ONLINE_TIMEOUT_TIMER_NUMBER ,   /*  检测外界温湿度不在线超时时间编号*/
	CHECK_ILLUMINATION_ONLINE_TIMEOUT_TIMER_NUMBER,	 /*   光照强度不在线超时时间编号*/
	CHECK_SLEET_ONLINE_TIMEOUT_TIMER_NUMBER ,   	 /*   雨雪不在线超时时间编号*/
	CLOSE_MOTOR_DELAY_T1_TIMER_NUMBER ,              /*   延时关闭盖板T1时间编号*/
	CLOSE_MOTOR_DELAY_T2_TIMER_NUMBER ,              /*   延时关闭盖板T2时间编号*/
	CLOSE_MOTOR_DELAY_T3_TIMER_NUMBER ,              /*   延时关闭盖板T3时间编号*/
	REMOTE_TEST_MOTOR_T4_TIMER_NUMBER ,              /*   远程测试电机动作T4时间编号*/
	SHOW_MODE_RGB_LED_BLINK_TIMER_NUMBER , 			 /*   显示工作状态RGB灯闪烁时间编号*/
	AUTO_EXIT_SETS_PAGE_TO_MAIN_PAGE_TIMER_NUMBER ,   /* 自动退出设置页面到主页时间编号*/
	SYSTEM_RUNNING_CUMULATIVE_TIMER_NUMBER ,         /* 系统累计运行时间基准1分钟编号*/
	AUTO_EXTINGUISH_DISPLAY_TIMER_NUMBER ,  		/* 熄屏时间编号编号*/
	SCAN_DEV_PROPERT_POST_TIMER_NUMBER ,			/* MQTT扫描设备属性(温度、湿度、风机速度等)间隔时间编号*/
	SCAN_DEV_EVENT_POST_TIMER_NUMBER ,				/* MQTT扫描设备事件(在线情况、异常情况事件)间隔时间编号*/

END_REGISTER_NUMBER};



void create_my_timer_pthread_init(void);

void* my_timer(void*arg);


#endif /* TASK_TIMER_TASK_H_ */
