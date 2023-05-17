/*
 * hmi_SysControl_Illumination.c
 *
 *  Created on: 2023年3月28日
 *      Author: 好
 */
#define LOG_TAG    "hmi_SysControl_Illumination"
#include "../himi/sys/hmi_SysControl/hmi_SysControl_Illumination.h"

/* 参数初始化*/
static void SystemMenuDateShow_Init(void);
/* 设置菜单显示效果 */
static void System_Control_Illumination_SetMenu(MenuShow_t *ptShowInfo);
/********************************************** 系统参数-系统控制-光照强度-光照强度使能设置页面  ***************************************************************/
static void System_Illumination_Enaable_Set_Page_Load(void);
static void System_Illumination_Enaable_Set_Page_Exit(void);
static void System_Illumination_Enaable_Set_Page_Task(void);
/************* 输入参数- 系统参数-系统控制-光照强度-光照强度 页面  *******************/
static void System_Control_Illumination_Enable_Input_Page_Load(void);
static void System_Control_Illumination_Enable_Input_Page_Exit(void);
static void System_Control_Illumination_Enable_Input_Page_Task(void);
static void System_Control_Illumination_Enable_Slcet_Input_Buttons_CB(key_Input_Number_Typedef key_number ,Key_Trg_Even key_state);
/********* 保存设置参数- 系统参数-系统控制-光照强度-光照强度使能  ******************/
static void System_Control_Illumination_Enable_Enter_Page_Load(void);
static void System_Control_Illumination_Enable_Enter_Page_Exit(void);
static void System_Control_Illumination_Enable_Enter_Page_Task(void);
/********************************************** 切换页面 - 系统参数-系统控制-光照强度-光照强度关闭设置值页面  ***************************************************************/
static void System_Illumination_Close_Value_Set_Page_Load(void);
static void System_Illumination_Close_Value_Set_Page_Exit(void);
static void System_Illumination_Close_Value_Set_Page_Task(void);
/************* 输入参数- 切换页面 - 系统参数-系统控制-光照强度-光照强度关闭设置值页面  *******************/
static void System_Illumination_Close_Value_Input_Page_Load(void);
static void System_Illumination_Close_Value_Input_Page_Exit(void);
static void System_Illumination_Close_Value_Input_Page_Task(void);
static void System_Illumination_Close_Value_Input_Buttons_CB(key_Input_Number_Typedef key_number ,Key_Trg_Even key_state);
/********* 保存设置参数- 切换页面 - 系统参数-系统控制-光照强度-光照强度关闭设置值  ******************/
static void System_Illumination_Close_Value_Enter_Page_Load(void);
static void System_Illumination_Close_Value_Enter_Page_Exit(void);
static void System_Illumination_Close_Value_Enter_Page_Task(void);
/********************************************** 切换页面 - 系统参数-系统控制-光照强度-光照强度打开设置值页面  ***************************************************************/
static void System_Illumination_Open_Value_Set_Page_Load(void);
static void System_Illumination_Open_Value_Set_Page_Exit(void);
static void System_Illumination_Open_Value_Set_Page_Task(void);
/************* 输入参数- 系统参数-系统控制-光照强度-光照强度打开设置值页面  *******************/
static void System_Illumination_Open_Value_Input_Page_Load(void);
static void System_Illumination_Open_Value_Input_Page_Exit(void);
static void System_Illumination_Open_Value_Input_Page_Task(void);
static void System_Illumination_Open_Value_Input_Buttons_CB(key_Input_Number_Typedef key_number ,Key_Trg_Even key_state);
/********* 保存设置参数- 系统参数-系统控制-光照强度-光照强度打开值  ******************/
static void System_Illumination_Open_Value_Enter_Page_Load(void);
static void System_Illumination_Open_Value_Enter_Page_Exit(void);
static void System_Illumination_Open_Value_Enter_Page_Task(void);
/************* 系统参数-系统时间公共回调函数  *******************/
static void System_Control_Illumination_Slcet_Set_Buttons_CB( key_Input_Number_Typedef key_number , Key_Trg_Even key_state);
static void System_Control_Illumination_Enter_Window_Buttons_CB( key_Input_Number_Typedef key_number , Key_Trg_Even key_state);

struct set_systemcontrol_illumination_menu_list_pararm{
	system_para_def system_para ;

	ShownMenuDate SY_ShowSysControlIlluminationEnableFun_t;

	ShownMenuDate SY_ShowSysControlIlluminationCloseFun_t;
	ShownMenuDate SY_ShowIntputSysControlIlluminationCloseFun_t;

	ShownMenuDate SY_ShowSysControlIlluminationOpenFun_t;
	ShownMenuDate SY_ShowIntputSysControlIlluminationOpenFun_t;

};


static struct set_systemcontrol_illumination_menu_list_pararm set_systemcontrol_illumination_pararm_t;


/******************系统参数-系统控制-光照强度设置页面选择*********************************/

