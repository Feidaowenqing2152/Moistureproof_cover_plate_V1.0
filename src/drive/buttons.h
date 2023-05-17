/*
 * buttons.h
 *
 *  Created on: 2023年2月10日
 *      Author: 好
 */

#ifndef DRIVE_BUTTONS_H_
#define DRIVE_BUTTONS_H_

#include "../common.h"
#include "../hardware/dev_buttons.h"

////////////////////////  key_timer   //////////////////////
#define BUTTONS_SHAKE_TIME          5	//5ms 硬件一级消抖时间
#define KEY_TRIGGER_TIMER     		20  //20ms  软件二级消抖时间
//#define KEY_TWO_TRIGGER_TIME  	  45 //250MS 双击时间阀值
#define KEY_LONG_PRESS_TIME  	   2000 //2s 长按时间阀值



typedef enum {
	 KEY_NOT_ACTION =0 ,          			  // 按键无动作
	 KEY_CLICK_ACTION  ,       				 // 单击动作
	 KEY_LONG_PRESS_ACTION  ,  	             // 长按动作 ----> 长按按键触发状态
	 KEY_LONG_RELEASE_ACTION ,               // 长按动作 ----> 长按按键释放
	 KEY_TWO_ACTION 						 //双击
}Key_Trg_Even;


typedef void (*ButtonsFunCB)(key_Input_Number_Typedef , Key_Trg_Even) ;
typedef void (*ButtonsTrgCb)(void);

int user_key_even_init(void);
void Buttons_Register(key_Input_Number_Typedef eKey, ButtonsFunCB pKeyFun);
void Buttons_Trg_Register(ButtonsTrgCb pfnKeyTrgFun_t);
void Buttons_Trg_UnRegister(void);
void Buttons_UnRegister(key_Input_Number_Typedef eKey);
void buttons_loop_scan_even(void);







#endif /* DRIVE_BUTTONS_H_ */


