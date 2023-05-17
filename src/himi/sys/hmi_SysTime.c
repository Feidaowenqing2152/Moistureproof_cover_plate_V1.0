/*
 * hmi_SysTime.c
 *
 *  Created on: 2023年3月22日
 *      Author: 好
 */

#define LOG_TAG    "hmi_SysTime"
#include "../himi/sys/hmi_SysTime.h"

/* 参数初始化*/
static void SystemMenuDateShow_Init(void);
/* 设置菜单显示效果 */
static void System_Timer_SetMenu(  MenuShow_t *ptShowInfo);
/********************************************** 切换页面 - 系统运行时间设置页面  ***************************************************************/
static void System_Run_Time_Set_Page_Load(void);
static void System_Run_Time_Set_Page_Exit(void);
static void System_Run_Time_Set_Page_Task(void);
/************* 输入参数- 系统运行时间 页面  *******************/
static void System_Run_Time_Input_Page_Load(void);
static void System_Run_Time_Input_Page_Exit(void);
static void System_Run_Time_Input_Page_Task(void);
static void System_Time_Slcet_Input_Buttons_CB(key_Input_Number_Typedef key_number ,Key_Trg_Even key_state);
/********* 保存设置参数- 系统运行时间  ******************/
static void System_Run_Time_Enter_Page_Load(void);
static void System_Run_Time_Enter_Page_Exit(void);
static void System_Run_Time_Enter_Page_Task(void);

/********************************************** 切换页面 - 自动返回主页时间值页面  ***************************************************************/
static void Auto_Exit_Time_Set_Page_Load(void);
static void Auto_Exit_Time_Set_Page_Exit(void);
static void Auto_Exit_Time_Set_Page_Task(void);
/************* 输入参数- 自动返回主页值页面  *******************/
static void Auto_Exit_Time_Input_Page_Load(void);
static void Auto_Exit_Time_Input_Page_Exit(void);
static void Auto_Exit_Time_Input_Page_Task(void);
static void Auto_Exit_Time_Input_Buttons_CB(key_Input_Number_Typedef key_number ,Key_Trg_Even key_state);
/********* 保存设置参数- 自动返回主页时间值  ******************/
static void Auto_Exit_Time_Enter_Page_Load(void);
static void Auto_Exit_Time_Enter_Page_Exit(void);
static void Auto_Exit_Time_Enter_Page_Task(void);
/********************************************** 切换页面 - 系统参数-系统时钟页面  ***************************************************************/
static void System_Clock_Set_Page_Load(void);
static void System_Clock_Set_Page_Exit(void);
static void System_Clock_Set_Page_Task(void);
/************* 输入参数- 系统参数-系统时钟设置页面  *******************/
static void System_Clock_Set_Input_Page_Load(void);
static void System_Clock_Set_Input_Page_Exit(void);
static void System_Clock_Set_Input_Page_Task(void);
static void System_Clock_Set_Input_Buttons_CB(key_Input_Number_Typedef key_number ,Key_Trg_Even key_state);
/********* 保存设置参数- 系统参数-系统时钟设置参数  ******************/
static void System_Clock_Set_Enter_Page_Load(void);
static void System_Clock_Set_Enter_Page_Exit(void);
static void System_Clock_Set_Enter_Page_Task(void);
/************* 系统参数-系统时间公共回调函数  *******************/
static void System_Time_Slcet_Set_Buttons_CB( key_Input_Number_Typedef key_number , Key_Trg_Even key_state);
static void System_Timer_Enter_Window_Buttons_CB( key_Input_Number_Typedef key_number , Key_Trg_Even key_state);



struct set_systemtime_menu_list_pararm{
	int auto_exit_sets_page_to_main_time ;  //自动返回时间
	system_para_def system_para ;
	struct tm system_t;
	ShownMenuDate SY_ShowAutoTimerDateFun_t;

	ShownMenuDate SY_ShowSyatemClockYearsFun_t;
	ShownMenuDate SY_ShowSyatemClockMonthsFun_t;
	ShownMenuDate SY_ShowSyatemClockDaysFun_t;
	ShownMenuDate SY_ShowSyatemClockHourFun_t;
	ShownMenuDate SY_ShowSyatemClockMinuteFun_t;

};


static struct set_systemtime_menu_list_pararm set_systemtime_menu_list_pararm_t ;


/******************外界参数-系统时间设置页面选择*********************************/

/* 系统时间设置菜单*/
static MenuList_t System_Timer_Set_Menu_Table[] =
{
    {"系统运行时间设置", NULL, System_Run_Time_Set_Page_Load, System_Run_Time_Set_Page_Exit, System_Run_Time_Set_Page_Task, NULL},

    {"自动返回主页时间设置", NULL, Auto_Exit_Time_Set_Page_Load, Auto_Exit_Time_Set_Page_Exit, Auto_Exit_Time_Set_Page_Task, NULL},

    {"系统时钟设置", NULL, System_Clock_Set_Page_Load, System_Clock_Set_Page_Exit, System_Clock_Set_Page_Task, NULL},

    {"返回上级菜单", NULL,  Return_Previous_Menu_Page_Load, NULL, NULL, NULL},

    {"返回主页面", NULL,  Back_Main_Page_Load,   NULL,   NULL, NULL},
};

