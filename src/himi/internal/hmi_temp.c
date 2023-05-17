/*
 * hmi_temp_set.c
 *
 *  Created on: 2023年2月13日
 *      Author: 好
 */
#define LOG_TAG    "internal/hmi_temp"
#include "../himi/internal/hmi_temp.h"


struct set_in_temp_menu_list_pararm{
	int auto_exit_sets_page_to_main_time ;  //自动返回时间
	internal_para_def inernal_para ;
	ShownMenuDate In_Temp_ShowCompensationDate_t;
	ShownMenuDate In_Temp_ShowAlarmThresholdDate ;
	ShownMenuDate In_Temp_ShowSampleRateDate ;
};


static struct set_in_temp_menu_list_pararm set_in_temp_menu_list_pararm_t ;



static void MenuDateShow_Init(void);

/* 设置地址复位初始化*/
static void Device_Addr_Reversion_Init(void);
/* 设置地址复位执行函数*/
static void In_Temp_Setting_Dev_Transducer_Reset_Addr(void);
 /******************内部参数-温度传感器设置页面选择*********************************/
 /* 设置菜单显示效果 */
 static void Humiture_SetMenu(  MenuShow_t *ptShowInfo);
 /********************************************** 切换页面 - 内部温度传感器温度校验补偿页面  ***************************************************************/
 static void In_Temp_Compensation_Page_Load(void);
 static void In_Temp_Compensation_Page_Exit(void);
 static void In_Temp_Compensation_PageTask(void);
 /************* 输入参数- 内部温度传感器温度校验补偿页面  *******************/
 static void In_Temp_Device_Compensation_Input_Page_Load(void);
 static void In_Temp_Device_Compensation_Input_Page_Exit(void);
 static void In_Temp_Device_Compensation_Input_Page_Task(void);
 static void Hmi_Internal_Temp_Compensation_Slcet_Input_Buttons_CB(key_Input_Number_Typedef key_number ,Key_Trg_Even key_state);
 /********* 保存设置参数- 内部温度传感器温度校验补偿  ******************/
 static void In_Temp_Device_Set_Compensation_Enter_Page_Load(void);
 static void In_Temp_Device_Set_Compensation_Enter_Page_Exit(void);
 static void In_Temp_Device_Set_Compensation_Page_Task(void);
 /********************************************** 切换页面 - 内部温度传感器高温报警阈值页面  ***************************************************************/
 static void In_Temp_Alarm_Threshold_Page_Load(void);
 static void In_Temp_Alarm_Threshold_Page_Exit(void);
 static void In_Temp_Alarm_Threshold_Page_Task(void);
 /************* 输入参数- 内部温度传感器高温阈值页面  *******************/
 static void In_Temp_Alarm_Threshold_Input_Page_Load(void);
 static void In_Temp_Alarm_Threshold_Input_Page_Exit(void);
 static void In_Temp_Alarm_Threshold_Input_Page_Task(void);
 static void Hmi_Internal_Temp_Alarm_Threshold_Input_Buttons_CB(key_Input_Number_Typedef key_number ,Key_Trg_Even key_state);
 /********* 保存设置参数- 内部温度传感器高温阈值  ******************/
 static void In_Temp_Alarm_Threshold_Enter_Page_Load(void);
 static void In_Temp_Alarm_Threshold_Enter_Page_Exit(void);
 static void In_Temp_Alarm_Threshold_Enter_Page_Task(void);
 /********************************************** 切换页面 - 内部温度传感器温度采集速率页面  ***************************************************************/
 static void In_Temp_Acquisition_Rate_Page_Load(void);
 static void In_Temp_Acquisition_Rate_Page_Exit(void);
 static void In_Temp_Acquisition_Rate_Page_Task(void);
 /************* 输入参数- 内部温度传感器温湿度采样速率页面  *******************/
 static void In_Temp_Sample_Rate_Input_Page_Load(void);
 static void In_Temp_Sample_Rate_Input_Page_Exit(void);
 static void In_Temp_Sample_Rate_Input_Page_Task(void);
 static void Hmi_Internal_Temp_Sample_Rate_Input_Buttons_CB(key_Input_Number_Typedef key_number ,Key_Trg_Even key_state);
 /********* 保存设置参数- 内部温度传感器温度采样速率  ******************/
 static void In_Temp_Sample_Rate_Enter_Page_Load(void);
 static void In_Temp_Sample_Rate_Enter_Page_Exit(void);
 static void In_Temp_Sample_Rate_Enter_Page_Task(void);
 /************* 内部温度传感器公共回调函数  *******************/
 static void Humiture_Slcet_Set_Buttons_CB( key_Input_Number_Typedef key_number , Key_Trg_Even key_state);
 static void Humiture_Slcet_Enter_Window_Buttons_CB( key_Input_Number_Typedef key_number , Key_Trg_Even key_state);

/******************内部参数-温度传感器设置页面选择*********************************/

