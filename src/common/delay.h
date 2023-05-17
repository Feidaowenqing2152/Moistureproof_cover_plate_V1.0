/*
 * delay.h
 *
 *  Created on: 2022年12月30日
 *      Author: 好
 */

#ifndef COMMON_DELAY_H_
#define COMMON_DELAY_H_


//#include "../common.h"
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>
#include <getopt.h>
#include <unistd.h>
#include <time.h>
#include <sys/time.h>

int get_sys_hours(void);
int get_sys_min(void);
int get_sys_sec(void);

void seconds_sleep(unsigned seconds);
void milliseconds_sleep(unsigned long mSec);
void microseconds_sleep(unsigned long uSec);
#endif /* COMMON_DELAY_H_ */
