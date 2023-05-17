/*
 * dev_smoke.h
 *
 *  Created on: 2023年2月16日
 *      Author: 好
 */

#ifndef HARDWARE_DEV_SMOKE_H_
#define HARDWARE_DEV_SMOKE_H_

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


#define ONLINE_STATE_ERROR 0 // 状态错误
#define ON_LINE_STATE 1      // 在线状态
#define NOT_ONLINE_STSTE 2   // 不在线状态

#define ALARM_TRG_STATE 0     // 传感器警报触发
#define ALARM_NOT_TRG_STATE 1 // 传感器警报未触发

// 自定义的ioctl命令
#define SENSOR_SMOKE_TYPE 's'                                              // 设备类型
#define GET_SMOKE_ALARM_STATE _IOR(SENSOR_SMOKE_TYPE, 0x1, int)            // 设备操作：传感器报警状态读取
#define GET_SMOKE_ONLINE_STATE _IOR(SENSOR_SMOKE_TYPE, 0x2, int)           // 设备操作：获取报警器在线状态
#define SET_CHECK_SMOKE_DEBOUNCING_TIMER _IOW(SENSOR_SMOKE_TYPE, 0x3, int) // 设置消抖时间
#define SMOKE_IOC_MAXNR 3


//按键枚举
typedef enum{
	GET_SMOKE_ALARM_STATE_NUMBER = 0,		//获取传感器报警状态
	GET_SMOKE_ONLINE_STATE_NUMBER ,		//获取传感器报警在线状态
	
MAX_SMOKE_STATE_NUMBER}Get_Smoke_State_Typedef;






int dev_smoke_init(void);
uint8_t get_smoke_state( Get_Smoke_State_Typedef Get_Smoke_State);





#endif /* HARDWARE_DEV_SMOKE_H_ */
