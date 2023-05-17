/*
 * hmi_sysCommunicate.c
 *
 *  Created on: 2023年3月22日
 *      Author: 好
 */
#define LOG_TAG    "hmi_SysCommunicate"
#include "../himi/sys/hmi_SysCommunicate.h"




/* 参数初始化*/
static void SystemMenuDateShow_Init(void);
/* 设置菜单显示效果 */
static void System_Communicate_SetMenu(  MenuShow_t *ptShowInfo);

/********************************************** 切换页面 - 系统通信-服务端IP设置页面  ***************************************************************/
static void System_Set_Communicate_Server_IP_Page_Load(void);
static void System_Set_Communicate_Server_IP_Page_Exit(void);
static void System_Set_Communicate_Server_IP_Page_Task(void);
/************* 输入参数- 系统通信-服务端IP 页面  *******************/
static void System_Set_Communicate_Server_IP_Input_Page_Load(void);
static void System_Set_Communicate_Server_IP_Input_Page_Exit(void);
static void System_Set_Communicate_Server_IP_Input_Page_Task(void);
static void System_Set_Communicate_Server_IP_Input_Buttons_CB(key_Input_Number_Typedef key_number ,Key_Trg_Even key_state);
/********* 保存设置参数- 系统通信-服务端IP ******************/
static void System_Set_Communicate_Server_IP_Enter_Page_Load(void);
static void System_Set_Communicate_Server_IP_Enter_Page_Exit(void);
static void System_Set_Communicate_Server_IP_Enter_Page_Task(void);

/********************************************** 切换页面 - 系统通信-通信端口设置页面  ***************************************************************/
static void System_Set_Communicate_Port_Page_Load(void);
static void System_Set_Communicate_Port_Page_Exit(void);
static void System_Set_Communicate_Port_Page_Task(void);

/************* 输入参数- 系统通信-通信端口 页面  *******************/
static void System_Communicate_Port_Input_Page_Load(void);
static void System_Communicate_Port_Input_Page_Exit(void);
static void System_Communicate_Port_Input_Page_Task(void);
static void System_Communicate_Port_Input_Buttons_CB(key_Input_Number_Typedef key_number ,Key_Trg_Even key_state);
/********* 保存设置参数- 系统通信-通信端口  ******************/
static void System_Communicate_Port_Enter_Page_Load(void);
static void System_Communicate_Port_Enter_Page_Exit(void);
static void System_Communicate_Port_Enter_Page_Task(void);
/********************************************** 切换页面 - 系统通信-登录ID值页面  ***************************************************************/
static void System_Set_Communicate_ID_Page_Load(void);
static void System_Set_Communicate_ID_Page_Exit(void);
static void System_Set_Communicate_ID_Page_Task(void);
/************* 输入参数- 系统通信-登录ID页面  *******************/
static void System_Communicate_ID_Input_Page_Load(void);
static void System_Communicate_ID_Input_Page_Exit(void);
static void System_Communicate_ID_Input_Page_Task(void);
static void System_Communicate_ID_Input_Buttons_CB(key_Input_Number_Typedef key_number ,Key_Trg_Even key_state);
/********* 保存设置参数- 系统通信-登录ID  ******************/
static void System_Communicate_ID_Enter_Page_Load(void);
static void System_Communicate_ID_Enter_Page_Exit(void);
static void System_Communicate_ID_Enter_Page_Task(void);
/********************************************** 切换页面 - 系统通信-系统登录密码页面  ***************************************************************/
static void System_Set_Communicate_Passwd_Page_Load(void);
static void System_Set_Communicate_Passwd_Page_Exit(void);
static void System_Set_Communicate_Passwd_Page_Task(void);
/************* 输入参数- 系统通信-系统登录密码设置页面  *******************/
static void System_Communicate_Passwd_Input_Page_Load(void);
static void System_Communicate_Passwd_Input_Page_Exit(void);
static void System_Communicate_Passwd_Input_Page_Task(void);
static void System_Communicate_Passwd_Input_Buttons_CB(key_Input_Number_Typedef key_number ,Key_Trg_Even key_state);
/********* 保存设置参数- 系统通信-系统登录密码设置参数  ******************/
static void System_Communicate_Passwd_Enter_Page_Load(void);
static void System_Communicate_Passwd_Enter_Page_Exit(void);
static void System_Communicate_Passwd_Enter_Page_Task(void);

/************* 系统参数-系统通信公共回调函数  *******************/
static void System_Communicate_Slcet_Set_Buttons_CB( key_Input_Number_Typedef key_number , Key_Trg_Even key_state);
static void System_Communicate_Enter_Window_Buttons_CB( key_Input_Number_Typedef key_number , Key_Trg_Even key_state);


struct set_system_communicate_menu_list_pararm{
	int auto_exit_sets_page_to_main_time ;  //自动返回时间
	system_para_def system_para ;
	mqtt_ip_tcp_def mqtt_ip_parameter_t ;
	mqtt_port_tcp_def   mqtt_port_para;
	mqtt_login_def mqtt_login_para;

	int login_id ;
	int login_passwd ;

	int server_ip_addr[4] ;

	ShownMenuDate SY_ShowCommunicateServerIPDateFun_t[4];
	ShownMenuDate SY_ShowCommunicatePortDateFun_t;
	ShownMenuDate SY_ShowCommunicateIDDateFun_t;
	ShownMenuDate SY_ShowCommunicatePasswdFun_t;
};


static struct set_system_communicate_menu_list_pararm set_system_communicate_pararm_t ;


/******************系统参数-系统通信设置页面选择*********************************/

/* 系统通信选择设置菜单*/
static MenuList_t System_Communicate_Set_Menu_Table[] =
{
	{"服务端IP设置", NULL, System_Set_Communicate_Server_IP_Page_Load, System_Set_Communicate_Server_IP_Page_Exit, System_Set_Communicate_Server_IP_Page_Task, NULL},

    {"系统通信端口设置", NULL, System_Set_Communicate_Port_Page_Load, System_Set_Communicate_Port_Page_Exit, System_Set_Communicate_Port_Page_Task, NULL},

    {"系统登录ID设置", NULL, System_Set_Communicate_ID_Page_Load, System_Set_Communicate_ID_Page_Exit, System_Set_Communicate_ID_Page_Task, NULL},

    {"系统登录密码设置", NULL, System_Set_Communicate_Passwd_Page_Load, System_Set_Communicate_Passwd_Page_Exit, System_Set_Communicate_Passwd_Page_Task, NULL},

    {"返回上级菜单", NULL,  Return_Previous_Menu_Page_Load, NULL, NULL, NULL},

    {"返回主页面", NULL,  Back_Main_Page_Load,   NULL,   NULL, NULL},
};

