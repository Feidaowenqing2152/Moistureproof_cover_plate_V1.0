/*
 * listen_rs485_masg_task.h
 *
 *  Created on: 2023年1月5日
 *      Author: 好
 */

#ifndef TASK_LISTEN_RS485_MASG_TASK_H_
#define TASK_LISTEN_RS485_MASG_TASK_H_

#include "../common.h"

#define RS485_READ_BUFFER_SIZE 256


void create_listen_rs485_masg_pthread_init(void);
void* listen_rs485_msg_task(void *arg);


#endif /* TASK_LISTEN_RS485_MASG_TASK_H_ */
