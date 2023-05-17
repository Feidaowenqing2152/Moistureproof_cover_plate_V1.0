/*
 * hmi_illumi.c
 *
 *  Created on: 2023年2月13日
 *      Author: 好
 */

#define LOG_TAG    "external/hmi_illumi"

#include "../himi/external/hmi_illumi.h"




struct set_ex_illumi_menu_list_pararm{                 //实时值
	int auto_exit_sets_page_to_main_time ;  //自动返回时间
    uint16_t exit_wait_timout_cnt ;
	external_para_def external_para ;
	ShownMenuDate Ex_Illumi_ShowCompensationDate_t ;
	ShownMenuDate Ex_Illumi_ShowRealTimeDate_t ;
	ShownMenuDate Ex_Illumi_ShowSetMinRefVauleDate ;
	ShownMenuDate Ex_Illumi_ShowSetMaxRefVauleDate ;
	ShownMenuDate Ex_Illumi_ShowSampleRateDate ;
};


static struct set_ex_illumi_menu_list_pararm set_ex_illumi_menu_list_pararm_t ;

/******************外界参数-光照传感器设置页面选择*********************************/
static void MenuDateShow_Init(void);
/* 设置地址复位初始化*/
static void Device_Addr_Reversion_Init(void);
/* 设置地址复位执行函数*/
static void Ex_Illumination_Setting_Dev_Transducer_Reset_Addr(void);
/* 设置菜单显示效果 */
static void Illumination_SetMenu(  MenuShow_t *ptShowInfo);
/********************************************** 切换页面 - 外界光照传感器选择设置页面  ***************************************************************/

/*********************** 切换页面 - 外界光照传感器温度校验补偿页面  *******************/
/* 外界光照传感器温度校验补偿菜单 */
static void Ex_Illumination_Compensation_Page_Load(void);
static void Ex_Illumination_Compensation_Page_Exit(void);
static void Ex_Illumination_Compensation_Page_Task(void);
/************* 输入参数- 外界光照传感器温度校验补偿页面  *******************/
static void Ex_Illumination_Device_Compensation_Input_Page_Load(void);
static void EX_Illumination_Device_Compensation_Input_Page_Exit(void);
static void Ex_Illumination_Device_Compensation_Input_Page_Task(void);
static void Hmi_External_Illumination_Compensation_Slcet_Input_Buttons_CB(key_Input_Number_Typedef key_number ,Key_Trg_Even key_state);
/********* 保存设置参数- 外界光照传感器温度校验补偿  ******************/
static void Ex_Illumination_Device_Set_Compensation_Enter_Page_Load(void);
static void EX_Illumination_Device_Set_Compensation_Enter_Page_Exit(void);
static void Ex_Illumination_Device_Set_Compensation_Page_Task(void);
/************* 切换页面 - 外界光照传感器光照基准值选择设置页面  **************************/
static void Ex_Illumination_Set_Ref_Value_Page_Load(void);
static void Ex_Illumination_Set_Ref_Value_Page_Exit(void);
static void Ex_Illumination_Set_Ref_Value_Page_Task(void);
/********** 切换页面 - 外界光照传感器光照最小光照强度选择设置页面  **********************/
static void Ex_Illumination_Min_Slect_Set_Page_Load(void);
static void Ex_Illumination_Min_Slect_Set_Page_Exit(void);
static void Ex_Illumination_Min_Slect_Set_Page_Task(void);
/************* 输入参数- 外界光照传感器最小光照强度页面  *******************/
static void Ex_Illumination_Min_Intput_Set_Page_Load(void);
static void Ex_Illumination_Min_Intput_Set_Page_Exit(void);
static void Ex_Illumination_Min_Intput_Set_Page_Task(void);
static void Illumination_Min_Slect_Input_Buttons_CB(key_Input_Number_Typedef key_number ,Key_Trg_Even key_state);
/********* 保存设置参数- 外界光照传感器最小光照强度页面 ******************/
static void Ex_Illumination_Min_Intput_Set_Enter_Page_Load(void);
static void Ex_Illumination_Min_Intput_Set_Enter_Page_Exit(void);
static void Ex_Illumination_Min_Intput_Set_Enter_Page_Task(void);
/************ 切换页面 - 外界光照传感器光照最大光照强度选择设置页面  ******/
static void Ex_Illumination_Max_Slect_Set_Page_Load(void);
static void Ex_Illumination_Max_Slect_Set_Page_Exit(void);
static void Ex_Illumination_Max_Slect_Set_Page_Task(void);
/************* 输入参数-  外界光照传感器光照最大光照强度值页面  *******************/
static void Ex_Illumination_Max_Intput_Set_Page_Load(void);
static void Ex_Illumination_Max_Intput_Set_Page_Exit(void);
static void Ex_Illumination_Max_Intput_Set_Page_Task(void);
static void Illumination_Max_Slect_Input_Buttons_CB(key_Input_Number_Typedef key_number ,Key_Trg_Even key_state);
/********* 保存设置参数- 外界光照传感器最大光照强度页面 ******************/
static void Ex_Illumination_Max_Intput_Set_Enter_Page_Load(void);
static void Ex_Illumination_Max_Intput_Set_Enter_Page_Exit(void);
static void Ex_Illumination_Max_Intput_Set_Enter_Page_Task(void);
/********* 切换页面 -外界光照传感器温度采集速率页面  *********************/
static void Ex_Illumination_Acquisition_Rate_Page_Load(void);
static void Ex_Illumination_Acquisition_Rate_Page_Exit(void);
static void Ex_Illumination_Acquisition_Rate_Page_Task(void);
/************* 输入参数- 外界光照传感器温湿度采样速率页面  *******************/
static void Ex_Illumination_Sample_Rate_Input_Page_Load(void);
static void EX_Illumination_Sample_Rate_Input_Page_Exit(void);
static void Ex_Illumination_Sample_Rate_Input_Page_Task(void);
static void Hmi_External_Illumination_Sample_Rate_Input_Buttons_CB(key_Input_Number_Typedef key_number ,Key_Trg_Even key_state);
/********* 保存设置参数- 外界光照传感器温度采样速率  ******************/
static void Ex_Illumination_Sample_Rate_Enter_Page_Load(void);
static void Ex_Illumination_Sample_Rate_Enter_Page_Exit(void);
static void Ex_Illumination_Sample_Rate_Enter_Page_Task(void);
/************* 外界温度传感器公共回调函数  *******************/
static void Illumination_Slcet_Set_Buttons_CB( key_Input_Number_Typedef key_number , Key_Trg_Even key_state);
static void Illumination_Slcet_Enter_Window_Buttons_CB( key_Input_Number_Typedef key_number , Key_Trg_Even key_state);



/******************外界参数-光照传感器设置页面选择*********************************/

/* 外界光照传感器设置菜单*/
static MenuList_t External_Illumination_Set_Menu_Table[] =
{
	{"设备地址复归", NULL, Device_Addr_Reversion_Page_Load, Device_Addr_Reversion_Page_Exit, Device_Addr_Reversion_Page_Task, NULL},

    {"光照强度校验补偿", NULL, Ex_Illumination_Compensation_Page_Load, Ex_Illumination_Compensation_Page_Exit, Ex_Illumination_Compensation_Page_Task, NULL},

    {"光照基准值设置", NULL, Ex_Illumination_Set_Ref_Value_Page_Load, Ex_Illumination_Set_Ref_Value_Page_Exit, Ex_Illumination_Set_Ref_Value_Page_Task, NULL},

    {"光照强度采集速率", NULL,  Ex_Illumination_Acquisition_Rate_Page_Load, Ex_Illumination_Acquisition_Rate_Page_Exit, Ex_Illumination_Acquisition_Rate_Page_Task, NULL},

    {"返回上级菜单", NULL,  Return_Previous_Menu_Page_Load, NULL, NULL, NULL},

    {"返回主页面", NULL,  Back_Main_Page_Load,   NULL,   NULL, NULL},
};


