/*
 * dev_dw_display.c
 *
 *  Created on: 2023年1月4日
 *      Author: 好
 */
#define LOG_TAG    "dw_display"

#include "../drive/dw_display.h"

static int dw_continuous_adderss_var_display(int heard_adder,int tail_adder,uint16_t var_buffer);
//static int dw_by_oneself_adderss_var_display(int var_adderss,int var_data);
static int dw_continuous_data_display(int heard_adder,int tail_adder,int *ip_buffer );
//static void dw_package_read_var_data(msg_read_data_t read_data_t, uint8_t *packet);
static void package_write_var_data(msg_write_var_t msg_ctl, uint8_t *packet);


uint16_t gen_crc16(const uint8_t *data, uint16_t size) {
//crc16: x16+x15+x2+1
#define CRC16_POLY 0xA001
    uint16_t out = 0;
    uint16_t tmp = 0;

    /* Sanity check: */
    if(data == NULL)
        return 0;

    out = 0xFFFF;
    for (int i = 0; i < size; i++){
    	out ^= data[i];
    	for (int j = 0; j < 8; j++){
    		tmp = out & 0x0001;
    		out >>= 1;
    		if(tmp==1)
    			out ^= CRC16_POLY;
    	}
    }

    return out;
}




static void package_write_var_data(msg_write_var_t msg_ctl, uint8_t *packet){
//	uint16_t crc16=0;
	packet[0]=(uint8_t)( (( DW_FH & 0xFF00 )>> 8) );
	packet[1]=(uint8_t)( DW_FH & 0X00FF );
	packet[2]=0x05;
	packet[3]=0x82;
	packet[4]=(uint8_t)( (( msg_ctl.var_adderss & 0xFF00 )>> 8) );
	packet[5]=(uint8_t)( msg_ctl.var_adderss & 0X00FF );
	packet[6]=(uint8_t)( (( msg_ctl.var_data & 0xFF00 )>> 8) );
	packet[7]=(uint8_t)( msg_ctl.var_data & 0X00FF );

//	crc16 = gen_crc16(packet+2, sizeof(msg_active_t)-4);
//	packet[6]=crc16 & 0x00ff;
//	packet[7]=(crc16>>8) & 0x00ff; msg_write_page

}
static void package_write_page_data(msg_write_page_t msg_write_page, uint8_t *packet){
//	uint16_t crc16=0;
	packet[0]=(uint8_t)( (( DW_FH & 0xFF00 )>> 8) );
	packet[1]=(uint8_t)( DW_FH & 0X00FF );
	packet[2]=0x07;
	packet[3]=0x82;
	packet[4]=0x00;
	packet[5]=0x84;
	packet[6]=(uint8_t)( (( msg_write_page.sys_switch_page_adderss & 0xFF00 )>> 8) );
	packet[7]=(uint8_t)( msg_write_page.sys_switch_page_adderss & 0X00FF );
	packet[8]=(uint8_t)( (( msg_write_page.switch_page_number & 0xFF00 )>> 8) );
	packet[9]=(uint8_t)( msg_write_page.switch_page_number & 0X00FF );

//	crc16 = gen_crc16(packet+2, sizeof(msg_active_t)-4);
//	packet[6]=crc16 & 0x00ff;
//	packet[7]=(crc16>>8) & 0x00ff; msg_write_page

}



//static void dw_package_read_var_data(msg_read_data_t read_data_t, uint8_t *packet){
////	uint16_t crc16=0;
//	read_data_t.head = (uint16_t)( (packet[0]<<8) | packet[1] );
//	read_data_t.length = packet[2] ;
//	read_data_t.cmd = packet[3] ;
//	read_data_t.var_adderss = (uint16_t)( (packet[4]<<8) | packet[5] );
//	read_data_t.read_lent = packet[6] ;
//	read_data_t.read_data = (uint16_t)( (packet[7]<<8) | packet[8] );
//}

static int dw_switch_page_display(int page_number){
	int write_lent = -1 ;
	msg_write_page_t msg_write_page;
	uint8_t write_var_pkt[10];
	msg_write_page.sys_switch_page_adderss = 0x5a01;
	msg_write_page.switch_page_number = page_number;
	package_write_page_data(msg_write_page, write_var_pkt);
	write_lent = dw_device_send(write_var_pkt,sizeof(write_var_pkt));
	return write_lent ;
}

int dw_by_oneself_adderss_var_display(int var_adderss,int var_data){
	int write_lent = -1 ;
	msg_write_var_t write_var_msg;
	uint8_t write_var_pkt[8];
	write_var_msg.var_adderss = var_adderss;
	write_var_msg.var_data = var_data;
	package_write_var_data(write_var_msg, write_var_pkt);
	write_lent = dw_device_send(write_var_pkt,sizeof(write_var_pkt));
	return write_lent ;
}

static int dw_continuous_data_display(int heard_adder,int tail_adder,int *ip_buffer ){
	int write_lent = 0 ;
	int ip_tmp[3] = {0} ;

	msg_write_var_t write_var_msg;
	uint8_t write_var_pkt[8];
	write_var_msg.var_adderss = heard_adder;

	for(int i = 0 ; i<4;i++){
		ip_tmp[0] = ip_buffer[i]/100;
		ip_tmp[1] = ip_buffer[i]%100/10;
		ip_tmp[2] = ip_buffer[i]%100%10;

		for(int x=0;x<3;x++){
			write_var_msg.var_data = ip_tmp[x];
			package_write_var_data(write_var_msg, write_var_pkt);
			write_lent = dw_device_send(write_var_pkt,sizeof(write_var_pkt));
			if(write_lent <= 0 ){
				log_e("setting_dw_ip_adderss error !! ");
			}
			write_var_msg.var_adderss ++;
			if(write_var_msg.var_adderss > (tail_adder+1) ){
				log_e("ip var adderss overstep !! ");
				return 0 ;
			}
		}
	}
	return write_lent ;
}





static int dw_continuous_adderss_var_display(int heard_adder,int tail_adder,uint16_t var_buffer){
	int write_lent = 0 ;

	int *date_buff =NULL ;
	int date_buff_lent = 0 ;
	int n = 0 ,m=0;

	msg_write_var_t write_var_msg;
	uint8_t write_var_pkt[8];
	if(tail_adder < heard_adder ){
		log_e("dw_continuous_adderss_var_display error \r");
		return -1;
	}
	date_buff_lent = tail_adder - heard_adder +1 ;
	date_buff = (int *)malloc( ( date_buff_lent *4 )+ 1 );
	if(date_buff == NULL){
		log_e("malloc error \r");
		return -1;
	}
	memset(date_buff, 0, ( date_buff_lent *4 )+ 1 );
	while(var_buffer!=0){
		m = var_buffer%10;
		date_buff[n] = m ;
		n++ ;
		var_buffer = var_buffer/10;
	}
	write_var_msg.var_adderss = heard_adder;
	for(int i = date_buff_lent ; i> 0 ; i-- ){
		write_var_msg.var_data = date_buff[i-1];
		package_write_var_data(write_var_msg, write_var_pkt);
		write_lent = dw_device_send(write_var_pkt,sizeof(write_var_pkt));
		if(write_lent <= 0 ){
			log_w("tty write error !! ");
		}
		write_var_msg.var_adderss ++ ;
	}
	free(date_buff);
	return write_lent ;
}






int dw_time_var(struct tm *time ){
	int write_lent = 0 ;
	int time_data[5] = {0} ;
	int time_tmp[4] = {0} ;
	int control_loop_cnts = 0 ;


	msg_write_var_t write_var_msg;
	uint8_t write_var_pkt[8];

	time_data[0] = time->tm_year+1900;
	time_data[1] = time->tm_mon+ 1;
	time_data[2] = time->tm_mday;
	time_data[3] = time->tm_hour ;
	time_data[4] = time->tm_min ;

	write_var_msg.var_adderss = TIME_VAR_HEARD_ADDERSS;
	for(int i = 0 ; i<5;i++){
		time_tmp[0] = time_data[i]/1000;
		time_tmp[1] = time_data[i]%1000/100;
		time_tmp[2] = time_data[i]%1000%100/10;
		time_tmp[3] = time_data[i]%1000%100%10;

		if(time_tmp[0]>0) control_loop_cnts = 4 ;
		else if(time_tmp[1]>0) control_loop_cnts = 3 ;
		else control_loop_cnts = 2 ;

		for(int x=0;x<control_loop_cnts;x++){
			if(time_tmp[0]>0){
				write_var_msg.var_data = time_tmp[x];
			}else if(time_tmp[1]>0){
				write_var_msg.var_data = time_tmp[x+1];
			}else{
				write_var_msg.var_data = time_tmp[x+2];
			}

			package_write_var_data(write_var_msg, write_var_pkt);
			write_lent = dw_device_send(write_var_pkt,sizeof(write_var_pkt));
			if(write_lent <= 0 ){
				log_w("write time error !! ");
				return 0 ;
			}
			write_var_msg.var_adderss ++;
			if(write_var_msg.var_adderss > TIME_VAR_TAIL_ADDERSS+1 ){
				log_w("time var adderss overstep !! ");
				return 0 ;
			}
		}
	}
	write_var_msg.var_adderss = WDAY_VAR_ADDERSS ;
	write_var_msg.var_data = time->tm_wday ;
	package_write_var_data(write_var_msg, write_var_pkt);
	write_lent = dw_device_send(write_var_pkt,sizeof(write_var_pkt));
	if(write_lent <= 0 ){
		log_w("wday error !! ");
		return 0 ;
	}
	return write_lent ;
}



 int dw_ip_var_adderss(int *ip_buffer ){
	int write_lent = 0 ;
	write_lent = dw_continuous_data_display(IP_VAR_HEARD_ADDERSS,IP_VAR_TAIL_ADDERSS,ip_buffer);
	return write_lent ;
}

 int dw_netmask_var(int *netmask_buffer ){
	int write_lent = 0 ;
	write_lent = dw_continuous_data_display(NETMASK_VAR_HEARD_ADDERSS,NETMASK_VAR_TAIL_ADDERSS,netmask_buffer);
	return write_lent ;
}

 int dw_route_gw_var(int *gw_buffer ){
	int write_lent = 0 ;
	write_lent = dw_continuous_data_display(GW_VAR_HEARD_ADDERSS,GW_VAR_TAIL_ADDERSS,gw_buffer);
	return write_lent ;
}


 int dw_broadcast_var(int *broadcast_buffer ){
	int write_lent = 0 ;
	write_lent = dw_continuous_data_display(BROADCAST_VAR_HEARD_ADDERSS,BROADCAST_VAR_TAIL_ADDERSS,broadcast_buffer);
	return write_lent ;
}


 int dw_eth_connect_state(uint8_t eth_state){
 	int write_lent = -1 ;
 	write_lent=dw_by_oneself_adderss_var_display(ETH_CONNECT_STATE_ADDERSS,eth_state);
 	return write_lent ;
 }


 int dw_cumulative_time(uint16_t cumulative_time){
	 int write_lent = -1 ;
	 write_lent=dw_continuous_adderss_var_display(CUMULATIVE_TIME_HEAD_ADDERSS,CUMULATIVE_TIME_TAIL_ADDERSS,cumulative_time);

 	return write_lent ;
 }

 int dw_external_temperature(uint16_t external_temperature ){
	 int write_lent = -1 ;
 	write_lent=dw_continuous_adderss_var_display(EXTERNAL_TEMP_HEARD_ADDERSS,EXTERNAL_TEMP_TAIL_ADDERSS,(uint16_t)(external_temperature));
 	return write_lent ;
 }

 int dw_external_humidity(uint16_t external_humidity ){
	 int write_lent = -1 ;
	 write_lent=dw_continuous_adderss_var_display(EXTERNAL_HUMIDITY_HEARD_ADDERSS,EXTERNAL_HUMIDITY_TAIL_ADDERSS,(uint16_t)(external_humidity));
 	return write_lent ;
 }


 int dw_interior_temperature(uint16_t interior_temperature){
	 int write_lent = -1 ;
	 write_lent=dw_continuous_adderss_var_display(INTERIOR_TEMP_HEARD_ADDERSS,INTERIOR_TEMP_TAIL_ADDERSS,(uint16_t)(interior_temperature));
 	return write_lent ;
 }

 int dw_interior_humidity(uint16_t interior_humidity ){
	 int write_lent = -1 ;
	 write_lent=dw_continuous_adderss_var_display(INTERIOR_HUMIDITY_HEARD_ADDERSS,INTERIOR_HUMIDITY_TAIL_ADDERSS,(uint16_t)(interior_humidity));
 	return write_lent ;
 }

 int dw_illumination_transducer(int illumination_grade){
 	int write_lent = -1 ;
 	write_lent=dw_by_oneself_adderss_var_display(ILLUMINATION_GRADE_VAR_ADDERSS,illumination_grade);
 	return write_lent ;
 }

 int dw_sleet_transducer(int sleet_state){
 	int write_lent = -1 ;
 	write_lent=dw_by_oneself_adderss_var_display(SLEET_GRADE_VAR_ADDERSS,sleet_state);
 	return write_lent ;
 }

