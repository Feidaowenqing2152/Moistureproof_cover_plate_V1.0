/*
 * dw_display_task.h
 *
 *  Created on: 2023年1月6日
 *      Author: 好
 */

#ifndef TASK_DW_DISPLAY_TASK_H_
#define TASK_DW_DISPLAY_TASK_H_

#include "../common.h"



#define REFERSH_DW_DISPLAY_TIME  1000  
#define SEND_GET_HUMITURE_CMD_TIMER  1000
#define CHECK_ETH_CONNECT_STATE_TIMER 1000
#define FAN_MOTOR_REFRESH_VELOCITY_TIMER 1000





void hmi_enter_main_page(void);
void create_dw_display_pthread_init(void);
void* dw_display_task(void *arg);
#endif /* TASK_DW_DISPLAY_TASK_H_ */