/* 系统参数-系统控制-光照强度设置菜单*/
static MenuList_t System_Illumination_Set_Menu_Table[] =
{
    {"光照强度使能设置", NULL, System_Illumination_Enaable_Set_Page_Load, System_Illumination_Enaable_Set_Page_Exit, System_Illumination_Enaable_Set_Page_Task, NULL},

    {"光照强度关闭阈值", NULL, System_Illumination_Close_Value_Set_Page_Load, System_Illumination_Close_Value_Set_Page_Exit, System_Illumination_Close_Value_Set_Page_Task, NULL},

    {"光照强度打开阈值", NULL, System_Illumination_Open_Value_Set_Page_Load, System_Illumination_Open_Value_Set_Page_Exit, System_Illumination_Open_Value_Set_Page_Task, NULL},

    {"返回上级菜单", NULL,  Return_Previous_Menu_Page_Load, NULL, NULL, NULL},

    {"返回主页面", NULL,  Back_Main_Page_Load,   NULL,   NULL, NULL},
};

/* 参数初始化*/
static void SystemMenuDateShow_Init(void){

	set_systemcontrol_illumination_pararm_t.SY_ShowSysControlIlluminationEnableFun_t = show_system_control_illumination_disable_state_date ;

	set_systemcontrol_illumination_pararm_t.SY_ShowSysControlIlluminationCloseFun_t = show_system_present_control_illumination_clsoe_value_date ;
	set_systemcontrol_illumination_pararm_t.SY_ShowIntputSysControlIlluminationCloseFun_t = show_system_intput_control_illumination_clsoe_value_date ;

	set_systemcontrol_illumination_pararm_t.SY_ShowSysControlIlluminationOpenFun_t = show_system_present_control_illumination_open_value_date ;
	set_systemcontrol_illumination_pararm_t.SY_ShowIntputSysControlIlluminationOpenFun_t = show_system_intput_control_illumination_open_value_date ;

	read_saveenv_cjson_system_parameter(&set_systemcontrol_illumination_pararm_t.system_para);

}


/* 设置菜单显示效果 */
static void System_Control_Illumination_SetMenu(MenuShow_t *ptShowInfo){
	show_refresh_time();
	show_eth_connect_state();
}
/********************************************** 系统参数-系统控制-光照强度设置页面  ***************************************************************/
void System_Control_Illumination_Page_Load(void){

	log_d("System_Control_Illumination_Page_Load ");
	type_slect_move_cursor slect_move_cursor;

	slect_move_cursor.dw_cursor_adderss = SYSTEM_SYS_ILLUMINATION_CONTROL_SELECT_CURSOR_ADDERSS ;
	slect_move_cursor.max_slect_move = 4 ;
	slect_move_cursor.min_slect_move = 0 ;
	slect_move_cursor.move_slect_step = 1 ;
	slect_move_cursor.now_slect_move = 0 ;
	slect_cursor_move_init(&slect_move_cursor);  //光标位置初始化
	slect_cursor_move(cursor_default_mode,cursor_null);  //初始化选择设置光标

	dw_show_switching_pages(PAGE_SYSTEM_CONTROL_ILLUMINATION_SETTING_NUMBER); //切换页面
	Buttons_Register(KEY_UP_TRG_NUMBER,System_Control_Illumination_Slcet_Set_Buttons_CB);
	Buttons_Register(KEY_ENTER_TRG_NUMBER,System_Control_Illumination_Slcet_Set_Buttons_CB);
	Buttons_Register(KEY_DOWN_TRG_NUMBER,System_Control_Illumination_Slcet_Set_Buttons_CB);
	SystemMenuDateShow_Init();
	//clear_time_cnt(AUTO_EXIT_SETS_PAGE_TO_MAIN_PAGE_TIMER_NUMBER);
	Menu_Bind(System_Illumination_Set_Menu_Table, GET_MENU_NUM(System_Illumination_Set_Menu_Table), System_Control_Illumination_SetMenu);
}

void System_Control_Illumination_Page_Exit(void){
	//clear_time_cnt(AUTO_EXIT_SETS_PAGE_TO_MAIN_PAGE_TIMER_NUMBER);
}

void System_Control_Illumination_Page_Task(void){
	if(check_time_arrive(AUTO_EXIT_SETS_PAGE_TO_MAIN_PAGE_TIMER_NUMBER,set_systemcontrol_illumination_pararm_t.system_para.AutoExitSetsPageTime*1000)){
		Back_Main_Page_Load();
	}
}

/********************************************** 系统参数-系统控制-光照强度-光照强度使能设置页面  ***************************************************************/
/* 系统参数-系统控制-光照强度-光照强度设置菜单 */
static MenuList_t System_Control_Illumination_Enable_Set_Menu_Table[] =
{
	{"设置光照控制是否使能", NULL,System_Control_Illumination_Enable_Input_Page_Load, System_Control_Illumination_Enable_Input_Page_Exit, System_Control_Illumination_Enable_Input_Page_Task, NULL},

    {"保存设置参数", NULL, System_Control_Illumination_Enable_Enter_Page_Load, System_Control_Illumination_Enable_Enter_Page_Exit, System_Control_Illumination_Enable_Enter_Page_Task, NULL},

    {"返回上级菜单", NULL,  Return_Previous_Menu_Page_Load, NULL, NULL, NULL},

    {"返回主页面", NULL,  Back_Main_Page_Load,   NULL,   NULL, NULL},
};