/* 参数初始化*/
static void SystemMenuDateShow_Init(void){
	system_para_def system_para_t ;
	set_systemtime_menu_list_pararm_t.SY_ShowAutoTimerDateFun_t = show_sy_auto_exit_date ;    //显示自动返回时间值

	set_systemtime_menu_list_pararm_t.SY_ShowSyatemClockYearsFun_t = show_sy_system_clock_years_date ;
	set_systemtime_menu_list_pararm_t.SY_ShowSyatemClockMonthsFun_t = show_sy_system_clock_month_date ;
	set_systemtime_menu_list_pararm_t.SY_ShowSyatemClockDaysFun_t = show_sy_system_clock_days_date ;
	set_systemtime_menu_list_pararm_t.SY_ShowSyatemClockHourFun_t = show_sy_system_clock_hours_date ;
	set_systemtime_menu_list_pararm_t.SY_ShowSyatemClockMinuteFun_t = show_sy_system_clock_minute_date ;

	read_saveenv_cjson_system_parameter(&system_para_t);
	set_systemtime_menu_list_pararm_t.auto_exit_sets_page_to_main_time = system_para_t.AutoExitSetsPageTime;

	read_sys_time( &set_systemtime_menu_list_pararm_t.system_t );
	set_systemtime_menu_list_pararm_t.system_para.SetSystemClcokYearsDate =  set_systemtime_menu_list_pararm_t.system_t.tm_year -100 ;  //years = tm_years+1900-2000
	set_systemtime_menu_list_pararm_t.system_para.SetSystemClcokMonthDate = set_systemtime_menu_list_pararm_t.system_t.tm_mon+1 ;
	set_systemtime_menu_list_pararm_t.system_para.SetSystemClcokDaysDate = set_systemtime_menu_list_pararm_t.system_t.tm_mday ;
	set_systemtime_menu_list_pararm_t.system_para.SetSystemClcokHousDate = set_systemtime_menu_list_pararm_t.system_t.tm_hour ;
	set_systemtime_menu_list_pararm_t.system_para.SetSystemClcokMinuteDate = set_systemtime_menu_list_pararm_t.system_t.tm_min ;
	set_systemtime_menu_list_pararm_t.system_para.SetSystemClcokSecondDate = set_systemtime_menu_list_pararm_t.system_t.tm_sec ;
}


/* 设置菜单显示效果 */
static void System_Timer_SetMenu(  MenuShow_t *ptShowInfo){
	show_refresh_time();
	show_eth_connect_state();
}
/********************************************** 切换页面 - 系统时间设置页面  ***************************************************************/
void System_Tmie_Setting_Page_Load(void){

	log_d("Hmi_Main_External_Setting_Page_Load ");
	type_slect_move_cursor slect_move_cursor;

	slect_move_cursor.dw_cursor_adderss = SYSTEM_TIME_SET_SELECT_CURSOR_ADDERSS ;
	slect_move_cursor.max_slect_move = 4 ;
	slect_move_cursor.min_slect_move = 0 ;
	slect_move_cursor.move_slect_step = 1 ;
	slect_move_cursor.now_slect_move = 0 ;
	slect_cursor_move_init(&slect_move_cursor);  //光标位置初始化
	dw_show_switching_pages(PAGE_SYSTEM_TIME_SETTING_NUMBER); //切换页面
	slect_cursor_move(cursor_default_mode,cursor_null);  //初始化选择设置光标
	Buttons_Register(KEY_UP_TRG_NUMBER,System_Time_Slcet_Set_Buttons_CB);
	Buttons_Register(KEY_ENTER_TRG_NUMBER,System_Time_Slcet_Set_Buttons_CB);
	Buttons_Register(KEY_DOWN_TRG_NUMBER,System_Time_Slcet_Set_Buttons_CB);
	SystemMenuDateShow_Init();
	//clear_time_cnt(AUTO_EXIT_SETS_PAGE_TO_MAIN_PAGE_TIMER_NUMBER);
	Menu_Bind(System_Timer_Set_Menu_Table, GET_MENU_NUM(System_Timer_Set_Menu_Table), System_Timer_SetMenu);
}

void System_Tmie_Setting_Page_Exit(void){
	//clear_time_cnt(AUTO_EXIT_SETS_PAGE_TO_MAIN_PAGE_TIMER_NUMBER);
}

void System_Tmie_Setting_Page_Task(void){
	if(check_time_arrive(AUTO_EXIT_SETS_PAGE_TO_MAIN_PAGE_TIMER_NUMBER,set_systemtime_menu_list_pararm_t.auto_exit_sets_page_to_main_time*1000)){
		Back_Main_Page_Load();
		//clear_time_cnt(AUTO_EXIT_SETS_PAGE_TO_MAIN_PAGE_TIMER_NUMBER);
	}
}






/********************************************** 切换页面 - 系统运行时间设置页面  ***************************************************************/
/* 系统运行时间设置菜单 */
static MenuList_t System_Run_Timer_Set_Menu_Table[] =
{
	{"系统运行时间归零", NULL, System_Run_Time_Input_Page_Load, System_Run_Time_Input_Page_Exit, System_Run_Time_Input_Page_Task, NULL},

    {"保存设置参数", NULL, System_Run_Time_Enter_Page_Load, System_Run_Time_Enter_Page_Exit, System_Run_Time_Enter_Page_Task, NULL},

    {"返回上级菜单", NULL,  Return_Previous_Menu_Page_Load, NULL, NULL, NULL},

    {"返回主页面", NULL,  Back_Main_Page_Load,   NULL,   NULL, NULL},
};

