/*
 * hmi_SysControl_CloseDelay.c
 *
 *  Created on: 2023年3月28日
 *      Author: 好
 */

#define LOG_TAG    "hmi_SysControl_CloseDelay"

#include "../himi/sys/hmi_SysControl/hmi_SysControl_CloseDelay.h"



/* 参数初始化*/
static void SystemMenuDateShow_Init(void);
/* 设置菜单显示效果 */
static void System_Delay_Close_SetMenu(MenuShow_t *ptShowInfo);
/********************************************** 切换页面 - 系统参数-系统控制-温度控制-内部温度关闭设置值页面  ***************************************************************/
static void System_Temperature_Delay_Close_Set_Page_Load(void);
static void System_Temperature_Delay_Close_Set_Page_Exit(void);
static void System_Temperature_Delay_Close_Set_Page_Task(void);
/************* 输入参数- 切换页面 - 系统参数-系统控制-温度差控制-内部温度关闭设置值页面  *******************/
static void System_Temperature_Delay_Close_Input_Page_Load(void);
static void System_Temperature_Delay_Close_Input_Page_Exit(void);
static void System_Temperature_Delay_Close_Input_Page_Task(void);
static void System_Temperature_Delay_Close_Input_Buttons_CB(key_Input_Number_Typedef key_number ,Key_Trg_Even key_state);
/********* 保存设置参数- 切换页面 - 系统参数-系统控制-温度差控制-内部温度关闭设置值  ******************/
static void System_Temperature_Delay_Close_Enter_Page_Load(void);
static void System_Temperature_Delay_Close_Enter_Page_Exit(void);
static void System_Temperature_Delay_Close_Enter_Page_Task(void);
/********************************************** 切换页面 - 系统参数-系统控制-温度差控制-外部温度关闭设置值页面  ***************************************************************/
static void System_Humidity_Delay_Close_Set_Page_Load(void);
static void System_Humidity_Delay_Close_Set_Page_Exit(void);
static void System_Humidity_Delay_Close_Set_Page_Task(void);
/************* 输入参数- 系统参数-系统控制-温度控制-外部温度关闭设置值页面  *******************/
static void System_Humidity_Delay_Close_Input_Page_Load(void);
static void System_Humidity_Delay_Close_Input_Page_Exit(void);
static void System_Humidity_Delay_Close_Input_Page_Task(void);
static void System_Humidity_Delay_Close_Input_Buttons_CB(key_Input_Number_Typedef key_number ,Key_Trg_Even key_state);
/********* 保存设置参数- 系统参数-系统控制-温度控制-外部温度关闭值  ******************/
static void System_Humidity_Delay_Close_Enter_Page_Load(void);
static void System_Humidity_Delay_Close_Enter_Page_Exit(void);
static void System_Humidity_Delay_Close_Enter_Page_Task(void);
/********************************************** 切换页面 - 系统参数-系统控制-温度差控制-光照延时关闭时间值设置值页面  ***************************************************************/
static void System_Illumination_Delay_Close_Set_Page_Load(void);
static void System_Illumination_Delay_Close_Set_Page_Exit(void);
static void System_Illumination_Delay_Close_Set_Page_Task(void);
/************* 输入参数- 系统参数-系统控制-温度差控制-光照延时关闭时间值设置值页面  *******************/
static void System_Illumination_Delay_Close_Input_Page_Load(void);
static void System_Illumination_Delay_Close_Input_Page_Exit(void);
static void System_Illumination_Delay_Close_Input_Page_Task(void);
static void System_Illumination_Delay_Close_Input_Buttons_CB(key_Input_Number_Typedef key_number ,Key_Trg_Even key_state);
/********* 保存设置参数- 系统参数-系统控制-温度差控制-光照延时关闭时间值值  ******************/
static void System_Illumination_Delay_Close_Enter_Page_Load(void);
static void System_Illumination_Delay_Close_Enter_Page_Exit(void);
static void System_Illumination_Delay_Close_Enter_Page_Task(void);
/************* 系统参数-系统时间公共回调函数  *******************/
static void System_Delay_Close_Set_Buttons_CB( key_Input_Number_Typedef key_number , Key_Trg_Even key_state);
static void System_Delay_Close_Enter_Window_Buttons_CB( key_Input_Number_Typedef key_number , Key_Trg_Even key_state);

struct set_systemdelay_close_menu_list_pararm{
	system_para_def system_para ;

	ShownMenuDate SY_ShowIntputSysTemperatureDelayCloseFun_t;
	ShownMenuDate SY_ShowIntputSysHumidityDelayCloseFun_t;
	ShownMenuDate SY_ShowIntputSysIlluminationDelayCloseFun_t;

};


static struct set_systemdelay_close_menu_list_pararm set_systemdelay_close_pararm_t;


/******************系统参数-系统控制-系统时间控制设置页面选择*********************************/

