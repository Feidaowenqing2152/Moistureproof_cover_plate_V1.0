/*
 * hmi_sleet.c
 *
 *  Created on: 2023年2月13日
 *      Author: 好
 */
#define LOG_TAG    "external/hmi_sleet"

#include "../himi/external/hmi_sleet.h"

struct set_ex_sleet_menu_list_pararm{
	int auto_exit_sets_page_to_main_time ;  //自动返回时间
	uint16_t exit_wait_timout_cnt ;

	external_para_def external_para ;
	ShownMenuDate Ex_Sleet_ShowRealTimeSensitivityDate_t ;  	//当前灵敏度显示
	ShownMenuDate Ex_Sleet_ShowIntputSensitivityDate_t ;    	//设置灵敏度显示
	ShownMenuDate Ex_Sleet_ShowRealTimeHeatLowLimitDate_t ;  	//当前加热下限温度显示
	ShownMenuDate Ex_Sleet_ShowIntputHeatLowLimitDate_t ;    	//设置加热下限温度显示
	ShownMenuDate Ex_Sleet_ShowRealTimeHeatHightLimitDate_t ;  	//当前加热上限温度显示
	ShownMenuDate Ex_Sleet_ShowIntputHeatHightLimitDate_t ;    	//设置加热上限温度显示
	ShownMenuDate Ex_Sleet_ShowRealTimeDelayAlarmResetDate_t ;  //当前报警复归延时显示
	ShownMenuDate Ex_Sleet_ShowIntputDelayAlarmResetDate_t ;    //设置报警复归延时显示
	ShownMenuDate Ex_Sleet_ShowSampleRateDate ;					//设置采样速率显示
};


static struct set_ex_sleet_menu_list_pararm set_ex_sleet_menu_list_pararm_t ;

/******************外界参数-雨雪传感器设置页面选择*********************************/
static void MenuDateShow_Init(void);

/* 设置地址复位初始化*/
static void Device_Addr_Reversion_Init(void);
/* 设置地址复位执行函数*/
static void Ex_Sleet_Setting_Dev_Transducer_Reset_Addr(void);
/* 设置菜单显示效果 */
static void Sleet_SetMenu(  MenuShow_t *ptShowInfo);

/********************************************** 切换页面 - 外界雨雪传感灵敏度设置页面  ***************************************************************/
static void Ex_Sleet_Sensitivity_Page_Load(void);
static void Ex_Sleet_Sensitivity_Page_Exit(void);
static void Ex_Sleet_Sensitivity_Page_Task(void);
/************* 输入参数- 外界雨雪传感灵敏度设置页面  *******************/
static void Ex_Sleet_Sensitivity_Input_Page_Load(void);
static void EX_Sleet_Sensitivity_Input_Page_Exit(void);
static void Ex_Sleet_Sensitivity_Input_Page_Task(void);
static void Hmi_External_Sleet_Sensitivity_Slcet_Input_Buttons_CB(key_Input_Number_Typedef key_number ,Key_Trg_Even key_state);
/********* 保存设置参数- 外界雨雪传感灵敏度设置页面  ******************/
static void Ex_Sleet_Sensitivity_Enter_Page_Load(void);
static void EX_Sleet_Sensitivity_Enter_Page_Exit(void);
static void EX_Sleet_Sensitivity_Enter_Page_Task(void);
/********************************************** 切换页面 - 外界雨雪传感器加热设置页面  ***************************************************************/
static void Ex_SLeet_Heat_Setting_Page_Load(void);
static void Ex_SLeet_Heat_Setting_Page_Exit(void);
static void Ex_SLeet_Heat_Setting_Page_Task(void);
/********************************************** 切换页面 - 外界雨雪传感器加热-加热下限选择设置页面  ***************************************************************/
static void Ex_Sleet_Heat_Lower_Limit_Setting_Page_Load(void);
static void Ex_Sleet_Heat_Lower_Limit_Setting_Page_Exit(void);
static void Ex_Sleet_Heat_Lower_Limit_Setting_Page_Task(void);
/************* 输入参数- 外界雨雪传感器加热-加热下限页面  *******************/
static void Ex_Sleet_Heat_Lower_Limit_Input_Page_Load(void);
static void Ex_Sleet_Heat_Lower_Limit_Input_Page_Exit(void);
static void Ex_Sleet_Heat_Lower_Limit_Input_Page_Task(void);
static void Sleet_Heat_Lower_Limit_Input_Buttons_CB(key_Input_Number_Typedef key_number ,Key_Trg_Even key_state);
/********* 保存设置参数- 外界雨雪传感器加热-加热下限页面 ******************/
static void Ex_Sleet_Heat_Lower_Limit_Input_Enter_Page_Load(void);
static void Ex_Sleet_Heat_Lower_Limit_Input_Enter_Page_Exit(void);
static void Ex_Sleet_Heat_Lower_Limit_Input_Enter_Page_Task(void);
/********************************************** 切换页面 - 外界雨雪传感器加热-加热上限设置页面  ***************************************************************/
static void Ex_Sleet_Heat_Hight_Limit_Setting_Page_Load(void);
static void Ex_Sleet_Heat_Hight_Limit_Setting_Page_Exit(void);
static void Ex_Sleet_Heat_Hight_Limit_Setting_Page_Task(void);
/************* 输入参数-  外界雨雪传感器加热-加热上限设置页面  *******************/
static void Ex_Sleet_Heat_Hight_Limit_Input_Page_Load(void);
static void Ex_Sleet_Heat_Hight_Limit_Input_Page_Exit(void);
static void Ex_Sleet_Heat_Hight_Limit_Input_Page_Task(void);
static void Ex_Sleet_Heat_Hight_Limit_Input_CB(key_Input_Number_Typedef key_number ,Key_Trg_Even key_state);
/********* 保存设置参数- 外界雨雪传感器加热-加热上限页面 ******************/
static void Ex_Sleet_Heat_Hight_Limit_Input_Enter_Page_Load(void);
static void Ex_Sleet_Heat_Hight_Limit_Input_Enter_Page_Exit(void);
static void Ex_Sleet_Heat_Hight_Limit_Input_Enter_Page_Task(void);
/********************************************** 切换页面 -外界雨雪传感器报警复归选择设置页面  ***************************************************************/
static void Ex_Sleet_Delay_Alarm_Setting_Page_Load(void);
static void Ex_Sleet_Delay_Alarm_Setting_Page_Exit(void);
static void Ex_Sleet_Delay_Alarm_Setting_Page_Task(void);
/************* 输入参数- 外界雨雪传感器报警复归设置页面  *******************/
static void Ex_Sleet_Delay_Alarm_Input_Page_Load(void);
static void Ex_Sleet_Delay_Alarm_Input_Page_Exit(void);
static void Ex_Sleet_Delay_Alarm_Input_Page_Task(void);
static void Hmi_External_Sleet_Delay_Alarm_Input_Buttons_CB(key_Input_Number_Typedef key_number ,Key_Trg_Even key_state);
/********* 保存设置参数- 外界雨雪传感器报警复归设置页面 ******************/
static void Ex_Sleet_Delay_Alarm_Input_Enter_Page_Load(void);
static void Ex_Sleet_Delay_Alarm_Input_Enter_Page_Exit(void);
static void Ex_Sleet_Delay_Alarm_Input_Enter_Page_Task(void);
/********************************************** 切换页面 -外界雨雪传感器采集速率页面  ***************************************************************/
static void Ex_Sleet_Acquisition_Rate_Page_Load(void);
static void Ex_Sleet_Acquisition_Rate_Page_Exit(void);
static void Ex_Sleet_Acquisition_Rate_Page_Task(void);
/************* 输入参数- 外界雨雪传感器采样速率页面  *******************/
static void Ex_Sleet_Sample_Rate_Input_Page_Load(void);
static void Ex_Sleet_Sample_Rate_Input_Page_Exit(void);
static void Ex_Sleet_Sample_Rate_Input_Page_Task(void);
static void Hmi_External_Sleet_Sample_Rate_Input_Buttons_CB(key_Input_Number_Typedef key_number ,Key_Trg_Even key_state);
/********* 保存设置参数- 外界雨雪传感器采样速率  ******************/
static void Ex_Sleet_Sample_Rate_Enter_Page_Load(void);
static void Ex_Sleet_Sample_Rate_Enter_Page_Exit(void);
static void Ex_Sleet_Sample_Rate_Enter_Page_Task(void);
/************* 外界雨雪传感器公共回调函数  *******************/
static void Sleet_Slcet_Set_Buttons_CB( key_Input_Number_Typedef key_number , Key_Trg_Even key_state);
static void Sleet_Slcet_Enter_Window_Buttons_CB( key_Input_Number_Typedef key_number , Key_Trg_Even key_state);