static void MenuDateShow_Init(void){
	system_para_def system_para_t ;
	set_ex_illumi_menu_list_pararm_t.Ex_Illumi_ShowCompensationDate_t = show_Illumi_compensation_date ;   //显示湿度补偿值
	set_ex_illumi_menu_list_pararm_t.Ex_Illumi_ShowRealTimeDate_t = show_Illumi_real_time_date ;         //显示实时光照强度值
	set_ex_illumi_menu_list_pararm_t.Ex_Illumi_ShowSetMinRefVauleDate = show_Illumi_intput_min_date ;    //显示设置最小光照值
	set_ex_illumi_menu_list_pararm_t.Ex_Illumi_ShowSetMaxRefVauleDate = show_Illumi_intput_max_date ;    //显示设置最小光照值
	set_ex_illumi_menu_list_pararm_t.Ex_Illumi_ShowSampleRateDate = show_Illumi_sample_rate_date ;		 //显示光照采集速率

	read_saveenv_cjson_system_parameter(&system_para_t);
	set_ex_illumi_menu_list_pararm_t.auto_exit_sets_page_to_main_time = system_para_t.AutoExitSetsPageTime;
}

/* 设置地址复位初始化*/
static void Device_Addr_Reversion_Init(void){
	struct dev_address_reset_par ex_illumination_address_reset_par ;
	ex_illumination_address_reset_par.setting_sleet_type_flag = 0 ;
	ex_illumination_address_reset_par.setting_cursor_dev_var_addr = EXTERNAL_ILLUMINATION_DEV_ADDERSS_RESET_CURSOR_ADDERSS ;
	ex_illumination_address_reset_par.setting_dev_reset_page = PAGE_EXTERNAL_ILLUMINATION_DEV_ADDR_SETTING_NUMBER ;
	ex_illumination_address_reset_par.auto_exit_setting_page_time = set_ex_illumi_menu_list_pararm_t.auto_exit_sets_page_to_main_time ;
	ex_illumination_address_reset_par.dev_addr_reset_wait_var_addr = EXTERNAL_ILLUMINATION_DEV_ADDR_RESET_WAIT_WINDOW_VAR_ADDERSS ;
	ex_illumination_address_reset_par.dev_addr_reset_success_var_addr = EXTERNAL_ILLUMINATION_DEV_ADDR_RESET_SUCCESS_WINDOW_VAR_ADDERSS ;
	ex_illumination_address_reset_par.dev_addr_reset_error_var_addr = EXTERNAL_ILLUMINATION_DEV_ADDR_RESET_ERROR_WINDOW_VAR_ADDERSS ;
	/* 设置设备地址确定执行函数 */
	ex_illumination_address_reset_par.dev_reset_execute_function_cb = Ex_Illumination_Setting_Dev_Transducer_Reset_Addr;
	Device_Addr_Reversion_Load_Init( &ex_illumination_address_reset_par);
}
/* 设置地址复位执行函数*/
static void Ex_Illumination_Setting_Dev_Transducer_Reset_Addr(void){
	Setting_Dev_Transducer_Reset_Addr( illumination_transducer )  ;
}


/* 设置菜单显示效果 */
static void Illumination_SetMenu(  MenuShow_t *ptShowInfo){
	show_refresh_time();
	show_eth_connect_state();
}

/********************************************** 切换页面 - 外界光照传感器选择设置页面  ***************************************************************/
void External_Illum_Setting_Page_Load(void){

	log_d("External_Illum_Setting_Page_Load ");
	type_slect_move_cursor slect_move_cursor;

	slect_move_cursor.dw_cursor_adderss = EXTERNAL_ILLUMINATION_DEV_SETTING_CURSOR_ADDERSS ;
	slect_move_cursor.max_slect_move = 5 ;
	slect_move_cursor.min_slect_move = 0 ;
	slect_move_cursor.move_slect_step = 1 ;
	slect_move_cursor.now_slect_move = 0 ;
	slect_cursor_move_init(&slect_move_cursor);  						//光标位置初始化
	dw_show_switching_pages(PAGE_EXTERNAL_ILLUMINATION_SETTING_NUMBER); 	//切换页面
	slect_cursor_move(cursor_default_mode,cursor_null);  				//初始化选择设置显示光标
	Buttons_Register(KEY_UP_TRG_NUMBER,Illumination_Slcet_Set_Buttons_CB);
	Buttons_Register(KEY_ENTER_TRG_NUMBER,Illumination_Slcet_Set_Buttons_CB);
	Buttons_Register(KEY_DOWN_TRG_NUMBER,Illumination_Slcet_Set_Buttons_CB);
	MenuDateShow_Init();
	Device_Addr_Reversion_Init();
	//clear_time_cnt(AUTO_EXIT_SETS_PAGE_TO_MAIN_PAGE_TIMER_NUMBER);
	Menu_Bind(External_Illumination_Set_Menu_Table, GET_MENU_NUM(External_Illumination_Set_Menu_Table), Illumination_SetMenu);
}

void External_Illum_Setting_Page_Exit(void){
	//clear_time_cnt(AUTO_EXIT_SETS_PAGE_TO_MAIN_PAGE_TIMER_NUMBER);
}

void External_Illum_Setting_Page_Task(void){
	if(check_time_arrive(AUTO_EXIT_SETS_PAGE_TO_MAIN_PAGE_TIMER_NUMBER,set_ex_illumi_menu_list_pararm_t.auto_exit_sets_page_to_main_time*1000)){
		Back_Main_Page_Load();
		//clear_time_cnt(AUTO_EXIT_SETS_PAGE_TO_MAIN_PAGE_TIMER_NUMBER);
	}
}





/********************************************** 切换页面 - 外界光照传感器温度校验补偿页面  ***************************************************************/
/* 外界光照传感器温度校验补偿菜单 */
static MenuList_t External_Illumination_Set_Compensation_Menu_Table[] =
{
	{"参数输入框", NULL, Ex_Illumination_Device_Compensation_Input_Page_Load, EX_Illumination_Device_Compensation_Input_Page_Exit, Ex_Illumination_Device_Compensation_Input_Page_Task, NULL},

    {"保存设置参数", NULL, Ex_Illumination_Device_Set_Compensation_Enter_Page_Load, EX_Illumination_Device_Set_Compensation_Enter_Page_Exit, Ex_Illumination_Device_Set_Compensation_Page_Task, NULL},

    {"返回上级菜单", NULL,  Return_Previous_Menu_Page_Load, NULL, NULL, NULL},

    {"返回主页面", NULL,  Back_Main_Page_Load,   NULL,   NULL, NULL},
};