/* 参数初始化*/
static void SystemMenuDateShow_Init(void){
	int *server_ip_tmp = NULL ;
	system_para_def system_para_t ;

	set_system_communicate_pararm_t.SY_ShowCommunicateServerIPDateFun_t[0] = show_system_server_ip_addr1_intput_date ;
	set_system_communicate_pararm_t.SY_ShowCommunicateServerIPDateFun_t[1] = show_system_server_ip_addr2_intput_date ;
	set_system_communicate_pararm_t.SY_ShowCommunicateServerIPDateFun_t[2] = show_system_server_ip_addr3_intput_date ;
	set_system_communicate_pararm_t.SY_ShowCommunicateServerIPDateFun_t[3] = show_system_server_ip_addr4_intput_date ;

	set_system_communicate_pararm_t.SY_ShowCommunicatePortDateFun_t = show_system_communicate_port_date ;
	set_system_communicate_pararm_t.SY_ShowCommunicateIDDateFun_t = show_system_login_id_date ;
	set_system_communicate_pararm_t.SY_ShowCommunicatePasswdFun_t = show_system_login_passwd_date ;

	read_saveenv_cjson_mqttip_parameter(&set_system_communicate_pararm_t.mqtt_ip_parameter_t);
	server_ip_tmp = ip_str_analysis_number(set_system_communicate_pararm_t.mqtt_ip_parameter_t.Host);
	for(uint8_t i=0;i<4;i++){
		set_system_communicate_pararm_t.server_ip_addr[i]=server_ip_tmp[i];
		set_system_communicate_pararm_t.SY_ShowCommunicateServerIPDateFun_t[i](set_system_communicate_pararm_t.server_ip_addr[i]);
	}

	read_saveenv_cjson_system_parameter(&system_para_t);
	set_system_communicate_pararm_t.auto_exit_sets_page_to_main_time = system_para_t.AutoExitSetsPageTime;

	read_saveenv_cjson_mqttport_parameter(&set_system_communicate_pararm_t.mqtt_port_para);
	read_saveenv_cjson_mqttlogin_parameter(&set_system_communicate_pararm_t.mqtt_login_para);

	char* str = strrchr(set_system_communicate_pararm_t.mqtt_login_para.username,'-');
	if(str == NULL ){
		log_e("username error \r");
		return ;
	}
	set_system_communicate_pararm_t.login_id =atoi((str+1)); //字符串ID转数字ID
	log_d("login_id=%d",set_system_communicate_pararm_t.login_id);
	read_saveenv_cjson_mqttlogin_parameter(&set_system_communicate_pararm_t.mqtt_login_para);
	set_system_communicate_pararm_t.login_passwd =atoi(set_system_communicate_pararm_t.mqtt_login_para.password); //字符串ID转数字ID
}


/* 设置菜单显示效果 */
static void System_Communicate_SetMenu(  MenuShow_t *ptShowInfo){
	show_refresh_time();
	show_eth_connect_state();
}
/********************************************** 切换页面 - 系统通信设置页面  ***************************************************************/
void System_Communicate_Setting_Page_Load(void){

	log_d("System_Communicate_Setting_Page_Load ");
	type_slect_move_cursor slect_move_cursor;

	slect_move_cursor.dw_cursor_adderss = SYSTEM_SYS_COMMUNICATE_SELECT_CURSOR_ADDERSS ;
	slect_move_cursor.max_slect_move = 5 ;
	slect_move_cursor.min_slect_move = 0 ;
	slect_move_cursor.move_slect_step = 1 ;
	slect_move_cursor.now_slect_move = 0 ;
	slect_cursor_move_init(&slect_move_cursor);  //光标位置初始化
	dw_show_switching_pages(PAGE_SYSTEM_COMMUNICATE_SETTING_NUMBER); //切换页面
	slect_cursor_move(cursor_default_mode,cursor_null);  //初始化选择设置光标
	Buttons_Register(KEY_UP_TRG_NUMBER,System_Communicate_Slcet_Set_Buttons_CB);
	Buttons_Register(KEY_ENTER_TRG_NUMBER,System_Communicate_Slcet_Set_Buttons_CB);
	Buttons_Register(KEY_DOWN_TRG_NUMBER,System_Communicate_Slcet_Set_Buttons_CB);
	SystemMenuDateShow_Init();
	//clear_time_cnt(AUTO_EXIT_SETS_PAGE_TO_MAIN_PAGE_TIMER_NUMBER);
	Menu_Bind(System_Communicate_Set_Menu_Table, GET_MENU_NUM(System_Communicate_Set_Menu_Table), System_Communicate_SetMenu);
}

void System_Communicate_Setting_Page_Exit(void){
	//clear_time_cnt(AUTO_EXIT_SETS_PAGE_TO_MAIN_PAGE_TIMER_NUMBER);
}

void System_Communicate_Setting_Page_Task(void){
	if(check_time_arrive(AUTO_EXIT_SETS_PAGE_TO_MAIN_PAGE_TIMER_NUMBER,set_system_communicate_pararm_t.auto_exit_sets_page_to_main_time*1000)){
		Back_Main_Page_Load();
	}
}





/********************************************** 切换页面 - 系统通信-服务端IP设置页面  ***************************************************************/
/* 系统通信-服务端IP设置菜单 */
static MenuList_t System_Communicate_Server_IP_Set_Menu_Table[] =
{
	{"用户输入框", NULL, System_Set_Communicate_Server_IP_Input_Page_Load, System_Set_Communicate_Server_IP_Input_Page_Exit, System_Set_Communicate_Server_IP_Input_Page_Task, NULL},

    {"保存设置参数", NULL, System_Set_Communicate_Server_IP_Enter_Page_Load, System_Set_Communicate_Server_IP_Enter_Page_Exit, System_Set_Communicate_Server_IP_Enter_Page_Task, NULL},

    {"返回上级菜单", NULL,  Return_Previous_Menu_Page_Load, NULL, NULL, NULL},

    {"返回主页面", NULL,  Back_Main_Page_Load,   NULL,   NULL, NULL},
};

