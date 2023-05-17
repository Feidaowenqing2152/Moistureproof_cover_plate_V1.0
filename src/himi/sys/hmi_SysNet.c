/*
 * hmi_SysNet.c
 *
 *  Created on: 2023年3月22日
 *      Author: 好
 */
#define LOG_TAG    "hmi_SysNet"
#include "../himi/sys/hmi_SysNet.h"

static void SystemMenuDateShow_Init(void);
/* 设置菜单显示效果 */
static void System_IP_SetMenu(  MenuShow_t *ptShowInfo);

static void Sy_Auto_Allocation_Set_Page_Load(void);
static void Sy_Auto_Allocation_Set_Page_Exit(void);
static void Sy_Auto_Allocation_Set_Page_Task(void);

static void Sy_Auto_Allocation_Input_Page_Load(void);
static void Sy_Auto_Allocation_Input_Page_Exit(void);
static void Sy_Auto_Allocation_Input_Page_Task(void);
static void System_Auto_Allocation_Slcet_Input_Buttons_CB(key_Input_Number_Typedef key_number ,Key_Trg_Even key_state);

static void Sy_Auto_Allocation_Enter_Page_Load(void);
static void Sy_Auto_Allocation_Enter_Page_Exit(void);
static void Sy_Auto_Allocation_Enter_Page_Task(void);

static void Sy_User_Allocation_Set_Page_Load(void);
static void Sy_User_Allocation_Set_Page_Exit(void);
static void Sy_User_Allocation_Set_Page_Task(void);

static void Sy_User_Ip_Addr_Input_Page_Load(void);
static void Sy_User_Ip_Addr_Input_Page_Exit(void);
static void Sy_User_Ip_Addr_Input_Page_Task(void);
static void User_Ip_Addr_Input_Buttons_CB(key_Input_Number_Typedef key_number ,Key_Trg_Even key_state);


static void Sy_User_Ip_Mask_Input_Page_Load(void);
static void Sy_User_Ip_Mask_Input_Page_Exit(void);
static void Sy_User_Ip_Mask_Input_Page_Task(void);
static void User_Ip_Mask_Input_Buttons_CB(key_Input_Number_Typedef key_number ,Key_Trg_Even key_state);


static void Sy_User_Ip_Gateway_Input_Page_Load(void);
static void Sy_User_Ip_Gateway_Input_Page_Exit(void);
static void Sy_User_Ip_Gateway_Input_Page_Task(void);
static void User_Ip_Gateway_Input_Buttons_CB(key_Input_Number_Typedef key_number ,Key_Trg_Even key_state);

static void Sy_User_Ip_Enter_Page_Load(void);
static void Sy_User_Ip_Enter_Page_Exit(void);
static void Sy_User_Ip_Enter_Page_Task(void);

/************* 系统参数-系统时间公共回调函数  *******************/
static void System_Net_Slcet_Set_Buttons_CB( key_Input_Number_Typedef key_number , Key_Trg_Even key_state);
static void System_Net_Enter_Window_Buttons_CB( key_Input_Number_Typedef key_number , Key_Trg_Even key_state);


struct set_systemipset_menu_list_pararm{
	int auto_exit_sets_page_to_main_time ;  //自动返回时间
	system_para_def system_para ;
	mqtt_ip_tcp_def mqtt_ip_parameter_t ;
	ShownMenuDate SY_ShowSystemIPDhcpStateFun_t;

	int ip_addr[4] ;
	int ip_mask[4] ;
	int ip_gateway[4] ;

	uint8_t user_set_change_flag[3];

	ShownMenuDate SY_ShowSyatemIPaddrFun_t[4];
	ShownMenuDate SY_ShowSyatemIPMaskFun_t[4];
	ShownMenuDate SY_ShowSyatemIPGatewayFun_t[4];



};


static struct set_systemipset_menu_list_pararm set_systemip_menu_list_pararm_t;


/******************外界参数-系统时间设置页面选择*********************************/

/* 系统时间设置菜单*/
static MenuList_t System_IP_Adderss_Set_Menu_Table[] =
{
    {"自动分配IP地址", NULL, Sy_Auto_Allocation_Set_Page_Load, Sy_Auto_Allocation_Set_Page_Exit, Sy_Auto_Allocation_Set_Page_Task, NULL},

    {"使用设置IP地址", NULL, Sy_User_Allocation_Set_Page_Load, Sy_User_Allocation_Set_Page_Exit, Sy_User_Allocation_Set_Page_Task, NULL},

    {"返回上级菜单", NULL,  Return_Previous_Menu_Page_Load, NULL, NULL, NULL},

    {"返回主页面", NULL,  Back_Main_Page_Load,   NULL,   NULL, NULL},
};