/******************外界参数-雨雪传感器设置页面选择*********************************/
/* 外界雨雪传感器设置菜单*/
static MenuList_t External_Sleet_Set_Menu_Table[] =
{
    {"设备地址复归", NULL, Device_Addr_Reversion_Page_Load, Device_Addr_Reversion_Page_Exit, Device_Addr_Reversion_Page_Task, NULL},

    {"灵敏度设置", NULL, Ex_Sleet_Sensitivity_Page_Load, Ex_Sleet_Sensitivity_Page_Exit, Ex_Sleet_Sensitivity_Page_Task, NULL},

    {"加热温度设置", NULL, Ex_SLeet_Heat_Setting_Page_Load, Ex_SLeet_Heat_Setting_Page_Exit, Ex_SLeet_Heat_Setting_Page_Task, NULL},

    {"报警复归延时设置", NULL,  Ex_Sleet_Delay_Alarm_Setting_Page_Load, Ex_Sleet_Delay_Alarm_Setting_Page_Exit, Ex_Sleet_Delay_Alarm_Setting_Page_Task, NULL},

    {"采集速率设置", NULL,  Ex_Sleet_Acquisition_Rate_Page_Load, Ex_Sleet_Acquisition_Rate_Page_Exit, Ex_Sleet_Acquisition_Rate_Page_Task, NULL},

    {"返回上级菜单", NULL,  Return_Previous_Menu_Page_Load, NULL, NULL, NULL},

    {"返回主页面", NULL,  Back_Main_Page_Load,   NULL,   NULL, NULL},
};


static void MenuDateShow_Init(void){
	system_para_def system_para_t ;
	set_ex_sleet_menu_list_pararm_t.Ex_Sleet_ShowRealTimeSensitivityDate_t = show_sleet_real_time_sensitivity_date ;            //显示灵敏度值
	set_ex_sleet_menu_list_pararm_t.Ex_Sleet_ShowIntputSensitivityDate_t = show_sleet_intput_sensitivity_date ;                 //显示设置灵敏度值
	set_ex_sleet_menu_list_pararm_t.Ex_Sleet_ShowRealTimeHeatLowLimitDate_t = show_sleet_real_time_heat_lower_limit_date ;    	 //显示当前加热下限值
	set_ex_sleet_menu_list_pararm_t.Ex_Sleet_ShowIntputHeatLowLimitDate_t = show_sleet_intput_heat_lower_limit_date ;   		 //显示设置加热下限值
	set_ex_sleet_menu_list_pararm_t.Ex_Sleet_ShowRealTimeHeatHightLimitDate_t = show_sleet_real_time_heat_hight_limit_date ;	 //显示当前加热上限值
	set_ex_sleet_menu_list_pararm_t.Ex_Sleet_ShowIntputHeatHightLimitDate_t = show_sleet_intput_heat_hight_limit_date ;          //显示设置加热上限值
	set_ex_sleet_menu_list_pararm_t.Ex_Sleet_ShowRealTimeDelayAlarmResetDate_t = show_sleet_real_time_delay_alarm_reset_date ;   //显示当前报警复归延时值
	set_ex_sleet_menu_list_pararm_t.Ex_Sleet_ShowIntputDelayAlarmResetDate_t = show_sleet_intput_delay_alarm_reset_date ;        //显示设置报警复归延时值
	set_ex_sleet_menu_list_pararm_t.Ex_Sleet_ShowSampleRateDate = show_sleet_sample_rate_date ;		 						     //显示雨雪采集速率

	read_saveenv_cjson_system_parameter(&system_para_t);
	set_ex_sleet_menu_list_pararm_t.auto_exit_sets_page_to_main_time = system_para_t.AutoExitSetsPageTime;
}

/* 设置地址复位初始化*/
static void Device_Addr_Reversion_Init(void){
	struct dev_address_reset_par ex_sleet_address_reset_par ;
	ex_sleet_address_reset_par.setting_sleet_type_flag = 1 ;
	ex_sleet_address_reset_par.setting_cursor_dev_var_addr = EXTERNAL_SLEET_DEV_ADDERSS_RESET_CURSOR_ADDERSS ;
	ex_sleet_address_reset_par.setting_dev_reset_page = PAGE_EXTERNAL_SLEET_DEV_ADDR_SETTING_NUMBER ;
	ex_sleet_address_reset_par.auto_exit_setting_page_time = set_ex_sleet_menu_list_pararm_t.auto_exit_sets_page_to_main_time ;
	ex_sleet_address_reset_par.dev_addr_reset_wait_var_addr = EXTERNAL_SLEET_DEV_ADDR_RESET_WAIT_WINDOW_VAR_ADDERSS ;
	ex_sleet_address_reset_par.dev_addr_reset_success_var_addr = EXTERNAL_SLEET_DEV_ADDR_RESET_SUCCESS_WINDOW_VAR_ADDERSS ;
	ex_sleet_address_reset_par.dev_addr_reset_error_var_addr = EXTERNAL_SLEET_DEV_ADDR_RESET_ERROR_WINDOW_VAR_ADDERSS ;
	/* 设置设备地址确定执行函数 */
	ex_sleet_address_reset_par.dev_reset_execute_function_cb = Ex_Sleet_Setting_Dev_Transducer_Reset_Addr;
	Device_Addr_Reversion_Load_Init( &ex_sleet_address_reset_par);
}
/* 设置地址复位执行函数*/
static void Ex_Sleet_Setting_Dev_Transducer_Reset_Addr(void){
	Setting_Dev_Transducer_Reset_Addr( sleet_transducer )  ;
}
/* 设置菜单显示效果 */
static void Sleet_SetMenu(  MenuShow_t *ptShowInfo){
	show_refresh_time();
	show_eth_connect_state();
}

/********************************************** 切换页面 - 外界雨雪传感器选择设置页面  ***************************************************************/
void External_Sleet_Setting_Page_Load(void){

	type_slect_move_cursor slect_move_cursor;

	slect_move_cursor.dw_cursor_adderss = EXTERNAL_SLEET_DEV_SETTING_CURSOR_ADDERSS ;
	slect_move_cursor.max_slect_move = 6 ;
	slect_move_cursor.min_slect_move = 0 ;
	slect_move_cursor.move_slect_step = 1 ;
	slect_move_cursor.now_slect_move = 0 ;
	slect_cursor_move_init(&slect_move_cursor);  					//光标位置初始化
	dw_show_switching_pages(PAGE_EXTERNAL_SLEET_SETTING_NUMBER); 	//切换页面
	slect_cursor_move(cursor_default_mode,cursor_null);  			//初始化选择设置显示光标
	Buttons_Register(KEY_UP_TRG_NUMBER,Sleet_Slcet_Set_Buttons_CB);
	Buttons_Register(KEY_ENTER_TRG_NUMBER,Sleet_Slcet_Set_Buttons_CB);
	Buttons_Register(KEY_DOWN_TRG_NUMBER,Sleet_Slcet_Set_Buttons_CB);
	MenuDateShow_Init();
	Device_Addr_Reversion_Init();
	//clear_time_cnt(AUTO_EXIT_SETS_PAGE_TO_MAIN_PAGE_TIMER_NUMBER);
	read_saveenv_cjson_external_parameter(&set_ex_sleet_menu_list_pararm_t.external_para);
	set_ex_sleet_menu_list_pararm_t.Ex_Sleet_ShowRealTimeSensitivityDate_t(set_ex_sleet_menu_list_pararm_t.external_para.ExternalSleetSensitivityDate); //显示当前灵敏度
	set_ex_sleet_menu_list_pararm_t.Ex_Sleet_ShowRealTimeDelayAlarmResetDate_t(set_ex_sleet_menu_list_pararm_t.external_para.ExternalSleetDelayAlarmRestDate); //显示当前报警复归延时
	Menu_Bind(External_Sleet_Set_Menu_Table, GET_MENU_NUM(External_Sleet_Set_Menu_Table), Sleet_SetMenu);
}

void External_Sleet_Setting_Page_Exit(void){
	//clear_time_cnt(AUTO_EXIT_SETS_PAGE_TO_MAIN_PAGE_TIMER_NUMBER);
}

void External_Sleet_Setting_Page_Task(void){
	if(check_time_arrive(AUTO_EXIT_SETS_PAGE_TO_MAIN_PAGE_TIMER_NUMBER,set_ex_sleet_menu_list_pararm_t.auto_exit_sets_page_to_main_time*1000)){
		Back_Main_Page_Load();
	}
}




/********************************************** 切换页面 - 外界雨雪传感灵敏度设置页面  ***************************************************************/
/* 外界雨雪传感灵敏度菜单 */
static MenuList_t External_Sleet_Set_Sensitivity_Menu_Table[] =
{
	{"参数输入框", NULL, Ex_Sleet_Sensitivity_Input_Page_Load, EX_Sleet_Sensitivity_Input_Page_Exit, Ex_Sleet_Sensitivity_Input_Page_Task, NULL},

    {"保存设置参数", NULL, Ex_Sleet_Sensitivity_Enter_Page_Load, EX_Sleet_Sensitivity_Enter_Page_Exit, EX_Sleet_Sensitivity_Enter_Page_Task, NULL},

    {"返回上级菜单", NULL,  Return_Previous_Menu_Page_Load, NULL, NULL, NULL},

    {"返回主页面", NULL,  Back_Main_Page_Load,   NULL,   NULL, NULL},
};