static void System_Set_Communicate_Server_IP_Page_Load(void){
	type_slect_move_cursor slect_move_cursor;

	slect_move_cursor.dw_cursor_adderss = SYSTEM_SYS_COMMUNICATE_SERVER_IP_INTPUT_SELECT_CURSOR_VAR_ADDERSS ;
	slect_move_cursor.max_slect_move = 11 ;
	slect_move_cursor.min_slect_move = 0 ;
	slect_move_cursor.move_slect_step = 1 ;
	slect_move_cursor.now_slect_move = 0 ;
	slect_cursor_move_init(&slect_move_cursor);  		//光标位置初始化
	slect_cursor_move(cursor_refresh_mode,cursor_null);  //关闭输入指示光标


	slect_move_cursor.dw_cursor_adderss = SYSTEM_SYS_COMMUNICATE_SERVER_IP_SELECT_CURSOR_ADDERSS ;
	slect_move_cursor.max_slect_move = 3 ;
	slect_move_cursor.min_slect_move = 0 ;
	slect_move_cursor.move_slect_step = 1 ;
	slect_move_cursor.now_slect_move = 0 ;
	slect_cursor_move_init(&slect_move_cursor); 		 			//光标位置初始化
	slect_cursor_move(cursor_default_mode,cursor_null);  			//初始化选择设置光标


	dw_show_switching_pages(PAGE_SYSTEM_COMMUNICATE_SERVER_IP_SETTING_NUMBER); //切换页面
	Buttons_Register(KEY_UP_TRG_NUMBER,System_Communicate_Slcet_Set_Buttons_CB);
	Buttons_Register(KEY_ENTER_TRG_NUMBER,System_Communicate_Slcet_Set_Buttons_CB);
	Buttons_Register(KEY_DOWN_TRG_NUMBER,System_Communicate_Slcet_Set_Buttons_CB);
	Menu_Bind(System_Communicate_Server_IP_Set_Menu_Table, GET_MENU_NUM(System_Communicate_Server_IP_Set_Menu_Table), System_Communicate_SetMenu);
}
static void System_Set_Communicate_Server_IP_Page_Exit(void){
	//clear_time_cnt(AUTO_EXIT_SETS_PAGE_TO_MAIN_PAGE_TIMER_NUMBER);
}
static void System_Set_Communicate_Server_IP_Page_Task(void){
	if(check_time_arrive(AUTO_EXIT_SETS_PAGE_TO_MAIN_PAGE_TIMER_NUMBER,set_system_communicate_pararm_t.auto_exit_sets_page_to_main_time*1000)){
		Back_Main_Page_Load();
		//clear_time_cnt(AUTO_EXIT_SETS_PAGE_TO_MAIN_PAGE_TIMER_NUMBER);
	}
}
/************* IP地址输入参数- 自动返回主页值页面  *******************/
static void System_Set_Communicate_Server_IP_Input_Page_Load(void){
	type_slect_move_cursor slect_move_cursor;

	slect_move_cursor.dw_cursor_adderss = SYSTEM_SYS_COMMUNICATE_SERVER_IP_SELECT_CURSOR_ADDERSS ;
	slect_move_cursor.max_slect_move = 3 ;
	slect_move_cursor.min_slect_move = 0 ;
	slect_move_cursor.move_slect_step = 1 ;
	slect_move_cursor.now_slect_move = 0 ;
	slect_cursor_move_init(&slect_move_cursor);  //光标位置初始化
	slect_cursor_move(cursor_refresh_mode,cursor_null);  //关闭选择设置光标

	slect_move_cursor.dw_cursor_adderss = SYSTEM_SYS_COMMUNICATE_SERVER_IP_INTPUT_SELECT_CURSOR_VAR_ADDERSS ;
	slect_move_cursor.max_slect_move = 11 ;
	slect_move_cursor.min_slect_move = 0 ;
	slect_move_cursor.move_slect_step = 1 ;
	slect_move_cursor.now_slect_move = 0 ;
	slect_cursor_move_init(&slect_move_cursor);  //光标位置初始化
	slect_cursor_move(cursor_default_mode,cursor_null);  //显示初始化输入指示光标位置

	Buttons_Register(KEY_UP_TRG_NUMBER,System_Set_Communicate_Server_IP_Input_Buttons_CB);
	Buttons_Register(KEY_ENTER_TRG_NUMBER,System_Set_Communicate_Server_IP_Input_Buttons_CB);
	Buttons_Register(KEY_DOWN_TRG_NUMBER,System_Set_Communicate_Server_IP_Input_Buttons_CB);
}

static void System_Set_Communicate_Server_IP_Input_Page_Exit(void){
	//clear_time_cnt(AUTO_EXIT_SETS_PAGE_TO_MAIN_PAGE_TIMER_NUMBER);
}

static void System_Set_Communicate_Server_IP_Input_Page_Task(void){
	if(check_time_arrive(AUTO_EXIT_SETS_PAGE_TO_MAIN_PAGE_TIMER_NUMBER,set_system_communicate_pararm_t.auto_exit_sets_page_to_main_time*1000)){
		Back_Main_Page_Load();
	}
}


static void System_Set_Communicate_Server_IP_Input_Buttons_CB(key_Input_Number_Typedef key_number ,Key_Trg_Even key_state){
	static uint8_t User_Trg_Buttons_Cnts = 0 ;

	if(key_state == KEY_CLICK_ACTION){
		//clear_time_cnt(AUTO_EXIT_SETS_PAGE_TO_MAIN_PAGE_TIMER_NUMBER);
		if(key_number ==KEY_ENTER_TRG_NUMBER ){
			User_Trg_Buttons_Cnts++ ;
			if(User_Trg_Buttons_Cnts > 11 ){
				User_Trg_Buttons_Cnts = 0 ;
				clearn_Temp_Compensation_Slcet_buttons_cnt();
				log_d("clearn User_Trg_Buttons_Cnts !");
				Menu_Exit(true);
				return ;
			}
		}
		for(uint8_t i=0;i<4;i++){
			if((User_Trg_Buttons_Cnts >=i*3) &&(User_Trg_Buttons_Cnts< i*3+3) ){
				set_system_communicate_pararm_t.server_ip_addr[i]=user_parameter_adjustment(set_system_communicate_pararm_t.server_ip_addr[i],false,4,key_number,set_system_communicate_pararm_t.SY_ShowCommunicateServerIPDateFun_t[i]);
			}
		}
		if(key_number ==KEY_ENTER_TRG_NUMBER ){
			if( (User_Trg_Buttons_Cnts %3) ==0 ){
				clearn_Temp_Compensation_Slcet_buttons_cnt();
			}
		}

	}
}