static void Ex_Illumination_Compensation_Page_Load(void){

	type_slect_move_cursor slect_move_cursor;

	slect_move_cursor.dw_cursor_adderss = EXTERNAL_ILLUMINATION_COMPENSATION_INPUT_SELECT_CURSOR_ADDERSS ;
	slect_move_cursor.max_slect_move = 3 ;
	slect_move_cursor.min_slect_move = 0 ;
	slect_move_cursor.move_slect_step = 1 ;
	slect_move_cursor.now_slect_move = 0 ;
	slect_cursor_move_init(&slect_move_cursor);  			//光标输入位置初始化
	slect_cursor_move(cursor_refresh_mode,cursor_null);  	//关闭输入位置光标
	slect_move_cursor.dw_cursor_adderss = EXTERNAL_ILLUMINATION_COMPENSATION_SELECT_CURSOR_ADDERSS ;
	slect_move_cursor.max_slect_move = 3 ;
	slect_move_cursor.min_slect_move = 0 ;
	slect_move_cursor.move_slect_step = 1 ;
	slect_move_cursor.now_slect_move = 0 ;
	slect_cursor_move_init(&slect_move_cursor); 		 			//光标位置初始化
	slect_cursor_move(cursor_default_mode,cursor_null);  			//初始化选择设置光标
	read_saveenv_cjson_external_parameter(&set_ex_illumi_menu_list_pararm_t.external_para);
	set_ex_illumi_menu_list_pararm_t.Ex_Illumi_ShowCompensationDate_t(set_ex_illumi_menu_list_pararm_t.external_para.ExternalIlluminationCompensationDate);  //显示温度补偿值
	dw_show_switching_pages(PAGE_EXTERNAL_ILLUMINATION_COMPENSATION_SETTING_NUMBER); //切换页面
	Buttons_Register(KEY_UP_TRG_NUMBER,Illumination_Slcet_Set_Buttons_CB);
	Buttons_Register(KEY_ENTER_TRG_NUMBER,Illumination_Slcet_Set_Buttons_CB);
	Buttons_Register(KEY_DOWN_TRG_NUMBER,Illumination_Slcet_Set_Buttons_CB);
	Menu_Bind(External_Illumination_Set_Compensation_Menu_Table, GET_MENU_NUM(External_Illumination_Set_Compensation_Menu_Table), Illumination_SetMenu);
}
static void Ex_Illumination_Compensation_Page_Exit(void){
	//clear_time_cnt(AUTO_EXIT_SETS_PAGE_TO_MAIN_PAGE_TIMER_NUMBER);
}
static void Ex_Illumination_Compensation_Page_Task(void){
	if(check_time_arrive(AUTO_EXIT_SETS_PAGE_TO_MAIN_PAGE_TIMER_NUMBER,set_ex_illumi_menu_list_pararm_t.auto_exit_sets_page_to_main_time*1000)){
		Back_Main_Page_Load();
		//clear_time_cnt(AUTO_EXIT_SETS_PAGE_TO_MAIN_PAGE_TIMER_NUMBER);
	}
}
/************* 输入参数- 外界光照传感器温度校验补偿页面  *******************/
static void Ex_Illumination_Device_Compensation_Input_Page_Load(void){
	type_slect_move_cursor slect_move_cursor;
	slect_move_cursor.dw_cursor_adderss = EXTERNAL_ILLUMINATION_COMPENSATION_SELECT_CURSOR_ADDERSS ;
	slect_move_cursor.max_slect_move = 3 ;
	slect_move_cursor.min_slect_move = 0 ;
	slect_move_cursor.move_slect_step = 1 ;
	slect_move_cursor.now_slect_move = 0 ;
	slect_cursor_move_init(&slect_move_cursor);  //光标位置初始化
	slect_cursor_move(cursor_refresh_mode,cursor_null);  //关闭光标
	slect_move_cursor.dw_cursor_adderss = EXTERNAL_ILLUMINATION_COMPENSATION_INPUT_SELECT_CURSOR_ADDERSS ;
	slect_move_cursor.max_slect_move = 3 ;
	slect_move_cursor.min_slect_move = 0 ;
	slect_move_cursor.move_slect_step = 1 ;
	slect_move_cursor.now_slect_move = 0 ;
	slect_cursor_move_init(&slect_move_cursor);  //光标位置初始化
	slect_cursor_move(cursor_default_mode,cursor_null);  //显示初始化光标位置
	Buttons_Register(KEY_UP_TRG_NUMBER,Hmi_External_Illumination_Compensation_Slcet_Input_Buttons_CB);
	Buttons_Register(KEY_ENTER_TRG_NUMBER,Hmi_External_Illumination_Compensation_Slcet_Input_Buttons_CB);
	Buttons_Register(KEY_DOWN_TRG_NUMBER,Hmi_External_Illumination_Compensation_Slcet_Input_Buttons_CB);
}

static void EX_Illumination_Device_Compensation_Input_Page_Exit(void){
	//clear_time_cnt(AUTO_EXIT_SETS_PAGE_TO_MAIN_PAGE_TIMER_NUMBER);
}

static void Ex_Illumination_Device_Compensation_Input_Page_Task(void){
	if(check_time_arrive(AUTO_EXIT_SETS_PAGE_TO_MAIN_PAGE_TIMER_NUMBER,set_ex_illumi_menu_list_pararm_t.auto_exit_sets_page_to_main_time*1000)){
		Back_Main_Page_Load();
		//clear_time_cnt(AUTO_EXIT_SETS_PAGE_TO_MAIN_PAGE_TIMER_NUMBER);
	}
}


static void Hmi_External_Illumination_Compensation_Slcet_Input_Buttons_CB(key_Input_Number_Typedef key_number ,Key_Trg_Even key_state){
	if(key_state == KEY_CLICK_ACTION){
		//clear_time_cnt(AUTO_EXIT_SETS_PAGE_TO_MAIN_PAGE_TIMER_NUMBER);
		set_ex_illumi_menu_list_pararm_t.external_para.ExternalIlluminationCompensationDate=user_parameter_adjustment(set_ex_illumi_menu_list_pararm_t.external_para.ExternalIlluminationCompensationDate,1,3,key_number,set_ex_illumi_menu_list_pararm_t.Ex_Illumi_ShowCompensationDate_t);
	}
}

/********* 保存设置参数- 外界光照传感器温度校验补偿  ******************/
static void Ex_Illumination_Device_Set_Compensation_Enter_Page_Load(void){
	int ret = -1 ;
	type_slect_move_cursor slect_move_cursor;
	slect_move_cursor.dw_cursor_adderss = EXTERNAL_ILLUMINATION_COMPENSATION_SELECT_CURSOR_ADDERSS ;
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
	dw_input_parameter_hint_window( 1 ,EXTERNAL_ILLUMINATION_COMPENSATION_WAIT_WINDOW_VAR_ADDERSS,EXTERNAL_ILLUMINATION_COMPENSATION_SUCCESS_WINDOW_VAR_ADDERSS,EXTERNAL_ILLUMINATION_COMPENSATION_ERROR_WINDOW_VAR_ADDERSS);
	ret = externalparaPoint_amend_config("ExternalIlluminationCompensationDate",set_ex_illumi_menu_list_pararm_t.external_para.ExternalIlluminationCompensationDate);
	if( !ret){
		 //显示成功窗口
		dw_input_parameter_hint_window(2,EXTERNAL_ILLUMINATION_COMPENSATION_WAIT_WINDOW_VAR_ADDERSS,EXTERNAL_ILLUMINATION_COMPENSATION_SUCCESS_WINDOW_VAR_ADDERSS,EXTERNAL_ILLUMINATION_COMPENSATION_ERROR_WINDOW_VAR_ADDERSS);
	}else{
		//显示错误窗口
		dw_input_parameter_hint_window( 3 ,EXTERNAL_ILLUMINATION_COMPENSATION_WAIT_WINDOW_VAR_ADDERSS,EXTERNAL_ILLUMINATION_COMPENSATION_SUCCESS_WINDOW_VAR_ADDERSS,EXTERNAL_ILLUMINATION_COMPENSATION_ERROR_WINDOW_VAR_ADDERSS);
	}
	Buttons_Register(KEY_ENTER_TRG_NUMBER,Illumination_Slcet_Enter_Window_Buttons_CB);
}

static void EX_Illumination_Device_Set_Compensation_Enter_Page_Exit(void){
	//清除窗口
	dw_input_parameter_hint_window( 0 ,EXTERNAL_ILLUMINATION_COMPENSATION_WAIT_WINDOW_VAR_ADDERSS,EXTERNAL_ILLUMINATION_COMPENSATION_SUCCESS_WINDOW_VAR_ADDERSS,EXTERNAL_ILLUMINATION_COMPENSATION_ERROR_WINDOW_VAR_ADDERSS);
	//clear_time_cnt(AUTO_EXIT_SETS_PAGE_TO_MAIN_PAGE_TIMER_NUMBER);
}

static void Ex_Illumination_Device_Set_Compensation_Page_Task(void){
	if(check_time_arrive(AUTO_EXIT_SETS_PAGE_TO_MAIN_PAGE_TIMER_NUMBER,set_ex_illumi_menu_list_pararm_t.auto_exit_sets_page_to_main_time*1000)){
		Back_Main_Page_Load();
		//clear_time_cnt(AUTO_EXIT_SETS_PAGE_TO_MAIN_PAGE_TIMER_NUMBER);
	}
}