static void Ex_Sleet_Sensitivity_Page_Load(void){

	type_slect_move_cursor slect_move_cursor;

	slect_move_cursor.dw_cursor_adderss = EXTERNAL_SLEET_SENSITIVITY_INPUT_SELECT_CURSOR_ADDERSS ;
	slect_move_cursor.max_slect_move = 3 ;
	slect_move_cursor.min_slect_move = 0 ;
	slect_move_cursor.move_slect_step = 1 ;
	slect_move_cursor.now_slect_move = 0 ;
	slect_cursor_move_init(&slect_move_cursor);  			//光标输入位置初始化
	slect_cursor_move(cursor_refresh_mode,cursor_null);  	//关闭输入位置光标
	slect_move_cursor.dw_cursor_adderss = EXTERNAL_SLEET_SENSITIVITY_SETTING_CURSOR_ADDERSS ;
	slect_move_cursor.max_slect_move = 3 ;
	slect_move_cursor.min_slect_move = 0 ;
	slect_move_cursor.move_slect_step = 1 ;
	slect_move_cursor.now_slect_move = 0 ;
	slect_cursor_move_init(&slect_move_cursor); 		 			//光标位置初始化
	slect_cursor_move(cursor_default_mode,cursor_null);  			//初始化选择设置光标
	read_saveenv_cjson_external_parameter(&set_ex_sleet_menu_list_pararm_t.external_para);
	set_ex_sleet_menu_list_pararm_t.Ex_Sleet_ShowIntputSensitivityDate_t(set_ex_sleet_menu_list_pararm_t.external_para.ExternalSleetSensitivityDate);   //显示输入灵敏度值
	dw_show_switching_pages(PAGE_EXTERNAL_SLEET_SENSITIVITY_SETTING_NUMBER); //切换页面
	Buttons_Register(KEY_UP_TRG_NUMBER,Sleet_Slcet_Set_Buttons_CB);
	Buttons_Register(KEY_ENTER_TRG_NUMBER,Sleet_Slcet_Set_Buttons_CB);
	Buttons_Register(KEY_DOWN_TRG_NUMBER,Sleet_Slcet_Set_Buttons_CB);
	Menu_Bind(External_Sleet_Set_Sensitivity_Menu_Table, GET_MENU_NUM(External_Sleet_Set_Sensitivity_Menu_Table), Sleet_SetMenu);
}
static void Ex_Sleet_Sensitivity_Page_Exit(void){
	//clear_time_cnt(AUTO_EXIT_SETS_PAGE_TO_MAIN_PAGE_TIMER_NUMBER);
}
static void Ex_Sleet_Sensitivity_Page_Task(void){
	if(check_time_arrive(AUTO_EXIT_SETS_PAGE_TO_MAIN_PAGE_TIMER_NUMBER,set_ex_sleet_menu_list_pararm_t.auto_exit_sets_page_to_main_time*1000)){
		Back_Main_Page_Load();
	}
}
/************* 输入参数- 外界雨雪传感灵敏度设置页面  *******************/
static void Ex_Sleet_Sensitivity_Input_Page_Load(void){
	type_slect_move_cursor slect_move_cursor;
	slect_move_cursor.dw_cursor_adderss = EXTERNAL_SLEET_SENSITIVITY_SETTING_CURSOR_ADDERSS ;
	slect_move_cursor.max_slect_move = 3 ;
	slect_move_cursor.min_slect_move = 0 ;
	slect_move_cursor.move_slect_step = 1 ;
	slect_move_cursor.now_slect_move = 0 ;
	slect_cursor_move_init(&slect_move_cursor);  //光标位置初始化
	slect_cursor_move(cursor_refresh_mode,cursor_null);  //关闭光标
	slect_move_cursor.dw_cursor_adderss = EXTERNAL_SLEET_SENSITIVITY_INPUT_SELECT_CURSOR_ADDERSS ;
	slect_move_cursor.max_slect_move = 3 ;
	slect_move_cursor.min_slect_move = 0 ;
	slect_move_cursor.move_slect_step = 1 ;
	slect_move_cursor.now_slect_move = 0 ;
	slect_cursor_move_init(&slect_move_cursor);  //光标位置初始化
	slect_cursor_move(cursor_default_mode,cursor_null);  //显示初始化光标位置
	Buttons_Register(KEY_UP_TRG_NUMBER,Hmi_External_Sleet_Sensitivity_Slcet_Input_Buttons_CB);
	Buttons_Register(KEY_ENTER_TRG_NUMBER,Hmi_External_Sleet_Sensitivity_Slcet_Input_Buttons_CB);
	Buttons_Register(KEY_DOWN_TRG_NUMBER,Hmi_External_Sleet_Sensitivity_Slcet_Input_Buttons_CB);
}

static void EX_Sleet_Sensitivity_Input_Page_Exit(void){
	//clear_time_cnt(AUTO_EXIT_SETS_PAGE_TO_MAIN_PAGE_TIMER_NUMBER);
}

static void Ex_Sleet_Sensitivity_Input_Page_Task(void){
	if(check_time_arrive(AUTO_EXIT_SETS_PAGE_TO_MAIN_PAGE_TIMER_NUMBER,set_ex_sleet_menu_list_pararm_t.auto_exit_sets_page_to_main_time*1000)){
		Back_Main_Page_Load();
		//clear_time_cnt(AUTO_EXIT_SETS_PAGE_TO_MAIN_PAGE_TIMER_NUMBER);
	}
}
static void Hmi_External_Sleet_Sensitivity_Slcet_Input_Buttons_CB(key_Input_Number_Typedef key_number ,Key_Trg_Even key_state){
	if(key_state == KEY_CLICK_ACTION){
		//clear_time_cnt(AUTO_EXIT_SETS_PAGE_TO_MAIN_PAGE_TIMER_NUMBER);
		set_ex_sleet_menu_list_pararm_t.external_para.ExternalSleetSensitivityDate=user_parameter_adjustment(set_ex_sleet_menu_list_pararm_t.external_para.ExternalSleetSensitivityDate,false,4,key_number,set_ex_sleet_menu_list_pararm_t.Ex_Sleet_ShowIntputSensitivityDate_t);
	}
}

/********* 保存设置参数- 外界雨雪传感灵敏度设置页面  ******************/
static void Ex_Sleet_Sensitivity_Enter_Page_Load(void){
	int ret = -1 ;
	type_slect_move_cursor slect_move_cursor;
	slect_move_cursor.dw_cursor_adderss = EXTERNAL_SLEET_SENSITIVITY_SETTING_CURSOR_ADDERSS ;
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
	dw_input_parameter_hint_window( 1 ,EXTERNAL_SLEET_SENSITIVITY_WAIT_WINDOW_VAR_ADDERSS,EXTERNAL_SLEET_SENSITIVITY_SUCCESS_WINDOW_VAR_ADDERSS,EXTERNAL_SLEET_SENSITIVITY_ERROR_WINDOW_VAR_ADDERSS);
	ret = externalparaPoint_amend_config("ExternalSleetSensitivityDate",set_ex_sleet_menu_list_pararm_t.external_para.ExternalSleetSensitivityDate);
	if( !ret){
		 //显示成功窗口
		set_ex_sleet_menu_list_pararm_t.Ex_Sleet_ShowRealTimeSensitivityDate_t(set_ex_sleet_menu_list_pararm_t.external_para.ExternalSleetSensitivityDate);
		dw_input_parameter_hint_window(2 ,EXTERNAL_SLEET_SENSITIVITY_WAIT_WINDOW_VAR_ADDERSS,EXTERNAL_SLEET_SENSITIVITY_SUCCESS_WINDOW_VAR_ADDERSS,EXTERNAL_SLEET_SENSITIVITY_ERROR_WINDOW_VAR_ADDERSS);
	}else{
		//显示错误窗口
		dw_input_parameter_hint_window( 3 ,EXTERNAL_SLEET_SENSITIVITY_WAIT_WINDOW_VAR_ADDERSS,EXTERNAL_SLEET_SENSITIVITY_SUCCESS_WINDOW_VAR_ADDERSS,EXTERNAL_SLEET_SENSITIVITY_ERROR_WINDOW_VAR_ADDERSS);
	}
	Buttons_Register(KEY_ENTER_TRG_NUMBER,Sleet_Slcet_Enter_Window_Buttons_CB);
}

static void EX_Sleet_Sensitivity_Enter_Page_Exit(void){
	//清除窗口
	dw_input_parameter_hint_window( 0 ,EXTERNAL_SLEET_SENSITIVITY_WAIT_WINDOW_VAR_ADDERSS,EXTERNAL_SLEET_SENSITIVITY_SUCCESS_WINDOW_VAR_ADDERSS,EXTERNAL_SLEET_SENSITIVITY_ERROR_WINDOW_VAR_ADDERSS);
	//clear_time_cnt(AUTO_EXIT_SETS_PAGE_TO_MAIN_PAGE_TIMER_NUMBER);
}

static void EX_Sleet_Sensitivity_Enter_Page_Task(void){
	if(check_time_arrive(AUTO_EXIT_SETS_PAGE_TO_MAIN_PAGE_TIMER_NUMBER,set_ex_sleet_menu_list_pararm_t.auto_exit_sets_page_to_main_time*1000)){
		Back_Main_Page_Load();
		//clear_time_cnt(AUTO_EXIT_SETS_PAGE_TO_MAIN_PAGE_TIMER_NUMBER);
	}
}

/********************************************** 切换页面 - 外界雨雪传感器加热设置页面  ***************************************************************/
/* 外界雨雪传感器加热选择设置菜单 */
static MenuList_t External_Sleet_Heat_Setting_Menu_Table[] =
{
	{"加热温度下限设置", NULL, Ex_Sleet_Heat_Lower_Limit_Setting_Page_Load, Ex_Sleet_Heat_Lower_Limit_Setting_Page_Exit, Ex_Sleet_Heat_Lower_Limit_Setting_Page_Task, NULL},

    {"加热温度上限设置", NULL, Ex_Sleet_Heat_Hight_Limit_Setting_Page_Load, Ex_Sleet_Heat_Hight_Limit_Setting_Page_Exit, Ex_Sleet_Heat_Hight_Limit_Setting_Page_Task, NULL},

    {"返回上级菜单", NULL,  Return_Previous_Menu_Page_Load, NULL, NULL, NULL},

    {"返回主页面", NULL,  Back_Main_Page_Load,   NULL,   NULL, NULL},
};