/* 系统参数-系统控制-系统时间控制设置菜单*/
static MenuList_t System_delay_close_Set_Menu_Table[] =
{
    {"温度延时关闭时间值", NULL, System_Temperature_Delay_Close_Set_Page_Load, System_Temperature_Delay_Close_Set_Page_Exit, System_Temperature_Delay_Close_Set_Page_Task, NULL},

    {"湿度延时关闭时间值", NULL, System_Humidity_Delay_Close_Set_Page_Load, System_Humidity_Delay_Close_Set_Page_Exit, System_Humidity_Delay_Close_Set_Page_Task, NULL},

    {"光照延时关闭时间值", NULL, System_Illumination_Delay_Close_Set_Page_Load, System_Illumination_Delay_Close_Set_Page_Exit, System_Illumination_Delay_Close_Set_Page_Task, NULL},

    {"返回上级菜单", NULL,  Return_Previous_Menu_Page_Load, NULL, NULL, NULL},

    {"返回主页面", NULL,  Back_Main_Page_Load,   NULL,   NULL, NULL},
};

/* 参数初始化*/
static void SystemMenuDateShow_Init(void){
	set_systemdelay_close_pararm_t.SY_ShowIntputSysTemperatureDelayCloseFun_t = show_system_temperature_delay_close_value_date ;
	set_systemdelay_close_pararm_t.SY_ShowIntputSysHumidityDelayCloseFun_t = show_system_humidity_delay_close_value_date ;
	set_systemdelay_close_pararm_t.SY_ShowIntputSysIlluminationDelayCloseFun_t = show_system_illumination_delay_close_value_date ;

	read_saveenv_cjson_system_parameter(&set_systemdelay_close_pararm_t.system_para);
}


/* 设置菜单显示效果 */
static void System_Delay_Close_SetMenu(MenuShow_t *ptShowInfo){
	show_refresh_time();
	show_eth_connect_state();
}
/********************************************** 系统参数-系统控制-温度控制设置页面  ***************************************************************/
void System_Control_CloseDelay_Page_Load(void){

	log_d("System_Control_CloseDelay_Page_Load ");
	type_slect_move_cursor slect_move_cursor;

	slect_move_cursor.dw_cursor_adderss = SYSTEM_SYS_CLOSE_DELAY_CONTROL_SELECT_CURSOR_ADDERSS ;
	slect_move_cursor.max_slect_move = 4 ;
	slect_move_cursor.min_slect_move = 0 ;
	slect_move_cursor.move_slect_step = 1 ;
	slect_move_cursor.now_slect_move = 0 ;
	slect_cursor_move_init(&slect_move_cursor);  //光标位置初始化
	slect_cursor_move(cursor_default_mode,cursor_null);  //初始化选择设置光标

	dw_show_switching_pages(PAGE_SYSTEM_CONTROL_CLSOEDELAY_SETTING_NUMBER); //切换页面
	Buttons_Register(KEY_UP_TRG_NUMBER,System_Delay_Close_Set_Buttons_CB);
	Buttons_Register(KEY_ENTER_TRG_NUMBER,System_Delay_Close_Set_Buttons_CB);
	Buttons_Register(KEY_DOWN_TRG_NUMBER,System_Delay_Close_Set_Buttons_CB);
	SystemMenuDateShow_Init();
	//clear_time_cnt(AUTO_EXIT_SETS_PAGE_TO_MAIN_PAGE_TIMER_NUMBER);
	Menu_Bind(System_delay_close_Set_Menu_Table, GET_MENU_NUM(System_delay_close_Set_Menu_Table), System_Delay_Close_SetMenu);
}

void System_Control_CloseDelay_Page_Exit(void){
	//clear_time_cnt(AUTO_EXIT_SETS_PAGE_TO_MAIN_PAGE_TIMER_NUMBER);
}

void System_Control_CloseDelay_Page_Task(void){
	if(check_time_arrive(AUTO_EXIT_SETS_PAGE_TO_MAIN_PAGE_TIMER_NUMBER,set_systemdelay_close_pararm_t.system_para.AutoExitSetsPageTime*1000)){
		Back_Main_Page_Load();
	}
}


/********************************************** 切换页面 - 系统参数-系统控制-温度控制-内部温度关闭设置值页面  ***************************************************************/
/* 自动返回主页菜单 */
static MenuList_t System_Temperature_Delay_Close_Menu_Table[] =
{
	{"温度延时关闭值输入框", NULL, System_Temperature_Delay_Close_Input_Page_Load,  System_Temperature_Delay_Close_Input_Page_Exit, System_Temperature_Delay_Close_Input_Page_Task, NULL},

    {"保存设置参数", NULL, System_Temperature_Delay_Close_Enter_Page_Load, System_Temperature_Delay_Close_Enter_Page_Exit,System_Temperature_Delay_Close_Enter_Page_Task, NULL},

    {"返回上级菜单", NULL, Return_Previous_Menu_Page_Load, NULL, NULL, NULL},

    {"返回主页面", NULL,  Back_Main_Page_Load,   NULL,   NULL, NULL},
};

