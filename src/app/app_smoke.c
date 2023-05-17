/*
 * app_smoke.c
 *
 *  Created on: 2023年2月17日
 *      Author: 好
 */
#define LOG_TAG    "app_smoke"
#include "../app/app_smoke.h"

static void smoke_alarm_state_cb(Get_Smoke_State_Typedef State_Typedef ,uint8_t state);
static void smoke_online_state_cb(Get_Smoke_State_Typedef State_Typedef ,uint8_t state);

static struct smoke_transducer_paramer smoke_transducer_paramer_t ;

void app_smoke_init(void){
	smoke_init();
	Smoke_Alarm_Register(GET_SMOKE_ALARM_STATE_NUMBER,smoke_alarm_state_cb );
	Smoke_Online_Register(GET_SMOKE_ONLINE_STATE_NUMBER ,smoke_online_state_cb );
}


struct smoke_transducer_paramer loop_scan_smoke_sate_task(uint16_t scan_timer){
	if(check_time_arrive(SCAN_SMOKE_STATE_TIME_NUMBER,scan_timer)){
		Smoke_loop_scan_even();
		clear_time_cnt(SCAN_SMOKE_STATE_TIME_NUMBER);
	}
	return smoke_transducer_paramer_t ;
}


static void smoke_alarm_state_cb(Get_Smoke_State_Typedef State_Typedef ,uint8_t state){
	if(State_Typedef == GET_SMOKE_ALARM_STATE_NUMBER ){
		smoke_transducer_paramer_t.smoke_status = state ;
		if(state == ALARM_TRG_STATE ){   //触发
			dw_smoke_state_var(2);
			log_i("internal smoke trg alarm");
		}else{	//未触发
			dw_smoke_state_var(0);
			log_i("internal smoke git right");
		}
	}
}


static void smoke_online_state_cb(Get_Smoke_State_Typedef State_Typedef ,uint8_t state){
	if(State_Typedef == GET_SMOKE_ONLINE_STATE_NUMBER ){
		smoke_transducer_paramer_t.smoke_online = state ;
		if(state == ON_LINE_STATE ){   //在线
			log_w("internal smoke online");
		}else if(state == NOT_ONLINE_STSTE ){   //不在线
			dw_smoke_state_var(1);
			log_w("internal smoke offline");
		}else{  //错误
			log_e("smoke error trg.");
		}
	}
}
