/*
 * hmi_humi.c
 *
 *  Created on: 2023年2月13日
 *      Author: 好
 */

#define LOG_TAG    "internal/hmi_humi"

#include "../himi/internal/hmi_humi.h"



struct set_in_humi_menu_list_pararm{
	int auto_exit_sets_page_to_main_time ;  //自动返回时间
	internal_para_def internal_para ;
	ShownMenuDate In_Humi_ShowCompensationDate_t;
	ShownMenuDate In_Humi_ShowAlarmThresholdDate ;
	ShownMenuDate In_Humi_ShowSampleRateDate ;
};


static struct set_in_humi_menu_list_pararm set_in_humi_menu_list_pararm_t ;

 /******************内部参数-湿度传感器设置页面选择*********************************/
 /* 设置菜单显示效果 */
static void MenuDateShow_Init(void);
/* 设置地址复位初始化*/
static void Device_Addr_Reversion_Init(void);
/* 设置地址复位执行函数*/
static void In_Humi_Setting_Dev_Transducer_Reset_Addr(void);

static void Humidity_SetMenu(  MenuShow_t *ptShowInfo);
 /********************************************** 切换页面 - 内部湿度传感器湿度校验补偿页面  ***************************************************************/
 static void In_Humidity_Compensation_Page_Load(void);
 static void In_Humidity_Compensation_Page_Exit(void);
 static void In_Humidity_Compensation_PageTask(void);
 /************* 输入参数- 内部湿度传感器湿度校验补偿页面  *******************/
 static void In_Humidity_Device_Compensation_Input_Page_Load(void);
 static void In_Humidity_Device_Compensation_Input_Page_Exit(void);
 static void In_Humidity_Device_Compensation_Input_Page_Task(void);
 static void Hmi_INTERNAL_Humidity_Compensation_Slcet_Input_Buttons_CB(key_Input_Number_Typedef key_number ,Key_Trg_Even key_state);
 /********* 保存设置参数- 内部湿度传感器湿度校验补偿  ******************/
 static void In_Humidity_Device_Set_Compensation_Enter_Page_Load(void);
 static void In_Humidity_Device_Set_Compensation_Enter_Page_Exit(void);
 static void In_Humidity_Device_Set_Compensation_Enter_Task(void);
 /********************************************** 切换页面 - 内部湿度传感器高湿报警阈值页面  ***************************************************************/
 static void In_Humidity_Alarm_Threshold_Page_Load(void);
 static void In_Humidity_Alarm_Threshold_Page_Exit(void);
 static void In_Humidity_Alarm_Threshold_Page_Task(void);
 /************* 输入参数- 内部湿度传感器高湿阈值页面  *******************/
 static void In_Humidity_Alarm_Threshold_Input_Page_Load(void);
 static void In_Humidity_Alarm_Threshold_Input_Page_Exit(void);
 static void In_Humidity_Alarm_Threshold_Input_Page_Task(void);
 static void Hmi_Internal_Humidity_Alarm_Threshold_Input_Buttons_CB(key_Input_Number_Typedef key_number ,Key_Trg_Even key_state);
 /********* 保存设置参数- 内部湿度传感器高湿阈值  ******************/
 static void In_Humidity_Alarm_Threshold_Enter_Page_Load(void);
 static void In_Humidity_Alarm_Threshold_Enter_Page_Exit(void);
 static void In_Humidity_Alarm_Threshold_Enter_Page_Task(void);
 /********************************************** 切换页面 - 内部湿度传感器湿度采集速率页面  ***************************************************************/
 static void In_Humidity_Acquisition_Rate_Page_Load(void);
 static void In_Humidity_Acquisition_Rate_Page_Exit(void);
 static void In_Humidity_Acquisition_Rate_Page_Task(void);
 /************* 输入参数- 内部湿度传感器湿湿度采样速率页面  *******************/
 static void In_Humidity_Sample_Rate_Input_Page_Load(void);
 static void In_Humidity_Sample_Rate_Input_Page_Exit(void);
 static void In_Humidity_Sample_Rate_Input_Page_Task(void);
 static void Hmi_INTERNAL_Humidity_Sample_Rate_Input_Buttons_CB(key_Input_Number_Typedef key_number ,Key_Trg_Even key_state);
 /********* 保存设置参数- 内部湿度传感器湿度采样速率  ******************/
 static void In_Humidity_Sample_Rate_Enter_Page_Load(void);
 static void In_Humidity_Sample_Rate_Enter_Page_Exit(void);
 static void In_Humidity_Sample_Rate_Enter_Page_Task(void);
 /************* 内部湿度传感器公共回调函数  *******************/
 static void Humidity_Slcet_Set_Buttons_CB( key_Input_Number_Typedef key_number , Key_Trg_Even key_state);
 static void Humidity_Slcet_Enter_Window_Buttons_CB( key_Input_Number_Typedef key_number , Key_Trg_Even key_state);

/******************内部参数-湿度传感器设置页面选择*********************************/