static void System_Temperature_Delay_Close_Set_Page_Load(void){
	type_slect_move_cursor slect_move_cursor;

	slect_move_cursor.dw_cursor_adderss = SYSTEM_TEMPERATURE_DELAY_CLOSE_CONTROL_INTPUT_SELECT_CURSOR_VAR_ADDERSS ;
	slect_move_cursor.max_slect_move = 2 ;
	slect_move_cursor.min_slect_move = 0 ;
	slect_move_cursor.move_slect_step = 1 ;
	slect_move_cursor.now_slect_move = 0 ;
	slect_cursor_move_init(&slect_move_cursor);  		//光标位置初始化
	slect_cursor_move(cursor_refresh_mode,cursor_null);  //关闭输入指示光标

	slect_move_cursor.dw_cursor_adderss = SYSTEM_TEMPERATURE_DELAY_CLOSE_CONTROL_SELECT_CURSOR_ADDERSS ;
	slect_move_cursor.max_slect_move = 3 ;
	slect_move_cursor.min_slect_move = 0 ;
	slect_move_cursor.move_slect_step = 1 ;
	slect_move_cursor.now_slect_move = 0 ;
	slect_cursor_move_init(&slect_move_cursor); 		 			//光标位置初始化
	slect_cursor_move(cursor_default_mode,cursor_null);  			//初始化选择设置光标

	set_systemdelay_close_pararm_t.SY_ShowIntputSysTemperatureDelayCloseFun_t( set_systemdelay_close_pararm_t.system_para.SetCloseTemperatureDelayDateT1 );

	dw_show_switching_pages(PAGE_SYSTEM_TEMPERATURE_DELAY_CLOSE_NUMBER); //切换页面
	Buttons_Register(KEY_UP_TRG_NUMBER,System_Delay_Close_Set_Buttons_CB);
	Buttons_Register(KEY_ENTER_TRG_NUMBER,System_Delay_Close_Set_Buttons_CB);
	Buttons_Register(KEY_DOWN_TRG_NUMBER,System_Delay_Close_Set_Buttons_CB);
	Menu_Bind(System_Temperature_Delay_Close_Menu_Table, GET_MENU_NUM(System_Temperature_Delay_Close_Menu_Table), System_Delay_Close_SetMenu);
}
static void System_Temperature_Delay_Close_Set_Page_Exit(void){
	//clear_time_cnt(AUTO_EXIT_SETS_PAGE_TO_MAIN_PAGE_TIMER_NUMBER);
}
static void System_Temperature_Delay_Close_Set_Page_Task(void){
	if(check_time_arrive(AUTO_EXIT_SETS_PAGE_TO_MAIN_PAGE_TIMER_NUMBER,set_systemdelay_close_pararm_t.system_para.AutoExitSetsPageTime*1000)){
		Back_Main_Page_Load();
	}
}
/************* 输入参数- 切换页面 - 系统参数-系统控制-温度差控制-内部温度关闭设置值页面  *******************/
static void System_Temperature_Delay_Close_Input_Page_Load(void){
	type_slect_move_cursor slect_move_cursor;

	slect_move_cursor.dw_cursor_adderss = SYSTEM_TEMPERATURE_DELAY_CLOSE_CONTROL_SELECT_CURSOR_ADDERSS ;
	slect_move_cursor.max_slect_move = 3 ;
	slect_move_cursor.min_slect_move = 0 ;
	slect_move_cursor.move_slect_step = 1 ;
	slect_move_cursor.now_slect_move = 0 ;
	slect_cursor_move_init(&slect_move_cursor);  //光标位置初始化
	slect_cursor_move(cursor_refresh_mode,cursor_null);  //关闭选择设置光标

	slect_move_cursor.dw_cursor_adderss = SYSTEM_TEMPERATURE_DELAY_CLOSE_CONTROL_INTPUT_SELECT_CURSOR_VAR_ADDERSS ;
	slect_move_cursor.max_slect_move = 2 ;
	slect_move_cursor.min_slect_move = 0 ;
	slect_move_cursor.move_slect_step = 1 ;
	slect_move_cursor.now_slect_move = 0 ;
	slect_cursor_move_init(&slect_move_cursor);  //光标位置初始化
	slect_cursor_move(cursor_default_mode,cursor_null);  //显示初始化输入指示光标位置

	Buttons_Register(KEY_UP_TRG_NUMBER,System_Temperature_Delay_Close_Input_Buttons_CB);
	Buttons_Register(KEY_ENTER_TRG_NUMBER,System_Temperature_Delay_Close_Input_Buttons_CB);
	Buttons_Register(KEY_DOWN_TRG_NUMBER,System_Temperature_Delay_Close_Input_Buttons_CB);
}

static void System_Temperature_Delay_Close_Input_Page_Exit(void){
	//clear_time_cnt(AUTO_EXIT_SETS_PAGE_TO_MAIN_PAGE_TIMER_NUMBER);
}

