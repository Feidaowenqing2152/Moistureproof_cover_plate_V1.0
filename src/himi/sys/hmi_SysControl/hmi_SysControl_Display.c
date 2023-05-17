/*
 * hmi_SysControl_Display.c
 *
 *  Created on: 2023年3月28日
 *      Author: 好
 */
#define LOG_TAG    "hmi_SysControl_Display"
#include "../himi/sys/hmi_SysControl/hmi_SysControl_Display.h"




/* 参数初始化*/
static void SystemMenuDateShow_Init(void);
/* 设置菜单显示效果 */
static void System_Control_Display_SetMenu(MenuShow_t *ptShowInfo);
/********************************************** 切换页面 - 系统参数-系统控制-屏幕控制-屏幕亮度设置值页面  ***************************************************************/
static void System_Display_Luminance_Set_Page_Load(void);
static void System_Display_Luminance_Set_Page_Exit(void);
static void System_Display_Luminance_Set_Page_Task(void);
/************* 输入参数- 切换页面 - 系统参数-系统控制-屏幕控制-屏幕亮度设置值页面  *******************/
static void System_Display_Luminance_Input_Page_Load(void);
static void System_Display_Luminance_Input_Page_Exit(void);
static void System_Display_Luminance_Input_Page_Task(void);
static void System_Display_Luminance_Input_Buttons_CB(key_Input_Number_Typedef key_number ,Key_Trg_Even key_state);
/********* 保存设置参数- 系统参数-系统控制-屏幕控制-屏幕亮度设置值  ******************/
static void System_Display_Luminance_Enter_Page_Load(void);
static void System_Display_Luminance_Enter_Page_Exit(void);
static void System_Display_Luminance_Enter_Page_Task(void);
/********************************************** 切换页面 - 系统参数-系统控制-屏幕控制-亮屏时间设置值页面  ***************************************************************/
static void System_Display_Delay_Set_Page_Load(void);
static void System_Display_Delay_Set_Page_Exit(void);
static void System_Display_Delay_Set_Page_Task(void);
/************* 输入参数- 系统参数-系统控制-屏幕控制-亮屏时间设置值页面  *******************/
static void System_Display_Delay_Input_Page_Load(void);
static void System_Display_Delay_Input_Page_Exit(void);
static void System_Display_Delay_Input_Page_Task(void);
static void System_Display_Delay_Input_Buttons_CB(key_Input_Number_Typedef key_number ,Key_Trg_Even key_state);
/********* 保存设置参数- 系统参数-系统控制-屏幕控制-亮屏时间设置值  ******************/
static void System_Display_Delay_Enter_Page_Load(void);
static void System_Display_Delay_Enter_Page_Exit(void);
static void System_Display_Delay_Enter_Page_Task(void);
/************* 系统参数-系统时间公共回调函数  *******************/
static void System_Control_Display_Set_Buttons_CB( key_Input_Number_Typedef key_number , Key_Trg_Even key_state);
static void System_Control_Display_Enter_Window_Buttons_CB( key_Input_Number_Typedef key_number , Key_Trg_Even key_state);

struct set_systemcontrol_display_menu_list_pararm{
	system_para_def system_para ;

	ShownMenuDate SY_ShowIntputSysDisplauLuminanceFun_t;
	ShownMenuDate SY_ShowIntputSysDisplayDelayFun_t;
};


static struct set_systemcontrol_display_menu_list_pararm set_systemcontrol_display_pararm_t;


/******************系统参数-系统控制-屏幕控制设置页面选择*********************************/

/* 系统参数-系统控制-屏幕控制设置菜单*/
static MenuList_t System_Control_Display_Set_Menu_Table[] =
{
    {"屏幕亮度设置", NULL, System_Display_Luminance_Set_Page_Load, System_Display_Luminance_Set_Page_Exit, System_Display_Luminance_Set_Page_Task, NULL},

    {"亮屏时间设置", NULL, System_Display_Delay_Set_Page_Load, System_Display_Delay_Set_Page_Exit, System_Display_Delay_Set_Page_Task, NULL},

    {"返回上级菜单", NULL,  Return_Previous_Menu_Page_Load, NULL, NULL, NULL},

    {"返回主页面", NULL,  Back_Main_Page_Load,   NULL,   NULL, NULL},
};

