


#define LOG_TAG    "main"

#include "../task/main.h"


#define PROGRAM_VERSION "Moistureproof_Cover_Plate V1.0.5"
#define HARDWARE_VERSION "Moistureproof_cover_plate_V1.0 2022/11/15"



extern uint8_t switch_mode;
extern struct moistureproof_state  moistureproof_state_type ;

static system_para_def SystemSetParam_t ;

GetInformMqttMasgEven GetInformMqttMasgEven_t={0};


static void get_saveenv_system_parameter_init(void);


static void get_saveenv_system_parameter_init(void){
 config_init();
}


int main(int argc, char *argv[])
{

	struct tm sys_time;

	union RemoteVariateTrgFlag {
	    struct {
	        uint8_t remote_timer_arrive_trg_flag : 1;		//远程控制设定时间到达标志位
			uint8_t motor_motion_trg_flag :1 ;       		//电机运动触发标志位
			uint8_t clear_remote_test_timer_flag: 1;		//清除远程控制时间标志位
			uint8_t cancel_fix_mode_trg_flag :1 ;    		//取消检修模式触发标志位
			uint8_t illumination_close_motro_trg_flag :1 ;	//光照检测触发电机关闭标志位
			uint8_t humidity_close_motro_trg_flag :1 ;		//湿度检测触发电机关闭标志位
			uint8_t temperature_close_motro_trg_flag :1 ;	//温度检测触发电机关闭标志位
			uint8_t recover_auto_control_status_flag:1 ;	//
	    } bits;
	    uint8_t byte;
	};

	union CloseMotorTgrFlag {
	    struct {
	        uint8_t temperature_close_timer_arrive_trg_flag : 1;	//温度关闭延时到达触发标志位
			uint8_t temperature_open_trg_flag : 1;					//温度判断打开触发标志位
			uint8_t humidity_close_timer_arrive_trg_flag : 1;		//湿度关闭延时到达触发标志位
			uint8_t humidity_open_trg_flag : 1;						//湿度判断打开触发标志位
			uint8_t system_timer_close_trg_flag : 1;				//本地时间判断关闭触发标志位
			uint8_t illumination_close_timer_arrive_trg_flag : 1;	//光照关闭延时到达触发标志位
			uint8_t sleet_close_trg_flag : 1;						//雨雪判断关闭触发标志位
			uint8_t fix_mode_close_trg_flag : 1;					//检修模式触发关闭标志位
	    } bits;
	    uint8_t byte;
	};
	static union RemoteVariateTrgFlag RemoteVariateTrgFlag_t = {
			.byte = 0 ,
	};
	static union CloseMotorTgrFlag CloseMotorTgrFlag_t  = {
			.byte = 0 ,
	};

	static uint8_t fix_mode_trg_flag = 0 ;  //检修模式触发标志位
	static uint8_t program_execution_steps = system_motor_reset_step ;
	static int old_motor_action_type = -1 ;

	uint8_t temperature_difference_c ;
	uint8_t humidity_k ;
	for (int i = 1; i < argc; ++i) {
		if (strcmp(argv[i], "-v") == 0 || strcmp(argv[i], "--version") == 0) {
			printf("Program Version: %s, Built on: %s at %s\nHardware Version: %s\n", PROGRAM_VERSION, __DATE__, __TIME__,HARDWARE_VERSION);
			return 0;
		}
	}
	easylogger_init();
	log_d("Start Moistureproof cover plate Syatem Init  .");
	printf("Program Version: %s,Built on: %s at %s\nHardware Version: %s\n", PROGRAM_VERSION, __DATE__, __TIME__,HARDWARE_VERSION);
	get_saveenv_system_parameter_init();
	set_sys_eth0_init();
	dev_buzz_init();
	rgb_led_init();
	//dev_set_buzz_frq(500);
	//dev_control_buzz_state(BUZZ_BLINK_DISABLE,BUZZ_ON);
	dw_function_init();
	uart_device_init(tty_dw_device);
	uart_device_init(rs485_bus_device);
	create_my_timer_pthread_init();
	create_get_scan_event_pthread_init();
	create_dw_display_pthread_init();
	create_deal_rs485_masg_pthread_init();
	create_listen_rs485_masg_pthread_init();
	create_mqtt_pub_pthread_init();
	log_d("Moistureproof cover plate Syatem Init Finsh .");
	while(1){
		Show_Rgb_Led_Main(GetInformMqttMasgEven_t.show_rgb_led_mode);
		switch ( program_execution_steps ) {
			case system_motor_reset_step :        //复位盖板状态
				if(motor_reset()){
					program_execution_steps = system_read_config_step ;
					log_d("now is motor reseting !");
				}
				break;
			case system_read_config_step :			//读取设定存储参数
				read_saveenv_cjson_system_parameter(&SystemSetParam_t);
				program_execution_steps = system_check_work_mode_step ;

				break;
			case system_check_work_mode_step :		//判断工作模式条件
				if(switch_mode == WORK_MODE ){
					if(fix_mode_trg_flag){  		//触发过检修模式
						CloseMotorTgrFlag_t.bits.fix_mode_close_trg_flag =0 ;
						RemoteVariateTrgFlag_t.bits.clear_remote_test_timer_flag = 0 ;
						program_execution_steps = system_running_fixd_mode_step ;
						log_d("fix trg   !");
					}else{
						if(GetInformMqttMasgEven_t.remote_test_flag ){  //远程测试模式
							deal_transducer_masg_t.local_run_mode = RUN_REMOTE_CONTROL_MODE ;
							program_execution_steps = system_running_remote_test_step ;
							GetInformMqttMasgEven_t.show_rgb_led_mode = RGB_REMOTE_MODE ;
						}else{
							if(RemoteVariateTrgFlag_t.bits.recover_auto_control_status_flag){
								RemoteVariateTrgFlag_t.byte = 0 ;
								CloseMotorTgrFlag_t.byte = 0 ;
							}
							GetInformMqttMasgEven_t.test_motor_delay_T4_date = 0 ;  		//清除远程测试时间
							GetInformMqttMasgEven_t.show_rgb_led_mode = RGB_WORK_MODE ;
							deal_transducer_masg_t.local_run_mode = RUN_WORK_MODE ;
							program_execution_steps = system_check_sleet_transducer_step ;	 //自动模式
						}
					}
				}else{
					if( CloseMotorTgrFlag_t.bits.fix_mode_close_trg_flag == 0  ){
						CloseMotorTgrFlag_t.bits.fix_mode_close_trg_flag =1 ;
						fix_mode_trg_flag =1 ;
						RemoteVariateTrgFlag_t.bits.clear_remote_test_timer_flag = 0 ;
						RemoteVariateTrgFlag_t.bits.cancel_fix_mode_trg_flag = 0 ;
						Motor_Move( MOTOR_STOP ,0);  		//盖板关闭
						Control_Fna_Motor(0);               //风机停止
						log_d(" now is fix mode  ,motor stop ");
						deal_transducer_masg_t.local_run_mode = RUN_FIX_MODE ;
						GetInformMqttMasgEven_t.show_rgb_led_mode = RGB_CHECK_MODE ;
						//取消远程控制命令
						if(GetInformMqttMasgEven_t.remote_test_flag==1){
							GetInformMqttMasgEven_t.remote_test_flag = 0 ;
							GetInformMqttMasgEven_t.test_motor_delay_T4_date = 0 ;
						}

					}
				}
				break;
			case system_check_sleet_transducer_step :								//判断雨雪传感器条件
				if( deal_transducer_masg_t.dev_online_state[sleet_transducer] ){	//判断是否在线
					if(!deal_transducer_masg_t.sleet_state){    					//雨雪传感器未触发
						CloseMotorTgrFlag_t.bits.sleet_close_trg_flag = 0 ;
						if(SystemSetParam_t.SetIlluminationControlEnable){			//判断光照传感器是否使能
							program_execution_steps = system_check_illumination_transducer_step ;
						}else{
							if(SystemSetParam_t.SetSystemTimeControlEnable){		//判断本地时间是否使能
								program_execution_steps = system_check_sys_timer_step ;
							}else{
								program_execution_steps = system_check_humidity_transducer_step ;
							}
						}
					}else{
						if(moistureproof_state_type.moistureproof_state_close_limit){  //盖板开启状态
							if(CloseMotorTgrFlag_t.bits.sleet_close_trg_flag == 0  ){
								CloseMotorTgrFlag_t.bits.sleet_close_trg_flag = 1 ;
								Control_Fna_Motor(0);               //风机停止
								Motor_Move( MOTOR_FORWORD ,100);  //盖板关闭
								log_d("sleet trigger ,motor close ");
							}
						}
						program_execution_steps = system_read_config_step ;
					}
				}else{
					program_execution_steps = system_read_config_step ;
				}
				break;
			case system_check_illumination_transducer_step :								//判断光照强度条件
				if( deal_transducer_masg_t.dev_online_state[illumination_transducer] ){		//是否在线
					if( deal_transducer_masg_t.illumination_par_t.illumination_percentage <= SystemSetParam_t.SetCloseIlluminationLX1){  //小于设定基准值，关闭
						if( moistureproof_state_type.moistureproof_state_close_limit ){  //盖板状态
							if(RemoteVariateTrgFlag_t.bits.illumination_close_motro_trg_flag == 0  ){
								RemoteVariateTrgFlag_t.bits.illumination_close_motro_trg_flag =1 ;
								CloseMotorTgrFlag_t.bits.illumination_close_timer_arrive_trg_flag = 0 ;
								clear_time_cnt(CLOSE_MOTOR_DELAY_T2_TIMER_NUMBER);
							}
							if(check_time_arrive(CLOSE_MOTOR_DELAY_T2_TIMER_NUMBER,SystemSetParam_t.SetCloseIlluminationDelayDateT2 *1000)){
								if( CloseMotorTgrFlag_t.bits.illumination_close_timer_arrive_trg_flag == 0 ){
									CloseMotorTgrFlag_t.bits.illumination_close_timer_arrive_trg_flag = 1 ;
									Control_Fna_Motor(0);               //风机停止
									Motor_Move( MOTOR_FORWORD ,100);  //盖板关闭
									RemoteVariateTrgFlag_t.bits.illumination_close_motro_trg_flag = 0 ;
									log_d("illumination trigger ,motor close ");
								}
							}
						}
						program_execution_steps = system_read_config_step ;
					}else if( deal_transducer_masg_t.illumination_par_t.illumination_percentage > SystemSetParam_t.SetOpenIlluminationLX2){
						RemoteVariateTrgFlag_t.bits.illumination_close_motro_trg_flag = 0 ;
						if(SystemSetParam_t.SetSystemTimeControlEnable){		//判断本地时间是否使能
							program_execution_steps = system_check_sys_timer_step ;
						}else{
							program_execution_steps = system_check_humidity_transducer_step ;
						}
						//log_d("enter illumination check = %d ",program_execution_steps);
					}else{
						RemoteVariateTrgFlag_t.bits.illumination_close_motro_trg_flag = 0 ;
						program_execution_steps = system_read_config_step ;
					}
				}else{
					RemoteVariateTrgFlag_t.bits.illumination_close_motro_trg_flag = 0 ;
					program_execution_steps = system_read_config_step ;
				}
				break;
			case system_check_sys_timer_step :		//本地时间判断条件
				read_sys_time( &sys_time );		//获取本地时钟
				if( ( (sys_time.tm_hour >=0)&&( sys_time.tm_hour < SystemSetParam_t.SetCloseAMSysTimeDateS1)) \
					|| (  ( sys_time.tm_hour <24 )&&( sys_time.tm_hour >=SystemSetParam_t.SetClosePMSysTimeDateS2 ) )){
					if( moistureproof_state_type.moistureproof_state_close_limit ){  //盖板状态
						if( CloseMotorTgrFlag_t.bits.system_timer_close_trg_flag == 0  ){
							CloseMotorTgrFlag_t.bits.system_timer_close_trg_flag = 1 ;
							Control_Fna_Motor(0);               //风机停止
							Motor_Move( MOTOR_FORWORD ,100);  //盖板关闭
							log_d("system time trigger ,motor close ");
						}
					}
					program_execution_steps = system_read_config_step ;
				}else{
					CloseMotorTgrFlag_t.bits.system_timer_close_trg_flag = 0 ;
					program_execution_steps = system_check_humidity_transducer_step ;
					//log_d("enter timer chaeck  ");
				}
				break;
			case system_check_humidity_transducer_step :		//内外湿度判断条件
				if((deal_transducer_masg_t.dev_online_state[external_temperature_transducer])&&( deal_transducer_masg_t.dev_online_state[interior_temperature_transducer] )){
					if( deal_transducer_masg_t.internal_humidity_date >= deal_transducer_masg_t.external_humidity_date){
						humidity_k = deal_transducer_masg_t.internal_humidity_date - deal_transducer_masg_t.external_humidity_date ;
						if(humidity_k <= SystemSetParam_t.SetCloseHumidityDateK1){
							goto _humiture_close_motor;  //跳转到关闭盖板延时
						}else if(  (humidity_k > SystemSetParam_t.SetCloseHumidityDateK1)&&(humidity_k < SystemSetParam_t.SetOpeneHumidityDateK2) ){
							RemoteVariateTrgFlag_t.bits.humidity_close_motro_trg_flag = 0  ;
							program_execution_steps = system_check_temperature_transducer_step  ;
						}else if(  humidity_k >= SystemSetParam_t.SetOpeneHumidityDateK2 ){
							program_execution_steps = system_read_config_step  ;
							RemoteVariateTrgFlag_t.bits.humidity_close_motro_trg_flag = 0  ;
							if( moistureproof_state_type.moistureproof_state_open_limit ){ 	//盖板未完全打开
								if( CloseMotorTgrFlag_t.bits.humidity_open_trg_flag == 0 ){
									Motor_Move( MOTOR_RESERSE ,100);  	//盖板开启
									CloseMotorTgrFlag_t.bits.humidity_open_trg_flag = 1 ;
									log_d("humidity trigger ,motor open ");
								}
							}else{
								if( CloseMotorTgrFlag_t.bits.humidity_open_trg_flag == 1){
									Control_Fna_Motor(100);           //风机打开
									CloseMotorTgrFlag_t.bits.humidity_open_trg_flag = 0 ;
									log_d("humidity trigger ,fan open ");
								}
							}
						}else{
							RemoteVariateTrgFlag_t.bits.humidity_close_motro_trg_flag = 0  ;
							program_execution_steps = system_read_config_step  ;
						}
					}else{
						_humiture_close_motor:
						program_execution_steps = system_read_config_step  ;
						if( moistureproof_state_type.moistureproof_state_close_limit ){  //盖板开启状态
							if( RemoteVariateTrgFlag_t.bits.humidity_close_motro_trg_flag == 0  ){
								RemoteVariateTrgFlag_t.bits.humidity_close_motro_trg_flag = 1  ;
								CloseMotorTgrFlag_t.bits.humidity_close_timer_arrive_trg_flag = 0 ;
								clear_time_cnt(CLOSE_MOTOR_DELAY_T3_TIMER_NUMBER);
								log_d("hunidity control trg clear timer ");
							}
							if(check_time_arrive(CLOSE_MOTOR_DELAY_T3_TIMER_NUMBER,SystemSetParam_t.SetCloseHumidityDelayDateT3 *1000)){
								if( CloseMotorTgrFlag_t.bits.humidity_close_timer_arrive_trg_flag == 0  ){
									CloseMotorTgrFlag_t.bits.humidity_close_timer_arrive_trg_flag = 1;
									Control_Fna_Motor(0);               //风机停止
									Motor_Move( MOTOR_FORWORD ,100);  //盖板关闭
									RemoteVariateTrgFlag_t.bits.humidity_close_motro_trg_flag = 0  ;
									log_d("humidity trigger ,motor close ");
								}
							}
						}
					}
				}else{
					RemoteVariateTrgFlag_t.bits.humidity_close_motro_trg_flag = 0  ;
					program_execution_steps = system_read_config_step ;
				}
				break;
			case system_check_temperature_transducer_step :		//内外温度判断条件
				if((deal_transducer_masg_t.dev_online_state[external_temperature_transducer])&&( deal_transducer_masg_t.dev_online_state[interior_temperature_transducer] )){
					if(deal_transducer_masg_t.internal_temperature_date > SystemSetParam_t.SetCloseInternalTemperature){
						if( deal_transducer_masg_t.external_temperature_date > SystemSetParam_t.SetCloseExternalTemperature ){
							if( deal_transducer_masg_t.internal_temperature_date > deal_transducer_masg_t.external_temperature_date){
								temperature_difference_c = deal_transducer_masg_t.internal_temperature_date - deal_transducer_masg_t.external_temperature_date ;
								if( temperature_difference_c <=SystemSetParam_t.SetCloseInternalTemperatureDifferenceC1  ){
									goto _close_motor_temperature;
								}else if( temperature_difference_c >= SystemSetParam_t.SetOpenInternalTemperatureDifferenceC2  ){
									program_execution_steps = system_read_config_step  ;
									if( moistureproof_state_type.moistureproof_state_open_limit ){ 	//盖板未完全打开
										if( CloseMotorTgrFlag_t.bits.temperature_open_trg_flag == 0  ){
											CloseMotorTgrFlag_t.bits.temperature_open_trg_flag = 1 ;
											Motor_Move( MOTOR_RESERSE ,100);  //盖板开启
											log_d("temperature trigger ,motor open ");
										}
									}else{
										if( CloseMotorTgrFlag_t.bits.temperature_open_trg_flag == 1  ){
											CloseMotorTgrFlag_t.bits.temperature_open_trg_flag = 0;
											Control_Fna_Motor(100);           //风机打开
											log_d("temperature trigger ,fan open ");
										}
									}
								}else{
									goto _close_motor_temperature;
								}
							}else{
								goto _close_motor_temperature;
							}
						}else{
							goto _close_motor_temperature;
						}

					}else{
						_close_motor_temperature:
						program_execution_steps = system_read_config_step  ;
						if( moistureproof_state_type.moistureproof_state_close_limit ){  //盖板开启状态
							if( RemoteVariateTrgFlag_t.bits.temperature_close_motro_trg_flag == 0  ){
								RemoteVariateTrgFlag_t.bits.temperature_close_motro_trg_flag = 1 ;
								CloseMotorTgrFlag_t.bits.temperature_close_timer_arrive_trg_flag = 0 ;
								clear_time_cnt(CLOSE_MOTOR_DELAY_T1_TIMER_NUMBER);
							}
							if(check_time_arrive(CLOSE_MOTOR_DELAY_T1_TIMER_NUMBER,SystemSetParam_t.SetCloseTemperatureDelayDateT1*1000)){
								if(CloseMotorTgrFlag_t.bits.temperature_close_timer_arrive_trg_flag == 0 ){
									CloseMotorTgrFlag_t.bits.temperature_close_timer_arrive_trg_flag =1;
									Control_Fna_Motor(0);               //风机停止
									Motor_Move( MOTOR_FORWORD ,100);  //盖板关闭
									log_d("temperature trigger ,motor close ");
									RemoteVariateTrgFlag_t.bits.temperature_close_motro_trg_flag = 0 ;
								}
							}
						}else{
							RemoteVariateTrgFlag_t.bits.temperature_close_motro_trg_flag = 0 ;
						}
					}
				}else{
					RemoteVariateTrgFlag_t.bits.temperature_close_motro_trg_flag = 0 ;
					program_execution_steps = system_read_config_step  ;
				}
				break;
			case system_running_fixd_mode_step :		//触发过检修模式，恢复检修之前状态
					if( moistureproof_state_type.moistureproof_state_close_limit ){  //盖板开启状态
						if( RemoteVariateTrgFlag_t.bits.cancel_fix_mode_trg_flag == 0  ){
							Control_Fna_Motor(0);               //风机停止
							Motor_Move( MOTOR_FORWORD ,100);  //盖板关闭
							RemoteVariateTrgFlag_t.bits.cancel_fix_mode_trg_flag =1 ;
							log_d("fix recover work ,motor close ");
						}
					}else{
						fix_mode_trg_flag = 0 ;
						RemoteVariateTrgFlag_t.bits.recover_auto_control_status_flag =1 ;  //标志位重置，重新开始检测
					}
					program_execution_steps = system_read_config_step ;
				break;
			case system_running_remote_test_step :   //远程测试模式
				program_execution_steps = system_read_config_step ;
				if( old_motor_action_type != GetInformMqttMasgEven_t.remote_test_motor_action_type){
					old_motor_action_type = GetInformMqttMasgEven_t.remote_test_motor_action_type  ;
					RemoteVariateTrgFlag_t.bits.clear_remote_test_timer_flag = 0;
					RemoteVariateTrgFlag_t.bits.recover_auto_control_status_flag = 1 ; //标志位重置，重新开始检测
				}
				if( GetInformMqttMasgEven_t.test_motor_delay_T4_date >0 ) {
					if( RemoteVariateTrgFlag_t.bits.clear_remote_test_timer_flag == 0  ){
						clear_time_cnt(REMOTE_TEST_MOTOR_T4_TIMER_NUMBER);
						RemoteVariateTrgFlag_t.bits.clear_remote_test_timer_flag = 1;
						RemoteVariateTrgFlag_t.bits.remote_timer_arrive_trg_flag = 0  ;
						log_d("clearn remote timer !!");
					}
					if(GetInformMqttMasgEven_t.remote_test_motor_action_type == 1){  //盖板打开指令
						if( moistureproof_state_type.moistureproof_state_open_limit ){ 		 	//盖板未完全打开
							if( RemoteVariateTrgFlag_t.bits.motor_motion_trg_flag == 0  ){
								Motor_Move( MOTOR_RESERSE ,100); 						 //盖板开启
								RemoteVariateTrgFlag_t.bits.motor_motion_trg_flag = 1 ;
								log_d("remote control ,motor open ");
							}
						}else{
							if( RemoteVariateTrgFlag_t.bits.motor_motion_trg_flag == 1 ){
								Control_Fna_Motor(100);     							 //风机打开
								RemoteVariateTrgFlag_t.bits.motor_motion_trg_flag = 0  ;
								log_d("remote control ,fan open ");
							}
						}
					}else if(GetInformMqttMasgEven_t.remote_test_motor_action_type == 0){ //盖板关闭指令
						if( moistureproof_state_type.moistureproof_state_close_limit ){         //盖板开启状态
							if( RemoteVariateTrgFlag_t.bits.motor_motion_trg_flag == 0  ){
								Control_Fna_Motor(0);                                 //风机停止
								Motor_Move( MOTOR_FORWORD ,100);					 //盖板关闭
								RemoteVariateTrgFlag_t.bits.motor_motion_trg_flag =1 ;
								log_d("remote control ,fan motor  close ");
							}
						}else{
							if(RemoteVariateTrgFlag_t.bits.motor_motion_trg_flag == 1 ){
								Motor_Move( MOTOR_STOP ,0);					 //盖板关闭
								RemoteVariateTrgFlag_t.bits.motor_motion_trg_flag = 0 ;
								log_d("remote control ,fan motor  close ");
							}
						}
					}else;
					if(check_time_arrive(REMOTE_TEST_MOTOR_T4_TIMER_NUMBER,GetInformMqttMasgEven_t.test_motor_delay_T4_date*1000)){
						if( RemoteVariateTrgFlag_t.bits.remote_timer_arrive_trg_flag == 0 ){
							GetInformMqttMasgEven_t.remote_test_flag = 0 ;  //恢复为自动模式
							GetInformMqttMasgEven_t.test_motor_delay_T4_date = 0 ;  //清除远程测试时间
							RemoteVariateTrgFlag_t.bits.clear_remote_test_timer_flag = 0;
							RemoteVariateTrgFlag_t.bits.remote_timer_arrive_trg_flag = 1 ;
							log_d("remote control test timer finsh . ");
						}
					}
				}else{
					GetInformMqttMasgEven_t.remote_test_flag = 0 ;  //恢复为自动模式
					RemoteVariateTrgFlag_t.bits.clear_remote_test_timer_flag = 0;
					log_d("intput remote control timer is 0!!");
				}
				break;
			default:
				break;
		}
	}
	return 0 ;
}