/********* 保存设置参数- 自动返回主页时间值  ******************/
static void System_Set_Communicate_Server_IP_Enter_Page_Load(void){
	uint8_t ip_setting_judge=0;

	int ret = -1 ;
	type_slect_move_cursor slect_move_cursor;

	slect_move_cursor.dw_cursor_adderss = SYSTEM_SYS_COMMUNICATE_SERVER_IP_INTPUT_SELECT_CURSOR_VAR_ADDERSS ;
	slect_move_cursor.max_slect_move = 11 ;
	slect_move_cursor.min_slect_move = 0 ;
	slect_move_cursor.move_slect_step = 1 ;
	slect_move_cursor.now_slect_move = 0 ;
	slect_cursor_move_init(&slect_move_cursor);  		//光标位置初始化
	slect_cursor_move(cursor_refresh_mode,cursor_null);  //关闭输入指示光标

	slect_move_cursor.dw_cursor_adderss = SYSTEM_SYS_COMMUNICATE_SERVER_IP_SELECT_CURSOR_ADDERSS ;
	slect_move_cursor.max_slect_move = 3 ;
	slect_move_cursor.min_slect_move = 0 ;
	slect_move_cursor.move_slect_step = 1 ;
	slect_move_cursor.now_slect_move = 0 ;
	slect_cursor_move_init(&slect_move_cursor);  		//光标位置初始化
	slect_cursor_move(cursor_refresh_mode,cursor_null);  //关闭输入指示光标

	Buttons_UnRegister(KEY_UP_TRG_NUMBER);
	Buttons_UnRegister(KEY_ENTER_TRG_NUMBER);
	Buttons_UnRegister(KEY_DOWN_TRG_NUMBER);

	//显示等待窗口
	dw_input_parameter_hint_window( 1 ,SYSTEM_SYS_COMMUNICATE_SERVER_IP_ADDR_WAIT_WINDOW_VAR_ADDERSS,SYSTEM_SYS_COMMUNICATE_SERVER_IP_ADDR_SUCCESS_WINDOW_VAR_ADDERSS,SYSTEM_SYS_COMMUNICATE_SERVER_IP_ADDR_ERROR_WINDOW_VAR_ADDERSS);
	for(uint8_t i=0;i<4;i++){
		if(set_system_communicate_pararm_t.server_ip_addr[i]>255){
			ip_setting_judge = 1;
			break ;
		}
	}
	if(!ip_setting_judge){
		 int *server_ip_tmp = NULL ;
		read_saveenv_cjson_mqttip_parameter(&set_system_communicate_pararm_t.mqtt_ip_parameter_t);
		server_ip_tmp = ip_str_analysis_number(set_system_communicate_pararm_t.mqtt_ip_parameter_t.Host);
		sprintf(set_system_communicate_pararm_t.mqtt_ip_parameter_t.Host,"%03d.%03d.%03d.%03d", \
				set_system_communicate_pararm_t.server_ip_addr[0],set_system_communicate_pararm_t.server_ip_addr[1],\
				set_system_communicate_pararm_t.server_ip_addr[2],set_system_communicate_pararm_t.server_ip_addr[3]) ;
		ret = mqttip_amend_config("Host",set_system_communicate_pararm_t.mqtt_ip_parameter_t.Host);
		if( !ret){
			 //显示成功窗口
			dw_input_parameter_hint_window(2 ,SYSTEM_SYS_COMMUNICATE_SERVER_IP_ADDR_WAIT_WINDOW_VAR_ADDERSS,SYSTEM_SYS_COMMUNICATE_SERVER_IP_ADDR_SUCCESS_WINDOW_VAR_ADDERSS,SYSTEM_SYS_COMMUNICATE_SERVER_IP_ADDR_ERROR_WINDOW_VAR_ADDERSS);
		}else{
			//显示错误窗口
			dw_input_parameter_hint_window( 3 ,SYSTEM_SYS_COMMUNICATE_SERVER_IP_ADDR_WAIT_WINDOW_VAR_ADDERSS,SYSTEM_SYS_COMMUNICATE_SERVER_IP_ADDR_SUCCESS_WINDOW_VAR_ADDERSS,SYSTEM_SYS_COMMUNICATE_SERVER_IP_ADDR_ERROR_WINDOW_VAR_ADDERSS);
		}
		for(uint8_t i=0;i<4;i++){
			if( server_ip_tmp[i] ==set_system_communicate_pararm_t.server_ip_addr[i] ){
				Set_Mqtt_Client_System_t.mqtt_host_change_flag = 0 ;
				log_d("set mqtt server ip no change .");
			}else{
				Set_Mqtt_Client_System_t.mqtt_host_change_flag = 1 ;
				log_d("set mqtt server ip  change .");
				break ;
			}
		}
	}else{
		//显示错误窗口
		dw_input_parameter_hint_window( 3 ,SYSTEM_SYS_COMMUNICATE_SERVER_IP_ADDR_WAIT_WINDOW_VAR_ADDERSS,SYSTEM_SYS_COMMUNICATE_SERVER_IP_ADDR_SUCCESS_WINDOW_VAR_ADDERSS,SYSTEM_SYS_COMMUNICATE_SERVER_IP_ADDR_ERROR_WINDOW_VAR_ADDERSS);
		ip_setting_judge = 0 ;

	}
	Buttons_Register(KEY_ENTER_TRG_NUMBER,System_Communicate_Enter_Window_Buttons_CB);
}

static void System_Set_Communicate_Server_IP_Enter_Page_Exit(void){
		//清除窗口
		dw_input_parameter_hint_window( 4,SYSTEM_SYS_COMMUNICATE_SERVER_IP_ADDR_WAIT_WINDOW_VAR_ADDERSS,SYSTEM_SYS_COMMUNICATE_SERVER_IP_ADDR_SUCCESS_WINDOW_VAR_ADDERSS,SYSTEM_SYS_COMMUNICATE_SERVER_IP_ADDR_ERROR_WINDOW_VAR_ADDERSS);
	//clear_time_cnt(AUTO_EXIT_SETS_PAGE_TO_MAIN_PAGE_TIMER_NUMBER);
}

static void System_Set_Communicate_Server_IP_Enter_Page_Task(void){
	if(check_time_arrive(AUTO_EXIT_SETS_PAGE_TO_MAIN_PAGE_TIMER_NUMBER,set_system_communicate_pararm_t.auto_exit_sets_page_to_main_time*1000)){
		Back_Main_Page_Load();
		//clear_time_cnt(AUTO_EXIT_SETS_PAGE_TO_MAIN_PAGE_TIMER_NUMBER);
	}
}



/********************************************** 切换页面 - 系统通信-通信端口设置页面  ***************************************************************/
/* 系统通信-通信端口设置菜单 */
static MenuList_t System_Communicate_Port_Set_Menu_Table[] =
{
	{"用户输入框", NULL, System_Communicate_Port_Input_Page_Load, System_Communicate_Port_Input_Page_Exit, System_Communicate_Port_Input_Page_Task, NULL},

    {"保存设置参数", NULL, System_Communicate_Port_Enter_Page_Load, System_Communicate_Port_Enter_Page_Exit, System_Communicate_Port_Enter_Page_Task, NULL},

    {"返回上级菜单", NULL,  Return_Previous_Menu_Page_Load, NULL, NULL, NULL},

    {"返回主页面", NULL,  Back_Main_Page_Load,   NULL,   NULL, NULL},
};