/* 参数初始化*/
static void SystemMenuDateShow_Init(void){
	int *ip_tmp = NULL ;
	system_para_def system_para_t ;
	set_systemip_menu_list_pararm_t.SY_ShowSystemIPDhcpStateFun_t = show_system_ip_dhcp_state_date ;

	set_systemip_menu_list_pararm_t.SY_ShowSyatemIPaddrFun_t[0] = show_system_ip_addr1_intput_date ;
	set_systemip_menu_list_pararm_t.SY_ShowSyatemIPaddrFun_t[1] = show_system_ip_addr2_intput_date ;
	set_systemip_menu_list_pararm_t.SY_ShowSyatemIPaddrFun_t[2] = show_system_ip_addr3_intput_date ;
	set_systemip_menu_list_pararm_t.SY_ShowSyatemIPaddrFun_t[3] = show_system_ip_addr4_intput_date ;

	set_systemip_menu_list_pararm_t.SY_ShowSyatemIPMaskFun_t[0] = show_system_ip_mask1_intput_date ;
	set_systemip_menu_list_pararm_t.SY_ShowSyatemIPMaskFun_t[1] = show_system_ip_mask2_intput_date ;
	set_systemip_menu_list_pararm_t.SY_ShowSyatemIPMaskFun_t[2] = show_system_ip_mask3_intput_date ;
	set_systemip_menu_list_pararm_t.SY_ShowSyatemIPMaskFun_t[3] = show_system_ip_mask4_intput_date ;


	set_systemip_menu_list_pararm_t.SY_ShowSyatemIPGatewayFun_t[0] = show_system_ip_gateway1_intput_date ;
	set_systemip_menu_list_pararm_t.SY_ShowSyatemIPGatewayFun_t[1] = show_system_ip_gateway2_intput_date ;
	set_systemip_menu_list_pararm_t.SY_ShowSyatemIPGatewayFun_t[2] = show_system_ip_gateway3_intput_date ;
	set_systemip_menu_list_pararm_t.SY_ShowSyatemIPGatewayFun_t[3] = show_system_ip_gateway4_intput_date ;

	read_saveenv_cjson_system_parameter(&system_para_t);
	set_systemip_menu_list_pararm_t.auto_exit_sets_page_to_main_time = system_para_t.AutoExitSetsPageTime;

	read_saveenv_cjson_mqttip_parameter(&set_systemip_menu_list_pararm_t.mqtt_ip_parameter_t);
	ip_tmp = ip_str_analysis_number(set_systemip_menu_list_pararm_t.mqtt_ip_parameter_t.ip);
	for(uint8_t i=0;i<4;i++){
		set_systemip_menu_list_pararm_t.ip_addr[i]=ip_tmp[i];
		set_systemip_menu_list_pararm_t.SY_ShowSyatemIPaddrFun_t[i](set_systemip_menu_list_pararm_t.ip_addr[i]);
	}
	ip_tmp = ip_str_analysis_number(set_systemip_menu_list_pararm_t.mqtt_ip_parameter_t.netmask);
	for(uint8_t i=0;i<4;i++){
		set_systemip_menu_list_pararm_t.ip_mask[i]= ip_tmp[i];
		set_systemip_menu_list_pararm_t.SY_ShowSyatemIPMaskFun_t[i](set_systemip_menu_list_pararm_t.ip_mask[i]);
	}
	ip_tmp = ip_str_analysis_number(set_systemip_menu_list_pararm_t.mqtt_ip_parameter_t.gateway);
	for(uint8_t i=0;i<4;i++){
		set_systemip_menu_list_pararm_t.ip_gateway[i]= ip_tmp[i];
		set_systemip_menu_list_pararm_t.SY_ShowSyatemIPGatewayFun_t[i](set_systemip_menu_list_pararm_t.ip_gateway[i]);
	}

}


/* 设置菜单显示效果 */
static void System_IP_SetMenu(  MenuShow_t *ptShowInfo){
	show_refresh_time();
	show_eth_connect_state();
}
/********************************************** 切换页面 - 系统时间设置页面  ***************************************************************/
void System_Net_Setting_Page_Load(void){

	log_d("System_Net_Setting_Page_Load ");
	type_slect_move_cursor slect_move_cursor;

	slect_move_cursor.dw_cursor_adderss = SYSTEM_NETWORK_SET_SELECT_CURSOR_ADDERSS ;
	slect_move_cursor.max_slect_move = 3 ;
	slect_move_cursor.min_slect_move = 0 ;
	slect_move_cursor.move_slect_step = 1 ;
	slect_move_cursor.now_slect_move = 0 ;
	slect_cursor_move_init(&slect_move_cursor);  //光标位置初始化
	dw_show_switching_pages(PAGE_SYSTEM_NETWORK_SETTING_NUMBER); //切换页面
	slect_cursor_move(cursor_default_mode,cursor_null);  //初始化选择设置光标
	Buttons_Register(KEY_UP_TRG_NUMBER,System_Net_Slcet_Set_Buttons_CB);
	Buttons_Register(KEY_ENTER_TRG_NUMBER,System_Net_Slcet_Set_Buttons_CB);
	Buttons_Register(KEY_DOWN_TRG_NUMBER,System_Net_Slcet_Set_Buttons_CB);
	SystemMenuDateShow_Init();
	//clear_time_cnt(AUTO_EXIT_SETS_PAGE_TO_MAIN_PAGE_TIMER_NUMBER);
	Menu_Bind(System_IP_Adderss_Set_Menu_Table, GET_MENU_NUM(System_IP_Adderss_Set_Menu_Table), System_IP_SetMenu);
}

void System_Net_Setting_Page_Exit(void){
	//clear_time_cnt(AUTO_EXIT_SETS_PAGE_TO_MAIN_PAGE_TIMER_NUMBER);
}

void System_Net_Setting_Page_Task(void){
	if(check_time_arrive(AUTO_EXIT_SETS_PAGE_TO_MAIN_PAGE_TIMER_NUMBER,set_systemip_menu_list_pararm_t.auto_exit_sets_page_to_main_time*1000)){
		Back_Main_Page_Load();
		//clear_time_cnt(AUTO_EXIT_SETS_PAGE_TO_MAIN_PAGE_TIMER_NUMBER);
	}
}






/********************************************** 切换页面 - 系统运行时间设置页面  ***************************************************************/
/* 系统运行时间设置菜单 */
static MenuList_t System_Auto_IP_Set_Menu_Table[] =
{
	{"设置IP地址获取形式", NULL, Sy_Auto_Allocation_Input_Page_Load, Sy_Auto_Allocation_Input_Page_Exit, Sy_Auto_Allocation_Input_Page_Task, NULL},

    {"保存设置参数", NULL, Sy_Auto_Allocation_Enter_Page_Load, Sy_Auto_Allocation_Enter_Page_Exit, Sy_Auto_Allocation_Enter_Page_Task, NULL},

    {"返回上级菜单", NULL,  Return_Previous_Menu_Page_Load, NULL, NULL, NULL},

    {"返回主页面", NULL,  Back_Main_Page_Load,   NULL,   NULL, NULL},
};

