/*
 * hmi_common.c
 *
 *  Created on: 2023年2月10日
 *      Author: 好
 */
#define LOG_TAG    "hmi_common"

#include "../common/hmi_common.h"

extern uint8_t Transducer_Setting_Status_Flag  ;   //传感器在设置状态

static type_slect_move_cursor slect_move_cursor_t;
static struct dev_address_reset_par common_dev_address_reset_par ;

static uint8_t Temp_Compensation_Slcet_buttons_cnt = 0 ;

static void Device_Addr_Reversion_SetMenu(MenuShow_t *ptShowInfo);
static void Device_Addr_Reversion_Enter_Page_Load(void);
static void Device_Addr_Reversion_Enter_Page_Exit(void);
static void Device_Addr_Reversion_Enter_Page_Task(void);
static void humiture_illumination_operation_status(int status);

static void Hmi_Slcet_Set_Buttons_CB( key_Input_Number_Typedef key_number , Key_Trg_Even key_state);
static void Hmi_Slcet_Enter_Window_Buttons_CB( key_Input_Number_Typedef key_number , Key_Trg_Even key_state);


void Return_Previous_Menu_Page_Load(void){
	Menu_Exit(true);	//退出到温度传感器设置菜单
	Menu_Exit(true);    //退出到外界参数设置菜单
}

void Back_Main_Page_Load(void){
	Menu_DeInit();			// 退出菜单
	hmi_enter_main_page();	// 进入主页
}

/* 设置菜单显示效果 */
static void Device_Addr_Reversion_SetMenu(MenuShow_t *ptShowInfo){
	show_refresh_time();
	show_eth_connect_state();
}



/********************************************** 切换页面 - 外界温度传感器设备地址复归页面  ***************************************************************/
/* 外界温度传感器设备地址复归菜单 */
static MenuList_t Dev_Addr_Reset_Menu_Table[] =
{
    {"确认复归", NULL, Device_Addr_Reversion_Enter_Page_Load, Device_Addr_Reversion_Enter_Page_Exit,Device_Addr_Reversion_Enter_Page_Task, NULL},

    {"返回上级菜单", NULL,  Return_Previous_Menu_Page_Load, NULL, NULL, NULL},

    {"返回主页面", NULL,  Back_Main_Page_Load,   NULL,   NULL, NULL},
};

void Device_Addr_Reversion_Load_Init(struct dev_address_reset_par *type_dev_address_reset_par_t ){
	common_dev_address_reset_par.setting_sleet_type_flag = type_dev_address_reset_par_t->setting_sleet_type_flag;
	common_dev_address_reset_par.setting_cursor_dev_var_addr = type_dev_address_reset_par_t->setting_cursor_dev_var_addr;
	common_dev_address_reset_par.setting_dev_reset_page = type_dev_address_reset_par_t->setting_dev_reset_page;
	common_dev_address_reset_par.auto_exit_setting_page_time = type_dev_address_reset_par_t->auto_exit_setting_page_time ;
	common_dev_address_reset_par.dev_addr_reset_wait_var_addr = type_dev_address_reset_par_t->dev_addr_reset_wait_var_addr;
	common_dev_address_reset_par.dev_addr_reset_success_var_addr = type_dev_address_reset_par_t->dev_addr_reset_success_var_addr;
	common_dev_address_reset_par.dev_addr_reset_error_var_addr = type_dev_address_reset_par_t->dev_addr_reset_error_var_addr;
	common_dev_address_reset_par.dev_reset_execute_function_cb = type_dev_address_reset_par_t->dev_reset_execute_function_cb ;
	log_d("sleet_type_flag=%d,",common_dev_address_reset_par.setting_sleet_type_flag);
}