/* 参数初始化*/
static void SystemMenuDateShow_Init(void){
	set_systemcontrol_display_pararm_t.SY_ShowIntputSysDisplauLuminanceFun_t = show_system_control_display_luminance_value_date ;
	set_systemcontrol_display_pararm_t.SY_ShowIntputSysDisplayDelayFun_t = show_system_control_display_delay_close_value_date ;
	read_saveenv_cjson_system_parameter(&set_systemcontrol_display_pararm_t.system_para);
}


/* 设置菜单显示效果 */
static void System_Control_Display_SetMenu(MenuShow_t *ptShowInfo){
	show_refresh_time();
	show_eth_connect_state();
}
/********************************************** 系统参数-系统控制-屏幕控制设置页面  ***************************************************************/
void System_Control_Display_Page_Load(void){

	log_d("System_Control_CloseDelay_Page_Load ");
	type_slect_move_cursor slect_move_cursor;

	slect_move_cursor.dw_cursor_adderss = SYSTEM_SYS_DISPLAY_CONTROL_SELECT_CURSOR_ADDERSS ;
	slect_move_cursor.max_slect_move = 4 ;
	slect_move_cursor.min_slect_move = 0 ;
	slect_move_cursor.move_slect_step = 1 ;
	slect_move_cursor.now_slect_move = 0 ;
	slect_cursor_move_init(&slect_move_cursor);  //光标位置初始化
	slect_cursor_move(cursor_default_mode,cursor_null);  //初始化选择设置光标

	dw_show_switching_pages(PAGE_SYSTEM_CONTROL_DISPLAY_SETTING_NUMBER); //切换页面
	Buttons_Register(KEY_UP_TRG_NUMBER,System_Control_Display_Set_Buttons_CB);
	Buttons_Register(KEY_ENTER_TRG_NUMBER,System_Control_Display_Set_Buttons_CB);
	Buttons_Register(KEY_DOWN_TRG_NUMBER,System_Control_Display_Set_Buttons_CB);
	SystemMenuDateShow_Init();
	//clear_time_cnt(AUTO_EXIT_SETS_PAGE_TO_MAIN_PAGE_TIMER_NUMBER);
	Menu_Bind(System_Control_Display_Set_Menu_Table, GET_MENU_NUM(System_Control_Display_Set_Menu_Table), System_Control_Display_SetMenu);
}

void System_Control_Display_Page_Exit(void){
	//clear_time_cnt(AUTO_EXIT_SETS_PAGE_TO_MAIN_PAGE_TIMER_NUMBER);
}

void System_Control_Display_Page_Task(void){
	if(check_time_arrive(AUTO_EXIT_SETS_PAGE_TO_MAIN_PAGE_TIMER_NUMBER,set_systemcontrol_display_pararm_t.system_para.AutoExitSetsPageTime*1000)){
		Back_Main_Page_Load();
	}
}


/********************************************** 切换页面 - 系统参数-系统控制-屏幕控制-屏幕亮度设置值页面  ***************************************************************/
/* 自动返回主页菜单 */
static MenuList_t System_Display_Luminance_Menu_Table[] =
{
	{"屏幕亮度值输入框", NULL, System_Display_Luminance_Input_Page_Load,  System_Display_Luminance_Input_Page_Exit, System_Display_Luminance_Input_Page_Task, NULL},

    {"保存设置参数", NULL, System_Display_Luminance_Enter_Page_Load, System_Display_Luminance_Enter_Page_Exit,System_Display_Luminance_Enter_Page_Task, NULL},

    {"返回上级菜单", NULL, Return_Previous_Menu_Page_Load, NULL, NULL, NULL},

    {"返回主页面", NULL,  Back_Main_Page_Load,   NULL,   NULL, NULL},
};