/********************************************** 切换页面 - 外界光照传感器光照基准值选择设置页面  ***************************************************************/
/* 外界光照传感器光照基准值选择设置菜单 */
static MenuList_t External_Illumination_Set_Reference_Value_Menu_Table[] =
{
	{"外界最小光照强度设置", NULL, Ex_Illumination_Min_Slect_Set_Page_Load, Ex_Illumination_Min_Slect_Set_Page_Exit, Ex_Illumination_Min_Slect_Set_Page_Task, NULL},

    {"外界最大光照强度设置", NULL, Ex_Illumination_Max_Slect_Set_Page_Load, Ex_Illumination_Max_Slect_Set_Page_Exit, Ex_Illumination_Max_Slect_Set_Page_Task, NULL},

    {"返回上级菜单", NULL,  Return_Previous_Menu_Page_Load, NULL, NULL, NULL},

    {"返回主页面", NULL,  Back_Main_Page_Load,   NULL,   NULL, NULL},
};

static void Ex_Illumination_Set_Ref_Value_Page_Load(void){
	type_slect_move_cursor slect_move_cursor;

	slect_move_cursor.dw_cursor_adderss = EXTERNAL_ILLUMINATION_REF_SETTING_CURSOR_ADDERSS ;
	slect_move_cursor.max_slect_move = 3 ;
	slect_move_cursor.min_slect_move = 0 ;
	slect_move_cursor.move_slect_step = 1 ;
	slect_move_cursor.now_slect_move = 0 ;
	slect_cursor_move_init(&slect_move_cursor); 		 			//光标位置初始化
	slect_cursor_move(cursor_default_mode,cursor_null);  			//初始化选择设置光标
	dw_show_switching_pages(PAGE_EXTERNAL_ILLUMINATION_VEF_VALUE_SETTING_NUMBER); //切换页面
	Buttons_Register(KEY_UP_TRG_NUMBER,Illumination_Slcet_Set_Buttons_CB);
	Buttons_Register(KEY_ENTER_TRG_NUMBER,Illumination_Slcet_Set_Buttons_CB);
	Buttons_Register(KEY_DOWN_TRG_NUMBER,Illumination_Slcet_Set_Buttons_CB);
	Menu_Bind(External_Illumination_Set_Reference_Value_Menu_Table, GET_MENU_NUM(External_Illumination_Set_Reference_Value_Menu_Table), Illumination_SetMenu);
}

static void Ex_Illumination_Set_Ref_Value_Page_Exit(void){
	//clear_time_cnt(AUTO_EXIT_SETS_PAGE_TO_MAIN_PAGE_TIMER_NUMBER);
}

static void Ex_Illumination_Set_Ref_Value_Page_Task(void){
	if(check_time_arrive(AUTO_EXIT_SETS_PAGE_TO_MAIN_PAGE_TIMER_NUMBER,set_ex_illumi_menu_list_pararm_t.auto_exit_sets_page_to_main_time*1000)){
			Back_Main_Page_Load();
		}
}


/********************************************** 切换页面 - 外界光照传感器光照最小光照强度选择设置页面  ***************************************************************/
/* 外界光照传感器光照最小光照强度选择设置菜单 */
static MenuList_t External_Illumination_Input_Min_Ref_Value_Menu_Table[] =
{
	{"参数输入框", NULL, Ex_Illumination_Min_Intput_Set_Page_Load, Ex_Illumination_Min_Intput_Set_Page_Exit, Ex_Illumination_Min_Intput_Set_Page_Task, NULL},

    {"保存设置参数", NULL, Ex_Illumination_Min_Intput_Set_Enter_Page_Load, Ex_Illumination_Min_Intput_Set_Enter_Page_Exit, Ex_Illumination_Min_Intput_Set_Enter_Page_Task, NULL},

    {"返回上级菜单", NULL,  Return_Previous_Menu_Page_Load, NULL, NULL, NULL},

    {"返回主页面", NULL,  Back_Main_Page_Load,   NULL,   NULL, NULL},
};
static void Ex_Illumination_Min_Slect_Set_Page_Load(void){
	type_slect_move_cursor slect_move_cursor;

	slect_move_cursor.dw_cursor_adderss = EXTERNAL_ILLUMINATION_REF_MIN_INPUT_SELECT_CURSOR_ADDERSS ;
	slect_move_cursor.max_slect_move = 6 ;
	slect_move_cursor.min_slect_move = 0 ;
	slect_move_cursor.move_slect_step = 1 ;
	slect_move_cursor.now_slect_move = 0 ;
	slect_cursor_move_init(&slect_move_cursor);  		//光标位置初始化
	slect_cursor_move(cursor_refresh_mode,cursor_null);  //关闭光标
	slect_move_cursor.dw_cursor_adderss = EXTERNAL_ILLUMINATION_INTPUT_REF_MIN_SELECT_CURSOR_ADDERSS ;
	slect_move_cursor.max_slect_move = 3 ;
	slect_move_cursor.min_slect_move = 0 ;
	slect_move_cursor.move_slect_step = 1 ;
	slect_move_cursor.now_slect_move = 0 ;
	slect_cursor_move_init(&slect_move_cursor); 		 			//光标位置初始化
	slect_cursor_move(cursor_default_mode,cursor_null);  			//初始化选择设置光标
	read_saveenv_cjson_external_parameter(&set_ex_illumi_menu_list_pararm_t.external_para);
	set_ex_illumi_menu_list_pararm_t.Ex_Illumi_ShowSetMinRefVauleDate(set_ex_illumi_menu_list_pararm_t.external_para.SetMinIlluminationDate);
	dw_show_switching_pages(PAGE_EXTERNAL_ILLUMINATION_MIN_VALUE_SETTING_NUMBER); //切换页面
	Buttons_Register(KEY_UP_TRG_NUMBER,Illumination_Slcet_Set_Buttons_CB);
	Buttons_Register(KEY_ENTER_TRG_NUMBER,Illumination_Slcet_Set_Buttons_CB);
	Buttons_Register(KEY_DOWN_TRG_NUMBER,Illumination_Slcet_Set_Buttons_CB);
	Menu_Bind(External_Illumination_Input_Min_Ref_Value_Menu_Table, GET_MENU_NUM(External_Illumination_Input_Min_Ref_Value_Menu_Table), Illumination_SetMenu);
}
static void Ex_Illumination_Min_Slect_Set_Page_Exit(void){
	//clear_time_cnt(AUTO_EXIT_SETS_PAGE_TO_MAIN_PAGE_TIMER_NUMBER);
}
static void Ex_Illumination_Min_Slect_Set_Page_Task(void){
	static uint8_t illumi_cnt = 0 ;
	static uint32_t old_illumination_date = 0 ;
	illumi_cnt++ ;
	if( illumi_cnt > 100 ){
		illumi_cnt = 0 ;
		if(old_illumination_date != deal_transducer_masg_t.illumination_par_t.illumination_date){
			set_ex_illumi_menu_list_pararm_t.Ex_Illumi_ShowRealTimeDate_t(deal_transducer_masg_t.illumination_par_t.illumination_date);
			old_illumination_date = deal_transducer_masg_t.illumination_par_t.illumination_date;
		}

	}
	if(check_time_arrive(AUTO_EXIT_SETS_PAGE_TO_MAIN_PAGE_TIMER_NUMBER,set_ex_illumi_menu_list_pararm_t.auto_exit_sets_page_to_main_time*1000)){
		Back_Main_Page_Load();
	}
}