static void Ex_SLeet_Heat_Setting_Page_Load(void){
	type_slect_move_cursor slect_move_cursor;

	slect_move_cursor.dw_cursor_adderss = EXTERNAL_SLEET_HEATTING_SETTING_CURSOR_ADDERSS ;
	slect_move_cursor.max_slect_move = 3 ;
	slect_move_cursor.min_slect_move = 0 ;
	slect_move_cursor.move_slect_step = 1 ;
	slect_move_cursor.now_slect_move = 0 ;
	slect_cursor_move_init(&slect_move_cursor); 		 			//光标位置初始化
	slect_cursor_move(cursor_default_mode,cursor_null);  			//初始化选择设置光标
	dw_show_switching_pages(PAGE_EXTERNAL_SLEET_HEATING_SETTING_NUMBER); //切换页面
	Buttons_Register(KEY_UP_TRG_NUMBER,Sleet_Slcet_Set_Buttons_CB);
	Buttons_Register(KEY_ENTER_TRG_NUMBER,Sleet_Slcet_Set_Buttons_CB);
	Buttons_Register(KEY_DOWN_TRG_NUMBER,Sleet_Slcet_Set_Buttons_CB);
	read_saveenv_cjson_external_parameter(&set_ex_sleet_menu_list_pararm_t.external_para);
	set_ex_sleet_menu_list_pararm_t.Ex_Sleet_ShowRealTimeHeatLowLimitDate_t(set_ex_sleet_menu_list_pararm_t.external_para.ExternalSleetHeatLowerLimitDate);
	set_ex_sleet_menu_list_pararm_t.Ex_Sleet_ShowRealTimeHeatHightLimitDate_t(set_ex_sleet_menu_list_pararm_t.external_para.ExternalSleetHeatHightLimitDate);
	Menu_Bind(External_Sleet_Heat_Setting_Menu_Table, GET_MENU_NUM(External_Sleet_Heat_Setting_Menu_Table), Sleet_SetMenu);
}

static void Ex_SLeet_Heat_Setting_Page_Exit(void){
	//clear_time_cnt(AUTO_EXIT_SETS_PAGE_TO_MAIN_PAGE_TIMER_NUMBER);
}

static void Ex_SLeet_Heat_Setting_Page_Task(void){
	if(check_time_arrive(AUTO_EXIT_SETS_PAGE_TO_MAIN_PAGE_TIMER_NUMBER,set_ex_sleet_menu_list_pararm_t.auto_exit_sets_page_to_main_time*1000)){
			Back_Main_Page_Load();
		}
}


/********************************************** 切换页面 - 外界雨雪传感器加热-加热下限选择设置页面  ***************************************************************/
/* 外界加热下限选择设置菜单 */
static MenuList_t External_Sleet_Heat_Lower_Limit_Input_Menu_Table[] =
{
	{"参数输入框", NULL, Ex_Sleet_Heat_Lower_Limit_Input_Page_Load, Ex_Sleet_Heat_Lower_Limit_Input_Page_Exit, Ex_Sleet_Heat_Lower_Limit_Input_Page_Task, NULL},

    {"保存设置参数", NULL, Ex_Sleet_Heat_Lower_Limit_Input_Enter_Page_Load, Ex_Sleet_Heat_Lower_Limit_Input_Enter_Page_Exit, Ex_Sleet_Heat_Lower_Limit_Input_Enter_Page_Task, NULL},

    {"返回上级菜单", NULL,  Return_Previous_Menu_Page_Load, NULL, NULL, NULL},

    {"返回主页面", NULL,  Back_Main_Page_Load,   NULL,   NULL, NULL},
};
static void Ex_Sleet_Heat_Lower_Limit_Setting_Page_Load(void){
	type_slect_move_cursor slect_move_cursor;

	slect_move_cursor.dw_cursor_adderss = EXTERNAL_SLEET_SENSITIVITY_LOW_LIMIT_INPUT_SELECT_CURSOR_ADDERSS ;
	slect_move_cursor.max_slect_move = 1 ;
	slect_move_cursor.min_slect_move = 0 ;
	slect_move_cursor.move_slect_step = 1 ;
	slect_move_cursor.now_slect_move = 0 ;
	slect_cursor_move_init(&slect_move_cursor);  		//光标位置初始化
	slect_cursor_move(cursor_refresh_mode,cursor_null);  //关闭光标
	slect_move_cursor.dw_cursor_adderss = EXTERNAL_SLEET_HEATTING_LOW_LIMIT_SETTING_CURSOR_ADDERSS ;
	slect_move_cursor.max_slect_move = 3 ;
	slect_move_cursor.min_slect_move = 0 ;
	slect_move_cursor.move_slect_step = 1 ;
	slect_move_cursor.now_slect_move = 0 ;
	slect_cursor_move_init(&slect_move_cursor); 		 			//光标位置初始化
	slect_cursor_move(cursor_default_mode,cursor_null);  			//初始化选择设置光标
	read_saveenv_cjson_external_parameter(&set_ex_sleet_menu_list_pararm_t.external_para);
	set_ex_sleet_menu_list_pararm_t.Ex_Sleet_ShowIntputHeatLowLimitDate_t(set_ex_sleet_menu_list_pararm_t.external_para.ExternalSleetHeatLowerLimitDate);
	dw_show_switching_pages(PAGE_EXTERNAL_SLEET_HEATING_LOW_LIMIT_SETTING_NUMBER); //切换页面
	Buttons_Register(KEY_UP_TRG_NUMBER,Sleet_Slcet_Set_Buttons_CB);
	Buttons_Register(KEY_ENTER_TRG_NUMBER,Sleet_Slcet_Set_Buttons_CB);
	Buttons_Register(KEY_DOWN_TRG_NUMBER,Sleet_Slcet_Set_Buttons_CB);
	Menu_Bind(External_Sleet_Heat_Lower_Limit_Input_Menu_Table, GET_MENU_NUM(External_Sleet_Heat_Lower_Limit_Input_Menu_Table), Sleet_SetMenu);
}
static void Ex_Sleet_Heat_Lower_Limit_Setting_Page_Exit(void){
	//clear_time_cnt(AUTO_EXIT_SETS_PAGE_TO_MAIN_PAGE_TIMER_NUMBER);
}
static void Ex_Sleet_Heat_Lower_Limit_Setting_Page_Task(void){
	if(check_time_arrive(AUTO_EXIT_SETS_PAGE_TO_MAIN_PAGE_TIMER_NUMBER,set_ex_sleet_menu_list_pararm_t.auto_exit_sets_page_to_main_time*1000)){
		Back_Main_Page_Load();
	}
}

