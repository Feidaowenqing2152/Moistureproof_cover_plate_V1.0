/*
 * hmi_SysControl.c
 *
 *  Created on: 2023年3月28日
 *      Author: 好
 */

#define LOG_TAG    "hmi_SysControl"
#include "../himi/sys/hmi_SysControl.h"



/* 设置菜单显示效果 */
static void System_Control_SetMenu(  MenuShow_t *ptShowInfo);
/********************************************** 切换页面 - 系统参数-系统控制第二页设置页面  ***************************************************************/
static void System_Control_Next_Page_Load(void);
static void System_Control_Next_Page_Exit(void);
static void System_Control_Next_Page_Task(void);

static void System_Control_Return_Previous_Menu_Page_Load(void);
/************* 系统参数-系统通信公共回调函数  *******************/
static void System_Control_Slcet_Set_Buttons_CB( key_Input_Number_Typedef key_number , Key_Trg_Even key_state);

struct set_system_control_menu_list_pararm{
	int auto_exit_sets_page_to_main_time ;  //自动返回时间
	system_para_def system_para ;
};


static struct set_system_control_menu_list_pararm set_system_control_pararm_t ;


/******************系统参数-系统控制选择设置页面选择*********************************/
/* 系统控制第一页设置菜单*/
static MenuList_t System_Control_First_Page_Set_Menu_Table[] =
{
    {"光照强度控制设置", NULL, System_Control_Illumination_Page_Load, System_Control_Illumination_Page_Exit, System_Control_Illumination_Page_Task, NULL},

    {"系统时间控制设置", NULL, System_Control_Timer_Page_Load, System_Control_Timer_Page_Exit, System_Control_Timer_Page_Task, NULL},

    {"湿度差值控制设置", NULL, System_Control_Humidity_Page_Load, System_Control_Humidity_Page_Exit, System_Control_Humidity_Page_Task, NULL},

    {"下一页设置", NULL,  System_Control_Next_Page_Load, System_Control_Next_Page_Exit, System_Control_Next_Page_Task, NULL},

    {"返回上级菜单", NULL,  Return_Previous_Menu_Page_Load, NULL, NULL, NULL},

    {"返回主页面", NULL,  Back_Main_Page_Load,   NULL,   NULL, NULL},
};


/* 设置菜单显示效果 */
static void System_Control_SetMenu(  MenuShow_t *ptShowInfo){
	show_refresh_time();
	show_eth_connect_state();
}
/********************************************** 切换页面 - 系统参数-系统控制第一页置页面  ***************************************************************/
void System_Control_Setting_Page_Load(void){

	log_d("System_Control_Setting_Page_Load ");
	type_slect_move_cursor slect_move_cursor;
	system_para_def system_para_t ;

	slect_move_cursor.dw_cursor_adderss = SYSTEM_SYS_CONTROL_PAGE1_SELECT_CURSOR_ADDERSS ;
	slect_move_cursor.max_slect_move = 5 ;
	slect_move_cursor.min_slect_move = 0 ;
	slect_move_cursor.move_slect_step = 1 ;
	slect_move_cursor.now_slect_move = 0 ;
	slect_cursor_move_init(&slect_move_cursor);  //光标位置初始化
	slect_cursor_move(cursor_default_mode,cursor_null);  //初始化选择设置光标

	read_saveenv_cjson_system_parameter(&system_para_t);
	set_system_control_pararm_t.auto_exit_sets_page_to_main_time = system_para_t.AutoExitSetsPageTime;

	dw_show_switching_pages(PAGE_SYSTEM_CONTROL_FIRST_PAGE_SETTING_NUMBER); 			//切换页面

	Buttons_Register(KEY_UP_TRG_NUMBER,System_Control_Slcet_Set_Buttons_CB);
	Buttons_Register(KEY_ENTER_TRG_NUMBER,System_Control_Slcet_Set_Buttons_CB);
	Buttons_Register(KEY_DOWN_TRG_NUMBER,System_Control_Slcet_Set_Buttons_CB);
	//clear_time_cnt(AUTO_EXIT_SETS_PAGE_TO_MAIN_PAGE_TIMER_NUMBER);
	Menu_Bind(System_Control_First_Page_Set_Menu_Table, GET_MENU_NUM(System_Control_First_Page_Set_Menu_Table), System_Control_SetMenu);
}

