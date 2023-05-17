/*
 * hmi_smoke.c
 *
 *  Created on: 2023年3月17日
 *      Author: 好
 */

#define LOG_TAG    "internal/hmi_smoke"

#include "../himi/internal/hmi_smoke.h"

/* 设置菜单显示效果 */
static void Smoke_SetMenu(  MenuShow_t *ptShowInfo);
static void MenuDateShow_Init(void);
static void In_Smoke_Acquisition_Rate_Page_Load(void);
static void In_Smoke_Acquisition_Rate_Page_Exit(void);
static void In_Smoke_Acquisition_Rate_Page_Task(void);
/************* 输入参数- 内部烟雾传感器温湿度采样速率页面  *******************/
static void In_Smoke_Sample_Rate_Input_Page_Load(void);
static void In_Smoke_Sample_Rate_Input_Page_Exit(void);
static void In_Smoke_Sample_Rate_Input_Page_Task(void);
static void Hmi_Internal_Smoke_Sample_Rate_Input_Buttons_CB(key_Input_Number_Typedef key_number ,Key_Trg_Even key_state);
/********* 保存设置参数- 内部烟雾传感器烟雾采样速率  ******************/
static void In_Smoke_Sample_Rate_Enter_Page_Load(void);
static void In_Smoke_Sample_Rate_Enter_Page_Exit(void);
static void In_Smoke_Sample_Rate_Enter_Page_Task(void);
/************* 内部烟雾传感器公共回调函数  *******************/
static void Smoke_Slcet_Set_Buttons_CB( key_Input_Number_Typedef key_number , Key_Trg_Even key_state);
static void Smoke_Slcet_Enter_Window_Buttons_CB( key_Input_Number_Typedef key_number , Key_Trg_Even key_state);

struct set_in_smoke_menu_list_pararm{
	int auto_exit_sets_page_to_main_time ;  //自动返回时间
	internal_para_def inernal_para ;
	ShownMenuDate In_Smoke_ShowSampleRateDate ;
};


static struct set_in_smoke_menu_list_pararm set_in_smoke_menu_list_pararm_t ;

/******************内部参数-烟雾传感器设置页面选择*********************************/
/******************内部参数-烟雾传感器设置页面选择*********************************/

/* 内部烟雾传感器设置菜单*/
static MenuList_t Internal_Smoke_Set_Menu_Table[] =
{
    {"烟雾采集速率", NULL,  In_Smoke_Acquisition_Rate_Page_Load, In_Smoke_Acquisition_Rate_Page_Exit, In_Smoke_Acquisition_Rate_Page_Task, NULL},

    {"返回上级菜单", NULL,  Return_Previous_Menu_Page_Load, NULL, NULL, NULL},

    {"返回主页面", NULL,  Back_Main_Page_Load,   NULL,   NULL, NULL},
};

/* 设置菜单显示效果 */
static void Smoke_SetMenu(  MenuShow_t *ptShowInfo){
	show_refresh_time();
	show_eth_connect_state();
}

static void MenuDateShow_Init(void){
	system_para_def system_para_t ;

	set_in_smoke_menu_list_pararm_t.In_Smoke_ShowSampleRateDate = show_in_smoke_sample_rate_date ;//显示烟雾采集速率
	read_saveenv_cjson_system_parameter(&system_para_t);
	set_in_smoke_menu_list_pararm_t.auto_exit_sets_page_to_main_time = system_para_t.AutoExitSetsPageTime;
}


