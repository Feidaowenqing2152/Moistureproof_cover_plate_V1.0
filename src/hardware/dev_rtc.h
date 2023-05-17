/*
 * dev_rtc.h
 *
 *  Created on: 2023年1月4日
 *      Author: 好
 */

#ifndef HARDWARE_DEV_RTC_H_
#define HARDWARE_DEV_RTC_H_



#include "../common.h"



//typedef struct rtc_time rtc_tm;

int dev_rtc_init(char* rtc);
int dev_read_rtc_time(int rtc_fd,struct rtc_time *rtc0_tm);
int dev_write_rtc_time(int rtc_fd,struct rtc_time *rtc0_tm);

#endif /* HARDWARE_DEV_RTC_H_ */