static void Sy_Auto_Allocation_Set_Page_Load(void){

	type_slect_move_cursor slect_move_cursor;
	log_d("Sy_Auto_Allocation_Set_Page_Load");

	slect_move_cursor.dw_cursor_adderss = SYSTEM_AUTO_IP_INTPUT_SELECT_CURSOR_VAR_ADDERSS ;
	slect_move_cursor.max_slect_move = 0 ;
	slect_move_cursor.min_slect_move = 0 ;
	slect_move_cursor.move_slect_step = 1 ;
	slect_move_cursor.now_slect_move = 0 ;
	slect_cursor_move_init(&slect_move_cursor);  		//光标位置初始化
	slect_cursor_move(cursor_refresh_mode,cursor_null);  //关闭输入指示光标
	slect_move_cursor.dw_cursor_adderss = SYSTEM_AUTO_SET_IP_SELECT_CURSOR_ADDERSS ;
	slect_move_cursor.max_slect_move = 3 ;
	slect_move_cursor.min_slect_move = 0 ;
	slect_move_cursor.move_slect_step = 1 ;
	slect_move_cursor.now_slect_move = 0 ;
	slect_cursor_move_init(&slect_move_cursor); 		 			//光标位置初始化
	slect_cursor_move(cursor_default_mode,cursor_null);  			//初始化选择设置光标
	dw_show_switching_pages(PAGE_SYSTEM_AUTO_IP_ADDR_SETTING_NUMBER); //切换页面
	Buttons_Register(KEY_UP_TRG_NUMBER,System_Net_Slcet_Set_Buttons_CB);
	Buttons_Register(KEY_ENTER_TRG_NUMBER,System_Net_Slcet_Set_Buttons_CB);
	Buttons_Register(KEY_DOWN_TRG_NUMBER,System_Net_Slcet_Set_Buttons_CB);

	log_d("ip_acquisition_type=%s",set_systemip_menu_list_pararm_t.mqtt_ip_parameter_t.ip_acquisition_type);


	if(strcmp(set_systemip_menu_list_pararm_t.mqtt_ip_parameter_t.ip_acquisition_type,"dhcp") == 0){
		set_systemip_menu_list_pararm_t.SY_ShowSystemIPDhcpStateFun_t(1);  //显示动态图标
	}


	Menu_Bind(System_Auto_IP_Set_Menu_Table, GET_MENU_NUM(System_Auto_IP_Set_Menu_Table), System_IP_SetMenu);
}
static void Sy_Auto_Allocation_Set_Page_Exit(void){
	//clear_time_cnt(AUTO_EXIT_SETS_PAGE_TO_MAIN_PAGE_TIMER_NUMBER);
}
static void Sy_Auto_Allocation_Set_Page_Task(void){
	if(check_time_arrive(AUTO_EXIT_SETS_PAGE_TO_MAIN_PAGE_TIMER_NUMBER,set_systemip_menu_list_pararm_t.auto_exit_sets_page_to_main_time*1000)){
		Back_Main_Page_Load();
	}
}
/************* 输入参数- 系统运行时间 页面  *******************/
static void Sy_Auto_Allocation_Input_Page_Load(void){
	type_slect_move_cursor slect_move_cursor;
	log_d("Sy_Auto_Allocation_Input_Page_Load");
	slect_move_cursor.dw_cursor_adderss = SYSTEM_AUTO_SET_IP_SELECT_CURSOR_ADDERSS ;
	slect_move_cursor.max_slect_move = 3 ;
	slect_move_cursor.min_slect_move = 0 ;
	slect_move_cursor.move_slect_step = 1 ;
	slect_move_cursor.now_slect_move = 0 ;
	slect_cursor_move_init(&slect_move_cursor);  		//光标位置初始化
	slect_cursor_move(cursor_refresh_mode,cursor_null);  //关闭输入指示光标
	slect_move_cursor.dw_cursor_adderss = SYSTEM_AUTO_IP_INTPUT_SELECT_CURSOR_VAR_ADDERSS ;
	slect_move_cursor.max_slect_move = 0 ;
	slect_move_cursor.min_slect_move = 0 ;
	slect_move_cursor.move_slect_step = 1 ;
	slect_move_cursor.now_slect_move = 0 ;
	slect_cursor_move_init(&slect_move_cursor); 		 			//光标位置初始化
	slect_cursor_move(cursor_default_mode,cursor_null);  			//初始化选择设置光标
	Buttons_Register(KEY_UP_TRG_NUMBER,System_Auto_Allocation_Slcet_Input_Buttons_CB);
	Buttons_Register(KEY_ENTER_TRG_NUMBER,System_Auto_Allocation_Slcet_Input_Buttons_CB);
	Buttons_Register(KEY_DOWN_TRG_NUMBER,System_Auto_Allocation_Slcet_Input_Buttons_CB);

}

static void Sy_Auto_Allocation_Input_Page_Exit(void){
	//clear_time_cnt(AUTO_EXIT_SETS_PAGE_TO_MAIN_PAGE_TIMER_NUMBER);
	//清除窗口
	dw_input_parameter_hint_window( 0 ,SYSTEM_RUN_TIME_ADJ_WAIT_WINDOW_VAR_ADDERSS,SYSTEM_RUN_TIME_ADJ_SUCCESS_WINDOW_VAR_ADDERSS,SYSTEM_RUN_TIME_ADJ_ERROR_WINDOW_VAR_ADDERSS);

}

static void Sy_Auto_Allocation_Input_Page_Task(void){
	if(check_time_arrive(AUTO_EXIT_SETS_PAGE_TO_MAIN_PAGE_TIMER_NUMBER,set_systemip_menu_list_pararm_t.auto_exit_sets_page_to_main_time*1000)){
		Back_Main_Page_Load();
	}
}

static void System_Auto_Allocation_Slcet_Input_Buttons_CB(key_Input_Number_Typedef key_number ,Key_Trg_Even key_state){
	static uint8_t buttons_trg_cnts = 0 ;
	static uint8_t buttons_trg_flag = 0 ;

	if(key_state == KEY_CLICK_ACTION){
		if(key_number ==  KEY_ENTER_TRG_NUMBER ){
			buttons_trg_flag = 0 ;
			Menu_Exit(true);
		}else{
			if(buttons_trg_flag == 0 ){
				buttons_trg_flag =1 ;
				if(strcmp(set_systemip_menu_list_pararm_t.mqtt_ip_parameter_t.ip_acquisition_type,"dhcp") == 0){
					buttons_trg_cnts = 1 ;
				}else{
					buttons_trg_cnts = 0 ;
				}
			}
			buttons_trg_cnts++ ;
			if(buttons_trg_cnts %2){
				set_systemip_menu_list_pararm_t.SY_ShowSystemIPDhcpStateFun_t(1);  //显示动态图标
				 strcpy(set_systemip_menu_list_pararm_t.mqtt_ip_parameter_t.ip_acquisition_type, "dhcp");
			}else{
				set_systemip_menu_list_pararm_t.SY_ShowSystemIPDhcpStateFun_t(0);  //显示动态图标
				 strcpy(set_systemip_menu_list_pararm_t.mqtt_ip_parameter_t.ip_acquisition_type, "static");
			}
		}
		log_d("ip_acquisition_type=%s",set_systemip_menu_list_pararm_t.mqtt_ip_parameter_t.ip_acquisition_type);
	}
}