/************* 输入参数- 外界雨雪传感器加热-加热下限页面  *******************/
static void Ex_Sleet_Heat_Lower_Limit_Input_Page_Load(void){
	type_slect_move_cursor slect_move_cursor;

	slect_move_cursor.dw_cursor_adderss = EXTERNAL_SLEET_HEATTING_LOW_LIMIT_SETTING_CURSOR_ADDERSS ;
	slect_move_cursor.max_slect_move = 3 ;
	slect_move_cursor.min_slect_move = 0 ;
	slect_move_cursor.move_slect_step = 1 ;
	slect_move_cursor.now_slect_move = 0 ;
	slect_cursor_move_init(&slect_move_cursor);  		//光标位置初始化
	slect_cursor_move(cursor_refresh_mode,cursor_null);  //关闭光标
	slect_move_cursor.dw_cursor_adderss = EXTERNAL_SLEET_SENSITIVITY_LOW_LIMIT_INPUT_SELECT_CURSOR_ADDERSS ;
	slect_move_cursor.max_slect_move = 1 ;
	slect_move_cursor.min_slect_move = 0 ;
	slect_move_cursor.move_slect_step = 1 ;
	slect_move_cursor.now_slect_move = 0 ;
	slect_cursor_move_init(&slect_move_cursor); 		 			//光标位置初始化
	slect_cursor_move(cursor_default_mode,cursor_null);  			//初始化选择设置光标
	Buttons_Register(KEY_UP_TRG_NUMBER,Sleet_Heat_Lower_Limit_Input_Buttons_CB);
	Buttons_Register(KEY_ENTER_TRG_NUMBER,Sleet_Heat_Lower_Limit_Input_Buttons_CB);
	Buttons_Register(KEY_DOWN_TRG_NUMBER,Sleet_Heat_Lower_Limit_Input_Buttons_CB);
}
static void Ex_Sleet_Heat_Lower_Limit_Input_Page_Exit(void){
	//clear_time_cnt(AUTO_EXIT_SETS_PAGE_TO_MAIN_PAGE_TIMER_NUMBER);
}
static void Ex_Sleet_Heat_Lower_Limit_Input_Page_Task(void){
	if(check_time_arrive(AUTO_EXIT_SETS_PAGE_TO_MAIN_PAGE_TIMER_NUMBER,set_ex_sleet_menu_list_pararm_t.auto_exit_sets_page_to_main_time*1000)){
		Back_Main_Page_Load();
	}
}
static void Sleet_Heat_Lower_Limit_Input_Buttons_CB(key_Input_Number_Typedef key_number ,Key_Trg_Even key_state){
	if(key_state == KEY_CLICK_ACTION){
		//clear_time_cnt(AUTO_EXIT_SETS_PAGE_TO_MAIN_PAGE_TIMER_NUMBER);
		set_ex_sleet_menu_list_pararm_t.external_para.ExternalSleetHeatLowerLimitDate=user_parameter_adjustment(set_ex_sleet_menu_list_pararm_t.external_para.ExternalSleetHeatLowerLimitDate,false,2,key_number,set_ex_sleet_menu_list_pararm_t.Ex_Sleet_ShowIntputHeatLowLimitDate_t);
	}
}
/********* 保存设置参数- 外界雨雪传感器加热-加热下限页面 ******************/
static void Ex_Sleet_Heat_Lower_Limit_Input_Enter_Page_Load(void){
	int ret = -1 ;
	type_slect_move_cursor slect_move_cursor;
	slect_move_cursor.dw_cursor_adderss = EXTERNAL_SLEET_HEATTING_LOW_LIMIT_SETTING_CURSOR_ADDERSS ;
	slect_move_cursor.max_slect_move = 3 ;
	slect_move_cursor.min_slect_move = 0 ;
	slect_move_cursor.move_slect_step = 1 ;
	slect_move_cursor.now_slect_move = 0 ;
	slect_cursor_move_init(&slect_move_cursor);  		//光标位置初始化
	slect_cursor_move(cursor_refresh_mode,cursor_null);  //关闭光标
	Buttons_UnRegister(KEY_UP_TRG_NUMBER);
	Buttons_UnRegister(KEY_ENTER_TRG_NUMBER);
	Buttons_UnRegister(KEY_DOWN_TRG_NUMBER);
	//显示等待窗口
	dw_input_parameter_hint_window( 1 ,EXTERNAL_SLEET_INTPUT_HEATTING_LOW_LIMIT_WAIT_WINDOW_VAR_ADDERSS,EXTERNAL_SLEET_INTPUT_HEATTING_LOW_LIMIT_SUCCESS_WINDOW_VAR_ADDERSS,EXTERNAL_ISLEET_INTPUT_HEATTING_LOW_LIMIT_ERROR_WINDOW_VAR_ADDERSS);
	ret = externalparaPoint_amend_config("ExternalSleetHeatLowerLimitDate",set_ex_sleet_menu_list_pararm_t.external_para.ExternalSleetHeatLowerLimitDate);
	if( !ret){
		 //显示成功窗口
		set_ex_sleet_menu_list_pararm_t.Ex_Sleet_ShowRealTimeHeatLowLimitDate_t(set_ex_sleet_menu_list_pararm_t.external_para.ExternalSleetHeatLowerLimitDate);
		dw_input_parameter_hint_window(2 ,EXTERNAL_SLEET_INTPUT_HEATTING_LOW_LIMIT_WAIT_WINDOW_VAR_ADDERSS,EXTERNAL_SLEET_INTPUT_HEATTING_LOW_LIMIT_SUCCESS_WINDOW_VAR_ADDERSS,EXTERNAL_ISLEET_INTPUT_HEATTING_LOW_LIMIT_ERROR_WINDOW_VAR_ADDERSS);
	}else{
		//显示错误窗口
		dw_input_parameter_hint_window( 3 ,EXTERNAL_SLEET_INTPUT_HEATTING_LOW_LIMIT_WAIT_WINDOW_VAR_ADDERSS,EXTERNAL_SLEET_INTPUT_HEATTING_LOW_LIMIT_SUCCESS_WINDOW_VAR_ADDERSS,EXTERNAL_ISLEET_INTPUT_HEATTING_LOW_LIMIT_ERROR_WINDOW_VAR_ADDERSS);
	}
	Buttons_Register(KEY_ENTER_TRG_NUMBER,Sleet_Slcet_Enter_Window_Buttons_CB);
}

static void Ex_Sleet_Heat_Lower_Limit_Input_Enter_Page_Exit(void){
	//清除窗口
	dw_input_parameter_hint_window(0  ,EXTERNAL_SLEET_INTPUT_HEATTING_LOW_LIMIT_WAIT_WINDOW_VAR_ADDERSS,EXTERNAL_SLEET_INTPUT_HEATTING_LOW_LIMIT_SUCCESS_WINDOW_VAR_ADDERSS,EXTERNAL_ISLEET_INTPUT_HEATTING_LOW_LIMIT_ERROR_WINDOW_VAR_ADDERSS);
	//clear_time_cnt(AUTO_EXIT_SETS_PAGE_TO_MAIN_PAGE_TIMER_NUMBER);
}

static void Ex_Sleet_Heat_Lower_Limit_Input_Enter_Page_Task(void){
	if(check_time_arrive(AUTO_EXIT_SETS_PAGE_TO_MAIN_PAGE_TIMER_NUMBER,set_ex_sleet_menu_list_pararm_t.auto_exit_sets_page_to_main_time*1000)){
			Back_Main_Page_Load();
		}
}


/********************************************** 切换页面 - 外界雨雪传感器加热-加热上限设置页面  ***************************************************************/
/* 外界雨雪传感器加热-加热上限选择设置菜单 */
static MenuList_t External_Sleet_Heat_Hight_Limit_Input_Menu_Table[] =
{
	{"参数输入框", NULL, Ex_Sleet_Heat_Hight_Limit_Input_Page_Load, Ex_Sleet_Heat_Hight_Limit_Input_Page_Exit, Ex_Sleet_Heat_Hight_Limit_Input_Page_Task, NULL},

    {"保存设置参数", NULL, Ex_Sleet_Heat_Hight_Limit_Input_Enter_Page_Load, Ex_Sleet_Heat_Hight_Limit_Input_Enter_Page_Exit, Ex_Sleet_Heat_Hight_Limit_Input_Enter_Page_Task, NULL},

    {"返回上级菜单", NULL,  Return_Previous_Menu_Page_Load, NULL, NULL, NULL},

    {"返回主页面", NULL,  Back_Main_Page_Load,   NULL,   NULL, NULL},
};


static void Ex_Sleet_Heat_Hight_Limit_Setting_Page_Load(void){
	type_slect_move_cursor slect_move_cursor;

	slect_move_cursor.dw_cursor_adderss = EXTERNAL_SLEET_SENSITIVITY_HIGH_LIMIT_INPUT_SELECT_CURSOR_ADDERSS ;
	slect_move_cursor.max_slect_move = 1 ;
	slect_move_cursor.min_slect_move = 0 ;
	slect_move_cursor.move_slect_step = 1 ;
	slect_move_cursor.now_slect_move = 0 ;
	slect_cursor_move_init(&slect_move_cursor);  		//光标位置初始化
	slect_cursor_move(cursor_refresh_mode,cursor_null);  //关闭光标
	slect_move_cursor.dw_cursor_adderss = EXTERNAL_SLEET_HEATTING_HIGH_LIMIT_SETTING_CURSOR_ADDERSS ;
	slect_move_cursor.max_slect_move = 3 ;
	slect_move_cursor.min_slect_move = 0 ;
	slect_move_cursor.move_slect_step = 1 ;
	slect_move_cursor.now_slect_move = 0 ;
	slect_cursor_move_init(&slect_move_cursor); 		 			//光标位置初始化
	slect_cursor_move(cursor_default_mode,cursor_null);  			//初始化选择设置光标
	read_saveenv_cjson_external_parameter(&set_ex_sleet_menu_list_pararm_t.external_para);
	set_ex_sleet_menu_list_pararm_t.Ex_Sleet_ShowIntputHeatHightLimitDate_t(set_ex_sleet_menu_list_pararm_t.external_para.ExternalSleetHeatHightLimitDate);
	dw_show_switching_pages(PAGE_EXTERNAL_SLEET_HEATING_HIGH_LIMIT_SETTING_NUMBER); //切换页面
	Buttons_Register(KEY_UP_TRG_NUMBER,Sleet_Slcet_Set_Buttons_CB);
	Buttons_Register(KEY_ENTER_TRG_NUMBER,Sleet_Slcet_Set_Buttons_CB);
	Buttons_Register(KEY_DOWN_TRG_NUMBER,Sleet_Slcet_Set_Buttons_CB);
	Menu_Bind(External_Sleet_Heat_Hight_Limit_Input_Menu_Table, GET_MENU_NUM(External_Sleet_Heat_Hight_Limit_Input_Menu_Table), Sleet_SetMenu);
}
static void Ex_Sleet_Heat_Hight_Limit_Setting_Page_Exit(void){
	//clear_time_cnt(AUTO_EXIT_SETS_PAGE_TO_MAIN_PAGE_TIMER_NUMBER);
}
static void Ex_Sleet_Heat_Hight_Limit_Setting_Page_Task(void){
	if(check_time_arrive(AUTO_EXIT_SETS_PAGE_TO_MAIN_PAGE_TIMER_NUMBER,set_ex_sleet_menu_list_pararm_t.auto_exit_sets_page_to_main_time*1000)){
			Back_Main_Page_Load();
		}
}
/************* 输入参数-  外界雨雪传感器加热-加热上限设置页面  *******************/
static void Ex_Sleet_Heat_Hight_Limit_Input_Page_Load(void){
	type_slect_move_cursor slect_move_cursor;

	slect_move_cursor.dw_cursor_adderss = EXTERNAL_SLEET_HEATTING_HIGH_LIMIT_SETTING_CURSOR_ADDERSS ;
	slect_move_cursor.max_slect_move = 3 ;
	slect_move_cursor.min_slect_move = 0 ;
	slect_move_cursor.move_slect_step = 1 ;
	slect_move_cursor.now_slect_move = 0 ;
	slect_cursor_move_init(&slect_move_cursor);  		//光标位置初始化
	slect_cursor_move(cursor_refresh_mode,cursor_null);  //关闭光标
	slect_move_cursor.dw_cursor_adderss = EXTERNAL_SLEET_SENSITIVITY_HIGH_LIMIT_INPUT_SELECT_CURSOR_ADDERSS ;
	slect_move_cursor.max_slect_move = 1 ;
	slect_move_cursor.min_slect_move = 0 ;
	slect_move_cursor.move_slect_step = 1 ;
	slect_move_cursor.now_slect_move = 0 ;
	slect_cursor_move_init(&slect_move_cursor); 		 			//光标位置初始化
	slect_cursor_move(cursor_default_mode,cursor_null);  			//初始化选择设置光标
	Buttons_Register(KEY_UP_TRG_NUMBER,Ex_Sleet_Heat_Hight_Limit_Input_CB);
	Buttons_Register(KEY_ENTER_TRG_NUMBER,Ex_Sleet_Heat_Hight_Limit_Input_CB);
	Buttons_Register(KEY_DOWN_TRG_NUMBER,Ex_Sleet_Heat_Hight_Limit_Input_CB);
}
static void Ex_Sleet_Heat_Hight_Limit_Input_Page_Exit(void){
	//clear_time_cnt(AUTO_EXIT_SETS_PAGE_TO_MAIN_PAGE_TIMER_NUMBER);
}
static void Ex_Sleet_Heat_Hight_Limit_Input_Page_Task(void){
	if(check_time_arrive(AUTO_EXIT_SETS_PAGE_TO_MAIN_PAGE_TIMER_NUMBER,set_ex_sleet_menu_list_pararm_t.auto_exit_sets_page_to_main_time*1000)){
		Back_Main_Page_Load();
	}
}