int dw_switching_pages(int page_number){
	int write_lent = -1 ;

	write_lent=dw_switch_page_display(page_number); //更新选择的光标
	return write_lent ;

}

int dw_setting_slect_var( int var_addr ,uint8_t var_state){
 	int write_lent = -1 ;

	write_lent=dw_by_oneself_adderss_var_display(var_addr,var_state);

 	return write_lent;
}


int dw_moistureproof_state(uint8_t moistureproof_state){
	int write_lent = -1 ;
	write_lent=dw_by_oneself_adderss_var_display(MOISTUREPROOF_ANIMATION_VAR_ADDERSS,moistureproof_state);
	return write_lent ;
}

int dw_moistureproof_state_var(uint8_t moistureproof_state_var){
	int write_lent = -1 ;
	write_lent=dw_by_oneself_adderss_var_display(MOISTUREPROOF_STATE_VAR_ADDERSS,moistureproof_state_var);
	return write_lent ;
}

int dw_fan_motor_rotate_data_var(uint16_t rotate_data){   //风机转速数字图标
	int write_lent = -1 ;
	static int old_date_tmp[4]={99,99,99,99};
	int date_tmp[4]={0};

	date_tmp[0] = rotate_data/1000;
	date_tmp[1] = rotate_data%1000/100;
	date_tmp[2] = rotate_data%1000%100/10;
	date_tmp[3] = rotate_data%1000%100%10;

	for(uint8_t i=0;i<4;i++){
		if( old_date_tmp[i]!= date_tmp[i] ){
			 old_date_tmp[i] = date_tmp[i];
			 write_lent=dw_by_oneself_adderss_var_display(FAN_MOTOR_ROTATE_HEARD_DATA_VAR_ADDERSS+i,date_tmp[i]);
		}
	}
	return write_lent ;
}

int dw_fan_motor_animation_state_var(uint8_t moistureproof_state_var){ //风机动画图标
	int write_lent = -1 ;
	write_lent=dw_by_oneself_adderss_var_display(FAN_MOTOR_ANIMATION_VAR_ADDERSS,moistureproof_state_var);
	return write_lent ;
}

int dw_smoke_state_var(uint8_t state){	//烟雾图标显示
	int write_lent = -1 ;
	write_lent=dw_by_oneself_adderss_var_display(SMOKE_ALARM_VAR_ADDERSS,state);
	return write_lent ;
}

int dw_water_state_var(uint8_t state){ //水浸图标显示
	int write_lent = -1 ;
	write_lent=dw_by_oneself_adderss_var_display(WATER_ALARM_VAR_ADDERSS,state);
	return write_lent ;
}

int dw_check_mode_state_var(uint8_t state){ //工作模式图标显示
	int write_lent = -1 ;
	write_lent=dw_by_oneself_adderss_var_display(CHECK_MODE_VAR_ADDERSS,state);
	return write_lent ;
}


int dw_external_humiture_online_state_var(uint8_t state){ //显示外界温湿度在线图标显示
	int write_lent = -1 ;
	write_lent=dw_by_oneself_adderss_var_display(EXTERNAL_HUMITURE_ONLINE_VAR_ADDERSS,state);
	return write_lent ;
}

int dw_internal_humiture_online_state_var(uint8_t state){ //显示内部温湿度在线图标显示
	int write_lent = -1 ;
	write_lent=dw_by_oneself_adderss_var_display(INTERNAL_HUMITURE_ONLINE_VAR_ADDERSS,state);
	return write_lent ;
}

//int dw_illumination_online_state_var(uint8_t state){ //显示光照强度在线图标显示
//	int write_lent = -1 ;
//	write_lent=dw_by_oneself_adderss_var_display(INTERNAL_HUMITURE_ONLINE_VAR_ADDERSS,state);
//	return write_lent ;
//}



int dw_input_parameter_hint_window( uint8_t set_var,int InputParHintWaitWindownAddr ,int InputParHintSuccessWindownAddr ,int InputParHintErrorWindownAddr){
	static uint8_t close_dev_addr_window_var_flag = 0 ;
	int write_lent = -1 ;
	switch (set_var) {
		case 0:
			if(close_dev_addr_window_var_flag ==1){
				write_lent=dw_by_oneself_adderss_var_display( InputParHintSuccessWindownAddr , 0 ) ;
			}else if(close_dev_addr_window_var_flag ==2){
				write_lent=dw_by_oneself_adderss_var_display( InputParHintErrorWindownAddr , 0 ) ;
			}else;
			break;
		case 1:
			write_lent=dw_by_oneself_adderss_var_display( InputParHintWaitWindownAddr , 1 ) ;
			break;
		case 2:
			close_dev_addr_window_var_flag = 1 ;
			write_lent=dw_by_oneself_adderss_var_display( InputParHintWaitWindownAddr , 0 ) ;
			write_lent=dw_by_oneself_adderss_var_display( InputParHintSuccessWindownAddr , 1 ) ;
			break;
		case 3:
			close_dev_addr_window_var_flag =2 ;
			write_lent=dw_by_oneself_adderss_var_display( InputParHintWaitWindownAddr , 0 ) ;
			write_lent=dw_by_oneself_adderss_var_display( InputParHintErrorWindownAddr , 1 ) ;
			break;
		default:
			write_lent=dw_by_oneself_adderss_var_display( InputParHintWaitWindownAddr , 0 ) ;
			write_lent=dw_by_oneself_adderss_var_display( InputParHintSuccessWindownAddr , 0 ) ;
			write_lent=dw_by_oneself_adderss_var_display( InputParHintErrorWindownAddr , 0 ) ;
			break;
	}
	return write_lent ;
}

/**************************************************外界温度相关参数度显示************************************************************************/
int show_ex_temp_compensation_date(int val){
	int tmp[2];
	int write_lent = -1 ;
	if( val >= 0){
		write_lent=dw_by_oneself_adderss_var_display( EXTERNAL_TEMP_COMPENSATION_INPUT_MINUS_VAR_ADDERSS , 0 ) ;
		tmp[0] = val /10 ;
		tmp[1] = val %10 ;
	}else{
		write_lent=dw_by_oneself_adderss_var_display( EXTERNAL_TEMP_COMPENSATION_INPUT_MINUS_VAR_ADDERSS , 1 ) ;
		tmp[0] = MINUS_CONVERT_POSITIVE(val) /10 ;
		tmp[1] = MINUS_CONVERT_POSITIVE(val) %10 ;
	}
	write_lent = dw_by_oneself_adderss_var_display( EXTERNAL_TEMP_COMPENSATION_DIGITS_NUMBER_VAR_ADDERSS , tmp[1] ) ;
	write_lent = dw_by_oneself_adderss_var_display( EXTERNAL_TEMP_COMPENSATION_DECADE_NUMBER_VAR_ADDERSS , tmp[0] ) ;
	return write_lent ;
}

int show_ex_temp_alarm_threshold_date(int val){
	int tmp[2];
	int write_lent = -1 ;

	tmp[0] = val /10 ;
	tmp[1] = val %10 ;
	write_lent = dw_by_oneself_adderss_var_display( EXTERNAL_TEMP_ALARM_THERSHOLD_DIGITS_NUMBER_VAR_ADDERSS , tmp[1] ) ;
	write_lent = dw_by_oneself_adderss_var_display( EXTERNAL_TEMP_ALARM_THERSHOLD_DECADE_NUMBER_VAR_ADDERSS , tmp[0] ) ;

	return write_lent ;
}