/* 内部温度传感器设置菜单*/
static MenuList_t Internal_Temp_Set_Menu_Table[] =
{
    {"设备地址复归", NULL, Device_Addr_Reversion_Page_Load, Device_Addr_Reversion_Page_Exit, Device_Addr_Reversion_Page_Task, NULL},

    {"温度校验补偿", NULL, In_Temp_Compensation_Page_Load, In_Temp_Compensation_Page_Exit, In_Temp_Compensation_PageTask, NULL},

    {"高温报警阈值", NULL, In_Temp_Alarm_Threshold_Page_Load, In_Temp_Alarm_Threshold_Page_Exit, In_Temp_Alarm_Threshold_Page_Task, NULL},

    {"温度采集速率", NULL,  In_Temp_Acquisition_Rate_Page_Load, In_Temp_Acquisition_Rate_Page_Exit, In_Temp_Acquisition_Rate_Page_Task, NULL},

    {"返回上级菜单", NULL,  Return_Previous_Menu_Page_Load, NULL, NULL, NULL},

    {"返回主页面", NULL,  Back_Main_Page_Load,   NULL,   NULL, NULL},
};


static void MenuDateShow_Init(void){
	system_para_def system_para_t ;
	set_in_temp_menu_list_pararm_t.In_Temp_ShowCompensationDate_t = show_in_temp_compensation_date ;    //显示温度补偿值
	set_in_temp_menu_list_pararm_t.In_Temp_ShowAlarmThresholdDate = show_in_temp_alarm_threshold_date ; //显示温度报警阈值
	set_in_temp_menu_list_pararm_t.In_Temp_ShowSampleRateDate = show_in_temp_humiture_sample_rate_date ;//显示温度采集速率
	read_saveenv_cjson_system_parameter(&system_para_t);
	set_in_temp_menu_list_pararm_t.auto_exit_sets_page_to_main_time = system_para_t.AutoExitSetsPageTime;
}

/* 设置地址复位初始化*/
static void Device_Addr_Reversion_Init(void){
	struct dev_address_reset_par in_temp_address_reset_par ;
	in_temp_address_reset_par.setting_sleet_type_flag = 0 ;
	in_temp_address_reset_par.setting_cursor_dev_var_addr = INTERNAL_TEMP_DEV_ADDERSS_RESET_CURSOR_ADDERSS ;
	in_temp_address_reset_par.setting_dev_reset_page = PAGE_INTERNAL_TEMP_DEV_ADDR_SETTING_NUMBER ;
	in_temp_address_reset_par.auto_exit_setting_page_time = set_in_temp_menu_list_pararm_t.auto_exit_sets_page_to_main_time ;
	in_temp_address_reset_par.dev_addr_reset_wait_var_addr = INTERNAL_TEMP_DEV_ADDR_RESET_WAIT_WINDOW_VAR_ADDERSS ;
	in_temp_address_reset_par.dev_addr_reset_success_var_addr = INTERNAL_TEMP_DEV_ADDR_RESET_SUCCESS_WINDOW_VAR_ADDERSS ;
	in_temp_address_reset_par.dev_addr_reset_error_var_addr = INTERNAL_TEMP_DEV_ADDR_RESET_ERROR_WINDOW_VAR_ADDERSS ;
	/* 设置设备地址确定执行函数 */
	in_temp_address_reset_par.dev_reset_execute_function_cb = In_Temp_Setting_Dev_Transducer_Reset_Addr;
	Device_Addr_Reversion_Load_Init( &in_temp_address_reset_par);
}
/* 设置地址复位执行函数*/
static void In_Temp_Setting_Dev_Transducer_Reset_Addr(void){
	Setting_Dev_Transducer_Reset_Addr( interior_temperature_transducer ) ;
}

/* 设置菜单显示效果 */
static void Humiture_SetMenu(  MenuShow_t *ptShowInfo){
	show_refresh_time();
	show_eth_connect_state();
}


/********************************************** 切换页面 - 内部温度传感器选择设置页面  ***************************************************************/
void Internal_Temp_Setting_Page_Load(void){

	log_d("Hmi_Main_Internal_Setting_Page_Load ");
	type_slect_move_cursor slect_move_cursor;


	slect_move_cursor.dw_cursor_adderss = INTERNAL_TEMP_DEV_SETTING_CURSOR_ADDERSS ;
	slect_move_cursor.max_slect_move = 5 ;
	slect_move_cursor.min_slect_move = 0 ;
	slect_move_cursor.move_slect_step = 1 ;
	slect_move_cursor.now_slect_move = 0 ;
	slect_cursor_move_init(&slect_move_cursor);  //光标位置初始化
	dw_show_switching_pages(PAGE_INTERNAL_TEMP_SETTING_NUMBER); //切换页面
	slect_cursor_move(cursor_default_mode,cursor_null);  //初始化选择设置光标
	Buttons_Register(KEY_UP_TRG_NUMBER,Humiture_Slcet_Set_Buttons_CB);
	Buttons_Register(KEY_ENTER_TRG_NUMBER,Humiture_Slcet_Set_Buttons_CB);
	Buttons_Register(KEY_DOWN_TRG_NUMBER,Humiture_Slcet_Set_Buttons_CB);
	MenuDateShow_Init();
	Device_Addr_Reversion_Init();
	//clear_time_cnt(AUTO_EXIT_SETS_PAGE_TO_MAIN_PAGE_TIMER_NUMBER);
	Menu_Bind(Internal_Temp_Set_Menu_Table, GET_MENU_NUM(Internal_Temp_Set_Menu_Table), Humiture_SetMenu);
}