static void Ex_Sleet_Heat_Hight_Limit_Input_CB(key_Input_Number_Typedef key_number ,Key_Trg_Even key_state){
	if(key_state == KEY_CLICK_ACTION){
		//clear_time_cnt(AUTO_EXIT_SETS_PAGE_TO_MAIN_PAGE_TIMER_NUMBER);
		set_ex_sleet_menu_list_pararm_t.external_para.ExternalSleetHeatHightLimitDate=user_parameter_adjustment(set_ex_sleet_menu_list_pararm_t.external_para.ExternalSleetHeatHightLimitDate,false,2,key_number,set_ex_sleet_menu_list_pararm_t.Ex_Sleet_ShowIntputHeatHightLimitDate_t);
	}
}
/********* 保存设置参数- 外界雨雪传感器加热-加热上限页面 ******************/
static void Ex_Sleet_Heat_Hight_Limit_Input_Enter_Page_Load(void){
	int ret = -1 ;
	type_slect_move_cursor slect_move_cursor;
	slect_move_cursor.dw_cursor_adderss = EXTERNAL_SLEET_HEATTING_HIGH_LIMIT_SETTING_CURSOR_ADDERSS ;
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
	dw_input_parameter_hint_window( 1 ,EXTERNAL_SLEET_INTPUT_HEATTING_HIGH_LIMIT_WAIT_WINDOW_VAR_ADDERSS,EXTERNAL_SLEET_INTPUT_HEATTING_HIGH_LIMIT_SUCCESS_WINDOW_VAR_ADDERSS,EXTERNAL_SLEET_INTPUT_HEATTING_HIGH_LIMIT_ERROR_WINDOW_VAR_ADDERSS);
	ret = externalparaPoint_amend_config("ExternalSleetHeatHightLimitDate",set_ex_sleet_menu_list_pararm_t.external_para.ExternalSleetHeatHightLimitDate);
	if( !ret){
		 //显示成功窗口
		set_ex_sleet_menu_list_pararm_t.Ex_Sleet_ShowRealTimeHeatHightLimitDate_t(set_ex_sleet_menu_list_pararm_t.external_para.ExternalSleetHeatHightLimitDate);
		dw_input_parameter_hint_window(2 ,EXTERNAL_SLEET_INTPUT_HEATTING_HIGH_LIMIT_WAIT_WINDOW_VAR_ADDERSS,EXTERNAL_SLEET_INTPUT_HEATTING_HIGH_LIMIT_SUCCESS_WINDOW_VAR_ADDERSS,EXTERNAL_SLEET_INTPUT_HEATTING_HIGH_LIMIT_ERROR_WINDOW_VAR_ADDERSS);
	}else{
		//显示错误窗口
		dw_input_parameter_hint_window( 3 ,EXTERNAL_SLEET_INTPUT_HEATTING_HIGH_LIMIT_WAIT_WINDOW_VAR_ADDERSS,EXTERNAL_SLEET_INTPUT_HEATTING_HIGH_LIMIT_SUCCESS_WINDOW_VAR_ADDERSS,EXTERNAL_SLEET_INTPUT_HEATTING_HIGH_LIMIT_ERROR_WINDOW_VAR_ADDERSS);
	}
	Buttons_Register(KEY_ENTER_TRG_NUMBER,Sleet_Slcet_Enter_Window_Buttons_CB);
}

static void Ex_Sleet_Heat_Hight_Limit_Input_Enter_Page_Exit(void){
	//清除窗口
	dw_input_parameter_hint_window(0  ,EXTERNAL_SLEET_INTPUT_HEATTING_HIGH_LIMIT_WAIT_WINDOW_VAR_ADDERSS,EXTERNAL_SLEET_INTPUT_HEATTING_HIGH_LIMIT_SUCCESS_WINDOW_VAR_ADDERSS,EXTERNAL_SLEET_INTPUT_HEATTING_HIGH_LIMIT_ERROR_WINDOW_VAR_ADDERSS);
	//clear_time_cnt(AUTO_EXIT_SETS_PAGE_TO_MAIN_PAGE_TIMER_NUMBER);
}

static void Ex_Sleet_Heat_Hight_Limit_Input_Enter_Page_Task(void){
	if(check_time_arrive(AUTO_EXIT_SETS_PAGE_TO_MAIN_PAGE_TIMER_NUMBER,set_ex_sleet_menu_list_pararm_t.auto_exit_sets_page_to_main_time*1000)){
		Back_Main_Page_Load();
	}
}


/********************************************** 切换页面 -外界雨雪传感器报警复归选择设置页面  ***************************************************************/
/* 外界雨雪传感器报警复归选择设置菜单 */
static MenuList_t External_Sleet_Delay_Alarm_Menu_Table[] =
{
	{"参数输入框", NULL, Ex_Sleet_Delay_Alarm_Input_Page_Load, Ex_Sleet_Delay_Alarm_Input_Page_Exit, Ex_Sleet_Delay_Alarm_Input_Page_Task, NULL},

    {"保存设置参数", NULL, Ex_Sleet_Delay_Alarm_Input_Enter_Page_Load, Ex_Sleet_Delay_Alarm_Input_Enter_Page_Exit, Ex_Sleet_Delay_Alarm_Input_Enter_Page_Task, NULL},

    {"返回上级菜单", NULL,  Return_Previous_Menu_Page_Load, NULL, NULL, NULL},

    {"返回主页面", NULL,  Back_Main_Page_Load,   NULL,   NULL, NULL},
};

static void Ex_Sleet_Delay_Alarm_Setting_Page_Load(void){
	type_slect_move_cursor slect_move_cursor;

	slect_move_cursor.dw_cursor_adderss = EXTERNAL_SLEET_DELAY_ALARM_RESET_INPUT_SELECT_CURSOR_ADDERSS ;
	slect_move_cursor.max_slect_move = 3 ;
	slect_move_cursor.min_slect_move = 0 ;
	slect_move_cursor.move_slect_step = 1 ;
	slect_move_cursor.now_slect_move = 0 ;
	slect_cursor_move_init(&slect_move_cursor);  		//输入指示光标位置初始化
	slect_cursor_move(cursor_refresh_mode,cursor_null);  //关闭输入指示光标
	slect_move_cursor.dw_cursor_adderss = EXTERNAL_SLEET_DELAY_ALARM_RESET_SETTING_CURSOR_ADDERSS ;
	slect_move_cursor.max_slect_move = 3 ;
	slect_move_cursor.min_slect_move = 0 ;
	slect_move_cursor.move_slect_step = 1 ;
	slect_move_cursor.now_slect_move = 0 ;
	slect_cursor_move_init(&slect_move_cursor); 		 			//光标位置初始化
	slect_cursor_move(cursor_default_mode,cursor_null);  			//初始化选择设置光标
	read_saveenv_cjson_external_parameter(&set_ex_sleet_menu_list_pararm_t.external_para);
	set_ex_sleet_menu_list_pararm_t.Ex_Sleet_ShowIntputDelayAlarmResetDate_t(set_ex_sleet_menu_list_pararm_t.external_para.ExternalSleetDelayAlarmRestDate); //显示输入报警复归延时值
	dw_show_switching_pages(PAGE_EXTERNAL_SLEET_DELAY_ALARM_RESET_SETTING_NUMBER); //切换页面
	Buttons_Register(KEY_UP_TRG_NUMBER,Sleet_Slcet_Set_Buttons_CB);
	Buttons_Register(KEY_ENTER_TRG_NUMBER,Sleet_Slcet_Set_Buttons_CB);
	Buttons_Register(KEY_DOWN_TRG_NUMBER,Sleet_Slcet_Set_Buttons_CB);
	Menu_Bind(External_Sleet_Delay_Alarm_Menu_Table, GET_MENU_NUM(External_Sleet_Delay_Alarm_Menu_Table), Sleet_SetMenu);
}

