/*
 * dw_display_task.c
 *
 *  Created on: 2023年1月6日
 *      Author: 好
 */
#define LOG_TAG    "dw_display_task"

#include "../task/dw_display_task.h"


uint8_t Transducer_Setting_Status_Flag = 0 ;   //传感器在设置状态

static uint8_t enter_main_menu_flag = 0 ;	//进入菜单标志位
static uint8_t exitinguish_display_flag  = 0 ;  //熄屏标志位
static uint8_t run_cnt_flag = 0 ;
static system_para_def system_para_t ;

static MainMenuCfg_t tMainMenu;


static void dw_display_hmi_init(void);

static void Hmi_Enter_Main_Set_Buttons_CB(key_Input_Number_Typedef key_number ,Key_Trg_Even key_state);
static void hmi_Clearn_Auto_Exit_Setting_Page_Cb(void);
static void transducer_init(void);

static void external_temperature_humidity_data(uint16_t humiture_online_timeout);
static void interior_temperature_humidity_data(uint16_t humiture_online_timeout);
static void show_illumination_transducer_gread(uint8_t illumination_percentage,uint16_t illumination_online_timeout);
static void show_sleet_transducer_state(uint16_t sleet_online_timeout);

static void user_buttons_register(void);
static void show_work_mode_state(void);



void hmi_enter_main_page(void){
	enter_main_menu_flag = 0 ;
    dw_show_switching_pages(PAGE_MAIN_NUMBER); //切换页面
    user_buttons_register();					//用户按键注册
	dw_show_ip_adderss();						//显示IP地址
}


void create_dw_display_pthread_init(void){
	//(1)timer thread
	pthread_t dw_display_id;

	enter_main_menu_flag = 0 ;
	dw_display_hmi_init();
	read_saveenv_cjson_system_parameter(&system_para_t);
	dw_control_display_luminance_date( system_para_t.DisplayBrightnessDate );
	hmi_enter_main_page();
	app_fna_motor_init();
	dw_external_humiture_online_state_var(0);  //关闭外界不在线图标
	dw_internal_humiture_online_state_var(0); //关闭内部不在线图标

	int dw_display = pthread_create(&dw_display_id,NULL,dw_display_task,NULL);
	if(dw_display){
		perror("dw_display_task error:");
		log_e("dw_display_task thread created error !.");
		exit(EXIT_FAILURE);
	}
	log_d("dw_display_task thread created.");
}







void* dw_display_task(void *arg) {
	external_para_def external_para_def_t ;
	internal_para_def internal_para_def_t ;
	while(1){
		if(check_time_arrive(SCAN_MENU_TASK_TIME_NUMBER,SCAN_MENU_TASK_TIME)){
			Menu_Task();
			clear_time_cnt(SCAN_MENU_TASK_TIME_NUMBER);
		}
		read_saveenv_cjson_system_parameter(&system_para_t);
		if(check_time_arrive(AUTO_EXTINGUISH_DISPLAY_TIMER_NUMBER,system_para_t.AutomaticallyExtinguishTimeDate *60000)){
			if(!run_cnt_flag){
				exitinguish_display_flag =1 ;
				enter_main_menu_flag = 0 ;
				dw_control_display_luminance_date( 0 );
				Back_Main_Page_Load();
				run_cnt_flag = 1 ;
			}

		}
		deal_transducer_masg_t.fan_velocity=Show_Fan_Motor_Velocity_Date_Task(!enter_main_menu_flag,FAN_MOTOR_REFRESH_VELOCITY_TIMER);
		Moistureproof_state_animation_Task(!enter_main_menu_flag);
		show_refresh_time();
		show_eth_connect_state();
		if(Transducer_Setting_Status_Flag){	//在设置状态
			clear_time_cnt(CHECK_EX_HUMITURE_ONLINE_TIMEOUT_TIMER_NUMBER);
			clear_time_cnt(CHECK_IN_HUMITURE_ONLINE_TIMEOUT_TIMER_NUMBER);
			clear_time_cnt(CHECK_ILLUMINATION_ONLINE_TIMEOUT_TIMER_NUMBER);
			clear_time_cnt(CHECK_SLEET_ONLINE_TIMEOUT_TIMER_NUMBER);
		}else{
			read_saveenv_cjson_external_parameter(&external_para_def_t);
			read_saveenv_cjson_internal_parameter(&internal_para_def_t);
			external_temperature_humidity_data(TRANSDUCER_OFFLINE_TIMEOUT+external_para_def_t.ExternalHumitureSampleRate);
			interior_temperature_humidity_data(TRANSDUCER_OFFLINE_TIMEOUT+internal_para_def_t.InternalHumitureSampleRate);
			show_illumination_transducer_gread(deal_transducer_masg_t.illumination_par_t.illumination_percentage,TRANSDUCER_OFFLINE_TIMEOUT+external_para_def_t.ExternalIlluminationSampleRate);
			show_sleet_transducer_state(TRANSDUCER_OFFLINE_TIMEOUT+external_para_def_t.ExternalSleetSampleRateDate);
		}
		show_work_mode_state();
	}
}