/* 内部湿度传感器设置菜单*/
static MenuList_t INTERNAL_Humidity_Set_Menu_Table[] =
{
    {"设备地址复归", NULL, Device_Addr_Reversion_Page_Load, Device_Addr_Reversion_Page_Exit, Device_Addr_Reversion_Page_Task, NULL},

    {"湿度校验补偿", NULL, In_Humidity_Compensation_Page_Load, In_Humidity_Compensation_Page_Exit, In_Humidity_Compensation_PageTask, NULL},

    {"湿度报警阈值", NULL, In_Humidity_Alarm_Threshold_Page_Load, In_Humidity_Alarm_Threshold_Page_Exit, In_Humidity_Alarm_Threshold_Page_Task, NULL},

    {"湿度采集速率", NULL,  In_Humidity_Acquisition_Rate_Page_Load, In_Humidity_Acquisition_Rate_Page_Exit, In_Humidity_Acquisition_Rate_Page_Task, NULL},

    {"返回上级菜单", NULL,  Return_Previous_Menu_Page_Load, NULL, NULL, NULL},

    {"返回主页面", NULL,  Back_Main_Page_Load,   NULL,   NULL, NULL},
};


static void MenuDateShow_Init(void){
	system_para_def system_para_t ;
	set_in_humi_menu_list_pararm_t.In_Humi_ShowCompensationDate_t = show_in_humill_compensation_date ;   //显示湿度补偿值
	set_in_humi_menu_list_pararm_t.In_Humi_ShowAlarmThresholdDate = show_in_humill_alarm_threshold_date ;  //显示湿度报警阈值
	set_in_humi_menu_list_pararm_t.In_Humi_ShowSampleRateDate = show_in_temp_humiture_sample_rate_date ; //显示湿度采集速率
	read_saveenv_cjson_system_parameter(&system_para_t);
	set_in_humi_menu_list_pararm_t.auto_exit_sets_page_to_main_time = system_para_t.AutoExitSetsPageTime;
}

/* 设置地址复位初始化*/
static void Device_Addr_Reversion_Init(void){
	struct dev_address_reset_par in_humi_address_reset_par ;
	in_humi_address_reset_par.setting_sleet_type_flag = 0 ;
	in_humi_address_reset_par.setting_cursor_dev_var_addr = INTERNAL_HUMIDITY_DEV_ADDERSS_RESET_CURSOR_ADDERSS ;
	in_humi_address_reset_par.setting_dev_reset_page = PAGE_INTERNAL_HUMIDITY_DEV_ADDR_SETTING_NUMBER ;
	in_humi_address_reset_par.auto_exit_setting_page_time = set_in_humi_menu_list_pararm_t.auto_exit_sets_page_to_main_time ;
	in_humi_address_reset_par.dev_addr_reset_wait_var_addr = INTERNAL_HUMIDITY_DEV_ADDR_RESET_WAIT_WINDOW_VAR_ADDERSS ;
	in_humi_address_reset_par.dev_addr_reset_success_var_addr = INTERNAL_HUMIDITY_DEV_ADDR_RESET_SUCCESS_WINDOW_VAR_ADDERSS ;
	in_humi_address_reset_par.dev_addr_reset_error_var_addr = INTERNAL_HUMIDITY_DEV_ADDR_RESET_ERROR_WINDOW_VAR_ADDERSS ;
	/* 设置设备地址确定执行函数 */
	in_humi_address_reset_par.dev_reset_execute_function_cb = In_Humi_Setting_Dev_Transducer_Reset_Addr ;
	Device_Addr_Reversion_Load_Init( &in_humi_address_reset_par);
}

/* 设置地址复位执行函数*/
static void In_Humi_Setting_Dev_Transducer_Reset_Addr(void){
	Setting_Dev_Transducer_Reset_Addr( interior_temperature_transducer ) ;
}

/* 设置菜单显示效果 */
static void Humidity_SetMenu(  MenuShow_t *ptShowInfo){
	show_refresh_time();
	show_eth_connect_state();
}



/********************************************** 切换页面 - 内部湿度传感器选择设置页面  ***************************************************************/
void Internal_Humi_Setting_Page_Load(void){
	log_d("Internal_Humi_Setting_Page_Load ");
	type_slect_move_cursor slect_move_cursor;
	slect_move_cursor.dw_cursor_adderss = INTERNAL_HUMIDITY_DEV_SETTING_CURSOR_ADDERSS ;
	slect_move_cursor.max_slect_move = 5 ;
	slect_move_cursor.min_slect_move = 0 ;
	slect_move_cursor.move_slect_step = 1 ;
	slect_move_cursor.now_slect_move = 0 ;
	slect_cursor_move_init(&slect_move_cursor);  						//光标位置初始化
	dw_show_switching_pages(PAGE_INTERNAL_HUMIDITY_SETTING_NUMBER); 	//切换页面
	slect_cursor_move(cursor_default_mode,cursor_null);  				//初始化选择设置显示光标
	Buttons_Register(KEY_UP_TRG_NUMBER,Humidity_Slcet_Set_Buttons_CB);
	Buttons_Register(KEY_ENTER_TRG_NUMBER,Humidity_Slcet_Set_Buttons_CB);
	Buttons_Register(KEY_DOWN_TRG_NUMBER,Humidity_Slcet_Set_Buttons_CB);
	MenuDateShow_Init();
	Device_Addr_Reversion_Init();
	//clear_time_cnt(AUTO_EXIT_SETS_PAGE_TO_MAIN_PAGE_TIMER_NUMBER);
	Menu_Bind(INTERNAL_Humidity_Set_Menu_Table, GET_MENU_NUM(INTERNAL_Humidity_Set_Menu_Table), Humidity_SetMenu);
}

