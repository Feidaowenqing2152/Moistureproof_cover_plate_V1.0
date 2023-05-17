/*
 * dev_buttons.h
 *
 *  Created on: 2023年2月10日
 *      Author: 好
 */

#ifndef HARDWARE_DEV_BUTTONS_H_
#define HARDWARE_DEV_BUTTONS_H_

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
#include <sys/stat.h>
#include <sys/time.h>
#include <sys/select.h>
#include <sys/socket.h>
#include <time.h>
#include <stdbool.h>
#include <pthread.h>
#include <errno.h>
#include <net/if.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <signal.h>

#include <elog.h>

//按键枚举
typedef enum{
	KEY_NULL_NUMBER = 0,		//空按键
	KEY_UP_TRG_NUMBER ,			//上按键编号
	KEY_ENTER_TRG_NUMBER,		//确定按键编号
	KEY_DOWN_TRG_NUMBER,		//下按键编号

MAX_KEY_NUMBER}key_Input_Number_Typedef;


//按键枚举
typedef enum{
    IO_KEY_OFF = 1,                         	/*!< (0)断开(无动作) */
    IO_KEY_ON = !IO_KEY_OFF,                     /*!< (1)闭合(有动作) */
	IO_KEY_ERROR = 2							/*!< 按键状态获取错误 */
}IoKeyState_e;

// 自定义的ioctl命令
#define BUTTONS_TYPE 'b'                                          // 设备类型
#define GET_KEY_DOWN_STATE _IOR(BUTTONS_TYPE, 1, int)               // 设备操作：获取下键状态
#define GET_KEY_ENTER_STATE _IOR(BUTTONS_TYPE, 2, int)            // 设备操作：获取确定键状态
#define GET_KEY_UP_STATE _IOR(BUTTONS_TYPE, 3, int)             // 设备操作：获取上键状态
#define SET_CHECK_KEY_DEBOUNCING_TIMER _IOW(BUTTONS_TYPE, 4, int) // 设置消抖时间
#define BUTTONS_IOC_MAXNR 4



int init_buttons(int shake_time);
uint8_t get_buttons_state( key_Input_Number_Typedef buttons_number);

#endif /* HARDWARE_DEV_BUTTONS_H_ */