static void System_Display_Luminance_Set_Page_Load(void){
	type_slect_move_cursor slect_move_cursor;

	slect_move_cursor.dw_cursor_adderss = SYSTEM_DISPLAY_LUMINANCE_CONTROL_INTPUT_SELECT_CURSOR_VAR_ADDERSS ;
	slect_move_cursor.max_slect_move = 2 ;
	slect_move_cursor.min_slect_move = 0 ;
	slect_move_cursor.move_slect_step = 1 ;
	slect_move_cursor.now_slect_move = 0 ;
	slect_cursor_move_init(&slect_move_cursor);  		//光标位置初始化
	slect_cursor_move(cursor_refresh_mode,cursor_null);  //关闭输入指示光标

	slect_move_cursor.dw_cursor_adderss = SYSTEM_DISPLAY_LUMINANCE_CONTROL_SELECT_CURSOR_ADDERSS ;
	slect_move_cursor.max_slect_move = 3 ;
	slect_move_cursor.min_slect_move = 0 ;
	slect_move_cursor.move_slect_step = 1 ;
	slect_move_cursor.now_slect_move = 0 ;
	slect_cursor_move_init(&slect_move_cursor); 		 			//光标位置初始化
	slect_cursor_move(cursor_default_mode,cursor_null);  			//初始化选择设置光标

	set_systemcontrol_display_pararm_t.SY_ShowIntputSysDisplauLuminanceFun_t( set_systemcontrol_display_pararm_t.system_para.DisplayBrightnessDate );

	dw_show_switching_pages(PAGE_SYSTEM_CONTROL_DISPLAY_LUMINANCE_NUMBER); //切换页面
	Buttons_Register(KEY_UP_TRG_NUMBER,System_Control_Display_Set_Buttons_CB);
	Buttons_Register(KEY_ENTER_TRG_NUMBER,System_Control_Display_Set_Buttons_CB);
	Buttons_Register(KEY_DOWN_TRG_NUMBER,System_Control_Display_Set_Buttons_CB);
	Menu_Bind(System_Display_Luminance_Menu_Table, GET_MENU_NUM(System_Display_Luminance_Menu_Table), System_Control_Display_SetMenu);
}
static void System_Display_Luminance_Set_Page_Exit(void){
	//clear_time_cnt(AUTO_EXIT_SETS_PAGE_TO_MAIN_PAGE_TIMER_NUMBER);
}
static void System_Display_Luminance_Set_Page_Task(void){
	if(check_time_arrive(AUTO_EXIT_SETS_PAGE_TO_MAIN_PAGE_TIMER_NUMBER,set_systemcontrol_display_pararm_t.system_para.AutoExitSetsPageTime*1000)){
		Back_Main_Page_Load();
	}
}
/************* 输入参数- 系统参数-系统控制-屏幕控制-屏幕亮度设置值页面  *******************/
static void System_Display_Luminance_Input_Page_Load(void){
	type_slect_move_cursor slect_move_cursor;

	slect_move_cursor.dw_cursor_adderss = SYSTEM_DISPLAY_LUMINANCE_CONTROL_SELECT_CURSOR_ADDERSS ;
	slect_move_cursor.max_slect_move = 3 ;
	slect_move_cursor.min_slect_move = 0 ;
	slect_move_cursor.move_slect_step = 1 ;
	slect_move_cursor.now_slect_move = 0 ;
	slect_cursor_move_init(&slect_move_cursor);  //光标位置初始化
	slect_cursor_move(cursor_refresh_mode,cursor_null);  //关闭选择设置光标

	slect_move_cursor.dw_cursor_adderss = SYSTEM_DISPLAY_LUMINANCE_CONTROL_INTPUT_SELECT_CURSOR_VAR_ADDERSS ;
	slect_move_cursor.max_slect_move = 2 ;
	slect_move_cursor.min_slect_move = 0 ;
	slect_move_cursor.move_slect_step = 1 ;
	slect_move_cursor.now_slect_move = 0 ;
	slect_cursor_move_init(&slect_move_cursor);  //光标位置初始化
	slect_cursor_move(cursor_default_mode,cursor_null);  //显示初始化输入指示光标位置

	Buttons_Register(KEY_UP_TRG_NUMBER,System_Display_Luminance_Input_Buttons_CB);
	Buttons_Register(KEY_ENTER_TRG_NUMBER,System_Display_Luminance_Input_Buttons_CB);
	Buttons_Register(KEY_DOWN_TRG_NUMBER,System_Display_Luminance_Input_Buttons_CB);
}