void Internal_Humi_Setting_Page_Exit(void){
	//clear_time_cnt(AUTO_EXIT_SETS_PAGE_TO_MAIN_PAGE_TIMER_NUMBER);
}
void Internal_Humi_Setting_Page_Task(void){
	if(check_time_arrive(AUTO_EXIT_SETS_PAGE_TO_MAIN_PAGE_TIMER_NUMBER,set_in_humi_menu_list_pararm_t.auto_exit_sets_page_to_main_time*1000)){
		Back_Main_Page_Load();
		//clear_time_cnt(AUTO_EXIT_SETS_PAGE_TO_MAIN_PAGE_TIMER_NUMBER);
	}
}






/********************************************** 切换页面 - 内部湿度传感器湿度校验补偿页面  ***************************************************************/
/* 内部湿度传感器湿度校验补偿菜单 */
static MenuList_t Internal_Humidity_Set_Compensation_Menu_Table[] =
{
	{"参数输入框", NULL, In_Humidity_Device_Compensation_Input_Page_Load, In_Humidity_Device_Compensation_Input_Page_Exit, In_Humidity_Device_Compensation_Input_Page_Task, NULL},

    {"保存设置参数", NULL, In_Humidity_Device_Set_Compensation_Enter_Page_Load, In_Humidity_Device_Set_Compensation_Enter_Page_Exit, In_Humidity_Device_Set_Compensation_Enter_Task, NULL},

    {"返回上级菜单", NULL,  Return_Previous_Menu_Page_Load, NULL, NULL, NULL},

    {"返回主页面", NULL,  Back_Main_Page_Load,   NULL,   NULL, NULL},
};

static void In_Humidity_Compensation_Page_Load(void){

	type_slect_move_cursor slect_move_cursor;

	slect_move_cursor.dw_cursor_adderss = INTERNAL_HUMIDITY_COMPENSATION_INPUT_SELECT_CURSOR_ADDERSS ;
	slect_move_cursor.max_slect_move = 2 ;
	slect_move_cursor.min_slect_move = 0 ;
	slect_move_cursor.move_slect_step = 1 ;
	slect_move_cursor.now_slect_move = 0 ;
	slect_cursor_move_init(&slect_move_cursor);  			//光标输入位置初始化
	slect_cursor_move(cursor_refresh_mode,cursor_null);  	//关闭输入位置光标
	slect_move_cursor.dw_cursor_adderss = INTERNAL_HUMIDITY_COMPENSATION_SELECT_CURSOR_ADDERSS ;
	slect_move_cursor.max_slect_move = 3 ;
	slect_move_cursor.min_slect_move = 0 ;
	slect_move_cursor.move_slect_step = 1 ;
	slect_move_cursor.now_slect_move = 0 ;
	slect_cursor_move_init(&slect_move_cursor); 		 			//光标位置初始化
	slect_cursor_move(cursor_default_mode,cursor_null);  			//初始化选择设置光标
	read_saveenv_cjson_internal_parameter(&set_in_humi_menu_list_pararm_t.internal_para);
	set_in_humi_menu_list_pararm_t.In_Humi_ShowCompensationDate_t(set_in_humi_menu_list_pararm_t.internal_para.InternalHumidityCompensationDate);  //显示湿度补偿值
	dw_show_switching_pages(PAGE_INTERNAL_HUMIDITY_COMPENSATION_SETTING_NUMBER); //切换页面
	Buttons_Register(KEY_UP_TRG_NUMBER,Humidity_Slcet_Set_Buttons_CB);
	Buttons_Register(KEY_ENTER_TRG_NUMBER,Humidity_Slcet_Set_Buttons_CB);
	Buttons_Register(KEY_DOWN_TRG_NUMBER,Humidity_Slcet_Set_Buttons_CB);
	Menu_Bind(Internal_Humidity_Set_Compensation_Menu_Table, GET_MENU_NUM(Internal_Humidity_Set_Compensation_Menu_Table), Humidity_SetMenu);
}
static void In_Humidity_Compensation_Page_Exit(void){
	//clear_time_cnt(AUTO_EXIT_SETS_PAGE_TO_MAIN_PAGE_TIMER_NUMBER);
}
static void In_Humidity_Compensation_PageTask(void){
	if(check_time_arrive(AUTO_EXIT_SETS_PAGE_TO_MAIN_PAGE_TIMER_NUMBER,set_in_humi_menu_list_pararm_t.auto_exit_sets_page_to_main_time*1000)){
		Back_Main_Page_Load();
		//clear_time_cnt(AUTO_EXIT_SETS_PAGE_TO_MAIN_PAGE_TIMER_NUMBER);
	}
}
/************* 输入参数- 内部湿度传感器湿度校验补偿页面  *******************/
static void In_Humidity_Device_Compensation_Input_Page_Load(void){
	type_slect_move_cursor slect_move_cursor;
	slect_move_cursor.dw_cursor_adderss = INTERNAL_HUMIDITY_COMPENSATION_SELECT_CURSOR_ADDERSS ;
	slect_move_cursor.max_slect_move = 3 ;
	slect_move_cursor.min_slect_move = 0 ;
	slect_move_cursor.move_slect_step = 1 ;
	slect_move_cursor.now_slect_move = 0 ;
	slect_cursor_move_init(&slect_move_cursor);  //光标位置初始化
	slect_cursor_move(cursor_refresh_mode,cursor_null);  //关闭光标
	slect_move_cursor.dw_cursor_adderss = INTERNAL_HUMIDITY_COMPENSATION_INPUT_SELECT_CURSOR_ADDERSS ;
	slect_move_cursor.max_slect_move = 2 ;
	slect_move_cursor.min_slect_move = 0 ;
	slect_move_cursor.move_slect_step = 1 ;
	slect_move_cursor.now_slect_move = 0 ;
	slect_cursor_move_init(&slect_move_cursor);  //光标位置初始化
	slect_cursor_move(cursor_default_mode,cursor_null);  //显示初始化光标位置
	Buttons_Register(KEY_UP_TRG_NUMBER,Hmi_INTERNAL_Humidity_Compensation_Slcet_Input_Buttons_CB);
	Buttons_Register(KEY_ENTER_TRG_NUMBER,Hmi_INTERNAL_Humidity_Compensation_Slcet_Input_Buttons_CB);
	Buttons_Register(KEY_DOWN_TRG_NUMBER,Hmi_INTERNAL_Humidity_Compensation_Slcet_Input_Buttons_CB);
}