void Device_Addr_Reversion_Page_Load(void){
	type_slect_move_cursor slect_move_cursor;
	slect_move_cursor.dw_cursor_adderss = common_dev_address_reset_par.setting_cursor_dev_var_addr ;
	slect_move_cursor.max_slect_move = 2 ;
	slect_move_cursor.min_slect_move = 0 ;
	slect_move_cursor.move_slect_step = 1 ;
	slect_move_cursor.now_slect_move = 0 ;
	slect_cursor_move_init(&slect_move_cursor);  						 //光标位置初始化
	dw_show_switching_pages(common_dev_address_reset_par.setting_dev_reset_page); //切换页面
	slect_cursor_move(cursor_default_mode,cursor_null);  				 //初始化选择设置光标
	Buttons_Register(KEY_UP_TRG_NUMBER,Hmi_Slcet_Set_Buttons_CB);
	Buttons_Register(KEY_ENTER_TRG_NUMBER,Hmi_Slcet_Set_Buttons_CB);
	Buttons_Register(KEY_DOWN_TRG_NUMBER,Hmi_Slcet_Set_Buttons_CB);
	Menu_Bind(Dev_Addr_Reset_Menu_Table, GET_MENU_NUM(Dev_Addr_Reset_Menu_Table), Device_Addr_Reversion_SetMenu);
}
void Device_Addr_Reversion_Page_Exit(void){
	common_dev_address_reset_par.dev_reset_execute_function_cb = NULL ;
}

void Device_Addr_Reversion_Page_Task(void){
	if(check_time_arrive(AUTO_EXIT_SETS_PAGE_TO_MAIN_PAGE_TIMER_NUMBER,common_dev_address_reset_par.auto_exit_setting_page_time*1000)){
		Back_Main_Page_Load();
	}
}
/************ 确定- 外界温度传感器设备地址复归  ****************/
static void Device_Addr_Reversion_Enter_Page_Load(void){
	log_d("sleet_type_flag=%d,Device_Addr_Reversion_Enter_Page_Load",common_dev_address_reset_par.setting_sleet_type_flag);
	Transducer_Setting_Status_Flag = 1 ;
	type_slect_move_cursor slect_move_cursor;
	slect_move_cursor.dw_cursor_adderss = common_dev_address_reset_par.setting_cursor_dev_var_addr ;
	slect_move_cursor.max_slect_move = 2 ;
	slect_move_cursor.min_slect_move = 0 ;
	slect_move_cursor.move_slect_step = 1 ;
	slect_move_cursor.now_slect_move = 0 ;
	slect_cursor_move_init(&slect_move_cursor);  		//光标位置初始化
	slect_cursor_move(cursor_refresh_mode,cursor_null);  //关闭光标
	Buttons_UnRegister(KEY_UP_TRG_NUMBER);
	Buttons_UnRegister(KEY_ENTER_TRG_NUMBER);
	Buttons_UnRegister(KEY_DOWN_TRG_NUMBER);
	Transducer_Operation_Status_Register(common_dev_address_reset_par.setting_sleet_type_flag,humiture_illumination_operation_status);
	common_dev_address_reset_par.dev_reset_execute_function_cb();
}

static void Device_Addr_Reversion_Enter_Page_Exit(void){
	dw_input_parameter_hint_window( 0 ,	common_dev_address_reset_par.dev_addr_reset_wait_var_addr , \
										common_dev_address_reset_par.dev_addr_reset_success_var_addr , \
										common_dev_address_reset_par.dev_addr_reset_error_var_addr ) ;
	Transducer_Operation_Status_UnRegister(common_dev_address_reset_par.setting_sleet_type_flag);
	Buttons_Register(KEY_ENTER_TRG_NUMBER,Hmi_Slcet_Enter_Window_Buttons_CB);
}

static void humiture_illumination_operation_status(int status){
	log_d("sleet_type_flag=%d,status=%d",common_dev_address_reset_par.setting_sleet_type_flag,status);
	dw_input_parameter_hint_window( status ,common_dev_address_reset_par.dev_addr_reset_wait_var_addr , \
											common_dev_address_reset_par.dev_addr_reset_success_var_addr , \
											common_dev_address_reset_par.dev_addr_reset_error_var_addr ) ;
	Buttons_Register(KEY_ENTER_TRG_NUMBER,Hmi_Slcet_Enter_Window_Buttons_CB);
}

static void Device_Addr_Reversion_Enter_Page_Task(void){
	if(check_time_arrive(AUTO_EXIT_SETS_PAGE_TO_MAIN_PAGE_TIMER_NUMBER,common_dev_address_reset_par.auto_exit_setting_page_time*1000)){
		Back_Main_Page_Load();
	}
}