/************* 输入参数- 外界光照传感器最小光照强度页面  *******************/
static void Ex_Illumination_Min_Intput_Set_Page_Load(void){
	type_slect_move_cursor slect_move_cursor;

	slect_move_cursor.dw_cursor_adderss = EXTERNAL_ILLUMINATION_INTPUT_REF_MIN_SELECT_CURSOR_ADDERSS ;
	slect_move_cursor.max_slect_move = 3 ;
	slect_move_cursor.min_slect_move = 0 ;
	slect_move_cursor.move_slect_step = 1 ;
	slect_move_cursor.now_slect_move = 0 ;
	slect_cursor_move_init(&slect_move_cursor);  		//光标位置初始化
	slect_cursor_move(cursor_refresh_mode,cursor_null);  //关闭光标
	slect_move_cursor.dw_cursor_adderss = EXTERNAL_ILLUMINATION_REF_MIN_INPUT_SELECT_CURSOR_ADDERSS ;
	slect_move_cursor.max_slect_move = 5 ;
	slect_move_cursor.min_slect_move = 0 ;
	slect_move_cursor.move_slect_step = 1 ;
	slect_move_cursor.now_slect_move = 0 ;
	slect_cursor_move_init(&slect_move_cursor); 		 			//光标位置初始化
	slect_cursor_move(cursor_default_mode,cursor_null);  			//初始化选择设置光标
	Buttons_Register(KEY_UP_TRG_NUMBER,Illumination_Min_Slect_Input_Buttons_CB);
	Buttons_Register(KEY_ENTER_TRG_NUMBER,Illumination_Min_Slect_Input_Buttons_CB);
	Buttons_Register(KEY_DOWN_TRG_NUMBER,Illumination_Min_Slect_Input_Buttons_CB);
}
static void Ex_Illumination_Min_Intput_Set_Page_Exit(void){
	//clear_time_cnt(AUTO_EXIT_SETS_PAGE_TO_MAIN_PAGE_TIMER_NUMBER);
}
static void Ex_Illumination_Min_Intput_Set_Page_Task(void){
	static uint8_t illumi_cnt = 0 ;
	static uint32_t old_illumination_date = 0 ;
	illumi_cnt++ ;
	if( illumi_cnt > 100 ){
		illumi_cnt = 0 ;
		if(old_illumination_date != deal_transducer_masg_t.illumination_par_t.illumination_date){
			set_ex_illumi_menu_list_pararm_t.Ex_Illumi_ShowRealTimeDate_t(deal_transducer_masg_t.illumination_par_t.illumination_date);
			old_illumination_date = deal_transducer_masg_t.illumination_par_t.illumination_date;
		}

	}
	if(check_time_arrive(AUTO_EXIT_SETS_PAGE_TO_MAIN_PAGE_TIMER_NUMBER,set_ex_illumi_menu_list_pararm_t.auto_exit_sets_page_to_main_time*1000)){
			Back_Main_Page_Load();
		}
}
static void Illumination_Min_Slect_Input_Buttons_CB(key_Input_Number_Typedef key_number ,Key_Trg_Even key_state){
	if(key_state == KEY_CLICK_ACTION){
		//clear_time_cnt(AUTO_EXIT_SETS_PAGE_TO_MAIN_PAGE_TIMER_NUMBER);
		set_ex_illumi_menu_list_pararm_t.external_para.SetMinIlluminationDate=user_parameter_adjustment(set_ex_illumi_menu_list_pararm_t.external_para.SetMinIlluminationDate,false,6,key_number,set_ex_illumi_menu_list_pararm_t.Ex_Illumi_ShowSetMinRefVauleDate);
	}
}
/********* 保存设置参数- 外界光照传感器最小光照强度页面 ******************/
static void Ex_Illumination_Min_Intput_Set_Enter_Page_Load(void){
	int ret = -1 ;
	type_slect_move_cursor slect_move_cursor;
	slect_move_cursor.dw_cursor_adderss = EXTERNAL_ILLUMINATION_INTPUT_REF_MIN_SELECT_CURSOR_ADDERSS ;
	slect_move_cursor.max_slect_move = 5 ;
	slect_move_cursor.min_slect_move = 0 ;
	slect_move_cursor.move_slect_step = 1 ;
	slect_move_cursor.now_slect_move = 0 ;
	slect_cursor_move_init(&slect_move_cursor);  //光标位置初始化
	slect_cursor_move(cursor_refresh_mode,cursor_null);  //关闭光标
	Buttons_UnRegister(KEY_UP_TRG_NUMBER);
	Buttons_UnRegister(KEY_ENTER_TRG_NUMBER);
	Buttons_UnRegister(KEY_DOWN_TRG_NUMBER);
	//显示等待窗口
	dw_input_parameter_hint_window( 1 ,EXTERNAL_ILLUMINATION_INTPUT_REF_MIN_WAIT_WINDOW_VAR_ADDERSS,EXTERNAL_ILLUMINATION_INTPUT_REF_MIN_SUCCESS_WINDOW_VAR_ADDERSS,EXTERNAL_ILLUMINATION_INTPUT_REF_MIN_ERROR_WINDOW_VAR_ADDERSS);
	ret = externalparaPoint_amend_config("SetMinIlluminationDate",set_ex_illumi_menu_list_pararm_t.external_para.SetMinIlluminationDate);
	if( !ret){
		 //显示成功窗口
		dw_input_parameter_hint_window(2,EXTERNAL_ILLUMINATION_INTPUT_REF_MIN_WAIT_WINDOW_VAR_ADDERSS,EXTERNAL_ILLUMINATION_INTPUT_REF_MIN_SUCCESS_WINDOW_VAR_ADDERSS,EXTERNAL_ILLUMINATION_INTPUT_REF_MIN_ERROR_WINDOW_VAR_ADDERSS);
	}else{
		//显示错误窗口
		dw_input_parameter_hint_window( 3 ,EXTERNAL_ILLUMINATION_INTPUT_REF_MIN_WAIT_WINDOW_VAR_ADDERSS,EXTERNAL_ILLUMINATION_INTPUT_REF_MIN_SUCCESS_WINDOW_VAR_ADDERSS,EXTERNAL_ILLUMINATION_INTPUT_REF_MIN_ERROR_WINDOW_VAR_ADDERSS);
	}
	Buttons_Register(KEY_ENTER_TRG_NUMBER,Illumination_Slcet_Enter_Window_Buttons_CB);
}

static void Ex_Illumination_Min_Intput_Set_Enter_Page_Exit(void){
	//清除窗口
	dw_input_parameter_hint_window(0 ,EXTERNAL_ILLUMINATION_INTPUT_REF_MIN_WAIT_WINDOW_VAR_ADDERSS,EXTERNAL_ILLUMINATION_INTPUT_REF_MIN_SUCCESS_WINDOW_VAR_ADDERSS,EXTERNAL_ILLUMINATION_INTPUT_REF_MIN_ERROR_WINDOW_VAR_ADDERSS);
	//clear_time_cnt(AUTO_EXIT_SETS_PAGE_TO_MAIN_PAGE_TIMER_NUMBER);
}

static void Ex_Illumination_Min_Intput_Set_Enter_Page_Task(void){
	static uint8_t illumi_cnt = 0 ;
	static uint32_t old_illumination_date = 0 ;
	illumi_cnt++ ;
	if( illumi_cnt > 100 ){
		illumi_cnt = 0 ;
		if(old_illumination_date != deal_transducer_masg_t.illumination_par_t.illumination_date){
			set_ex_illumi_menu_list_pararm_t.Ex_Illumi_ShowRealTimeDate_t(deal_transducer_masg_t.illumination_par_t.illumination_date);
			old_illumination_date = deal_transducer_masg_t.illumination_par_t.illumination_date;
		}

	}
	if(check_time_arrive(AUTO_EXIT_SETS_PAGE_TO_MAIN_PAGE_TIMER_NUMBER,set_ex_illumi_menu_list_pararm_t.auto_exit_sets_page_to_main_time*1000)){
			Back_Main_Page_Load();
		}
}