static void Ex_Sleet_Delay_Alarm_Setting_Page_Exit(void){
	//clear_time_cnt(AUTO_EXIT_SETS_PAGE_TO_MAIN_PAGE_TIMER_NUMBER);
}
static void Ex_Sleet_Delay_Alarm_Setting_Page_Task(void){
	if(check_time_arrive(AUTO_EXIT_SETS_PAGE_TO_MAIN_PAGE_TIMER_NUMBER,set_ex_sleet_menu_list_pararm_t.auto_exit_sets_page_to_main_time*1000)){
		Back_Main_Page_Load();
		//clear_time_cnt(AUTO_EXIT_SETS_PAGE_TO_MAIN_PAGE_TIMER_NUMBER);
	}
}

/************* 输入参数- 外界雨雪传感器报警复归设置页面  *******************/
static void Ex_Sleet_Delay_Alarm_Input_Page_Load(void){
	type_slect_move_cursor slect_move_cursor;

	slect_move_cursor.dw_cursor_adderss = EXTERNAL_SLEET_DELAY_ALARM_RESET_SETTING_CURSOR_ADDERSS ;
	slect_move_cursor.max_slect_move = 3 ;
	slect_move_cursor.min_slect_move = 0 ;
	slect_move_cursor.move_slect_step = 1 ;
	slect_move_cursor.now_slect_move = 0 ;
	slect_cursor_move_init(&slect_move_cursor);  //光标位置初始化
	slect_cursor_move(cursor_refresh_mode,cursor_null);  //关闭选择设置光标
	slect_move_cursor.dw_cursor_adderss = EXTERNAL_SLEET_DELAY_ALARM_RESET_INPUT_SELECT_CURSOR_ADDERSS ;
	slect_move_cursor.max_slect_move = 3 ;
	slect_move_cursor.min_slect_move = 0 ;
	slect_move_cursor.move_slect_step = 1 ;
	slect_move_cursor.now_slect_move = 0 ;
	slect_cursor_move_init(&slect_move_cursor);  //光标位置初始化
	slect_cursor_move(cursor_default_mode,cursor_null);  //显示初始化输入指示光标位置
	Buttons_Register(KEY_UP_TRG_NUMBER,Hmi_External_Sleet_Delay_Alarm_Input_Buttons_CB);
	Buttons_Register(KEY_ENTER_TRG_NUMBER,Hmi_External_Sleet_Delay_Alarm_Input_Buttons_CB);
	Buttons_Register(KEY_DOWN_TRG_NUMBER,Hmi_External_Sleet_Delay_Alarm_Input_Buttons_CB);
}

static void Ex_Sleet_Delay_Alarm_Input_Page_Exit(void){
	//clear_time_cnt(AUTO_EXIT_SETS_PAGE_TO_MAIN_PAGE_TIMER_NUMBER);
}

static void Ex_Sleet_Delay_Alarm_Input_Page_Task(void){
	if(check_time_arrive(AUTO_EXIT_SETS_PAGE_TO_MAIN_PAGE_TIMER_NUMBER,set_ex_sleet_menu_list_pararm_t.auto_exit_sets_page_to_main_time*1000)){
		Back_Main_Page_Load();
	}
}

static void Hmi_External_Sleet_Delay_Alarm_Input_Buttons_CB(key_Input_Number_Typedef key_number ,Key_Trg_Even key_state){
	if(key_state == KEY_CLICK_ACTION){
		//clear_time_cnt(AUTO_EXIT_SETS_PAGE_TO_MAIN_PAGE_TIMER_NUMBER);
		set_ex_sleet_menu_list_pararm_t.external_para.ExternalSleetDelayAlarmRestDate=user_parameter_adjustment(set_ex_sleet_menu_list_pararm_t.external_para.ExternalSleetDelayAlarmRestDate,false,4,key_number,set_ex_sleet_menu_list_pararm_t.Ex_Sleet_ShowIntputDelayAlarmResetDate_t);
	}
}

/********* 保存设置参数- 外界雨雪传感器报警复归设置页面 ******************/
static void Ex_Sleet_Delay_Alarm_Input_Enter_Page_Load(void){
	int ret = -1 ;
	type_slect_move_cursor slect_move_cursor;
	slect_move_cursor.dw_cursor_adderss = EXTERNAL_SLEET_DELAY_ALARM_RESET_INPUT_SELECT_CURSOR_ADDERSS ;
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
	dw_input_parameter_hint_window( 1 ,EXTERNAL_SLEET_DELAY_ALARM_RESET_WAIT_WINDOW_VAR_ADDERSS,EXTERNAL_SLEET_DELAY_ALARM_RESET_SUCCESS_WINDOW_VAR_ADDERSS,EXTERNAL_SLEET_DELAY_ALARM_RESET_ERROR_WINDOW_VAR_ADDERSS);
	ret = externalparaPoint_amend_config("ExternalSleetDelayAlarmRestDate",set_ex_sleet_menu_list_pararm_t.external_para.ExternalSleetDelayAlarmRestDate);
	if( !ret){
		 //显示成功窗口
		set_ex_sleet_menu_list_pararm_t.Ex_Sleet_ShowRealTimeDelayAlarmResetDate_t(set_ex_sleet_menu_list_pararm_t.external_para.ExternalSleetDelayAlarmRestDate); //显示采样速率
		dw_input_parameter_hint_window(2 ,EXTERNAL_SLEET_DELAY_ALARM_RESET_WAIT_WINDOW_VAR_ADDERSS,EXTERNAL_SLEET_DELAY_ALARM_RESET_SUCCESS_WINDOW_VAR_ADDERSS,EXTERNAL_SLEET_DELAY_ALARM_RESET_ERROR_WINDOW_VAR_ADDERSS);
	}else{
		//显示错误窗口
		dw_input_parameter_hint_window( 3 ,EXTERNAL_SLEET_DELAY_ALARM_RESET_WAIT_WINDOW_VAR_ADDERSS,EXTERNAL_SLEET_DELAY_ALARM_RESET_SUCCESS_WINDOW_VAR_ADDERSS,EXTERNAL_SLEET_DELAY_ALARM_RESET_ERROR_WINDOW_VAR_ADDERSS);
	}
	Buttons_Register(KEY_ENTER_TRG_NUMBER,Sleet_Slcet_Enter_Window_Buttons_CB);
}

static void Ex_Sleet_Delay_Alarm_Input_Enter_Page_Exit(void){
	//清除窗口
	dw_input_parameter_hint_window( 0 ,EXTERNAL_SLEET_DELAY_ALARM_RESET_WAIT_WINDOW_VAR_ADDERSS,EXTERNAL_SLEET_DELAY_ALARM_RESET_SUCCESS_WINDOW_VAR_ADDERSS,EXTERNAL_SLEET_DELAY_ALARM_RESET_ERROR_WINDOW_VAR_ADDERSS);
	//clear_time_cnt(AUTO_EXIT_SETS_PAGE_TO_MAIN_PAGE_TIMER_NUMBER);
}

static void Ex_Sleet_Delay_Alarm_Input_Enter_Page_Task(void){
	if(check_time_arrive(AUTO_EXIT_SETS_PAGE_TO_MAIN_PAGE_TIMER_NUMBER,set_ex_sleet_menu_list_pararm_t.auto_exit_sets_page_to_main_time*1000)){
		Back_Main_Page_Load();
	}
}


/********************************************** 切换页面 -外界雨雪传感器采集速率页面  ***************************************************************/
/* 外界雨雪传感器采集速率菜单 */
static MenuList_t External_Sleet_Sample_Rate_Menu_Table[] =
{
	{"参数输入框", NULL, Ex_Sleet_Sample_Rate_Input_Page_Load, Ex_Sleet_Sample_Rate_Input_Page_Exit, Ex_Sleet_Sample_Rate_Input_Page_Task, NULL},

    {"保存设置参数", NULL, Ex_Sleet_Sample_Rate_Enter_Page_Load, Ex_Sleet_Sample_Rate_Enter_Page_Exit, Ex_Sleet_Sample_Rate_Enter_Page_Task, NULL},

    {"返回上级菜单", NULL,  Return_Previous_Menu_Page_Load, NULL, NULL, NULL},

    {"返回主页面", NULL,  Back_Main_Page_Load,   NULL,   NULL, NULL},
};

