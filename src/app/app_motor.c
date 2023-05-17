/*
 * app_motor.c
 *
 *  Created on: 2023年2月15日
 *      Author: 好
 */
#define LOG_TAG    "app_motor"

#include "../app/app_motor.h"

static struct led_pwm_param dev_motor_config;

static struct moistureproof_state  moistureproof_state_t ;

static void MotorLimit_Change_cb(Motor_Limit_Typedef Motor_Limit_Number ,Check_Motor_Limit_State Check_Motor_Limit_t);



void app_motor_init(void){
	moistureproof_state_t.moistureproof_state_close_limit=MOTOR_LIMIT_ERROR;
	moistureproof_state_t.moistureproof_state_open_limit=MOTOR_LIMIT_ERROR;
	default_dw_show_moistureproof_open_state();
	default_dw_show_moistureproof_close_state();
	motor_init();
	Motor_Register(FORWORD_LIMITTRG_NUMBER ,MotorLimit_Change_cb);
	Motor_Register(REVERSE_LIMITTRG_NUMBER ,MotorLimit_Change_cb);

	if( get_motor_limit_state(REVERSE_LIMITTRG_NUMBER) != 0  ){  //未完全闭合
		dw_moistureproof_state(0);
	}else{
		dw_moistureproof_state(24);
	}
}

int motor_reset(void){
	static uint8_t motor_reset_flag = 0 ;
	if( get_motor_limit_state(FORWORD_LIMITTRG_NUMBER) !=MOTOR_LIMIT_TRG){
		if(motor_reset_flag == 0 ){
			dev_motor_config.duty = 100 ;
			dev_motor_config.motor_direction = MOTOR_FORWORD;
			dev_motor_config.period_ns = MOTOR_FRQ;
			dev_motor_config.polarity = MOTOR_POLARITY_INVERSED;
			motor_config(&dev_motor_config);
			motor_reset_flag = 1 ;
		}
		return 0 ;
	}else{
		log_d(" motor_reset over ");
		return 1 ;
	}
}

void Motor_Move(uint8_t move_dir ,int duty ){
	//Moistureproof_state_animation(type_moistureproof_state_t,move_dir);
	dev_motor_config.duty = duty ;
	dev_motor_config.period_ns = MOTOR_FRQ ;
	dev_motor_config.polarity=MOTOR_POLARITY_INVERSED;
	dev_motor_config.motor_direction=move_dir ;
	motor_config(&dev_motor_config);
}

struct moistureproof_state loop_scan_motor_limit_state(uint16_t scan_timer){
	if(check_time_arrive(SCAN_MOTOR_LIMIT_STATE_TIME_NUMBER,scan_timer)){
		Motor_loop_scan_even();
		clear_time_cnt(SCAN_MOTOR_LIMIT_STATE_TIME_NUMBER);
	}
	return moistureproof_state_t ;
}

void Moistureproof_state_animation_Task(uint8_t refresh_flag){

	uint32_t all_animation_frame_timer = 0 ;
	 static uint16_t animation_frame_timer = 0 ;
	 static int old_motor_dir =0 ;
	 if(old_motor_dir != dev_motor_config.motor_direction){
		 if(dev_motor_config.motor_direction!= MOTOR_STOP){
			all_animation_frame_timer = 1000/dev_motor_config.duty +5;
			all_animation_frame_timer /= 10;
			all_animation_frame_timer *= MAX_DUTY_ALL_FRAME_TIME;
			all_animation_frame_timer *= 10 ;
			animation_frame_timer = all_animation_frame_timer/24 +5;
			animation_frame_timer /= 10;
		 }
		 if( (moistureproof_state_t.moistureproof_state_close_limit != MOTOR_LIMIT_TRG) &&(moistureproof_state_t.moistureproof_state_close_limit != MOTOR_LIMIT_ERROR) ){
			 dw_moistureproof_state_var(1);     //开启
		 }else if(moistureproof_state_t.moistureproof_state_close_limit != MOTOR_LIMIT_ERROR) {
			 dw_moistureproof_state_var(0);   //关闭
		 }else;
		 old_motor_dir = dev_motor_config.motor_direction ;
	 }

	if(dev_motor_config.motor_direction == MOTOR_FORWORD ){
		dw_show_moistureproof_close_state(animation_frame_timer,refresh_flag);
		if( moistureproof_state_t.moistureproof_state_close_limit == MOTOR_LIMIT_TRG ){
			dw_moistureproof_state(0);
			default_dw_show_moistureproof_open_state();
			dev_motor_config.duty = 0 ;
			dev_motor_config.motor_direction = MOTOR_STOP;
		}
	}else if(dev_motor_config.motor_direction == MOTOR_RESERSE ){
		dw_show_moistureproof_open_state(animation_frame_timer,refresh_flag);
		if( moistureproof_state_t.moistureproof_state_open_limit == MOTOR_LIMIT_TRG ){
			//motor_config(&dev_motor_config);
			dw_moistureproof_state(24);
			default_dw_show_moistureproof_close_state();
			dev_motor_config.duty = 0 ;
			dev_motor_config.motor_direction = MOTOR_STOP;
		}
	}else{
	}
}

static void MotorLimit_Change_cb(Motor_Limit_Typedef Motor_Limit_Number ,Check_Motor_Limit_State Check_Motor_Limit_t){
	if(Motor_Limit_Number == FORWORD_LIMITTRG_NUMBER){
		moistureproof_state_t.moistureproof_state_close_limit = Check_Motor_Limit_t;
	}else if(Motor_Limit_Number == REVERSE_LIMITTRG_NUMBER){
		moistureproof_state_t.moistureproof_state_open_limit =  Check_Motor_Limit_t;
	}else;

}




