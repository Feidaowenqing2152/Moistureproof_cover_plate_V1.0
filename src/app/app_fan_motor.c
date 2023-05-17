/*
 * app_fan_motor.c
 *
 *  Created on: 2023年2月15日
 *      Author: 好
 */
#define LOG_TAG    "app_fan_motor"

#include "../app/app_fan_motor.h"



void app_fna_motor_init(void){

	dev_fan_motor_init(FAN_SAMPLING_TIMER);
	set_fan_enbale_an_disable(0); 		    //设置风机失能
	dw_fan_motor_animation_state_var(0);   //停止风机动画
}



void Control_Fna_Motor(int duty ){
	if(duty == 0 ){
		dw_fan_motor_animation_state_var(0);   //停止风机动画
	}else{
		dw_fan_motor_animation_state_var(1);   //停止风机动画
	}
	fan_motor_set_rotate(duty);
}


int Show_Fan_Motor_Velocity_Date_Task(uint8_t refresh_flag,uint16_t refresh_time){
	 int fan_rpm_velocity = 0 ;

	if(check_time_arrive(FAN_MOTOR_REFRESH_VELOCITY_TIMER_NUMBER,refresh_time)){
		if(refresh_flag){
			fan_rpm_velocity =(int) ((int)(FAN_VERLOCITY_MULTIPLE_RPM))*get_fan_motor_velocity_rpm();
			if(fan_rpm_velocity>=9999){
				fan_rpm_velocity =9999;
			}else if(fan_rpm_velocity<=0){
				fan_rpm_velocity = 0  ;
			}else;
			dw_fan_motor_rotate_data_var(fan_rpm_velocity);
		}
		clear_time_cnt(FAN_MOTOR_REFRESH_VELOCITY_TIMER_NUMBER);
	}
	return fan_rpm_velocity ;
}
