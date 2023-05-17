/*
 * water_alarm.c
 *
 *  Created on: 2023年2月16日
 *      Author: 好
 */
#define LOG_TAG    "water_alarm"

#include "../drive/water_alarm.h"

Water_Alarm_State_Cb  pfnWaterAlarmNotifyFun;
Water_Online_State_Cb pfnWaterOnlineNotifyFun ;

void water_init(void){
	dev_water_init();
	pfnWaterAlarmNotifyFun = NULL ;
	pfnWaterOnlineNotifyFun = NULL ;
}

/**
  * @brief      注册烟雾传感器检测动作改变时的通知回调函数
  *
  * @param[in]  eKey 指定按键, 取值为 @reg IoKeyType_e
  * @param[in]  pKeyFun 通知回调函数
  */

void Water_Alarm_Register(Get_Water_State_Typedef alarm_type, Water_Alarm_State_Cb pWaterAlarmFun){
    if (alarm_type < MAX_WATER_STATE_NUMBER)
    {
    	pfnWaterAlarmNotifyFun = pWaterAlarmFun;
    }
}

/**
  * @brief      注册烟雾传感器检测动作改变时的通知回调函数
  *
  * @param[in]  eKey 指定按键, 取值为 @reg IoKeyType_e
  * @param[in]  pKeyFun 通知回调函数
  */

void Water_Online_Register(Get_Water_State_Typedef online_type, Water_Online_State_Cb pWaterOnlineFun){
    if (online_type < MAX_WATER_STATE_NUMBER)
    {
    	pfnWaterOnlineNotifyFun = pWaterOnlineFun;
    }
}

/**
  * @brief      注销烟雾传感器检测动作改变时的通知回调函数
  *
  * @param[in]  eKey 指定按键, 取值为 @reg IoKeyType_e
  */

void Water_UnRegister(Get_Water_State_Typedef water_type){
    if (water_type < MAX_WATER_STATE_NUMBER)
    {
		switch (water_type) {
		case GET_WATER_ALARM_STATE_NUMBER:
			pfnWaterAlarmNotifyFun = NULL;
			break;
		case GET_WATER_ONLINE_STATE_NUMBER:
			pfnWaterOnlineNotifyFun = NULL;
			break;
		default:
			break;
		}
    }
}


void Water_loop_scan_even(void){
	static uint8_t old_water_alarm_state =1 ;
	uint8_t state_tmp = 1 ;

	state_tmp = get_water_state(GET_WATER_ONLINE_STATE_NUMBER);
	if(state_tmp == ON_LINE_STATE){
		state_tmp = get_water_state(GET_WATER_ALARM_STATE_NUMBER);
		if( old_water_alarm_state != state_tmp){
			old_water_alarm_state = state_tmp;
			pfnWaterAlarmNotifyFun((Get_Water_State_Typedef)GET_WATER_ALARM_STATE_NUMBER,state_tmp);
		}
	}else{
		if( old_water_alarm_state != state_tmp){
			old_water_alarm_state = state_tmp;
			log_d("GET_WATER_ONLINE_STATE_NUMBER TRG ");
			pfnWaterOnlineNotifyFun((Get_Water_State_Typedef)GET_WATER_ONLINE_STATE_NUMBER,state_tmp);
		}
	}
}