static void System_Run_Time_Set_Page_Load(void){
	type_slect_move_cursor slect_move_cursor;
	slect_move_cursor.dw_cursor_adderss = SYSTEM_RUN_TIME_SET_SELECT_CURSOR_ADDERSS ;
	slect_move_cursor.max_slect_move = 3 ;
	slect_move_cursor.min_slect_move = 0 ;
	slect_move_cursor.move_slect_step = 1 ;
	slect_move_cursor.now_slect_move = 0 ;
	slect_cursor_move_init(&slect_move_cursor); 		 			//光标位置初始化
	slect_cursor_move(cursor_default_mode,cursor_null);  			//初始化选择设置光标
	dw_show_switching_pages(PAGE_SYSTEM_RUN_TIME_SETTING_NUMBER); //切换页面
	Buttons_Register(KEY_UP_TRG_NUMBER,System_Time_Slcet_Set_Buttons_CB);
	Buttons_Register(KEY_ENTER_TRG_NUMBER,System_Time_Slcet_Set_Buttons_CB);
	Buttons_Register(KEY_DOWN_TRG_NUMBER,System_Time_Slcet_Set_Buttons_CB);
	Menu_Bind(System_Run_Timer_Set_Menu_Table, GET_MENU_NUM(System_Run_Timer_Set_Menu_Table), System_Timer_SetMenu);
}
static void System_Run_Time_Set_Page_Exit(void){
	//clear_time_cnt(AUTO_EXIT_SETS_PAGE_TO_MAIN_PAGE_TIMER_NUMBER);
}
static void System_Run_Time_Set_Page_Task(void){
	if(check_time_arrive(AUTO_EXIT_SETS_PAGE_TO_MAIN_PAGE_TIMER_NUMBER,set_systemtime_menu_list_pararm_t.auto_exit_sets_page_to_main_time*1000)){
		Back_Main_Page_Load();
	}
}
/************* 输入参数- 系统运行时间 页面  *******************/
static void System_Run_Time_Input_Page_Load(void){
	type_slect_move_cursor slect_move_cursor;
	slect_move_cursor.dw_cursor_adderss = SYSTEM_RUN_TIME_SET_SELECT_CURSOR_ADDERSS ;
	slect_move_cursor.max_slect_move = 3 ;
	slect_move_cursor.min_slect_move = 0 ;
	slect_move_cursor.move_slect_step = 1 ;
	slect_move_cursor.now_slect_move = 0 ;
	slect_cursor_move_init(&slect_move_cursor);  //光标位置初始化
	slect_cursor_move(cursor_refresh_mode,cursor_null);  //关闭光标
	//显示成果窗口
	dw_input_parameter_hint_window( 2 ,SYSTEM_RUN_TIME_ADJ_WAIT_WINDOW_VAR_ADDERSS,SYSTEM_RUN_TIME_ADJ_SUCCESS_WINDOW_VAR_ADDERSS,SYSTEM_RUN_TIME_ADJ_ERROR_WINDOW_VAR_ADDERSS);
	set_systemtime_menu_list_pararm_t.system_para.CumulativeRunningTime = 0 ;
	Buttons_Register(KEY_UP_TRG_NUMBER,System_Time_Slcet_Input_Buttons_CB);
	Buttons_Register(KEY_ENTER_TRG_NUMBER,System_Time_Slcet_Input_Buttons_CB);
	Buttons_Register(KEY_DOWN_TRG_NUMBER,System_Time_Slcet_Input_Buttons_CB);
}

static void System_Run_Time_Input_Page_Exit(void){
	//clear_time_cnt(AUTO_EXIT_SETS_PAGE_TO_MAIN_PAGE_TIMER_NUMBER);
	//清除窗口
	dw_input_parameter_hint_window( 0 ,SYSTEM_RUN_TIME_ADJ_WAIT_WINDOW_VAR_ADDERSS,SYSTEM_RUN_TIME_ADJ_SUCCESS_WINDOW_VAR_ADDERSS,SYSTEM_RUN_TIME_ADJ_ERROR_WINDOW_VAR_ADDERSS);

}

static void System_Run_Time_Input_Page_Task(void){
	if(check_time_arrive(AUTO_EXIT_SETS_PAGE_TO_MAIN_PAGE_TIMER_NUMBER,set_systemtime_menu_list_pararm_t.auto_exit_sets_page_to_main_time*1000)){
		Back_Main_Page_Load();
		//clear_time_cnt(AUTO_EXIT_SETS_PAGE_TO_MAIN_PAGE_TIMER_NUMBER);
	}
}


static void System_Time_Slcet_Input_Buttons_CB(key_Input_Number_Typedef key_number ,Key_Trg_Even key_state){
	if(key_state == KEY_CLICK_ACTION){
		//clear_time_cnt(AUTO_EXIT_SETS_PAGE_TO_MAIN_PAGE_TIMER_NUMBER);
		Menu_Exit(true);
	}
}