static void System_Display_Luminance_Input_Page_Exit(void){
	//clear_time_cnt(AUTO_EXIT_SETS_PAGE_TO_MAIN_PAGE_TIMER_NUMBER);
}

static void System_Display_Luminance_Input_Page_Task(void){
	if(check_time_arrive(AUTO_EXIT_SETS_PAGE_TO_MAIN_PAGE_TIMER_NUMBER,set_systemcontrol_display_pararm_t.system_para.AutoExitSetsPageTime*1000)){
		Back_Main_Page_Load();
	}
}


static void System_Display_Luminance_Input_Buttons_CB(key_Input_Number_Typedef key_number ,Key_Trg_Even key_state){
	if(key_state == KEY_CLICK_ACTION){
		//clear_time_cnt(AUTO_EXIT_SETS_PAGE_TO_MAIN_PAGE_TIMER_NUMBER);
		set_systemcontrol_display_pararm_t.system_para.DisplayBrightnessDate=user_parameter_adjustment(set_systemcontrol_display_pararm_t.system_para.DisplayBrightnessDate, \
				false,3,key_number,set_systemcontrol_display_pararm_t.SY_ShowIntputSysDisplauLuminanceFun_t);
	}
}


/********* 保存设置参数- 系统参数-系统控制-屏幕控制-屏幕亮度设置  ******************/
static void System_Display_Luminance_Enter_Page_Load(void){
	int ret = -1 ;
	type_slect_move_cursor slect_move_cursor;

	slect_move_cursor.dw_cursor_adderss = SYSTEM_DISPLAY_LUMINANCE_CONTROL_SELECT_CURSOR_ADDERSS ;
	slect_move_cursor.max_slect_move = 3 ;
	slect_move_cursor.min_slect_move = 0 ;
	slect_move_cursor.move_slect_step = 1 ;
	slect_move_cursor.now_slect_move = 0 ;
	slect_cursor_move_init(&slect_move_cursor);  //光标位置初始化
	slect_cursor_move(cursor_refresh_mode,cursor_null);  //关闭选择设置光标

	Buttons_UnRegister(KEY_UP_TRG_NUMBER);
	Buttons_UnRegister(KEY_ENTER_TRG_NUMBER);
	Buttons_UnRegister(KEY_DOWN_TRG_NUMBER);
	//显示等待窗口
	dw_input_parameter_hint_window( 1 ,SYSTEM_DISPLAY_LUMINANCE_CONTROL_WAIT_WINDOW_VAR_ADDERSS,SYSTEM_DISPLAY_LUMINANCE_CONTROL_SUCCESS_WINDOW_VAR_ADDERSS,SYSTEM_DISPLAY_LUMINANCE_CONTROL_ERROR_WINDOW_VAR_ADDERSS);
	ret = systemparaPoint_amend_config("DisplayBrightnessDate",set_systemcontrol_display_pararm_t.system_para.DisplayBrightnessDate);
	if( !ret){
		 //显示成功窗口
		dw_control_display_luminance_date( set_systemcontrol_display_pararm_t.system_para.DisplayBrightnessDate );
		dw_input_parameter_hint_window(2,SYSTEM_DISPLAY_LUMINANCE_CONTROL_WAIT_WINDOW_VAR_ADDERSS,SYSTEM_DISPLAY_LUMINANCE_CONTROL_SUCCESS_WINDOW_VAR_ADDERSS,SYSTEM_DISPLAY_LUMINANCE_CONTROL_ERROR_WINDOW_VAR_ADDERSS);
	}else{
		//显示错误窗口
		dw_input_parameter_hint_window( 3,SYSTEM_DISPLAY_LUMINANCE_CONTROL_WAIT_WINDOW_VAR_ADDERSS,SYSTEM_DISPLAY_LUMINANCE_CONTROL_SUCCESS_WINDOW_VAR_ADDERSS,SYSTEM_DISPLAY_LUMINANCE_CONTROL_ERROR_WINDOW_VAR_ADDERSS);
	}
	Buttons_Register(KEY_ENTER_TRG_NUMBER,System_Control_Display_Enter_Window_Buttons_CB);
}