/********************************************** 切换页面 - 内部烟雾传感器选择设置页面  ***************************************************************/
void Internal_Smoke_Setting_Page_Load(void){

	log_d("Internal_Smoke_Setting_Page_Load ");
	type_slect_move_cursor slect_move_cursor;
	slect_move_cursor.dw_cursor_adderss = INTERNAL_SMOKE_DEV_SETTING_CURSOR_ADDERSS ;
	slect_move_cursor.max_slect_move = 2 ;
	slect_move_cursor.min_slect_move = 0 ;
	slect_move_cursor.move_slect_step = 1 ;
	slect_move_cursor.now_slect_move = 0 ;
	slect_cursor_move_init(&slect_move_cursor);  //光标位置初始化
	dw_show_switching_pages(PAGE_INTERNAL_SMOKE_SETTING_NUMBER); //切换页面
	slect_cursor_move(cursor_default_mode,cursor_null);  //初始化选择设置光标
	Buttons_Register(KEY_UP_TRG_NUMBER,Smoke_Slcet_Set_Buttons_CB);
	Buttons_Register(KEY_ENTER_TRG_NUMBER,Smoke_Slcet_Set_Buttons_CB);
	Buttons_Register(KEY_DOWN_TRG_NUMBER,Smoke_Slcet_Set_Buttons_CB);
	MenuDateShow_Init();
	//clear_time_cnt(AUTO_EXIT_SETS_PAGE_TO_MAIN_PAGE_TIMER_NUMBER);
	Menu_Bind(Internal_Smoke_Set_Menu_Table, GET_MENU_NUM(Internal_Smoke_Set_Menu_Table), Smoke_SetMenu);
}

void Internal_Smoke_Setting_Page_Exit(void){
	//clear_time_cnt(AUTO_EXIT_SETS_PAGE_TO_MAIN_PAGE_TIMER_NUMBER);
}

void Internal_Smoke_Setting_Page_Task(void){
	if(check_time_arrive(AUTO_EXIT_SETS_PAGE_TO_MAIN_PAGE_TIMER_NUMBER,set_in_smoke_menu_list_pararm_t.auto_exit_sets_page_to_main_time*1000)){
		Back_Main_Page_Load();
		//clear_time_cnt(AUTO_EXIT_SETS_PAGE_TO_MAIN_PAGE_TIMER_NUMBER);
	}
}


/********************************************** 切换页面 - 内部烟雾传感器烟雾采集速率页面  ***************************************************************/
/* 内部烟雾传感器烟雾采集速率菜单 */
static MenuList_t Internal_Smoke_Sample_Rate_Menu_Table[] =
{
	{"参数输入框", NULL, In_Smoke_Sample_Rate_Input_Page_Load, In_Smoke_Sample_Rate_Input_Page_Exit, In_Smoke_Sample_Rate_Input_Page_Task, NULL},

    {"保存设置参数", NULL, In_Smoke_Sample_Rate_Enter_Page_Load, In_Smoke_Sample_Rate_Enter_Page_Exit, In_Smoke_Sample_Rate_Enter_Page_Task, NULL},

    {"返回上级菜单", NULL,  Return_Previous_Menu_Page_Load, NULL, NULL, NULL},

    {"返回主页面", NULL,  Back_Main_Page_Load,   NULL,   NULL, NULL},
};


static void In_Smoke_Acquisition_Rate_Page_Load(void){
	type_slect_move_cursor slect_move_cursor;

	slect_move_cursor.dw_cursor_adderss = INTERNAL_SMOKE_SAMPLE_RATE_INPUT_SELECT_CURSOR_ADDERSS ;
	slect_move_cursor.max_slect_move = 1 ;
	slect_move_cursor.min_slect_move = 0 ;
	slect_move_cursor.move_slect_step = 1 ;
	slect_move_cursor.now_slect_move = 0 ;
	slect_cursor_move_init(&slect_move_cursor);  		//输入指示光标位置初始化
	slect_cursor_move(cursor_refresh_mode,cursor_null);  //关闭输入指示光标
	slect_move_cursor.dw_cursor_adderss = INTERNAL_SMOKE_SAMPLE_RATE_SELECT_CURSOR_ADDERSS ;
	slect_move_cursor.max_slect_move = 3 ;
	slect_move_cursor.min_slect_move = 0 ;
	slect_move_cursor.move_slect_step = 1 ;
	slect_move_cursor.now_slect_move = 0 ;
	slect_cursor_move_init(&slect_move_cursor); 		 			//光标位置初始化
	slect_cursor_move(cursor_default_mode,cursor_null);  			//初始化选择设置光标
	read_saveenv_cjson_internal_parameter(&set_in_smoke_menu_list_pararm_t.inernal_para);
	set_in_smoke_menu_list_pararm_t.In_Smoke_ShowSampleRateDate(set_in_smoke_menu_list_pararm_t.inernal_para.InternalSmokeSampleRate ); //显示采样速率
	dw_show_switching_pages(PAGE_INTERNAL_SMOKE_SAMPLE_RATE_SETTING_NUMBER); //切换页面
	Buttons_Register(KEY_UP_TRG_NUMBER,Smoke_Slcet_Set_Buttons_CB);
	Buttons_Register(KEY_ENTER_TRG_NUMBER,Smoke_Slcet_Set_Buttons_CB);
	Buttons_Register(KEY_DOWN_TRG_NUMBER,Smoke_Slcet_Set_Buttons_CB);
	Menu_Bind(Internal_Smoke_Sample_Rate_Menu_Table, GET_MENU_NUM(Internal_Smoke_Sample_Rate_Menu_Table), Smoke_SetMenu);
}