/********* 保存设置参数- 系统运行时间  ******************/
static void System_Run_Time_Enter_Page_Load(void){
	int ret = -1 ;
	type_slect_move_cursor slect_move_cursor;
	slect_move_cursor.dw_cursor_adderss = SYSTEM_RUN_TIME_SET_SELECT_CURSOR_ADDERSS ;
	slect_move_cursor.max_slect_move = 3 ;
	slect_move_cursor.min_slect_move = 0 ;
	slect_move_cursor.move_slect_step = 1 ;
	slect_move_cursor.now_slect_move = 0 ;
	slect_cursor_move_init(&slect_move_cursor);  //光标位置初始化
	slect_cursor_move(cursor_refresh_mode,cursor_null);  //关闭光标
	Buttons_UnRegister(KEY_UP_TRG_NUMBER);
	Buttons_UnRegister(KEY_ENTER_TRG_NUMBER);
	Buttons_UnRegister(KEY_DOWN_TRG_NUMBER);
	//显示等待窗口
	dw_input_parameter_hint_window( 1 ,SYSTEM_RUN_TIME_SAVEENV_WAIT_WINDOW_VAR_ADDERSS,SYSTEM_RUN_TIME_SAVEENV_SUCCESS_WINDOW_VAR_ADDERSS,SYSTEM_RUN_TIME_SAVEENV_ERROR_WINDOW_VAR_ADDERSS);
	ret = systemparaPoint_amend_config("CumulativeRunningTime",set_systemtime_menu_list_pararm_t.system_para.CumulativeRunningTime);
	if( !ret){
		 //显示成功窗口
		dw_input_parameter_hint_window(2,SYSTEM_RUN_TIME_SAVEENV_WAIT_WINDOW_VAR_ADDERSS,SYSTEM_RUN_TIME_SAVEENV_SUCCESS_WINDOW_VAR_ADDERSS,SYSTEM_RUN_TIME_SAVEENV_ERROR_WINDOW_VAR_ADDERSS);
	}else{
		//显示错误窗口
		dw_input_parameter_hint_window( 3 ,SYSTEM_RUN_TIME_SAVEENV_WAIT_WINDOW_VAR_ADDERSS,SYSTEM_RUN_TIME_SAVEENV_SUCCESS_WINDOW_VAR_ADDERSS,SYSTEM_RUN_TIME_SAVEENV_ERROR_WINDOW_VAR_ADDERSS);
	}
	Buttons_Register(KEY_ENTER_TRG_NUMBER,System_Timer_Enter_Window_Buttons_CB);
}

static void System_Run_Time_Enter_Page_Exit(void){
	//清除窗口
	dw_input_parameter_hint_window( 0 ,SYSTEM_RUN_TIME_SAVEENV_WAIT_WINDOW_VAR_ADDERSS,SYSTEM_RUN_TIME_SAVEENV_SUCCESS_WINDOW_VAR_ADDERSS,SYSTEM_RUN_TIME_SAVEENV_ERROR_WINDOW_VAR_ADDERSS);
	//clear_time_cnt(AUTO_EXIT_SETS_PAGE_TO_MAIN_PAGE_TIMER_NUMBER);
}

static void System_Run_Time_Enter_Page_Task(void){
	if(check_time_arrive(AUTO_EXIT_SETS_PAGE_TO_MAIN_PAGE_TIMER_NUMBER,set_systemtime_menu_list_pararm_t.auto_exit_sets_page_to_main_time*1000)){
		Back_Main_Page_Load();
		//clear_time_cnt(AUTO_EXIT_SETS_PAGE_TO_MAIN_PAGE_TIMER_NUMBER);
	}
}

/********************************************** 切换页面 - 自动返回主页时间值页面  ***************************************************************/
/* 自动返回主页菜单 */
static MenuList_t Auto_Exit_Time_Menu_Table[] =
{
	{"参数输入框", NULL, Auto_Exit_Time_Input_Page_Load, Auto_Exit_Time_Input_Page_Exit, Auto_Exit_Time_Input_Page_Task, NULL},

    {"保存设置参数", NULL, Auto_Exit_Time_Enter_Page_Load, Auto_Exit_Time_Enter_Page_Exit, Auto_Exit_Time_Enter_Page_Task, NULL},

    {"返回上级菜单", NULL,  Return_Previous_Menu_Page_Load, NULL, NULL, NULL},

    {"返回主页面", NULL,  Back_Main_Page_Load,   NULL,   NULL, NULL},
};

static void Auto_Exit_Time_Set_Page_Load(void){
	type_slect_move_cursor slect_move_cursor;

	slect_move_cursor.dw_cursor_adderss = AUTO_EXIT_TIME_INTPUT_SELECT_CURSOR_VAR_ADDERSS ;
	slect_move_cursor.max_slect_move = 1 ;
	slect_move_cursor.min_slect_move = 0 ;
	slect_move_cursor.move_slect_step = 1 ;
	slect_move_cursor.now_slect_move = 0 ;
	slect_cursor_move_init(&slect_move_cursor);  		//光标位置初始化
	slect_cursor_move(cursor_refresh_mode,cursor_null);  //关闭输入指示光标
	slect_move_cursor.dw_cursor_adderss = AUTO_EXIT_SET_PAGE_SELECT_CURSOR_ADDERSS ;
	slect_move_cursor.max_slect_move = 3 ;
	slect_move_cursor.min_slect_move = 0 ;
	slect_move_cursor.move_slect_step = 1 ;
	slect_move_cursor.now_slect_move = 0 ;
	slect_cursor_move_init(&slect_move_cursor); 		 			//光标位置初始化
	slect_cursor_move(cursor_default_mode,cursor_null);  			//初始化选择设置光标
	read_saveenv_cjson_system_parameter(&set_systemtime_menu_list_pararm_t.system_para);
	set_systemtime_menu_list_pararm_t.SY_ShowAutoTimerDateFun_t(set_systemtime_menu_list_pararm_t.system_para.AutoExitSetsPageTime);  //显示高温阈值
	dw_show_switching_pages(PAGE_AUTO_EXIT_TIME_SETTING_NUMBER); //切换页面
	Buttons_Register(KEY_UP_TRG_NUMBER,System_Time_Slcet_Set_Buttons_CB);
	Buttons_Register(KEY_ENTER_TRG_NUMBER,System_Time_Slcet_Set_Buttons_CB);
	Buttons_Register(KEY_DOWN_TRG_NUMBER,System_Time_Slcet_Set_Buttons_CB);
	Menu_Bind(Auto_Exit_Time_Menu_Table, GET_MENU_NUM(Auto_Exit_Time_Menu_Table), System_Timer_SetMenu);
}
static void Auto_Exit_Time_Set_Page_Exit(void){
	//clear_time_cnt(AUTO_EXIT_SETS_PAGE_TO_MAIN_PAGE_TIMER_NUMBER);
}
static void Auto_Exit_Time_Set_Page_Task(void){
	if(check_time_arrive(AUTO_EXIT_SETS_PAGE_TO_MAIN_PAGE_TIMER_NUMBER,set_systemtime_menu_list_pararm_t.auto_exit_sets_page_to_main_time*1000)){
		Back_Main_Page_Load();
		//clear_time_cnt(AUTO_EXIT_SETS_PAGE_TO_MAIN_PAGE_TIMER_NUMBER);
	}
}
/************* 输入参数- 自动返回主页值页面  *******************/
static void Auto_Exit_Time_Input_Page_Load(void){
	type_slect_move_cursor slect_move_cursor;

	slect_move_cursor.dw_cursor_adderss = AUTO_EXIT_SET_PAGE_SELECT_CURSOR_ADDERSS ;
	slect_move_cursor.max_slect_move = 3 ;
	slect_move_cursor.min_slect_move = 0 ;
	slect_move_cursor.move_slect_step = 1 ;
	slect_move_cursor.now_slect_move = 0 ;
	slect_cursor_move_init(&slect_move_cursor);  //光标位置初始化
	slect_cursor_move(cursor_refresh_mode,cursor_null);  //关闭选择设置光标
	slect_move_cursor.dw_cursor_adderss = AUTO_EXIT_TIME_INTPUT_SELECT_CURSOR_VAR_ADDERSS ;
	slect_move_cursor.max_slect_move = 1 ;
	slect_move_cursor.min_slect_move = 0 ;
	slect_move_cursor.move_slect_step = 1 ;
	slect_move_cursor.now_slect_move = 0 ;
	slect_cursor_move_init(&slect_move_cursor);  //光标位置初始化
	slect_cursor_move(cursor_default_mode,cursor_null);  //显示初始化输入指示光标位置
	Buttons_Register(KEY_UP_TRG_NUMBER,Auto_Exit_Time_Input_Buttons_CB);
	Buttons_Register(KEY_ENTER_TRG_NUMBER,Auto_Exit_Time_Input_Buttons_CB);
	Buttons_Register(KEY_DOWN_TRG_NUMBER,Auto_Exit_Time_Input_Buttons_CB);
}

