/*
 * water_alarm.h
 *
 *  Created on: 2023年2月16日
 *      Author: 好
 */

#ifndef DRIVE_WATER_ALARM_H_
#define DRIVE_WATER_ALARM_H_

#include "../common.h"
#include "../hardware/dev_water.h"

typedef void (*Water_Alarm_State_Cb)(Get_Water_State_Typedef , uint8_t) ;
typedef void (*Water_Online_State_Cb)(Get_Water_State_Typedef , uint8_t) ;

void water_init(void);
void Water_Alarm_Register(Get_Water_State_Typedef alarm_type, Water_Alarm_State_Cb pWaterAlarmFun);
void Water_Online_Register(Get_Water_State_Typedef online_type, Water_Online_State_Cb pWaterOnlineFun);
void Water_UnRegister(Get_Water_State_Typedef water_type);
void Water_loop_scan_even(void);

#endif /* DRIVE_WATER_ALARM_H_ */