/********* 保存设置参数- 系统运行时间  ******************/
static void Sy_Auto_Allocation_Enter_Page_Load(void){
	int ret = -1,dhcp_ret=-1 ;
	struct eth eth0 ;
	struct eth dhcp_eth0;
	type_slect_move_cursor slect_move_cursor;
	slect_move_cursor.dw_cursor_adderss = SYSTEM_AUTO_SET_IP_SELECT_CURSOR_ADDERSS ;
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
	dw_input_parameter_hint_window( 1 ,SYSTEM_AUTO_IP_WAIT_WINDOW_VAR_ADDERSS,SYSTEM_AUTO_IP_SUCCESS_WINDOW_VAR_ADDERSS,SYSTEM_AUTO_IP_ERROR_WINDOW_VAR_ADDERSS);
	strcpy(eth0.ip_dhcp_state, set_systemip_menu_list_pararm_t.mqtt_ip_parameter_t.ip_acquisition_type);
	ret = mqttip_amend_config("IpAcquisitionType",set_systemip_menu_list_pararm_t.mqtt_ip_parameter_t.ip_acquisition_type);
	ret = set_sys_network(&eth0 ,"ip_dhcp_state");
	if(strcmp(set_systemip_menu_list_pararm_t.mqtt_ip_parameter_t.ip_acquisition_type,"dhcp") == 0){
		dhcp_ret = network_eth0_dhcp_status("eth0",&dhcp_eth0);
	}else{
		dhcp_ret = 0 ;
	}
	if( (!ret) && (dhcp_ret==0 )){
		 //显示成功窗口
		dw_input_parameter_hint_window(2,SYSTEM_AUTO_IP_WAIT_WINDOW_VAR_ADDERSS,SYSTEM_AUTO_IP_SUCCESS_WINDOW_VAR_ADDERSS,SYSTEM_AUTO_IP_ERROR_WINDOW_VAR_ADDERSS);
	}else{
		//显示错误窗口
		dw_input_parameter_hint_window( 3,SYSTEM_AUTO_IP_WAIT_WINDOW_VAR_ADDERSS,SYSTEM_AUTO_IP_SUCCESS_WINDOW_VAR_ADDERSS,SYSTEM_AUTO_IP_ERROR_WINDOW_VAR_ADDERSS);
	}

	Buttons_Register(KEY_ENTER_TRG_NUMBER,System_Net_Enter_Window_Buttons_CB);
}

static void Sy_Auto_Allocation_Enter_Page_Exit(void){
	//清除窗口
	dw_input_parameter_hint_window( 0 ,SYSTEM_AUTO_IP_WAIT_WINDOW_VAR_ADDERSS,SYSTEM_AUTO_IP_SUCCESS_WINDOW_VAR_ADDERSS,SYSTEM_AUTO_IP_ERROR_WINDOW_VAR_ADDERSS);
	//clear_time_cnt(AUTO_EXIT_SETS_PAGE_TO_MAIN_PAGE_TIMER_NUMBER);
}

static void Sy_Auto_Allocation_Enter_Page_Task(void){
	if(check_time_arrive(AUTO_EXIT_SETS_PAGE_TO_MAIN_PAGE_TIMER_NUMBER,set_systemip_menu_list_pararm_t.auto_exit_sets_page_to_main_time*1000)){
		Back_Main_Page_Load();
		//clear_time_cnt(AUTO_EXIT_SETS_PAGE_TO_MAIN_PAGE_TIMER_NUMBER);
	}
}

/********************************************** 切换页面 - 自动返回主页时间值页面  ***************************************************************/
/* 自动返回主页菜单 */
static MenuList_t System_User_IP_Set_Menu_Table[] =
{
	{"参数输入IP地址框", NULL, Sy_User_Ip_Addr_Input_Page_Load, Sy_User_Ip_Addr_Input_Page_Exit, Sy_User_Ip_Addr_Input_Page_Task, NULL},

	{"参数输入IP掩码框", NULL, Sy_User_Ip_Mask_Input_Page_Load, Sy_User_Ip_Mask_Input_Page_Exit, Sy_User_Ip_Mask_Input_Page_Task, NULL},

	{"参数输入IP网关框", NULL, Sy_User_Ip_Gateway_Input_Page_Load, Sy_User_Ip_Gateway_Input_Page_Exit, Sy_User_Ip_Gateway_Input_Page_Task, NULL},

    {"保存设置参数", NULL, Sy_User_Ip_Enter_Page_Load, Sy_User_Ip_Enter_Page_Exit, Sy_User_Ip_Enter_Page_Task, NULL},

    {"返回上级菜单", NULL,  Return_Previous_Menu_Page_Load, NULL, NULL, NULL},

    {"返回主页面", NULL,  Back_Main_Page_Load,   NULL,   NULL, NULL},
};