static void System_Illumination_Enaable_Set_Page_Load(void){

	type_slect_move_cursor slect_move_cursor;
	log_d("System_Illumination_Enaable_Set_Page_Load");

	slect_move_cursor.dw_cursor_adderss = SYSTEM_SYS_ILLUMINATION_CONTROL_ENAABLE_INTPUT_SELECT_CURSOR_VAR_ADDERSS ;
	slect_move_cursor.max_slect_move = 0 ;
	slect_move_cursor.min_slect_move = 0 ;
	slect_move_cursor.move_slect_step = 1 ;
	slect_move_cursor.now_slect_move = 0 ;
	slect_cursor_move_init(&slect_move_cursor);  		//光标位置初始化
	slect_cursor_move(cursor_refresh_mode,cursor_null);  //关闭输入指示光标

	slect_move_cursor.dw_cursor_adderss = SYSTEM_SYS_ILLUMINATION_CONTROL_ENAABLE_SELECT_CURSOR_ADDERSS ;
	slect_move_cursor.max_slect_move = 3 ;
	slect_move_cursor.min_slect_move = 0 ;
	slect_move_cursor.move_slect_step = 1 ;
	slect_move_cursor.now_slect_move = 0 ;
	slect_cursor_move_init(&slect_move_cursor); 		 			//光标位置初始化
	slect_cursor_move(cursor_default_mode,cursor_null);  			//初始化选择设置光标
	set_systemcontrol_illumination_pararm_t.SY_ShowSysControlIlluminationEnableFun_t(!set_systemcontrol_illumination_pararm_t.system_para.SetIlluminationControlEnable);

	dw_show_switching_pages(PAGE_SYSTEM_CONTROL_ILLUMINATION_ENABLE_NUMBER); //切换页面

	Buttons_Register(KEY_UP_TRG_NUMBER,System_Control_Illumination_Slcet_Set_Buttons_CB);
	Buttons_Register(KEY_ENTER_TRG_NUMBER,System_Control_Illumination_Slcet_Set_Buttons_CB);
	Buttons_Register(KEY_DOWN_TRG_NUMBER,System_Control_Illumination_Slcet_Set_Buttons_CB);

	Menu_Bind(System_Control_Illumination_Enable_Set_Menu_Table, GET_MENU_NUM(System_Control_Illumination_Enable_Set_Menu_Table), System_Control_Illumination_SetMenu);
}
static void System_Illumination_Enaable_Set_Page_Exit(void){
	//clear_time_cnt(AUTO_EXIT_SETS_PAGE_TO_MAIN_PAGE_TIMER_NUMBER);
}
static void System_Illumination_Enaable_Set_Page_Task(void){
	if(check_time_arrive(AUTO_EXIT_SETS_PAGE_TO_MAIN_PAGE_TIMER_NUMBER,set_systemcontrol_illumination_pararm_t.system_para.AutoExitSetsPageTime*1000)){
		Back_Main_Page_Load();
	}
}
/************* 输入参数- 系统参数-系统控制-光照强度-光照强度 页面  *******************/
static void System_Control_Illumination_Enable_Input_Page_Load(void){
	type_slect_move_cursor slect_move_cursor;
	log_d("System_Control_Illumination_Enable_Input_Page_Load");
	slect_move_cursor.dw_cursor_adderss = SYSTEM_SYS_ILLUMINATION_CONTROL_ENAABLE_SELECT_CURSOR_ADDERSS ;
	slect_move_cursor.max_slect_move = 3 ;
	slect_move_cursor.min_slect_move = 0 ;
	slect_move_cursor.move_slect_step = 1 ;
	slect_move_cursor.now_slect_move = 0 ;
	slect_cursor_move_init(&slect_move_cursor);  		//光标位置初始化
	slect_cursor_move(cursor_refresh_mode,cursor_null);  //关闭输入指示光标

	slect_move_cursor.dw_cursor_adderss = SYSTEM_SYS_ILLUMINATION_CONTROL_ENAABLE_INTPUT_SELECT_CURSOR_VAR_ADDERSS ;
	slect_move_cursor.max_slect_move = 0 ;
	slect_move_cursor.min_slect_move = 0 ;
	slect_move_cursor.move_slect_step = 1 ;
	slect_move_cursor.now_slect_move = 0 ;
	slect_cursor_move_init(&slect_move_cursor); 		 			//光标位置初始化
	slect_cursor_move(cursor_default_mode,cursor_null);  			//初始化选择设置光标

	Buttons_Register(KEY_UP_TRG_NUMBER,System_Control_Illumination_Enable_Slcet_Input_Buttons_CB);
	Buttons_Register(KEY_ENTER_TRG_NUMBER,System_Control_Illumination_Enable_Slcet_Input_Buttons_CB);
	Buttons_Register(KEY_DOWN_TRG_NUMBER,System_Control_Illumination_Enable_Slcet_Input_Buttons_CB);

}

static void System_Control_Illumination_Enable_Input_Page_Exit(void){
	//clear_time_cnt(AUTO_EXIT_SETS_PAGE_TO_MAIN_PAGE_TIMER_NUMBER);
	//清除窗口
	dw_input_parameter_hint_window( 0 ,SYSTEM_RUN_TIME_ADJ_WAIT_WINDOW_VAR_ADDERSS,SYSTEM_RUN_TIME_ADJ_SUCCESS_WINDOW_VAR_ADDERSS,SYSTEM_RUN_TIME_ADJ_ERROR_WINDOW_VAR_ADDERSS);

}