int show_ex_temp_humiture_sample_rate_date(int val){
	int tmp[2];
	int write_lent = -1 ;

	tmp[0] = val /10 ;
	tmp[1] = val %10 ;
	write_lent = dw_by_oneself_adderss_var_display( EXTERNAL_TEMP_SAMPLE_RATE_DIGITS_NUMBER_VAR_ADDERSS , tmp[1] );
	write_lent = dw_by_oneself_adderss_var_display( EXTERNAL_TEMP_SAMPLE_RATE_DECADE_NUMBER_VAR_ADDERSS , tmp[0] );

	return write_lent ;
}

/**************************************************外界湿度相关参数度显示************************************************************************/
int show_ex_humill_compensation_date(int val){
	int tmp[2];
	int write_lent = -1 ;
	if( val >= 0){
		write_lent=dw_by_oneself_adderss_var_display( EXTERNAL_HUMIDITY_COMPENSATION_INPUT_MINUS_VAR_ADDERSS , 0 ) ;
		tmp[0] = val /10 ;
		tmp[1] = val %10 ;
	}else{
		write_lent=dw_by_oneself_adderss_var_display( EXTERNAL_HUMIDITY_COMPENSATION_INPUT_MINUS_VAR_ADDERSS , 1 ) ;
		tmp[0] = MINUS_CONVERT_POSITIVE(val) /10 ;
		tmp[1] = MINUS_CONVERT_POSITIVE(val) %10 ;
	}
	write_lent = dw_by_oneself_adderss_var_display( EXTERNAL_HUMIDITY_COMPENSATION_DIGITS_NUMBER_VAR_ADDERSS , tmp[1] ) ;
	write_lent = dw_by_oneself_adderss_var_display( EXTERNAL_HUMIDITY_COMPENSATION_DECADE_NUMBER_VAR_ADDERSS , tmp[0]  ) ;
	return write_lent ;
}

int show_ex_humill_alarm_threshold_date(int val){
	int tmp[2];
	int write_lent = -1 ;

	tmp[0] = val /10 ;
	tmp[1] = val %10 ;
	write_lent = dw_by_oneself_adderss_var_display( EXTERNAL_HUMIDITY_ALARM_THERSHOLD_DIGITS_NUMBER_VAR_ADDERSS , tmp[1] ) ;
	write_lent = dw_by_oneself_adderss_var_display( EXTERNAL_HUMIDITY_ALARM_THERSHOLD_DECADE_NUMBER_VAR_ADDERSS , tmp[0] ) ;

	return write_lent ;
}

/**************************************************光照相关参数度显示************************************************************************/
int show_Illumi_compensation_date(int val){
	int tmp[3];
	int write_lent = -1 ;
	if( val >= 0){
		write_lent=dw_by_oneself_adderss_var_display( EXTERNAL_ILLUMINATION_COMPENSATION_INPUT_MINUS_VAR_ADDERSS , 0 ) ;
		tmp[0] = val /100 ;
		tmp[1] = val %100/10 ;
		tmp[2] = val %100%10 ;
	}else{
		write_lent=dw_by_oneself_adderss_var_display( EXTERNAL_ILLUMINATION_COMPENSATION_INPUT_MINUS_VAR_ADDERSS , 1 ) ;
		tmp[0] = MINUS_CONVERT_POSITIVE(val) /100 ;
		tmp[1] = MINUS_CONVERT_POSITIVE(val) %100/10 ;
		tmp[2] = MINUS_CONVERT_POSITIVE(val) %100%10 ;

	}
	write_lent = dw_by_oneself_adderss_var_display( EXTERNAL_ILLUMINATION_COMPENSATION_HUNDREDS_NUMBER_VAR_ADDERSS , tmp[0] ) ;
	write_lent = dw_by_oneself_adderss_var_display( EXTERNAL_ILLUMINATION_COMPENSATION_DIGITS_NUMBER_VAR_ADDERSS , tmp[1] ) ;
	write_lent = dw_by_oneself_adderss_var_display( EXTERNAL_ILLUMINATION_COMPENSATION_DECADE_NUMBER_VAR_ADDERSS , tmp[2] ) ;
	return write_lent ;
}

int show_Illumi_real_time_date(int val){
	int tmp[6];
	int write_lent = -1 ;

	tmp[0] = val / 100000 ;
	tmp[1] = val % 100000 / 10000;
	tmp[2] = val % 100000 % 10000 / 1000;
	tmp[3] = val % 100000 % 10000 % 1000 / 100 ;
	tmp[4] = val % 100000 % 100000 % 10000 % 1000 % 100 / 10 ;
	tmp[5] = val % 100000 % 100000 % 10000 % 1000 % 100 % 10 ;

	write_lent = dw_by_oneself_adderss_var_display( EXTERNAL_ILLUMINATION_REAL_TIME_ONE_HUNDRED_THOUSAND_NUMBER_VAR_ADDERSS , tmp[0] );
	write_lent = dw_by_oneself_adderss_var_display( EXTERNAL_ILLUMINATION_REAL_TIME_THEN_THOUSAND_NUMBER_VAR_ADDERSS , tmp[1] );
	write_lent = dw_by_oneself_adderss_var_display( EXTERNAL_ILLUMINATION_REAL_TIME_THOUSAND_NUMBER_VAR_ADDERSS , tmp[2] );
	write_lent = dw_by_oneself_adderss_var_display( EXTERNAL_ILLUMINATION_REAL_TIME_HUNDRED_NUMBER_VAR_ADDERSS , tmp[3] );
	write_lent = dw_by_oneself_adderss_var_display( EXTERNAL_ILLUMINATION_REAL_TIME_DIGITS_NUMBER_VAR_ADDERSS , tmp[4] );
	write_lent = dw_by_oneself_adderss_var_display( EXTERNAL_ILLUMINATION_REAL_TIME_DECADE_NUMBER_VAR_ADDERSS , tmp[5] );

	return write_lent ;
}


int show_Illumi_intput_min_date(int val){
	int tmp[6];
	int write_lent = -1 ;

	tmp[0] = val / 100000 ;
	tmp[1] = val % 100000 / 10000 ;
	tmp[2] = val % 100000 % 10000 / 1000 ;
	tmp[3] = val % 100000 % 10000 % 1000 / 100 ;
	tmp[4] = val % 100000 % 100000 % 10000 % 1000 % 100 / 10 ;
	tmp[5] = val % 100000 % 100000 % 10000 % 1000 % 100 % 10 ;

	write_lent = dw_by_oneself_adderss_var_display( EXTERNAL_ILLUMINATION_INTPUT_REF_MIN_ONE_HUNDRED_THOUSAND_NUMBER_VAR_ADDERSS , tmp[0] );
	write_lent = dw_by_oneself_adderss_var_display( EXTERNAL_ILLUMINATION_INTPUT_REF_MIN_THEN_THOUSAND_NUMBER_VAR_ADDERSS , tmp[1] );
	write_lent = dw_by_oneself_adderss_var_display( EXTERNAL_ILLUMINATION_INTPUT_REF_MIN_THOUSAND_NUMBER_VAR_ADDERSS , tmp[2] );
	write_lent = dw_by_oneself_adderss_var_display( EXTERNAL_ILLUMINATION_INTPUT_REF_MIN_HUNDRED_NUMBER_VAR_ADDERSS , tmp[3] );
	write_lent = dw_by_oneself_adderss_var_display( EXTERNAL_ILLUMINATION_INTPUT_REF_MIN_DIGITS_NUMBER_VAR_ADDERSS , tmp[4] );
	write_lent = dw_by_oneself_adderss_var_display( EXTERNAL_ILLUMINATION_INTPUT_REF_MIN_DECADE_NUMBER_VAR_ADDERSS , tmp[5] );
	return write_lent ;
}


int show_Illumi_intput_max_date(int val){
	int tmp[6];
	int write_lent = -1 ;

	tmp[0] = val / 100000 ;
	tmp[1] = val % 100000 / 10000 ;
	tmp[2] = val % 100000 % 10000 / 1000 ;
	tmp[3] = val % 100000 % 10000 % 1000 / 100 ;
	tmp[4] = val % 100000 % 100000 % 10000 % 1000 % 100 / 10 ;
	tmp[5] = val % 100000 % 100000 % 10000 % 1000 % 100 % 10 ;

	write_lent = dw_by_oneself_adderss_var_display( EXTERNAL_ILLUMINATION_INTPUT_REF_MAX_ONE_HUNDRED_THOUSAND_NUMBER_VAR_ADDERSS , tmp[0] );
	write_lent = dw_by_oneself_adderss_var_display( EXTERNAL_ILLUMINATION_INTPUT_REF_MAX_THEN_THOUSAND_NUMBER_VAR_ADDERSS , tmp[1] );
	write_lent = dw_by_oneself_adderss_var_display( EXTERNAL_ILLUMINATION_INTPUT_REF_MAX_THOUSAND_NUMBER_VAR_ADDERSS , tmp[2] );
	write_lent = dw_by_oneself_adderss_var_display( EXTERNAL_ILLUMINATION_INTPUT_REF_MAX_HUNDRED_NUMBER_VAR_ADDERSS , tmp[3] );
	write_lent = dw_by_oneself_adderss_var_display( EXTERNAL_ILLUMINATION_INTPUT_REF_MAX_DIGITS_NUMBER_VAR_ADDERSS , tmp[4] );
	write_lent = dw_by_oneself_adderss_var_display( EXTERNAL_ILLUMINATION_INTPUT_REF_MAX_DECADE_NUMBER_VAR_ADDERSS , tmp[5] );
	return write_lent ;
}

int show_Illumi_sample_rate_date(int val){
	int tmp[2];
	int write_lent = -1 ;

	tmp[0] = val /10 ;
	tmp[1] = val %10 ;
	write_lent = dw_by_oneself_adderss_var_display( EXTERNAL_ILLUMINATION_SAMPLE_RATE_DIGITS_NUMBER_VAR_ADDERSS , tmp[1] );
	write_lent = dw_by_oneself_adderss_var_display( EXTERNAL_ILLUMINATION_SAMPLE_RATE_DECADE_NUMBER_VAR_ADDERSS , tmp[0] );

	return write_lent ;
}