static void In_Humidity_Device_Compensation_Input_Page_Exit(void){
	//clear_time_cnt(AUTO_EXIT_SETS_PAGE_TO_MAIN_PAGE_TIMER_NUMBER);
}

static void In_Humidity_Device_Compensation_Input_Page_Task(void){
	if(check_time_arrive(AUTO_EXIT_SETS_PAGE_TO_MAIN_PAGE_TIMER_NUMBER,set_in_humi_menu_list_pararm_t.auto_exit_sets_page_to_main_time*1000)){
		Back_Main_Page_Load();
		//clear_time_cnt(AUTO_EXIT_SETS_PAGE_TO_MAIN_PAGE_TIMER_NUMBER);
	}
}


static void Hmi_INTERNAL_Humidity_Compensation_Slcet_Input_Buttons_CB(key_Input_Number_Typedef key_number ,Key_Trg_Even key_state){
	if(key_state == KEY_CLICK_ACTION){
		//clear_time_cnt(AUTO_EXIT_SETS_PAGE_TO_MAIN_PAGE_TIMER_NUMBER);
		set_in_humi_menu_list_pararm_t.internal_para.InternalHumidityCompensationDate=user_parameter_adjustment(set_in_humi_menu_list_pararm_t.internal_para.InternalHumidityCompensationDate,1,2,key_number,set_in_humi_menu_list_pararm_t.In_Humi_ShowCompensationDate_t);
	}
}

/********* 保存设置参数- 内部湿度传感器湿度校验补偿  ******************/
static void In_Humidity_Device_Set_Compensation_Enter_Page_Load(void){
	int ret = -1 ;
	type_slect_move_cursor slect_move_cursor;
	slect_move_cursor.dw_cursor_adderss = INTERNAL_HUMIDITY_COMPENSATION_SELECT_CURSOR_ADDERSS ;
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
	dw_input_parameter_hint_window( 1 ,INTERNAL_HUMIDITY_COMPENSATION_WAIT_WINDOW_VAR_ADDERSS,INTERNAL_HUMIDITY_COMPENSATION_SUCCESS_WINDOW_VAR_ADDERSS,INTERNAL_HUMIDITY_COMPENSATION_ERROR_WINDOW_VAR_ADDERSS);
	ret = internalparaPoint_amend_config("InternalHumidityCompensationDate",set_in_humi_menu_list_pararm_t.internal_para.InternalHumidityCompensationDate);
	if( !ret){
		 //显示成功窗口
		dw_input_parameter_hint_window(2,INTERNAL_HUMIDITY_COMPENSATION_WAIT_WINDOW_VAR_ADDERSS,INTERNAL_HUMIDITY_COMPENSATION_SUCCESS_WINDOW_VAR_ADDERSS,INTERNAL_HUMIDITY_COMPENSATION_ERROR_WINDOW_VAR_ADDERSS);
	}else{
		//显示错误窗口
		dw_input_parameter_hint_window( 3 ,INTERNAL_HUMIDITY_COMPENSATION_WAIT_WINDOW_VAR_ADDERSS,INTERNAL_HUMIDITY_COMPENSATION_SUCCESS_WINDOW_VAR_ADDERSS,INTERNAL_HUMIDITY_COMPENSATION_ERROR_WINDOW_VAR_ADDERSS);
	}
	Buttons_Register(KEY_ENTER_TRG_NUMBER,Humidity_Slcet_Enter_Window_Buttons_CB);
}

static void In_Humidity_Device_Set_Compensation_Enter_Page_Exit(void){
	//清除窗口
	dw_input_parameter_hint_window( 0 ,INTERNAL_HUMIDITY_COMPENSATION_WAIT_WINDOW_VAR_ADDERSS,INTERNAL_HUMIDITY_COMPENSATION_SUCCESS_WINDOW_VAR_ADDERSS,INTERNAL_HUMIDITY_COMPENSATION_ERROR_WINDOW_VAR_ADDERSS);
	//clear_time_cnt(AUTO_EXIT_SETS_PAGE_TO_MAIN_PAGE_TIMER_NUMBER);
}

static void In_Humidity_Device_Set_Compensation_Enter_Task(void){
	if(check_time_arrive(AUTO_EXIT_SETS_PAGE_TO_MAIN_PAGE_TIMER_NUMBER,set_in_humi_menu_list_pararm_t.auto_exit_sets_page_to_main_time*1000)){
		Back_Main_Page_Load();
		//clear_time_cnt(AUTO_EXIT_SETS_PAGE_TO_MAIN_PAGE_TIMER_NUMBER);
	}
}

