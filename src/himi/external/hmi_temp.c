/*
 * hmi_temp_set.c
 *
 *  Created on: 2023年2月13日
 *      Author: 好
 */

#define LOG_TAG    "external/hmi_temp"

#include "../himi/external/hmi_temp.h"


struct set_ex_temp_menu_list_pararm{
	int auto_exit_sets_page_to_main_time ;  //自动返回时间
	external_para_def external_para ;
	ShownMenuDate Ex_Temp_ShowCompensationDate_t;
	ShownMenuDate Ex_Temp_ShowAlarmThresholdDate ;
	ShownMenuDate EX_Temp_ShowSampleRateDate ;
};


static struct set_ex_temp_menu_list_pararm set_ex_temp_menu_list_pararm_t ;



static void MenuDateShow_Init(void);
/* 设置地址复位初始化*/
static void Device_Addr_Reversion_Init(void);
/* 设置地址复位执行函数*/
static void Ex_Temp_Setting_Dev_Transducer_Reset_Addr(void);
 /******************外界参数-温度传感器设置页面选择*********************************/
 /* 设置菜单显示效果 */
 static void Humiture_SetMenu(  MenuShow_t *ptShowInfo);
 /********************************************** 切换页面 - 外界温度传感器温度校验补偿页面  ***************************************************************/
 static void Ex_Temp_Compensation_Page_Load(void);
 static void Ex_Temp_Compensation_Page_Exit(void);
 static void Ex_Temp_Compensation_PageTask(void);
 /************* 输入参数- 外界温度传感器温度校验补偿页面  *******************/
 static void Ex_Temp_Device_Compensation_Input_Page_Load(void);
 static void Ex_Temp_Device_Compensation_Input_Page_Exit(void);
 static void Ex_Temp_Device_Compensation_Input_Page_Task(void);
 static void Hmi_External_Temp_Compensation_Slcet_Input_Buttons_CB(key_Input_Number_Typedef key_number ,Key_Trg_Even key_state);
 /********* 保存设置参数- 外界温度传感器温度校验补偿  ******************/
 static void Ex_Temp_Device_Set_Compensation_Enter_Page_Load(void);
 static void Ex_Temp_Device_Set_Compensation_Enter_Page_Exit(void);
 static void Ex_Temp_Device_Set_Compensation_Page_Task(void);
 /********************************************** 切换页面 - 外界温度传感器高温报警阈值页面  ***************************************************************/
 static void Ex_Temp_Alarm_Threshold_Page_Load(void);
 static void Ex_Temp_Alarm_Threshold_Page_Exit(void);
 static void Ex_Temp_Alarm_Threshold_Page_Task(void);
 /************* 输入参数- 外界温度传感器高温阈值页面  *******************/
 static void Ex_Temp_Alarm_Threshold_Input_Page_Load(void);
 static void EX_Temp_Alarm_Threshold_Input_Page_Exit(void);
 static void Ex_Temp_Alarm_Threshold_Input_Page_Task(void);
 static void Hmi_External_Temp_Alarm_Threshold_Input_Buttons_CB(key_Input_Number_Typedef key_number ,Key_Trg_Even key_state);
 /********* 保存设置参数- 外界温度传感器高温阈值  ******************/
 static void Ex_Temp_Alarm_Threshold_Enter_Page_Load(void);
 static void Ex_Temp_Alarm_Threshold_Enter_Page_Exit(void);
 static void Ex_Temp_Alarm_Threshold_Enter_Page_Task(void);
 /********************************************** 切换页面 - 外界温度传感器温度采集速率页面  ***************************************************************/
 static void Ex_Temp_Acquisition_Rate_Page_Load(void);
 static void Ex_Temp_Acquisition_Rate_Page_Exit(void);
 static void Ex_Temp_Acquisition_Rate_Page_Task(void);
 /************* 输入参数- 外界温度传感器温湿度采样速率页面  *******************/
 static void Ex_Temp_Sample_Rate_Input_Page_Load(void);
 static void EX_Temp_Sample_Rate_Input_Page_Exit(void);
 static void Ex_Temp_Sample_Rate_Input_Page_Task(void);
 static void Hmi_External_Temp_Sample_Rate_Input_Buttons_CB(key_Input_Number_Typedef key_number ,Key_Trg_Even key_state);
 /********* 保存设置参数- 外界温度传感器温度采样速率  ******************/
 static void Ex_Temp_Sample_Rate_Enter_Page_Load(void);
 static void Ex_Temp_Sample_Rate_Enter_Page_Exit(void);
 static void Ex_Temp_Sample_Rate_Enter_Page_Task(void);
 /************* 外界温度传感器公共回调函数  *******************/
 static void Humiture_Slcet_Set_Buttons_CB( key_Input_Number_Typedef key_number , Key_Trg_Even key_state);
 static void Humiture_Slcet_Enter_Window_Buttons_CB( key_Input_Number_Typedef key_number , Key_Trg_Even key_state);

/******************外界参数-温度传感器设置页面选择*********************************/