static void System_Set_Communicate_Port_Page_Load(void){
	type_slect_move_cursor slect_move_cursor;

	slect_move_cursor.dw_cursor_adderss = SYSTEM_SYS_COMMUNICATE_PORT_INTPUT_SELECT_CURSOR_VAR_ADDERSS ;
	slect_move_cursor.max_slect_move = 3 ;
	slect_move_cursor.min_slect_move = 0 ;
	slect_move_cursor.move_slect_step = 1 ;
	slect_move_cursor.now_slect_move = 0 ;
	slect_cursor_move_init(&slect_move_cursor);  //光标位置初始化
	slect_cursor_move(cursor_refresh_mode,cursor_null);  //关闭光标

	slect_move_cursor.dw_cursor_adderss = SYSTEM_SYS_COMMUNICATE_PORT_SELECT_CURSOR_ADDERSS ;
	slect_move_cursor.max_slect_move = 3 ;
	slect_move_cursor.min_slect_move = 0 ;
	slect_move_cursor.move_slect_step = 1 ;
	slect_move_cursor.now_slect_move = 0 ;
	slect_cursor_move_init(&slect_move_cursor); 		 			//光标位置初始化
	slect_cursor_move(cursor_default_mode,cursor_null);  			//初始化选择设置光标

	set_system_communicate_pararm_t.SY_ShowCommunicatePortDateFun_t(set_system_communicate_pararm_t.mqtt_port_para.port); //显示端口

	dw_show_switching_pages(PAGE_SYSTEM_COMMUNICATE_PORT_SETTING_NUMBER); //切换页面
	Buttons_Register(KEY_UP_TRG_NUMBER,System_Communicate_Slcet_Set_Buttons_CB);
	Buttons_Register(KEY_ENTER_TRG_NUMBER,System_Communicate_Slcet_Set_Buttons_CB);
	Buttons_Register(KEY_DOWN_TRG_NUMBER,System_Communicate_Slcet_Set_Buttons_CB);
	Menu_Bind(System_Communicate_Port_Set_Menu_Table, GET_MENU_NUM(System_Communicate_Port_Set_Menu_Table), System_Communicate_SetMenu);
}
static void System_Set_Communicate_Port_Page_Exit(void){
	//clear_time_cnt(AUTO_EXIT_SETS_PAGE_TO_MAIN_PAGE_TIMER_NUMBER);
}
static void System_Set_Communicate_Port_Page_Task(void){
	if(check_time_arrive(AUTO_EXIT_SETS_PAGE_TO_MAIN_PAGE_TIMER_NUMBER,set_system_communicate_pararm_t.auto_exit_sets_page_to_main_time*1000)){
		Back_Main_Page_Load();
	}
}
/************* 输入参数- 系统通信-通信端口 页面  *******************/
static void System_Communicate_Port_Input_Page_Load(void){
	type_slect_move_cursor slect_move_cursor;

	slect_move_cursor.dw_cursor_adderss = SYSTEM_SYS_COMMUNICATE_PORT_SELECT_CURSOR_ADDERSS ;
	slect_move_cursor.max_slect_move = 3 ;
	slect_move_cursor.min_slect_move = 0 ;
	slect_move_cursor.move_slect_step = 1 ;
	slect_move_cursor.now_slect_move = 0 ;
	slect_cursor_move_init(&slect_move_cursor);  //光标位置初始化
	slect_cursor_move(cursor_refresh_mode,cursor_null);  //关闭光标

	slect_move_cursor.dw_cursor_adderss = SYSTEM_SYS_COMMUNICATE_PORT_INTPUT_SELECT_CURSOR_VAR_ADDERSS ;
	slect_move_cursor.max_slect_move = 3 ;
	slect_move_cursor.min_slect_move = 0 ;
	slect_move_cursor.move_slect_step = 1 ;
	slect_move_cursor.now_slect_move = 0 ;
	slect_cursor_move_init(&slect_move_cursor);  //光标位置初始化
	slect_cursor_move(cursor_default_mode,cursor_null);  			//初始化选择设置光标

	Buttons_Register(KEY_UP_TRG_NUMBER,System_Communicate_Port_Input_Buttons_CB);
	Buttons_Register(KEY_ENTER_TRG_NUMBER,System_Communicate_Port_Input_Buttons_CB);
	Buttons_Register(KEY_DOWN_TRG_NUMBER,System_Communicate_Port_Input_Buttons_CB);
}

static void System_Communicate_Port_Input_Page_Exit(void){
	//clear_time_cnt(AUTO_EXIT_SETS_PAGE_TO_MAIN_PAGE_TIMER_NUMBER);
	//清除窗口
	dw_input_parameter_hint_window( 0 ,SYSTEM_RUN_TIME_ADJ_WAIT_WINDOW_VAR_ADDERSS,SYSTEM_RUN_TIME_ADJ_SUCCESS_WINDOW_VAR_ADDERSS,SYSTEM_RUN_TIME_ADJ_ERROR_WINDOW_VAR_ADDERSS);

}

static void System_Communicate_Port_Input_Page_Task(void){
	if(check_time_arrive(AUTO_EXIT_SETS_PAGE_TO_MAIN_PAGE_TIMER_NUMBER,set_system_communicate_pararm_t.auto_exit_sets_page_to_main_time*1000)){
		Back_Main_Page_Load();
	}
}


static void System_Communicate_Port_Input_Buttons_CB(key_Input_Number_Typedef key_number ,Key_Trg_Even key_state){
	if(key_state == KEY_CLICK_ACTION){
		//clear_time_cnt(AUTO_EXIT_SETS_PAGE_TO_MAIN_PAGE_TIMER_NUMBER);
		set_system_communicate_pararm_t.mqtt_port_para.port=user_parameter_adjustment(set_system_communicate_pararm_t.mqtt_port_para.port, \
			false,4,key_number,set_system_communicate_pararm_t.SY_ShowCommunicatePortDateFun_t);
	}
}

/********* 保存设置参数- 系统通信-通信端口  ******************/
static void System_Communicate_Port_Enter_Page_Load(void){
	int ret = -1 ;
	type_slect_move_cursor slect_move_cursor;
	slect_move_cursor.dw_cursor_adderss = SYSTEM_SYS_COMMUNICATE_PORT_SELECT_CURSOR_ADDERSS ;
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
	mqtt_port_tcp_def   mqtt_port_para_t;
	read_saveenv_cjson_mqttport_parameter(&mqtt_port_para_t); //读取之前系统保存的端口号
	dw_input_parameter_hint_window( 1 ,SYSTEM_SYS_COMMUNICATE_PORT_WAIT_WINDOW_VAR_ADDERSS,SYSTEM_SYS_COMMUNICATE_PORT_SUCCESS_WINDOW_VAR_ADDERSS,SYSTEM_SYS_COMMUNICATE_PORT_ERROR_WINDOW_VAR_ADDERSS);
	ret = mqttport_amend_config("Port",set_system_communicate_pararm_t.mqtt_port_para.port);
	if( !ret){
		 //显示成功窗口
		dw_input_parameter_hint_window(2,SYSTEM_SYS_COMMUNICATE_PORT_WAIT_WINDOW_VAR_ADDERSS,SYSTEM_SYS_COMMUNICATE_PORT_SUCCESS_WINDOW_VAR_ADDERSS,SYSTEM_SYS_COMMUNICATE_PORT_ERROR_WINDOW_VAR_ADDERSS);
	}else{
		//显示错误窗口
		dw_input_parameter_hint_window( 3,SYSTEM_SYS_COMMUNICATE_PORT_WAIT_WINDOW_VAR_ADDERSS,SYSTEM_SYS_COMMUNICATE_PORT_SUCCESS_WINDOW_VAR_ADDERSS,SYSTEM_SYS_COMMUNICATE_PORT_ERROR_WINDOW_VAR_ADDERSS);
	}
	if(mqtt_port_para_t.port == set_system_communicate_pararm_t.mqtt_port_para.port){
		Set_Mqtt_Client_System_t.mqtt_port_change_flag = 0 ;
		log_d("mqtt port no change .");
	}else{
		Set_Mqtt_Client_System_t.mqtt_port_change_flag = 1 ;
		log_d("mqtt port change .");
	}
	Buttons_Register(KEY_ENTER_TRG_NUMBER,System_Communicate_Enter_Window_Buttons_CB);
}