static void In_Smoke_Acquisition_Rate_Page_Exit(void){
	//clear_time_cnt(AUTO_EXIT_SETS_PAGE_TO_MAIN_PAGE_TIMER_NUMBER);
}


static void In_Smoke_Acquisition_Rate_Page_Task(void){
	if(check_time_arrive(AUTO_EXIT_SETS_PAGE_TO_MAIN_PAGE_TIMER_NUMBER,set_in_smoke_menu_list_pararm_t.auto_exit_sets_page_to_main_time*1000)){
		Back_Main_Page_Load();
		//clear_time_cnt(AUTO_EXIT_SETS_PAGE_TO_MAIN_PAGE_TIMER_NUMBER);
	}
}


/************* 输入参数- 内部烟雾传感器温湿度采样速率页面  *******************/
static void In_Smoke_Sample_Rate_Input_Page_Load(void){
	type_slect_move_cursor slect_move_cursor;

	slect_move_cursor.dw_cursor_adderss = INTERNAL_SMOKE_SAMPLE_RATE_SELECT_CURSOR_ADDERSS ;
	slect_move_cursor.max_slect_move = 3 ;
	slect_move_cursor.min_slect_move = 0 ;
	slect_move_cursor.move_slect_step = 1 ;
	slect_move_cursor.now_slect_move = 0 ;
	slect_cursor_move_init(&slect_move_cursor);  //光标位置初始化
	slect_cursor_move(cursor_refresh_mode,cursor_null);  //关闭选择设置光标
	slect_move_cursor.dw_cursor_adderss = INTERNAL_SMOKE_SAMPLE_RATE_INPUT_SELECT_CURSOR_ADDERSS ;
	slect_move_cursor.max_slect_move = 1 ;
	slect_move_cursor.min_slect_move = 0 ;
	slect_move_cursor.move_slect_step = 1 ;
	slect_move_cursor.now_slect_move = 0 ;
	slect_cursor_move_init(&slect_move_cursor);  //光标位置初始化
	slect_cursor_move(cursor_default_mode,cursor_null);  //显示初始化输入指示光标位置
	Buttons_Register(KEY_UP_TRG_NUMBER,Hmi_Internal_Smoke_Sample_Rate_Input_Buttons_CB);
	Buttons_Register(KEY_ENTER_TRG_NUMBER,Hmi_Internal_Smoke_Sample_Rate_Input_Buttons_CB);
	Buttons_Register(KEY_DOWN_TRG_NUMBER,Hmi_Internal_Smoke_Sample_Rate_Input_Buttons_CB);
}

static void In_Smoke_Sample_Rate_Input_Page_Exit(void){
	//clear_time_cnt(AUTO_EXIT_SETS_PAGE_TO_MAIN_PAGE_TIMER_NUMBER);
}

static void In_Smoke_Sample_Rate_Input_Page_Task(void){
	if(check_time_arrive(AUTO_EXIT_SETS_PAGE_TO_MAIN_PAGE_TIMER_NUMBER,set_in_smoke_menu_list_pararm_t.auto_exit_sets_page_to_main_time*1000)){
		Back_Main_Page_Load();
		//clear_time_cnt(AUTO_EXIT_SETS_PAGE_TO_MAIN_PAGE_TIMER_NUMBER);
	}
}