/**************************************************雨雪相关参数度显示************************************************************************/
int show_sleet_real_time_sensitivity_date(int val){
	int tmp[4];
	int write_lent = -1 ;

	tmp[0] = val / 1000 ;
	tmp[1] = val % 1000 / 100;
	tmp[2] = val % 1000 % 100 / 10;
	tmp[3] = val % 1000 % 100 % 10;

	write_lent = dw_by_oneself_adderss_var_display( EXTERNAL_SLEET_SENSITIVITY_THOUSAND_NUMBER_VAR_ADDERSS , tmp[0] );
	write_lent = dw_by_oneself_adderss_var_display( EXTERNAL_SLEET_SENSITIVITY_HUNDREDS_NUMBER_VAR_ADDERSS , tmp[1] );
	write_lent = dw_by_oneself_adderss_var_display( EXTERNAL_SLEET_SENSITIVITY_DIGITS_NUMBER_VAR_ADDERSS , tmp[2] );
	write_lent = dw_by_oneself_adderss_var_display( EXTERNAL_SLEET_SENSITIVITY_DECADE_NUMBER_VAR_ADDERSS , tmp[3] );
	return write_lent ;
}


int show_sleet_intput_sensitivity_date(int val){
	int tmp[4];
	int write_lent = -1 ;

	tmp[0] = val / 1000 ;
	tmp[1] = val % 1000 / 100;
	tmp[2] = val % 1000 % 100 / 10;
	tmp[3] = val % 1000 % 100 % 10;

	write_lent = dw_by_oneself_adderss_var_display( EXTERNAL_SLEET_SENSITIVITY_INPUT_THOUSAND_NUMBER_VAR_ADDERSS , tmp[0] );
	write_lent = dw_by_oneself_adderss_var_display( EXTERNAL_SLEET_SENSITIVITY_INPUT_HUNDREDS_NUMBER_VAR_ADDERSS , tmp[1] );
	write_lent = dw_by_oneself_adderss_var_display( EXTERNAL_SLEET_SENSITIVITY_INPUT_DIGITS_NUMBER_VAR_ADDERSS , tmp[2] );
	write_lent = dw_by_oneself_adderss_var_display( EXTERNAL_SLEET_SENSITIVITY_INPUT_DECADE_NUMBER_VAR_ADDERSS , tmp[3] );
	return write_lent ;
}

int show_sleet_real_time_heat_lower_limit_date(int val){
	int tmp[2];
	int write_lent = -1 ;

	tmp[0] = val / 10 ;
	tmp[1] = val % 10;

	write_lent = dw_by_oneself_adderss_var_display( EXTERNAL_SLEET_SHOW_HEATTING_LOW_LIMIT_DECADE_NUMBER_VAR_ADDERSS , tmp[0] );
	write_lent = dw_by_oneself_adderss_var_display( EXTERNAL_SLEET_SHOW_HEATTING_LOW_LIMIT_DIGITS_NUMBER_VAR_ADDERSS , tmp[1] );

	return write_lent ;
}


int show_sleet_intput_heat_lower_limit_date(int val){
	int tmp[2];
	int write_lent = -1 ;

	tmp[0] = val / 10 ;
	tmp[1] = val % 10;

	write_lent = dw_by_oneself_adderss_var_display( EXTERNAL_SLEET_INTPUT_HEATTING_LOW_LIMIT_DECADE_NUMBER_VAR_ADDERSS , tmp[0] );
	write_lent = dw_by_oneself_adderss_var_display( EXTERNAL_SLEET_INTPUT_HEATTING_LOW_LIMIT_DIGITS_NUMBER_VAR_ADDERSS , tmp[1] );

	return write_lent ;
}


int show_sleet_real_time_heat_hight_limit_date(int val){
	int tmp[2];
	int write_lent = -1 ;

	tmp[0] = val / 10 ;
	tmp[1] = val % 10;

	write_lent = dw_by_oneself_adderss_var_display( EXTERNAL_SLEET_SHOW_HEATTING_HIGH_LIMIT_DECADE_NUMBER_VAR_ADDERSS , tmp[0] );
	write_lent = dw_by_oneself_adderss_var_display( EXTERNAL_SLEET_SHOW_HEATTING_HIGH_LIMIT_DIGITS_NUMBER_VAR_ADDERSS , tmp[1] );

	return write_lent ;
}


int show_sleet_intput_heat_hight_limit_date(int val){
	int tmp[2];
	int write_lent = -1 ;

	tmp[0] = val / 10 ;
	tmp[1] = val % 10;

	write_lent = dw_by_oneself_adderss_var_display( EXTERNAL_SLEET_INTPUT_HEATTING_HIGH_LIMIT_DECADE_NUMBER_VAR_ADDERSS , tmp[0] );
	write_lent = dw_by_oneself_adderss_var_display( EXTERNAL_SLEET_INTPUT_HEATTING_HIGH_LIMIT_DIGITS_NUMBER_VAR_ADDERSS , tmp[1] );

	return write_lent ;
}

int show_sleet_real_time_delay_alarm_reset_date(int val){
	int tmp[4];
	int write_lent = -1 ;

	tmp[0] = val / 1000 ;
	tmp[1] = val % 1000 / 100;
	tmp[2] = val % 1000 % 100 / 10;
	tmp[3] = val % 1000 % 100 % 10;

	write_lent = dw_by_oneself_adderss_var_display( EXTERNAL_SLEET_DELAY_ALARM_RESET_SHOW_THOUSAND_NUMBER_VAR_ADDERSS , tmp[0] );
	write_lent = dw_by_oneself_adderss_var_display( EXTERNAL_SLEET_DELAY_ALARM_RESET_SHOW_HUNDREDS_NUMBER_VAR_ADDERSS , tmp[1] );
	write_lent = dw_by_oneself_adderss_var_display( EXTERNAL_SLEET_DELAY_ALARM_RESET_SHOW_DIGITS_NUMBER_VAR_ADDERSS , tmp[2] );
	write_lent = dw_by_oneself_adderss_var_display( EXTERNAL_SLEET_DELAY_ALARM_RESET_SHOW_DECADE_NUMBER_VAR_ADDERSS , tmp[3] );
	return write_lent ;
}


int show_sleet_intput_delay_alarm_reset_date(int val){
	int tmp[4];
	int write_lent = -1 ;

	tmp[0] = val / 1000 ;
	tmp[1] = val % 1000 / 100;
	tmp[2] = val % 1000 % 100 / 10;
	tmp[3] = val % 1000 % 100 % 10;

	write_lent = dw_by_oneself_adderss_var_display( EXTERNAL_SLEET_DELAY_ALARM_RESET_INTPUT_THOUSAND_NUMBER_VAR_ADDERSS , tmp[0] );
	write_lent = dw_by_oneself_adderss_var_display( EXTERNAL_SLEET_DELAY_ALARM_RESET_INTPUT_HUNDREDS_NUMBER_VAR_ADDERSS , tmp[1] );
	write_lent = dw_by_oneself_adderss_var_display( EXTERNAL_SLEET_DELAY_ALARM_RESET_INTPUT_DIGITS_NUMBER_VAR_ADDERSS , tmp[2] );
	write_lent = dw_by_oneself_adderss_var_display( EXTERNAL_SLEET_DELAY_ALARM_RESET_INTPUT_DECADE_NUMBER_VAR_ADDERSS , tmp[3] );
	return write_lent ;
}


int show_sleet_sample_rate_date(int val){
	int tmp[2];
	int write_lent = -1 ;

	tmp[0] = val /10 ;
	tmp[1] = val %10 ;
	write_lent = dw_by_oneself_adderss_var_display( EXTERNAL_SLEET_SAMPLE_RATE_DECADE_NUMBER_VAR_ADDERSS , tmp[0] );
	write_lent = dw_by_oneself_adderss_var_display( EXTERNAL_SLEET_SAMPLE_RATE_DIGITS_NUMBER_VAR_ADDERSS , tmp[1] );

	return write_lent ;
}

/**************************************************内部温度相关参数度显示************************************************************************/
int show_in_temp_compensation_date(int val){
	int tmp[2];
	int write_lent = -1 ;
	if( val >= 0){
		write_lent=dw_by_oneself_adderss_var_display( INTERNAL_TEMP_COMPENSATION_INPUT_MINUS_VAR_ADDERSS , 0 ) ;
		tmp[0] = val /10 ;
		tmp[1] = val %10 ;
	}else{
		write_lent=dw_by_oneself_adderss_var_display( INTERNAL_TEMP_COMPENSATION_INPUT_MINUS_VAR_ADDERSS , 1 ) ;
		tmp[0] = MINUS_CONVERT_POSITIVE(val) /10 ;
		tmp[1] = MINUS_CONVERT_POSITIVE(val) %10 ;
	}
	write_lent = dw_by_oneself_adderss_var_display( INTERNAL_TEMP_COMPENSATION_DIGITS_NUMBER_VAR_ADDERSS , tmp[1] ) ;
	write_lent = dw_by_oneself_adderss_var_display( INTERNAL_TEMP_COMPENSATION_DECADE_NUMBER_VAR_ADDERSS , tmp[0] ) ;
	return write_lent ;
}

int show_in_temp_alarm_threshold_date(int val){
	int tmp[2];
	int write_lent = -1 ;

	tmp[0] = val /10 ;
	tmp[1] = val %10 ;
	write_lent = dw_by_oneself_adderss_var_display( INTERNAL_TEMP_ALARM_THERSHOLD_DIGITS_NUMBER_VAR_ADDERSS , tmp[1] ) ;
	write_lent = dw_by_oneself_adderss_var_display( INTERNAL_TEMP_ALARM_THERSHOLD_DECADE_NUMBER_VAR_ADDERSS , tmp[0] ) ;

	return write_lent ;
}

int show_in_temp_humiture_sample_rate_date(int val){
	int tmp[2];
	int write_lent = -1 ;

	tmp[0] = val /10 ;
	tmp[1] = val %10 ;
	write_lent = dw_by_oneself_adderss_var_display( INTERNAL_TEMP_SAMPLE_RATE_DIGITS_NUMBER_VAR_ADDERSS , tmp[1] );
	write_lent = dw_by_oneself_adderss_var_display( INTERNAL_TEMP_SAMPLE_RATE_DECADE_NUMBER_VAR_ADDERSS , tmp[0] );

	return write_lent ;
}