static void user_buttons_register(void){
	Buttons_Register(KEY_UP_TRG_NUMBER,Hmi_Enter_Main_Set_Buttons_CB);
	Buttons_Register(KEY_ENTER_TRG_NUMBER,Hmi_Enter_Main_Set_Buttons_CB);
	Buttons_Register(KEY_DOWN_TRG_NUMBER,Hmi_Enter_Main_Set_Buttons_CB);

	Buttons_Trg_Register(hmi_Clearn_Auto_Exit_Setting_Page_Cb);	//清除返回主页时间和亮度计时
}

static void dw_display_hmi_init(void){

	transducer_init();

    tMainMenu.pszDesc = "参数设置";
    tMainMenu.pszEnDesc = "Main Menu Config";
    tMainMenu.pfnLoadCallFun = Hmi_Enter_Menuconfig_Page_Load;	//进入菜单密码验证界面
    tMainMenu.pfnRunCallFun = Hmi_Enter_Menuconfig_Page_Task;
    log_d("hmi_main_init ");
//    Menu_ShortcutEnter(true, 2, 3, 0); // 开机通过快捷菜单索引进入语言选择界面
}

static void Hmi_Enter_Main_Set_Buttons_CB(key_Input_Number_Typedef key_number ,Key_Trg_Even key_state){
	if(key_state == KEY_CLICK_ACTION){
		switch(key_number){
		case KEY_UP_TRG_NUMBER :
			break;
		case KEY_ENTER_TRG_NUMBER :
			if(!exitinguish_display_flag){
				log_d("enter main setting page.");
				if (!Menu_IsRun()){		//进入菜单
					enter_main_menu_flag = 1 ;
					Menu_Init(&tMainMenu);
				}
			}else{
				run_cnt_flag = 0 ;
				exitinguish_display_flag = 0 ;
				dw_control_display_luminance_date(system_para_t.DisplayBrightnessDate );
				Back_Main_Page_Load();
			}
			break;
		case KEY_DOWN_TRG_NUMBER :
			break;
		default :
			break;
		}
	}
}

static void hmi_Clearn_Auto_Exit_Setting_Page_Cb(void){
	clear_time_cnt(AUTO_EXIT_SETS_PAGE_TO_MAIN_PAGE_TIMER_NUMBER);
	clear_time_cnt(AUTO_EXTINGUISH_DISPLAY_TIMER_NUMBER);
	//log_i("clear auto exit main page time");
}




static void transducer_init(void){

	transducer_decive_t.dev_adderss_alter_flag = 0 ;
	transducer_decive_t.humiture_illumination_factory_ack_flag = 0 ;
	transducer_decive_t.humiture_illumination_soft_reset_ack_flag = 0 ;
	transducer_decive_t.humiture_illumination_adderss_ack_flag = 0 ;

	transducer_decive_t.sleet_adderss_alter_flag = 0;
	transducer_decive_t.sleet_trg_buad_flag = 0 ;
	transducer_decive_t.sleet_buad_ack_flag = 0;

}





static void external_temperature_humidity_data(uint16_t humiture_online_timeout){
	static int old_external_temperature = 0 ,old_external_humidity=0;
	static uint8_t  external_online_show_flag =0 ;

	if( deal_transducer_masg_t.dev_online_ack_flag[external_temperature_transducer] == ack ){
		deal_transducer_masg_t.dev_online_ack_flag[external_temperature_transducer] = nack ;
		deal_transducer_masg_t.dev_online_state[external_temperature_transducer] = online ;
		if(external_online_show_flag){
			external_online_show_flag = 0 ;
			dw_external_humiture_online_state_var(0);
			log_w("external temperature online ");
		}
		if(deal_transducer_masg_t.external_temperature_date != old_external_temperature){
			dw_show_external_temperature();
			old_external_temperature = deal_transducer_masg_t.external_temperature_date;
		}
		if(deal_transducer_masg_t.external_humidity_date != old_external_humidity){
			dw_show_external_humidity();
			old_external_humidity = deal_transducer_masg_t.external_humidity_date;
		}
		clear_time_cnt(CHECK_EX_HUMITURE_ONLINE_TIMEOUT_TIMER_NUMBER);
	}

	if(!external_online_show_flag){
		if(check_time_arrive(CHECK_EX_HUMITURE_ONLINE_TIMEOUT_TIMER_NUMBER,humiture_online_timeout)){
			external_online_show_flag =1 ;
			dw_external_humiture_online_state_var(1);
			deal_transducer_masg_t.dev_online_state[external_temperature_transducer] = offline ;
			log_w("external temperature offline !!");
		}
	}

}