/* 外界温度传感器设置菜单*/
static MenuList_t External_Temp_Set_Menu_Table[] =
{
    {"设备地址复归", NULL, Device_Addr_Reversion_Page_Load, Device_Addr_Reversion_Page_Exit, Device_Addr_Reversion_Page_Task, NULL},

    {"温度校验补偿", NULL, Ex_Temp_Compensation_Page_Load, Ex_Temp_Compensation_Page_Exit, Ex_Temp_Compensation_PageTask, NULL},

    {"高温报警阈值", NULL, Ex_Temp_Alarm_Threshold_Page_Load, Ex_Temp_Alarm_Threshold_Page_Exit, Ex_Temp_Alarm_Threshold_Page_Task, NULL},

    {"温度采集速率", NULL,  Ex_Temp_Acquisition_Rate_Page_Load, Ex_Temp_Acquisition_Rate_Page_Exit, Ex_Temp_Acquisition_Rate_Page_Task, NULL},

    {"返回上级菜单", NULL,  Return_Previous_Menu_Page_Load, NULL, NULL, NULL},

    {"返回主页面", NULL,  Back_Main_Page_Load,   NULL,   NULL, NULL},
};

/* 参数初始化*/
static void MenuDateShow_Init(void){
	system_para_def system_para_t ;
	set_ex_temp_menu_list_pararm_t.Ex_Temp_ShowCompensationDate_t = show_ex_temp_compensation_date ;    //显示温度补偿值
	set_ex_temp_menu_list_pararm_t.Ex_Temp_ShowAlarmThresholdDate = show_ex_temp_alarm_threshold_date ; //显示温度报警阈值
	set_ex_temp_menu_list_pararm_t.EX_Temp_ShowSampleRateDate = show_ex_temp_humiture_sample_rate_date ;//显示温度采集速率

	read_saveenv_cjson_system_parameter(&system_para_t);
	set_ex_temp_menu_list_pararm_t.auto_exit_sets_page_to_main_time = system_para_t.AutoExitSetsPageTime;
}
/* 设置地址复位初始化*/
static void Device_Addr_Reversion_Init(void){
	struct dev_address_reset_par ex_tmp_address_reset_par ;
	ex_tmp_address_reset_par.setting_sleet_type_flag = 0 ;
	ex_tmp_address_reset_par.setting_cursor_dev_var_addr = EXTERNAL_TEMP_DEV_ADDERSS_RESET_CURSOR_ADDERSS ;
	ex_tmp_address_reset_par.setting_dev_reset_page = PAGE_EXTERNAL_TEMP_DEV_ADDR_SETTING_NUMBER ;
	ex_tmp_address_reset_par.auto_exit_setting_page_time = set_ex_temp_menu_list_pararm_t.auto_exit_sets_page_to_main_time ;
	ex_tmp_address_reset_par.dev_addr_reset_wait_var_addr = EXTERNAL_TEMP_DEV_ADDR_RESET_WAIT_WINDOW_VAR_ADDERSS ;
	ex_tmp_address_reset_par.dev_addr_reset_success_var_addr = EXTERNAL_TEMP_DEV_ADDR_RESET_SUCCESS_WINDOW_VAR_ADDERSS ;
	ex_tmp_address_reset_par.dev_addr_reset_error_var_addr = EXTERNAL_TEMP_DEV_ADDR_RESET_ERROR_WINDOW_VAR_ADDERSS ;
	/* 设置设备地址确定执行函数 */
	ex_tmp_address_reset_par.dev_reset_execute_function_cb = Ex_Temp_Setting_Dev_Transducer_Reset_Addr ;
	Device_Addr_Reversion_Load_Init( &ex_tmp_address_reset_par);
}
/* 设置地址复位执行函数*/
static void Ex_Temp_Setting_Dev_Transducer_Reset_Addr(void){
	 Setting_Dev_Transducer_Reset_Addr( external_temperature_transducer ) ;
}

/* 设置菜单显示效果 */
static void Humiture_SetMenu(  MenuShow_t *ptShowInfo){
	show_refresh_time();
	show_eth_connect_state();
}
/********************************************** 切换页面 - 外界温度传感器选择设置页面  ***************************************************************/
void External_Temp_Setting_Page_Load(void){

	log_d("Hmi_Main_External_Setting_Page_Load ");
	type_slect_move_cursor slect_move_cursor;

	slect_move_cursor.dw_cursor_adderss = EXTERNAL_TEMP_DEV_SETTING_CURSOR_ADDERSS ;
	slect_move_cursor.max_slect_move = 5 ;
	slect_move_cursor.min_slect_move = 0 ;
	slect_move_cursor.move_slect_step = 1 ;
	slect_move_cursor.now_slect_move = 0 ;
	slect_cursor_move_init(&slect_move_cursor);  //光标位置初始化
	dw_show_switching_pages(PAGE_EXTERNAL_TEMP_SETTING_NUMBER); //切换页面
	slect_cursor_move(cursor_default_mode,cursor_null);  //初始化选择设置光标
	Buttons_Register(KEY_UP_TRG_NUMBER,Humiture_Slcet_Set_Buttons_CB);
	Buttons_Register(KEY_ENTER_TRG_NUMBER,Humiture_Slcet_Set_Buttons_CB);
	Buttons_Register(KEY_DOWN_TRG_NUMBER,Humiture_Slcet_Set_Buttons_CB);
	MenuDateShow_Init();
	Device_Addr_Reversion_Init();
	//clear_time_cnt(AUTO_EXIT_SETS_PAGE_TO_MAIN_PAGE_TIMER_NUMBER);
	Menu_Bind(External_Temp_Set_Menu_Table, GET_MENU_NUM(External_Temp_Set_Menu_Table), Humiture_SetMenu);
}

