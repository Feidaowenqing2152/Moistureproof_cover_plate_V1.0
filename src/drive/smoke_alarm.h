/*
 * smoke_alarm.h
 *
 *  Created on: 2023年2月16日
 *      Author: 好
 */

#ifndef DRIVE_SMOKE_ALARM_H_
#define DRIVE_SMOKE_ALARM_H_

#include "../common.h"
#include "../hardware/dev_smoke.h"

typedef void (*Smoke_Alarm_State_Cb)(Get_Smoke_State_Typedef , uint8_t) ;
typedef void (*Smoke_Online_State_Cb)(Get_Smoke_State_Typedef , uint8_t) ;


void smoke_init(void);
void Smoke_Alarm_Register(Get_Smoke_State_Typedef alarm_type, Smoke_Alarm_State_Cb pSmokeAlarmFun);
void Smoke_Online_Register(Get_Smoke_State_Typedef online_type, Smoke_Online_State_Cb pSmokeOnlineFun);
void Smoke_UnRegister(Get_Smoke_State_Typedef alarm_type);
void Smoke_loop_scan_even(void);

#endif /* DRIVE_SMOKE_ALARM_H_ */
