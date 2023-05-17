/*
 * rtc.h
 *
 *  Created on: 2023年3月23日
 *      Author: 好
 */

#ifndef DRIVE_RTC_H_
#define DRIVE_RTC_H_

#include "../common.h"

#define RTC_NAME "/dev/rtc0"

int rtc_init(void);
int read_rtc_time(struct rtc_time *rtc_tm);
int write_rtc_time(struct rtc_time *rtc_tm);
int read_sys_time(struct tm *time );
int write_sys_time(struct tm *time );

#endif /* DRIVE_RTC_H_ */