void Internal_Temp_Setting_Page_Exit(void){
	//clear_time_cnt(AUTO_EXIT_SETS_PAGE_TO_MAIN_PAGE_TIMER_NUMBER);
}

void Internal_Temp_Setting_Page_Task(void){
	if(check_time_arrive(AUTO_EXIT_SETS_PAGE_TO_MAIN_PAGE_TIMER_NUMBER,set_in_temp_menu_list_pararm_t.auto_exit_sets_page_to_main_time*1000)){
		Back_Main_Page_Load();
		//clear_time_cnt(AUTO_EXIT_SETS_PAGE_TO_MAIN_PAGE_TIMER_NUMBER);
	}
}






/********************************************** 切换页面 - 内部温度传感器温度校验补偿页面  ***************************************************************/
/* 内部温度传感器温度校验补偿菜单 */
static MenuList_t Internal_Temp_Set_Compensation_Menu_Table[] =
{
	{"参数输入框", NULL, In_Temp_Device_Compensation_Input_Page_Load, In_Temp_Device_Compensation_Input_Page_Exit, In_Temp_Device_Compensation_Input_Page_Task, NULL},

    {"保存设置参数", NULL, In_Temp_Device_Set_Compensation_Enter_Page_Load, In_Temp_Device_Set_Compensation_Enter_Page_Exit, In_Temp_Device_Set_Compensation_Page_Task, NULL},

    {"返回上级菜单", NULL,  Return_Previous_Menu_Page_Load, NULL, NULL, NULL},

    {"返回主页面", NULL,  Back_Main_Page_Load,   NULL,   NULL, NULL},
};

static void In_Temp_Compensation_Page_Load(void){

	type_slect_move_cursor slect_move_cursor;

	slect_move_cursor.dw_cursor_adderss = INTERNAL_TEMP_COMPENSATION_INPUT_SELECT_CURSOR_ADDERSS ;
	slect_move_cursor.max_slect_move = 2 ;
	slect_move_cursor.min_slect_move = 0 ;
	slect_move_cursor.move_slect_step = 1 ;
	slect_move_cursor.now_slect_move = 0 ;
	slect_cursor_move_init(&slect_move_cursor);  //光标位置初始化
	slect_cursor_move(cursor_refresh_mode,cursor_null);  //关闭光标
	slect_move_cursor.dw_cursor_adderss = INTERNAL_TEMP_COMPENSATION_SELECT_CURSOR_ADDERSS ;
	slect_move_cursor.max_slect_move = 3 ;
	slect_move_cursor.min_slect_move = 0 ;
	slect_move_cursor.move_slect_step = 1 ;
	slect_move_cursor.now_slect_move = 0 ;
	slect_cursor_move_init(&slect_move_cursor); 		 			//光标位置初始化
	slect_cursor_move(cursor_default_mode,cursor_null);  			//初始化选择设置光标
	read_saveenv_cjson_internal_parameter(&set_in_temp_menu_list_pararm_t.inernal_para);
	set_in_temp_menu_list_pararm_t.In_Temp_ShowCompensationDate_t(set_in_temp_menu_list_pararm_t.inernal_para.InternalTemperatureCompensationDate);  //显示温度补偿值
	dw_show_switching_pages(PAGE_INTERNAL_TEMP_COMPENSATION_SETTING_NUMBER); //切换页面
	Buttons_Register(KEY_UP_TRG_NUMBER,Humiture_Slcet_Set_Buttons_CB);
	Buttons_Register(KEY_ENTER_TRG_NUMBER,Humiture_Slcet_Set_Buttons_CB);
	Buttons_Register(KEY_DOWN_TRG_NUMBER,Humiture_Slcet_Set_Buttons_CB);
	Menu_Bind(Internal_Temp_Set_Compensation_Menu_Table, GET_MENU_NUM(Internal_Temp_Set_Compensation_Menu_Table), Humiture_SetMenu);
}
static void In_Temp_Compensation_Page_Exit(void){
	//clear_time_cnt(AUTO_EXIT_SETS_PAGE_TO_MAIN_PAGE_TIMER_NUMBER);
}
static void In_Temp_Compensation_PageTask(void){
	if(check_time_arrive(AUTO_EXIT_SETS_PAGE_TO_MAIN_PAGE_TIMER_NUMBER,set_in_temp_menu_list_pararm_t.auto_exit_sets_page_to_main_time*1000)){
		Back_Main_Page_Load();
		//clear_time_cnt(AUTO_EXIT_SETS_PAGE_TO_MAIN_PAGE_TIMER_NUMBER);
	}
}
/************* 输入参数- 内部温度传感器温度校验补偿页面  *******************/
static void In_Temp_Device_Compensation_Input_Page_Load(void){
	type_slect_move_cursor slect_move_cursor;
	slect_move_cursor.dw_cursor_adderss = INTERNAL_TEMP_COMPENSATION_SELECT_CURSOR_ADDERSS ;
	slect_move_cursor.max_slect_move = 3 ;
	slect_move_cursor.min_slect_move = 0 ;
	slect_move_cursor.move_slect_step = 1 ;
	slect_move_cursor.now_slect_move = 0 ;
	slect_cursor_move_init(&slect_move_cursor);  //光标位置初始化
	slect_cursor_move(cursor_refresh_mode,cursor_null);  //关闭光标
	slect_move_cursor.dw_cursor_adderss = INTERNAL_TEMP_COMPENSATION_INPUT_SELECT_CURSOR_ADDERSS ;
	slect_move_cursor.max_slect_move = 2 ;
	slect_move_cursor.min_slect_move = 0 ;
	slect_move_cursor.move_slect_step = 1 ;
	slect_move_cursor.now_slect_move = 0 ;
	slect_cursor_move_init(&slect_move_cursor);  //光标位置初始化
	slect_cursor_move(cursor_default_mode,cursor_null);  //显示初始化光标位置
	Buttons_Register(KEY_UP_TRG_NUMBER,Hmi_Internal_Temp_Compensation_Slcet_Input_Buttons_CB);
	Buttons_Register(KEY_ENTER_TRG_NUMBER,Hmi_Internal_Temp_Compensation_Slcet_Input_Buttons_CB);
	Buttons_Register(KEY_DOWN_TRG_NUMBER,Hmi_Internal_Temp_Compensation_Slcet_Input_Buttons_CB);
}