/**************************************************内部湿度相关参数度显示************************************************************************/
int show_in_humill_compensation_date(int val){
	int tmp[2];
	int write_lent = -1 ;
	if( val >= 0){
		write_lent=dw_by_oneself_adderss_var_display( INTERNAL_HUMIDITY_COMPENSATION_INPUT_MINUS_VAR_ADDERSS , 0 ) ;
		tmp[0] = val /10 ;
		tmp[1] = val %10 ;
	}else{
		write_lent=dw_by_oneself_adderss_var_display( INTERNAL_HUMIDITY_COMPENSATION_INPUT_MINUS_VAR_ADDERSS , 1 ) ;
		tmp[0] = MINUS_CONVERT_POSITIVE(val) /10 ;
		tmp[1] = MINUS_CONVERT_POSITIVE(val) %10 ;
	}
	write_lent = dw_by_oneself_adderss_var_display( INTERNAL_HUMIDITY_COMPENSATION_DIGITS_NUMBER_VAR_ADDERSS , tmp[1] ) ;
	write_lent = dw_by_oneself_adderss_var_display( INTERNAL_HUMIDITY_COMPENSATION_DECADE_NUMBER_VAR_ADDERSS , tmp[0]  ) ;
	return write_lent ;
}

int show_in_humill_alarm_threshold_date(int val){
	int tmp[2];
	int write_lent = -1 ;

	tmp[0] = val /10 ;
	tmp[1] = val %10 ;
	write_lent = dw_by_oneself_adderss_var_display( INTERNAL_HUMIDITY_ALARM_THERSHOLD_DIGITS_NUMBER_VAR_ADDERSS , tmp[1] ) ;
	write_lent = dw_by_oneself_adderss_var_display( INTERNAL_HUMIDITY_ALARM_THERSHOLD_DECADE_NUMBER_VAR_ADDERSS , tmp[0] ) ;

	return write_lent ;
}


/**************************************************内部烟雾相关参数度显示************************************************************************/
int show_in_smoke_sample_rate_date(int val){
	int tmp[2];
	int write_lent = -1 ;

	tmp[0] = val /10 ;
	tmp[1] = val %10 ;
	write_lent = dw_by_oneself_adderss_var_display( INTERNAL_SMOKE_SAMPLE_RATE_DIGITS_NUMBER_VAR_ADDERSS , tmp[1] );
	write_lent = dw_by_oneself_adderss_var_display( INTERNAL_SMOKE_SAMPLE_RATE_DECADE_NUMBER_VAR_ADDERSS , tmp[0] );

	return write_lent ;
}

/**************************************************内部水浸相关参数度显示************************************************************************/
int show_in_water_sample_rate_date(int val){
	int tmp[2];
	int write_lent = -1 ;

	tmp[0] = val /10 ;
	tmp[1] = val %10 ;
	write_lent = dw_by_oneself_adderss_var_display( INTERNAL_WATER_SAMPLE_RATE_DIGITS_NUMBER_VAR_ADDERSS , tmp[1] );
	write_lent = dw_by_oneself_adderss_var_display( INTERNAL_WATER_SAMPLE_RATE_DECADE_NUMBER_VAR_ADDERSS , tmp[0] );

	return write_lent ;
}

/**************************************************自动返回主页相关参数度显示************************************************************************/
int show_sy_auto_exit_date(int val){
	int tmp[2];
	int write_lent = -1 ;

	tmp[0] = val /10 ;
	tmp[1] = val %10 ;
	write_lent = dw_by_oneself_adderss_var_display( AUTO_EXIT_INTPUT_TIME_DIGITS_NUMBER_VAR_ADDERSS , tmp[1] );
	write_lent = dw_by_oneself_adderss_var_display( AUTO_EXIT_INTPUT_TIME_DECADE_NUMBER_VAR_ADDERSS , tmp[0] );

	return write_lent ;
}

/**************************************************系统时钟相关参数度显示************************************************************************/
int show_sy_system_clock_years_date(int val){
	int tmp[2];
	int write_lent = -1 ;
	tmp[0] = val /10 ;
	tmp[1] = val %10 ;
	write_lent = dw_by_oneself_adderss_var_display( SYSTEM_TIME_INTPUT_YEARS_DIGITS_NUMBER_VAR_ADDERSS , tmp[1] );
	write_lent = dw_by_oneself_adderss_var_display( SYSTEM_TIME_INTPUT_YEARS_DECADE_NUMBER_VAR_ADDERSS , tmp[0] );
	return write_lent ;
}

int show_sy_system_clock_month_date(int val){
	int tmp[2];
	int write_lent = -1 ;
	tmp[0] = val /10 ;
	tmp[1] = val %10 ;
	write_lent = dw_by_oneself_adderss_var_display( SYSTEM_TIME_INTPUT_MONTH_DIGITS_NUMBER_VAR_ADDERSS , tmp[1] );
	write_lent = dw_by_oneself_adderss_var_display( SYSTEM_TIME_INTPUT_MONTH_DECADE_NUMBER_VAR_ADDERSS , tmp[0] );
	return write_lent ;
}

int show_sy_system_clock_days_date(int val){
	int tmp[2];
	int write_lent = -1 ;
	tmp[0] = val /10 ;
	tmp[1] = val %10 ;
	write_lent = dw_by_oneself_adderss_var_display( SYSTEM_TIME_INTPUT_DAYS_DIGITS_NUMBER_VAR_ADDERSS , tmp[1] );
	write_lent = dw_by_oneself_adderss_var_display( SYSTEM_TIME_INTPUT_DAYS_DECADE_NUMBER_VAR_ADDERSS , tmp[0] );
	return write_lent ;
}

int show_sy_system_clock_hours_date(int val){
	int tmp[2];
	int write_lent = -1 ;
	tmp[0] = val /10 ;
	tmp[1] = val %10 ;
	write_lent = dw_by_oneself_adderss_var_display( SYSTEM_TIME_INTPUT_HOUR_DIGITS_NUMBER_VAR_ADDERSS , tmp[1] );
	write_lent = dw_by_oneself_adderss_var_display( SYSTEM_TIME_INTPUT_HOUR_DECADE_NUMBER_VAR_ADDERSS , tmp[0] );
	return write_lent ;
}

int show_sy_system_clock_minute_date(int val){
	int tmp[2];
	int write_lent = -1 ;
	tmp[0] = val /10 ;
	tmp[1] = val %10 ;
	write_lent = dw_by_oneself_adderss_var_display( SYSTEM_TIME_INTPUT_MINUTE_DIGITS_NUMBER_VAR_ADDERSS , tmp[1] );
	write_lent = dw_by_oneself_adderss_var_display( SYSTEM_TIME_INTPUT_MINUTE_DECADE_NUMBER_VAR_ADDERSS , tmp[0] );
	return write_lent ;
}
/**************************************************系统网络相关参数度显示************************************************************************/

int show_system_ip_dhcp_state_date(int val){
	int write_lent = -1 ;
	write_lent = dw_by_oneself_adderss_var_display( SYSTEM_AUTO_IP_INDICATE_VAR_ADDERSS , val );
	return write_lent ;
}



int show_system_ip_addr1_intput_date(int val){
	int tmp[3];
	int write_lent = -1 ;

	tmp[0] = val / 100;
	tmp[1] = val % 100 / 10 ;
	tmp[2] = val % 100 % 10 ;

	write_lent = dw_by_oneself_adderss_var_display( SYSTEM_USER_IP_ADDR1_INTPUT_HUNDRED_NUMBER_VAR_ADDERSS , tmp[0] );
	write_lent = dw_by_oneself_adderss_var_display( SYSTEM_USER_IP_ADDR1_INTPUT_DECADE_NUMBER_VAR_ADDERSS , tmp[1] );
	write_lent = dw_by_oneself_adderss_var_display( SYSTEM_USER_IP_ADDR1_INTPUT_DIGITS_NUMBER_VAR_ADDERSS , tmp[2] );

	return write_lent ;
}
int show_system_ip_addr2_intput_date(int val){
	int tmp[3];
	int write_lent = -1 ;

	tmp[0] = val / 100;
	tmp[1] = val % 100 / 10 ;
	tmp[2] = val % 100 % 10 ;

	write_lent = dw_by_oneself_adderss_var_display( SYSTEM_USER_IP_ADDR2_INTPUT_HUNDRED_NUMBER_VAR_ADDERSS , tmp[0] );
	write_lent = dw_by_oneself_adderss_var_display( SYSTEM_USER_IP_ADDR2_INTPUT_DECADE_NUMBER_VAR_ADDERSS , tmp[1] );
	write_lent = dw_by_oneself_adderss_var_display( SYSTEM_USER_IP_ADDR2_INTPUT_DIGITS_NUMBER_VAR_ADDERSS , tmp[2] );
	return write_lent ;
}
int show_system_ip_addr3_intput_date(int val){
	int tmp[3];
	int write_lent = -1 ;

	tmp[0] = val / 100;
	tmp[1] = val % 100 / 10 ;
	tmp[2] = val % 100 % 10 ;

	write_lent = dw_by_oneself_adderss_var_display( SYSTEM_USER_IP_ADDR3_INTPUT_HUNDRED_NUMBER_VAR_ADDERSS , tmp[0] );
	write_lent = dw_by_oneself_adderss_var_display( SYSTEM_USER_IP_ADDR3_INTPUT_DECADE_NUMBER_VAR_ADDERSS , tmp[1] );
	write_lent = dw_by_oneself_adderss_var_display( SYSTEM_USER_IP_ADDR3_INTPUT_DIGITS_NUMBER_VAR_ADDERSS , tmp[2] );

	return write_lent ;
}
int show_system_ip_addr4_intput_date(int val){
	int tmp[3];
	int write_lent = -1 ;

	tmp[0] = val / 100;
	tmp[1] = val % 100 / 10 ;
	tmp[2] = val % 100 % 10 ;

	write_lent = dw_by_oneself_adderss_var_display( SYSTEM_USER_IP_ADDR4_INTPUT_HUNDRED_NUMBER_VAR_ADDERSS , tmp[0] );
	write_lent = dw_by_oneself_adderss_var_display( SYSTEM_USER_IP_ADDR4_INTPUT_DECADE_NUMBER_VAR_ADDERSS , tmp[1] );
	write_lent = dw_by_oneself_adderss_var_display( SYSTEM_USER_IP_ADDR4_INTPUT_DIGITS_NUMBER_VAR_ADDERSS , tmp[2] );

	return write_lent ;
}