static void System_Display_Luminance_Enter_Page_Exit(void){
	dw_input_parameter_hint_window( 0,SYSTEM_DISPLAY_LUMINANCE_CONTROL_WAIT_WINDOW_VAR_ADDERSS,SYSTEM_DISPLAY_LUMINANCE_CONTROL_SUCCESS_WINDOW_VAR_ADDERSS,SYSTEM_DISPLAY_LUMINANCE_CONTROL_ERROR_WINDOW_VAR_ADDERSS);
	//clear_time_cnt(AUTO_EXIT_SETS_PAGE_TO_MAIN_PAGE_TIMER_NUMBER);
}

static void System_Display_Luminance_Enter_Page_Task(void){
	if(check_time_arrive(AUTO_EXIT_SETS_PAGE_TO_MAIN_PAGE_TIMER_NUMBER,set_systemcontrol_display_pararm_t.system_para.AutoExitSetsPageTime*1000)){
		Back_Main_Page_Load();
	}
}


/********************************************** 切换页面 - 系统参数-系统控制-屏幕控制-亮屏时间设置值页面  ***************************************************************/
/* 自动返回主页菜单 */
static MenuList_t System_Display_Delay_Menu_Table[] =
{
	{"亮屏时间值输入框", NULL, System_Display_Delay_Input_Page_Load, System_Display_Delay_Input_Page_Exit,System_Display_Delay_Input_Page_Task, NULL},

    {"保存设置参数", NULL, System_Display_Delay_Enter_Page_Load, System_Display_Delay_Enter_Page_Exit, System_Display_Delay_Enter_Page_Task, NULL},

    {"返回上级菜单", NULL,  Return_Previous_Menu_Page_Load, NULL, NULL, NULL},

    {"返回主页面", NULL,  Back_Main_Page_Load,   NULL,   NULL, NULL},
};