static void System_Control_Illumination_Enable_Input_Page_Task(void){
	if(check_time_arrive(AUTO_EXIT_SETS_PAGE_TO_MAIN_PAGE_TIMER_NUMBER,set_systemcontrol_illumination_pararm_t.system_para.AutoExitSetsPageTime*1000)){
		Back_Main_Page_Load();
	}
}

static void System_Control_Illumination_Enable_Slcet_Input_Buttons_CB(key_Input_Number_Typedef key_number ,Key_Trg_Even key_state){
	if(key_state == KEY_CLICK_ACTION){
		//clear_time_cnt(AUTO_EXIT_SETS_PAGE_TO_MAIN_PAGE_TIMER_NUMBER);
		if(key_number ==  KEY_ENTER_TRG_NUMBER ){
			Menu_Exit(true);
		}else{
			set_systemcontrol_illumination_pararm_t.system_para.SetIlluminationControlEnable = !set_systemcontrol_illumination_pararm_t.system_para.SetIlluminationControlEnable;
			set_systemcontrol_illumination_pararm_t.SY_ShowSysControlIlluminationEnableFun_t(!set_systemcontrol_illumination_pararm_t.system_para.SetIlluminationControlEnable);  //显示动态图标
		}
	}
}

/********* 保存设置参数- 系统参数-系统控制-光照强度-光照强度使能  ******************/
static void System_Control_Illumination_Enable_Enter_Page_Load(void){
	int ret = -1 ;
	type_slect_move_cursor slect_move_cursor;
	slect_move_cursor.dw_cursor_adderss = SYSTEM_SYS_ILLUMINATION_CONTROL_ENAABLE_SELECT_CURSOR_ADDERSS ;
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
	dw_input_parameter_hint_window( 1 ,SYSTEM_SYS_ILLUMINATION_CONTROL_ENAABLE_WAIT_WINDOW_VAR_ADDERSS,SYSTEM_SYS_ILLUMINATION_CONTROL_ENAABLE_SUCCESS_WINDOW_VAR_ADDERSS,SYSTEM_SYS_ILLUMINATION_CONTROL_ENAABLE_ERROR_WINDOW_VAR_ADDERSS);
	ret = systemparaPoint_amend_config("SetIlluminationControlEnable",set_systemcontrol_illumination_pararm_t.system_para.SetIlluminationControlEnable);
	if( !ret){
		 //显示成功窗口
		dw_input_parameter_hint_window(2,SYSTEM_SYS_ILLUMINATION_CONTROL_ENAABLE_WAIT_WINDOW_VAR_ADDERSS,SYSTEM_SYS_ILLUMINATION_CONTROL_ENAABLE_SUCCESS_WINDOW_VAR_ADDERSS,SYSTEM_SYS_ILLUMINATION_CONTROL_ENAABLE_ERROR_WINDOW_VAR_ADDERSS);
	}else{
		//显示错误窗口
		dw_input_parameter_hint_window( 3,SYSTEM_SYS_ILLUMINATION_CONTROL_ENAABLE_WAIT_WINDOW_VAR_ADDERSS,SYSTEM_SYS_ILLUMINATION_CONTROL_ENAABLE_SUCCESS_WINDOW_VAR_ADDERSS,SYSTEM_SYS_ILLUMINATION_CONTROL_ENAABLE_ERROR_WINDOW_VAR_ADDERSS);
	}
	Buttons_Register(KEY_ENTER_TRG_NUMBER,System_Control_Illumination_Enter_Window_Buttons_CB);
}

static void System_Control_Illumination_Enable_Enter_Page_Exit(void){
	//清除窗口
	dw_input_parameter_hint_window( 0,SYSTEM_SYS_ILLUMINATION_CONTROL_ENAABLE_WAIT_WINDOW_VAR_ADDERSS,SYSTEM_SYS_ILLUMINATION_CONTROL_ENAABLE_SUCCESS_WINDOW_VAR_ADDERSS,SYSTEM_SYS_ILLUMINATION_CONTROL_ENAABLE_ERROR_WINDOW_VAR_ADDERSS);
	//clear_time_cnt(AUTO_EXIT_SETS_PAGE_TO_MAIN_PAGE_TIMER_NUMBER);
}

static void System_Control_Illumination_Enable_Enter_Page_Task(void){
	if(check_time_arrive(AUTO_EXIT_SETS_PAGE_TO_MAIN_PAGE_TIMER_NUMBER,set_systemcontrol_illumination_pararm_t.system_para.AutoExitSetsPageTime*1000)){
		Back_Main_Page_Load();
	}
}

/********************************************** 切换页面 - 系统参数-系统控制-光照强度-光照强度关闭设置值页面  ***************************************************************/
/* 自动返回主页菜单 */
static MenuList_t System_Illumination_Close_Value_Set_Menu_Table[] =
{
	{"设置光照强度关闭值输入框", NULL, System_Illumination_Close_Value_Input_Page_Load, System_Illumination_Close_Value_Input_Page_Exit,System_Illumination_Close_Value_Input_Page_Task, NULL},

    {"保存设置参数", NULL, System_Illumination_Close_Value_Enter_Page_Load, System_Illumination_Close_Value_Enter_Page_Exit, System_Illumination_Close_Value_Enter_Page_Task, NULL},

    {"返回上级菜单", NULL, Return_Previous_Menu_Page_Load, NULL, NULL, NULL},

    {"返回主页面", NULL,  Back_Main_Page_Load,   NULL,   NULL, NULL},
};

