/*
 * delay.c
 *
 *  Created on: 2022年12月30日
 *      Author: 好
 */



#include "../common/delay.h"


int get_sys_hours(void){
	struct tm *t;
	struct timeval tv;
	struct timezone tz;

	gettimeofday( &tv, &tz ) ;
	t = localtime( &tv.tv_sec ) ;
	return t->tm_hour;
}

int get_sys_min(void){
	struct tm *t;
	struct timeval tv;
	struct timezone tz;

	gettimeofday( &tv, &tz ) ;
	t = localtime( &tv.tv_sec ) ;
	return t->tm_min;
}

int get_sys_sec(void){
	struct tm *t;
	struct timeval tv;
	struct timezone tz;

	gettimeofday( &tv, &tz ) ;
	t = localtime( &tv.tv_sec ) ;
	return t->tm_sec;
}


 void seconds_sleep(unsigned seconds){
     struct timeval tv;
     tv.tv_sec=seconds;
     tv.tv_usec=0;
     int err;
     do{
        err=select(0,NULL,NULL,NULL,&tv);
     }while(err<0 && errno==EINTR);
 }

 void milliseconds_sleep(unsigned long mSec){
     struct timeval tv;
     tv.tv_sec=mSec/1000;
     tv.tv_usec=(mSec%1000)*1000;
     int err;
     do{
        err=select(0,NULL,NULL,NULL,&tv);
     }while(err<0 && errno==EINTR);
 }

 void microseconds_sleep(unsigned long uSec){
     struct timeval tv;
     tv.tv_sec=uSec/1000000;
     tv.tv_usec=uSec%1000000;
     int err;
     do{
         err=select(0,NULL,NULL,NULL,&tv);
     }while(err<0 && errno==EINTR);
 }
