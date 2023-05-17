/*
 * rtc.c
 *
 *  Created on: 2023年3月23日
 *      Author: 好
 */

#define LOG_TAG    "rtc"


#include "../drive/rtc.h"


static int rtc0_fd = -1 ;


int rtc_init(void){
	rtc0_fd = dev_rtc_init(RTC_NAME);
    if (rtc0_fd == -1) {
		return -1;
    }
	return 0 ;
}

int read_rtc_time(struct rtc_time *rtc_tm){
	int retval = 0 ;
    /* Read the RTC time/date */
    retval =  dev_read_rtc_time(rtc0_fd ,rtc_tm);
	return retval ;
}

int write_rtc_time(struct rtc_time *rtc_tm){
	int retval = 0 ;
    /* Read the RTC time/date */
    retval = dev_write_rtc_time(rtc0_fd ,rtc_tm);
	return retval ;
}


int read_sys_time(struct tm *time ){
	struct tm *t;

    struct timeval tv;
    struct timezone tz;

	gettimeofday( &tv, &tz ) ;
	t = localtime( &tv.tv_sec ) ;
	time->tm_year = t->tm_year;
	time->tm_mon = t->tm_mon;
	time->tm_mday = t->tm_mday;
	time->tm_wday = t->tm_wday;
	time->tm_hour = t->tm_hour;
	time->tm_min = t->tm_min;
	time->tm_sec = t->tm_sec;
	return 0 ;
}

int write_sys_time(struct tm *time ){

	struct rtc_time rtc_tm;
	struct tm _tm;
	struct timeval time_tv;
	time_t timep;

    _tm.tm_sec = time->tm_sec;
    _tm.tm_min = time->tm_min;
    _tm.tm_hour = time->tm_hour;
    _tm.tm_mday = time->tm_mday;
    _tm.tm_mon = time->tm_mon - 1;
    _tm.tm_year = time->tm_year - 1900;

    rtc_tm.tm_sec = time->tm_sec;
    rtc_tm.tm_min = time->tm_min;
    rtc_tm.tm_hour = time->tm_hour;
    rtc_tm.tm_mday = time->tm_mday;
    rtc_tm.tm_mon = time->tm_mon - 1;
    rtc_tm.tm_year = time->tm_year- 1900;

    if( write_rtc_time(&rtc_tm) < 0 ){
    	log_e("write_rtc_time error ");
    	 return -1;
    }

    timep = mktime(&_tm);
    time_tv.tv_sec = timep;
    time_tv.tv_usec = 0;
    if(settimeofday(&time_tv, (struct timezone *) 0) < 0)
       {
    	log_e("Set system datetime error!");
           return -1;
       }
	return 0 ;
}