static void System_Illumination_Close_Value_Set_Page_Load(void){
	type_slect_move_cursor slect_move_cursor;

	slect_move_cursor.dw_cursor_adderss = SYSTEM_ILLUMINATION_CONTROL_CLOSE_VALUE_INTPUT_SELECT_CURSOR_VAR_ADDERSS ;
	slect_move_cursor.max_slect_move = 1 ;
	slect_move_cursor.min_slect_move = 0 ;
	slect_move_cursor.move_slect_step = 1 ;
	slect_move_cursor.now_slect_move = 0 ;
	slect_cursor_move_init(&slect_move_cursor);  		//光标位置初始化
	slect_cursor_move(cursor_refresh_mode,cursor_null);  //关闭输入指示光标

	slect_move_cursor.dw_cursor_adderss = SYSTEM_ILLUMINATION_CONTROL_CLOSE_SELECT_CURSOR_ADDERSS ;
	slect_move_cursor.max_slect_move = 3 ;
	slect_move_cursor.min_slect_move = 0 ;
	slect_move_cursor.move_slect_step = 1 ;
	slect_move_cursor.now_slect_move = 0 ;
	slect_cursor_move_init(&slect_move_cursor); 		 			//光标位置初始化
	slect_cursor_move(cursor_default_mode,cursor_null);  			//初始化选择设置光标

	set_systemcontrol_illumination_pararm_t.SY_ShowSysControlIlluminationCloseFun_t( deal_transducer_masg_t.illumination_par_t.illumination_percentage );
	set_systemcontrol_illumination_pararm_t.SY_ShowIntputSysControlIlluminationCloseFun_t( set_systemcontrol_illumination_pararm_t.system_para.SetCloseIlluminationLX1 );

	dw_show_switching_pages(PAGE_SYSTEM_CONTROL_ILLUMINATION_CLOSE_NUMBER); //切换页面
	Buttons_Register(KEY_UP_TRG_NUMBER,System_Control_Illumination_Slcet_Set_Buttons_CB);
	Buttons_Register(KEY_ENTER_TRG_NUMBER,System_Control_Illumination_Slcet_Set_Buttons_CB);
	Buttons_Register(KEY_DOWN_TRG_NUMBER,System_Control_Illumination_Slcet_Set_Buttons_CB);
	Menu_Bind(System_Illumination_Close_Value_Set_Menu_Table, GET_MENU_NUM(System_Illumination_Close_Value_Set_Menu_Table), System_Control_Illumination_SetMenu);
}
static void System_Illumination_Close_Value_Set_Page_Exit(void){
	//clear_time_cnt(AUTO_EXIT_SETS_PAGE_TO_MAIN_PAGE_TIMER_NUMBER);
}
static void System_Illumination_Close_Value_Set_Page_Task(void){
	static uint8_t illumi_cnt = 0 ;
	static uint8_t old_illumination_percentage = 0 ;
	illumi_cnt++ ;
	if( illumi_cnt > 100 ){
		illumi_cnt = 0 ;
		if(old_illumination_percentage != deal_transducer_masg_t.illumination_par_t.illumination_date){
			set_systemcontrol_illumination_pararm_t.SY_ShowSysControlIlluminationCloseFun_t( deal_transducer_masg_t.illumination_par_t.illumination_percentage );
			old_illumination_percentage = deal_transducer_masg_t.illumination_par_t.illumination_percentage;
		}
	}
	if(check_time_arrive(AUTO_EXIT_SETS_PAGE_TO_MAIN_PAGE_TIMER_NUMBER,set_systemcontrol_illumination_pararm_t.system_para.AutoExitSetsPageTime*1000)){
		Back_Main_Page_Load();
	}
}
/************* 输入参数- 切换页面 - 系统参数-系统控制-光照强度-光照强度关闭设置值页面  *******************/
static void System_Illumination_Close_Value_Input_Page_Load(void){
	type_slect_move_cursor slect_move_cursor;

	slect_move_cursor.dw_cursor_adderss = SYSTEM_ILLUMINATION_CONTROL_CLOSE_SELECT_CURSOR_ADDERSS ;
	slect_move_cursor.max_slect_move = 3 ;
	slect_move_cursor.min_slect_move = 0 ;
	slect_move_cursor.move_slect_step = 1 ;
	slect_move_cursor.now_slect_move = 0 ;
	slect_cursor_move_init(&slect_move_cursor);  //光标位置初始化
	slect_cursor_move(cursor_refresh_mode,cursor_null);  //关闭选择设置光标

	slect_move_cursor.dw_cursor_adderss = SYSTEM_ILLUMINATION_CONTROL_CLOSE_VALUE_INTPUT_SELECT_CURSOR_VAR_ADDERSS ;
	slect_move_cursor.max_slect_move = 1 ;
	slect_move_cursor.min_slect_move = 0 ;
	slect_move_cursor.move_slect_step = 1 ;
	slect_move_cursor.now_slect_move = 0 ;
	slect_cursor_move_init(&slect_move_cursor);  //光标位置初始化
	slect_cursor_move(cursor_default_mode,cursor_null);  //显示初始化输入指示光标位置

	Buttons_Register(KEY_UP_TRG_NUMBER,System_Illumination_Close_Value_Input_Buttons_CB);
	Buttons_Register(KEY_ENTER_TRG_NUMBER,System_Illumination_Close_Value_Input_Buttons_CB);
	Buttons_Register(KEY_DOWN_TRG_NUMBER,System_Illumination_Close_Value_Input_Buttons_CB);
}

