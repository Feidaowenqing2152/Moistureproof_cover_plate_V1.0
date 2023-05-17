/*
 * motor.h
 *
 *  Created on: 2023年2月15日
 *      Author: 好
 */

#ifndef DRIVE_MOTOR_H_
#define DRIVE_MOTOR_H_

#include "../common.h"
#include "../hardware/dev_motor.h"
typedef void (*Motor_Limit_State_Cb)(Motor_Limit_Typedef , Check_Motor_Limit_State) ;

void motor_init(void);
void Motor_Register(Motor_Limit_Typedef eMotor_Number, Motor_Limit_State_Cb pMotorFun);
void Motor_UnRegister(Motor_Limit_Typedef eMotor_Number);
void Motor_loop_scan_even(void);
int get_motor_motion_status(void);



#endif /* DRIVE_MOTOR_H_ */
