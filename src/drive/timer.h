/*
 * timer.h
 *
 *  Created on: 2023年2月10日
 *      Author: 好
 */

#ifndef DRIVE_TIMER_H_
#define DRIVE_TIMER_H_

#include "../common.h"

void time_reference ( int *timer_cnt);
void user_timer_init(void);
void add_system_time();
void clear_time_cnt(uint8_t time_number);
uint8_t check_time_arrive(uint8_t time_number, int time);

#endif /* DRIVE_TIMER_H_ */