int show_system_ip_mask1_intput_date(int val){
	int tmp[3];
	int write_lent = -1 ;

	tmp[0] = val / 100;
	tmp[1] = val % 100 / 10 ;
	tmp[2] = val % 100 % 10 ;

	write_lent = dw_by_oneself_adderss_var_display( SYSTEM_USER_IP_MASK1_INTPUT_HUNDRED_NUMBER_VAR_ADDERSS , tmp[0] );
	write_lent = dw_by_oneself_adderss_var_display( SYSTEM_USER_IP_MASK1_INTPUT_DECADE_NUMBER_VAR_ADDERSS , tmp[1] );
	write_lent = dw_by_oneself_adderss_var_display( SYSTEM_USER_IP_MASK1_INTPUT_DIGITS_NUMBER_VAR_ADDERSS , tmp[2] );

	return write_lent ;
}
int show_system_ip_mask2_intput_date(int val){
	int tmp[3];
	int write_lent = -1 ;

	tmp[0] = val / 100;
	tmp[1] = val % 100 / 10 ;
	tmp[2] = val % 100 % 10 ;

	write_lent = dw_by_oneself_adderss_var_display( SYSTEM_USER_IP_MASK2_INTPUT_HUNDRED_NUMBER_VAR_ADDERSS , tmp[0] );
	write_lent = dw_by_oneself_adderss_var_display( SYSTEM_USER_IP_MASK2_INTPUT_DECADE_NUMBER_VAR_ADDERSS , tmp[1] );
	write_lent = dw_by_oneself_adderss_var_display( SYSTEM_USER_IP_MASK2_INTPUT_DIGITS_NUMBER_VAR_ADDERSS , tmp[2] );

	return write_lent ;
}
int show_system_ip_mask3_intput_date(int val){
	int tmp[3];
	int write_lent = -1 ;

	tmp[0] = val / 100;
	tmp[1] = val % 100 / 10 ;
	tmp[2] = val % 100 % 10 ;

	write_lent = dw_by_oneself_adderss_var_display( SYSTEM_USER_IP_MASK3_INTPUT_HUNDRED_NUMBER_VAR_ADDERSS , tmp[0] );
	write_lent = dw_by_oneself_adderss_var_display( SYSTEM_USER_IP_MASK3_INTPUT_DECADE_NUMBER_VAR_ADDERSS , tmp[1] );
	write_lent = dw_by_oneself_adderss_var_display( SYSTEM_USER_IP_MASK3_INTPUT_DIGITS_NUMBER_VAR_ADDERSS , tmp[2] );

	return write_lent ;
}
int show_system_ip_mask4_intput_date(int val){
	int tmp[3];
	int write_lent = -1 ;

	tmp[0] = val / 100;
	tmp[1] = val % 100 / 10 ;
	tmp[2] = val % 100 % 10 ;

	write_lent = dw_by_oneself_adderss_var_display( SYSTEM_USER_IP_MASK4_INTPUT_HUNDRED_NUMBER_VAR_ADDERSS , tmp[0] );
	write_lent = dw_by_oneself_adderss_var_display( SYSTEM_USER_IP_MASK4_INTPUT_DECADE_NUMBER_VAR_ADDERSS , tmp[1] );
	write_lent = dw_by_oneself_adderss_var_display( SYSTEM_USER_IP_MASK4_INTPUT_DIGITS_NUMBER_VAR_ADDERSS , tmp[2] );

	return write_lent ;
}

int show_system_ip_gateway1_intput_date(int val){
	int tmp[3];
	int write_lent = -1 ;

	tmp[0] = val / 100;
	tmp[1] = val % 100 / 10 ;
	tmp[2] = val % 100 % 10 ;

	write_lent = dw_by_oneself_adderss_var_display( SYSTEM_USER_IP_GATEWAY1_INTPUT_HUNDRED_NUMBER_VAR_ADDERSS , tmp[0] );
	write_lent = dw_by_oneself_adderss_var_display( SYSTEM_USER_IP_GATEWAY1_INTPUT_DECADE_NUMBER_VAR_ADDERSS , tmp[1] );
	write_lent = dw_by_oneself_adderss_var_display( SYSTEM_USER_IP_GATEWAY1_INTPUT_DIGITS_NUMBER_VAR_ADDERSS , tmp[2] );

	return write_lent ;
}
int show_system_ip_gateway2_intput_date(int val){
	int tmp[3];
	int write_lent = -1 ;

	tmp[0] = val / 100;
	tmp[1] = val % 100 / 10 ;
	tmp[2] = val % 100 % 10 ;

	write_lent = dw_by_oneself_adderss_var_display( SYSTEM_USER_IP_GATEWAY2_INTPUT_HUNDRED_NUMBER_VAR_ADDERSS , tmp[0] );
	write_lent = dw_by_oneself_adderss_var_display( SYSTEM_USER_IP_GATEWAY2_INTPUT_DECADE_NUMBER_VAR_ADDERSS , tmp[1] );
	write_lent = dw_by_oneself_adderss_var_display( SYSTEM_USER_IP_GATEWAY2_INTPUT_DIGITS_NUMBER_VAR_ADDERSS , tmp[2] );

	return write_lent ;
}
int show_system_ip_gateway3_intput_date(int val){
	int tmp[3];
	int write_lent = -1 ;

	tmp[0] = val / 100;
	tmp[1] = val % 100 / 10 ;
	tmp[2] = val % 100 % 10 ;

	write_lent = dw_by_oneself_adderss_var_display( SYSTEM_USER_IP_GATEWAY3_INTPUT_HUNDRED_NUMBER_VAR_ADDERSS , tmp[0] );
	write_lent = dw_by_oneself_adderss_var_display( SYSTEM_USER_IP_GATEWAY3_INTPUT_DECADE_NUMBER_VAR_ADDERSS , tmp[1] );
	write_lent = dw_by_oneself_adderss_var_display( SYSTEM_USER_IP_GATEWAY3_INTPUT_DIGITS_NUMBER_VAR_ADDERSS , tmp[2] );

	return write_lent ;
}
int show_system_ip_gateway4_intput_date(int val){
	int tmp[3];
	int write_lent = -1 ;

	tmp[0] = val / 100;
	tmp[1] = val % 100 / 10 ;
	tmp[2] = val % 100 % 10 ;

	write_lent = dw_by_oneself_adderss_var_display( SYSTEM_USER_IP_GATEWAY4_INTPUT_HUNDRED_NUMBER_VAR_ADDERSS , tmp[0] );
	write_lent = dw_by_oneself_adderss_var_display( SYSTEM_USER_IP_GATEWAY4_INTPUT_DECADE_NUMBER_VAR_ADDERSS , tmp[1] );
	write_lent = dw_by_oneself_adderss_var_display( SYSTEM_USER_IP_GATEWAY4_INTPUT_DIGITS_NUMBER_VAR_ADDERSS , tmp[2] );

	return write_lent ;
}





int show_system_server_ip_addr1_intput_date(int val){
	int tmp[3];
	int write_lent = -1 ;

	tmp[0] = val / 100;
	tmp[1] = val % 100 / 10 ;
	tmp[2] = val % 100 % 10 ;

	write_lent = dw_by_oneself_adderss_var_display( SYSTEM_SYS_COMMUNICATE_SERVER_IP_ADDR1_INTPUT_HUNDRED_NUMBER_VAR_ADDERSS , tmp[0] );
	write_lent = dw_by_oneself_adderss_var_display( SYSTEM_SYS_COMMUNICATE_SERVER_IP_ADDR1_INTPUT_DECADE_NUMBER_VAR_ADDERSS , tmp[1] );
	write_lent = dw_by_oneself_adderss_var_display( SYSTEM_SYS_COMMUNICATE_SERVER_IP_ADDR1_INTPUT_DIGITS_NUMBER_VAR_ADDERSS , tmp[2] );

	return write_lent ;
}

int show_system_server_ip_addr2_intput_date(int val){
	int tmp[3];
	int write_lent = -1 ;

	tmp[0] = val / 100;
	tmp[1] = val % 100 / 10 ;
	tmp[2] = val % 100 % 10 ;

	write_lent = dw_by_oneself_adderss_var_display( SYSTEM_SYS_COMMUNICATE_SERVER_IP_ADDR2_INTPUT_HUNDRED_NUMBER_VAR_ADDERSS , tmp[0] );
	write_lent = dw_by_oneself_adderss_var_display( SYSTEM_SYS_COMMUNICATE_SERVER_IP_ADDR2_INTPUT_DECADE_NUMBER_VAR_ADDERSS , tmp[1] );
	write_lent = dw_by_oneself_adderss_var_display( SYSTEM_SYS_COMMUNICATE_SERVER_IP_ADDR2_INTPUT_DIGITS_NUMBER_VAR_ADDERSS , tmp[2] );
	return write_lent ;
}

int show_system_server_ip_addr3_intput_date(int val){
	int tmp[3];
	int write_lent = -1 ;

	tmp[0] = val / 100;
	tmp[1] = val % 100 / 10 ;
	tmp[2] = val % 100 % 10 ;

	write_lent = dw_by_oneself_adderss_var_display( SYSTEM_SYS_COMMUNICATE_SERVER_IP_ADDR3_INTPUT_HUNDRED_NUMBER_VAR_ADDERSS , tmp[0] );
	write_lent = dw_by_oneself_adderss_var_display( SYSTEM_SYS_COMMUNICATE_SERVER_IP_ADDR3_INTPUT_DECADE_NUMBER_VAR_ADDERSS , tmp[1] );
	write_lent = dw_by_oneself_adderss_var_display( SYSTEM_SYS_COMMUNICATE_SERVER_IP_ADDR3_INTPUT_DIGITS_NUMBER_VAR_ADDERSS , tmp[2] );

	return write_lent ;
}

int show_system_server_ip_addr4_intput_date(int val){
	int tmp[3];
	int write_lent = -1 ;

	tmp[0] = val / 100;
	tmp[1] = val % 100 / 10 ;
	tmp[2] = val % 100 % 10 ;

	write_lent = dw_by_oneself_adderss_var_display( SYSTEM_SYS_COMMUNICATE_SERVER_IP_ADDR4_INTPUT_HUNDRED_NUMBER_VAR_ADDERSS , tmp[0] );
	write_lent = dw_by_oneself_adderss_var_display( SYSTEM_SYS_COMMUNICATE_SERVER_IP_ADDR4_INTPUT_DECADE_NUMBER_VAR_ADDERSS , tmp[1] );
	write_lent = dw_by_oneself_adderss_var_display( SYSTEM_SYS_COMMUNICATE_SERVER_IP_ADDR4_INTPUT_DIGITS_NUMBER_VAR_ADDERSS , tmp[2] );

	return write_lent ;
}