static void Hmi_Internal_Smoke_Sample_Rate_Input_Buttons_CB(key_Input_Number_Typedef key_number ,Key_Trg_Even key_state){
	if(key_state == KEY_CLICK_ACTION){
		//clear_time_cnt(AUTO_EXIT_SETS_PAGE_TO_MAIN_PAGE_TIMER_NUMBER);
		set_in_smoke_menu_list_pararm_t.inernal_para.InternalSmokeSampleRate=user_parameter_adjustment(set_in_smoke_menu_list_pararm_t.inernal_para.InternalSmokeSampleRate,0,2,key_number,set_in_smoke_menu_list_pararm_t.In_Smoke_ShowSampleRateDate);
	}
}


/********* 保存设置参数- 内部烟雾传感器烟雾采样速率  ******************/
static void In_Smoke_Sample_Rate_Enter_Page_Load(void){
	int ret = -1 ;
	type_slect_move_cursor slect_move_cursor;
	slect_move_cursor.dw_cursor_adderss = INTERNAL_SMOKE_SAMPLE_RATE_SELECT_CURSOR_ADDERSS ;
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
	dw_input_parameter_hint_window( 1 ,INTERNAL_SMOKE_SAMPLE_RATE_WAIT_WINDOW_VAR_ADDERSS,INTERNAL_SMOKE_SAMPLE_RATE_SUCCESS_WINDOW_VAR_ADDERSS,INTERNAL_SMOKE_SAMPLE_RATE_ERROR_WINDOW_VAR_ADDERSS);
	ret = internalparaPoint_amend_config("InternalSmokeSampleRate",set_in_smoke_menu_list_pararm_t.inernal_para.InternalSmokeSampleRate);
	if( !ret){
		 //显示成功窗口
		dw_input_parameter_hint_window(2,INTERNAL_SMOKE_SAMPLE_RATE_WAIT_WINDOW_VAR_ADDERSS,INTERNAL_SMOKE_SAMPLE_RATE_SUCCESS_WINDOW_VAR_ADDERSS,INTERNAL_SMOKE_SAMPLE_RATE_ERROR_WINDOW_VAR_ADDERSS);
	}else{
		//显示错误窗口
		dw_input_parameter_hint_window( 3 ,INTERNAL_SMOKE_SAMPLE_RATE_WAIT_WINDOW_VAR_ADDERSS,INTERNAL_SMOKE_SAMPLE_RATE_SUCCESS_WINDOW_VAR_ADDERSS,INTERNAL_SMOKE_SAMPLE_RATE_ERROR_WINDOW_VAR_ADDERSS);
	}
	Buttons_Register(KEY_ENTER_TRG_NUMBER,Smoke_Slcet_Enter_Window_Buttons_CB);
}

static void In_Smoke_Sample_Rate_Enter_Page_Exit(void){
	//清除窗口
	dw_input_parameter_hint_window( 0 ,INTERNAL_SMOKE_SAMPLE_RATE_WAIT_WINDOW_VAR_ADDERSS,INTERNAL_SMOKE_SAMPLE_RATE_SUCCESS_WINDOW_VAR_ADDERSS,INTERNAL_SMOKE_SAMPLE_RATE_ERROR_WINDOW_VAR_ADDERSS);
	//clear_time_cnt(AUTO_EXIT_SETS_PAGE_TO_MAIN_PAGE_TIMER_NUMBER);
}

static void In_Smoke_Sample_Rate_Enter_Page_Task(void){
	if(check_time_arrive(AUTO_EXIT_SETS_PAGE_TO_MAIN_PAGE_TIMER_NUMBER,set_in_smoke_menu_list_pararm_t.auto_exit_sets_page_to_main_time*1000)){
		Back_Main_Page_Load();
		//clear_time_cnt(AUTO_EXIT_SETS_PAGE_TO_MAIN_PAGE_TIMER_NUMBER);
	}
}


/************* 内部烟雾传感器公共回调函数  *******************/
static void Smoke_Slcet_Set_Buttons_CB( key_Input_Number_Typedef key_number , Key_Trg_Even key_state){
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

static void Smoke_Slcet_Enter_Window_Buttons_CB( key_Input_Number_Typedef key_number , Key_Trg_Even key_state){
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


