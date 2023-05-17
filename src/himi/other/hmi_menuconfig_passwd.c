/*
 * hmi_menuconfig_passwd.c
 *
 *  Created on: 2023年5月16日
 *      Author: 好
 */
#define LOG_TAG    "hmi_menuconfig_passwd"

#include "../himi/other/hmi_menuconfig_passwd.h"

static void MenuDateShow_Init(void);


/************* 输入参数- 设置密码页面  *******************/
static void Set_Login_Passwd_Input_Page_Load(void);
static void Set_Login_Passwd_Input_Page_Exit(void);
static void Set_Login_Passwd_Input_Page_Task(void);
static void Hmi_Set_Menuconfig_Passwd_Input_Buttons_CB(key_Input_Number_Typedef key_number ,Key_Trg_Even key_state);


/********* 保存设置参数- 设置密码  ******************/
static void Set_Login_Passwd_Enter_Page_Load(void);
static void Set_Login_Passwd_Enter_Page_Exit(void);
static void Set_Login_Passwd_Enter_Page_Task(void);

static void Slcet_Cursor_Set_Buttons_CB( key_Input_Number_Typedef key_number , Key_Trg_Even key_state);
static void Passwd_Slcet_Enter_Window_Buttons_CB( key_Input_Number_Typedef key_number , Key_Trg_Even key_state);


struct menucnfig_passwd_menu_list_pararm{
	other_para_def other_para_def_t ;
	system_para_def system_para_t ;
	ShownMenuDate SetLoginPasswd_ShowCompensationDate_t;	//显示密码函数
};

static struct menucnfig_passwd_menu_list_pararm menucnfig_passwd_menu_list_pararm_t;

/********************************************** 切换页面 - 设置登录菜单密码页面  ***************************************************************/
/*设置密码菜单 */
static MenuList_t Set_Login_Passwd_Menu_Table[] =
{
	{"参数输入框", NULL, Set_Login_Passwd_Input_Page_Load, Set_Login_Passwd_Input_Page_Exit, Set_Login_Passwd_Input_Page_Task, NULL},

    {"保存设置参数", NULL, Set_Login_Passwd_Enter_Page_Load, Set_Login_Passwd_Enter_Page_Exit, Set_Login_Passwd_Enter_Page_Task, NULL},

    {"返回上级菜单", NULL,  Return_Previous_Menu_Page_Load, NULL, NULL, NULL},

    {"返回主页面", NULL,  Back_Main_Page_Load,   NULL,   NULL, NULL},
};


/* 设置菜单显示效果 */
static void MenuconfigPasswd_SetMenu(  MenuShow_t *ptShowInfo){
	show_refresh_time();
	show_eth_connect_state();
}


static void MenuDateShow_Init(void){
	read_saveenv_cjson_system_parameter(&menucnfig_passwd_menu_list_pararm_t.system_para_t);
	read_saveenv_cjson_other_parameter(&menucnfig_passwd_menu_list_pararm_t.other_para_def_t);
	menucnfig_passwd_menu_list_pararm_t.SetLoginPasswd_ShowCompensationDate_t =show_set_menuconfig_passwd_date;
}


