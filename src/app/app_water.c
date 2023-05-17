/*
 * app_water.c
 *
 *  Created on: 2023年2月17日
 *      Author: 好
 */

#define LOG_TAG    "app_water"

#include "../app/app_water.h"

static struct water_transducer_paramer water_transducer_paramer_t ;

static void water_alarm_state_cb(Get_Water_State_Typedef State_Typedef ,uint8_t state);
static void water_online_state_cb(Get_Water_State_Typedef State_Typedef ,uint8_t state);

void app_water_init(void){
	water_init();
	Water_Alarm_Register(GET_WATER_ALARM_STATE_NUMBER,water_alarm_state_cb );
	Water_Online_Register(GET_WATER_ONLINE_STATE_NUMBER ,water_online_state_cb );

}


struct water_transducer_paramer loop_scan_water_sate_task(uint16_t scan_timer){
	if(check_time_arrive(SCAN_WATER_STATE_TIME_NUMBER,scan_timer)){
		Water_loop_scan_even();
		clear_time_cnt(SCAN_WATER_STATE_TIME_NUMBER);
	}
	return water_transducer_paramer_t ;
}


static void water_alarm_state_cb(Get_Water_State_Typedef State_Typedef ,uint8_t state){
	if(State_Typedef == GET_WATER_ALARM_STATE_NUMBER ){
		water_transducer_paramer_t.water_status = state ;
		if(state == ALARM_TRG_STATE ){   //触发
			dw_water_state_var(2);
			log_i("internal water trg alarm");
		}else{	//未触发
			dw_water_state_var(0);
			log_i("internal water git right");
		}
	}

}


static void water_online_state_cb(Get_Water_State_Typedef State_Typedef ,uint8_t state){
	if(State_Typedef == GET_WATER_ONLINE_STATE_NUMBER ){
		water_transducer_paramer_t.water_online = state ;
		if(state == ON_LINE_STATE ){   //在线
			log_w("internal water online");
		}else if(state == NOT_ONLINE_STSTE ){   //不在线
			dw_water_state_var(1);
			log_w("internal water offline");
		}else{  //错误
			log_e("water error trg.");
		}
	}
}


