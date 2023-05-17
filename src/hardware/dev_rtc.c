/*
 * dev_rtc.c
 *
 *  Created on: 2023年1月4日
 *      Author: 好
 */
#define LOG_TAG    "dev_rtc"

#include "../hardware/dev_rtc.h"



int dev_rtc_init(char* rtc){
	int rtc0_fd = -1 ;
	rtc0_fd = open( rtc, O_RDONLY);
    if (rtc0_fd == -1) {
		perror(RTC_NAME);
		log_e("open  %s error!!",RTC_NAME);
		exit(EXIT_FAILURE);
		return -1;
    }
    log_d("open %s success",RTC_NAME);
	return rtc0_fd;
}

int dev_read_rtc_time(int rtc_fd,struct rtc_time *rtc0_tm){
	int retval = 0 ;
    /* Read the RTC time/date */
    retval = ioctl(rtc_fd, RTC_RD_TIME, rtc0_tm);
    if (retval == -1) {
		perror("rtc0 read error");
		log_e("rtc0 read error!!");
		close(rtc_fd);
		return -1;
    }
    //close(rtc_fd);
	return retval ;
}

int dev_write_rtc_time(int rtc_fd,struct rtc_time *rtc0_tm){
	int retval = 0 ;
    /* Write the RTC time/date */
    retval = ioctl(rtc_fd, RTC_SET_TIME, rtc0_tm);
    if (retval == -1) {
		perror("rtc0 write_ error");
		log_e("rtc0 write_ error!!");
		close(rtc_fd);
		return -1;
    }

	return retval ;
}