/********************************************** 切换页面 - 内部湿度传感器高湿报警阈值页面  ***************************************************************/
/* 内部湿度传感器湿度校验补偿菜单 */
static MenuList_t Internal_Humidity_Alarm_Threshold_Menu_Table[] =
{
	{"参数输入框", NULL, In_Humidity_Alarm_Threshold_Input_Page_Load, In_Humidity_Alarm_Threshold_Input_Page_Exit, In_Humidity_Alarm_Threshold_Input_Page_Task, NULL},

    {"保存设置参数", NULL, In_Humidity_Alarm_Threshold_Enter_Page_Load, In_Humidity_Alarm_Threshold_Enter_Page_Exit, In_Humidity_Alarm_Threshold_Enter_Page_Task, NULL},

    {"返回上级菜单", NULL,  Return_Previous_Menu_Page_Load, NULL, NULL, NULL},

    {"返回主页面", NULL,  Back_Main_Page_Load,   NULL,   NULL, NULL},
};



static void In_Humidity_Alarm_Threshold_Page_Load(void){
	type_slect_move_cursor slect_move_cursor;

	slect_move_cursor.dw_cursor_adderss = INTERNAL_HUMIDITY_ALARM_THERSHOLD_INPUT_SELECT_CURSOR_ADDERSS ;
	slect_move_cursor.max_slect_move = 1 ;
	slect_move_cursor.min_slect_move = 0 ;
	slect_move_cursor.move_slect_step = 1 ;
	slect_move_cursor.now_slect_move = 0 ;
	slect_cursor_move_init(&slect_move_cursor);  		//光标位置初始化
	slect_cursor_move(cursor_refresh_mode,cursor_null);  //关闭输入指示光标
	slect_move_cursor.dw_cursor_adderss = INTERNAL_HUMIDITY_ALARM_THERSHOLD_SELECT_CURSOR_ADDERSS ;
	slect_move_cursor.max_slect_move = 3 ;
	slect_move_cursor.min_slect_move = 0 ;
	slect_move_cursor.move_slect_step = 1 ;
	slect_move_cursor.now_slect_move = 0 ;
	slect_cursor_move_init(&slect_move_cursor); 		 			//光标位置初始化
	slect_cursor_move(cursor_default_mode,cursor_null);  			//初始化选择设置光标
	read_saveenv_cjson_internal_parameter(&set_in_humi_menu_list_pararm_t.internal_para);
	set_in_humi_menu_list_pararm_t.In_Humi_ShowAlarmThresholdDate(set_in_humi_menu_list_pararm_t.internal_para.InternalAlarmHumidity);  //显示高湿阈值
	dw_show_switching_pages(PAGE_INTERNAL_HUMIDITY_ALARM_THRESHOLD_SETTING_NUMBER); //切换页面
	Buttons_Register(KEY_UP_TRG_NUMBER,Humidity_Slcet_Set_Buttons_CB);
	Buttons_Register(KEY_ENTER_TRG_NUMBER,Humidity_Slcet_Set_Buttons_CB);
	Buttons_Register(KEY_DOWN_TRG_NUMBER,Humidity_Slcet_Set_Buttons_CB);
	Menu_Bind(Internal_Humidity_Alarm_Threshold_Menu_Table, GET_MENU_NUM(Internal_Humidity_Alarm_Threshold_Menu_Table), Humidity_SetMenu);
}
static void In_Humidity_Alarm_Threshold_Page_Exit(void){
	//clear_time_cnt(AUTO_EXIT_SETS_PAGE_TO_MAIN_PAGE_TIMER_NUMBER);
}
static void In_Humidity_Alarm_Threshold_Page_Task(void){
	if(check_time_arrive(AUTO_EXIT_SETS_PAGE_TO_MAIN_PAGE_TIMER_NUMBER,set_in_humi_menu_list_pararm_t.auto_exit_sets_page_to_main_time*1000)){
		Back_Main_Page_Load();
		//clear_time_cnt(AUTO_EXIT_SETS_PAGE_TO_MAIN_PAGE_TIMER_NUMBER);
	}
}
/************* 输入参数- 内部湿度传感器高湿阈值页面  *******************/
static void In_Humidity_Alarm_Threshold_Input_Page_Load(void){
	type_slect_move_cursor slect_move_cursor;

	slect_move_cursor.dw_cursor_adderss = INTERNAL_HUMIDITY_ALARM_THERSHOLD_SELECT_CURSOR_ADDERSS ;
	slect_move_cursor.max_slect_move = 3 ;
	slect_move_cursor.min_slect_move = 0 ;
	slect_move_cursor.move_slect_step = 1 ;
	slect_move_cursor.now_slect_move = 0 ;
	slect_cursor_move_init(&slect_move_cursor);  //光标位置初始化
	slect_cursor_move(cursor_refresh_mode,cursor_null);  //关闭选择设置光标
	slect_move_cursor.dw_cursor_adderss = INTERNAL_HUMIDITY_ALARM_THERSHOLD_INPUT_SELECT_CURSOR_ADDERSS ;
	slect_move_cursor.max_slect_move = 1 ;
	slect_move_cursor.min_slect_move = 0 ;
	slect_move_cursor.move_slect_step = 1 ;
	slect_move_cursor.now_slect_move = 0 ;
	slect_cursor_move_init(&slect_move_cursor);  //光标位置初始化
	slect_cursor_move(cursor_default_mode,cursor_null);  //显示初始化输入指示光标位置
	Buttons_Register(KEY_UP_TRG_NUMBER,Hmi_Internal_Humidity_Alarm_Threshold_Input_Buttons_CB);
	Buttons_Register(KEY_ENTER_TRG_NUMBER,Hmi_Internal_Humidity_Alarm_Threshold_Input_Buttons_CB);
	Buttons_Register(KEY_DOWN_TRG_NUMBER,Hmi_Internal_Humidity_Alarm_Threshold_Input_Buttons_CB);
}