void External_Temp_Setting_Page_Exit(void){
	//clear_time_cnt(AUTO_EXIT_SETS_PAGE_TO_MAIN_PAGE_TIMER_NUMBER);
}

void External_Temp_Setting_Page_Task(void){
	if(check_time_arrive(AUTO_EXIT_SETS_PAGE_TO_MAIN_PAGE_TIMER_NUMBER,set_ex_temp_menu_list_pararm_t.auto_exit_sets_page_to_main_time*1000)){
		Back_Main_Page_Load();
		//clear_time_cnt(AUTO_EXIT_SETS_PAGE_TO_MAIN_PAGE_TIMER_NUMBER);
	}
}






/********************************************** 切换页面 - 外界温度传感器温度校验补偿页面  ***************************************************************/
/* 外界温度传感器温度校验补偿菜单 */
static MenuList_t External_Temp_Set_Compensation_Menu_Table[] =
{
	{"参数输入框", NULL, Ex_Temp_Device_Compensation_Input_Page_Load, Ex_Temp_Device_Compensation_Input_Page_Exit, Ex_Temp_Device_Compensation_Input_Page_Task, NULL},

    {"保存设置参数", NULL, Ex_Temp_Device_Set_Compensation_Enter_Page_Load, Ex_Temp_Device_Set_Compensation_Enter_Page_Exit, Ex_Temp_Device_Set_Compensation_Page_Task, NULL},

    {"返回上级菜单", NULL,  Return_Previous_Menu_Page_Load, NULL, NULL, NULL},

    {"返回主页面", NULL,  Back_Main_Page_Load,   NULL,   NULL, NULL},
};

static void Ex_Temp_Compensation_Page_Load(void){

	type_slect_move_cursor slect_move_cursor;

	slect_move_cursor.dw_cursor_adderss = EXTERNAL_TEMP_COMPENSATION_INPUT_SELECT_CURSOR_ADDERSS ;
	slect_move_cursor.max_slect_move = 2 ;
	slect_move_cursor.min_slect_move = 0 ;
	slect_move_cursor.move_slect_step = 1 ;
	slect_move_cursor.now_slect_move = 0 ;
	slect_cursor_move_init(&slect_move_cursor);  //光标位置初始化
	slect_cursor_move(cursor_refresh_mode,cursor_null);  //关闭光标
	slect_move_cursor.dw_cursor_adderss = EXTERNAL_TEMP_COMPENSATION_SELECT_CURSOR_ADDERSS ;
	slect_move_cursor.max_slect_move = 3 ;
	slect_move_cursor.min_slect_move = 0 ;
	slect_move_cursor.move_slect_step = 1 ;
	slect_move_cursor.now_slect_move = 0 ;
	slect_cursor_move_init(&slect_move_cursor); 		 			//光标位置初始化
	slect_cursor_move(cursor_default_mode,cursor_null);  			//初始化选择设置光标
	read_saveenv_cjson_external_parameter(&set_ex_temp_menu_list_pararm_t.external_para);
	set_ex_temp_menu_list_pararm_t.Ex_Temp_ShowCompensationDate_t(set_ex_temp_menu_list_pararm_t.external_para.ExternalTemperatureCompensationDate);  //显示温度补偿值
	dw_show_switching_pages(PAGE_EXTERNAL_TEMP_COMPENSATION_SETTING_NUMBER); //切换页面
	Buttons_Register(KEY_UP_TRG_NUMBER,Humiture_Slcet_Set_Buttons_CB);
	Buttons_Register(KEY_ENTER_TRG_NUMBER,Humiture_Slcet_Set_Buttons_CB);
	Buttons_Register(KEY_DOWN_TRG_NUMBER,Humiture_Slcet_Set_Buttons_CB);
	Menu_Bind(External_Temp_Set_Compensation_Menu_Table, GET_MENU_NUM(External_Temp_Set_Compensation_Menu_Table), Humiture_SetMenu);
}
static void Ex_Temp_Compensation_Page_Exit(void){
	//clear_time_cnt(AUTO_EXIT_SETS_PAGE_TO_MAIN_PAGE_TIMER_NUMBER);
}
static void Ex_Temp_Compensation_PageTask(void){
	if(check_time_arrive(AUTO_EXIT_SETS_PAGE_TO_MAIN_PAGE_TIMER_NUMBER,set_ex_temp_menu_list_pararm_t.auto_exit_sets_page_to_main_time*1000)){
		Back_Main_Page_Load();
		//clear_time_cnt(AUTO_EXIT_SETS_PAGE_TO_MAIN_PAGE_TIMER_NUMBER);
	}
}
/************* 输入参数- 外界温度传感器温度校验补偿页面  *******************/
static void Ex_Temp_Device_Compensation_Input_Page_Load(void){
	type_slect_move_cursor slect_move_cursor;
	slect_move_cursor.dw_cursor_adderss = EXTERNAL_TEMP_COMPENSATION_SELECT_CURSOR_ADDERSS ;
	slect_move_cursor.max_slect_move = 3 ;
	slect_move_cursor.min_slect_move = 0 ;
	slect_move_cursor.move_slect_step = 1 ;
	slect_move_cursor.now_slect_move = 0 ;
	slect_cursor_move_init(&slect_move_cursor);  //光标位置初始化
	slect_cursor_move(cursor_refresh_mode,cursor_null);  //关闭光标
	slect_move_cursor.dw_cursor_adderss = EXTERNAL_TEMP_COMPENSATION_INPUT_SELECT_CURSOR_ADDERSS ;
	slect_move_cursor.max_slect_move = 2 ;
	slect_move_cursor.min_slect_move = 0 ;
	slect_move_cursor.move_slect_step = 1 ;
	slect_move_cursor.now_slect_move = 0 ;
	slect_cursor_move_init(&slect_move_cursor);  //光标位置初始化
	slect_cursor_move(cursor_default_mode,cursor_null);  //显示初始化光标位置
	Buttons_Register(KEY_UP_TRG_NUMBER,Hmi_External_Temp_Compensation_Slcet_Input_Buttons_CB);
	Buttons_Register(KEY_ENTER_TRG_NUMBER,Hmi_External_Temp_Compensation_Slcet_Input_Buttons_CB);
	Buttons_Register(KEY_DOWN_TRG_NUMBER,Hmi_External_Temp_Compensation_Slcet_Input_Buttons_CB);
}