/********************************************** 切换页面 - 外界光照传感器光照最大光照强度选择设置页面  ***************************************************************/
/* 外界光照传感器光照最大光照强度选择设置菜单 */
static MenuList_t External_Illumination_Input_Max_Ref_Value_Menu_Table[] =
{
	{"参数输入框", NULL, Ex_Illumination_Max_Intput_Set_Page_Load, Ex_Illumination_Max_Intput_Set_Page_Exit, Ex_Illumination_Max_Intput_Set_Page_Task, NULL},

    {"保存设置参数", NULL, Ex_Illumination_Max_Intput_Set_Enter_Page_Load, Ex_Illumination_Max_Intput_Set_Enter_Page_Exit, Ex_Illumination_Max_Intput_Set_Enter_Page_Task, NULL},

    {"返回上级菜单", NULL,  Return_Previous_Menu_Page_Load, NULL, NULL, NULL},

    {"返回主页面", NULL,  Back_Main_Page_Load,   NULL,   NULL, NULL},
};


static void Ex_Illumination_Max_Slect_Set_Page_Load(void){
	type_slect_move_cursor slect_move_cursor;

	slect_move_cursor.dw_cursor_adderss = EXTERNAL_ILLUMINATION_REF_MAX_INPUT_SELECT_CURSOR_ADDERSS ;
	slect_move_cursor.max_slect_move = 5 ;
	slect_move_cursor.min_slect_move = 0 ;
	slect_move_cursor.move_slect_step = 1 ;
	slect_move_cursor.now_slect_move = 0 ;
	slect_cursor_move_init(&slect_move_cursor);  		//光标位置初始化
	slect_cursor_move(cursor_refresh_mode,cursor_null);  //关闭光标
	slect_move_cursor.dw_cursor_adderss = EXTERNAL_ILLUMINATION_INTPUT_REF_MAX_SELECT_CURSOR_ADDERSS ;
	slect_move_cursor.max_slect_move = 3 ;
	slect_move_cursor.min_slect_move = 0 ;
	slect_move_cursor.move_slect_step = 1 ;
	slect_move_cursor.now_slect_move = 0 ;
	slect_cursor_move_init(&slect_move_cursor); 		 			//光标位置初始化
	slect_cursor_move(cursor_default_mode,cursor_null);  			//初始化选择设置光标
	read_saveenv_cjson_external_parameter(&set_ex_illumi_menu_list_pararm_t.external_para);
	set_ex_illumi_menu_list_pararm_t.Ex_Illumi_ShowSetMinRefVauleDate(set_ex_illumi_menu_list_pararm_t.external_para.SetMaxIlluminationDate);
	dw_show_switching_pages(PAGE_EXTERNAL_ILLUMINATION_MAX_VALUE_SETTING_NUMBER); //切换页面
	Buttons_Register(KEY_UP_TRG_NUMBER,Illumination_Slcet_Set_Buttons_CB);
	Buttons_Register(KEY_ENTER_TRG_NUMBER,Illumination_Slcet_Set_Buttons_CB);
	Buttons_Register(KEY_DOWN_TRG_NUMBER,Illumination_Slcet_Set_Buttons_CB);
	Menu_Bind(External_Illumination_Input_Max_Ref_Value_Menu_Table, GET_MENU_NUM(External_Illumination_Input_Max_Ref_Value_Menu_Table), Illumination_SetMenu);
}
static void Ex_Illumination_Max_Slect_Set_Page_Exit(void){
	//clear_time_cnt(AUTO_EXIT_SETS_PAGE_TO_MAIN_PAGE_TIMER_NUMBER);
}
static void Ex_Illumination_Max_Slect_Set_Page_Task(void){
	static uint8_t illumi_cnt = 0 ;
	static uint32_t old_illumination_date = 0 ;
	illumi_cnt++ ;
	if( illumi_cnt > 100 ){
		illumi_cnt = 0 ;
		if(old_illumination_date != deal_transducer_masg_t.illumination_par_t.illumination_date){
			set_ex_illumi_menu_list_pararm_t.Ex_Illumi_ShowRealTimeDate_t(deal_transducer_masg_t.illumination_par_t.illumination_date);
			old_illumination_date = deal_transducer_masg_t.illumination_par_t.illumination_date;
		}
	}
	if(check_time_arrive(AUTO_EXIT_SETS_PAGE_TO_MAIN_PAGE_TIMER_NUMBER,set_ex_illumi_menu_list_pararm_t.auto_exit_sets_page_to_main_time*1000)){
			Back_Main_Page_Load();
		}
}
/************* 输入参数-  外界光照传感器光照最大光照强度值页面  *******************/
static void Ex_Illumination_Max_Intput_Set_Page_Load(void){
	type_slect_move_cursor slect_move_cursor;

	slect_move_cursor.dw_cursor_adderss = EXTERNAL_ILLUMINATION_INTPUT_REF_MAX_SELECT_CURSOR_ADDERSS ;
	slect_move_cursor.max_slect_move = 3 ;
	slect_move_cursor.min_slect_move = 0 ;
	slect_move_cursor.move_slect_step = 1 ;
	slect_move_cursor.now_slect_move = 0 ;
	slect_cursor_move_init(&slect_move_cursor);  		//光标位置初始化
	slect_cursor_move(cursor_refresh_mode,cursor_null);  //关闭光标
	slect_move_cursor.dw_cursor_adderss = EXTERNAL_ILLUMINATION_REF_MAX_INPUT_SELECT_CURSOR_ADDERSS ;
	slect_move_cursor.max_slect_move = 5 ;
	slect_move_cursor.min_slect_move = 0 ;
	slect_move_cursor.move_slect_step = 1 ;
	slect_move_cursor.now_slect_move = 0 ;
	slect_cursor_move_init(&slect_move_cursor); 		 			//光标位置初始化
	slect_cursor_move(cursor_default_mode,cursor_null);  			//初始化选择设置光标
	Buttons_Register(KEY_UP_TRG_NUMBER,Illumination_Max_Slect_Input_Buttons_CB);
	Buttons_Register(KEY_ENTER_TRG_NUMBER,Illumination_Max_Slect_Input_Buttons_CB);
	Buttons_Register(KEY_DOWN_TRG_NUMBER,Illumination_Max_Slect_Input_Buttons_CB);
}
static void Ex_Illumination_Max_Intput_Set_Page_Exit(void){
	//clear_time_cnt(AUTO_EXIT_SETS_PAGE_TO_MAIN_PAGE_TIMER_NUMBER);
}
static void Ex_Illumination_Max_Intput_Set_Page_Task(void){
	static uint8_t illumi_cnt = 0 ;
	static uint32_t old_illumination_date = 0 ;
	illumi_cnt++ ;
	if( illumi_cnt > 100 ){
		illumi_cnt = 0 ;
		if(old_illumination_date != deal_transducer_masg_t.illumination_par_t.illumination_date){
			set_ex_illumi_menu_list_pararm_t.Ex_Illumi_ShowRealTimeDate_t(deal_transducer_masg_t.illumination_par_t.illumination_date);
			old_illumination_date = deal_transducer_masg_t.illumination_par_t.illumination_date;
		}
	}
	if(check_time_arrive(AUTO_EXIT_SETS_PAGE_TO_MAIN_PAGE_TIMER_NUMBER,set_ex_illumi_menu_list_pararm_t.auto_exit_sets_page_to_main_time*1000)){
		Back_Main_Page_Load();
	}
}

static void Illumination_Max_Slect_Input_Buttons_CB(key_Input_Number_Typedef key_number ,Key_Trg_Even key_state){
	if(key_state == KEY_CLICK_ACTION){
		//clear_time_cnt(AUTO_EXIT_SETS_PAGE_TO_MAIN_PAGE_TIMER_NUMBER);
		set_ex_illumi_menu_list_pararm_t.external_para.SetMaxIlluminationDate=user_parameter_adjustment(set_ex_illumi_menu_list_pararm_t.external_para.SetMaxIlluminationDate,false,6,key_number,set_ex_illumi_menu_list_pararm_t.Ex_Illumi_ShowSetMaxRefVauleDate);
	}
}