static void In_Temp_Device_Compensation_Input_Page_Exit(void){
	//clear_time_cnt(AUTO_EXIT_SETS_PAGE_TO_MAIN_PAGE_TIMER_NUMBER);
}

static void In_Temp_Device_Compensation_Input_Page_Task(void){
	if(check_time_arrive(AUTO_EXIT_SETS_PAGE_TO_MAIN_PAGE_TIMER_NUMBER,set_in_temp_menu_list_pararm_t.auto_exit_sets_page_to_main_time*1000)){
		Back_Main_Page_Load();
		//clear_time_cnt(AUTO_EXIT_SETS_PAGE_TO_MAIN_PAGE_TIMER_NUMBER);
	}
}


static void Hmi_Internal_Temp_Compensation_Slcet_Input_Buttons_CB(key_Input_Number_Typedef key_number ,Key_Trg_Even key_state){
	if(key_state == KEY_CLICK_ACTION){
		//clear_time_cnt(AUTO_EXIT_SETS_PAGE_TO_MAIN_PAGE_TIMER_NUMBER);
		set_in_temp_menu_list_pararm_t.inernal_para.InternalTemperatureCompensationDate=user_parameter_adjustment(set_in_temp_menu_list_pararm_t.inernal_para.InternalTemperatureCompensationDate,1,2,key_number,set_in_temp_menu_list_pararm_t.In_Temp_ShowCompensationDate_t);
	}
}

/********* 保存设置参数- 内部温度传感器温度校验补偿  ******************/
static void In_Temp_Device_Set_Compensation_Enter_Page_Load(void){
	int ret = -1 ;
	type_slect_move_cursor slect_move_cursor;
	slect_move_cursor.dw_cursor_adderss = INTERNAL_TEMP_COMPENSATION_SELECT_CURSOR_ADDERSS ;
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
	dw_input_parameter_hint_window( 1 ,INTERNAL_TEMP_COMPENSATION_WAIT_WINDOW_VAR_ADDERSS,INTERNAL_TEMP_COMPENSATION_SUCCESS_WINDOW_VAR_ADDERSS,INTERNAL_TEMP_COMPENSATION_ERROR_WINDOW_VAR_ADDERSS);
	ret = internalparaPoint_amend_config("InternalTemperatureCompensationDate",set_in_temp_menu_list_pararm_t.inernal_para.InternalTemperatureCompensationDate);
	if( !ret){
		 //显示成功窗口
		dw_input_parameter_hint_window(2,INTERNAL_TEMP_COMPENSATION_WAIT_WINDOW_VAR_ADDERSS,INTERNAL_TEMP_COMPENSATION_SUCCESS_WINDOW_VAR_ADDERSS,INTERNAL_TEMP_COMPENSATION_ERROR_WINDOW_VAR_ADDERSS);
	}else{
		//显示错误窗口
		dw_input_parameter_hint_window( 3 ,INTERNAL_TEMP_COMPENSATION_WAIT_WINDOW_VAR_ADDERSS,INTERNAL_TEMP_COMPENSATION_SUCCESS_WINDOW_VAR_ADDERSS,INTERNAL_TEMP_COMPENSATION_ERROR_WINDOW_VAR_ADDERSS);
	}
	Buttons_Register(KEY_ENTER_TRG_NUMBER,Humiture_Slcet_Enter_Window_Buttons_CB);
}

static void In_Temp_Device_Set_Compensation_Enter_Page_Exit(void){
	//清除窗口
	dw_input_parameter_hint_window( 0 ,INTERNAL_TEMP_COMPENSATION_WAIT_WINDOW_VAR_ADDERSS,INTERNAL_TEMP_COMPENSATION_SUCCESS_WINDOW_VAR_ADDERSS,INTERNAL_TEMP_COMPENSATION_ERROR_WINDOW_VAR_ADDERSS);
	//clear_time_cnt(AUTO_EXIT_SETS_PAGE_TO_MAIN_PAGE_TIMER_NUMBER);
}

