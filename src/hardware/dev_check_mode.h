/*
 * dev_check_mode.h
 *
 *  Created on: 2023年2月16日
 *      Author: 好
 */

#ifndef HARDWARE_DEV_CHECK_MODE_H_
#define HARDWARE_DEV_CHECK_MODE_H_

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


//#define WORK_MODE 1 //工作模式或使能检测功能
//#define FIX_MODE 0  //检修模式或失能检测功能

//按键枚举
typedef enum{
	FIX_MODE = 0 ,                         //工作模式或使能检测功能
	WORK_MODE = !FIX_MODE,                 //检修模式或失能检测功能
}CheckModeState_t;

//自定义的ioctl命令
#define CHECK_MODE_TYPE 'c'                                             //设备类型 :工作模式检测
#define GET_CHECK_MODE_STATE _IOR(CHECK_MODE_TYPE, 0x1, int)            //设备操作：读I工作模式管脚状态
#define SET_CHECK_MODE_DEBOUNCING_TIMER _IOW(CHECK_MODE_TYPE, 0x2, int) //设置检测工作模式管脚消抖时间
#define ENABLE_CHECK_MODE_FUNCTION _IOW(CHECK_MODE_TYPE, 0x3, int)      //设置是否使能检测工作模式功能
#define CHECK_MODE_IOC_MAXNR 3

int dev_check_mode_init(void);
//设备操作：读工作模式管脚状态
uint8_t get_work_mode_state(void);


#endif /* HARDWARE_DEV_CHECK_MODE_H_ */