static void System_Display_Delay_Set_Page_Load(void){
	type_slect_move_cursor slect_move_cursor;

	slect_move_cursor.dw_cursor_adderss = SYSTEM_DISPLAY_TIMER_CONTROL_INTPUT_SELECT_CURSOR_VAR_ADDERSS ;
	slect_move_cursor.max_slect_move = 1 ;
	slect_move_cursor.min_slect_move = 0 ;
	slect_move_cursor.move_slect_step = 1 ;
	slect_move_cursor.now_slect_move = 0 ;
	slect_cursor_move_init(&slect_move_cursor);  		//光标位置初始化
	slect_cursor_move(cursor_refresh_mode,cursor_null);  //关闭输入指示光标

	slect_move_cursor.dw_cursor_adderss = SYSTEM_DISPLAY_TIMER_CONTROL_SELECT_CURSOR_ADDERSS ;
	slect_move_cursor.max_slect_move = 3 ;
	slect_move_cursor.min_slect_move = 0 ;
	slect_move_cursor.move_slect_step = 1 ;
	slect_move_cursor.now_slect_move = 0 ;
	slect_cursor_move_init(&slect_move_cursor); 		 			//光标位置初始化
	slect_cursor_move(cursor_default_mode,cursor_null);  			//初始化选择设置光标

	set_systemcontrol_display_pararm_t.SY_ShowIntputSysDisplayDelayFun_t( set_systemcontrol_display_pararm_t.system_para.AutomaticallyExtinguishTimeDate );

	dw_show_switching_pages(PAGE_SYSTEM_CONTROL_DISPLAY_DELAY_CLOSE_NUMBER); //切换页面
	Buttons_Register(KEY_UP_TRG_NUMBER,System_Control_Display_Set_Buttons_CB);
	Buttons_Register(KEY_ENTER_TRG_NUMBER,System_Control_Display_Set_Buttons_CB);
	Buttons_Register(KEY_DOWN_TRG_NUMBER,System_Control_Display_Set_Buttons_CB);
	Menu_Bind(System_Display_Delay_Menu_Table, GET_MENU_NUM(System_Display_Delay_Menu_Table), System_Control_Display_SetMenu);
}
static void System_Display_Delay_Set_Page_Exit(void){
	//clear_time_cnt(AUTO_EXIT_SETS_PAGE_TO_MAIN_PAGE_TIMER_NUMBER);
}
static void System_Display_Delay_Set_Page_Task(void){
	if(check_time_arrive(AUTO_EXIT_SETS_PAGE_TO_MAIN_PAGE_TIMER_NUMBER,set_systemcontrol_display_pararm_t.system_para.AutoExitSetsPageTime*1000)){
		Back_Main_Page_Load();
	}
}
/************* 输入参数- 系统参数-系统控制-屏幕控制-亮屏时间设置值页面  *******************/
static void System_Display_Delay_Input_Page_Load(void){
	type_slect_move_cursor slect_move_cursor;

	slect_move_cursor.dw_cursor_adderss = SYSTEM_DISPLAY_TIMER_CONTROL_SELECT_CURSOR_ADDERSS ;
	slect_move_cursor.max_slect_move = 3 ;
	slect_move_cursor.min_slect_move = 0 ;
	slect_move_cursor.move_slect_step = 1 ;
	slect_move_cursor.now_slect_move = 0 ;
	slect_cursor_move_init(&slect_move_cursor);  //光标位置初始化
	slect_cursor_move(cursor_refresh_mode,cursor_null);  //关闭选择设置光标

	slect_move_cursor.dw_cursor_adderss = SYSTEM_DISPLAY_TIMER_CONTROL_INTPUT_SELECT_CURSOR_VAR_ADDERSS ;
	slect_move_cursor.max_slect_move = 1 ;
	slect_move_cursor.min_slect_move = 0 ;
	slect_move_cursor.move_slect_step = 1 ;
	slect_move_cursor.now_slect_move = 0 ;
	slect_cursor_move_init(&slect_move_cursor);  //光标位置初始化
	slect_cursor_move(cursor_default_mode,cursor_null);  //显示初始化输入指示光标位置


	Buttons_Register(KEY_UP_TRG_NUMBER,System_Display_Delay_Input_Buttons_CB);
	Buttons_Register(KEY_ENTER_TRG_NUMBER,System_Display_Delay_Input_Buttons_CB);
	Buttons_Register(KEY_DOWN_TRG_NUMBER,System_Display_Delay_Input_Buttons_CB);
}

static void System_Display_Delay_Input_Page_Exit(void){
	//clear_time_cnt(AUTO_EXIT_SETS_PAGE_TO_MAIN_PAGE_TIMER_NUMBER);
}

static void System_Display_Delay_Input_Page_Task(void){
	if(check_time_arrive(AUTO_EXIT_SETS_PAGE_TO_MAIN_PAGE_TIMER_NUMBER,set_systemcontrol_display_pararm_t.system_para.AutoExitSetsPageTime*1000)){
		Back_Main_Page_Load();
	}
}


static void System_Display_Delay_Input_Buttons_CB(key_Input_Number_Typedef key_number ,Key_Trg_Even key_state){
	if(key_state == KEY_CLICK_ACTION){
		//clear_time_cnt(AUTO_EXIT_SETS_PAGE_TO_MAIN_PAGE_TIMER_NUMBER);
		set_systemcontrol_display_pararm_t.system_para.AutomaticallyExtinguishTimeDate=user_parameter_adjustment(set_systemcontrol_display_pararm_t.system_para.AutomaticallyExtinguishTimeDate, \
				false,2,key_number,set_systemcontrol_display_pararm_t.SY_ShowIntputSysDisplayDelayFun_t);
	}
}