static void In_Humidity_Alarm_Threshold_Input_Page_Exit(void){
	//clear_time_cnt(AUTO_EXIT_SETS_PAGE_TO_MAIN_PAGE_TIMER_NUMBER);
}

static void In_Humidity_Alarm_Threshold_Input_Page_Task(void){
	if(check_time_arrive(AUTO_EXIT_SETS_PAGE_TO_MAIN_PAGE_TIMER_NUMBER,set_in_humi_menu_list_pararm_t.auto_exit_sets_page_to_main_time*1000)){
		Back_Main_Page_Load();
		//clear_time_cnt(AUTO_EXIT_SETS_PAGE_TO_MAIN_PAGE_TIMER_NUMBER);
	}
}


static void Hmi_Internal_Humidity_Alarm_Threshold_Input_Buttons_CB(key_Input_Number_Typedef key_number ,Key_Trg_Even key_state){
	if(key_state == KEY_CLICK_ACTION){
		//clear_time_cnt(AUTO_EXIT_SETS_PAGE_TO_MAIN_PAGE_TIMER_NUMBER);
		set_in_humi_menu_list_pararm_t.internal_para.InternalAlarmHumidity=user_parameter_adjustment(set_in_humi_menu_list_pararm_t.internal_para.InternalAlarmHumidity,0,2,key_number,set_in_humi_menu_list_pararm_t.In_Humi_ShowAlarmThresholdDate);
	}
}

/********* 保存设置参数- 内部湿度传感器高湿阈值  ******************/
static void In_Humidity_Alarm_Threshold_Enter_Page_Load(void){
	int ret = -1 ;
	type_slect_move_cursor slect_move_cursor;
	slect_move_cursor.dw_cursor_adderss = INTERNAL_HUMIDITY_ALARM_THERSHOLD_SELECT_CURSOR_ADDERSS ;
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
	dw_input_parameter_hint_window( 1 ,INTERNAL_HUMIDITY_ALARM_THERSHOLD_WAIT_WINDOW_VAR_ADDERSS,INTERNAL_HUMIDITY_ALARM_THERSHOLD_SUCCESS_WINDOW_VAR_ADDERSS,INTERNAL_HUMIDITY_ALARM_THERSHOLD_ERROR_WINDOW_VAR_ADDERSS);
	ret = internalparaPoint_amend_config("InternalAlarmHumidity",set_in_humi_menu_list_pararm_t.internal_para.InternalAlarmHumidity);
	if( !ret){
		 //显示成功窗口
		dw_input_parameter_hint_window(2,INTERNAL_HUMIDITY_ALARM_THERSHOLD_WAIT_WINDOW_VAR_ADDERSS,INTERNAL_HUMIDITY_ALARM_THERSHOLD_SUCCESS_WINDOW_VAR_ADDERSS,INTERNAL_HUMIDITY_ALARM_THERSHOLD_ERROR_WINDOW_VAR_ADDERSS);
	}else{
		//显示错误窗口
		dw_input_parameter_hint_window( 3 ,INTERNAL_HUMIDITY_ALARM_THERSHOLD_WAIT_WINDOW_VAR_ADDERSS,INTERNAL_HUMIDITY_ALARM_THERSHOLD_SUCCESS_WINDOW_VAR_ADDERSS,INTERNAL_HUMIDITY_ALARM_THERSHOLD_ERROR_WINDOW_VAR_ADDERSS);
	}
	Buttons_Register(KEY_ENTER_TRG_NUMBER,Humidity_Slcet_Enter_Window_Buttons_CB);
}

static void In_Humidity_Alarm_Threshold_Enter_Page_Exit(void){
	//清除窗口
	dw_input_parameter_hint_window( 0 ,INTERNAL_HUMIDITY_ALARM_THERSHOLD_WAIT_WINDOW_VAR_ADDERSS,INTERNAL_HUMIDITY_ALARM_THERSHOLD_SUCCESS_WINDOW_VAR_ADDERSS,INTERNAL_HUMIDITY_ALARM_THERSHOLD_ERROR_WINDOW_VAR_ADDERSS);
	//clear_time_cnt(AUTO_EXIT_SETS_PAGE_TO_MAIN_PAGE_TIMER_NUMBER);
}