void Menuconfig_Passwd_Setting_Page_Load(void){

	type_slect_move_cursor slect_move_cursor;

	slect_move_cursor.dw_cursor_adderss = SETTING_LOGIN_PASSWD_INTPUT_SELECT_CURSOR_VAR_ADDERSS ;
	slect_move_cursor.max_slect_move = 3 ;
	slect_move_cursor.min_slect_move = 0 ;
	slect_move_cursor.move_slect_step = 1 ;
	slect_move_cursor.now_slect_move = 0 ;
	slect_cursor_move_init(&slect_move_cursor);  			//光标输入位置初始化
	slect_cursor_move(cursor_refresh_mode,cursor_null);  	//关闭输入位置光标
	slect_move_cursor.dw_cursor_adderss = SETTING_LOGIN_PASSWD_SELECT_CURSOR_ADDERSS ;
	slect_move_cursor.max_slect_move = 3 ;
	slect_move_cursor.min_slect_move = 0 ;
	slect_move_cursor.move_slect_step = 1 ;
	slect_move_cursor.now_slect_move = 0 ;
	slect_cursor_move_init(&slect_move_cursor); 		 			//光标位置初始化
	slect_cursor_move(cursor_default_mode,cursor_null);  			//初始化选择设置光标
	MenuDateShow_Init();
	dw_show_switching_pages(PAGE_SETTING_MENUCONFIG_PASSWORD_NUMBER); //切换页面
	Buttons_Register(KEY_UP_TRG_NUMBER,Slcet_Cursor_Set_Buttons_CB);
	Buttons_Register(KEY_ENTER_TRG_NUMBER,Slcet_Cursor_Set_Buttons_CB);
	Buttons_Register(KEY_DOWN_TRG_NUMBER,Slcet_Cursor_Set_Buttons_CB);
	log_d("login_menuconfig_passwd=%d",menucnfig_passwd_menu_list_pararm_t.other_para_def_t.login_menuconfig_passwd);
	menucnfig_passwd_menu_list_pararm_t.SetLoginPasswd_ShowCompensationDate_t(menucnfig_passwd_menu_list_pararm_t.other_para_def_t.login_menuconfig_passwd);  //显示湿度补偿值
	Menu_Bind(Set_Login_Passwd_Menu_Table, GET_MENU_NUM(Set_Login_Passwd_Menu_Table), MenuconfigPasswd_SetMenu);
}


void Menuconfig_Passwd_Setting_Page_Exit(void){
//	Buttons_UnRegister(KEY_UP_TRG_NUMBER);
//	Buttons_UnRegister(KEY_ENTER_TRG_NUMBER);
//	Buttons_UnRegister(KEY_DOWN_TRG_NUMBER);
}

void Menuconfig_Passwd_Setting_Page_Task(void){
	if(check_time_arrive(AUTO_EXIT_SETS_PAGE_TO_MAIN_PAGE_TIMER_NUMBER,menucnfig_passwd_menu_list_pararm_t.system_para_t.AutoExitSetsPageTime*1000)){
		Back_Main_Page_Load();
	}
}


/************* 输入参数- 设置密码页面  *******************/
static void Set_Login_Passwd_Input_Page_Load(void){
	type_slect_move_cursor slect_move_cursor;
	slect_move_cursor.dw_cursor_adderss = SETTING_LOGIN_PASSWD_SELECT_CURSOR_ADDERSS ;
	slect_move_cursor.max_slect_move = 3 ;
	slect_move_cursor.min_slect_move = 0 ;
	slect_move_cursor.move_slect_step = 1 ;
	slect_move_cursor.now_slect_move = 0 ;
	slect_cursor_move_init(&slect_move_cursor);  			//光标输入位置初始化
	slect_cursor_move(cursor_refresh_mode,cursor_null);  	//关闭输入位置光标
	slect_move_cursor.dw_cursor_adderss = SETTING_LOGIN_PASSWD_INTPUT_SELECT_CURSOR_VAR_ADDERSS ;
	slect_move_cursor.max_slect_move = 3 ;
	slect_move_cursor.min_slect_move = 0 ;
	slect_move_cursor.move_slect_step = 1 ;
	slect_move_cursor.now_slect_move = 0 ;
	slect_cursor_move_init(&slect_move_cursor); 		 			//光标位置初始化
	slect_cursor_move(cursor_default_mode,cursor_null);  			//初始化选择设置光标
	Buttons_Register(KEY_UP_TRG_NUMBER,Hmi_Set_Menuconfig_Passwd_Input_Buttons_CB);
	Buttons_Register(KEY_ENTER_TRG_NUMBER,Hmi_Set_Menuconfig_Passwd_Input_Buttons_CB);
	Buttons_Register(KEY_DOWN_TRG_NUMBER,Hmi_Set_Menuconfig_Passwd_Input_Buttons_CB);
}
static void Set_Login_Passwd_Input_Page_Exit(void){
//	Buttons_UnRegister(KEY_UP_TRG_NUMBER);
//	Buttons_UnRegister(KEY_ENTER_TRG_NUMBER);
//	Buttons_UnRegister(KEY_DOWN_TRG_NUMBER);
}
static void Set_Login_Passwd_Input_Page_Task(void){
	if(check_time_arrive(AUTO_EXIT_SETS_PAGE_TO_MAIN_PAGE_TIMER_NUMBER,menucnfig_passwd_menu_list_pararm_t.system_para_t.AutoExitSetsPageTime*1000)){
		Back_Main_Page_Load();
	}
}

