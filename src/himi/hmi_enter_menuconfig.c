/*
 * hmi_enter_menuconfig.c
 *
 *  Created on: 2023年5月16日
 *      Author: 好
 */

#define LOG_TAG    "hmi_enter_menuconfig"

#include "../himi/hmi_enter_menuconfig.h"


static void MenuDateShow_Init(void);

static void Enter_Menuconfig_Passwd_Input_Page_Load(void);
static void Enter_Menuconfig_Passwd_Input_Page_Exit(void);
static void Enter_Menuconfig_Passwd_Input_Page_Task(void);


static void Enter_Menuconfig_Passwd_Confirm_Page_Load(void);
static void Enter_Menuconfig_Passwd_Confirm_Page_Exit(void);
static void Enter_Menuconfig_Passwd_Confirm_Page_Task(void);

static void Hmi_Enter_Menuconfig_Passwd_Input_Buttons_CB(key_Input_Number_Typedef key_number ,Key_Trg_Even key_state);
static void Slcet_Cursor_Set_Buttons_CB( key_Input_Number_Typedef key_number , Key_Trg_Even key_state);
static void Enter_Passwd_Window_Buttons_CB( key_Input_Number_Typedef key_number , Key_Trg_Even key_state);

struct enter_menuconfig_passwd_menu_list_pararm{
	int enter_menuconfig_passwd ;
	system_para_def system_para_t ;
	other_para_def other_para_def_t ;
	ShownMenuDate SetLoginPasswd_ShowCompensationDate_t;	//显示密码函数
};


static struct enter_menuconfig_passwd_menu_list_pararm enter_menuconfig_passwd_menu_list_pararm_t ;

static void MenuDateShow_Init(void){
	read_saveenv_cjson_system_parameter(&enter_menuconfig_passwd_menu_list_pararm_t.system_para_t);
	read_saveenv_cjson_other_parameter(&enter_menuconfig_passwd_menu_list_pararm_t.other_para_def_t);
	enter_menuconfig_passwd_menu_list_pararm_t.SetLoginPasswd_ShowCompensationDate_t =show_enter_menuconfig_passwd_date;
	enter_menuconfig_passwd_menu_list_pararm_t.enter_menuconfig_passwd = 0 ;
}

/* 设置菜单显示效果 */
static void Other_SetMenu(  MenuShow_t *ptShowInfo){
	show_refresh_time();
	show_eth_connect_state();
}


/********************************************** 切换页面 - 其他参数选择设置页面  ***************************************************************/
/* 其他参数选择设置菜单*/
static MenuList_t Enter_Menuconfig_Menu_Table[] =
{
	{"密码输入框", NULL, Enter_Menuconfig_Passwd_Input_Page_Load, Enter_Menuconfig_Passwd_Input_Page_Exit, Enter_Menuconfig_Passwd_Input_Page_Task, NULL},

    {"确定", NULL, Enter_Menuconfig_Passwd_Confirm_Page_Load, Enter_Menuconfig_Passwd_Confirm_Page_Exit, Enter_Menuconfig_Passwd_Confirm_Page_Task, NULL},

    {"退出", NULL,  Back_Main_Page_Load,   NULL,   NULL, NULL},

	{"进入菜单设置", NULL, Hmi_Main_Setting_Page_Load, Hmi_Main_Setting_Page_Exit, Hmi_Main_Setting_Page_Task, NULL},
};


void Hmi_Enter_Menuconfig_Page_Load(void){
	log_d("Hmi_Enter_Menuconfig_Page_Load ");

	type_slect_move_cursor slect_move_cursor;
	slect_move_cursor.dw_cursor_adderss = ENTER_MENUCONFIG_PASSWD_INTPUT_SELECT_CURSOR_VAR_ADDERSS ;
	slect_move_cursor.max_slect_move = 3 ;
	slect_move_cursor.min_slect_move = 0 ;
	slect_move_cursor.move_slect_step = 1 ;
	slect_move_cursor.now_slect_move = 0 ;
	slect_cursor_move_init(&slect_move_cursor);  			//光标输入位置初始化
	slect_cursor_move(cursor_refresh_mode,cursor_null);  	//关闭输入位置光标
	slect_move_cursor.dw_cursor_adderss = ENTER_MENUCONFIG_PASSWD_SELECT_CURSOR_ADDERSS ;
	slect_move_cursor.max_slect_move = 2 ;
	slect_move_cursor.min_slect_move = 0 ;
	slect_move_cursor.move_slect_step = 1 ;
	slect_move_cursor.now_slect_move = 0 ;
	slect_cursor_move_init(&slect_move_cursor); 		 			//光标位置初始化
	slect_cursor_move(cursor_default_mode,cursor_null);  			//初始化选择设置光标
	dw_show_switching_pages(PAGE_CHECK_MENUCONFIG_PASSWORD_NUMBER); 	//切换页面

	MenuDateShow_Init();
	enter_menuconfig_passwd_menu_list_pararm_t.SetLoginPasswd_ShowCompensationDate_t(enter_menuconfig_passwd_menu_list_pararm_t.enter_menuconfig_passwd );
	Buttons_Register(KEY_UP_TRG_NUMBER,Slcet_Cursor_Set_Buttons_CB);
	Buttons_Register(KEY_ENTER_TRG_NUMBER,Slcet_Cursor_Set_Buttons_CB);
	Buttons_Register(KEY_DOWN_TRG_NUMBER,Slcet_Cursor_Set_Buttons_CB);
	Menu_Bind(Enter_Menuconfig_Menu_Table, GET_MENU_NUM(Enter_Menuconfig_Menu_Table)-1, Other_SetMenu);
}