static void In_Humidity_Alarm_Threshold_Enter_Page_Task(void){
	if(check_time_arrive(AUTO_EXIT_SETS_PAGE_TO_MAIN_PAGE_TIMER_NUMBER,set_in_humi_menu_list_pararm_t.auto_exit_sets_page_to_main_time*1000)){
		Back_Main_Page_Load();
		//clear_time_cnt(AUTO_EXIT_SETS_PAGE_TO_MAIN_PAGE_TIMER_NUMBER);
	}
}
/********************************************** 切换页面 - 内部湿度传感器湿度采集速率页面  ***************************************************************/
/* 内部湿度传感器湿度采集速率菜单 */
static MenuList_t Internal_Humidity_Sample_Rate_Menu_Table[] =
{
	{"参数输入框", NULL, In_Humidity_Sample_Rate_Input_Page_Load, In_Humidity_Sample_Rate_Input_Page_Exit, In_Humidity_Sample_Rate_Input_Page_Task, NULL},

    {"保存设置参数", NULL, In_Humidity_Sample_Rate_Enter_Page_Load, In_Humidity_Sample_Rate_Enter_Page_Exit, In_Humidity_Sample_Rate_Enter_Page_Task, NULL},

    {"返回上级菜单", NULL,  Return_Previous_Menu_Page_Load, NULL, NULL, NULL},

    {"返回主页面", NULL,  Back_Main_Page_Load,   NULL,   NULL, NULL},
};

static void In_Humidity_Acquisition_Rate_Page_Load(void){
	type_slect_move_cursor slect_move_cursor;

	slect_move_cursor.dw_cursor_adderss = INTERNAL_HUMIDITY_SAMPLE_RATE_INPUT_SELECT_CURSOR_ADDERSS ;
	slect_move_cursor.max_slect_move = 1 ;
	slect_move_cursor.min_slect_move = 0 ;
	slect_move_cursor.move_slect_step = 1 ;
	slect_move_cursor.now_slect_move = 0 ;
	slect_cursor_move_init(&slect_move_cursor);  		//输入指示光标位置初始化
	slect_cursor_move(cursor_refresh_mode,cursor_null);  //关闭输入指示光标
	slect_move_cursor.dw_cursor_adderss = INTERNAL_HUMIDITY_SAMPLE_RATE_SELECT_CURSOR_ADDERSS ;
	slect_move_cursor.max_slect_move = 3 ;
	slect_move_cursor.min_slect_move = 0 ;
	slect_move_cursor.move_slect_step = 1 ;
	slect_move_cursor.now_slect_move = 0 ;
	slect_cursor_move_init(&slect_move_cursor); 		 			//光标位置初始化
	slect_cursor_move(cursor_default_mode,cursor_null);  			//初始化选择设置光标
	read_saveenv_cjson_internal_parameter(&set_in_humi_menu_list_pararm_t.internal_para);
	set_in_humi_menu_list_pararm_t.In_Humi_ShowSampleRateDate(set_in_humi_menu_list_pararm_t.internal_para.InternalHumitureSampleRate); //显示采样速率
	dw_show_switching_pages(PAGE_INTERNAL_HUMIDITY_SAMPLE_RATE_SETTING_NUMBER); //切换页面
	Buttons_Register(KEY_UP_TRG_NUMBER,Humidity_Slcet_Set_Buttons_CB);
	Buttons_Register(KEY_ENTER_TRG_NUMBER,Humidity_Slcet_Set_Buttons_CB);
	Buttons_Register(KEY_DOWN_TRG_NUMBER,Humidity_Slcet_Set_Buttons_CB);
	Menu_Bind(Internal_Humidity_Sample_Rate_Menu_Table, GET_MENU_NUM(Internal_Humidity_Sample_Rate_Menu_Table), Humidity_SetMenu);
}

static void In_Humidity_Acquisition_Rate_Page_Exit(void){
	//clear_time_cnt(AUTO_EXIT_SETS_PAGE_TO_MAIN_PAGE_TIMER_NUMBER);
}
static void In_Humidity_Acquisition_Rate_Page_Task(void){
	if(check_time_arrive(AUTO_EXIT_SETS_PAGE_TO_MAIN_PAGE_TIMER_NUMBER,set_in_humi_menu_list_pararm_t.auto_exit_sets_page_to_main_time*1000)){
		Back_Main_Page_Load();
		//clear_time_cnt(AUTO_EXIT_SETS_PAGE_TO_MAIN_PAGE_TIMER_NUMBER);
	}
}

/************* 输入参数- 内部湿度传感器湿湿度采样速率页面  *******************/
static void In_Humidity_Sample_Rate_Input_Page_Load(void){
	type_slect_move_cursor slect_move_cursor;

	slect_move_cursor.dw_cursor_adderss = INTERNAL_HUMIDITY_SAMPLE_RATE_SELECT_CURSOR_ADDERSS ;
	slect_move_cursor.max_slect_move = 3 ;
	slect_move_cursor.min_slect_move = 0 ;
	slect_move_cursor.move_slect_step = 1 ;
	slect_move_cursor.now_slect_move = 0 ;
	slect_cursor_move_init(&slect_move_cursor);  //光标位置初始化
	slect_cursor_move(cursor_refresh_mode,cursor_null);  //关闭选择设置光标
	slect_move_cursor.dw_cursor_adderss = INTERNAL_HUMIDITY_SAMPLE_RATE_INPUT_SELECT_CURSOR_ADDERSS ;
	slect_move_cursor.max_slect_move = 1 ;
	slect_move_cursor.min_slect_move = 0 ;
	slect_move_cursor.move_slect_step = 1 ;
	slect_move_cursor.now_slect_move = 0 ;
	slect_cursor_move_init(&slect_move_cursor);  //光标位置初始化
	slect_cursor_move(cursor_default_mode,cursor_null);  //显示初始化输入指示光标位置
	Buttons_Register(KEY_UP_TRG_NUMBER,Hmi_INTERNAL_Humidity_Sample_Rate_Input_Buttons_CB);
	Buttons_Register(KEY_ENTER_TRG_NUMBER,Hmi_INTERNAL_Humidity_Sample_Rate_Input_Buttons_CB);
	Buttons_Register(KEY_DOWN_TRG_NUMBER,Hmi_INTERNAL_Humidity_Sample_Rate_Input_Buttons_CB);
}

