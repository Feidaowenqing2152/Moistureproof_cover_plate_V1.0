/*
 * smoke_alarm.c
 *
 *  Created on: 2023年2月16日
 *      Author: 好
 */

#define LOG_TAG    "smoke_alarm"

#include "../drive/smoke_alarm.h"


Smoke_Alarm_State_Cb  pfnSmokeAlarmNotifyFun;
Smoke_Online_State_Cb pfnSmokeOnlineNotifyFun ;

void smoke_init(void){
	dev_smoke_init();
	pfnSmokeAlarmNotifyFun = NULL ;
	pfnSmokeOnlineNotifyFun = NULL ;
}

/**
  * @brief      注册烟雾传感器检测动作改变时的通知回调函数
  *
  * @param[in]  eKey 指定按键, 取值为 @reg IoKeyType_e
  * @param[in]  pKeyFun 通知回调函数
  */

void Smoke_Alarm_Register(Get_Smoke_State_Typedef alarm_type, Smoke_Alarm_State_Cb pSmokeAlarmFun){
    if (alarm_type < MAX_SMOKE_STATE_NUMBER)
    {
    	pfnSmokeAlarmNotifyFun = pSmokeAlarmFun;
    }
}

/**
  * @brief      注册烟雾传感器检测动作改变时的通知回调函数
  *
  * @param[in]  eKey 指定按键, 取值为 @reg IoKeyType_e
  * @param[in]  pKeyFun 通知回调函数
  */

void Smoke_Online_Register(Get_Smoke_State_Typedef online_type, Smoke_Online_State_Cb pSmokeOnlineFun){
    if (online_type < MAX_SMOKE_STATE_NUMBER)
    {
    	pfnSmokeOnlineNotifyFun = pSmokeOnlineFun;
    }
}

/**
  * @brief      注销烟雾传感器检测动作改变时的通知回调函数
  *
  * @param[in]  eKey 指定按键, 取值为 @reg IoKeyType_e
  */

void Smoke_UnRegister(Get_Smoke_State_Typedef alarm_type){
    if (alarm_type < MAX_SMOKE_STATE_NUMBER)
    {
       	switch (alarm_type) {
		case GET_SMOKE_ALARM_STATE_NUMBER:
			pfnSmokeAlarmNotifyFun = NULL;
			break;
		case GET_SMOKE_ONLINE_STATE_NUMBER:
			pfnSmokeOnlineNotifyFun = NULL;
			break;
		default:
			break;
		}
    }
}


void Smoke_loop_scan_even(void){
	static uint8_t old_smoke_alarm_state = 1 ;
	uint8_t state_tmp = 1 ;

	state_tmp = get_smoke_state(GET_SMOKE_ONLINE_STATE_NUMBER);
	if(state_tmp == ON_LINE_STATE){
		state_tmp = get_smoke_state(GET_SMOKE_ALARM_STATE_NUMBER);
		if( old_smoke_alarm_state != state_tmp){
			old_smoke_alarm_state = state_tmp;
			pfnSmokeAlarmNotifyFun((Get_Smoke_State_Typedef)GET_SMOKE_ALARM_STATE_NUMBER,state_tmp);
		}
	}else{
		if( old_smoke_alarm_state != state_tmp){
			old_smoke_alarm_state = state_tmp;
			pfnSmokeOnlineNotifyFun((Get_Smoke_State_Typedef)GET_SMOKE_ONLINE_STATE_NUMBER,state_tmp);
		}
	}
}




