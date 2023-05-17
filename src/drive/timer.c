/*
 * timer.c
 *
 *  Created on: 2023年2月10日
 *      Author: 好
 */

#include "../drive/timer.h"


static int user_timer_array[END_REGISTER_NUMBER] = {0};
static int timeout_control_array[END_REGISTER_NUMBER] = {0};
static int timer_time_cnt =0 ;

void time_reference ( int *timer_cnt){
     timer_time_cnt = *timer_cnt;
	    *timer_cnt = 0 ;
}

void user_timer_init(void){
	 uint8_t i = 0;
	for(i = 0; i < END_REGISTER_NUMBER; i++){
		user_timer_array[i] = 0;
		timeout_control_array[i] = 0;
	}
}

/*********************
function:
The system reference time is added to the user time array.
*********************/
void add_system_time(){
	 uint8_t i;
	 int temp = 0;

	temp = timer_time_cnt;
	timer_time_cnt = 0;
	for(i = 0; i < END_REGISTER_NUMBER; i++){
		if(user_timer_array[i] <= timeout_control_array[i])
		 user_timer_array[i] += temp;
	}
}


/*********************
	function:
		Clear the user time count.
*********************/
void clear_time_cnt(uint8_t time_number){
	if(END_REGISTER_NUMBER >= time_number)
		user_timer_array[time_number] = 0;
}



/*********************
	function:
		time if arrived
*********************/
uint8_t check_time_arrive(uint8_t time_number, int time){
	timeout_control_array[time_number] = time;

	if(time <= user_timer_array[time_number])
		return 1;
	else
		return 0;
}