static void Ex_Temp_Device_Compensation_Input_Page_Exit(void){
	//clear_time_cnt(AUTO_EXIT_SETS_PAGE_TO_MAIN_PAGE_TIMER_NUMBER);
}

static void Ex_Temp_Device_Compensation_Input_Page_Task(void){
	if(check_time_arrive(AUTO_EXIT_SETS_PAGE_TO_MAIN_PAGE_TIMER_NUMBER,set_ex_temp_menu_list_pararm_t.auto_exit_sets_page_to_main_time*1000)){
		Back_Main_Page_Load();
		//clear_time_cnt(AUTO_EXIT_SETS_PAGE_TO_MAIN_PAGE_TIMER_NUMBER);
	}
}


static void Hmi_External_Temp_Compensation_Slcet_Input_Buttons_CB(key_Input_Number_Typedef key_number ,Key_Trg_Even key_state){
	if(key_state == KEY_CLICK_ACTION){
		//clear_time_cnt(AUTO_EXIT_SETS_PAGE_TO_MAIN_PAGE_TIMER_NUMBER);
		set_ex_temp_menu_list_pararm_t.external_para.ExternalTemperatureCompensationDate=user_parameter_adjustment(set_ex_temp_menu_list_pararm_t.external_para.ExternalTemperatureCompensationDate,1,2,key_number,set_ex_temp_menu_list_pararm_t.Ex_Temp_ShowCompensationDate_t);
	}
}

/********* 保存设置参数- 外界温度传感器温度校验补偿  ******************/
static void Ex_Temp_Device_Set_Compensation_Enter_Page_Load(void){
	int ret = -1 ;
	type_slect_move_cursor slect_move_cursor;
	slect_move_cursor.dw_cursor_adderss = EXTERNAL_TEMP_COMPENSATION_SELECT_CURSOR_ADDERSS ;
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
	dw_input_parameter_hint_window( 1 ,EXTERNAL_TEMP_COMPENSATION_WAIT_WINDOW_VAR_ADDERSS,EXTERNAL_TEMP_COMPENSATION_SUCCESS_WINDOW_VAR_ADDERSS,EXTERNAL_TEMP_COMPENSATION_ERROR_WINDOW_VAR_ADDERSS);
	ret = externalparaPoint_amend_config("ExternalTemperatureCompensationDate",set_ex_temp_menu_list_pararm_t.external_para.ExternalTemperatureCompensationDate);
	if( !ret){
		 //显示成功窗口
		dw_input_parameter_hint_window(2,EXTERNAL_TEMP_COMPENSATION_WAIT_WINDOW_VAR_ADDERSS,EXTERNAL_TEMP_COMPENSATION_SUCCESS_WINDOW_VAR_ADDERSS,EXTERNAL_TEMP_COMPENSATION_ERROR_WINDOW_VAR_ADDERSS);
	}else{
		//显示错误窗口
		dw_input_parameter_hint_window( 3 ,EXTERNAL_TEMP_COMPENSATION_WAIT_WINDOW_VAR_ADDERSS,EXTERNAL_TEMP_COMPENSATION_SUCCESS_WINDOW_VAR_ADDERSS,EXTERNAL_TEMP_COMPENSATION_ERROR_WINDOW_VAR_ADDERSS);
	}
	Buttons_Register(KEY_ENTER_TRG_NUMBER,Humiture_Slcet_Enter_Window_Buttons_CB);
}

static void Ex_Temp_Device_Set_Compensation_Enter_Page_Exit(void){
	//清除窗口
	dw_input_parameter_hint_window( 0 ,EXTERNAL_TEMP_COMPENSATION_WAIT_WINDOW_VAR_ADDERSS,EXTERNAL_TEMP_COMPENSATION_SUCCESS_WINDOW_VAR_ADDERSS,EXTERNAL_TEMP_COMPENSATION_ERROR_WINDOW_VAR_ADDERSS);
	//clear_time_cnt(AUTO_EXIT_SETS_PAGE_TO_MAIN_PAGE_TIMER_NUMBER);
}

static void Ex_Temp_Device_Set_Compensation_Page_Task(void){
	if(check_time_arrive(AUTO_EXIT_SETS_PAGE_TO_MAIN_PAGE_TIMER_NUMBER,set_ex_temp_menu_list_pararm_t.auto_exit_sets_page_to_main_time*1000)){
		Back_Main_Page_Load();
		//clear_time_cnt(AUTO_EXIT_SETS_PAGE_TO_MAIN_PAGE_TIMER_NUMBER);
	}
}

