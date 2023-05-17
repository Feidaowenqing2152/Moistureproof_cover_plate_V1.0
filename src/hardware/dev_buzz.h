/*
 * dev_buzz.h
 *
 *  Created on: 2023年2月17日
 *      Author: 好
 */

#ifndef HARDWARE_DEV_BUZZ_H_
#define HARDWARE_DEV_BUZZ_H_


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

//按键枚举
typedef enum{
	BUZZ_OFF = 0 ,                         	/*!< (0)断开(无动作) */
	BUZZ_ON = !BUZZ_OFF,                     /*!< (1)闭合(有动作) */
}ControlBuzzState_t;


//按键枚举
typedef enum{
	BUZZ_BLINK_DISABLE = 0 ,                         	/*!< (0)断开(无动作) */
	BUZZ_BLINK_ENABLE = !BUZZ_BLINK_DISABLE,             /*!< (1)闭合(有动作) */
}ControlBuzzStateType_t;

//自定义的ioctl命令
#define DEV_BUZZ_TYPE 'b'                               //设备类型
#define SET_BUZZ_ACTION _IOW(DEV_BUZZ_TYPE, 0x1, int)   //设备操作：设置RLED
#define ENABLE_BUZZ_BLINK _IOW(DEV_BUZZ_TYPE, 0x2, int) //设备操作：使能/失能buzz闪烁
#define SET_BUZZ_FRQ _IOW(DEV_BUZZ_TYPE, 0x3, int)      //设备操作：设置频率
#define BUZZ_IOC_MAXNR 3

int dev_buzz_init(void);
void dev_control_buzz_state( ControlBuzzStateType_t buzz_type , ControlBuzzState_t buzz_state);
void dev_set_buzz_frq( int buzz_frq_ms);


#endif /* HARDWARE_DEV_BUZZ_H_ */