static void System_Communicate_Port_Enter_Page_Exit(void){
	//清除窗口
	dw_input_parameter_hint_window( 0 ,SYSTEM_SYS_COMMUNICATE_PORT_WAIT_WINDOW_VAR_ADDERSS,SYSTEM_SYS_COMMUNICATE_PORT_SUCCESS_WINDOW_VAR_ADDERSS,SYSTEM_SYS_COMMUNICATE_PORT_ERROR_WINDOW_VAR_ADDERSS);
	//clear_time_cnt(AUTO_EXIT_SETS_PAGE_TO_MAIN_PAGE_TIMER_NUMBER);
}

static void System_Communicate_Port_Enter_Page_Task(void){
	if(check_time_arrive(AUTO_EXIT_SETS_PAGE_TO_MAIN_PAGE_TIMER_NUMBER,set_system_communicate_pararm_t.auto_exit_sets_page_to_main_time*1000)){
		Back_Main_Page_Load();
	}
}

/********************************************** 切换页面 - 系统通信-登录ID值页面  ***************************************************************/
/* 登录ID菜单 */
static MenuList_t System_Login_ID_Menu_Table[] =
{
	{"参数输入框", NULL, System_Communicate_ID_Input_Page_Load, System_Communicate_ID_Input_Page_Exit, System_Communicate_ID_Input_Page_Task, NULL},

    {"保存设置参数", NULL, System_Communicate_ID_Enter_Page_Load, System_Communicate_ID_Enter_Page_Exit, System_Communicate_ID_Enter_Page_Task, NULL},

    {"返回上级菜单", NULL,  Return_Previous_Menu_Page_Load, NULL, NULL, NULL},

    {"返回主页面", NULL,  Back_Main_Page_Load,   NULL,   NULL, NULL},
};

static void System_Set_Communicate_ID_Page_Load(void){
	type_slect_move_cursor slect_move_cursor;

	slect_move_cursor.dw_cursor_adderss = SYSTEM_SYS_COMMUNICATE_ID_INTPUT_SELECT_CURSOR_VAR_ADDERSS ;
	slect_move_cursor.max_slect_move = 3 ;
	slect_move_cursor.min_slect_move = 0 ;
	slect_move_cursor.move_slect_step = 1 ;
	slect_move_cursor.now_slect_move = 0 ;
	slect_cursor_move_init(&slect_move_cursor);  		//光标位置初始化
	slect_cursor_move(cursor_refresh_mode,cursor_null);  //关闭输入指示光标

	slect_move_cursor.dw_cursor_adderss = SYSTEM_SYS_COMMUNICATE_ID_SELECT_CURSOR_ADDERSS ;
	slect_move_cursor.max_slect_move = 3 ;
	slect_move_cursor.min_slect_move = 0 ;
	slect_move_cursor.move_slect_step = 1 ;
	slect_move_cursor.now_slect_move = 0 ;
	slect_cursor_move_init(&slect_move_cursor); 		 			//光标位置初始化
	slect_cursor_move(cursor_default_mode,cursor_null);  			//初始化选择设置光标

	set_system_communicate_pararm_t.SY_ShowCommunicateIDDateFun_t(set_system_communicate_pararm_t.login_id);  //显示登录ID
	dw_show_switching_pages(PAGE_SYSTEM_COMMUNICATE_ID_SETTING_NUMBER); //切换页面

	Buttons_Register(KEY_UP_TRG_NUMBER,System_Communicate_Slcet_Set_Buttons_CB);
	Buttons_Register(KEY_ENTER_TRG_NUMBER,System_Communicate_Slcet_Set_Buttons_CB);
	Buttons_Register(KEY_DOWN_TRG_NUMBER,System_Communicate_Slcet_Set_Buttons_CB);
	Menu_Bind(System_Login_ID_Menu_Table, GET_MENU_NUM(System_Login_ID_Menu_Table), System_Communicate_SetMenu);
}
static void System_Set_Communicate_ID_Page_Exit(void){
	//clear_time_cnt(AUTO_EXIT_SETS_PAGE_TO_MAIN_PAGE_TIMER_NUMBER);
}
static void System_Set_Communicate_ID_Page_Task(void){
	if(check_time_arrive(AUTO_EXIT_SETS_PAGE_TO_MAIN_PAGE_TIMER_NUMBER,set_system_communicate_pararm_t.auto_exit_sets_page_to_main_time*1000)){
		Back_Main_Page_Load();
	}
}
/************* 输入参数- 系统通信-登录ID页面  *******************/
static void System_Communicate_ID_Input_Page_Load(void){
	type_slect_move_cursor slect_move_cursor;

	slect_move_cursor.dw_cursor_adderss = SYSTEM_SYS_COMMUNICATE_ID_SELECT_CURSOR_ADDERSS ;
	slect_move_cursor.max_slect_move = 3 ;
	slect_move_cursor.min_slect_move = 0 ;
	slect_move_cursor.move_slect_step = 1 ;
	slect_move_cursor.now_slect_move = 0 ;
	slect_cursor_move_init(&slect_move_cursor);  //光标位置初始化
	slect_cursor_move(cursor_refresh_mode,cursor_null);  //关闭选择设置光标

	slect_move_cursor.dw_cursor_adderss = SYSTEM_SYS_COMMUNICATE_ID_INTPUT_SELECT_CURSOR_VAR_ADDERSS ;
	slect_move_cursor.max_slect_move = 3 ;
	slect_move_cursor.min_slect_move = 0 ;
	slect_move_cursor.move_slect_step = 1 ;
	slect_move_cursor.now_slect_move = 0 ;
	slect_cursor_move_init(&slect_move_cursor);  //光标位置初始化
	slect_cursor_move(cursor_default_mode,cursor_null);  //显示初始化输入指示光标位置

	Buttons_Register(KEY_UP_TRG_NUMBER,System_Communicate_ID_Input_Buttons_CB);
	Buttons_Register(KEY_ENTER_TRG_NUMBER,System_Communicate_ID_Input_Buttons_CB);
	Buttons_Register(KEY_DOWN_TRG_NUMBER,System_Communicate_ID_Input_Buttons_CB);
}

static void System_Communicate_ID_Input_Page_Exit(void){
	//clear_time_cnt(AUTO_EXIT_SETS_PAGE_TO_MAIN_PAGE_TIMER_NUMBER);
}

static void System_Communicate_ID_Input_Page_Task(void){
	if(check_time_arrive(AUTO_EXIT_SETS_PAGE_TO_MAIN_PAGE_TIMER_NUMBER,set_system_communicate_pararm_t.auto_exit_sets_page_to_main_time*1000)){
		Back_Main_Page_Load();
		//clear_time_cnt(AUTO_EXIT_SETS_PAGE_TO_MAIN_PAGE_TIMER_NUMBER);
	}
}


static void System_Communicate_ID_Input_Buttons_CB(key_Input_Number_Typedef key_number ,Key_Trg_Even key_state){
	if(key_state == KEY_CLICK_ACTION){
		//clear_time_cnt(AUTO_EXIT_SETS_PAGE_TO_MAIN_PAGE_TIMER_NUMBER);
		set_system_communicate_pararm_t.login_id=user_parameter_adjustment(set_system_communicate_pararm_t.login_id \
				,false,4,key_number,set_system_communicate_pararm_t.SY_ShowCommunicateIDDateFun_t);
	}
}

