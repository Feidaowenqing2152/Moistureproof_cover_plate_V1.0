/*
 * app_motor.h
 *
 *  Created on: 2023年2月15日
 *      Author: 好
 */

#ifndef APP_APP_MOTOR_H_
#define APP_APP_MOTOR_H_

#include "../common.h"

#define MAX_DUTY_ALL_FRAME_TIME       5006       //100%占空比，播放完毕24帧动画所需时间 ms

struct moistureproof_state{
	uint8_t moistureproof_state_close_limit ;   //盖板闭合限位			0---盖板关闭到位 1---未完全关闭
	uint8_t moistureproof_state_open_limit ;	//盖板打开限位			0---盖板打开到位 1---未完全打开
};


#define MOISTUREPROOF_ANIMATION_TIMER  100



void app_motor_init(void);
int motor_reset(void);
void Motor_Move(uint8_t move_dir ,int duty );
struct moistureproof_state loop_scan_motor_limit_state(uint16_t scan_timer);
void Moistureproof_state_animation_Task(uint8_t refresh_flag);



#endif /* APP_APP_MOTOR_H_ */