static void Ex_Sleet_Acquisition_Rate_Page_Load(void){
	type_slect_move_cursor slect_move_cursor;

	slect_move_cursor.dw_cursor_adderss = EXTERNAL_SLEET_SAMPLE_RATE_INPUT_SELECT_CURSOR_ADDERSS ;
	slect_move_cursor.max_slect_move = 1 ;
	slect_move_cursor.min_slect_move = 0 ;
	slect_move_cursor.move_slect_step = 1 ;
	slect_move_cursor.now_slect_move = 0 ;
	slect_cursor_move_init(&slect_move_cursor);  		//输入指示光标位置初始化
	slect_cursor_move(cursor_refresh_mode,cursor_null);  //关闭输入指示光标
	slect_move_cursor.dw_cursor_adderss = EXTERNAL_SLEET_SAMPLE_RATE_SELECT_CURSOR_ADDERSS ;
	slect_move_cursor.max_slect_move = 3 ;
	slect_move_cursor.min_slect_move = 0 ;
	slect_move_cursor.move_slect_step = 1 ;
	slect_move_cursor.now_slect_move = 0 ;
	slect_cursor_move_init(&slect_move_cursor); 		 			//光标位置初始化
	slect_cursor_move(cursor_default_mode,cursor_null);  			//初始化选择设置光标
	read_saveenv_cjson_external_parameter(&set_ex_sleet_menu_list_pararm_t.external_para);
	set_ex_sleet_menu_list_pararm_t.Ex_Sleet_ShowSampleRateDate(set_ex_sleet_menu_list_pararm_t.external_para.ExternalSleetSampleRateDate); //显示采样速率
	dw_show_switching_pages(PAGE_EXTERNAL_SLEET_SAMPLE_RATE_SETTING_NUMBER); //切换页面
	Buttons_Register(KEY_UP_TRG_NUMBER,Sleet_Slcet_Set_Buttons_CB);
	Buttons_Register(KEY_ENTER_TRG_NUMBER,Sleet_Slcet_Set_Buttons_CB);
	Buttons_Register(KEY_DOWN_TRG_NUMBER,Sleet_Slcet_Set_Buttons_CB);
	Menu_Bind(External_Sleet_Sample_Rate_Menu_Table, GET_MENU_NUM(External_Sleet_Sample_Rate_Menu_Table), Sleet_SetMenu);
}

static void Ex_Sleet_Acquisition_Rate_Page_Exit(void){
	//clear_time_cnt(AUTO_EXIT_SETS_PAGE_TO_MAIN_PAGE_TIMER_NUMBER);
}
static void Ex_Sleet_Acquisition_Rate_Page_Task(void){
	if(check_time_arrive(AUTO_EXIT_SETS_PAGE_TO_MAIN_PAGE_TIMER_NUMBER,set_ex_sleet_menu_list_pararm_t.auto_exit_sets_page_to_main_time*1000)){
		Back_Main_Page_Load();
		//clear_time_cnt(AUTO_EXIT_SETS_PAGE_TO_MAIN_PAGE_TIMER_NUMBER);
	}
}

/************* 输入参数- 外界雨雪传感器采样速率页面  *******************/
static void Ex_Sleet_Sample_Rate_Input_Page_Load(void){
	type_slect_move_cursor slect_move_cursor;

	slect_move_cursor.dw_cursor_adderss = EXTERNAL_SLEET_SAMPLE_RATE_SELECT_CURSOR_ADDERSS ;
	slect_move_cursor.max_slect_move = 3 ;
	slect_move_cursor.min_slect_move = 0 ;
	slect_move_cursor.move_slect_step = 1 ;
	slect_move_cursor.now_slect_move = 0 ;
	slect_cursor_move_init(&slect_move_cursor);  //光标位置初始化
	slect_cursor_move(cursor_refresh_mode,cursor_null);  //关闭选择设置光标
	slect_move_cursor.dw_cursor_adderss = EXTERNAL_SLEET_SAMPLE_RATE_INPUT_SELECT_CURSOR_ADDERSS ;
	slect_move_cursor.max_slect_move = 1 ;
	slect_move_cursor.min_slect_move = 0 ;
	slect_move_cursor.move_slect_step = 1 ;
	slect_move_cursor.now_slect_move = 0 ;
	slect_cursor_move_init(&slect_move_cursor);  //光标位置初始化
	slect_cursor_move(cursor_default_mode,cursor_null);  //显示初始化输入指示光标位置
	Buttons_Register(KEY_UP_TRG_NUMBER,Hmi_External_Sleet_Sample_Rate_Input_Buttons_CB);
	Buttons_Register(KEY_ENTER_TRG_NUMBER,Hmi_External_Sleet_Sample_Rate_Input_Buttons_CB);
	Buttons_Register(KEY_DOWN_TRG_NUMBER,Hmi_External_Sleet_Sample_Rate_Input_Buttons_CB);
}

static void Ex_Sleet_Sample_Rate_Input_Page_Exit(void){
	//clear_time_cnt(AUTO_EXIT_SETS_PAGE_TO_MAIN_PAGE_TIMER_NUMBER);
}

static void Ex_Sleet_Sample_Rate_Input_Page_Task(void){
	if(check_time_arrive(AUTO_EXIT_SETS_PAGE_TO_MAIN_PAGE_TIMER_NUMBER,set_ex_sleet_menu_list_pararm_t.auto_exit_sets_page_to_main_time*1000)){
		Back_Main_Page_Load();
	}
}

static void Hmi_External_Sleet_Sample_Rate_Input_Buttons_CB(key_Input_Number_Typedef key_number ,Key_Trg_Even key_state){
	if(key_state == KEY_CLICK_ACTION){
		//clear_time_cnt(AUTO_EXIT_SETS_PAGE_TO_MAIN_PAGE_TIMER_NUMBER);
		set_ex_sleet_menu_list_pararm_t.external_para.ExternalSleetSampleRateDate=user_parameter_adjustment(set_ex_sleet_menu_list_pararm_t.external_para.ExternalSleetSampleRateDate,0,2,key_number,set_ex_sleet_menu_list_pararm_t.Ex_Sleet_ShowSampleRateDate);
	}
}

/********* 保存设置参数- 外界雨雪传感器采样速率  ******************/
static void Ex_Sleet_Sample_Rate_Enter_Page_Load(void){
	int ret = -1 ;
	type_slect_move_cursor slect_move_cursor;
	slect_move_cursor.dw_cursor_adderss = EXTERNAL_SLEET_SAMPLE_RATE_SELECT_CURSOR_ADDERSS ;
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
	dw_input_parameter_hint_window( 1 ,EXTERNAL_SLEET_SAMPLE_RATE_WAIT_WINDOW_VAR_ADDERSS,EXTERNAL_SLEET_SAMPLE_RATE_SUCCESS_WINDOW_VAR_ADDERSS,EXTERNAL_SLEET_SAMPLE_RATE_ERROR_WINDOW_VAR_ADDERSS);
	ret = externalparaPoint_amend_config("ExternalSleetSampleRateDate",set_ex_sleet_menu_list_pararm_t.external_para.ExternalSleetSampleRateDate);
	if( !ret){
		 //显示成功窗口
		dw_input_parameter_hint_window(2,EXTERNAL_SLEET_SAMPLE_RATE_WAIT_WINDOW_VAR_ADDERSS,EXTERNAL_SLEET_SAMPLE_RATE_SUCCESS_WINDOW_VAR_ADDERSS,EXTERNAL_SLEET_SAMPLE_RATE_ERROR_WINDOW_VAR_ADDERSS);
	}else{
		//显示错误窗口
		dw_input_parameter_hint_window( 3 ,EXTERNAL_SLEET_SAMPLE_RATE_WAIT_WINDOW_VAR_ADDERSS,EXTERNAL_SLEET_SAMPLE_RATE_SUCCESS_WINDOW_VAR_ADDERSS,EXTERNAL_SLEET_SAMPLE_RATE_ERROR_WINDOW_VAR_ADDERSS);
	}
	Buttons_Register(KEY_ENTER_TRG_NUMBER,Sleet_Slcet_Enter_Window_Buttons_CB);
}

static void Ex_Sleet_Sample_Rate_Enter_Page_Exit(void){
	//清除窗口
	dw_input_parameter_hint_window( 0 ,EXTERNAL_SLEET_SAMPLE_RATE_WAIT_WINDOW_VAR_ADDERSS,EXTERNAL_SLEET_SAMPLE_RATE_SUCCESS_WINDOW_VAR_ADDERSS,EXTERNAL_SLEET_SAMPLE_RATE_ERROR_WINDOW_VAR_ADDERSS);
	//clear_time_cnt(AUTO_EXIT_SETS_PAGE_TO_MAIN_PAGE_TIMER_NUMBER);
}

static void Ex_Sleet_Sample_Rate_Enter_Page_Task(void){
	if(check_time_arrive(AUTO_EXIT_SETS_PAGE_TO_MAIN_PAGE_TIMER_NUMBER,set_ex_sleet_menu_list_pararm_t.auto_exit_sets_page_to_main_time*1000)){
		Back_Main_Page_Load();
	}
}

/************* 外界雨雪传感器公共回调函数  *******************/
static void Sleet_Slcet_Set_Buttons_CB( key_Input_Number_Typedef key_number , Key_Trg_Even key_state){
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

static void Sleet_Slcet_Enter_Window_Buttons_CB( key_Input_Number_Typedef key_number , Key_Trg_Even key_state){
	if(key_state == KEY_CLICK_ACTION){
		//clear_time_cnt(AUTO_EXIT_SETS_PAGE_TO_MAIN_PAGE_TIMER_NUMBER);
		switch(key_number){
		case KEY_UP_TRG_NUMBER :
			log_d("slect up ");
			break;
		case KEY_ENTER_TRG_NUMBER :
			Menu_Exit(true);
			log_d("slect enter ");
			break;
		case KEY_DOWN_TRG_NUMBER :
			log_d("slect down ");
			break;
		default :
			break;
		}
	}
}



