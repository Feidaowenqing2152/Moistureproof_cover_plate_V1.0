/*
 * get_scan_event.c
 *
 *  Created on: 2023年2月17日
 *      Author: 好
 */
#define LOG_TAG    "scan_event_task"

#include "../task/scan_event_task.h"

extern uint8_t Transducer_Setting_Status_Flag  ;   //传感器在设置状态

struct moistureproof_state  moistureproof_state_type ;


uint8_t switch_mode = RUN_MODE_ERROR ;

void create_get_scan_event_pthread_init(void){
	//(1)timer thread
	pthread_t get_scan_event_id;
	transducer_modbus_init();
	user_key_even_init();
	app_motor_init();
	app_smoke_init();
	app_water_init();
	app_check_mode_init();


	int get_scan_event = pthread_create(&get_scan_event_id,NULL,scan_event_task,NULL);
	if(get_scan_event){
		log_e("scan_event_task thread created error !.");
		exit(EXIT_FAILURE);
	}
	log_d("scan_event_task thread created.");
}



void* scan_event_task(void *arg) {
	struct smoke_transducer_paramer smoke_transducer_paramer_t ;
	struct water_transducer_paramer water_transducer_paramer_t ;
	external_para_def external_para_def_t ;
	internal_para_def internal_para_def_t ;
	while(1){
		if(check_time_arrive(SACN_BUTTONS_TASK_TIME_NUMBER,SACN_BUTTONS_TASK_TIME)){
			buttons_loop_scan_even();
			clear_time_cnt(SACN_BUTTONS_TASK_TIME_NUMBER);
		}
		Eth_Scan_Loop_State(CHECK_ETH_CONNECT_STATE_TIMER);
		moistureproof_state_type = loop_scan_motor_limit_state(SCAN_MOTOR_LIMIT_STATE_TIME);
		if( (moistureproof_state_type.moistureproof_state_close_limit==MOTOR_LIMIT_TRG) && \
				(moistureproof_state_type.moistureproof_state_open_limit==MOTOR_LIMIT_NULL_TRG) ){
			deal_transducer_masg_t.board_status = true ;
		}else {
			deal_transducer_masg_t.board_status = false ;
		}

		smoke_transducer_paramer_t = loop_scan_smoke_sate_task(SCAN_WATER_STATE_TIME);
		deal_transducer_masg_t.smoke_state = smoke_transducer_paramer_t.smoke_status ;
		deal_transducer_masg_t.dev_online_state[smoke_transducer] = !smoke_transducer_paramer_t.smoke_online ;
		water_transducer_paramer_t = loop_scan_water_sate_task(SCAN_WATER_STATE_TIME);
		deal_transducer_masg_t.water_state = water_transducer_paramer_t.water_status ;
		deal_transducer_masg_t.dev_online_state[water_transducer] = !water_transducer_paramer_t.water_online ;
		switch_mode = loop_scan_check_mode_sate_task(SCAN_CHECK_MODE_STATE_TIME);
		if(!Transducer_Setting_Status_Flag){		//在设置状态
			read_saveenv_cjson_external_parameter(&external_para_def_t);
			read_saveenv_cjson_internal_parameter(&internal_para_def_t);
			send_get_transducer_cmd(external_para_def_t.ExternalIlluminationSampleRate*1000,external_para_def_t.ExternalSleetSampleRateDate*1000, \
									external_para_def_t.ExternalIlluminationSampleRate*1000,internal_para_def_t.InternalHumitureSampleRate*1000);
		}
	}
}