/********* 保存设置参数- 外界光照传感器最大光照强度页面 ******************/
static void Ex_Illumination_Max_Intput_Set_Enter_Page_Load(void){
	int ret = -1 ;
	type_slect_move_cursor slect_move_cursor;
	slect_move_cursor.dw_cursor_adderss = EXTERNAL_ILLUMINATION_INTPUT_REF_MAX_SELECT_CURSOR_ADDERSS ;
	slect_move_cursor.max_slect_move = 5 ;
	slect_move_cursor.min_slect_move = 0 ;
	slect_move_cursor.move_slect_step = 1 ;
	slect_move_cursor.now_slect_move = 0 ;
	slect_cursor_move_init(&slect_move_cursor);  //光标位置初始化
	slect_cursor_move(cursor_refresh_mode,cursor_null);  //关闭光标
	Buttons_UnRegister(KEY_UP_TRG_NUMBER);
	Buttons_UnRegister(KEY_ENTER_TRG_NUMBER);
	Buttons_UnRegister(KEY_DOWN_TRG_NUMBER);
	//显示等待窗口
	dw_input_parameter_hint_window( 1 ,EXTERNAL_ILLUMINATION_INTPUT_REF_MAX_WAIT_WINDOW_VAR_ADDERSS,EXTERNAL_ILLUMINATION_INTPUT_REF_MAX_SUCCESS_WINDOW_VAR_ADDERSS,EXTERNAL_ILLUMINATION_INTPUT_REF_MAX_ERROR_WINDOW_VAR_ADDERSS);
	ret = externalparaPoint_amend_config("SetMaxIlluminationDate",set_ex_illumi_menu_list_pararm_t.external_para.SetMaxIlluminationDate);
	if( !ret){
		 //显示成功窗口
		dw_input_parameter_hint_window(2 ,EXTERNAL_ILLUMINATION_INTPUT_REF_MAX_WAIT_WINDOW_VAR_ADDERSS,EXTERNAL_ILLUMINATION_INTPUT_REF_MAX_SUCCESS_WINDOW_VAR_ADDERSS,EXTERNAL_ILLUMINATION_INTPUT_REF_MAX_ERROR_WINDOW_VAR_ADDERSS);
	}else{
		//显示错误窗口
		dw_input_parameter_hint_window( 3 ,EXTERNAL_ILLUMINATION_INTPUT_REF_MAX_WAIT_WINDOW_VAR_ADDERSS,EXTERNAL_ILLUMINATION_INTPUT_REF_MAX_SUCCESS_WINDOW_VAR_ADDERSS,EXTERNAL_ILLUMINATION_INTPUT_REF_MAX_ERROR_WINDOW_VAR_ADDERSS);
	}
	Buttons_Register(KEY_ENTER_TRG_NUMBER,Illumination_Slcet_Enter_Window_Buttons_CB);
}

static void Ex_Illumination_Max_Intput_Set_Enter_Page_Exit(void){
	//清除窗口
	dw_input_parameter_hint_window(0 ,EXTERNAL_ILLUMINATION_INTPUT_REF_MAX_WAIT_WINDOW_VAR_ADDERSS,EXTERNAL_ILLUMINATION_INTPUT_REF_MAX_SUCCESS_WINDOW_VAR_ADDERSS,EXTERNAL_ILLUMINATION_INTPUT_REF_MAX_ERROR_WINDOW_VAR_ADDERSS);
	//clear_time_cnt(AUTO_EXIT_SETS_PAGE_TO_MAIN_PAGE_TIMER_NUMBER);
}

static void Ex_Illumination_Max_Intput_Set_Enter_Page_Task(void){
	static uint8_t illumi_cnt = 0 ;
	static uint32_t old_illumination_date = 0 ;
	illumi_cnt++ ;
	if( illumi_cnt > 100 ){
		illumi_cnt = 0 ;
		if(old_illumination_date != deal_transducer_masg_t.illumination_par_t.illumination_date){
			set_ex_illumi_menu_list_pararm_t.Ex_Illumi_ShowRealTimeDate_t(deal_transducer_masg_t.illumination_par_t.illumination_date);
			old_illumination_date = deal_transducer_masg_t.illumination_par_t.illumination_date;
		}
	}
	if(check_time_arrive(AUTO_EXIT_SETS_PAGE_TO_MAIN_PAGE_TIMER_NUMBER,set_ex_illumi_menu_list_pararm_t.auto_exit_sets_page_to_main_time*1000)){
		Back_Main_Page_Load();
	}
}


/********************************************** 切换页面 -外界光照传感器温度采集速率页面  ***************************************************************/
/* 外界光照传感器温度采集速率菜单 */
static MenuList_t External_Humidity_Sample_Rate_Menu_Table[] =
{
	{"参数输入框", NULL, Ex_Illumination_Sample_Rate_Input_Page_Load, EX_Illumination_Sample_Rate_Input_Page_Exit, Ex_Illumination_Sample_Rate_Input_Page_Task, NULL},

    {"保存设置参数", NULL, Ex_Illumination_Sample_Rate_Enter_Page_Load, Ex_Illumination_Sample_Rate_Enter_Page_Exit, Ex_Illumination_Sample_Rate_Enter_Page_Task, NULL},

    {"返回上级菜单", NULL,  Return_Previous_Menu_Page_Load, NULL, NULL, NULL},

    {"返回主页面", NULL,  Back_Main_Page_Load,   NULL,   NULL, NULL},
};

static void Ex_Illumination_Acquisition_Rate_Page_Load(void){
	type_slect_move_cursor slect_move_cursor;

	slect_move_cursor.dw_cursor_adderss = EXTERNAL_ILLUMINATION_SAMPLE_RATE_INPUT_SELECT_CURSOR_ADDERSS ;
	slect_move_cursor.max_slect_move = 1 ;
	slect_move_cursor.min_slect_move = 0 ;
	slect_move_cursor.move_slect_step = 1 ;
	slect_move_cursor.now_slect_move = 0 ;
	slect_cursor_move_init(&slect_move_cursor);  		//输入指示光标位置初始化
	slect_cursor_move(cursor_refresh_mode,cursor_null);  //关闭输入指示光标
	slect_move_cursor.dw_cursor_adderss = EXTERNAL_ILLUMINATION_SAMPLE_RATE_SELECT_CURSOR_ADDERSS ;
	slect_move_cursor.max_slect_move = 3 ;
	slect_move_cursor.min_slect_move = 0 ;
	slect_move_cursor.move_slect_step = 1 ;
	slect_move_cursor.now_slect_move = 0 ;
	slect_cursor_move_init(&slect_move_cursor); 		 			//光标位置初始化
	slect_cursor_move(cursor_default_mode,cursor_null);  			//初始化选择设置光标
	read_saveenv_cjson_external_parameter(&set_ex_illumi_menu_list_pararm_t.external_para);
	set_ex_illumi_menu_list_pararm_t.Ex_Illumi_ShowSampleRateDate(set_ex_illumi_menu_list_pararm_t.external_para.ExternalIlluminationSampleRate); //显示采样速率
	dw_show_switching_pages(PAGE_EXTERNAL_ILLUMINATION_SAMPLE_RATE_SETTING_NUMBER); //切换页面
	Buttons_Register(KEY_UP_TRG_NUMBER,Illumination_Slcet_Set_Buttons_CB);
	Buttons_Register(KEY_ENTER_TRG_NUMBER,Illumination_Slcet_Set_Buttons_CB);
	Buttons_Register(KEY_DOWN_TRG_NUMBER,Illumination_Slcet_Set_Buttons_CB);
	Menu_Bind(External_Humidity_Sample_Rate_Menu_Table, GET_MENU_NUM(External_Humidity_Sample_Rate_Menu_Table), Illumination_SetMenu);
}