static void System_Temperature_Delay_Close_Input_Page_Task(void){
	if(check_time_arrive(AUTO_EXIT_SETS_PAGE_TO_MAIN_PAGE_TIMER_NUMBER,set_systemdelay_close_pararm_t.system_para.AutoExitSetsPageTime*1000)){
		Back_Main_Page_Load();
	}
}


static void System_Temperature_Delay_Close_Input_Buttons_CB(key_Input_Number_Typedef key_number ,Key_Trg_Even key_state){
	if(key_state == KEY_CLICK_ACTION){
		//clear_time_cnt(AUTO_EXIT_SETS_PAGE_TO_MAIN_PAGE_TIMER_NUMBER);
		set_systemdelay_close_pararm_t.system_para.SetCloseTemperatureDelayDateT1=user_parameter_adjustment(set_systemdelay_close_pararm_t.system_para.SetCloseTemperatureDelayDateT1, \
				false,3,key_number,set_systemdelay_close_pararm_t.SY_ShowIntputSysTemperatureDelayCloseFun_t);
	}
}


/********* 保存设置参数- 切换页面 - 系统参数-系统控制-温度差控制-内部温度关闭设置值  ******************/
static void System_Temperature_Delay_Close_Enter_Page_Load(void){
	int ret = -1 ;
	type_slect_move_cursor slect_move_cursor;

	slect_move_cursor.dw_cursor_adderss = SYSTEM_IN_TEMPERATURE_CLOSE_CONTROL_SELECT_CURSOR_ADDERSS ;
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
	dw_input_parameter_hint_window( 1 ,SYSTEM_TEMPERATURE_DELAY_CLOSE_CONTROL_WAIT_WINDOW_VAR_ADDERSS,SYSTEM_TEMPERATURE_DELAY_CLOSE_CONTROL_SUCCESS_WINDOW_VAR_ADDERSS,SYSTEM_TEMPERATURE_DELAY_CLOSE_CONTROL_ERROR_WINDOW_VAR_ADDERSS);
	ret = systemparaPoint_amend_config("SetCloseTemperatureDelayDateT1",set_systemdelay_close_pararm_t.system_para.SetCloseTemperatureDelayDateT1);
	if( !ret){
		 //显示成功窗口
		dw_input_parameter_hint_window(2,SYSTEM_TEMPERATURE_DELAY_CLOSE_CONTROL_WAIT_WINDOW_VAR_ADDERSS,SYSTEM_TEMPERATURE_DELAY_CLOSE_CONTROL_SUCCESS_WINDOW_VAR_ADDERSS,SYSTEM_TEMPERATURE_DELAY_CLOSE_CONTROL_ERROR_WINDOW_VAR_ADDERSS);
	}else{
		//显示错误窗口
		dw_input_parameter_hint_window( 3,SYSTEM_TEMPERATURE_DELAY_CLOSE_CONTROL_WAIT_WINDOW_VAR_ADDERSS,SYSTEM_TEMPERATURE_DELAY_CLOSE_CONTROL_SUCCESS_WINDOW_VAR_ADDERSS,SYSTEM_TEMPERATURE_DELAY_CLOSE_CONTROL_ERROR_WINDOW_VAR_ADDERSS);
	}
	Buttons_Register(KEY_ENTER_TRG_NUMBER,System_Delay_Close_Enter_Window_Buttons_CB);
}

static void System_Temperature_Delay_Close_Enter_Page_Exit(void){
	dw_input_parameter_hint_window( 0,SYSTEM_TEMPERATURE_DELAY_CLOSE_CONTROL_WAIT_WINDOW_VAR_ADDERSS,SYSTEM_TEMPERATURE_DELAY_CLOSE_CONTROL_SUCCESS_WINDOW_VAR_ADDERSS,SYSTEM_TEMPERATURE_DELAY_CLOSE_CONTROL_ERROR_WINDOW_VAR_ADDERSS);
	//clear_time_cnt(AUTO_EXIT_SETS_PAGE_TO_MAIN_PAGE_TIMER_NUMBER);
}

static void System_Temperature_Delay_Close_Enter_Page_Task(void){
	if(check_time_arrive(AUTO_EXIT_SETS_PAGE_TO_MAIN_PAGE_TIMER_NUMBER,set_systemdelay_close_pararm_t.system_para.AutoExitSetsPageTime*1000)){
		Back_Main_Page_Load();
	}
}


/********************************************** 切换页面 - 系统参数-系统控制-温度差控制-外部温度关闭设置值页面  ***************************************************************/
/* 自动返回主页菜单 */
static MenuList_t System_Humidity_Delay_Close_Menu_Table[] =
{
	{"湿度延时关闭值输入框", NULL, System_Humidity_Delay_Close_Input_Page_Load, System_Humidity_Delay_Close_Input_Page_Exit,System_Humidity_Delay_Close_Input_Page_Task, NULL},

    {"保存设置参数", NULL, System_Humidity_Delay_Close_Enter_Page_Load, System_Humidity_Delay_Close_Enter_Page_Exit, System_Humidity_Delay_Close_Enter_Page_Task, NULL},

    {"返回上级菜单", NULL,  Return_Previous_Menu_Page_Load, NULL, NULL, NULL},

    {"返回主页面", NULL,  Back_Main_Page_Load,   NULL,   NULL, NULL},
};