/********************************************** 切换页面 - 外界温度传感器高温报警阈值页面  ***************************************************************/
/* 外界温度传感器温度校验补偿菜单 */
static MenuList_t External_Temp_Alarm_Threshold_Menu_Table[] =
{
	{"参数输入框", NULL, Ex_Temp_Alarm_Threshold_Input_Page_Load, EX_Temp_Alarm_Threshold_Input_Page_Exit, Ex_Temp_Alarm_Threshold_Input_Page_Task, NULL},

    {"保存设置参数", NULL, Ex_Temp_Alarm_Threshold_Enter_Page_Load, Ex_Temp_Alarm_Threshold_Enter_Page_Exit, Ex_Temp_Alarm_Threshold_Enter_Page_Task, NULL},

    {"返回上级菜单", NULL,  Return_Previous_Menu_Page_Load, NULL, NULL, NULL},

    {"返回主页面", NULL,  Back_Main_Page_Load,   NULL,   NULL, NULL},
};



static void Ex_Temp_Alarm_Threshold_Page_Load(void){
	type_slect_move_cursor slect_move_cursor;

	slect_move_cursor.dw_cursor_adderss = EXTERNAL_TEMP_ALARM_THERSHOLD_INPUT_SELECT_CURSOR_ADDERSS ;
	slect_move_cursor.max_slect_move = 1 ;
	slect_move_cursor.min_slect_move = 0 ;
	slect_move_cursor.move_slect_step = 1 ;
	slect_move_cursor.now_slect_move = 0 ;
	slect_cursor_move_init(&slect_move_cursor);  		//光标位置初始化
	slect_cursor_move(cursor_refresh_mode,cursor_null);  //关闭输入指示光标
	slect_move_cursor.dw_cursor_adderss = EXTERNAL_TEMP_ALARM_THERSHOLD_SELECT_CURSOR_ADDERSS ;
	slect_move_cursor.max_slect_move = 3 ;
	slect_move_cursor.min_slect_move = 0 ;
	slect_move_cursor.move_slect_step = 1 ;
	slect_move_cursor.now_slect_move = 0 ;
	slect_cursor_move_init(&slect_move_cursor); 		 			//光标位置初始化
	slect_cursor_move(cursor_default_mode,cursor_null);  			//初始化选择设置光标
	read_saveenv_cjson_external_parameter(&set_ex_temp_menu_list_pararm_t.external_para);
	set_ex_temp_menu_list_pararm_t.Ex_Temp_ShowAlarmThresholdDate(set_ex_temp_menu_list_pararm_t.external_para.ExternalAlarmTemperature);  //显示高温阈值
	dw_show_switching_pages(PAGE_EXTERNAL_TEMP_ALARM_THRESHOLD_SETTING_NUMBER); //切换页面
	Buttons_Register(KEY_UP_TRG_NUMBER,Humiture_Slcet_Set_Buttons_CB);
	Buttons_Register(KEY_ENTER_TRG_NUMBER,Humiture_Slcet_Set_Buttons_CB);
	Buttons_Register(KEY_DOWN_TRG_NUMBER,Humiture_Slcet_Set_Buttons_CB);
	Menu_Bind(External_Temp_Alarm_Threshold_Menu_Table, GET_MENU_NUM(External_Temp_Alarm_Threshold_Menu_Table), Humiture_SetMenu);
}
static void Ex_Temp_Alarm_Threshold_Page_Exit(void){
	//clear_time_cnt(AUTO_EXIT_SETS_PAGE_TO_MAIN_PAGE_TIMER_NUMBER);
}
static void Ex_Temp_Alarm_Threshold_Page_Task(void){
	if(check_time_arrive(AUTO_EXIT_SETS_PAGE_TO_MAIN_PAGE_TIMER_NUMBER,set_ex_temp_menu_list_pararm_t.auto_exit_sets_page_to_main_time*1000)){
		Back_Main_Page_Load();
		//clear_time_cnt(AUTO_EXIT_SETS_PAGE_TO_MAIN_PAGE_TIMER_NUMBER);
	}
}
/************* 输入参数- 外界温度传感器高温阈值页面  *******************/
static void Ex_Temp_Alarm_Threshold_Input_Page_Load(void){
	type_slect_move_cursor slect_move_cursor;

	slect_move_cursor.dw_cursor_adderss = EXTERNAL_TEMP_ALARM_THERSHOLD_SELECT_CURSOR_ADDERSS ;
	slect_move_cursor.max_slect_move = 3 ;
	slect_move_cursor.min_slect_move = 0 ;
	slect_move_cursor.move_slect_step = 1 ;
	slect_move_cursor.now_slect_move = 0 ;
	slect_cursor_move_init(&slect_move_cursor);  //光标位置初始化
	slect_cursor_move(cursor_refresh_mode,cursor_null);  //关闭选择设置光标
	slect_move_cursor.dw_cursor_adderss = EXTERNAL_TEMP_ALARM_THERSHOLD_INPUT_SELECT_CURSOR_ADDERSS ;
	slect_move_cursor.max_slect_move = 1 ;
	slect_move_cursor.min_slect_move = 0 ;
	slect_move_cursor.move_slect_step = 1 ;
	slect_move_cursor.now_slect_move = 0 ;
	slect_cursor_move_init(&slect_move_cursor);  //光标位置初始化
	slect_cursor_move(cursor_default_mode,cursor_null);  //显示初始化输入指示光标位置
	Buttons_Register(KEY_UP_TRG_NUMBER,Hmi_External_Temp_Alarm_Threshold_Input_Buttons_CB);
	Buttons_Register(KEY_ENTER_TRG_NUMBER,Hmi_External_Temp_Alarm_Threshold_Input_Buttons_CB);
	Buttons_Register(KEY_DOWN_TRG_NUMBER,Hmi_External_Temp_Alarm_Threshold_Input_Buttons_CB);
}