static void Hmi_Slcet_Set_Buttons_CB( key_Input_Number_Typedef key_number , Key_Trg_Even key_state){
	if(key_state == KEY_CLICK_ACTION){
		//clear_time_cnt(AUTO_EXIT_SETS_PAGE_TO_MAIN_PAGE_TIMER_NUMBER);
		switch(key_number){
		case KEY_UP_TRG_NUMBER :
			slect_cursor_move(cursor_refresh_mode,cursor_up);
			Menu_SelectPrevious(true);
			break;
		case KEY_ENTER_TRG_NUMBER :
			Menu_Enter();
			break;
		case KEY_DOWN_TRG_NUMBER :
			slect_cursor_move(cursor_refresh_mode,cursor_down);
			Menu_SelectNext(true);
			break;
		default :
			slect_cursor_move(cursor_refresh_mode,cursor_up);
			Menu_SelectPrevious(true);
			break;
		}
	}
}

static void Hmi_Slcet_Enter_Window_Buttons_CB( key_Input_Number_Typedef key_number , Key_Trg_Even key_state){
	if(key_state == KEY_CLICK_ACTION){
		//clear_time_cnt(AUTO_EXIT_SETS_PAGE_TO_MAIN_PAGE_TIMER_NUMBER);
		switch(key_number){
		case KEY_ENTER_TRG_NUMBER :
			Menu_Exit(true);
			Transducer_Setting_Status_Flag = 0 ;
			break;
		default :
			//Menu_Exit(true);
			break;
		}
	}
}


void show_eth_connect_state(void){
	static uint8_t old_eth_connect_state = 0 ;

	if(old_eth_connect_state != type_dw_switch_ico.cascading_connection_state){
		old_eth_connect_state = type_dw_switch_ico.cascading_connection_state;
		dw_show_eth_connect_state(type_dw_switch_ico.cascading_connection_state);
	}
}

void show_refresh_time(void){
	if(check_time_arrive(REFERSH_DW_DISPLAY_TIME_NUMBER,REFERSH_DW_DISPLAY_TIME)){
		dw_show_time_adderss();
		clear_time_cnt(REFERSH_DW_DISPLAY_TIME_NUMBER);
	}
}


void slect_cursor_move_init(type_slect_move_cursor *move_cursor_t ){
	slect_move_cursor_t.max_slect_move = move_cursor_t->max_slect_move ;
	slect_move_cursor_t.min_slect_move = move_cursor_t->min_slect_move;
	slect_move_cursor_t.move_slect_step = move_cursor_t->move_slect_step ;
	slect_move_cursor_t.now_slect_move = move_cursor_t->now_slect_move ;
	slect_move_cursor_t.dw_cursor_adderss = move_cursor_t->dw_cursor_adderss ;
}
void default_now_slect_cursor_move(type_slect_move_cursor *move_cursor_t){

	slect_move_cursor_t.now_slect_move = move_cursor_t->now_slect_move ;
}

uint8_t slect_cursor_move(type_cursor_show_mode restore_default_enable ,Cursor_Action cursor_action){
	 if(restore_default_enable == cursor_default_mode ){
		 dw_setting_slect_var(slect_move_cursor_t.dw_cursor_adderss,0); //更新选择的光标
	 }else if(restore_default_enable == cursor_refresh_mode ){
		if(cursor_action == cursor_up){
			if( slect_move_cursor_t.now_slect_move > slect_move_cursor_t.min_slect_move )
				slect_move_cursor_t.now_slect_move -=slect_move_cursor_t.move_slect_step;
			else {
				slect_move_cursor_t.now_slect_move  = slect_move_cursor_t.max_slect_move  ;
			}
		}else if(cursor_action == cursor_down){
			slect_move_cursor_t.now_slect_move+=slect_move_cursor_t.move_slect_step;
			if(slect_move_cursor_t.now_slect_move > slect_move_cursor_t.max_slect_move  ){
				slect_move_cursor_t.now_slect_move = slect_move_cursor_t.min_slect_move  ;
			}
		}else if(cursor_action == cursor_null){
			slect_move_cursor_t.now_slect_move = slect_move_cursor_t.max_slect_move+1 ;
		}else;
		dw_setting_slect_var(slect_move_cursor_t.dw_cursor_adderss,slect_move_cursor_t.now_slect_move); //更新选择的光标
	 }
	return slect_move_cursor_t.now_slect_move;
}