static void System_Humidity_Delay_Close_Set_Page_Load(void){
	type_slect_move_cursor slect_move_cursor;

	slect_move_cursor.dw_cursor_adderss = SYSTEM_HUMIDITY_DELAY_CLOSE_CONTROL_INTPUT_SELECT_CURSOR_VAR_ADDERSS ;
	slect_move_cursor.max_slect_move = 2 ;
	slect_move_cursor.min_slect_move = 0 ;
	slect_move_cursor.move_slect_step = 1 ;
	slect_move_cursor.now_slect_move = 0 ;
	slect_cursor_move_init(&slect_move_cursor);  		//光标位置初始化
	slect_cursor_move(cursor_refresh_mode,cursor_null);  //关闭输入指示光标

	slect_move_cursor.dw_cursor_adderss = SYSTEM_HUMIDITY_DELAY_CLOSE_CONTROL_SELECT_CURSOR_ADDERSS ;
	slect_move_cursor.max_slect_move = 3 ;
	slect_move_cursor.min_slect_move = 0 ;
	slect_move_cursor.move_slect_step = 1 ;
	slect_move_cursor.now_slect_move = 0 ;
	slect_cursor_move_init(&slect_move_cursor); 		 			//光标位置初始化
	slect_cursor_move(cursor_default_mode,cursor_null);  			//初始化选择设置光标

	set_systemdelay_close_pararm_t.SY_ShowIntputSysHumidityDelayCloseFun_t( set_systemdelay_close_pararm_t.system_para.SetCloseHumidityDelayDateT3 );

	dw_show_switching_pages(PAGE_SYSTEM_HUMIDITY_DELAY_CLOSE_NUMBER); //切换页面
	Buttons_Register(KEY_UP_TRG_NUMBER,System_Delay_Close_Set_Buttons_CB);
	Buttons_Register(KEY_ENTER_TRG_NUMBER,System_Delay_Close_Set_Buttons_CB);
	Buttons_Register(KEY_DOWN_TRG_NUMBER,System_Delay_Close_Set_Buttons_CB);
	Menu_Bind(System_Humidity_Delay_Close_Menu_Table, GET_MENU_NUM(System_Humidity_Delay_Close_Menu_Table), System_Delay_Close_SetMenu);
}
static void System_Humidity_Delay_Close_Set_Page_Exit(void){
	//clear_time_cnt(AUTO_EXIT_SETS_PAGE_TO_MAIN_PAGE_TIMER_NUMBER);
}
static void System_Humidity_Delay_Close_Set_Page_Task(void){
	if(check_time_arrive(AUTO_EXIT_SETS_PAGE_TO_MAIN_PAGE_TIMER_NUMBER,set_systemdelay_close_pararm_t.system_para.AutoExitSetsPageTime*1000)){
		Back_Main_Page_Load();
	}
}
/************* 输入参数- 系统参数-系统控制-温度控制-外部温度关闭设置值页面  *******************/
static void System_Humidity_Delay_Close_Input_Page_Load(void){
	type_slect_move_cursor slect_move_cursor;

	slect_move_cursor.dw_cursor_adderss = SYSTEM_HUMIDITY_DELAY_CLOSE_CONTROL_SELECT_CURSOR_ADDERSS ;
	slect_move_cursor.max_slect_move = 3 ;
	slect_move_cursor.min_slect_move = 0 ;
	slect_move_cursor.move_slect_step = 1 ;
	slect_move_cursor.now_slect_move = 0 ;
	slect_cursor_move_init(&slect_move_cursor);  //光标位置初始化
	slect_cursor_move(cursor_refresh_mode,cursor_null);  //关闭选择设置光标

	slect_move_cursor.dw_cursor_adderss = SYSTEM_HUMIDITY_DELAY_CLOSE_CONTROL_INTPUT_SELECT_CURSOR_VAR_ADDERSS ;
	slect_move_cursor.max_slect_move = 2 ;
	slect_move_cursor.min_slect_move = 0 ;
	slect_move_cursor.move_slect_step = 1 ;
	slect_move_cursor.now_slect_move = 0 ;
	slect_cursor_move_init(&slect_move_cursor);  //光标位置初始化
	slect_cursor_move(cursor_default_mode,cursor_null);  //显示初始化输入指示光标位置


	Buttons_Register(KEY_UP_TRG_NUMBER,System_Humidity_Delay_Close_Input_Buttons_CB);
	Buttons_Register(KEY_ENTER_TRG_NUMBER,System_Humidity_Delay_Close_Input_Buttons_CB);
	Buttons_Register(KEY_DOWN_TRG_NUMBER,System_Humidity_Delay_Close_Input_Buttons_CB);
}

static void System_Humidity_Delay_Close_Input_Page_Exit(void){
	//clear_time_cnt(AUTO_EXIT_SETS_PAGE_TO_MAIN_PAGE_TIMER_NUMBER);
}