int show_system_communicate_port_date(int val){
	int tmp[4];
	int write_lent = -1 ;

	tmp[0] = val / 1000 ;
	tmp[1] = val % 1000 / 100;
	tmp[2] = val % 1000 % 100 / 10;
	tmp[3] = val % 1000 % 100 % 10;

	write_lent = dw_by_oneself_adderss_var_display( SYSTEM_SYS_COMMUNICATE_PORT_INTPUT_THOUSAND_NUMBER_VAR_ADDERSS , tmp[0] );
	write_lent = dw_by_oneself_adderss_var_display( SYSTEM_SYS_COMMUNICATE_PORT_INTPUT_HUNDREDS_NUMBER_VAR_ADDERSS , tmp[1] );
	write_lent = dw_by_oneself_adderss_var_display( SYSTEM_SYS_COMMUNICATE_PORT_INTPUT_DIGITS_NUMBER_VAR_ADDERSS , tmp[2] );
	write_lent = dw_by_oneself_adderss_var_display( SYSTEM_SYS_COMMUNICATE_PORT_INTPUT_DECADE_NUMBER_VAR_ADDERSS , tmp[3] );
	return write_lent ;
}
int show_system_login_id_date(int val){
	int tmp[4];
	int write_lent = -1 ;

	tmp[0] = val / 1000 ;
	tmp[1] = val % 1000 / 100;
	tmp[2] = val % 1000 % 100 / 10;
	tmp[3] = val % 1000 % 100 % 10;

	write_lent = dw_by_oneself_adderss_var_display( SYSTEM_SYS_COMMUNICATE_ID_INTPUT_THOUSAND_NUMBER_VAR_ADDERSS , tmp[0] );
	write_lent = dw_by_oneself_adderss_var_display( SYSTEM_SYS_COMMUNICATE_ID_INTPUT_HUNDREDS_NUMBER_VAR_ADDERSS , tmp[1] );
	write_lent = dw_by_oneself_adderss_var_display( SYSTEM_SYS_COMMUNICATE_ID_INTPUT_DIGITS_NUMBER_VAR_ADDERSS , tmp[2] );
	write_lent = dw_by_oneself_adderss_var_display( SYSTEM_SYS_COMMUNICATE_ID_INTPUT_DECADE_NUMBER_VAR_ADDERSS , tmp[3] );
	return write_lent ;
}

int show_system_login_passwd_date(int val){
	int tmp[8];
	int write_lent = -1 ;

	tmp[0] = val / 10000000 ;
	tmp[1] = val % 10000000 /1000000 ;
	tmp[2] = val % 10000000 %1000000/100000 ;
	tmp[3] = val % 10000000 %1000000%100000/10000 ;
	tmp[4] = val % 10000000 %1000000%100000%10000/1000 ;
	tmp[5] = val % 10000000 %1000000%100000%10000%1000/100 ;
	tmp[6] = val % 10000000 %1000000%100000%10000%1000%100/10 ;
	tmp[7] = val % 10000000 %1000000%100000%10000%1000%100%10 ;

	write_lent = dw_by_oneself_adderss_var_display( SYSTEM_SYS_COMMUNICATE_PASSWD_INTPUT_8_NUMBER_VAR_ADDERSS , tmp[0] );
	write_lent = dw_by_oneself_adderss_var_display( SYSTEM_SYS_COMMUNICATE_PASSWD_INTPUT_7_NUMBER_VAR_ADDERSS , tmp[1] );
	write_lent = dw_by_oneself_adderss_var_display( SYSTEM_SYS_COMMUNICATE_PASSWD_INTPUT_6_NUMBER_VAR_ADDERSS , tmp[2] );
	write_lent = dw_by_oneself_adderss_var_display( SYSTEM_SYS_COMMUNICATE_PASSWD_INTPUT_5_NUMBER_VAR_ADDERSS , tmp[3] );
	write_lent = dw_by_oneself_adderss_var_display( SYSTEM_SYS_COMMUNICATE_PASSWD_INTPUT_4_NUMBER_VAR_ADDERSS , tmp[4] );
	write_lent = dw_by_oneself_adderss_var_display( SYSTEM_SYS_COMMUNICATE_PASSWD_INTPUT_3_NUMBER_VAR_ADDERSS , tmp[5] );
	write_lent = dw_by_oneself_adderss_var_display( SYSTEM_SYS_COMMUNICATE_PASSWD_INTPUT_2_NUMBER_VAR_ADDERSS , tmp[6] );
	write_lent = dw_by_oneself_adderss_var_display( SYSTEM_SYS_COMMUNICATE_PASSWD_INTPUT_1_NUMBER_VAR_ADDERSS , tmp[7] );
	return write_lent ;
}
/**************************************************系统控制-光照强度控制参数度显示************************************************************************/

int show_system_control_illumination_disable_state_date(int val){
	int write_lent = -1 ;
	write_lent = dw_by_oneself_adderss_var_display( SYSTEM_SYS_ILLUMINATION_CONTROL_DISABLE_CURSOR_VAR_ADDERSS , val );
	return write_lent ;
}

int show_system_present_control_illumination_clsoe_value_date(int val){
	int tmp[2];
	int write_lent = -1 ;
	tmp[0] = val /10 ;
	tmp[1] = val %10 ;
	write_lent = dw_by_oneself_adderss_var_display( SYSTEM_ILLUMINATION_CONTROL_SHOW_CLOSE_VALUE_DIGITS_NUMBER_VAR_ADDERSS , tmp[0] );
	write_lent = dw_by_oneself_adderss_var_display( SYSTEM_ILLUMINATION_CONTROL_SHOW_CLOSE_VALUE_DECADE_NUMBER_VAR_ADDERSS , tmp[1] );
	return write_lent ;
}

int show_system_intput_control_illumination_clsoe_value_date(int val){
	int tmp[2];
	int write_lent = -1 ;
	tmp[0] = val /10 ;
	tmp[1] = val %10 ;
	write_lent = dw_by_oneself_adderss_var_display( SYSTEM_ILLUMINATION_CONTROL_CLOSE_INTPUT_DIGITS_NUMBER_VAR_ADDERSS , tmp[0] );
	write_lent = dw_by_oneself_adderss_var_display( SYSTEM_ILLUMINATION_CONTROL_CLOSE_INTPUT_DECADE_NUMBER_VAR_ADDERSS , tmp[1] );
	return write_lent ;
}

int show_system_present_control_illumination_open_value_date(int val){
	int tmp[2];
	int write_lent = -1 ;
	tmp[0] = val /10 ;
	tmp[1] = val %10 ;
	write_lent = dw_by_oneself_adderss_var_display( SYSTEM_ILLUMINATION_CONTROL_SHOW_OPEN_VALUE_DIGITS_NUMBER_VAR_ADDERSS , tmp[0] );
	write_lent = dw_by_oneself_adderss_var_display( SYSTEM_ILLUMINATION_CONTROL_SHOW_OPEN_VALUE_DECADE_NUMBER_VAR_ADDERSS , tmp[1] );
	return write_lent ;
}

int show_system_intput_control_illumination_open_value_date(int val){
	int tmp[2];
	int write_lent = -1 ;
	tmp[0] = val /10 ;
	tmp[1] = val %10 ;
	write_lent = dw_by_oneself_adderss_var_display( SYSTEM_ILLUMINATION_CONTROL_OPEN_INTPUT_DIGITS_NUMBER_VAR_ADDERSS , tmp[0] );
	write_lent = dw_by_oneself_adderss_var_display( SYSTEM_ILLUMINATION_CONTROL_OPEN_INTPUT_DECADE_NUMBER_VAR_ADDERSS , tmp[1] );
	return write_lent ;
}
/**************************************************系统控制-系统时间控制参数度显示************************************************************************/
int show_system_control_timer_disable_state_date(int val){
	int write_lent = -1 ;
	write_lent = dw_by_oneself_adderss_var_display( SYSTEM_SYS_TIMER_CONTROL_DISABLE_CURSOR_VAR_ADDERSS , val );
	return write_lent ;
}

int show_system_intput_control_timer_am_open_value_date(int val){
	int tmp[2];
	int write_lent = -1 ;
	tmp[0] = val /10 ;
	tmp[1] = val %10 ;
	write_lent = dw_by_oneself_adderss_var_display( SYSTEM_TIMER_AM_OPEN_CONTROL_CLOSE_INTPUT_DIGITS_NUMBER_VAR_ADDERSS , tmp[0] );
	write_lent = dw_by_oneself_adderss_var_display( SYSTEM_TIMER_AM_OPEN_CONTROL_CLOSE_INTPUT_DECADE_NUMBER_VAR_ADDERSS , tmp[1] );
	return write_lent ;
}

int show_system_intput_control_timer_pm_open_value_date(int val){
	int tmp[2];
	int write_lent = -1 ;
	tmp[0] = val /10 ;
	tmp[1] = val %10 ;
	write_lent = dw_by_oneself_adderss_var_display( SYSTEM_TIMER_PM_OPEN_CONTROL_CLOSE_INTPUT_DIGITS_NUMBER_VAR_ADDERSS , tmp[0] );
	write_lent = dw_by_oneself_adderss_var_display( SYSTEM_TIMER_PM_OPEN_CONTROL_CLOSE_INTPUT_DECADE_NUMBER_VAR_ADDERSS , tmp[1] );
	return write_lent ;
}
/**************************************************系统控制-湿度差控制参数度显示************************************************************************/
int show_system_intput_control_humidity_close_value_date(int val){
	int tmp[2];
	int write_lent = -1 ;
	tmp[0] = val /10 ;
	tmp[1] = val %10 ;
	write_lent = dw_by_oneself_adderss_var_display( SYSTEM_HUMIDITY_CLOSE_CONTROL_INTPUT_DIGITS_NUMBER_VAR_ADDERSS , tmp[0] );
	write_lent = dw_by_oneself_adderss_var_display( SYSTEM_HUMIDITY_CLOSE_CONTROL_INTPUT_DECADE_NUMBER_VAR_ADDERSS , tmp[1] );
	return write_lent ;
}

