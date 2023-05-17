/*
 * hmi_menuconfig_set.c
 *
 *  Created on: 2023年5月16日
 *      Author: 好
 */

#define LOG_TAG    "hmi_menuconfig_set"

#include "../himi/hmi_menuconfig_set.h"

static int hmi_set_auto_exit_sets_page_to_main_time = 0 ;

static void Slect_Main_Set_Init(void);
static void ShowSetMenu(MenuShow_t *ptShowInfo);
static void Hmi_Main_Slcet_Set_Buttons_CB(key_Input_Number_Typedef key_number ,Key_Trg_Even key_state);


/* 主菜单 */
MenuList_t sg_SetMenuTable[] =
{
    {"外界参数设置", "External_Main_Setting", Hmi_Main_External_Setting_Page_Load, Hmi_Main_External_Setting_Page_Exit, Hmi_Main_External_Setting_Page_Task, NULL},

    {"内部参数设置", "Internal_Main_Setting", Hmi_Main_Internal_Setting_Page_Load, Hmi_Main_Internal_Setting_Page_Exit, Hmi_Main_Internal_Setting_Page_Task, NULL},

    {"系统参数设置", "System_Main_Setting",  Hmi_Main_System_Setting_Page_Load, Hmi_Main_System_Setting_Page_Exit, Hmi_Main_System_Setting_Page_Task, NULL},

    {"其他参数设置", "Other_Main_Setting",  Hmi_Main_Other_Setting_Page_Load, Hmi_Main_Other_Setting_Page_Exit, Hmi_Main_Other_Setting_Page_Task, NULL},

	{"返回主页", "Back_Main_Page",  Back_Main_Page_Load, NULL, NULL, NULL},
};

void Hmi_Main_Setting_Page_Load(void){
	system_para_def system_para_t ;
	read_saveenv_cjson_system_parameter(&system_para_t);
	hmi_set_auto_exit_sets_page_to_main_time = system_para_t.AutoExitSetsPageTime;

	Slect_Main_Set_Init();		 //光标位置初始化

	Buttons_Register(KEY_UP_TRG_NUMBER,Hmi_Main_Slcet_Set_Buttons_CB);
	Buttons_Register(KEY_ENTER_TRG_NUMBER,Hmi_Main_Slcet_Set_Buttons_CB);
	Buttons_Register(KEY_DOWN_TRG_NUMBER,Hmi_Main_Slcet_Set_Buttons_CB);
	Menu_Bind(sg_SetMenuTable, GET_MENU_NUM(sg_SetMenuTable), ShowSetMenu);
	log_d("Hmi_Main_Setting_Page_Load ");
}

void Hmi_Main_Setting_Page_Exit(void){
	log_d("Hmi_Main_Setting_Page_Exit ");
    dw_show_switching_pages(PAGE_MAIN_NUMBER); //切换页面
	dw_show_ip_adderss();
}

void Hmi_Main_Setting_Page_Task(void){
	//log_d("Hmi_Main_Setting_Page_Task ");
	if(check_time_arrive(AUTO_EXIT_SETS_PAGE_TO_MAIN_PAGE_TIMER_NUMBER,hmi_set_auto_exit_sets_page_to_main_time*1000)){
		Back_Main_Page_Load();
	}
}

/* 设置菜单显示效果 */
static void ShowSetMenu(MenuShow_t *ptShowInfo){
	show_refresh_time();
	show_eth_connect_state();
}
static void Slect_Main_Set_Init(void){
	type_slect_move_cursor slect_move_cursor;
	slect_move_cursor.dw_cursor_adderss = MAIN_SET_EXTERNAL_CURSOR_ADDERSS ;
	slect_move_cursor.max_slect_move = 4 ;
	slect_move_cursor.min_slect_move = 0 ;
	slect_move_cursor.move_slect_step = 1 ;
	slect_move_cursor.now_slect_move = 0 ;
	slect_cursor_move_init(&slect_move_cursor);  //光标位置初始化
	dw_show_switching_pages(PAGE_MAIN_SETTING_NUMBER);
	slect_cursor_move(cursor_default_mode,cursor_null);  //初始化选择设置光标
}

static void Hmi_Main_Slcet_Set_Buttons_CB(key_Input_Number_Typedef key_number ,Key_Trg_Even key_state){

	if(key_state == KEY_CLICK_ACTION){
		//clear_time_cnt(AUTO_EXIT_SETS_PAGE_TO_MAIN_PAGE_TIMER_NUMBER);
		switch(key_number){
		case KEY_UP_TRG_NUMBER :
			log_d("buttons up.");
			slect_cursor_move(cursor_refresh_mode,cursor_up);
			Menu_SelectPrevious(true);
			break;
		case KEY_ENTER_TRG_NUMBER :
			log_d("buttons enter.");
			Menu_Enter();
			break;
		case KEY_DOWN_TRG_NUMBER :
			log_d("buttons down.");
			slect_cursor_move(cursor_refresh_mode,cursor_down);
			Menu_SelectNext(true);
			break;
		default :
			slect_cursor_move(cursor_refresh_mode,cursor_down);
			Menu_SelectPrevious(true);
			break;
		}
	}
}
