/*
 * main.h
 *
 *  Created on: 2022年6月15日
 *      Author: 好
 */

#ifndef TASK_MAIN_H_
#define TASK_MAIN_H_


#include "../common.h"

typedef enum{
	RUN_MODE_ERROR = 0 ,
	RUN_FIX_MODE  ,                  //工作模式或使能检测功能
	RUN_WORK_MODE ,                 //检修模式或失能检测功能
	RUN_REMOTE_CONTROL_MODE ,
}Local_Run_Mode;




enum system_run_step{
	system_motor_reset_step = 0 ,
	system_read_config_step ,
	system_check_work_mode_step ,
	system_check_sleet_transducer_step ,
	system_check_illumination_transducer_step ,
	system_check_sys_timer_step ,
	system_check_humidity_transducer_step ,
	system_check_temperature_transducer_step ,
	system_running_fixd_mode_step ,
	system_running_remote_test_step ,
};



typedef struct
{
	int close_ref_LX1_illumination_date ;    //盖板关闭参考基准光照值LX1
	int open_ref_LX2_illumination_date ;    //盖板关闭参考基准光照值LX2
	int close_motor_delay_T1_date ;     	//延时关闭盖板t1参考值
	int close_motor_delay_T2_date ;     	//延时关闭盖板t2参考值
	int close_motor_delay_T3_date ;     	//延时关闭盖板t2参考值
	int close_motor_time_S1 ;                //设置盖板关闭时间S1
	int close_motor_time_S2 ;                //设置盖板关闭时间S2
	int close_motor_humidity_K1;   //设置内外湿度差K1
	int open_motor_humidity_K2;   //设置内外湿度差K2
	int close_motor_temperature_C1;   //设置内外温度差C1
	int open_motor_temperature_C2;   //设置内外温度差C2
	int close_motor_internal_temperature ;  //关闭盖板内部温度
	int close_motor_external_temperature ;  //关闭盖板外界温度

}GetInformDwSetParamEven;  //获取迪文屏幕设置参数

typedef struct
{
	int show_rgb_led_mode ;                 //RGB显示模式
	int remote_test_flag ;                  //远程测试标志位
	int test_motor_delay_T4_date ;     	    //远程测试T4延时值
	int remote_test_motor_action_type ;    //远程测试电机动作类型

}GetInformMqttMasgEven;



#endif /* TASK_MAIN_H_ */