static void Auto_Exit_Time_Input_Page_Exit(void){
	//clear_time_cnt(AUTO_EXIT_SETS_PAGE_TO_MAIN_PAGE_TIMER_NUMBER);
}

static void Auto_Exit_Time_Input_Page_Task(void){
	if(check_time_arrive(AUTO_EXIT_SETS_PAGE_TO_MAIN_PAGE_TIMER_NUMBER,set_systemtime_menu_list_pararm_t.auto_exit_sets_page_to_main_time*1000)){
		Back_Main_Page_Load();
		//clear_time_cnt(AUTO_EXIT_SETS_PAGE_TO_MAIN_PAGE_TIMER_NUMBER);
	}
}


static void Auto_Exit_Time_Input_Buttons_CB(key_Input_Number_Typedef key_number ,Key_Trg_Even key_state){
	if(key_state == KEY_CLICK_ACTION){
		//clear_time_cnt(AUTO_EXIT_SETS_PAGE_TO_MAIN_PAGE_TIMER_NUMBER);
		set_systemtime_menu_list_pararm_t.system_para.AutoExitSetsPageTime=user_parameter_adjustment(set_systemtime_menu_list_pararm_t.system_para.AutoExitSetsPageTime,false,2,key_number,set_systemtime_menu_list_pararm_t.SY_ShowAutoTimerDateFun_t);
	}
}

/********* 保存设置参数- 自动返回主页时间值  ******************/
static void Auto_Exit_Time_Enter_Page_Load(void){
	int ret = -1 ;
	type_slect_move_cursor slect_move_cursor;
	slect_move_cursor.dw_cursor_adderss = AUTO_EXIT_SET_PAGE_SELECT_CURSOR_ADDERSS ;
	slect_move_cursor.max_slect_move = 3 ;
	slect_move_cursor.min_slect_move = 0 ;
	slect_move_cursor.move_slect_step = 1 ;
	slect_move_cursor.now_slect_move = 0 ;
	slect_cursor_move_init(&slect_move_cursor);  //光标位置初始化
	slect_cursor_move(cursor_refresh_mode,cursor_null);  //关闭光标
	Buttons_UnRegister(KEY_UP_TRG_NUMBER);
	Buttons_UnRegister(KEY_ENTER_TRG_NUMBER);
	Buttons_UnRegister(KEY_DOWN_TRG_NUMBER);
	//显示等待窗口
	dw_input_parameter_hint_window( 1 ,AUTO_EXIT_TIME_WAIT_WINDOW_VAR_ADDERSS,AUTO_EXIT_TIME_SUCCESS_WINDOW_VAR_ADDERSS,AUTO_EXIT_TIME_ERROR_WINDOW_VAR_ADDERSS);
	ret = systemparaPoint_amend_config("AutoExitSetsPageTime",set_systemtime_menu_list_pararm_t.system_para.AutoExitSetsPageTime);
	if( !ret){
		 //显示成功窗口
		dw_input_parameter_hint_window(2 ,AUTO_EXIT_TIME_WAIT_WINDOW_VAR_ADDERSS,AUTO_EXIT_TIME_SUCCESS_WINDOW_VAR_ADDERSS,AUTO_EXIT_TIME_ERROR_WINDOW_VAR_ADDERSS);
	}else{
		//显示错误窗口
		dw_input_parameter_hint_window( 3  ,AUTO_EXIT_TIME_WAIT_WINDOW_VAR_ADDERSS,AUTO_EXIT_TIME_SUCCESS_WINDOW_VAR_ADDERSS,AUTO_EXIT_TIME_ERROR_WINDOW_VAR_ADDERSS);
	}
	Buttons_Register(KEY_ENTER_TRG_NUMBER,System_Timer_Enter_Window_Buttons_CB);
}