int show_system_intput_control_humidity_open_value_date(int val){
	int tmp[2];
	int write_lent = -1 ;
	tmp[0] = val /10 ;
	tmp[1] = val %10 ;
	write_lent = dw_by_oneself_adderss_var_display( SYSTEM_HUMIDITY_OPEN_CONTRO_INTPUT_DIGITS_NUMBER_VAR_ADDERSS , tmp[0] );
	write_lent = dw_by_oneself_adderss_var_display( SYSTEM_HUMIDITY_OPEN_CONTROL_INTPUT_DECADE_NUMBER_VAR_ADDERSS , tmp[1] );
	return write_lent ;
}
/**************************************************系统控制-温度控制参数度显示************************************************************************/
int show_system_intput_control_in_temperature_close_value_date(int val){
	int tmp[2];
	int write_lent = -1 ;
	tmp[0] = val /10 ;
	tmp[1] = val %10 ;
	write_lent = dw_by_oneself_adderss_var_display( SYSTEM_IN_TEMPERATURE_CLOSE_CONTROL_INTPUT_DIGITS_NUMBER_VAR_ADDERSS , tmp[0] );
	write_lent = dw_by_oneself_adderss_var_display( SYSTEM_IN_TEMPERATURE_CLOSE_CONTROL_INTPUT_DECADE_NUMBER_VAR_ADDERSS , tmp[1] );
	return write_lent ;
}

int show_system_intput_control_ex_temperature_close_value_date(int val){
	int tmp[2];
	int write_lent = -1 ;
	tmp[0] = val /10 ;
	tmp[1] = val %10 ;
	write_lent = dw_by_oneself_adderss_var_display( SYSTEM_EX_TEMPERATURE_CLOSE_CONTROL_INTPUT_DIGITS_NUMBER_VAR_ADDERSS , tmp[0] );
	write_lent = dw_by_oneself_adderss_var_display( SYSTEM_EX_TEMPERATURE_CLOSE_CONTROL_INTPUT_DECADE_NUMBER_VAR_ADDERSS , tmp[1] );
	return write_lent ;
}

int show_system_intput_control_temperature_differ_close_value_date(int val){
	int tmp[2];
	int write_lent = -1 ;
	tmp[0] = val /10 ;
	tmp[1] = val %10 ;
	write_lent = dw_by_oneself_adderss_var_display( SYSTEM_TEMPERATURE_DIFFERENCE_CLOSE_CONTROL_INTPUT_DIGITS_NUMBER_VAR_ADDERSS , tmp[0] );
	write_lent = dw_by_oneself_adderss_var_display( SYSTEM_TEMPERATURE_DIFFERENCE_CLOSE_CONTROL_INTPUT_DECADE_NUMBER_VAR_ADDERSS , tmp[1] );
	return write_lent ;
}

int show_system_intput_control_temperature_differ_open_value_date(int val){
	int tmp[2];
	int write_lent = -1 ;
	tmp[0] = val /10 ;
	tmp[1] = val %10 ;
	write_lent = dw_by_oneself_adderss_var_display( SYSTEM_TEMPERATURE_DIFFERENCE_OPEN_CONTROL_INTPUT_DIGITS_NUMBER_VAR_ADDERSS , tmp[0] );
	write_lent = dw_by_oneself_adderss_var_display( SYSTEM_TEMPERATURE_DIFFERENCE_OPEN_CONTROL_INTPUT_DECADE_NUMBER_VAR_ADDERSS , tmp[1] );
	return write_lent ;
}
/**************************************************系统控制-盖板延时关闭参数度显示************************************************************************/
int show_system_temperature_delay_close_value_date(int val){
	int tmp[3];
	int write_lent = -1 ;
	tmp[0] = val /100 ;
	tmp[1] = val %100/10 ;
	tmp[2] = val %100%10 ;
	write_lent = dw_by_oneself_adderss_var_display( SYSTEM_TEMPERATURE_DELAY_CLOSE_CONTROL_INTPUT_HUNDREDS_NUMBER_VAR_ADDERSS , tmp[0] );
	write_lent = dw_by_oneself_adderss_var_display( SYSTEM_TEMPERATURE_DELAY_CLOSE_CONTROL_INTPUT_DIGITS_NUMBER_VAR_ADDERSS , tmp[1] );
	write_lent = dw_by_oneself_adderss_var_display( SYSTEM_TEMPERATURE_DELAY_CLOSE_CONTROL_INTPUT_DECADE_NUMBER_VAR_ADDERSS , tmp[2] );
	return write_lent ;
}

int show_system_humidity_delay_close_value_date(int val){
	int tmp[3];
	int write_lent = -1 ;
	tmp[0] = val /100 ;
	tmp[1] = val %100/10 ;
	tmp[2] = val %100%10 ;
	write_lent = dw_by_oneself_adderss_var_display( SYSTEM_HUMIDITY_DELAY_CLOSE_CONTROL_INTPUT_HUNDREDS_NUMBER_VAR_ADDERSS , tmp[0] );
	write_lent = dw_by_oneself_adderss_var_display( SYSTEM_HUMIDITY_DELAY_CLOSE_CONTROL_INTPUT_DIGITS_NUMBER_VAR_ADDERSS , tmp[1] );
	write_lent = dw_by_oneself_adderss_var_display( SYSTEM_HUMIDITY_DELAY_CLOSE_CONTROL_INTPUT_DECADE_NUMBER_VAR_ADDERSS , tmp[2] );
	return write_lent ;
}

int show_system_illumination_delay_close_value_date(int val){
	int tmp[3];
	int write_lent = -1 ;
	tmp[0] = val /100 ;
	tmp[1] = val %100/10 ;
	tmp[2] = val %100%10 ;
	write_lent = dw_by_oneself_adderss_var_display( SYSTEM_ILLUMIAATION_DELAY_CLOSE_CONTROL_INTPUT_HUNDREDS_NUMBER_VAR_ADDERSS , tmp[0] );
	write_lent = dw_by_oneself_adderss_var_display( SYSTEM_ILLUMIAATION_DELAY_CLOSE_CONTROL_INTPUT_DIGITS_NUMBER_VAR_ADDERSS , tmp[1] );
	write_lent = dw_by_oneself_adderss_var_display( SYSTEM_ILLUMIAATION_DELAY_CLOSE_CONTROL_INTPUT_DECADE_NUMBER_VAR_ADDERSS , tmp[2] );
	return write_lent ;
}

/**************************************************系统控制-屏幕控制参数度显示************************************************************************/
int show_system_control_display_luminance_value_date(int val){
	int tmp[3];
	int write_lent = -1 ;
	tmp[0] = val /100 ;
	tmp[1] = val %100/10 ;
	tmp[2] = val %100%10 ;
	write_lent = dw_by_oneself_adderss_var_display( SYSTEM_DISPLAY_LUMINANCE_CONTROL_INTPUT_HUNDREDS_NUMBER_VAR_ADDERSS , tmp[0] );
	write_lent = dw_by_oneself_adderss_var_display( SYSTEM_DISPLAY_LUMINANCE_CONTROL_INTPUT_DIGITS_NUMBER_VAR_ADDERSS , tmp[1] );
	write_lent = dw_by_oneself_adderss_var_display( SYSTEM_DISPLAY_LUMINANCE_CONTROL_INTPUT_DECADE_NUMBER_VAR_ADDERSS , tmp[2] );
	return write_lent ;
}

int show_system_control_display_delay_close_value_date(int val){
	int tmp[2];
	int write_lent = -1 ;
	tmp[0] = val /10 ;
	tmp[1] = val %10 ;
	write_lent = dw_by_oneself_adderss_var_display( SYSTEM_DISPLAY_TIMER_CONTROL_INTPUT_DIGITS_NUMBER_VAR_ADDERSS , tmp[0] );
	write_lent = dw_by_oneself_adderss_var_display( SYSTEM_DISPLAY_TIMER_CONTROL_INTPUT_DECADE_NUMBER_VAR_ADDERSS , tmp[1] );
	return write_lent ;
}

int dw_control_display_luminance_date(int display_luminance_date){
	int write_lent = -1 ;
	msg_write_var_t write_var_msg;
	uint8_t write_var_pkt[8];
	write_var_msg.var_adderss = 0x0082;
//	write_var_msg.var_data = (display_luminance_date <<8) | 0x0064  ;
	write_var_msg.var_data = (display_luminance_date <<8) | display_luminance_date  ;
	package_write_var_data(write_var_msg, write_var_pkt);

	write_lent = dw_device_send(write_var_pkt,sizeof(write_var_pkt));
	return write_lent ;
}



/**************************************************其他参数-设置密码显示************************************************************************/
int show_set_menuconfig_passwd_date(int val){
	int tmp[4];
	int write_lent = -1 ;

	tmp[0] = val / 1000 ;
	tmp[1] = val % 1000 / 100;
	tmp[2] = val % 1000 % 100 / 10;
	tmp[3] = val % 1000 % 100 % 10;

	write_lent = dw_by_oneself_adderss_var_display( SETTING_LOGIN_PASSWD_INTPUT_THOUSAND_NUMBER_VAR_ADDERSS , tmp[3] );
	write_lent = dw_by_oneself_adderss_var_display( SETTING_LOGIN_PASSWD_INTPUT_HUNDREDS_NUMBER_VAR_ADDERSS , tmp[2] );
	write_lent = dw_by_oneself_adderss_var_display( SETTING_LOGIN_PASSWD_INTPUT_DIGITS_NUMBER_VAR_ADDERSS , tmp[1] );
	write_lent = dw_by_oneself_adderss_var_display( SETTING_LOGIN_PASSWD_INTPUT_DECADE_NUMBER_VAR_ADDERSS , tmp[0] );
	return write_lent ;
}

/**************************************************菜单密码验证显示************************************************************************/
int show_enter_menuconfig_passwd_date(int val){
	int tmp[4];
	int write_lent = -1 ;

	tmp[0] = val / 1000 ;
	tmp[1] = val % 1000 / 100;
	tmp[2] = val % 1000 % 100 / 10;
	tmp[3] = val % 1000 % 100 % 10;

	write_lent = dw_by_oneself_adderss_var_display( ENTER_MENUCONFIG_PASSWD_INTPUT_THOUSAND_NUMBER_VAR_ADDERSS , tmp[3] );
	write_lent = dw_by_oneself_adderss_var_display( ENTER_MENUCONFIG_PASSWD_INTPUT_HUNDREDS_NUMBER_VAR_ADDERSS , tmp[2] );
	write_lent = dw_by_oneself_adderss_var_display( ENTER_MENUCONFIG_PASSWD_INTPUT_DIGITS_NUMBER_VAR_ADDERSS , tmp[1] );
	write_lent = dw_by_oneself_adderss_var_display( ENTER_MENUCONFIG_PASSWD_INTPUT_DECADE_NUMBER_VAR_ADDERSS , tmp[0] );
	return write_lent ;
}