static void Sy_User_Allocation_Set_Page_Load(void){
	type_slect_move_cursor slect_move_cursor;

	slect_move_cursor.dw_cursor_adderss = SYSTEM_USER_IP_ADDR_INTPUT_SELECT_CURSOR_VAR_ADDERSS ;
	slect_move_cursor.max_slect_move = 11 ;
	slect_move_cursor.min_slect_move = 0 ;
	slect_move_cursor.move_slect_step = 1 ;
	slect_move_cursor.now_slect_move = 0 ;
	slect_cursor_move_init(&slect_move_cursor);  		//光标位置初始化
	slect_cursor_move(cursor_refresh_mode,cursor_null);  //关闭输入指示光标

	slect_move_cursor.dw_cursor_adderss = SYSTEM_USER_IP_MASK_INTPUT_SELECT_CURSOR_VAR_ADDERSS ;
	slect_move_cursor.max_slect_move = 11 ;
	slect_move_cursor.min_slect_move = 0 ;
	slect_move_cursor.move_slect_step = 1 ;
	slect_move_cursor.now_slect_move = 0 ;
	slect_cursor_move_init(&slect_move_cursor);  		//光标位置初始化
	slect_cursor_move(cursor_refresh_mode,cursor_null);  //关闭输入指示光标

	slect_move_cursor.dw_cursor_adderss = SYSTEM_USER_IP_GATEWAY_INTPUT_SELECT_CURSOR_VAR_ADDERSS ;
	slect_move_cursor.max_slect_move = 11 ;
	slect_move_cursor.min_slect_move = 0 ;
	slect_move_cursor.move_slect_step = 1 ;
	slect_move_cursor.now_slect_move = 0 ;
	slect_cursor_move_init(&slect_move_cursor);  		//光标位置初始化
	slect_cursor_move(cursor_refresh_mode,cursor_null);  //关闭输入指示光标

	slect_move_cursor.dw_cursor_adderss = SYSTEM_USER_SET_IP_SELECT_CURSOR_ADDERSS ;
	slect_move_cursor.max_slect_move = 5 ;
	slect_move_cursor.min_slect_move = 0 ;
	slect_move_cursor.move_slect_step = 1 ;
	slect_move_cursor.now_slect_move = 0 ;
	slect_cursor_move_init(&slect_move_cursor); 		 			//光标位置初始化
	slect_cursor_move(cursor_default_mode,cursor_null);  			//初始化选择设置光标


	dw_show_switching_pages(PAGE_SYSTEM_USER_IP_ADDR_SETTING_NUMBER); //切换页面
	Buttons_Register(KEY_UP_TRG_NUMBER,System_Net_Slcet_Set_Buttons_CB);
	Buttons_Register(KEY_ENTER_TRG_NUMBER,System_Net_Slcet_Set_Buttons_CB);
	Buttons_Register(KEY_DOWN_TRG_NUMBER,System_Net_Slcet_Set_Buttons_CB);
	Menu_Bind(System_User_IP_Set_Menu_Table, GET_MENU_NUM(System_User_IP_Set_Menu_Table), System_IP_SetMenu);
}
static void Sy_User_Allocation_Set_Page_Exit(void){
	//clear_time_cnt(AUTO_EXIT_SETS_PAGE_TO_MAIN_PAGE_TIMER_NUMBER);
}
static void Sy_User_Allocation_Set_Page_Task(void){
	if(check_time_arrive(AUTO_EXIT_SETS_PAGE_TO_MAIN_PAGE_TIMER_NUMBER,set_systemip_menu_list_pararm_t.auto_exit_sets_page_to_main_time*1000)){
		Back_Main_Page_Load();
		//clear_time_cnt(AUTO_EXIT_SETS_PAGE_TO_MAIN_PAGE_TIMER_NUMBER);
	}
}
/************* IP地址输入参数- 自动返回主页值页面  *******************/
static void Sy_User_Ip_Addr_Input_Page_Load(void){
	type_slect_move_cursor slect_move_cursor;

	slect_move_cursor.dw_cursor_adderss = SYSTEM_USER_SET_IP_SELECT_CURSOR_ADDERSS ;
	slect_move_cursor.max_slect_move = 5 ;
	slect_move_cursor.min_slect_move = 0 ;
	slect_move_cursor.move_slect_step = 1 ;
	slect_move_cursor.now_slect_move = 0 ;
	slect_cursor_move_init(&slect_move_cursor);  //光标位置初始化
	slect_cursor_move(cursor_refresh_mode,cursor_null);  //关闭选择设置光标

	slect_move_cursor.dw_cursor_adderss = SYSTEM_USER_IP_ADDR_INTPUT_SELECT_CURSOR_VAR_ADDERSS ;
	slect_move_cursor.max_slect_move = 11 ;
	slect_move_cursor.min_slect_move = 0 ;
	slect_move_cursor.move_slect_step = 1 ;
	slect_move_cursor.now_slect_move = 0 ;
	slect_cursor_move_init(&slect_move_cursor);  //光标位置初始化
	slect_cursor_move(cursor_default_mode,cursor_null);  //显示初始化输入指示光标位置

	set_systemip_menu_list_pararm_t.user_set_change_flag[0] =1 ;

	Buttons_Register(KEY_UP_TRG_NUMBER,User_Ip_Addr_Input_Buttons_CB);
	Buttons_Register(KEY_ENTER_TRG_NUMBER,User_Ip_Addr_Input_Buttons_CB);
	Buttons_Register(KEY_DOWN_TRG_NUMBER,User_Ip_Addr_Input_Buttons_CB);
}

static void Sy_User_Ip_Addr_Input_Page_Exit(void){
	//clear_time_cnt(AUTO_EXIT_SETS_PAGE_TO_MAIN_PAGE_TIMER_NUMBER);
}

static void Sy_User_Ip_Addr_Input_Page_Task(void){
	if(check_time_arrive(AUTO_EXIT_SETS_PAGE_TO_MAIN_PAGE_TIMER_NUMBER,set_systemip_menu_list_pararm_t.auto_exit_sets_page_to_main_time*1000)){
		Back_Main_Page_Load();
	}
}


static void User_Ip_Addr_Input_Buttons_CB(key_Input_Number_Typedef key_number ,Key_Trg_Even key_state){
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
				set_systemip_menu_list_pararm_t.ip_addr[i]=user_parameter_adjustment(set_systemip_menu_list_pararm_t.ip_addr[i],false,4,key_number,set_systemip_menu_list_pararm_t.SY_ShowSyatemIPaddrFun_t[i]);
			}
		}
		if(key_number ==KEY_ENTER_TRG_NUMBER ){
			if( (User_Trg_Buttons_Cnts %3) ==0 ){
				clearn_Temp_Compensation_Slcet_buttons_cnt();
			}
		}

	}
}