static void Auto_Exit_Time_Enter_Page_Exit(void){
	//清除窗口
	dw_input_parameter_hint_window( 0  ,AUTO_EXIT_TIME_WAIT_WINDOW_VAR_ADDERSS,AUTO_EXIT_TIME_SUCCESS_WINDOW_VAR_ADDERSS,AUTO_EXIT_TIME_ERROR_WINDOW_VAR_ADDERSS);
	//clear_time_cnt(AUTO_EXIT_SETS_PAGE_TO_MAIN_PAGE_TIMER_NUMBER);
}

static void Auto_Exit_Time_Enter_Page_Task(void){
	if(check_time_arrive(AUTO_EXIT_SETS_PAGE_TO_MAIN_PAGE_TIMER_NUMBER,set_systemtime_menu_list_pararm_t.auto_exit_sets_page_to_main_time*1000)){
		Back_Main_Page_Load();
		//clear_time_cnt(AUTO_EXIT_SETS_PAGE_TO_MAIN_PAGE_TIMER_NUMBER);
	}
}

/********************************************** 切换页面 - 系统参数-系统时钟页面  ***************************************************************/
/* 系统参数-系统时钟设置菜单 */
static MenuList_t System_Clock_Set_Menu_Table[] =
{
	{"参数输入框", NULL, System_Clock_Set_Input_Page_Load, System_Clock_Set_Input_Page_Exit, System_Clock_Set_Input_Page_Task, NULL},

    {"保存设置参数", NULL, System_Clock_Set_Enter_Page_Load, System_Clock_Set_Enter_Page_Exit, System_Clock_Set_Enter_Page_Task, NULL},

    {"返回上级菜单", NULL,  Return_Previous_Menu_Page_Load, NULL, NULL, NULL},

    {"返回主页面", NULL,  Back_Main_Page_Load,   NULL,   NULL, NULL},
};

static void System_Clock_Set_Page_Load(void){

	type_slect_move_cursor slect_move_cursor;
	log_d("clearn System_Clock_Set_Page_Load !");
	slect_move_cursor.dw_cursor_adderss = SYSTEM_TIME_INTPUT_SELECT_CURSOR_VAR_ADDERSS ;
	slect_move_cursor.max_slect_move = 9 ;
	slect_move_cursor.min_slect_move = 0 ;
	slect_move_cursor.move_slect_step = 1 ;
	slect_move_cursor.now_slect_move = 0 ;
	slect_cursor_move_init(&slect_move_cursor);  		//输入指示光标位置初始化
	slect_cursor_move(cursor_refresh_mode,cursor_null);  //关闭输入指示光标
	slect_move_cursor.dw_cursor_adderss = SYSTEM_TIME_PAGE_SELECT_CURSOR_ADDERSS ;
	slect_move_cursor.max_slect_move = 3 ;
	slect_move_cursor.min_slect_move = 0 ;
	slect_move_cursor.move_slect_step = 1 ;
	slect_move_cursor.now_slect_move = 0 ;
	slect_cursor_move_init(&slect_move_cursor); 		 			//光标位置初始化
	slect_cursor_move(cursor_default_mode,cursor_null);  			//初始化选择设置光标
	dw_show_switching_pages(PAGE_SYSTEM_CLOCK_SETTING_NUMBER); //切换页面

	set_systemtime_menu_list_pararm_t.SY_ShowSyatemClockYearsFun_t(set_systemtime_menu_list_pararm_t.system_para.SetSystemClcokYearsDate);
	set_systemtime_menu_list_pararm_t.SY_ShowSyatemClockMonthsFun_t(set_systemtime_menu_list_pararm_t.system_para.SetSystemClcokMonthDate);
	set_systemtime_menu_list_pararm_t.SY_ShowSyatemClockDaysFun_t(set_systemtime_menu_list_pararm_t.system_para.SetSystemClcokDaysDate);
	set_systemtime_menu_list_pararm_t.SY_ShowSyatemClockHourFun_t(set_systemtime_menu_list_pararm_t.system_para.SetSystemClcokHousDate);
	set_systemtime_menu_list_pararm_t.SY_ShowSyatemClockMinuteFun_t(set_systemtime_menu_list_pararm_t.system_para.SetSystemClcokMinuteDate);
	log_d("SetSystemClcokYearsDate=%d",set_systemtime_menu_list_pararm_t.system_para.SetSystemClcokYearsDate);
	log_d("SetSystemClcokMonthDate=%d",set_systemtime_menu_list_pararm_t.system_para.SetSystemClcokMonthDate);
	log_d("SetSystemClcokDaysDate=%d",set_systemtime_menu_list_pararm_t.system_para.SetSystemClcokDaysDate);
	log_d("SetSystemClcokHousDate=%d",set_systemtime_menu_list_pararm_t.system_para.SetSystemClcokHousDate);
	log_d("SetSystemClcokMinuteDate=%d",set_systemtime_menu_list_pararm_t.system_para.SetSystemClcokMinuteDate);
	Buttons_Register(KEY_UP_TRG_NUMBER,System_Time_Slcet_Set_Buttons_CB);
	Buttons_Register(KEY_ENTER_TRG_NUMBER,System_Time_Slcet_Set_Buttons_CB);
	Buttons_Register(KEY_DOWN_TRG_NUMBER,System_Time_Slcet_Set_Buttons_CB);
	Menu_Bind(System_Clock_Set_Menu_Table, GET_MENU_NUM(System_Clock_Set_Menu_Table), System_Timer_SetMenu);
}