static void In_Temp_Device_Set_Compensation_Page_Task(void){
	if(check_time_arrive(AUTO_EXIT_SETS_PAGE_TO_MAIN_PAGE_TIMER_NUMBER,set_in_temp_menu_list_pararm_t.auto_exit_sets_page_to_main_time*1000)){
		Back_Main_Page_Load();
		//clear_time_cnt(AUTO_EXIT_SETS_PAGE_TO_MAIN_PAGE_TIMER_NUMBER);
	}
}

/********************************************** 切换页面 - 内部温度传感器高温报警阈值页面  ***************************************************************/
/* 内部温度传感器温度校验补偿菜单 */
static MenuList_t Internal_Temp_Alarm_Threshold_Menu_Table[] =
{
	{"参数输入框", NULL, In_Temp_Alarm_Threshold_Input_Page_Load, In_Temp_Alarm_Threshold_Input_Page_Exit, In_Temp_Alarm_Threshold_Input_Page_Task, NULL},

    {"保存设置参数", NULL, In_Temp_Alarm_Threshold_Enter_Page_Load, In_Temp_Alarm_Threshold_Enter_Page_Exit, In_Temp_Alarm_Threshold_Enter_Page_Task, NULL},

    {"返回上级菜单", NULL,  Return_Previous_Menu_Page_Load, NULL, NULL, NULL},

    {"返回主页面", NULL,  Back_Main_Page_Load,   NULL,   NULL, NULL},
};



static void In_Temp_Alarm_Threshold_Page_Load(void){
	type_slect_move_cursor slect_move_cursor;

	slect_move_cursor.dw_cursor_adderss = INTERNAL_TEMP_ALARM_THERSHOLD_INPUT_SELECT_CURSOR_ADDERSS ;
	slect_move_cursor.max_slect_move = 1 ;
	slect_move_cursor.min_slect_move = 0 ;
	slect_move_cursor.move_slect_step = 1 ;
	slect_move_cursor.now_slect_move = 0 ;
	slect_cursor_move_init(&slect_move_cursor);  		//光标位置初始化
	slect_cursor_move(cursor_refresh_mode,cursor_null);  //关闭输入指示光标
	slect_move_cursor.dw_cursor_adderss = INTERNAL_TEMP_ALARM_THERSHOLD_SELECT_CURSOR_ADDERSS ;
	slect_move_cursor.max_slect_move = 3 ;
	slect_move_cursor.min_slect_move = 0 ;
	slect_move_cursor.move_slect_step = 1 ;
	slect_move_cursor.now_slect_move = 0 ;
	slect_cursor_move_init(&slect_move_cursor); 		 			//光标位置初始化
	slect_cursor_move(cursor_default_mode,cursor_null);  			//初始化选择设置光标
	read_saveenv_cjson_internal_parameter(&set_in_temp_menu_list_pararm_t.inernal_para);
	set_in_temp_menu_list_pararm_t.In_Temp_ShowAlarmThresholdDate(set_in_temp_menu_list_pararm_t.inernal_para.InternalAlarmTemperature);  //显示高温阈值
	dw_show_switching_pages(PAGE_INTERNAL_TEMP_ALARM_THRESHOLD_SETTING_NUMBER); //切换页面
	Buttons_Register(KEY_UP_TRG_NUMBER,Humiture_Slcet_Set_Buttons_CB);
	Buttons_Register(KEY_ENTER_TRG_NUMBER,Humiture_Slcet_Set_Buttons_CB);
	Buttons_Register(KEY_DOWN_TRG_NUMBER,Humiture_Slcet_Set_Buttons_CB);
	Menu_Bind(Internal_Temp_Alarm_Threshold_Menu_Table, GET_MENU_NUM(Internal_Temp_Alarm_Threshold_Menu_Table), Humiture_SetMenu);
}
static void In_Temp_Alarm_Threshold_Page_Exit(void){
	//clear_time_cnt(AUTO_EXIT_SETS_PAGE_TO_MAIN_PAGE_TIMER_NUMBER);
}
static void In_Temp_Alarm_Threshold_Page_Task(void){
	if(check_time_arrive(AUTO_EXIT_SETS_PAGE_TO_MAIN_PAGE_TIMER_NUMBER,set_in_temp_menu_list_pararm_t.auto_exit_sets_page_to_main_time*1000)){
		Back_Main_Page_Load();
		//clear_time_cnt(AUTO_EXIT_SETS_PAGE_TO_MAIN_PAGE_TIMER_NUMBER);
	}
}
/************* 输入参数- 内部温度传感器高温阈值页面  *******************/
static void In_Temp_Alarm_Threshold_Input_Page_Load(void){
	type_slect_move_cursor slect_move_cursor;

	slect_move_cursor.dw_cursor_adderss = INTERNAL_TEMP_ALARM_THERSHOLD_SELECT_CURSOR_ADDERSS ;
	slect_move_cursor.max_slect_move = 3 ;
	slect_move_cursor.min_slect_move = 0 ;
	slect_move_cursor.move_slect_step = 1 ;
	slect_move_cursor.now_slect_move = 0 ;
	slect_cursor_move_init(&slect_move_cursor);  //光标位置初始化
	slect_cursor_move(cursor_refresh_mode,cursor_null);  //关闭选择设置光标
	slect_move_cursor.dw_cursor_adderss = INTERNAL_TEMP_ALARM_THERSHOLD_INPUT_SELECT_CURSOR_ADDERSS ;
	slect_move_cursor.max_slect_move = 1 ;
	slect_move_cursor.min_slect_move = 0 ;
	slect_move_cursor.move_slect_step = 1 ;
	slect_move_cursor.now_slect_move = 0 ;
	slect_cursor_move_init(&slect_move_cursor);  //光标位置初始化
	slect_cursor_move(cursor_default_mode,cursor_null);  //显示初始化输入指示光标位置
	Buttons_Register(KEY_UP_TRG_NUMBER,Hmi_Internal_Temp_Alarm_Threshold_Input_Buttons_CB);
	Buttons_Register(KEY_ENTER_TRG_NUMBER,Hmi_Internal_Temp_Alarm_Threshold_Input_Buttons_CB);
	Buttons_Register(KEY_DOWN_TRG_NUMBER,Hmi_Internal_Temp_Alarm_Threshold_Input_Buttons_CB);
}