static void EX_Temp_Alarm_Threshold_Input_Page_Exit(void){
	//clear_time_cnt(AUTO_EXIT_SETS_PAGE_TO_MAIN_PAGE_TIMER_NUMBER);
}

static void Ex_Temp_Alarm_Threshold_Input_Page_Task(void){
	if(check_time_arrive(AUTO_EXIT_SETS_PAGE_TO_MAIN_PAGE_TIMER_NUMBER,set_ex_temp_menu_list_pararm_t.auto_exit_sets_page_to_main_time*1000)){
		Back_Main_Page_Load();
		//clear_time_cnt(AUTO_EXIT_SETS_PAGE_TO_MAIN_PAGE_TIMER_NUMBER);
	}
}


static void Hmi_External_Temp_Alarm_Threshold_Input_Buttons_CB(key_Input_Number_Typedef key_number ,Key_Trg_Even key_state){
	if(key_state == KEY_CLICK_ACTION){
		//clear_time_cnt(AUTO_EXIT_SETS_PAGE_TO_MAIN_PAGE_TIMER_NUMBER);
		set_ex_temp_menu_list_pararm_t.external_para.ExternalAlarmTemperature=user_parameter_adjustment(set_ex_temp_menu_list_pararm_t.external_para.ExternalAlarmTemperature,0,2,key_number,set_ex_temp_menu_list_pararm_t.Ex_Temp_ShowAlarmThresholdDate);
	}
}

/********* 保存设置参数- 外界温度传感器高温阈值  ******************/
static void Ex_Temp_Alarm_Threshold_Enter_Page_Load(void){
	int ret = -1 ;
	type_slect_move_cursor slect_move_cursor;
	slect_move_cursor.dw_cursor_adderss = EXTERNAL_TEMP_ALARM_THERSHOLD_SELECT_CURSOR_ADDERSS ;
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
	dw_input_parameter_hint_window( 1 ,EXTERNAL_TEMP_ALARM_THERSHOLD_WAIT_WINDOW_VAR_ADDERSS,EXTERNAL_TEMP_ALARM_THERSHOLD_SUCCESS_WINDOW_VAR_ADDERSS,EXTERNAL_TEMP_ALARM_THERSHOLD_ERROR_WINDOW_VAR_ADDERSS);
	ret = externalparaPoint_amend_config("ExternalAlarmTemperature",set_ex_temp_menu_list_pararm_t.external_para.ExternalAlarmTemperature);
	if( !ret){
		 //显示成功窗口
		dw_input_parameter_hint_window(2,EXTERNAL_TEMP_ALARM_THERSHOLD_WAIT_WINDOW_VAR_ADDERSS,EXTERNAL_TEMP_ALARM_THERSHOLD_SUCCESS_WINDOW_VAR_ADDERSS,EXTERNAL_TEMP_ALARM_THERSHOLD_ERROR_WINDOW_VAR_ADDERSS);
	}else{
		//显示错误窗口
		dw_input_parameter_hint_window( 3 ,EXTERNAL_TEMP_ALARM_THERSHOLD_WAIT_WINDOW_VAR_ADDERSS,EXTERNAL_TEMP_ALARM_THERSHOLD_SUCCESS_WINDOW_VAR_ADDERSS,EXTERNAL_TEMP_ALARM_THERSHOLD_ERROR_WINDOW_VAR_ADDERSS);
	}
	Buttons_Register(KEY_ENTER_TRG_NUMBER,Humiture_Slcet_Enter_Window_Buttons_CB);
}

static void Ex_Temp_Alarm_Threshold_Enter_Page_Exit(void){
	//清除窗口
	dw_input_parameter_hint_window( 0 ,EXTERNAL_TEMP_ALARM_THERSHOLD_WAIT_WINDOW_VAR_ADDERSS,EXTERNAL_TEMP_ALARM_THERSHOLD_SUCCESS_WINDOW_VAR_ADDERSS,EXTERNAL_TEMP_ALARM_THERSHOLD_ERROR_WINDOW_VAR_ADDERSS);
	//clear_time_cnt(AUTO_EXIT_SETS_PAGE_TO_MAIN_PAGE_TIMER_NUMBER);
}

static void Ex_Temp_Alarm_Threshold_Enter_Page_Task(void){
	if(check_time_arrive(AUTO_EXIT_SETS_PAGE_TO_MAIN_PAGE_TIMER_NUMBER,set_ex_temp_menu_list_pararm_t.auto_exit_sets_page_to_main_time*1000)){
		Back_Main_Page_Load();
		//clear_time_cnt(AUTO_EXIT_SETS_PAGE_TO_MAIN_PAGE_TIMER_NUMBER);
	}
}