/************* IP掩码输入参数- 自动返回主页值页面  *******************/
static void Sy_User_Ip_Mask_Input_Page_Load(void){
	type_slect_move_cursor slect_move_cursor;

	slect_move_cursor.dw_cursor_adderss = SYSTEM_USER_SET_IP_SELECT_CURSOR_ADDERSS ;
	slect_move_cursor.max_slect_move = 5 ;
	slect_move_cursor.min_slect_move = 0 ;
	slect_move_cursor.move_slect_step = 1 ;
	slect_move_cursor.now_slect_move = 0 ;
	slect_cursor_move_init(&slect_move_cursor);  		//光标位置初始化
	slect_cursor_move(cursor_refresh_mode,cursor_null);  //关闭输入指示光标

	slect_move_cursor.dw_cursor_adderss = SYSTEM_USER_IP_MASK_INTPUT_SELECT_CURSOR_VAR_ADDERSS ;
	slect_move_cursor.max_slect_move = 11 ;
	slect_move_cursor.min_slect_move = 0 ;
	slect_move_cursor.move_slect_step = 1 ;
	slect_move_cursor.now_slect_move = 0 ;
	slect_cursor_move_init(&slect_move_cursor); 		 			//光标位置初始化
	slect_cursor_move(cursor_default_mode,cursor_null);  			//初始化选择设置光标

	set_systemip_menu_list_pararm_t.user_set_change_flag[1] =1 ;

	Buttons_Register(KEY_UP_TRG_NUMBER,User_Ip_Mask_Input_Buttons_CB);
	Buttons_Register(KEY_ENTER_TRG_NUMBER,User_Ip_Mask_Input_Buttons_CB);
	Buttons_Register(KEY_DOWN_TRG_NUMBER,User_Ip_Mask_Input_Buttons_CB);
}

static void Sy_User_Ip_Mask_Input_Page_Exit(void){
	//clear_time_cnt(AUTO_EXIT_SETS_PAGE_TO_MAIN_PAGE_TIMER_NUMBER);
}

static void Sy_User_Ip_Mask_Input_Page_Task(void){
	if(check_time_arrive(AUTO_EXIT_SETS_PAGE_TO_MAIN_PAGE_TIMER_NUMBER,set_systemip_menu_list_pararm_t.auto_exit_sets_page_to_main_time*1000)){
		Back_Main_Page_Load();
	}
}
static void User_Ip_Mask_Input_Buttons_CB(key_Input_Number_Typedef key_number ,Key_Trg_Even key_state){
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
				set_systemip_menu_list_pararm_t.ip_mask[i]=user_parameter_adjustment(set_systemip_menu_list_pararm_t.ip_mask[i],false,4,key_number,set_systemip_menu_list_pararm_t.SY_ShowSyatemIPMaskFun_t[i]);
			}
		}
		if(key_number ==KEY_ENTER_TRG_NUMBER ){
			if( (User_Trg_Buttons_Cnts %3) ==0 ){
				clearn_Temp_Compensation_Slcet_buttons_cnt();
			}
		}

	}
}
/************* IP网关输入参数- 自动返回主页值页面  *******************/
static void Sy_User_Ip_Gateway_Input_Page_Load(void){
	type_slect_move_cursor slect_move_cursor;

	slect_move_cursor.dw_cursor_adderss = SYSTEM_USER_SET_IP_SELECT_CURSOR_ADDERSS ;
	slect_move_cursor.max_slect_move = 5 ;
	slect_move_cursor.min_slect_move = 0 ;
	slect_move_cursor.move_slect_step = 1 ;
	slect_move_cursor.now_slect_move = 0 ;
	slect_cursor_move_init(&slect_move_cursor);  		//光标位置初始化
	slect_cursor_move(cursor_refresh_mode,cursor_null);  //关闭输入指示光标

	slect_move_cursor.dw_cursor_adderss = SYSTEM_USER_IP_GATEWAY_INTPUT_SELECT_CURSOR_VAR_ADDERSS ;
	slect_move_cursor.max_slect_move = 11 ;
	slect_move_cursor.min_slect_move = 0 ;
	slect_move_cursor.move_slect_step = 1 ;
	slect_move_cursor.now_slect_move = 0 ;
	slect_cursor_move_init(&slect_move_cursor); 		 			//光标位置初始化
	slect_cursor_move(cursor_default_mode,cursor_null);  			//初始化选择设置光标

	set_systemip_menu_list_pararm_t.user_set_change_flag[2] =1 ;
	Buttons_Register(KEY_UP_TRG_NUMBER,User_Ip_Gateway_Input_Buttons_CB);
	Buttons_Register(KEY_ENTER_TRG_NUMBER,User_Ip_Gateway_Input_Buttons_CB);
	Buttons_Register(KEY_DOWN_TRG_NUMBER,User_Ip_Gateway_Input_Buttons_CB);
}

static void Sy_User_Ip_Gateway_Input_Page_Exit(void){
	//clear_time_cnt(AUTO_EXIT_SETS_PAGE_TO_MAIN_PAGE_TIMER_NUMBER);
}

static void Sy_User_Ip_Gateway_Input_Page_Task(void){
	if(check_time_arrive(AUTO_EXIT_SETS_PAGE_TO_MAIN_PAGE_TIMER_NUMBER,set_systemip_menu_list_pararm_t.auto_exit_sets_page_to_main_time*1000)){
		Back_Main_Page_Load();
	}
}