static void System_Illumination_Close_Value_Input_Page_Exit(void){
	//clear_time_cnt(AUTO_EXIT_SETS_PAGE_TO_MAIN_PAGE_TIMER_NUMBER);
}

static void System_Illumination_Close_Value_Input_Page_Task(void){
	if(check_time_arrive(AUTO_EXIT_SETS_PAGE_TO_MAIN_PAGE_TIMER_NUMBER,set_systemcontrol_illumination_pararm_t.system_para.AutoExitSetsPageTime*1000)){
		Back_Main_Page_Load();
	}
}


static void System_Illumination_Close_Value_Input_Buttons_CB(key_Input_Number_Typedef key_number ,Key_Trg_Even key_state){
	if(key_state == KEY_CLICK_ACTION){
		//clear_time_cnt(AUTO_EXIT_SETS_PAGE_TO_MAIN_PAGE_TIMER_NUMBER);
		set_systemcontrol_illumination_pararm_t.system_para.SetCloseIlluminationLX1=user_parameter_adjustment(set_systemcontrol_illumination_pararm_t.system_para.SetCloseIlluminationLX1, \
				false,2,key_number,set_systemcontrol_illumination_pararm_t.SY_ShowIntputSysControlIlluminationCloseFun_t);
	}
}


/********* 保存设置参数- 切换页面 - 系统参数-系统控制-光照强度-光照强度关闭设置值  ******************/
static void System_Illumination_Close_Value_Enter_Page_Load(void){
	int ret = -1 ;
	type_slect_move_cursor slect_move_cursor;

	slect_move_cursor.dw_cursor_adderss = SYSTEM_ILLUMINATION_CONTROL_CLOSE_SELECT_CURSOR_ADDERSS ;
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
	dw_input_parameter_hint_window( 1 ,SYSTEM_ILLUMINATION_CONTROL_CLOSE_WAIT_WINDOW_VAR_ADDERSS,SYSTEM_ILLUMINATION_CONTROL_CLOSE_SUCCESS_WINDOW_VAR_ADDERSS,SYSTEM_ILLUMINATION_CONTROL_CLOSE_ERROR_WINDOW_VAR_ADDERSS);
	ret = systemparaPoint_amend_config("SetCloseIlluminationLX1",set_systemcontrol_illumination_pararm_t.system_para.SetCloseIlluminationLX1);
	if( !ret){
		 //显示成功窗口
		dw_input_parameter_hint_window(2,SYSTEM_ILLUMINATION_CONTROL_CLOSE_WAIT_WINDOW_VAR_ADDERSS,SYSTEM_ILLUMINATION_CONTROL_CLOSE_SUCCESS_WINDOW_VAR_ADDERSS,SYSTEM_ILLUMINATION_CONTROL_CLOSE_ERROR_WINDOW_VAR_ADDERSS);
	}else{
		//显示错误窗口
		dw_input_parameter_hint_window( 3,SYSTEM_ILLUMINATION_CONTROL_CLOSE_WAIT_WINDOW_VAR_ADDERSS,SYSTEM_ILLUMINATION_CONTROL_CLOSE_SUCCESS_WINDOW_VAR_ADDERSS,SYSTEM_ILLUMINATION_CONTROL_CLOSE_ERROR_WINDOW_VAR_ADDERSS);
	}

	Buttons_Register(KEY_ENTER_TRG_NUMBER,System_Control_Illumination_Enter_Window_Buttons_CB);
}

static void System_Illumination_Close_Value_Enter_Page_Exit(void){
	dw_input_parameter_hint_window( 0,SYSTEM_ILLUMINATION_CONTROL_CLOSE_WAIT_WINDOW_VAR_ADDERSS,SYSTEM_ILLUMINATION_CONTROL_CLOSE_SUCCESS_WINDOW_VAR_ADDERSS,SYSTEM_ILLUMINATION_CONTROL_CLOSE_ERROR_WINDOW_VAR_ADDERSS);
	//clear_time_cnt(AUTO_EXIT_SETS_PAGE_TO_MAIN_PAGE_TIMER_NUMBER);
}

static void System_Illumination_Close_Value_Enter_Page_Task(void){
	if(check_time_arrive(AUTO_EXIT_SETS_PAGE_TO_MAIN_PAGE_TIMER_NUMBER,set_systemcontrol_illumination_pararm_t.system_para.AutoExitSetsPageTime*1000)){
		Back_Main_Page_Load();
	}
}


/********************************************** 切换页面 - 系统参数-系统控制-光照强度-光照强度打开设置值页面  ***************************************************************/
/* 自动返回主页菜单 */
static MenuList_t System_Illumination_Open_Value_Set_Menu_Table[] =
{
	{"设置光照强度打开值输入框", NULL, System_Illumination_Open_Value_Input_Page_Load, System_Illumination_Open_Value_Input_Page_Exit,System_Illumination_Open_Value_Input_Page_Task, NULL},

    {"保存设置参数", NULL, System_Illumination_Open_Value_Enter_Page_Load, System_Illumination_Open_Value_Enter_Page_Exit, System_Illumination_Open_Value_Enter_Page_Task, NULL},

    {"返回上级菜单", NULL,  Return_Previous_Menu_Page_Load, NULL, NULL, NULL},

    {"返回主页面", NULL,  Back_Main_Page_Load,   NULL,   NULL, NULL},
};