/********************************************** 切换页面 - 外界温度传感器温度采集速率页面  ***************************************************************/
/* 外界温度传感器温度采集速率菜单 */
static MenuList_t External_Temp_Sample_Rate_Menu_Table[] =
{
	{"参数输入框", NULL, Ex_Temp_Sample_Rate_Input_Page_Load, EX_Temp_Sample_Rate_Input_Page_Exit, Ex_Temp_Sample_Rate_Input_Page_Task, NULL},

    {"保存设置参数", NULL, Ex_Temp_Sample_Rate_Enter_Page_Load, Ex_Temp_Sample_Rate_Enter_Page_Exit, Ex_Temp_Sample_Rate_Enter_Page_Task, NULL},

    {"返回上级菜单", NULL,  Return_Previous_Menu_Page_Load, NULL, NULL, NULL},

    {"返回主页面", NULL,  Back_Main_Page_Load,   NULL,   NULL, NULL},
};

static void Ex_Temp_Acquisition_Rate_Page_Load(void){
	type_slect_move_cursor slect_move_cursor;

	slect_move_cursor.dw_cursor_adderss = EXTERNAL_TEMP_SAMPLE_RATE_INPUT_SELECT_CURSOR_ADDERSS ;
	slect_move_cursor.max_slect_move = 1 ;
	slect_move_cursor.min_slect_move = 0 ;
	slect_move_cursor.move_slect_step = 1 ;
	slect_move_cursor.now_slect_move = 0 ;
	slect_cursor_move_init(&slect_move_cursor);  		//输入指示光标位置初始化
	slect_cursor_move(cursor_refresh_mode,cursor_null);  //关闭输入指示光标
	slect_move_cursor.dw_cursor_adderss = EXTERNAL_TEMP_SAMPLE_RATE_SELECT_CURSOR_ADDERSS ;
	slect_move_cursor.max_slect_move = 3 ;
	slect_move_cursor.min_slect_move = 0 ;
	slect_move_cursor.move_slect_step = 1 ;
	slect_move_cursor.now_slect_move = 0 ;
	slect_cursor_move_init(&slect_move_cursor); 		 			//光标位置初始化
	slect_cursor_move(cursor_default_mode,cursor_null);  			//初始化选择设置光标
	read_saveenv_cjson_external_parameter(&set_ex_temp_menu_list_pararm_t.external_para);
	set_ex_temp_menu_list_pararm_t.EX_Temp_ShowSampleRateDate(set_ex_temp_menu_list_pararm_t.external_para.ExternalHumitureSampleRate); //显示采样速率
	dw_show_switching_pages(PAGE_EXTERNAL_TEMP_SAMPLE_RATE_SETTING_NUMBER); //切换页面
	Buttons_Register(KEY_UP_TRG_NUMBER,Humiture_Slcet_Set_Buttons_CB);
	Buttons_Register(KEY_ENTER_TRG_NUMBER,Humiture_Slcet_Set_Buttons_CB);
	Buttons_Register(KEY_DOWN_TRG_NUMBER,Humiture_Slcet_Set_Buttons_CB);
	Menu_Bind(External_Temp_Sample_Rate_Menu_Table, GET_MENU_NUM(External_Temp_Sample_Rate_Menu_Table), Humiture_SetMenu);
}

static void Ex_Temp_Acquisition_Rate_Page_Exit(void){
	//clear_time_cnt(AUTO_EXIT_SETS_PAGE_TO_MAIN_PAGE_TIMER_NUMBER);
}
static void Ex_Temp_Acquisition_Rate_Page_Task(void){
	if(check_time_arrive(AUTO_EXIT_SETS_PAGE_TO_MAIN_PAGE_TIMER_NUMBER,set_ex_temp_menu_list_pararm_t.auto_exit_sets_page_to_main_time*1000)){
		Back_Main_Page_Load();
		//clear_time_cnt(AUTO_EXIT_SETS_PAGE_TO_MAIN_PAGE_TIMER_NUMBER);
	}
}

/************* 输入参数- 外界温度传感器温湿度采样速率页面  *******************/
static void Ex_Temp_Sample_Rate_Input_Page_Load(void){
	type_slect_move_cursor slect_move_cursor;

	slect_move_cursor.dw_cursor_adderss = EXTERNAL_TEMP_SAMPLE_RATE_SELECT_CURSOR_ADDERSS ;
	slect_move_cursor.max_slect_move = 3 ;
	slect_move_cursor.min_slect_move = 0 ;
	slect_move_cursor.move_slect_step = 1 ;
	slect_move_cursor.now_slect_move = 0 ;
	slect_cursor_move_init(&slect_move_cursor);  //光标位置初始化
	slect_cursor_move(cursor_refresh_mode,cursor_null);  //关闭选择设置光标
	slect_move_cursor.dw_cursor_adderss = EXTERNAL_TEMP_SAMPLE_RATE_INPUT_SELECT_CURSOR_ADDERSS ;
	slect_move_cursor.max_slect_move = 1 ;
	slect_move_cursor.min_slect_move = 0 ;
	slect_move_cursor.move_slect_step = 1 ;
	slect_move_cursor.now_slect_move = 0 ;
	slect_cursor_move_init(&slect_move_cursor);  //光标位置初始化
	slect_cursor_move(cursor_default_mode,cursor_null);  //显示初始化输入指示光标位置
	Buttons_Register(KEY_UP_TRG_NUMBER,Hmi_External_Temp_Sample_Rate_Input_Buttons_CB);
	Buttons_Register(KEY_ENTER_TRG_NUMBER,Hmi_External_Temp_Sample_Rate_Input_Buttons_CB);
	Buttons_Register(KEY_DOWN_TRG_NUMBER,Hmi_External_Temp_Sample_Rate_Input_Buttons_CB);
}