static void In_Temp_Alarm_Threshold_Input_Page_Exit(void){
	//clear_time_cnt(AUTO_EXIT_SETS_PAGE_TO_MAIN_PAGE_TIMER_NUMBER);
}

static void In_Temp_Alarm_Threshold_Input_Page_Task(void){
	if(check_time_arrive(AUTO_EXIT_SETS_PAGE_TO_MAIN_PAGE_TIMER_NUMBER,set_in_temp_menu_list_pararm_t.auto_exit_sets_page_to_main_time*1000)){
		Back_Main_Page_Load();
		//clear_time_cnt(AUTO_EXIT_SETS_PAGE_TO_MAIN_PAGE_TIMER_NUMBER);
	}
}


static void Hmi_Internal_Temp_Alarm_Threshold_Input_Buttons_CB(key_Input_Number_Typedef key_number ,Key_Trg_Even key_state){
	if(key_state == KEY_CLICK_ACTION){
		//clear_time_cnt(AUTO_EXIT_SETS_PAGE_TO_MAIN_PAGE_TIMER_NUMBER);
		set_in_temp_menu_list_pararm_t.inernal_para.InternalAlarmTemperature=user_parameter_adjustment(set_in_temp_menu_list_pararm_t.inernal_para.InternalAlarmTemperature,false,2,key_number,set_in_temp_menu_list_pararm_t.In_Temp_ShowAlarmThresholdDate);
	}
}

/********* 保存设置参数- 内部温度传感器高温阈值  ******************/
static void In_Temp_Alarm_Threshold_Enter_Page_Load(void){
	int ret = -1 ;
	type_slect_move_cursor slect_move_cursor;
	slect_move_cursor.dw_cursor_adderss = INTERNAL_TEMP_ALARM_THERSHOLD_SELECT_CURSOR_ADDERSS ;
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
	dw_input_parameter_hint_window( 1 ,INTERNAL_TEMP_ALARM_THERSHOLD_WAIT_WINDOW_VAR_ADDERSS,INTERNAL_TEMP_ALARM_THERSHOLD_SUCCESS_WINDOW_VAR_ADDERSS,INTERNAL_TEMP_ALARM_THERSHOLD_ERROR_WINDOW_VAR_ADDERSS);
	ret = internalparaPoint_amend_config("InternalAlarmTemperature",set_in_temp_menu_list_pararm_t.inernal_para.InternalAlarmTemperature);
	if( !ret){
		 //显示成功窗口
		dw_input_parameter_hint_window(2,INTERNAL_TEMP_ALARM_THERSHOLD_WAIT_WINDOW_VAR_ADDERSS,INTERNAL_TEMP_ALARM_THERSHOLD_SUCCESS_WINDOW_VAR_ADDERSS,INTERNAL_TEMP_ALARM_THERSHOLD_ERROR_WINDOW_VAR_ADDERSS);
	}else{
		//显示错误窗口
		dw_input_parameter_hint_window( 3 ,INTERNAL_TEMP_ALARM_THERSHOLD_WAIT_WINDOW_VAR_ADDERSS,INTERNAL_TEMP_ALARM_THERSHOLD_SUCCESS_WINDOW_VAR_ADDERSS,INTERNAL_TEMP_ALARM_THERSHOLD_ERROR_WINDOW_VAR_ADDERSS);
	}
	Buttons_Register(KEY_ENTER_TRG_NUMBER,Humiture_Slcet_Enter_Window_Buttons_CB);
}

static void In_Temp_Alarm_Threshold_Enter_Page_Exit(void){
	//清除窗口
	dw_input_parameter_hint_window( 0 ,INTERNAL_TEMP_ALARM_THERSHOLD_WAIT_WINDOW_VAR_ADDERSS,INTERNAL_TEMP_ALARM_THERSHOLD_SUCCESS_WINDOW_VAR_ADDERSS,INTERNAL_TEMP_ALARM_THERSHOLD_ERROR_WINDOW_VAR_ADDERSS);
	//clear_time_cnt(AUTO_EXIT_SETS_PAGE_TO_MAIN_PAGE_TIMER_NUMBER);
}

static void In_Temp_Alarm_Threshold_Enter_Page_Task(void){
	if(check_time_arrive(AUTO_EXIT_SETS_PAGE_TO_MAIN_PAGE_TIMER_NUMBER,set_in_temp_menu_list_pararm_t.auto_exit_sets_page_to_main_time*1000)){
		Back_Main_Page_Load();
		//clear_time_cnt(AUTO_EXIT_SETS_PAGE_TO_MAIN_PAGE_TIMER_NUMBER);
	}
}