static void interior_temperature_humidity_data(uint16_t humiture_online_timeout){
	static int old_interior_temperature = 0 ,old_interior_humidity=0;
	static uint8_t  internal_online_show_flag =0 ;
//	if( deal_transducer_masg_t.dev_online_state[interior_temperature_transducer] == online){
	if( deal_transducer_masg_t.dev_online_ack_flag[interior_temperature_transducer] == ack ){
		deal_transducer_masg_t.dev_online_ack_flag[interior_temperature_transducer] = nack ;
		deal_transducer_masg_t.dev_online_state[interior_temperature_transducer] = online ;
		if(internal_online_show_flag){
			internal_online_show_flag = 0 ;
			dw_internal_humiture_online_state_var(0);
			log_w("internal temperature online ");
		}
		if(deal_transducer_masg_t.internal_temperature_date != old_interior_temperature){
			dw_show_interior_temperature();
			old_interior_temperature = deal_transducer_masg_t.internal_temperature_date;
		}
		if(deal_transducer_masg_t.internal_humidity_date != old_interior_humidity){
			dw_show_interior_humidity();
			old_interior_humidity = deal_transducer_masg_t.internal_humidity_date;
		}
		clear_time_cnt(CHECK_IN_HUMITURE_ONLINE_TIMEOUT_TIMER_NUMBER);
	}
	if(!internal_online_show_flag){
		if(check_time_arrive(CHECK_IN_HUMITURE_ONLINE_TIMEOUT_TIMER_NUMBER,humiture_online_timeout)){
			internal_online_show_flag =1 ;
			dw_internal_humiture_online_state_var(1);
			deal_transducer_masg_t.dev_online_state[interior_temperature_transducer] = offline ;
			log_w("internal temperature offline !!");
		}
	}

}

static void show_illumination_transducer_gread(uint8_t illumination_percentage,uint16_t illumination_online_timeout){
	static uint8_t old_illumination_transducer_gread = 0 ;
	static uint8_t  illumination_online_show_flag =0 ;

//	if( deal_transducer_masg_t.dev_online_state[illumination_transducer] == online){
	if( deal_transducer_masg_t.dev_online_ack_flag[illumination_transducer] == ack ){
		deal_transducer_masg_t.dev_online_ack_flag[illumination_transducer] = nack ;
		deal_transducer_masg_t.dev_online_state[illumination_transducer] = online ;
		if((illumination_percentage != old_illumination_transducer_gread) ||(illumination_online_show_flag)){
		    dw_show_illumination_transducer(illumination_percentage);
		    old_illumination_transducer_gread = illumination_percentage;
		}
		if(illumination_online_show_flag){
			illumination_online_show_flag = 0 ;
			log_w("illumination online ");
		}
		clear_time_cnt(CHECK_ILLUMINATION_ONLINE_TIMEOUT_TIMER_NUMBER);
	}
	if(!illumination_online_show_flag){
		if(check_time_arrive(CHECK_ILLUMINATION_ONLINE_TIMEOUT_TIMER_NUMBER,illumination_online_timeout)){
			illumination_online_show_flag =1 ;
			dw_illumination_transducer(5);
			deal_transducer_masg_t.dev_online_state[illumination_transducer] = offline ;
			log_w("illumination offline !!");
		}
	}

}

static void show_sleet_transducer_state(uint16_t sleet_online_timeout){
	static bool old_sleet_transducer_state = 0 ;
	static uint8_t sleet_online_show_flag =0 ;

	if( deal_transducer_masg_t.dev_online_ack_flag[sleet_transducer] == ack ){
		deal_transducer_masg_t.dev_online_ack_flag[sleet_transducer] = nack ;
		deal_transducer_masg_t.dev_online_state[sleet_transducer] = online ;
		if((deal_transducer_masg_t.sleet_state != old_sleet_transducer_state) ||(sleet_online_show_flag)){
			dw_show_sleet_transducer();
		    old_sleet_transducer_state = deal_transducer_masg_t.sleet_state;
		}
		if(sleet_online_show_flag){
			sleet_online_show_flag = 0 ;
			log_w("sleet online ");
		}
		clear_time_cnt(CHECK_SLEET_ONLINE_TIMEOUT_TIMER_NUMBER);
	}else{
		if(!sleet_online_show_flag){
			if(check_time_arrive(CHECK_SLEET_ONLINE_TIMEOUT_TIMER_NUMBER,sleet_online_timeout)){
				sleet_online_show_flag =1 ;
				dw_sleet_transducer(2);
				deal_transducer_masg_t.dev_online_state[sleet_transducer] = offline ;
				log_w("sleet offline !!");
			}
		}
	}

}

static void show_work_mode_state(void){
	static int old_work_mode_status = -1 ;
	if( deal_transducer_masg_t.local_run_mode != old_work_mode_status ){
		old_work_mode_status =deal_transducer_masg_t.local_run_mode ;
		switch(old_work_mode_status){
		case RUN_FIX_MODE :
			dw_check_mode_state_var(1);
			break;
		case RUN_WORK_MODE :
			dw_check_mode_state_var(0);
			break;
		case RUN_REMOTE_CONTROL_MODE :
			dw_check_mode_state_var(2);
			break;
		default : break;
		}

	}
}