static void EX_Temp_Sample_Rate_Input_Page_Exit(void){
	//clear_time_cnt(AUTO_EXIT_SETS_PAGE_TO_MAIN_PAGE_TIMER_NUMBER);
}

static void Ex_Temp_Sample_Rate_Input_Page_Task(void){
	if(check_time_arrive(AUTO_EXIT_SETS_PAGE_TO_MAIN_PAGE_TIMER_NUMBER,set_ex_temp_menu_list_pararm_t.auto_exit_sets_page_to_main_time*1000)){
		Back_Main_Page_Load();
		//clear_time_cnt(AUTO_EXIT_SETS_PAGE_TO_MAIN_PAGE_TIMER_NUMBER);
	}
}

static void Hmi_External_Temp_Sample_Rate_Input_Buttons_CB(key_Input_Number_Typedef key_number ,Key_Trg_Even key_state){
	if(key_state == KEY_CLICK_ACTION){
		//clear_time_cnt(AUTO_EXIT_SETS_PAGE_TO_MAIN_PAGE_TIMER_NUMBER);
		set_ex_temp_menu_list_pararm_t.external_para.ExternalHumitureSampleRate=user_parameter_adjustment(set_ex_temp_menu_list_pararm_t.external_para.ExternalHumitureSampleRate,0,2,key_number,set_ex_temp_menu_list_pararm_t.EX_Temp_ShowSampleRateDate);
	}
}

/********* 保存设置参数- 外界温度传感器温度采样速率  ******************/
static void Ex_Temp_Sample_Rate_Enter_Page_Load(void){
	int ret = -1 ;
	type_slect_move_cursor slect_move_cursor;
	slect_move_cursor.dw_cursor_adderss = EXTERNAL_TEMP_SAMPLE_RATE_SELECT_CURSOR_ADDERSS ;
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
	dw_input_parameter_hint_window( 1 ,EXTERNAL_TEMP_SAMPLE_RATE_WAIT_WINDOW_VAR_ADDERSS,EXTERNAL_TEMP_SAMPLE_RATE_SUCCESS_WINDOW_VAR_ADDERSS,EXTERNAL_TEMP_SAMPLE_RATE_ERROR_WINDOW_VAR_ADDERSS);
	ret = externalparaPoint_amend_config("ExternalHumitureSampleRate",set_ex_temp_menu_list_pararm_t.external_para.ExternalHumitureSampleRate);
	if( !ret){
		 //显示成功窗口
		dw_input_parameter_hint_window(2,EXTERNAL_TEMP_SAMPLE_RATE_WAIT_WINDOW_VAR_ADDERSS,EXTERNAL_TEMP_SAMPLE_RATE_SUCCESS_WINDOW_VAR_ADDERSS,EXTERNAL_TEMP_SAMPLE_RATE_ERROR_WINDOW_VAR_ADDERSS);
	}else{
		//显示错误窗口
		dw_input_parameter_hint_window( 3 ,EXTERNAL_TEMP_SAMPLE_RATE_WAIT_WINDOW_VAR_ADDERSS,EXTERNAL_TEMP_SAMPLE_RATE_SUCCESS_WINDOW_VAR_ADDERSS,EXTERNAL_TEMP_SAMPLE_RATE_ERROR_WINDOW_VAR_ADDERSS);
	}
	Buttons_Register(KEY_ENTER_TRG_NUMBER,Humiture_Slcet_Enter_Window_Buttons_CB);
}

static void Ex_Temp_Sample_Rate_Enter_Page_Exit(void){
	//清除窗口
		dw_input_parameter_hint_window( 0 ,EXTERNAL_TEMP_SAMPLE_RATE_WAIT_WINDOW_VAR_ADDERSS,EXTERNAL_TEMP_SAMPLE_RATE_SUCCESS_WINDOW_VAR_ADDERSS,EXTERNAL_TEMP_SAMPLE_RATE_ERROR_WINDOW_VAR_ADDERSS);
		//clear_time_cnt(AUTO_EXIT_SETS_PAGE_TO_MAIN_PAGE_TIMER_NUMBER);
}

static void Ex_Temp_Sample_Rate_Enter_Page_Task(void){
	if(check_time_arrive(AUTO_EXIT_SETS_PAGE_TO_MAIN_PAGE_TIMER_NUMBER,set_ex_temp_menu_list_pararm_t.auto_exit_sets_page_to_main_time*1000)){
		Back_Main_Page_Load();
		//clear_time_cnt(AUTO_EXIT_SETS_PAGE_TO_MAIN_PAGE_TIMER_NUMBER);
	}
}

/************* 外界温度传感器公共回调函数  *******************/
static void Humiture_Slcet_Set_Buttons_CB( key_Input_Number_Typedef key_number , Key_Trg_Even key_state){
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

static void Humiture_Slcet_Enter_Window_Buttons_CB( key_Input_Number_Typedef key_number , Key_Trg_Even key_state){
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