int user_parameter_adjustment(int parameter_adj_date ,bool enable_symbol, uint8_t digit_wide, uint8_t key_number ,ShowUserSetPar ShowUserSetPar_t){
#define MAX_BUFF 20
	int date_buff[MAX_BUFF]={0};
	int n = 0 ,m=0;
	bool symbol_flag = 0 ;
	bool tmp_falg  =0 ;
	int par_tmp = 0 ;
	int multiple = 1 ;
	uint8_t wide_tmp = 0 ;

	if(digit_wide >MAX_BUFF){
		log_e("input digit_wide error !! ");
		return -1 ;
	}
	if(enable_symbol){
		tmp_falg = 0 ;
		if(parameter_adj_date >0){
			symbol_flag = 0 ;
		}else{
			symbol_flag = 1 ;
		}
	}
	while(parameter_adj_date!=0){
		m = parameter_adj_date%10;
		date_buff[n] = m ;
		n++ ;
		parameter_adj_date /= 10;
	}

	switch(key_number){
		case KEY_UP_TRG_NUMBER :
			if(enable_symbol){
				if(Temp_Compensation_Slcet_buttons_cnt == 0 ){
					tmp_falg = 1 ;
					symbol_flag = !symbol_flag ;
				}else{
					date_buff[Temp_Compensation_Slcet_buttons_cnt-1]++;
					if( date_buff[Temp_Compensation_Slcet_buttons_cnt-1] >9)
						date_buff[Temp_Compensation_Slcet_buttons_cnt-1] = 0 ;
				}
			}else{
				date_buff[Temp_Compensation_Slcet_buttons_cnt]++;
				if( date_buff[Temp_Compensation_Slcet_buttons_cnt] >9)
					date_buff[Temp_Compensation_Slcet_buttons_cnt] = 0 ;
			}
		break;
		case KEY_ENTER_TRG_NUMBER :
			if(enable_symbol){
				wide_tmp = digit_wide ;
			}else{
				wide_tmp = digit_wide -1 ;
			}
			Temp_Compensation_Slcet_buttons_cnt++ ;
			if(Temp_Compensation_Slcet_buttons_cnt >wide_tmp){
				 Temp_Compensation_Slcet_buttons_cnt = 0 ;
				Menu_Exit(true);
			}else{
				slect_cursor_move(cursor_refresh_mode,cursor_down);
			}
		break;
		case KEY_DOWN_TRG_NUMBER :
			if(enable_symbol){
				if(Temp_Compensation_Slcet_buttons_cnt == 0 ){
					tmp_falg = 1 ;
					symbol_flag = !symbol_flag ;
				}else{
					date_buff[Temp_Compensation_Slcet_buttons_cnt-1]--;
					if( date_buff[Temp_Compensation_Slcet_buttons_cnt-1] <0)
						date_buff[Temp_Compensation_Slcet_buttons_cnt-1] = 9 ;
				}
			}else{
				date_buff[Temp_Compensation_Slcet_buttons_cnt]--;
				if( date_buff[Temp_Compensation_Slcet_buttons_cnt] <0)
					date_buff[Temp_Compensation_Slcet_buttons_cnt] = 9 ;
			}
		break;
		default :
		slect_cursor_move(cursor_refresh_mode,cursor_down);
		break;
	}
	if( digit_wide > 1 ){
		for(uint8_t i = 1 ; i<digit_wide;i++){
			multiple *=10 ;
			par_tmp = par_tmp+date_buff[i]*multiple ;
		}
		par_tmp+=date_buff[0];
	}else{
		par_tmp=date_buff[0];
	}

	if(enable_symbol){
		if(tmp_falg){
			if(symbol_flag ){
				par_tmp = POSITIVE_CONVERT_MINUS( par_tmp );
			}else{
				par_tmp = MINUS_CONVERT_POSITIVE( par_tmp);
			}
		}
	}
	ShowUserSetPar_t(par_tmp);
	return par_tmp ;
}

void clearn_Temp_Compensation_Slcet_buttons_cnt(void){
	Temp_Compensation_Slcet_buttons_cnt = 0 ;
}

int *ip_str_analysis_number(char *ip_setting_str){
	static int tmp[4]={0};
	char dest[]= {""} ;

	char * str_sp = NULL ;


	for(uint8_t i=0;i<3;i++){
		str_sp = strstr(ip_setting_str ,".");
		if(str_sp==NULL){
			//return  ;
		}
		strncpy(dest, ip_setting_str, (sizeof(char) *(str_sp - ip_setting_str)));
		tmp[i]= atoi(dest);
		ip_setting_str = str_sp+1 ;
		memcpy(dest, "", 3) ;
	}
	tmp[3]= atoi(ip_setting_str);
	return tmp ;
}