static void System_Clock_Set_Page_Exit(void){
	//clear_time_cnt(AUTO_EXIT_SETS_PAGE_TO_MAIN_PAGE_TIMER_NUMBER);
}
static void System_Clock_Set_Page_Task(void){
	if(check_time_arrive(AUTO_EXIT_SETS_PAGE_TO_MAIN_PAGE_TIMER_NUMBER,set_systemtime_menu_list_pararm_t.auto_exit_sets_page_to_main_time*1000)){
		Back_Main_Page_Load();
		//clear_time_cnt(AUTO_EXIT_SETS_PAGE_TO_MAIN_PAGE_TIMER_NUMBER);
	}
}

/************* 输入参数- 系统参数-系统时钟设置页面  *******************/
static void System_Clock_Set_Input_Page_Load(void){
	type_slect_move_cursor slect_move_cursor;
	log_d("clearn System_Clock_Set_Input_Page_Load !");
	slect_move_cursor.dw_cursor_adderss = SYSTEM_TIME_PAGE_SELECT_CURSOR_ADDERSS ;
	slect_move_cursor.max_slect_move = 3 ;
	slect_move_cursor.min_slect_move = 0 ;
	slect_move_cursor.move_slect_step = 1 ;
	slect_move_cursor.now_slect_move = 0 ;
	slect_cursor_move_init(&slect_move_cursor);  //光标位置初始化
	slect_cursor_move(cursor_refresh_mode,cursor_null);  //关闭选择设置光标
	slect_move_cursor.dw_cursor_adderss = SYSTEM_TIME_INTPUT_SELECT_CURSOR_VAR_ADDERSS ;
	slect_move_cursor.max_slect_move = 9 ;
	slect_move_cursor.min_slect_move = 0 ;
	slect_move_cursor.move_slect_step = 1 ;
	slect_move_cursor.now_slect_move = 0 ;
	slect_cursor_move_init(&slect_move_cursor);  //光标位置初始化
	slect_cursor_move(cursor_default_mode,cursor_null);  //显示初始化输入指示光标位置
	Buttons_Register(KEY_UP_TRG_NUMBER,System_Clock_Set_Input_Buttons_CB);
	Buttons_Register(KEY_ENTER_TRG_NUMBER,System_Clock_Set_Input_Buttons_CB);
	Buttons_Register(KEY_DOWN_TRG_NUMBER,System_Clock_Set_Input_Buttons_CB);

}

static void System_Clock_Set_Input_Page_Exit(void){
	//clear_time_cnt(AUTO_EXIT_SETS_PAGE_TO_MAIN_PAGE_TIMER_NUMBER);
}

static void System_Clock_Set_Input_Page_Task(void){
	if(check_time_arrive(AUTO_EXIT_SETS_PAGE_TO_MAIN_PAGE_TIMER_NUMBER,set_systemtime_menu_list_pararm_t.auto_exit_sets_page_to_main_time*1000)){
		Back_Main_Page_Load();
	}
}

static void System_Clock_Set_Input_Buttons_CB(key_Input_Number_Typedef key_number ,Key_Trg_Even key_state){
	static uint8_t User_Trg_Buttons_Cnts = 0 ;

	if(key_state == KEY_CLICK_ACTION){
		//clear_time_cnt(AUTO_EXIT_SETS_PAGE_TO_MAIN_PAGE_TIMER_NUMBER);
		if(key_number ==KEY_ENTER_TRG_NUMBER ){
			User_Trg_Buttons_Cnts++ ;
			if(User_Trg_Buttons_Cnts > 9 ){
				User_Trg_Buttons_Cnts = 0 ;
				clearn_Temp_Compensation_Slcet_buttons_cnt();
				log_d("clearn User_Trg_Buttons_Cnts !");
				Menu_Exit(true);
				return ;
			}
		}
		//log_d("User_Trg_Buttons_Cnts=%d",User_Trg_Buttons_Cnts);
		if((User_Trg_Buttons_Cnts >=0) &&(User_Trg_Buttons_Cnts< 2) ){
			set_systemtime_menu_list_pararm_t.system_para.SetSystemClcokYearsDate=user_parameter_adjustment(set_systemtime_menu_list_pararm_t.system_para.SetSystemClcokYearsDate,  \
																				false,3,key_number,set_systemtime_menu_list_pararm_t.SY_ShowSyatemClockYearsFun_t);
		}else if( (User_Trg_Buttons_Cnts>= 2 ) &&(User_Trg_Buttons_Cnts < 4 ) ){
			set_systemtime_menu_list_pararm_t.system_para.SetSystemClcokMonthDate=user_parameter_adjustment(set_systemtime_menu_list_pararm_t.system_para.SetSystemClcokMonthDate,  \
																				false,3,key_number,set_systemtime_menu_list_pararm_t.SY_ShowSyatemClockMonthsFun_t);
		}else if( (User_Trg_Buttons_Cnts>= 4 ) &&(User_Trg_Buttons_Cnts < 6 ) ){
			set_systemtime_menu_list_pararm_t.system_para.SetSystemClcokDaysDate=user_parameter_adjustment(set_systemtime_menu_list_pararm_t.system_para.SetSystemClcokDaysDate,  \
																				false,3,key_number,set_systemtime_menu_list_pararm_t.SY_ShowSyatemClockDaysFun_t);
		}else if( (User_Trg_Buttons_Cnts>= 6 ) &&(User_Trg_Buttons_Cnts < 8 ) ){
			set_systemtime_menu_list_pararm_t.system_para.SetSystemClcokHousDate=user_parameter_adjustment(set_systemtime_menu_list_pararm_t.system_para.SetSystemClcokHousDate,  \
																				false,3,key_number,set_systemtime_menu_list_pararm_t.SY_ShowSyatemClockHourFun_t);
		}else {
			set_systemtime_menu_list_pararm_t.system_para.SetSystemClcokMinuteDate=user_parameter_adjustment(set_systemtime_menu_list_pararm_t.system_para.SetSystemClcokMinuteDate,  \
																				false,3,key_number,set_systemtime_menu_list_pararm_t.SY_ShowSyatemClockMinuteFun_t);
		}
		if(key_number ==KEY_ENTER_TRG_NUMBER ){
			if( (User_Trg_Buttons_Cnts %2) ==0 ){
				clearn_Temp_Compensation_Slcet_buttons_cnt();
			}
		}

	}
}