static void System_Humidity_Delay_Close_Input_Page_Task(void){
	if(check_time_arrive(AUTO_EXIT_SETS_PAGE_TO_MAIN_PAGE_TIMER_NUMBER,set_systemdelay_close_pararm_t.system_para.AutoExitSetsPageTime*1000)){
		Back_Main_Page_Load();
	}
}


static void System_Humidity_Delay_Close_Input_Buttons_CB(key_Input_Number_Typedef key_number ,Key_Trg_Even key_state){
	if(key_state == KEY_CLICK_ACTION){
		clear_time_cnt(AUTO_EXIT_SETS_PAGE_TO_MAIN_PAGE_TIMER_NUMBER);
		set_systemdelay_close_pararm_t.system_para.SetCloseHumidityDelayDateT3=user_parameter_adjustment(set_systemdelay_close_pararm_t.system_para.SetCloseHumidityDelayDateT3, \
				false,3,key_number,set_systemdelay_close_pararm_t.SY_ShowIntputSysHumidityDelayCloseFun_t);
	}
}


/********* 保存设置参数- 系统参数-系统控制-温度控制-外部温度关闭值  ******************/
static void System_Humidity_Delay_Close_Enter_Page_Load(void){
	int ret = -1 ;
	type_slect_move_cursor slect_move_cursor;

	slect_move_cursor.dw_cursor_adderss = SYSTEM_EX_TEMPERATURE_CLOSE_CONTROL_SELECT_CURSOR_ADDERSS ;
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
	dw_input_parameter_hint_window( 1 ,SYSTEM_HUMIDITY_DELAY_CLOSE_CONTROL_WAIT_WINDOW_VAR_ADDERSS,SYSTEM_HUMIDITY_DELAY_CLOSE_CONTROL_SUCCESS_WINDOW_VAR_ADDERSS,SYSTEM_HUMIDITY_DELAY_CLOSE_CONTROL_ERROR_WINDOW_VAR_ADDERSS);
	ret = systemparaPoint_amend_config("SetCloseHumidityDelayDateT3",set_systemdelay_close_pararm_t.system_para.SetCloseHumidityDelayDateT3);
	if( !ret){
		 //显示成功窗口
		dw_input_parameter_hint_window(2 ,SYSTEM_HUMIDITY_DELAY_CLOSE_CONTROL_WAIT_WINDOW_VAR_ADDERSS,SYSTEM_HUMIDITY_DELAY_CLOSE_CONTROL_SUCCESS_WINDOW_VAR_ADDERSS,SYSTEM_HUMIDITY_DELAY_CLOSE_CONTROL_ERROR_WINDOW_VAR_ADDERSS);
	}else{
		//显示错误窗口
		dw_input_parameter_hint_window( 3,SYSTEM_HUMIDITY_DELAY_CLOSE_CONTROL_WAIT_WINDOW_VAR_ADDERSS,SYSTEM_HUMIDITY_DELAY_CLOSE_CONTROL_SUCCESS_WINDOW_VAR_ADDERSS,SYSTEM_HUMIDITY_DELAY_CLOSE_CONTROL_ERROR_WINDOW_VAR_ADDERSS);
	}

	Buttons_Register(KEY_ENTER_TRG_NUMBER,System_Delay_Close_Enter_Window_Buttons_CB);
}

static void System_Humidity_Delay_Close_Enter_Page_Exit(void){
	dw_input_parameter_hint_window( 0,SYSTEM_HUMIDITY_DELAY_CLOSE_CONTROL_WAIT_WINDOW_VAR_ADDERSS,SYSTEM_HUMIDITY_DELAY_CLOSE_CONTROL_SUCCESS_WINDOW_VAR_ADDERSS,SYSTEM_HUMIDITY_DELAY_CLOSE_CONTROL_ERROR_WINDOW_VAR_ADDERSS);
	//clear_time_cnt(AUTO_EXIT_SETS_PAGE_TO_MAIN_PAGE_TIMER_NUMBER);
}

static void System_Humidity_Delay_Close_Enter_Page_Task(void){
	if(check_time_arrive(AUTO_EXIT_SETS_PAGE_TO_MAIN_PAGE_TIMER_NUMBER,set_systemdelay_close_pararm_t.system_para.AutoExitSetsPageTime*1000)){
		Back_Main_Page_Load();
	}
}


/********************************************** 切换页面 - 系统参数-系统控制-温度差控制-光照延时关闭时间值设置值页面  ***************************************************************/
/* 自动返回主页菜单 */
static MenuList_t System_Illumination_Delay_Close_Menu_Table[] =
{
	{"光照延时关闭时间值输入框", NULL, System_Illumination_Delay_Close_Input_Page_Load, System_Illumination_Delay_Close_Input_Page_Exit,System_Illumination_Delay_Close_Input_Page_Task, NULL},

    {"保存设置参数", NULL, System_Illumination_Delay_Close_Enter_Page_Load, System_Illumination_Delay_Close_Enter_Page_Exit, System_Illumination_Delay_Close_Enter_Page_Task, NULL},

    {"返回上级菜单", NULL,  Return_Previous_Menu_Page_Load, NULL, NULL, NULL},

    {"返回主页面", NULL,  Back_Main_Page_Load,   NULL,   NULL, NULL},
};

