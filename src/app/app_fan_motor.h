/*
 * app_fan_motor.h
 *
 *  Created on: 2023年2月15日
 *      Author: 好
 */

#ifndef APP_APP_FAN_MOTOR_H_
#define APP_APP_FAN_MOTOR_H_

#include "../common.h"
#include "../hardware/dev_fan_motor.h"

#define FAN_SAMPLING_TIMER 3   //风机速度采样时间3S
#define FAN_VERLOCITY_MULTIPLE_RPM 60/FAN_SAMPLING_TIMER+0.5

void app_fna_motor_init(void);
void Control_Fna_Motor(int duty );
int Show_Fan_Motor_Velocity_Date_Task(uint8_t refresh_flag,uint16_t refresh_time);


#endif /* APP_APP_FAN_MOTOR_H_ */