static void System_Illumination_Open_Value_Set_Page_Load(void){
	type_slect_move_cursor slect_move_cursor;

	slect_move_cursor.dw_cursor_adderss = SYSTEM_ILLUMINATION_CONTROL_OPEN_VALUE_INTPUT_SELECT_CURSOR_VAR_ADDERSS ;
	slect_move_cursor.max_slect_move = 1 ;
	slect_move_cursor.min_slect_move = 0 ;
	slect_move_cursor.move_slect_step = 1 ;
	slect_move_cursor.now_slect_move = 0 ;
	slect_cursor_move_init(&slect_move_cursor);  		//光标位置初始化
	slect_cursor_move(cursor_refresh_mode,cursor_null);  //关闭输入指示光标

	slect_move_cursor.dw_cursor_adderss = SYSTEM_ILLUMINATION_CONTROL_OPEN_SELECT_CURSOR_ADDERSS ;
	slect_move_cursor.max_slect_move = 3 ;
	slect_move_cursor.min_slect_move = 0 ;
	slect_move_cursor.move_slect_step = 1 ;
	slect_move_cursor.now_slect_move = 0 ;
	slect_cursor_move_init(&slect_move_cursor); 		 			//光标位置初始化
	slect_cursor_move(cursor_default_mode,cursor_null);  			//初始化选择设置光标

	set_systemcontrol_illumination_pararm_t.SY_ShowSysControlIlluminationOpenFun_t( deal_transducer_masg_t.illumination_par_t.illumination_percentage);
	set_systemcontrol_illumination_pararm_t.SY_ShowIntputSysControlIlluminationOpenFun_t( set_systemcontrol_illumination_pararm_t.system_para.SetOpenIlluminationLX2 );

	dw_show_switching_pages(PAGE_SYSTEM_CONTROL_ILLUMINATION_OPEN_NUMBER); //切换页面
	Buttons_Register(KEY_UP_TRG_NUMBER,System_Control_Illumination_Slcet_Set_Buttons_CB);
	Buttons_Register(KEY_ENTER_TRG_NUMBER,System_Control_Illumination_Slcet_Set_Buttons_CB);
	Buttons_Register(KEY_DOWN_TRG_NUMBER,System_Control_Illumination_Slcet_Set_Buttons_CB);
	Menu_Bind(System_Illumination_Open_Value_Set_Menu_Table, GET_MENU_NUM(System_Illumination_Open_Value_Set_Menu_Table), System_Control_Illumination_SetMenu);
}
static void System_Illumination_Open_Value_Set_Page_Exit(void){
	//clear_time_cnt(AUTO_EXIT_SETS_PAGE_TO_MAIN_PAGE_TIMER_NUMBER);
}
static void System_Illumination_Open_Value_Set_Page_Task(void){
	static uint8_t illumi_cnt = 0 ;
	static uint8_t old_illumination_percentage = 0 ;
	illumi_cnt++ ;
	if( illumi_cnt > 100 ){
		illumi_cnt = 0 ;
		if(old_illumination_percentage != deal_transducer_masg_t.illumination_par_t.illumination_date){
			set_systemcontrol_illumination_pararm_t.SY_ShowSysControlIlluminationCloseFun_t( deal_transducer_masg_t.illumination_par_t.illumination_percentage );
			old_illumination_percentage = deal_transducer_masg_t.illumination_par_t.illumination_percentage;
		}
	}
	if(check_time_arrive(AUTO_EXIT_SETS_PAGE_TO_MAIN_PAGE_TIMER_NUMBER,set_systemcontrol_illumination_pararm_t.system_para.AutoExitSetsPageTime*1000)){
		Back_Main_Page_Load();
	}
}
/************* 输入参数- 系统参数-系统控制-光照强度-光照强度打开设置值页面  *******************/
static void System_Illumination_Open_Value_Input_Page_Load(void){
	type_slect_move_cursor slect_move_cursor;

	slect_move_cursor.dw_cursor_adderss = SYSTEM_ILLUMINATION_CONTROL_OPEN_SELECT_CURSOR_ADDERSS ;
	slect_move_cursor.max_slect_move = 3 ;
	slect_move_cursor.min_slect_move = 0 ;
	slect_move_cursor.move_slect_step = 1 ;
	slect_move_cursor.now_slect_move = 0 ;
	slect_cursor_move_init(&slect_move_cursor);  //光标位置初始化
	slect_cursor_move(cursor_refresh_mode,cursor_null);  //关闭选择设置光标

	slect_move_cursor.dw_cursor_adderss = SYSTEM_ILLUMINATION_CONTROL_OPEN_VALUE_INTPUT_SELECT_CURSOR_VAR_ADDERSS ;
	slect_move_cursor.max_slect_move = 1 ;
	slect_move_cursor.min_slect_move = 0 ;
	slect_move_cursor.move_slect_step = 1 ;
	slect_move_cursor.now_slect_move = 0 ;
	slect_cursor_move_init(&slect_move_cursor);  //光标位置初始化
	slect_cursor_move(cursor_default_mode,cursor_null);  //显示初始化输入指示光标位置


	Buttons_Register(KEY_UP_TRG_NUMBER,System_Illumination_Open_Value_Input_Buttons_CB);
	Buttons_Register(KEY_ENTER_TRG_NUMBER,System_Illumination_Open_Value_Input_Buttons_CB);
	Buttons_Register(KEY_DOWN_TRG_NUMBER,System_Illumination_Open_Value_Input_Buttons_CB);
}