/********* 保存设置参数- 系统参数-系统时钟设置参数  ******************/
static void System_Clock_Set_Enter_Page_Load(void){
	int ret = -1 ;
	struct tm time ;
	type_slect_move_cursor slect_move_cursor;
	slect_move_cursor.dw_cursor_adderss = SYSTEM_TIME_PAGE_SELECT_CURSOR_ADDERSS ;
	slect_move_cursor.max_slect_move = 3 ;
	slect_move_cursor.min_slect_move = 0 ;
	slect_move_cursor.move_slect_step = 1 ;
	slect_move_cursor.now_slect_move = 0 ;
	slect_cursor_move_init(&slect_move_cursor);  //光标位置初始化
	slect_cursor_move(cursor_refresh_mode,cursor_null);  //关闭光标
	Buttons_UnRegister(KEY_UP_TRG_NUMBER);
	Buttons_UnRegister(KEY_ENTER_TRG_NUMBER);
	Buttons_UnRegister(KEY_DOWN_TRG_NUMBER);
	time.tm_year = set_systemtime_menu_list_pararm_t.system_para.SetSystemClcokYearsDate + 2000 ;
	time.tm_mon = set_systemtime_menu_list_pararm_t.system_para.SetSystemClcokMonthDate ;
	time.tm_mday = set_systemtime_menu_list_pararm_t.system_para.SetSystemClcokDaysDate ;
	time.tm_hour = set_systemtime_menu_list_pararm_t.system_para.SetSystemClcokHousDate ;
	time.tm_min = set_systemtime_menu_list_pararm_t.system_para.SetSystemClcokMinuteDate ;
	time.tm_sec = 0 ;

	//显示等待窗口
	dw_input_parameter_hint_window( 1 ,SYSTEM_TIME_WAIT_WINDOW_VAR_ADDERSS,SYSTEM_TIME_SUCCESS_WINDOW_VAR_ADDERSS,SYSTEM_TIME_ERROR_WINDOW_VAR_ADDERSS);
	ret = write_sys_time(&time);
	if( ret >=0){
		 //显示成功窗口
		dw_input_parameter_hint_window(2,SYSTEM_TIME_WAIT_WINDOW_VAR_ADDERSS,SYSTEM_TIME_SUCCESS_WINDOW_VAR_ADDERSS,SYSTEM_TIME_ERROR_WINDOW_VAR_ADDERSS);
	}else{
		//显示错误窗口
		dw_input_parameter_hint_window( 3,SYSTEM_TIME_WAIT_WINDOW_VAR_ADDERSS,SYSTEM_TIME_SUCCESS_WINDOW_VAR_ADDERSS,SYSTEM_TIME_ERROR_WINDOW_VAR_ADDERSS);
	}
	Buttons_Register(KEY_ENTER_TRG_NUMBER,System_Timer_Enter_Window_Buttons_CB);
}

static void System_Clock_Set_Enter_Page_Exit(void){
	//清除窗口
		dw_input_parameter_hint_window( 0 ,SYSTEM_TIME_WAIT_WINDOW_VAR_ADDERSS,SYSTEM_TIME_SUCCESS_WINDOW_VAR_ADDERSS,SYSTEM_TIME_ERROR_WINDOW_VAR_ADDERSS);
		//clear_time_cnt(AUTO_EXIT_SETS_PAGE_TO_MAIN_PAGE_TIMER_NUMBER);
}

static void System_Clock_Set_Enter_Page_Task(void){
	if(check_time_arrive(AUTO_EXIT_SETS_PAGE_TO_MAIN_PAGE_TIMER_NUMBER,set_systemtime_menu_list_pararm_t.auto_exit_sets_page_to_main_time*1000)){
		Back_Main_Page_Load();
		//clear_time_cnt(AUTO_EXIT_SETS_PAGE_TO_MAIN_PAGE_TIMER_NUMBER);
	}
}

/************* 系统参数-系统时间公共回调函数  *******************/
static void System_Time_Slcet_Set_Buttons_CB( key_Input_Number_Typedef key_number , Key_Trg_Even key_state){
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

static void System_Timer_Enter_Window_Buttons_CB( key_Input_Number_Typedef key_number , Key_Trg_Even key_state){
	if(key_state == KEY_CLICK_ACTION){
		//clear_time_cnt(AUTO_EXIT_SETS_PAGE_TO_MAIN_PAGE_TIMER_NUMBER);
		switch(key_number){
		case KEY_UP_TRG_NUMBER :
			//Menu_Exit(true);
			log_d("slect up ");
			break;
		case KEY_ENTER_TRG_NUMBER :
			Menu_Exit(true);
			log_d("slect enter ");
			break;
		case KEY_DOWN_TRG_NUMBER :
			//Menu_Exit(true);
			log_d("slect down ");
			break;
		default :
			//Menu_Exit(true);
			break;
		}
	}
}