/********************************************** 切换页面 - 内部温度传感器温度采集速率页面  ***************************************************************/
/* 内部温度传感器温度采集速率菜单 */
static MenuList_t Internal_Temp_Sample_Rate_Menu_Table[] =
{
	{"参数输入框", NULL, In_Temp_Sample_Rate_Input_Page_Load, In_Temp_Sample_Rate_Input_Page_Exit, In_Temp_Sample_Rate_Input_Page_Task, NULL},

    {"保存设置参数", NULL, In_Temp_Sample_Rate_Enter_Page_Load, In_Temp_Sample_Rate_Enter_Page_Exit, In_Temp_Sample_Rate_Enter_Page_Task, NULL},

    {"返回上级菜单", NULL,  Return_Previous_Menu_Page_Load, NULL, NULL, NULL},

    {"返回主页面", NULL,  Back_Main_Page_Load,   NULL,   NULL, NULL},
};

static void In_Temp_Acquisition_Rate_Page_Load(void){
	type_slect_move_cursor slect_move_cursor;

	slect_move_cursor.dw_cursor_adderss = INTERNAL_TEMP_SAMPLE_RATE_INPUT_SELECT_CURSOR_ADDERSS ;
	slect_move_cursor.max_slect_move = 1 ;
	slect_move_cursor.min_slect_move = 0 ;
	slect_move_cursor.move_slect_step = 1 ;
	slect_move_cursor.now_slect_move = 0 ;
	slect_cursor_move_init(&slect_move_cursor);  		//输入指示光标位置初始化
	slect_cursor_move(cursor_refresh_mode,cursor_null);  //关闭输入指示光标
	slect_move_cursor.dw_cursor_adderss = INTERNAL_TEMP_SAMPLE_RATE_SELECT_CURSOR_ADDERSS ;
	slect_move_cursor.max_slect_move = 3 ;
	slect_move_cursor.min_slect_move = 0 ;
	slect_move_cursor.move_slect_step = 1 ;
	slect_move_cursor.now_slect_move = 0 ;
	slect_cursor_move_init(&slect_move_cursor); 		 			//光标位置初始化
	slect_cursor_move(cursor_default_mode,cursor_null);  			//初始化选择设置光标
	read_saveenv_cjson_internal_parameter(&set_in_temp_menu_list_pararm_t.inernal_para);
	set_in_temp_menu_list_pararm_t.In_Temp_ShowSampleRateDate(set_in_temp_menu_list_pararm_t.inernal_para.InternalHumitureSampleRate); //显示采样速率
	dw_show_switching_pages(PAGE_INTERNAL_TEMP_SAMPLE_RATE_SETTING_NUMBER); //切换页面
	Buttons_Register(KEY_UP_TRG_NUMBER,Humiture_Slcet_Set_Buttons_CB);
	Buttons_Register(KEY_ENTER_TRG_NUMBER,Humiture_Slcet_Set_Buttons_CB);
	Buttons_Register(KEY_DOWN_TRG_NUMBER,Humiture_Slcet_Set_Buttons_CB);
	Menu_Bind(Internal_Temp_Sample_Rate_Menu_Table, GET_MENU_NUM(Internal_Temp_Sample_Rate_Menu_Table), Humiture_SetMenu);
}

static void In_Temp_Acquisition_Rate_Page_Exit(void){
	//clear_time_cnt(AUTO_EXIT_SETS_PAGE_TO_MAIN_PAGE_TIMER_NUMBER);
}
static void In_Temp_Acquisition_Rate_Page_Task(void){
	if(check_time_arrive(AUTO_EXIT_SETS_PAGE_TO_MAIN_PAGE_TIMER_NUMBER,set_in_temp_menu_list_pararm_t.auto_exit_sets_page_to_main_time*1000)){
		Back_Main_Page_Load();
		//clear_time_cnt(AUTO_EXIT_SETS_PAGE_TO_MAIN_PAGE_TIMER_NUMBER);
	}
}

/************* 输入参数- 内部温度传感器温湿度采样速率页面  *******************/
static void In_Temp_Sample_Rate_Input_Page_Load(void){
	type_slect_move_cursor slect_move_cursor;

	slect_move_cursor.dw_cursor_adderss = INTERNAL_TEMP_SAMPLE_RATE_SELECT_CURSOR_ADDERSS ;
	slect_move_cursor.max_slect_move = 3 ;
	slect_move_cursor.min_slect_move = 0 ;
	slect_move_cursor.move_slect_step = 1 ;
	slect_move_cursor.now_slect_move = 0 ;
	slect_cursor_move_init(&slect_move_cursor);  //光标位置初始化
	slect_cursor_move(cursor_refresh_mode,cursor_null);  //关闭选择设置光标
	slect_move_cursor.dw_cursor_adderss = INTERNAL_TEMP_SAMPLE_RATE_INPUT_SELECT_CURSOR_ADDERSS ;
	slect_move_cursor.max_slect_move = 1 ;
	slect_move_cursor.min_slect_move = 0 ;
	slect_move_cursor.move_slect_step = 1 ;
	slect_move_cursor.now_slect_move = 0 ;
	slect_cursor_move_init(&slect_move_cursor);  //光标位置初始化
	slect_cursor_move(cursor_default_mode,cursor_null);  //显示初始化输入指示光标位置
	Buttons_Register(KEY_UP_TRG_NUMBER,Hmi_Internal_Temp_Sample_Rate_Input_Buttons_CB);
	Buttons_Register(KEY_ENTER_TRG_NUMBER,Hmi_Internal_Temp_Sample_Rate_Input_Buttons_CB);
	Buttons_Register(KEY_DOWN_TRG_NUMBER,Hmi_Internal_Temp_Sample_Rate_Input_Buttons_CB);
}