/********* 保存设置参数- 系统通信-登录ID  ******************/
static void System_Communicate_ID_Enter_Page_Load(void){
	int ret = -1 ;
	type_slect_move_cursor slect_move_cursor;
	slect_move_cursor.dw_cursor_adderss = SYSTEM_SYS_COMMUNICATE_ID_SELECT_CURSOR_ADDERSS ;
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
	dw_input_parameter_hint_window( 1 ,SYSTEM_SYS_COMMUNICATE_ID_WAIT_WINDOW_VAR_ADDERSS,SYSTEM_SYS_COMMUNICATE_ID_SUCCESS_WINDOW_VAR_ADDERSS,SYSTEM_SYS_COMMUNICATE_ID_ERROR_WINDOW_VAR_ADDERSS);
	sprintf(set_system_communicate_pararm_t.mqtt_login_para.username,"MoistureproofCoverPlan-%04d",set_system_communicate_pararm_t.login_id);

	mqtt_login_def mqtt_login_para_t;
	read_saveenv_cjson_mqttlogin_parameter(&mqtt_login_para_t);
	ret = mqttloginPoint_amend_config("Username",set_system_communicate_pararm_t.mqtt_login_para.username);
	if( !ret){
		 //显示成功窗口
		dw_input_parameter_hint_window(2  ,SYSTEM_SYS_COMMUNICATE_ID_WAIT_WINDOW_VAR_ADDERSS,SYSTEM_SYS_COMMUNICATE_ID_SUCCESS_WINDOW_VAR_ADDERSS,SYSTEM_SYS_COMMUNICATE_ID_ERROR_WINDOW_VAR_ADDERSS);
	}else{
		//显示错误窗口
		dw_input_parameter_hint_window( 3  ,SYSTEM_SYS_COMMUNICATE_ID_WAIT_WINDOW_VAR_ADDERSS,SYSTEM_SYS_COMMUNICATE_ID_SUCCESS_WINDOW_VAR_ADDERSS,SYSTEM_SYS_COMMUNICATE_ID_ERROR_WINDOW_VAR_ADDERSS);
	}
	if(strcmp(mqtt_login_para_t.username,set_system_communicate_pararm_t.mqtt_login_para.username ) ==0){
		Set_Mqtt_Client_System_t.mqtt_username_change_flag = 0 ;
		log_d("mqtt usrname no change ");
	}else{
		Set_Mqtt_Client_System_t.mqtt_username_change_flag = 1 ;
		log_d("mqtt usrname change ");
	}
	Buttons_Register(KEY_ENTER_TRG_NUMBER,System_Communicate_Enter_Window_Buttons_CB);
}

static void System_Communicate_ID_Enter_Page_Exit(void){
	//清除窗口
	dw_input_parameter_hint_window( 0  ,SYSTEM_SYS_COMMUNICATE_ID_WAIT_WINDOW_VAR_ADDERSS,SYSTEM_SYS_COMMUNICATE_ID_SUCCESS_WINDOW_VAR_ADDERSS,SYSTEM_SYS_COMMUNICATE_ID_ERROR_WINDOW_VAR_ADDERSS);
	//clear_time_cnt(AUTO_EXIT_SETS_PAGE_TO_MAIN_PAGE_TIMER_NUMBER);
}

static void System_Communicate_ID_Enter_Page_Task(void){
	if(check_time_arrive(AUTO_EXIT_SETS_PAGE_TO_MAIN_PAGE_TIMER_NUMBER,set_system_communicate_pararm_t.auto_exit_sets_page_to_main_time*1000)){
		Back_Main_Page_Load();
	}
}

/********************************************** 切换页面 - 系统通信-系统登录密码页面  ***************************************************************/
/* 系统通信-系统登录密码设置菜单 */
static MenuList_t System_Communicate_Passwd_Menu_Table[] =
{
	{"参数输入框", NULL, System_Communicate_Passwd_Input_Page_Load, System_Communicate_Passwd_Input_Page_Exit, System_Communicate_Passwd_Input_Page_Task, NULL},

    {"保存设置参数", NULL, System_Communicate_Passwd_Enter_Page_Load, System_Communicate_Passwd_Enter_Page_Exit, System_Communicate_Passwd_Enter_Page_Task, NULL},

    {"返回上级菜单", NULL,  Return_Previous_Menu_Page_Load, NULL, NULL, NULL},

    {"返回主页面", NULL,  Back_Main_Page_Load,   NULL,   NULL, NULL},
};

static void System_Set_Communicate_Passwd_Page_Load(void){

	type_slect_move_cursor slect_move_cursor;
	log_d("clearn System_Set_Communicate_Passwd_Page_Load !");
	slect_move_cursor.dw_cursor_adderss = SYSTEM_SYS_COMMUNICATE_PASSWD_INTPUT_SELECT_CURSOR_VAR_ADDERSS ;
	slect_move_cursor.max_slect_move = 7 ;
	slect_move_cursor.min_slect_move = 0 ;
	slect_move_cursor.move_slect_step = 1 ;
	slect_move_cursor.now_slect_move = 0 ;
	slect_cursor_move_init(&slect_move_cursor);  		//输入指示光标位置初始化
	slect_cursor_move(cursor_refresh_mode,cursor_null);  //关闭输入指示光标

	slect_move_cursor.dw_cursor_adderss = SYSTEM_SYS_COMMUNICATE_PASSWD_SELECT_CURSOR_ADDERSS ;
	slect_move_cursor.max_slect_move = 3 ;
	slect_move_cursor.min_slect_move = 0 ;
	slect_move_cursor.move_slect_step = 1 ;
	slect_move_cursor.now_slect_move = 0 ;
	slect_cursor_move_init(&slect_move_cursor); 		 			//光标位置初始化
	slect_cursor_move(cursor_default_mode,cursor_null);  			//初始化选择设置光标

	set_system_communicate_pararm_t.SY_ShowCommunicatePasswdFun_t(set_system_communicate_pararm_t.login_passwd);

	dw_show_switching_pages(PAGE_SYSTEM_COMMUNICATE_PASSWD_SETTING_NUMBER); //切换页面

	Buttons_Register(KEY_UP_TRG_NUMBER,System_Communicate_Slcet_Set_Buttons_CB);
	Buttons_Register(KEY_ENTER_TRG_NUMBER,System_Communicate_Slcet_Set_Buttons_CB);
	Buttons_Register(KEY_DOWN_TRG_NUMBER,System_Communicate_Slcet_Set_Buttons_CB);
	Menu_Bind(System_Communicate_Passwd_Menu_Table, GET_MENU_NUM(System_Communicate_Passwd_Menu_Table), System_Communicate_SetMenu);
}

static void System_Set_Communicate_Passwd_Page_Exit(void){
	//clear_time_cnt(AUTO_EXIT_SETS_PAGE_TO_MAIN_PAGE_TIMER_NUMBER);
}
static void System_Set_Communicate_Passwd_Page_Task(void){
	if(check_time_arrive(AUTO_EXIT_SETS_PAGE_TO_MAIN_PAGE_TIMER_NUMBER,set_system_communicate_pararm_t.auto_exit_sets_page_to_main_time*1000)){
		Back_Main_Page_Load();
	}
}