static void User_Ip_Gateway_Input_Buttons_CB(key_Input_Number_Typedef key_number ,Key_Trg_Even key_state){
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
				set_systemip_menu_list_pararm_t.ip_gateway[i]=user_parameter_adjustment(set_systemip_menu_list_pararm_t.ip_gateway[i],false,4,key_number,set_systemip_menu_list_pararm_t.SY_ShowSyatemIPGatewayFun_t[i]);
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
static void Sy_User_Ip_Enter_Page_Load(void){
	uint8_t ip_setting_judge=0;

	int ret = -1 ;
	type_slect_move_cursor slect_move_cursor;
	struct eth eth0 ;

	slect_move_cursor.dw_cursor_adderss = SYSTEM_USER_IP_ADDR_INTPUT_SELECT_CURSOR_VAR_ADDERSS ;
	slect_move_cursor.max_slect_move = 11 ;
	slect_move_cursor.min_slect_move = 0 ;
	slect_move_cursor.move_slect_step = 1 ;
	slect_move_cursor.now_slect_move = 0 ;
	slect_cursor_move_init(&slect_move_cursor);  		//光标位置初始化
	slect_cursor_move(cursor_refresh_mode,cursor_null);  //关闭输入指示光标

	slect_move_cursor.dw_cursor_adderss = SYSTEM_USER_IP_MASK_INTPUT_SELECT_CURSOR_VAR_ADDERSS ;
	slect_move_cursor.max_slect_move = 11 ;
	slect_move_cursor.min_slect_move = 0 ;
	slect_move_cursor.move_slect_step = 1 ;
	slect_move_cursor.now_slect_move = 0 ;
	slect_cursor_move_init(&slect_move_cursor);  		//光标位置初始化
	slect_cursor_move(cursor_refresh_mode,cursor_null);  //关闭输入指示光标

	slect_move_cursor.dw_cursor_adderss = SYSTEM_USER_IP_GATEWAY_INTPUT_SELECT_CURSOR_VAR_ADDERSS ;
	slect_move_cursor.max_slect_move = 11 ;
	slect_move_cursor.min_slect_move = 0 ;
	slect_move_cursor.move_slect_step = 1 ;
	slect_move_cursor.now_slect_move = 0 ;
	slect_cursor_move_init(&slect_move_cursor);  		//光标位置初始化
	slect_cursor_move(cursor_refresh_mode,cursor_null);  //关闭输入指示光标

	slect_move_cursor.dw_cursor_adderss = SYSTEM_USER_SET_IP_SELECT_CURSOR_ADDERSS ;
	slect_move_cursor.max_slect_move = 5 ;
	slect_move_cursor.min_slect_move = 0 ;
	slect_move_cursor.move_slect_step = 1 ;
	slect_move_cursor.now_slect_move = 0 ;
	slect_cursor_move_init(&slect_move_cursor);  		//光标位置初始化
	slect_cursor_move(cursor_refresh_mode,cursor_null);  //关闭输入指示光标

	Buttons_UnRegister(KEY_UP_TRG_NUMBER);
	Buttons_UnRegister(KEY_ENTER_TRG_NUMBER);
	Buttons_UnRegister(KEY_DOWN_TRG_NUMBER);
	if(set_systemip_menu_list_pararm_t.user_set_change_flag[0]){
		//显示等待窗口
		dw_input_parameter_hint_window( 1 ,SYSTEM_USER_IP_ADDR_WAIT_WINDOW_VAR_ADDERSS,SYSTEM_USER_IP_ADDR_SUCCESS_WINDOW_VAR_ADDERSS,SYSTEM_USER_IP_ADDR_ERROR_WINDOW_VAR_ADDERSS);
		for(uint8_t i=0;i<4;i++){
			if(set_systemip_menu_list_pararm_t.ip_addr[i]>255){
				ip_setting_judge = 1;
				break ;
			}
		}
		if(!ip_setting_judge){
			sprintf(set_systemip_menu_list_pararm_t.mqtt_ip_parameter_t.ip,"%03d.%03d.%03d.%03d", \
				   set_systemip_menu_list_pararm_t.ip_addr[0],set_systemip_menu_list_pararm_t.ip_addr[1],\
				   set_systemip_menu_list_pararm_t.ip_addr[2],set_systemip_menu_list_pararm_t.ip_addr[3]) ;
			ret = mqttip_amend_config("Ip",set_systemip_menu_list_pararm_t.mqtt_ip_parameter_t.ip);
			if( !ret){
				 //显示成功窗口
				strcpy(eth0.ip_adderss, set_systemip_menu_list_pararm_t.mqtt_ip_parameter_t.ip);
				set_sys_network(&eth0,"ip_adderss");
				dw_input_parameter_hint_window(2  ,SYSTEM_USER_IP_ADDR_WAIT_WINDOW_VAR_ADDERSS,SYSTEM_USER_IP_ADDR_SUCCESS_WINDOW_VAR_ADDERSS,SYSTEM_USER_IP_ADDR_ERROR_WINDOW_VAR_ADDERSS);
			}else{
				//显示错误窗口
				dw_input_parameter_hint_window( 3  ,SYSTEM_USER_IP_ADDR_WAIT_WINDOW_VAR_ADDERSS,SYSTEM_USER_IP_ADDR_SUCCESS_WINDOW_VAR_ADDERSS,SYSTEM_USER_IP_ADDR_ERROR_WINDOW_VAR_ADDERSS);
			}
		}else{
			//显示错误窗口
			dw_input_parameter_hint_window( 3  ,SYSTEM_USER_IP_ADDR_WAIT_WINDOW_VAR_ADDERSS,SYSTEM_USER_IP_ADDR_SUCCESS_WINDOW_VAR_ADDERSS,SYSTEM_USER_IP_ADDR_ERROR_WINDOW_VAR_ADDERSS);
			ip_setting_judge = 0 ;

		}
	}
	if(set_systemip_menu_list_pararm_t.user_set_change_flag[1]){
		//显示等待窗口
		dw_input_parameter_hint_window( 1 ,SYSTEM_USER_IP_MASK_WAIT_WINDOW_VAR_ADDERSS,SYSTEM_USER_IP_MASK_SUCCESS_WINDOW_VAR_ADDERSS,SYSTEM_USER_IP_MASK_ERROR_WINDOW_VAR_ADDERSS);
		for(uint8_t i=0;i<4;i++){
			if(set_systemip_menu_list_pararm_t.ip_mask[i]>255){
				ip_setting_judge = 1;
				break ;
			}
		}
		if(!ip_setting_judge){
			sprintf(set_systemip_menu_list_pararm_t.mqtt_ip_parameter_t.netmask,"%03d.%03d.%03d.%03d", \
				   set_systemip_menu_list_pararm_t.ip_mask[0],set_systemip_menu_list_pararm_t.ip_mask[1],\
				   set_systemip_menu_list_pararm_t.ip_mask[2],set_systemip_menu_list_pararm_t.ip_mask[3]) ;
			ret = mqttip_amend_config("Netmask",set_systemip_menu_list_pararm_t.mqtt_ip_parameter_t.netmask);
			if( !ret){
				 //显示成功窗口
				strcpy(eth0.ip_netmask, set_systemip_menu_list_pararm_t.mqtt_ip_parameter_t.netmask);
				set_sys_network(&eth0,"ip_netmask");
				dw_input_parameter_hint_window(2 ,SYSTEM_USER_IP_MASK_WAIT_WINDOW_VAR_ADDERSS,SYSTEM_USER_IP_MASK_SUCCESS_WINDOW_VAR_ADDERSS,SYSTEM_USER_IP_MASK_ERROR_WINDOW_VAR_ADDERSS);
			}else{
				//显示错误窗口
				dw_input_parameter_hint_window( 3 ,SYSTEM_USER_IP_MASK_WAIT_WINDOW_VAR_ADDERSS,SYSTEM_USER_IP_MASK_SUCCESS_WINDOW_VAR_ADDERSS,SYSTEM_USER_IP_MASK_ERROR_WINDOW_VAR_ADDERSS);

			}
		}else{
			//显示错误窗口
			dw_input_parameter_hint_window( 3 ,SYSTEM_USER_IP_MASK_WAIT_WINDOW_VAR_ADDERSS,SYSTEM_USER_IP_MASK_SUCCESS_WINDOW_VAR_ADDERSS,SYSTEM_USER_IP_MASK_ERROR_WINDOW_VAR_ADDERSS);
			ip_setting_judge = 0 ;

		}
	}
	if(set_systemip_menu_list_pararm_t.user_set_change_flag[2]){
		//显示等待窗口
		dw_input_parameter_hint_window( 1 ,SYSTEM_USER_IP_GATEWAY_WAIT_WINDOW_VAR_ADDERSS,SYSTEM_USER_IP_GATEWAY_SUCCESS_WINDOW_VAR_ADDERSS,SYSTEM_USER_IP_GATEWAY_ERROR_WINDOW_VAR_ADDERSS);
		for(uint8_t i=0;i<4;i++){
			if(set_systemip_menu_list_pararm_t.ip_gateway[i]>255){
				ip_setting_judge = 1;
				break ;
			}
		}
		if(!ip_setting_judge){
			sprintf(set_systemip_menu_list_pararm_t.mqtt_ip_parameter_t.gateway,"%03d.%03d.%03d.%03d", \
				   set_systemip_menu_list_pararm_t.ip_gateway[0],set_systemip_menu_list_pararm_t.ip_gateway[1],\
				   set_systemip_menu_list_pararm_t.ip_gateway[2],set_systemip_menu_list_pararm_t.ip_gateway[3]) ;
			ret = mqttip_amend_config("Gateway",set_systemip_menu_list_pararm_t.mqtt_ip_parameter_t.gateway);
			if( !ret){
				 //显示成功窗口
				strcpy(eth0.ip_gateway, set_systemip_menu_list_pararm_t.mqtt_ip_parameter_t.gateway);
				set_sys_network(&eth0,"ip_gateway");
				dw_input_parameter_hint_window(2,SYSTEM_USER_IP_GATEWAY_WAIT_WINDOW_VAR_ADDERSS,SYSTEM_USER_IP_GATEWAY_SUCCESS_WINDOW_VAR_ADDERSS,SYSTEM_USER_IP_GATEWAY_ERROR_WINDOW_VAR_ADDERSS);
			}else{
				//显示错误窗口
				dw_input_parameter_hint_window( 3,SYSTEM_USER_IP_GATEWAY_WAIT_WINDOW_VAR_ADDERSS,SYSTEM_USER_IP_GATEWAY_SUCCESS_WINDOW_VAR_ADDERSS,SYSTEM_USER_IP_GATEWAY_ERROR_WINDOW_VAR_ADDERSS);
			}
		}else{
			//显示错误窗口
			dw_input_parameter_hint_window( 3 ,SYSTEM_USER_IP_GATEWAY_WAIT_WINDOW_VAR_ADDERSS,SYSTEM_USER_IP_GATEWAY_SUCCESS_WINDOW_VAR_ADDERSS,SYSTEM_USER_IP_GATEWAY_ERROR_WINDOW_VAR_ADDERSS);
			ip_setting_judge = 0 ;

		}
	}


	Buttons_Register(KEY_ENTER_TRG_NUMBER,System_Net_Enter_Window_Buttons_CB);
}

static void Sy_User_Ip_Enter_Page_Exit(void){
	if(set_systemip_menu_list_pararm_t.user_set_change_flag[0]){
		//清除窗口
		dw_input_parameter_hint_window( 4,SYSTEM_USER_IP_ADDR_WAIT_WINDOW_VAR_ADDERSS,SYSTEM_USER_IP_ADDR_SUCCESS_WINDOW_VAR_ADDERSS,SYSTEM_USER_IP_ADDR_ERROR_WINDOW_VAR_ADDERSS);
	}
	if(set_systemip_menu_list_pararm_t.user_set_change_flag[1]){
		//清除窗口
		dw_input_parameter_hint_window( 4 ,SYSTEM_USER_IP_MASK_WAIT_WINDOW_VAR_ADDERSS,SYSTEM_USER_IP_MASK_SUCCESS_WINDOW_VAR_ADDERSS,SYSTEM_USER_IP_MASK_ERROR_WINDOW_VAR_ADDERSS);
	}
	if(set_systemip_menu_list_pararm_t.user_set_change_flag[2]){
		//清除窗口
		dw_input_parameter_hint_window( 4 ,SYSTEM_USER_IP_GATEWAY_WAIT_WINDOW_VAR_ADDERSS,SYSTEM_USER_IP_GATEWAY_SUCCESS_WINDOW_VAR_ADDERSS,SYSTEM_USER_IP_GATEWAY_ERROR_WINDOW_VAR_ADDERSS);
	}
	set_systemip_menu_list_pararm_t.user_set_change_flag[0] = 0 ;
	set_systemip_menu_list_pararm_t.user_set_change_flag[1] = 0 ;
	set_systemip_menu_list_pararm_t.user_set_change_flag[2] = 0 ;
	//clear_time_cnt(AUTO_EXIT_SETS_PAGE_TO_MAIN_PAGE_TIMER_NUMBER);
}

static void Sy_User_Ip_Enter_Page_Task(void){
	if(check_time_arrive(AUTO_EXIT_SETS_PAGE_TO_MAIN_PAGE_TIMER_NUMBER,set_systemip_menu_list_pararm_t.auto_exit_sets_page_to_main_time*1000)){
		Back_Main_Page_Load();
		//clear_time_cnt(AUTO_EXIT_SETS_PAGE_TO_MAIN_PAGE_TIMER_NUMBER);
	}
}


/************* 系统参数-系统时间公共回调函数  *******************/
static void System_Net_Slcet_Set_Buttons_CB( key_Input_Number_Typedef key_number , Key_Trg_Even key_state){
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

static void System_Net_Enter_Window_Buttons_CB( key_Input_Number_Typedef key_number , Key_Trg_Even key_state){
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