void Hmi_Enter_Menuconfig_Page_Task(void){
	if(check_time_arrive(AUTO_EXIT_SETS_PAGE_TO_MAIN_PAGE_TIMER_NUMBER,enter_menuconfig_passwd_menu_list_pararm_t.system_para_t.AutoExitSetsPageTime*1000)){
		Back_Main_Page_Load();
	}
}

static void Enter_Menuconfig_Passwd_Input_Page_Load(void){
	type_slect_move_cursor slect_move_cursor;
	slect_move_cursor.dw_cursor_adderss = ENTER_MENUCONFIG_PASSWD_SELECT_CURSOR_ADDERSS ;
	slect_move_cursor.max_slect_move = 2 ;
	slect_move_cursor.min_slect_move = 0 ;
	slect_move_cursor.move_slect_step = 1 ;
	slect_move_cursor.now_slect_move = 0 ;
	slect_cursor_move_init(&slect_move_cursor);  			//光标输入位置初始化
	slect_cursor_move(cursor_refresh_mode,cursor_null);  	//关闭输入位置光标
	slect_move_cursor.dw_cursor_adderss = ENTER_MENUCONFIG_PASSWD_INTPUT_SELECT_CURSOR_VAR_ADDERSS ;
	slect_move_cursor.max_slect_move = 3 ;
	slect_move_cursor.min_slect_move = 0 ;
	slect_move_cursor.move_slect_step = 1 ;
	slect_move_cursor.now_slect_move = 0 ;
	slect_cursor_move_init(&slect_move_cursor); 		 			//光标位置初始化
	slect_cursor_move(cursor_default_mode,cursor_null);  			//初始化选择设置光标
	Buttons_Register(KEY_UP_TRG_NUMBER,Hmi_Enter_Menuconfig_Passwd_Input_Buttons_CB);
	Buttons_Register(KEY_ENTER_TRG_NUMBER,Hmi_Enter_Menuconfig_Passwd_Input_Buttons_CB);
	Buttons_Register(KEY_DOWN_TRG_NUMBER,Hmi_Enter_Menuconfig_Passwd_Input_Buttons_CB);
}
static void Enter_Menuconfig_Passwd_Input_Page_Exit(void){

}
static void Enter_Menuconfig_Passwd_Input_Page_Task(void){
	if(check_time_arrive(AUTO_EXIT_SETS_PAGE_TO_MAIN_PAGE_TIMER_NUMBER,enter_menuconfig_passwd_menu_list_pararm_t.system_para_t.AutoExitSetsPageTime*1000)){
		Back_Main_Page_Load();
	}
}


static void Hmi_Enter_Menuconfig_Passwd_Input_Buttons_CB(key_Input_Number_Typedef key_number ,Key_Trg_Even key_state){
	if(key_state == KEY_CLICK_ACTION){
		enter_menuconfig_passwd_menu_list_pararm_t.enter_menuconfig_passwd =user_parameter_adjustment(enter_menuconfig_passwd_menu_list_pararm_t.enter_menuconfig_passwd ,0,4,key_number,enter_menuconfig_passwd_menu_list_pararm_t.SetLoginPasswd_ShowCompensationDate_t);
	}
}


static void Enter_Menuconfig_Passwd_Confirm_Page_Load(void){
	type_slect_move_cursor slect_move_cursor;
	slect_move_cursor.dw_cursor_adderss = ENTER_MENUCONFIG_PASSWD_INTPUT_SELECT_CURSOR_VAR_ADDERSS ;
	slect_move_cursor.max_slect_move = 3 ;
	slect_move_cursor.min_slect_move = 0 ;
	slect_move_cursor.move_slect_step = 1 ;
	slect_move_cursor.now_slect_move = 0 ;
	slect_cursor_move_init(&slect_move_cursor);  //光标位置初始化
	slect_cursor_move(cursor_refresh_mode,cursor_null);  //关闭光标
	Buttons_UnRegister(KEY_UP_TRG_NUMBER);
	Buttons_UnRegister(KEY_ENTER_TRG_NUMBER);
	Buttons_UnRegister(KEY_DOWN_TRG_NUMBER);
	log_d("intput menuconfig passwd=%d",enter_menuconfig_passwd_menu_list_pararm_t.enter_menuconfig_passwd);

	if(enter_menuconfig_passwd_menu_list_pararm_t.enter_menuconfig_passwd == enter_menuconfig_passwd_menu_list_pararm_t.other_para_def_t.login_menuconfig_passwd){
		 Menu_ShortcutEnter(true, 1, 3); // 开机通过快捷菜单索引进入语言选择界面
	}else{
		dw_by_oneself_adderss_var_display( ENTER_MENUCONFIG_PASSWD_ERROR_WINDOW_VAR_ADDERSS , 1 ) ;
		Buttons_Register(KEY_ENTER_TRG_NUMBER,Enter_Passwd_Window_Buttons_CB);
	}
}
static void Enter_Menuconfig_Passwd_Confirm_Page_Exit(void){
	dw_by_oneself_adderss_var_display( ENTER_MENUCONFIG_PASSWD_ERROR_WINDOW_VAR_ADDERSS , 0 ) ;
}
static void Enter_Menuconfig_Passwd_Confirm_Page_Task(void){
	if(check_time_arrive(AUTO_EXIT_SETS_PAGE_TO_MAIN_PAGE_TIMER_NUMBER,enter_menuconfig_passwd_menu_list_pararm_t.system_para_t.AutoExitSetsPageTime*1000)){
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

static void Enter_Passwd_Window_Buttons_CB( key_Input_Number_Typedef key_number , Key_Trg_Even key_state){
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
