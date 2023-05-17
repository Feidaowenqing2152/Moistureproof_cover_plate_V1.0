/*
 * hmi_internal_set.c
 *
 *  Created on: 2023年2月10日
 *      Author: 好
 */
#define LOG_TAG    "internal/hmi_internal_set"

#include "../himi/internal/hmi_internal_set.h"

static int hmi_auto_exit_sets_page_to_main_time = 0 ;

static void Show_Internal_Setting_Menu(MenuShow_t *ptShowInfo);

static void Hmi_Internal_Main_Slcet_Set_Buttons_CB(key_Input_Number_Typedef key_number ,Key_Trg_Even key_state);
static void Internal_Slect_Set_Init(void);

/* 主菜单 */
MenuList_t sg_InternalSetMenuTable[] =
{
    {"温度传感器设置", "", Internal_Temp_Setting_Page_Load, Internal_Temp_Setting_Page_Exit, Internal_Temp_Setting_Page_Task, NULL},

    {"湿度传感器设置", "", Internal_Humi_Setting_Page_Load, Internal_Humi_Setting_Page_Exit, Internal_Humi_Setting_Page_Task, NULL},

    {"水浸传感器设置", "", Internal_Water_Setting_Page_Load, Internal_Water_Setting_Page_Exit, Internal_Water_Setting_Page_Task, NULL},

    {"烟雾传感器设置", "", Internal_Smoke_Setting_Page_Load, Internal_Smoke_Setting_Page_Exit, Internal_Smoke_Setting_Page_Task, NULL},

    {"返回主菜单", "", Return_Previous_Menu_Page_Load, NULL, NULL, NULL},

    {"返回主页面", "", Back_Main_Page_Load, NULL, NULL, NULL},

};



void Hmi_Main_Internal_Setting_Page_Load(void){
	log_d("Hmi_Main_Internal_Setting_Page_Load ");
	system_para_def system_para_t ;
	read_saveenv_cjson_system_parameter(&system_para_t);
	hmi_auto_exit_sets_page_to_main_time = system_para_t.AutoExitSetsPageTime;
	Internal_Slect_Set_Init();   //初始化选择设置光标

	Buttons_Register(KEY_UP_TRG_NUMBER,Hmi_Internal_Main_Slcet_Set_Buttons_CB);
	Buttons_Register(KEY_ENTER_TRG_NUMBER,Hmi_Internal_Main_Slcet_Set_Buttons_CB);
	Buttons_Register(KEY_DOWN_TRG_NUMBER,Hmi_Internal_Main_Slcet_Set_Buttons_CB);
	Menu_Bind(sg_InternalSetMenuTable, GET_MENU_NUM(sg_InternalSetMenuTable), Show_Internal_Setting_Menu);
}

void Hmi_Main_Internal_Setting_Page_Exit(void){
	log_d("Hmi_Main_Internal_Setting_Page_Exit ");
}

void Hmi_Main_Internal_Setting_Page_Task(void){
	if(check_time_arrive(AUTO_EXIT_SETS_PAGE_TO_MAIN_PAGE_TIMER_NUMBER,hmi_auto_exit_sets_page_to_main_time*1000)){
		Back_Main_Page_Load();
		//clear_time_cnt(AUTO_EXIT_SETS_PAGE_TO_MAIN_PAGE_TIMER_NUMBER);
	}
}

/* 设置菜单显示效果 */
static void Show_Internal_Setting_Menu(MenuShow_t *ptShowInfo){
	show_refresh_time();
	show_eth_connect_state();
}
/******************外界参数设置页面选择*********************************/
static void Internal_Slect_Set_Init(void){
	type_slect_move_cursor slect_move_cursor;
	slect_move_cursor.dw_cursor_adderss = INTERNAL_TEMPERATURE_SET_CURSOR_ADDERSS ;
	slect_move_cursor.max_slect_move = 5 ;
	slect_move_cursor.min_slect_move = 0 ;
	slect_move_cursor.move_slect_step = 1 ;
	slect_move_cursor.now_slect_move = 0 ;
	slect_cursor_move_init(&slect_move_cursor);  //光标位置初始化
	dw_show_switching_pages(PAGE_INTERNAL_SETTING_NUMBER); //切换页面
	slect_cursor_move(cursor_default_mode,cursor_null);  //初始化选择设置光标
}




static void Hmi_Internal_Main_Slcet_Set_Buttons_CB(key_Input_Number_Typedef key_number ,Key_Trg_Even key_state){
	if(key_state == KEY_CLICK_ACTION){
		//clear_time_cnt(AUTO_EXIT_SETS_PAGE_TO_MAIN_PAGE_TIMER_NUMBER);
		switch(key_number){
		case KEY_UP_TRG_NUMBER :
			log_d("key up.");
			slect_cursor_move(cursor_refresh_mode,cursor_up);
			Menu_SelectPrevious(true);
			break;
		case KEY_ENTER_TRG_NUMBER :
			log_d("key enter.");
			Menu_Enter();
			break;
		case KEY_DOWN_TRG_NUMBER :
			log_d("key down.");
			slect_cursor_move(cursor_refresh_mode,cursor_down);
			Menu_SelectNext(true);
			break;
		default :
			slect_cursor_move(cursor_refresh_mode,cursor_up);
			Menu_SelectPrevious(true);
			break;
		}
	}
}
