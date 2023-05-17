/*
 * check_mode.c
 *
 *  Created on: 2023年2月17日
 *      Author: 好
 */
#define LOG_TAG    "check_mode"

#include "../drive/check_mode.h"

Check_Mode_State_Cb   pfnCheckModeNotifyFun;



void check_mode_init(void){
	dev_check_mode_init();
	pfnCheckModeNotifyFun = NULL ;
}


/**
  * @brief      注册工作模式检测动作改变时的通知回调函数
  *
  * @param[in]  eKey 指定按键, 取值为 @reg IoKeyType_e
  * @param[in]  pKeyFun 通知回调函数
  */

void Check_Mode_Register(Check_Mode_State_Cb pCheckModeFun){
    	pfnCheckModeNotifyFun = pCheckModeFun;
}

/**
  * @brief      注销工作模式检测动作改变时的通知回调函数
  *
  * @param[in]  eKey 指定按键, 取值为 @reg IoKeyType_e
  */

void Check_Mode_UnRegister(void){
	pfnCheckModeNotifyFun = NULL ;
}



void Check_Mode_loop_scan_even(void){
	static uint8_t old_mode_state = 3 ;
	uint8_t state_tmp = 0 ;
	state_tmp =get_work_mode_state();
	if( old_mode_state != state_tmp){
		old_mode_state = state_tmp;
		pfnCheckModeNotifyFun(state_tmp);
	}

}







