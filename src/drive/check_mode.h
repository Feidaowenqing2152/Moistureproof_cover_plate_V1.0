/*
 * check_mode.h
 *
 *  Created on: 2023年2月17日
 *      Author: 好
 */

#ifndef DRIVE_CHECK_MODE_H_
#define DRIVE_CHECK_MODE_H_
#include "../common.h"
#include "../hardware/dev_check_mode.h"

typedef void (*Check_Mode_State_Cb)( CheckModeState_t) ;

void check_mode_init(void);
void Check_Mode_Register(Check_Mode_State_Cb pCheckModeFun);
void Check_Mode_UnRegister(void);
void Check_Mode_loop_scan_even(void);

#endif /* DRIVE_CHECK_MODE_H_ */