static void System_Illumination_Delay_Close_Set_Page_Load(void){
	type_slect_move_cursor slect_move_cursor;

	slect_move_cursor.dw_cursor_adderss = SYSTEM_ILLUMIAATION_DELAY_CLOSE_CONTROL_INTPUT_SELECT_CURSOR_VAR_ADDERSS ;
	slect_move_cursor.max_slect_move = 2 ;
	slect_move_cursor.min_slect_move = 0 ;
	slect_move_cursor.move_slect_step = 1 ;
	slect_move_cursor.now_slect_move = 0 ;
	slect_cursor_move_init(&slect_move_cursor);  		//光标位置初始化
	slect_cursor_move(cursor_refresh_mode,cursor_null);  //关闭输入指示光标

	slect_move_cursor.dw_cursor_adderss = SYSTEM_ILLUMIAATION_DELAY_CLOSE_CONTROL_SELECT_CURSOR_ADDERSS ;
	slect_move_cursor.max_slect_move = 3 ;
	slect_move_cursor.min_slect_move = 0 ;
	slect_move_cursor.move_slect_step = 1 ;
	slect_move_cursor.now_slect_move = 0 ;
	slect_cursor_move_init(&slect_move_cursor); 		 			//光标位置初始化
	slect_cursor_move(cursor_default_mode,cursor_null);  			//初始化选择设置光标

	set_systemdelay_close_pararm_t.SY_ShowIntputSysIlluminationDelayCloseFun_t( set_systemdelay_close_pararm_t.system_para.SetCloseIlluminationDelayDateT2 );

	dw_show_switching_pages(PAGE_SYSTEM_ILLUMINATION_DELAY_CLOSE_NUMBER); //切换页面
	Buttons_Register(KEY_UP_TRG_NUMBER,System_Delay_Close_Set_Buttons_CB);
	Buttons_Register(KEY_ENTER_TRG_NUMBER,System_Delay_Close_Set_Buttons_CB);
	Buttons_Register(KEY_DOWN_TRG_NUMBER,System_Delay_Close_Set_Buttons_CB);
	Menu_Bind(System_Illumination_Delay_Close_Menu_Table, GET_MENU_NUM(System_Illumination_Delay_Close_Menu_Table), System_Delay_Close_SetMenu);
}
static void System_Illumination_Delay_Close_Set_Page_Exit(void){
	//clear_time_cnt(AUTO_EXIT_SETS_PAGE_TO_MAIN_PAGE_TIMER_NUMBER);
}
static void System_Illumination_Delay_Close_Set_Page_Task(void){
	if(check_time_arrive(AUTO_EXIT_SETS_PAGE_TO_MAIN_PAGE_TIMER_NUMBER,set_systemdelay_close_pararm_t.system_para.AutoExitSetsPageTime*1000)){
		Back_Main_Page_Load();
	}
}
/************* 输入参数- 系统参数-系统控制-温度差控制-光照延时关闭时间值设置值页面  *******************/
static void System_Illumination_Delay_Close_Input_Page_Load(void){
	type_slect_move_cursor slect_move_cursor;

	slect_move_cursor.dw_cursor_adderss = SYSTEM_ILLUMIAATION_DELAY_CLOSE_CONTROL_SELECT_CURSOR_ADDERSS ;
	slect_move_cursor.max_slect_move = 3 ;
	slect_move_cursor.min_slect_move = 0 ;
	slect_move_cursor.move_slect_step = 1 ;
	slect_move_cursor.now_slect_move = 0 ;
	slect_cursor_move_init(&slect_move_cursor);  //光标位置初始化
	slect_cursor_move(cursor_refresh_mode,cursor_null);  //关闭选择设置光标

	slect_move_cursor.dw_cursor_adderss = SYSTEM_ILLUMIAATION_DELAY_CLOSE_CONTROL_INTPUT_SELECT_CURSOR_VAR_ADDERSS ;
	slect_move_cursor.max_slect_move = 2 ;
	slect_move_cursor.min_slect_move = 0 ;
	slect_move_cursor.move_slect_step = 1 ;
	slect_move_cursor.now_slect_move = 0 ;
	slect_cursor_move_init(&slect_move_cursor);  //光标位置初始化
	slect_cursor_move(cursor_default_mode,cursor_null);  //显示初始化输入指示光标位置


	Buttons_Register(KEY_UP_TRG_NUMBER,System_Illumination_Delay_Close_Input_Buttons_CB);
	Buttons_Register(KEY_ENTER_TRG_NUMBER,System_Illumination_Delay_Close_Input_Buttons_CB);
	Buttons_Register(KEY_DOWN_TRG_NUMBER,System_Illumination_Delay_Close_Input_Buttons_CB);
}