void System_Control_Setting_Page_Exit(void){
	//clear_time_cnt(AUTO_EXIT_SETS_PAGE_TO_MAIN_PAGE_TIMER_NUMBER);
}

void System_Control_Setting_Page_Task(void){
	if(check_time_arrive(AUTO_EXIT_SETS_PAGE_TO_MAIN_PAGE_TIMER_NUMBER,set_system_control_pararm_t.auto_exit_sets_page_to_main_time*1000)){
		Back_Main_Page_Load();
	}
}

/********************************************** 切换页面 - 系统参数-系统控制第二页设置页面  ***************************************************************/
/* 系统控制上一页设置菜单*/
static MenuList_t System_Control_Last_Page_Set_Menu_Table[] =
{
    {"温度控制设置", NULL, System_Control_Temperature_Page_Load, System_Control_Temperature_Page_Exit, System_Control_Temperature_Page_Task, NULL},

    {"盖板关闭延时设置", NULL, System_Control_CloseDelay_Page_Load, System_Control_CloseDelay_Page_Exit, System_Control_CloseDelay_Page_Task, NULL},

    {"系统屏幕控制设置", NULL, System_Control_Display_Page_Load, System_Control_Display_Page_Exit, System_Control_Display_Page_Task, NULL},

    {"上一页设置", NULL,  System_Control_Setting_Page_Load, System_Control_Setting_Page_Exit, System_Control_Setting_Page_Task, NULL},

    {"返回上级菜单", NULL,  System_Control_Return_Previous_Menu_Page_Load, NULL, NULL, NULL},

    {"返回主页面", NULL,  Back_Main_Page_Load,   NULL,   NULL, NULL},
};
static void System_Control_Next_Page_Load(void){
	type_slect_move_cursor slect_move_cursor;
	system_para_def system_para_t ;

	slect_move_cursor.dw_cursor_adderss = SYSTEM_SYS_CONTROL_PAGE2_SELECT_CURSOR_ADDERSS ;
	slect_move_cursor.max_slect_move = 5 ;
	slect_move_cursor.min_slect_move = 0 ;
	slect_move_cursor.move_slect_step = 1 ;
	slect_move_cursor.now_slect_move = 0 ;
	slect_cursor_move_init(&slect_move_cursor); 		 			//光标位置初始化
	slect_cursor_move(cursor_default_mode,cursor_null);  			//初始化选择设置光标

	read_saveenv_cjson_system_parameter(&system_para_t);
	set_system_control_pararm_t.auto_exit_sets_page_to_main_time = system_para_t.AutoExitSetsPageTime;

	dw_show_switching_pages(PAGE_SYSTEM_CONTROL_LAST_PAGE_SETTING_NUMBER); //切换页面
	Buttons_Register(KEY_UP_TRG_NUMBER,System_Control_Slcet_Set_Buttons_CB);
	Buttons_Register(KEY_ENTER_TRG_NUMBER,System_Control_Slcet_Set_Buttons_CB);
	Buttons_Register(KEY_DOWN_TRG_NUMBER,System_Control_Slcet_Set_Buttons_CB);
	Menu_Bind(System_Control_Last_Page_Set_Menu_Table, GET_MENU_NUM(System_Control_Last_Page_Set_Menu_Table), System_Control_SetMenu);
}
static void System_Control_Next_Page_Exit(void){
	//clear_time_cnt(AUTO_EXIT_SETS_PAGE_TO_MAIN_PAGE_TIMER_NUMBER);
}
static void System_Control_Next_Page_Task(void){
	if(check_time_arrive(AUTO_EXIT_SETS_PAGE_TO_MAIN_PAGE_TIMER_NUMBER,set_system_control_pararm_t.auto_exit_sets_page_to_main_time*1000)){
		Back_Main_Page_Load();
	}
}


/************* 系统参数-系统通信公共回调函数  *******************/
static void System_Control_Slcet_Set_Buttons_CB( key_Input_Number_Typedef key_number , Key_Trg_Even key_state){
	if(key_state == KEY_CLICK_ACTION){
		//clear_time_cnt(AUTO_EXIT_SETS_PAGE_TO_MAIN_PAGE_TIMER_NUMBER);
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

static void System_Control_Return_Previous_Menu_Page_Load(void){
	Menu_Exit(true);	//退出到温度传感器设置菜单
	Menu_Exit(true);    //退出到外界参数设置菜单
	Menu_Exit(true);    //退出到外界参数设置菜单
}

