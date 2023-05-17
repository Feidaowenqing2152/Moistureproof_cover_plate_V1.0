/*
 * motor.c
 *
 *  Created on: 2023年2月15日
 *      Author: 好
 */
#define LOG_TAG    "motor"

#include "../drive/motor.h"

Motor_Limit_State_Cb pfnMotorNotifyFun;

void motor_init(void){
	dev_motor_init(10);
	pfnMotorNotifyFun = NULL ;
}

/**
  * @brief      注册电机限位检测动作改变时的通知回调函数
  *
  * @param[in]  eKey 指定按键, 取值为 @reg IoKeyType_e
  * @param[in]  pKeyFun 通知回调函数
  */
void Motor_Register(Motor_Limit_Typedef eMotor_Number, Motor_Limit_State_Cb pMotorFun){
    if (eMotor_Number < MAX_LIMITTRG_NUMBER)
    {
    	pfnMotorNotifyFun = pMotorFun;
    }
}


/**
  * @brief      注销电机限位检测动作改变时的通知回调函数
  *
  * @param[in]  eKey 指定按键, 取值为 @reg IoKeyType_e
  */

void Motor_UnRegister(Motor_Limit_Typedef eMotor_Number){
    if (eMotor_Number < MAX_LIMITTRG_NUMBER)
    {
    	pfnMotorNotifyFun = NULL;
    }
}


void Motor_loop_scan_even(void){
	static uint8_t old_forword_limit_state =MOTOR_LIMIT_ERROR ;
	static uint8_t old_reverse_limit_state =MOTOR_LIMIT_ERROR;
	uint8_t limit_state_tmp = 0 ;

	limit_state_tmp = get_motor_limit_state(FORWORD_LIMITTRG_NUMBER);
	if( old_forword_limit_state != limit_state_tmp){
		old_forword_limit_state = limit_state_tmp;
		pfnMotorNotifyFun((Motor_Limit_Typedef)FORWORD_LIMITTRG_NUMBER,limit_state_tmp);
	}

	limit_state_tmp = get_motor_limit_state(REVERSE_LIMITTRG_NUMBER);
	if( old_reverse_limit_state != limit_state_tmp){
		old_reverse_limit_state = limit_state_tmp;
		pfnMotorNotifyFun((Motor_Limit_Typedef)REVERSE_LIMITTRG_NUMBER,limit_state_tmp);
	}
}


int get_motor_motion_status(void){
	int ret  = -1 ;
	ret = dev_get_motor_motion_status();
	return ret ;
}






