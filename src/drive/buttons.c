/*
 * buttons.c
 *
 *  Created on: 2023年2月10日
 *      Author: 好
 */

#define LOG_TAG    "buttons"

#include "../drive/buttons.h"


static void buttons_even_scan( key_Input_Number_Typedef input_key_number,IoKeyState_e input_key_state);

static unsigned char key_event = 0;	 //全局按键状态
static unsigned char key_number = 0; //全局按键编号

ButtonsFunCB pfnKeyNotifyFun = NULL;
ButtonsTrgCb pfnKeyTrgFun = NULL ;

int user_key_even_init(void)
{
	int buttons_fd = 0 ;
	buttons_fd=init_buttons(BUTTONS_SHAKE_TIME);
	key_event = KEY_NOT_ACTION;
	key_number = KEY_NULL_NUMBER;
	pfnKeyNotifyFun = NULL;
	return buttons_fd;
}

/**
  * @brief      注册按键动作改变时的通知回调函数
  *
  * @param[in]  eKey 指定按键, 取值为 @reg IoKeyType_e
  * @param[in]  pKeyFun 通知回调函数
  */
void Buttons_Register(key_Input_Number_Typedef eKey, ButtonsFunCB pKeyFun){
    if (eKey < MAX_KEY_NUMBER)
    {
        pfnKeyNotifyFun = pKeyFun;
    }
}


void Buttons_Trg_Register(ButtonsTrgCb pfnKeyTrgFun_t){
	if(pfnKeyTrgFun_t != NULL)
		pfnKeyTrgFun = pfnKeyTrgFun_t ;
}

/**
  * @brief      注销按键动作改变时的通知回调函数
  *
  * @param[in]  eKey 指定按键, 取值为 @reg IoKeyType_e
  */

void Buttons_UnRegister(key_Input_Number_Typedef eKey){
    if (eKey < MAX_KEY_NUMBER)
    {
        pfnKeyNotifyFun = NULL;
    }
}

void Buttons_Trg_UnRegister(void){
	pfnKeyTrgFun = NULL;
}

void buttons_loop_scan_even(void){
	for(uint8_t i=(KEY_NULL_NUMBER+1);i<MAX_KEY_NUMBER;i++){
		buttons_even_scan(i,get_buttons_state(i));
	}
}

/**
* 	@brief  :获取按键动作
	@input : input_key_number ：按键编号
				 input_key_state ： 检测按键管脚
		@param :[out] 按键动作标号 KEY_NOT_ACTION - 按键无动作 ；
				KEY_CLICK_ACTION--单击动作 ；
				KEY_LONG_PRESS_ACTION--长按动作 ----> 长按按键触发状态；
				KEY_LONG_RELEASE_ACTION ---     长按动作 ----> 长按按键释放；
	@note:调用该函数后，在处理按键动作后，需要释放掉当前按键，即调用rest_key_state()函数释放按键；
 */
static void buttons_even_scan( key_Input_Number_Typedef input_key_number,IoKeyState_e input_key_state){
	static unsigned char key_state = IO_KEY_OFF;
	static unsigned char key_step = 0;
	static unsigned char key_even_flag = 0 ;
	static unsigned char key_release_flag = 0 ; //按键释放标志位

	if(input_key_state==IO_KEY_ERROR){
		key_state = IO_KEY_OFF;
		key_step = 0;
		key_even_flag = 0 ;
		key_release_flag = 0 ; 					  /* 按键释放 */
		key_number = KEY_NULL_NUMBER ;
		log_e("buttons get error !!!");
		return;
	}

	if ((input_key_state == IO_KEY_ON) &&(!key_release_flag)){	//记录触发按键编号
		key_release_flag = 1 ; 				//按键未被释放
		key_number = input_key_number;
	}
	if (input_key_number == key_number){	//检测按键编号是否为未释放前编号
		key_state = input_key_state;
	}
	else{
		return ;
	}
	if (key_number != KEY_NULL_NUMBER){
		switch (key_step){
		case 0:
			if (key_state==IO_KEY_OFF){					  /* 第0步，按键未被触发 */
				key_release_flag = 0 ; 					  /* 按键释放 */
				clear_time_cnt(KEY_TRIGGER_TIMER_NUMBER); /* 清除消抖时间 */
			}
			else{
				key_step++; /* 按键触发 ，进入第1步 */
			}
			break;
		case 1:
			if (key_state==IO_KEY_OFF)	/* 再次确认按键是否按下 */
				key_step--; /* 若没有，则返回第0步 */
			else{			/* 如确认按键按下 */
				if (check_time_arrive(KEY_TRIGGER_TIMER_NUMBER, KEY_TRIGGER_TIMER)){ /* 检查按键按下时间，是否超过设定消抖时间 ，若超过 */
					clear_time_cnt(KEY_TRIGGER_TIMER_NUMBER); /* 清除消抖时间 */
					key_step++;								  /* 进入 第2步 */
				}
			}
			break;
		case 2:
			if (key_state==IO_KEY_OFF){ /* 若超过设定消抖时间后，按键弹起 */
				clear_time_cnt(KEY_TRIGGER_TIMER_NUMBER); /* 清除消抖时间 */
				key_step++;								  /*  进入第3部 */
			}
			else{ /* 若超过设定消抖时间后，按键还未被释放 */
				if (check_time_arrive(KEY_TRIGGER_TIMER_NUMBER, KEY_LONG_PRESS_TIME)){ /* 检查按键按下时间是否超过 长按设定时间 ，若超过 */
					key_event = KEY_LONG_PRESS_ACTION; /* 发生长按 动作 */
					key_step += 2;					   /* 进入第4步 */
					key_even_flag = 1 ;
				}
			}
			break;
		case 3:
			if (key_state==IO_KEY_OFF){ /* 按键被释放 */
				if (check_time_arrive(KEY_TRIGGER_TIMER_NUMBER, KEY_TRIGGER_TIMER)){ /* 检查释放时间是否满足 消抖时间 ，若满足 */
					key_event = KEY_CLICK_ACTION; /* 则发生 单击 动作 */
					key_step = 0;				  /* 返回 第 0 步 */
					key_even_flag = 1 ;
				}
			}
			else{ /* 若按键释放时间 未满足 消抖时间 ，则 */
				clear_time_cnt(KEY_TRIGGER_TIMER_NUMBER); /* 清除消抖时间 */
				key_step--;								  /* 返回 第3步 ，继续判断按键按下时间 */
			}
			break;
		case 4:
			if (key_state==IO_KEY_OFF){ /* 长按 按键释放后 */
				if (check_time_arrive(KEY_TRIGGER_TIMER_NUMBER, KEY_TRIGGER_TIMER)){ /* 检查长按按键 释放 时间是否满足 按键消抖时间 */
					key_event = KEY_LONG_RELEASE_ACTION; /* 则 发生 长按 动作 */
					key_step = 0;						 /* 返回 第 0 步 */
					key_even_flag = 1 ;
				}
			}
			break;
		default:
			break;
		}
	}
	if( key_even_flag ==1 ){
		if(pfnKeyNotifyFun !=NULL)
			pfnKeyNotifyFun((key_Input_Number_Typedef)key_number, key_event);
		if(pfnKeyTrgFun !=NULL)
			pfnKeyTrgFun();
		key_even_flag = 0 ;
		key_release_flag = 0 ; 					  /* 按键释放 */
		key_number = KEY_NULL_NUMBER ;
	}
}








