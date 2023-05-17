/*
 * hmi_menuconfig_set.h
 *
 *  Created on: 2023年5月16日
 *      Author: 好
 */

#ifndef HIMI_HMI_MENUCONFIG_SET_H_
#define HIMI_HMI_MENUCONFIG_SET_H_

#include "../common.h"

void Hmi_Main_Setting_Page_Load(void);
void Hmi_Main_Setting_Page_Exit(void);
void Hmi_Main_Setting_Page_Task(void);

#define MAIN_SET_EXTERNAL_CURSOR_ADDERSS 0x4070  //主菜单-参数选择光标地址

#endif /* HIMI_HMI_MENUCONFIG_SET_H_ */
