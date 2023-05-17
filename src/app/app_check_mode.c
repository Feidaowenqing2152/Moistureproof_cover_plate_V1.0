/*
 * app_check_mode.c
 *
 *  Created on: 2023年2月17日
 *      Author: 好
 */
#define LOG_TAG    "app_check_mode"


#include "../app/app_check_mode.h"

static bool work_mode = WORK_MODE ;

static void check_mode_state_cb(CheckModeState_t state);

void app_check_mode_init(void){
	check_mode_init();
	Check_Mode_Register(check_mode_state_cb);
}


bool loop_scan_check_mode_sate_task(uint16_t scan_timer){
	if(check_time_arrive(SCAN_CHECK_MODE_STATE_TIME_NUMBER,scan_timer)){
		Check_Mode_loop_scan_even();
		clear_time_cnt(SCAN_CHECK_MODE_STATE_TIME_NUMBER);
	}
	return work_mode ;
}



static void check_mode_state_cb(CheckModeState_t state){
	if(state == FIX_MODE ){   //检修模式
		//dw_check_mode_state_var(1);
		work_mode = FIX_MODE ;
		log_d("this is fix mode trg.");
	}else{	                  //工作模式
		//dw_check_mode_state_var(0);
		work_mode = WORK_MODE ;
		log_d("this is work mode trg.");
	}
}