static void System_Illumination_Delay_Close_Input_Page_Exit(void){
	//clear_time_cnt(AUTO_EXIT_SETS_PAGE_TO_MAIN_PAGE_TIMER_NUMBER);
}

static void System_Illumination_Delay_Close_Input_Page_Task(void){
	if(check_time_arrive(AUTO_EXIT_SETS_PAGE_TO_MAIN_PAGE_TIMER_NUMBER,set_systemdelay_close_pararm_t.system_para.AutoExitSetsPageTime*1000)){
		Back_Main_Page_Load();
	}
}


static void System_Illumination_Delay_Close_Input_Buttons_CB(key_Input_Number_Typedef key_number ,Key_Trg_Even key_state){
	if(key_state == KEY_CLICK_ACTION){
		//clear_time_cnt(AUTO_EXIT_SETS_PAGE_TO_MAIN_PAGE_TIMER_NUMBER);
		set_systemdelay_close_pararm_t.system_para.SetCloseIlluminationDelayDateT2=user_parameter_adjustment(set_systemdelay_close_pararm_t.system_para.SetCloseIlluminationDelayDateT2, \
				false,3,key_number,set_systemdelay_close_pararm_t.SY_ShowIntputSysIlluminationDelayCloseFun_t);
	}
}


/********* 保存设置参数- 系统参数-系统控制-温度差控制-光照延时关闭时间值值  ******************/
static void System_Illumination_Delay_Close_Enter_Page_Load(void){
	int ret = -1 ;
	type_slect_move_cursor slect_move_cursor;

	slect_move_cursor.dw_cursor_adderss = SYSTEM_ILLUMIAATION_DELAY_CLOSE_CONTROL_SELECT_CURSOR_ADDERSS ;
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
	dw_input_parameter_hint_window( 1 ,SYSTEM_ILLUMIAATION_DELAY_CLOSE_CONTROL_WAIT_WINDOW_VAR_ADDERSS,SYSTEM_ILLUMIAATION_DELAY_CLOSE_CONTROL_SUCCESS_WINDOW_VAR_ADDERSS,SYSTEM_ILLUMIAATION_DELAY_CLOSE_CONTROL_ERROR_WINDOW_VAR_ADDERSS);
	ret = systemparaPoint_amend_config("SetCloseIlluminationDelayDateT2",set_systemdelay_close_pararm_t.system_para.SetCloseIlluminationDelayDateT2);
	if( !ret){
		 //显示成功窗口
		dw_input_parameter_hint_window(2 ,SYSTEM_ILLUMIAATION_DELAY_CLOSE_CONTROL_WAIT_WINDOW_VAR_ADDERSS,SYSTEM_ILLUMIAATION_DELAY_CLOSE_CONTROL_SUCCESS_WINDOW_VAR_ADDERSS,SYSTEM_ILLUMIAATION_DELAY_CLOSE_CONTROL_ERROR_WINDOW_VAR_ADDERSS);
	}else{
		//显示错误窗口
		dw_input_parameter_hint_window( 3,SYSTEM_ILLUMIAATION_DELAY_CLOSE_CONTROL_WAIT_WINDOW_VAR_ADDERSS,SYSTEM_ILLUMIAATION_DELAY_CLOSE_CONTROL_SUCCESS_WINDOW_VAR_ADDERSS,SYSTEM_ILLUMIAATION_DELAY_CLOSE_CONTROL_ERROR_WINDOW_VAR_ADDERSS);
	}
	Buttons_Register(KEY_ENTER_TRG_NUMBER,System_Delay_Close_Enter_Window_Buttons_CB);
}

static void System_Illumination_Delay_Close_Enter_Page_Exit(void){
	dw_input_parameter_hint_window( 0,SYSTEM_ILLUMIAATION_DELAY_CLOSE_CONTROL_WAIT_WINDOW_VAR_ADDERSS,SYSTEM_ILLUMIAATION_DELAY_CLOSE_CONTROL_SUCCESS_WINDOW_VAR_ADDERSS,SYSTEM_ILLUMIAATION_DELAY_CLOSE_CONTROL_ERROR_WINDOW_VAR_ADDERSS);
	//clear_time_cnt(AUTO_EXIT_SETS_PAGE_TO_MAIN_PAGE_TIMER_NUMBER);
}

static void System_Illumination_Delay_Close_Enter_Page_Task(void){
	if(check_time_arrive(AUTO_EXIT_SETS_PAGE_TO_MAIN_PAGE_TIMER_NUMBER,set_systemdelay_close_pararm_t.system_para.AutoExitSetsPageTime*1000)){
		Back_Main_Page_Load();
	}
}




/************* 系统参数-系统时间公共回调函数  *******************/
static void System_Delay_Close_Set_Buttons_CB( key_Input_Number_Typedef key_number , Key_Trg_Even key_state){
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

static void System_Delay_Close_Enter_Window_Buttons_CB( key_Input_Number_Typedef key_number , Key_Trg_Even key_state){
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