/********* 保存设置参数- 系统参数-系统控制-屏幕控制-亮屏时间设置值  ******************/
static void System_Display_Delay_Enter_Page_Load(void){
	int ret = -1 ;
	type_slect_move_cursor slect_move_cursor;

	slect_move_cursor.dw_cursor_adderss = SYSTEM_DISPLAY_TIMER_CONTROL_SELECT_CURSOR_ADDERSS ;
	slect_move_cursor.max_slect_move = 3 ;
	slect_move_cursor.min_slect_move = 0 ;
	slect_move_cursor.move_slect_step = 1 ;
	slect_move_cursor.now_slect_move = 0 ;
	slect_cursor_move_init(&slect_move_cursor);  //光标位置初始化
	slect_cursor_move(cursor_refresh_mode,cursor_null);  //关闭选择设置光标

	Buttons_UnRegister(KEY_UP_TRG_NUMBER);
	Buttons_UnRegister(KEY_ENTER_TRG_NUMBER);
	Buttons_UnRegister(KEY_DOWN_TRG_NUMBER);
	//显示等待窗口
	dw_input_parameter_hint_window( 1 ,SYSTEM_DISPLAY_TIMER_CONTROL_WAIT_WINDOW_VAR_ADDERSS,SYSTEM_DISPLAY_TIMER_CONTROL_SUCCESS_WINDOW_VAR_ADDERSS,SYSTEM_DISPLAY_TIMER_CONTROL_ERROR_WINDOW_VAR_ADDERSS);
	ret = systemparaPoint_amend_config("AutomaticallyExtinguishTimeDate",set_systemcontrol_display_pararm_t.system_para.AutomaticallyExtinguishTimeDate);
	if( !ret){
		 //显示成功窗口
		dw_input_parameter_hint_window(2 ,SYSTEM_DISPLAY_TIMER_CONTROL_WAIT_WINDOW_VAR_ADDERSS,SYSTEM_DISPLAY_TIMER_CONTROL_SUCCESS_WINDOW_VAR_ADDERSS,SYSTEM_DISPLAY_TIMER_CONTROL_ERROR_WINDOW_VAR_ADDERSS);
	}else{
		//显示错误窗口
		dw_input_parameter_hint_window( 3,SYSTEM_DISPLAY_TIMER_CONTROL_WAIT_WINDOW_VAR_ADDERSS,SYSTEM_DISPLAY_TIMER_CONTROL_SUCCESS_WINDOW_VAR_ADDERSS,SYSTEM_DISPLAY_TIMER_CONTROL_ERROR_WINDOW_VAR_ADDERSS);
	}

	Buttons_Register(KEY_ENTER_TRG_NUMBER,System_Control_Display_Enter_Window_Buttons_CB);
}

static void System_Display_Delay_Enter_Page_Exit(void){
	dw_input_parameter_hint_window( 0,SYSTEM_DISPLAY_TIMER_CONTROL_WAIT_WINDOW_VAR_ADDERSS,SYSTEM_DISPLAY_TIMER_CONTROL_SUCCESS_WINDOW_VAR_ADDERSS,SYSTEM_DISPLAY_TIMER_CONTROL_ERROR_WINDOW_VAR_ADDERSS);
	//clear_time_cnt(AUTO_EXIT_SETS_PAGE_TO_MAIN_PAGE_TIMER_NUMBER);
}

static void System_Display_Delay_Enter_Page_Task(void){
	if(check_time_arrive(AUTO_EXIT_SETS_PAGE_TO_MAIN_PAGE_TIMER_NUMBER,set_systemcontrol_display_pararm_t.system_para.AutoExitSetsPageTime*1000)){
		Back_Main_Page_Load();
	}
}




/************* 系统参数-系统时间公共回调函数  *******************/
static void System_Control_Display_Set_Buttons_CB( key_Input_Number_Typedef key_number , Key_Trg_Even key_state){
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

static void System_Control_Display_Enter_Window_Buttons_CB( key_Input_Number_Typedef key_number , Key_Trg_Even key_state){
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