static void In_Humidity_Sample_Rate_Input_Page_Exit(void){
	//clear_time_cnt(AUTO_EXIT_SETS_PAGE_TO_MAIN_PAGE_TIMER_NUMBER);
}

static void In_Humidity_Sample_Rate_Input_Page_Task(void){
	if(check_time_arrive(AUTO_EXIT_SETS_PAGE_TO_MAIN_PAGE_TIMER_NUMBER,set_in_humi_menu_list_pararm_t.auto_exit_sets_page_to_main_time*1000)){
		Back_Main_Page_Load();
		//clear_time_cnt(AUTO_EXIT_SETS_PAGE_TO_MAIN_PAGE_TIMER_NUMBER);
	}
}

static void Hmi_INTERNAL_Humidity_Sample_Rate_Input_Buttons_CB(key_Input_Number_Typedef key_number ,Key_Trg_Even key_state){
	if(key_state == KEY_CLICK_ACTION){
		//clear_time_cnt(AUTO_EXIT_SETS_PAGE_TO_MAIN_PAGE_TIMER_NUMBER);
		set_in_humi_menu_list_pararm_t.internal_para.InternalHumitureSampleRate=user_parameter_adjustment(set_in_humi_menu_list_pararm_t.internal_para.InternalHumitureSampleRate,0,2,key_number,set_in_humi_menu_list_pararm_t.In_Humi_ShowSampleRateDate);
	}
}

/********* 保存设置参数- 内部湿度传感器湿度采样速率  ******************/
static void In_Humidity_Sample_Rate_Enter_Page_Load(void){
	int ret = -1 ;
	type_slect_move_cursor slect_move_cursor;
	slect_move_cursor.dw_cursor_adderss = INTERNAL_HUMIDITY_SAMPLE_RATE_SELECT_CURSOR_ADDERSS ;
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
	dw_input_parameter_hint_window( 1 ,INTERNAL_HUMIDITY_SAMPLE_RATE_WAIT_WINDOW_VAR_ADDERSS,INTERNAL_HUMIDITY_SAMPLE_RATE_SUCCESS_WINDOW_VAR_ADDERSS,INTERNAL_HUMIDITY_SAMPLE_RATE_ERROR_WINDOW_VAR_ADDERSS);
	ret = internalparaPoint_amend_config("InternalHumitureSampleRate",set_in_humi_menu_list_pararm_t.internal_para.InternalHumitureSampleRate);
	if( !ret){
		 //显示成功窗口
		dw_input_parameter_hint_window(2,INTERNAL_HUMIDITY_SAMPLE_RATE_WAIT_WINDOW_VAR_ADDERSS,INTERNAL_HUMIDITY_SAMPLE_RATE_SUCCESS_WINDOW_VAR_ADDERSS,INTERNAL_HUMIDITY_SAMPLE_RATE_ERROR_WINDOW_VAR_ADDERSS);
	}else{
		//显示错误窗口
		dw_input_parameter_hint_window( 3 ,INTERNAL_HUMIDITY_SAMPLE_RATE_WAIT_WINDOW_VAR_ADDERSS,INTERNAL_HUMIDITY_SAMPLE_RATE_SUCCESS_WINDOW_VAR_ADDERSS,INTERNAL_HUMIDITY_SAMPLE_RATE_ERROR_WINDOW_VAR_ADDERSS);
	}
	Buttons_Register(KEY_ENTER_TRG_NUMBER,Humidity_Slcet_Enter_Window_Buttons_CB);
}

static void In_Humidity_Sample_Rate_Enter_Page_Exit(void){
	//清除窗口
		dw_input_parameter_hint_window( 0 ,INTERNAL_HUMIDITY_SAMPLE_RATE_WAIT_WINDOW_VAR_ADDERSS,INTERNAL_HUMIDITY_SAMPLE_RATE_SUCCESS_WINDOW_VAR_ADDERSS,INTERNAL_HUMIDITY_SAMPLE_RATE_ERROR_WINDOW_VAR_ADDERSS);
		//clear_time_cnt(AUTO_EXIT_SETS_PAGE_TO_MAIN_PAGE_TIMER_NUMBER);
}

static void In_Humidity_Sample_Rate_Enter_Page_Task(void){
	if(check_time_arrive(AUTO_EXIT_SETS_PAGE_TO_MAIN_PAGE_TIMER_NUMBER,set_in_humi_menu_list_pararm_t.auto_exit_sets_page_to_main_time*1000)){
		Back_Main_Page_Load();
		//clear_time_cnt(AUTO_EXIT_SETS_PAGE_TO_MAIN_PAGE_TIMER_NUMBER);
	}
}

/************* 内部湿度传感器公共回调函数  *******************/
static void Humidity_Slcet_Set_Buttons_CB( key_Input_Number_Typedef key_number , Key_Trg_Even key_state){
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

static void Humidity_Slcet_Enter_Window_Buttons_CB( key_Input_Number_Typedef key_number , Key_Trg_Even key_state){
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

