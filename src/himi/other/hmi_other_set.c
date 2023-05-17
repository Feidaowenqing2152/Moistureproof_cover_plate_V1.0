/*
 * hmi_other_set.c
 *
 *  Created on: 2023年5月15日
 *      Author: 好
 */
#define LOG_TAG    "hmi_other_set"

#include "../himi/other/hmi_other_set.h"


static void MenuDateShow_Init(void);

static void Slcet_Cursor_Set_Buttons_CB( key_Input_Number_Typedef key_number , Key_Trg_Even key_state);

struct other_set_menu_list_pararm{
	int auto_exit_sets_page_to_main_time ;  				//自动返回时间
};


static struct other_set_menu_list_pararm other_set_menu_list_pararm_t ;

static void MenuDateShow_Init(void){
	system_para_def system_para_t ;
	read_saveenv_cjson_system_parameter(&system_para_t);
	other_set_menu_list_pararm_t.auto_exit_sets_page_to_main_time = system_para_t.AutoExitSetsPageTime;
}

/* 设置菜单显示效果 */
static void Other_SetMenu(  MenuShow_t *ptShowInfo){
	show_refresh_time();
	show_eth_connect_state();
}


/********************************************** 切换页面 - 其他参数选择设置页面  ***************************************************************/
/* 其他参数选择设置菜单*/
static MenuList_t Other_Set_Menu_Table[] =
{
    {"菜单登录密码设置", NULL, Menuconfig_Passwd_Setting_Page_Load, Menuconfig_Passwd_Setting_Page_Exit, Menuconfig_Passwd_Setting_Page_Task, NULL},

    {"返回上级菜单", NULL,  Return_Previous_Menu_Page_Load, NULL, NULL, NULL},

    {"返回主页面", NULL,  Back_Main_Page_Load,   NULL,   NULL, NULL},
};



void Hmi_Main_Other_Setting_Page_Load(void){
	log_d("Hmi_Main_Other_Setting_Page_Load ");
	type_slect_move_cursor slect_move_cursor;
	slect_move_cursor.dw_cursor_adderss = OTHER_SETTING_SELECT_CURSOR_ADDERSS ;
	slect_move_cursor.max_slect_move = 2 ;
	slect_move_cursor.min_slect_move = 0 ;
	slect_move_cursor.move_slect_step = 1 ;
	slect_move_cursor.now_slect_move = 0 ;
	slect_cursor_move_init(&slect_move_cursor);  			//光标位置初始化
	dw_show_switching_pages(PAGE_OTHER_SETTING_NUMBER); 	//切换页面
	slect_cursor_move(cursor_default_mode,cursor_null);  	//初始化选择设置显示光标
	Buttons_Register(KEY_UP_TRG_NUMBER,Slcet_Cursor_Set_Buttons_CB);
	Buttons_Register(KEY_ENTER_TRG_NUMBER,Slcet_Cursor_Set_Buttons_CB);
	Buttons_Register(KEY_DOWN_TRG_NUMBER,Slcet_Cursor_Set_Buttons_CB);
	MenuDateShow_Init();
	Menu_Bind(Other_Set_Menu_Table, GET_MENU_NUM(Other_Set_Menu_Table), Other_SetMenu);
}
void Hmi_Main_Other_Setting_Page_Exit(void){
//	Buttons_UnRegister(KEY_UP_TRG_NUMBER);
//	Buttons_UnRegister(KEY_ENTER_TRG_NUMBER);
//	Buttons_UnRegister(KEY_DOWN_TRG_NUMBER);
}
void Hmi_Main_Other_Setting_Page_Task(void){
	if(check_time_arrive(AUTO_EXIT_SETS_PAGE_TO_MAIN_PAGE_TIMER_NUMBER,other_set_menu_list_pararm_t.auto_exit_sets_page_to_main_time*1000)){
		Back_Main_Page_Load();
	}
}




/************* 内部湿度传感器公共回调函数  *******************/
static void Slcet_Cursor_Set_Buttons_CB( key_Input_Number_Typedef key_number , Key_Trg_Even key_state){
	if(key_state == KEY_CLICK_ACTION){
		switch(key_number){
		case KEY_UP_TRG_NUMBER :
			slect_cursor_move(cursor_refresh_mode,cursor_up);
			Menu_SelectPrevious(true);
			log_d("slect up ");
			break;
		case KEY_ENTER_TRG_NUMBER :
			Menu_Enter();
			log_d("slect enter ");
			break;
		case KEY_DOWN_TRG_NUMBER :
			slect_cursor_move(cursor_refresh_mode,cursor_down);
			Menu_SelectNext(true);
			log_d("slect down ");
			break;
		default :
			slect_cursor_move(cursor_refresh_mode,cursor_up);
			Menu_SelectPrevious(true);
			break;
		}
	}
}