static void Ex_Illumination_Acquisition_Rate_Page_Exit(void){
	//clear_time_cnt(AUTO_EXIT_SETS_PAGE_TO_MAIN_PAGE_TIMER_NUMBER);
}
static void Ex_Illumination_Acquisition_Rate_Page_Task(void){
	if(check_time_arrive(AUTO_EXIT_SETS_PAGE_TO_MAIN_PAGE_TIMER_NUMBER,set_ex_illumi_menu_list_pararm_t.auto_exit_sets_page_to_main_time*1000)){
		Back_Main_Page_Load();
		//clear_time_cnt(AUTO_EXIT_SETS_PAGE_TO_MAIN_PAGE_TIMER_NUMBER);
	}
}

/************* 输入参数- 外界光照传感器温湿度采样速率页面  *******************/
static void Ex_Illumination_Sample_Rate_Input_Page_Load(void){
	type_slect_move_cursor slect_move_cursor;

	slect_move_cursor.dw_cursor_adderss = EXTERNAL_ILLUMINATION_SAMPLE_RATE_SELECT_CURSOR_ADDERSS ;
	slect_move_cursor.max_slect_move = 3 ;
	slect_move_cursor.min_slect_move = 0 ;
	slect_move_cursor.move_slect_step = 1 ;
	slect_move_cursor.now_slect_move = 0 ;
	slect_cursor_move_init(&slect_move_cursor);  //光标位置初始化
	slect_cursor_move(cursor_refresh_mode,cursor_null);  //关闭选择设置光标
	slect_move_cursor.dw_cursor_adderss = EXTERNAL_ILLUMINATION_SAMPLE_RATE_INPUT_SELECT_CURSOR_ADDERSS ;
	slect_move_cursor.max_slect_move = 1 ;
	slect_move_cursor.min_slect_move = 0 ;
	slect_move_cursor.move_slect_step = 1 ;
	slect_move_cursor.now_slect_move = 0 ;
	slect_cursor_move_init(&slect_move_cursor);  //光标位置初始化
	slect_cursor_move(cursor_default_mode,cursor_null);  //显示初始化输入指示光标位置
	Buttons_Register(KEY_UP_TRG_NUMBER,Hmi_External_Illumination_Sample_Rate_Input_Buttons_CB);
	Buttons_Register(KEY_ENTER_TRG_NUMBER,Hmi_External_Illumination_Sample_Rate_Input_Buttons_CB);
	Buttons_Register(KEY_DOWN_TRG_NUMBER,Hmi_External_Illumination_Sample_Rate_Input_Buttons_CB);
}

static void EX_Illumination_Sample_Rate_Input_Page_Exit(void){
	//clear_time_cnt(AUTO_EXIT_SETS_PAGE_TO_MAIN_PAGE_TIMER_NUMBER);
}

static void Ex_Illumination_Sample_Rate_Input_Page_Task(void){
	if(check_time_arrive(AUTO_EXIT_SETS_PAGE_TO_MAIN_PAGE_TIMER_NUMBER,set_ex_illumi_menu_list_pararm_t.auto_exit_sets_page_to_main_time*1000)){
		Back_Main_Page_Load();
		//clear_time_cnt(AUTO_EXIT_SETS_PAGE_TO_MAIN_PAGE_TIMER_NUMBER);
	}
}

static void Hmi_External_Illumination_Sample_Rate_Input_Buttons_CB(key_Input_Number_Typedef key_number ,Key_Trg_Even key_state){
	if(key_state == KEY_CLICK_ACTION){
		//clear_time_cnt(AUTO_EXIT_SETS_PAGE_TO_MAIN_PAGE_TIMER_NUMBER);
		set_ex_illumi_menu_list_pararm_t.external_para.ExternalIlluminationSampleRate=user_parameter_adjustment(set_ex_illumi_menu_list_pararm_t.external_para.ExternalIlluminationSampleRate,0,2,key_number,set_ex_illumi_menu_list_pararm_t.Ex_Illumi_ShowSampleRateDate);
	}
}

/********* 保存设置参数- 外界光照传感器温度采样速率  ******************/
static void Ex_Illumination_Sample_Rate_Enter_Page_Load(void){
	int ret = -1 ;
	type_slect_move_cursor slect_move_cursor;
	slect_move_cursor.dw_cursor_adderss = EXTERNAL_ILLUMINATION_SAMPLE_RATE_SELECT_CURSOR_ADDERSS ;
	slect_move_cursor.max_slect_move = 1 ;
	slect_move_cursor.min_slect_move = 0 ;
	slect_move_cursor.move_slect_step = 1 ;
	slect_move_cursor.now_slect_move = 0 ;
	slect_cursor_move_init(&slect_move_cursor);  //光标位置初始化
	slect_cursor_move(cursor_refresh_mode,cursor_null);  //关闭光标
	Buttons_UnRegister(KEY_UP_TRG_NUMBER);
	Buttons_UnRegister(KEY_ENTER_TRG_NUMBER);
	Buttons_UnRegister(KEY_DOWN_TRG_NUMBER);
	//显示等待窗口
	dw_input_parameter_hint_window( 1 ,EXTERNAL_ILLUMINATION_SAMPLE_RATE_WAIT_WINDOW_VAR_ADDERSS,EXTERNAL_ILLUMINATION_SAMPLE_RATE_SUCCESS_WINDOW_VAR_ADDERSS,EXTERNAL_ILLUMINATION_SAMPLE_RATE_ERROR_WINDOW_VAR_ADDERSS);
	ret = externalparaPoint_amend_config("ExternalIlluminationSampleRate",set_ex_illumi_menu_list_pararm_t.external_para.ExternalIlluminationSampleRate);
	if( !ret){
		 //显示成功窗口
		dw_input_parameter_hint_window(2 ,EXTERNAL_ILLUMINATION_SAMPLE_RATE_WAIT_WINDOW_VAR_ADDERSS,EXTERNAL_ILLUMINATION_SAMPLE_RATE_SUCCESS_WINDOW_VAR_ADDERSS,EXTERNAL_ILLUMINATION_SAMPLE_RATE_ERROR_WINDOW_VAR_ADDERSS);
	}else{
		//显示错误窗口
		dw_input_parameter_hint_window( 3 ,EXTERNAL_ILLUMINATION_SAMPLE_RATE_WAIT_WINDOW_VAR_ADDERSS,EXTERNAL_ILLUMINATION_SAMPLE_RATE_SUCCESS_WINDOW_VAR_ADDERSS,EXTERNAL_ILLUMINATION_SAMPLE_RATE_ERROR_WINDOW_VAR_ADDERSS);
	}
	Buttons_Register(KEY_ENTER_TRG_NUMBER,Illumination_Slcet_Enter_Window_Buttons_CB);
}

static void Ex_Illumination_Sample_Rate_Enter_Page_Exit(void){
	//清除窗口
	dw_input_parameter_hint_window( 0 ,EXTERNAL_ILLUMINATION_SAMPLE_RATE_WAIT_WINDOW_VAR_ADDERSS,EXTERNAL_ILLUMINATION_SAMPLE_RATE_SUCCESS_WINDOW_VAR_ADDERSS,EXTERNAL_ILLUMINATION_SAMPLE_RATE_ERROR_WINDOW_VAR_ADDERSS);
	//clear_time_cnt(AUTO_EXIT_SETS_PAGE_TO_MAIN_PAGE_TIMER_NUMBER);
}

static void Ex_Illumination_Sample_Rate_Enter_Page_Task(void){
	if(check_time_arrive(AUTO_EXIT_SETS_PAGE_TO_MAIN_PAGE_TIMER_NUMBER,set_ex_illumi_menu_list_pararm_t.auto_exit_sets_page_to_main_time*1000)){
		Back_Main_Page_Load();
	}
}

/************* 外界温度传感器公共回调函数  *******************/
static void Illumination_Slcet_Set_Buttons_CB( key_Input_Number_Typedef key_number , Key_Trg_Even key_state){
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

static void Illumination_Slcet_Enter_Window_Buttons_CB( key_Input_Number_Typedef key_number , Key_Trg_Even key_state){
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