static void In_Temp_Sample_Rate_Input_Page_Exit(void){
	//clear_time_cnt(AUTO_EXIT_SETS_PAGE_TO_MAIN_PAGE_TIMER_NUMBER);
}

static void In_Temp_Sample_Rate_Input_Page_Task(void){
	if(check_time_arrive(AUTO_EXIT_SETS_PAGE_TO_MAIN_PAGE_TIMER_NUMBER,set_in_temp_menu_list_pararm_t.auto_exit_sets_page_to_main_time*1000)){
		Back_Main_Page_Load();
		//clear_time_cnt(AUTO_EXIT_SETS_PAGE_TO_MAIN_PAGE_TIMER_NUMBER);
	}
}

static void Hmi_Internal_Temp_Sample_Rate_Input_Buttons_CB(key_Input_Number_Typedef key_number ,Key_Trg_Even key_state){
	if(key_state == KEY_CLICK_ACTION){
		//clear_time_cnt(AUTO_EXIT_SETS_PAGE_TO_MAIN_PAGE_TIMER_NUMBER);
		set_in_temp_menu_list_pararm_t.inernal_para.InternalHumitureSampleRate=user_parameter_adjustment(set_in_temp_menu_list_pararm_t.inernal_para.InternalHumitureSampleRate,0,2,key_number,set_in_temp_menu_list_pararm_t.In_Temp_ShowSampleRateDate);
	}
}

/********* 保存设置参数- 内部温度传感器温度采样速率  ******************/
static void In_Temp_Sample_Rate_Enter_Page_Load(void){
	int ret = -1 ;
	type_slect_move_cursor slect_move_cursor;
	slect_move_cursor.dw_cursor_adderss = INTERNAL_TEMP_SAMPLE_RATE_SELECT_CURSOR_ADDERSS ;
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
	dw_input_parameter_hint_window( 1 ,INTERNAL_TEMP_SAMPLE_RATE_WAIT_WINDOW_VAR_ADDERSS,INTERNAL_TEMP_SAMPLE_RATE_SUCCESS_WINDOW_VAR_ADDERSS,INTERNAL_TEMP_SAMPLE_RATE_ERROR_WINDOW_VAR_ADDERSS);
	ret = internalparaPoint_amend_config("InternalHumitureSampleRate",set_in_temp_menu_list_pararm_t.inernal_para.InternalHumitureSampleRate);
	if( !ret){
		 //显示成功窗口
		dw_input_parameter_hint_window(2,INTERNAL_TEMP_SAMPLE_RATE_WAIT_WINDOW_VAR_ADDERSS,INTERNAL_TEMP_SAMPLE_RATE_SUCCESS_WINDOW_VAR_ADDERSS,INTERNAL_TEMP_SAMPLE_RATE_ERROR_WINDOW_VAR_ADDERSS);
	}else{
		//显示错误窗口
		dw_input_parameter_hint_window( 3 ,INTERNAL_TEMP_SAMPLE_RATE_WAIT_WINDOW_VAR_ADDERSS,INTERNAL_TEMP_SAMPLE_RATE_SUCCESS_WINDOW_VAR_ADDERSS,INTERNAL_TEMP_SAMPLE_RATE_ERROR_WINDOW_VAR_ADDERSS);
	}
	Buttons_Register(KEY_ENTER_TRG_NUMBER,Humiture_Slcet_Enter_Window_Buttons_CB);
}

static void In_Temp_Sample_Rate_Enter_Page_Exit(void){
	//清除窗口
		dw_input_parameter_hint_window( 0 ,INTERNAL_TEMP_SAMPLE_RATE_WAIT_WINDOW_VAR_ADDERSS,INTERNAL_TEMP_SAMPLE_RATE_SUCCESS_WINDOW_VAR_ADDERSS,INTERNAL_TEMP_SAMPLE_RATE_ERROR_WINDOW_VAR_ADDERSS);
		//clear_time_cnt(AUTO_EXIT_SETS_PAGE_TO_MAIN_PAGE_TIMER_NUMBER);
}

static void In_Temp_Sample_Rate_Enter_Page_Task(void){
	if(check_time_arrive(AUTO_EXIT_SETS_PAGE_TO_MAIN_PAGE_TIMER_NUMBER,set_in_temp_menu_list_pararm_t.auto_exit_sets_page_to_main_time*1000)){
		Back_Main_Page_Load();
		//clear_time_cnt(AUTO_EXIT_SETS_PAGE_TO_MAIN_PAGE_TIMER_NUMBER);
	}
}

/************* 内部温度传感器公共回调函数  *******************/
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
