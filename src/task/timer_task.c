/*
 * timer_task.c
 *
 *  Created on: 2023年1月4日
 *      Author: 好
 */
#define LOG_TAG    "timer_task"

#include "../task/timer_task.h"


static system_para_def timer_system_t ;

void create_my_timer_pthread_init(void){
	//(1)timer thread
	pthread_t timer_id;
	rtc_init();
	read_saveenv_cjson_system_parameter( &timer_system_t);
	dw_cumulative_time(timer_system_t.CumulativeRunningTime);
	int ret_timer = pthread_create(&timer_id,NULL,my_timer,NULL);
	if(ret_timer){
		log_e("timer thread created error .");
		exit(EXIT_FAILURE);
	}
	log_d("timer thread created.");
}


void* my_timer(void *arg) {
	static int timer_ref = 0 ;
	static uint16_t min_ref = 0 ;
	user_timer_init();
	while (1) {
		milliseconds_sleep(1);
		timer_ref++;
		time_reference(&timer_ref);
		add_system_time();

		if(check_time_arrive(SYSTEM_RUNNING_CUMULATIVE_TIMER_NUMBER,SYSTEM_RUNNING_CUMULATIVE_TIMER)){
			min_ref ++ ;
			if(min_ref >=60){
				min_ref = 0 ;
				timer_system_t.CumulativeRunningTime ++ ;
				if(timer_system_t.CumulativeRunningTime >9999)
					timer_system_t.CumulativeRunningTime = 9999 ;
				dw_cumulative_time(timer_system_t.CumulativeRunningTime);
				systemparaPoint_amend_config("CumulativeRunningTime",timer_system_t.CumulativeRunningTime);
			}
			clear_time_cnt(SYSTEM_RUNNING_CUMULATIVE_TIMER_NUMBER);
		}
	}
}