static void System_Illumination_Open_Value_Input_Page_Exit(void){
	//clear_time_cnt(AUTO_EXIT_SETS_PAGE_TO_MAIN_PAGE_TIMER_NUMBER);
}

static void System_Illumination_Open_Value_Input_Page_Task(void){
	if(check_time_arrive(AUTO_EXIT_SETS_PAGE_TO_MAIN_PAGE_TIMER_NUMBER,set_systemcontrol_illumination_pararm_t.system_para.AutoExitSetsPageTime*1000)){
		Back_Main_Page_Load();
	}
}


static void System_Illumination_Open_Value_Input_Buttons_CB(key_Input_Number_Typedef key_number ,Key_Trg_Even key_state){
	if(key_state == KEY_CLICK_ACTION){
		//clear_time_cnt(AUTO_EXIT_SETS_PAGE_TO_MAIN_PAGE_TIMER_NUMBER);
		set_systemcontrol_illumination_pararm_t.system_para.SetOpenIlluminationLX2=user_parameter_adjustment(set_systemcontrol_illumination_pararm_t.system_para.SetOpenIlluminationLX2, \
				false,2,key_number,set_systemcontrol_illumination_pararm_t.SY_ShowIntputSysControlIlluminationOpenFun_t);
	}
}


/********* 保存设置参数- 系统参数-系统控制-光照强度-光照强度打开值  ******************/
static void System_Illumination_Open_Value_Enter_Page_Load(void){
	int ret = -1 ;
	type_slect_move_cursor slect_move_cursor;

	slect_move_cursor.dw_cursor_adderss = SYSTEM_ILLUMINATION_CONTROL_OPEN_SELECT_CURSOR_ADDERSS ;
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
	dw_input_parameter_hint_window( 1 ,SYSTEM_ILLUMINATION_CONTROL_OPEN_WAIT_WINDOW_VAR_ADDERSS,SYSTEM_ILLUMINATION_CONTROL_OPEN_SUCCESS_WINDOW_VAR_ADDERSS,SYSTEM_ILLUMINATION_CONTROL_OPEN_ERROR_WINDOW_VAR_ADDERSS);
	ret = systemparaPoint_amend_config("SetOpenIlluminationLX2",set_systemcontrol_illumination_pararm_t.system_para.SetOpenIlluminationLX2);
	if( !ret){
		 //显示成功窗口
		dw_input_parameter_hint_window(2,SYSTEM_ILLUMINATION_CONTROL_OPEN_WAIT_WINDOW_VAR_ADDERSS,SYSTEM_ILLUMINATION_CONTROL_OPEN_SUCCESS_WINDOW_VAR_ADDERSS,SYSTEM_ILLUMINATION_CONTROL_OPEN_ERROR_WINDOW_VAR_ADDERSS);
	}else{
		//显示错误窗口
		dw_input_parameter_hint_window( 3,SYSTEM_ILLUMINATION_CONTROL_OPEN_WAIT_WINDOW_VAR_ADDERSS,SYSTEM_ILLUMINATION_CONTROL_OPEN_SUCCESS_WINDOW_VAR_ADDERSS,SYSTEM_ILLUMINATION_CONTROL_OPEN_ERROR_WINDOW_VAR_ADDERSS);
	}

	Buttons_Register(KEY_ENTER_TRG_NUMBER,System_Control_Illumination_Enter_Window_Buttons_CB);
}

static void System_Illumination_Open_Value_Enter_Page_Exit(void){
	dw_input_parameter_hint_window( 0,SYSTEM_ILLUMINATION_CONTROL_OPEN_WAIT_WINDOW_VAR_ADDERSS,SYSTEM_ILLUMINATION_CONTROL_OPEN_SUCCESS_WINDOW_VAR_ADDERSS,SYSTEM_ILLUMINATION_CONTROL_OPEN_ERROR_WINDOW_VAR_ADDERSS);
	//clear_time_cnt(AUTO_EXIT_SETS_PAGE_TO_MAIN_PAGE_TIMER_NUMBER);
}

static void System_Illumination_Open_Value_Enter_Page_Task(void){
	if(check_time_arrive(AUTO_EXIT_SETS_PAGE_TO_MAIN_PAGE_TIMER_NUMBER,set_systemcontrol_illumination_pararm_t.system_para.AutoExitSetsPageTime*1000)){
		Back_Main_Page_Load();
	}
}

/************* 系统参数-系统时间公共回调函数  *******************/
static void System_Control_Illumination_Slcet_Set_Buttons_CB( key_Input_Number_Typedef key_number , Key_Trg_Even key_state){
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

static void System_Control_Illumination_Enter_Window_Buttons_CB( key_Input_Number_Typedef key_number , Key_Trg_Even key_state){
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