/************* 输入参数- 系统通信-系统登录密码设置页面  *******************/
static void System_Communicate_Passwd_Input_Page_Load(void){
	type_slect_move_cursor slect_move_cursor;
	log_d("clearn System_Communicate_Passwd_Input_Page_Load !");
	slect_move_cursor.dw_cursor_adderss = SYSTEM_SYS_COMMUNICATE_PASSWD_SELECT_CURSOR_ADDERSS ;
	slect_move_cursor.max_slect_move = 3 ;
	slect_move_cursor.min_slect_move = 0 ;
	slect_move_cursor.move_slect_step = 1 ;
	slect_move_cursor.now_slect_move = 0 ;
	slect_cursor_move_init(&slect_move_cursor);  //光标位置初始化
	slect_cursor_move(cursor_refresh_mode,cursor_null);  //关闭选择设置光标

	slect_move_cursor.dw_cursor_adderss = SYSTEM_SYS_COMMUNICATE_PASSWD_INTPUT_SELECT_CURSOR_VAR_ADDERSS ;
	slect_move_cursor.max_slect_move = 7 ;
	slect_move_cursor.min_slect_move = 0 ;
	slect_move_cursor.move_slect_step = 1 ;
	slect_move_cursor.now_slect_move = 0 ;
	slect_cursor_move_init(&slect_move_cursor);  //光标位置初始化
	slect_cursor_move(cursor_default_mode,cursor_null);  //显示初始化输入指示光标位置

	Buttons_Register(KEY_UP_TRG_NUMBER,System_Communicate_Passwd_Input_Buttons_CB);
	Buttons_Register(KEY_ENTER_TRG_NUMBER,System_Communicate_Passwd_Input_Buttons_CB);
	Buttons_Register(KEY_DOWN_TRG_NUMBER,System_Communicate_Passwd_Input_Buttons_CB);

}

static void System_Communicate_Passwd_Input_Page_Exit(void){
	//clear_time_cnt(AUTO_EXIT_SETS_PAGE_TO_MAIN_PAGE_TIMER_NUMBER);
}

static void System_Communicate_Passwd_Input_Page_Task(void){
	if(check_time_arrive(AUTO_EXIT_SETS_PAGE_TO_MAIN_PAGE_TIMER_NUMBER,set_system_communicate_pararm_t.auto_exit_sets_page_to_main_time*1000)){
		Back_Main_Page_Load();
	}
}

static void System_Communicate_Passwd_Input_Buttons_CB(key_Input_Number_Typedef key_number ,Key_Trg_Even key_state){
	if(key_state == KEY_CLICK_ACTION){
		//clear_time_cnt(AUTO_EXIT_SETS_PAGE_TO_MAIN_PAGE_TIMER_NUMBER);
		set_system_communicate_pararm_t.login_passwd=user_parameter_adjustment(set_system_communicate_pararm_t.login_passwd \
				,false,8,key_number,set_system_communicate_pararm_t.SY_ShowCommunicatePasswdFun_t);
	}
}

/********* 保存设置参数- 系统通信-系统登录密码设置参数  ******************/
static void System_Communicate_Passwd_Enter_Page_Load(void){
	int ret = -1 ;
	type_slect_move_cursor slect_move_cursor;
	slect_move_cursor.dw_cursor_adderss = SYSTEM_SYS_COMMUNICATE_PASSWD_SELECT_CURSOR_ADDERSS ;
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
	dw_input_parameter_hint_window( 1 ,SYSTEM_SYS_COMMUNICATE_PASSWD_WAIT_WINDOW_VAR_ADDERSS,SYSTEM_SYS_COMMUNICATE_PASSWD_SUCCESS_WINDOW_VAR_ADDERSS,SYSTEM_SYS_COMMUNICATE_PASSWD_ERROR_WINDOW_VAR_ADDERSS);
	sprintf(set_system_communicate_pararm_t.mqtt_login_para.password,"%08d",set_system_communicate_pararm_t.login_passwd);

	mqtt_login_def mqtt_login_para_t;
	read_saveenv_cjson_mqttlogin_parameter(&mqtt_login_para_t);
	ret = mqttloginPoint_amend_config("Password",set_system_communicate_pararm_t.mqtt_login_para.password);
	if( ret >=0){
		 //显示成功窗口
		dw_input_parameter_hint_window(2,SYSTEM_SYS_COMMUNICATE_PASSWD_WAIT_WINDOW_VAR_ADDERSS,SYSTEM_SYS_COMMUNICATE_PASSWD_SUCCESS_WINDOW_VAR_ADDERSS,SYSTEM_SYS_COMMUNICATE_PASSWD_ERROR_WINDOW_VAR_ADDERSS);
	}else{
		//显示错误窗口
		dw_input_parameter_hint_window( 3,SYSTEM_SYS_COMMUNICATE_PASSWD_WAIT_WINDOW_VAR_ADDERSS,SYSTEM_SYS_COMMUNICATE_PASSWD_SUCCESS_WINDOW_VAR_ADDERSS,SYSTEM_SYS_COMMUNICATE_PASSWD_ERROR_WINDOW_VAR_ADDERSS);
	}
	if(strcmp(mqtt_login_para_t.password,set_system_communicate_pararm_t.mqtt_login_para.password ) ==0){
		Set_Mqtt_Client_System_t.mqtt_password_change_flag = 0 ;
		log_d("mqtt password no change ");
	}else{
		Set_Mqtt_Client_System_t.mqtt_password_change_flag = 1 ;
		log_d("mqtt password change ");
	}
	Buttons_Register(KEY_ENTER_TRG_NUMBER,System_Communicate_Enter_Window_Buttons_CB);
}

static void System_Communicate_Passwd_Enter_Page_Exit(void){
	//清除窗口
		dw_input_parameter_hint_window( 0,SYSTEM_SYS_COMMUNICATE_PASSWD_WAIT_WINDOW_VAR_ADDERSS,SYSTEM_SYS_COMMUNICATE_PASSWD_SUCCESS_WINDOW_VAR_ADDERSS,SYSTEM_SYS_COMMUNICATE_PASSWD_ERROR_WINDOW_VAR_ADDERSS);
		//clear_time_cnt(AUTO_EXIT_SETS_PAGE_TO_MAIN_PAGE_TIMER_NUMBER);
}

static void System_Communicate_Passwd_Enter_Page_Task(void){
	if(check_time_arrive(AUTO_EXIT_SETS_PAGE_TO_MAIN_PAGE_TIMER_NUMBER,set_system_communicate_pararm_t.auto_exit_sets_page_to_main_time*1000)){
		Back_Main_Page_Load();
	}
}

/************* 系统参数-系统通信公共回调函数  *******************/
static void System_Communicate_Slcet_Set_Buttons_CB( key_Input_Number_Typedef key_number , Key_Trg_Even key_state){
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

static void System_Communicate_Enter_Window_Buttons_CB( key_Input_Number_Typedef key_number , Key_Trg_Even key_state){
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

