static void Hmi_Set_Menuconfig_Passwd_Input_Buttons_CB(key_Input_Number_Typedef key_number ,Key_Trg_Even key_state){
	if(key_state == KEY_CLICK_ACTION){
		menucnfig_passwd_menu_list_pararm_t.other_para_def_t.login_menuconfig_passwd=user_parameter_adjustment(menucnfig_passwd_menu_list_pararm_t.other_para_def_t.login_menuconfig_passwd,0,4,key_number,menucnfig_passwd_menu_list_pararm_t.SetLoginPasswd_ShowCompensationDate_t);
	}
}


/********* 保存设置参数- 设置密码  ******************/
static void Set_Login_Passwd_Enter_Page_Load(void){
	int ret = -1 ;
	type_slect_move_cursor slect_move_cursor;
	slect_move_cursor.dw_cursor_adderss = SETTING_LOGIN_PASSWD_INTPUT_SELECT_CURSOR_VAR_ADDERSS ;
	slect_move_cursor.max_slect_move = 3 ;
	slect_move_cursor.min_slect_move = 0 ;
	slect_move_cursor.move_slect_step = 1 ;
	slect_move_cursor.now_slect_move = 0 ;
	slect_cursor_move_init(&slect_move_cursor);  //光标位置初始化
	slect_cursor_move(cursor_refresh_mode,cursor_null);  //关闭光标
	Buttons_UnRegister(KEY_UP_TRG_NUMBER);
	Buttons_UnRegister(KEY_ENTER_TRG_NUMBER);
	Buttons_UnRegister(KEY_DOWN_TRG_NUMBER);
	log_d("login_menuconfig_passwd=%d",menucnfig_passwd_menu_list_pararm_t.other_para_def_t.login_menuconfig_passwd);
	ret = OtherparaPoint_amend_config("LoginMenuconfigPasswd",menucnfig_passwd_menu_list_pararm_t.other_para_def_t.login_menuconfig_passwd);
	if( !ret){
		 //显示成功窗口
		dw_by_oneself_adderss_var_display( SETTING_LOGIN_PASSWD_SUCCESS_WINDOW_VAR_ADDERSS , 1 ) ;
	}else{
		//显示错误窗口
		dw_by_oneself_adderss_var_display( SETTING_LOGIN_PASSWD_ERROR_WINDOW_VAR_ADDERSS , 1 ) ;
	}
	Buttons_Register(KEY_ENTER_TRG_NUMBER,Passwd_Slcet_Enter_Window_Buttons_CB);
}

static void Set_Login_Passwd_Enter_Page_Exit(void){
	//清除窗口
	dw_by_oneself_adderss_var_display( SETTING_LOGIN_PASSWD_SUCCESS_WINDOW_VAR_ADDERSS , 0 ) ;
	dw_by_oneself_adderss_var_display( SETTING_LOGIN_PASSWD_ERROR_WINDOW_VAR_ADDERSS , 0 ) ;
//	Buttons_UnRegister(KEY_UP_TRG_NUMBER);
//	Buttons_UnRegister(KEY_ENTER_TRG_NUMBER);
//	Buttons_UnRegister(KEY_DOWN_TRG_NUMBER);
}

static void Set_Login_Passwd_Enter_Page_Task(void){
	if(check_time_arrive(AUTO_EXIT_SETS_PAGE_TO_MAIN_PAGE_TIMER_NUMBER,menucnfig_passwd_menu_list_pararm_t.system_para_t.AutoExitSetsPageTime*1000)){
		Back_Main_Page_Load();
	}
}


/************* 内部湿度传感器公共回调函数  *******************/
static void Slcet_Cursor_Set_Buttons_CB( key_Input_Number_Typedef key_number , Key_Trg_Even key_state){
	if(key_state == KEY_CLICK_ACTION){
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



static void Passwd_Slcet_Enter_Window_Buttons_CB( key_Input_Number_Typedef key_number , Key_Trg_Even key_state){
	if(key_state == KEY_CLICK_ACTION){
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
