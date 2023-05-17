/*
 * dw_function.c
 *
 *  Created on: 2023年2月10日
 *      Author: 好
 */

#define LOG_TAG    "dw_function"

#include "../app/dw_function.h"

static int *ip_char_string_cove(char* string );

static int animation_off_step = 24 ;
static int animation_on_step = 0 ;

int dw_function_init(void){

	return 0;
}






int dw_show_ip_adderss(void){
	int ret = -1 ,dhcp_ret=-1;
	int *ip_data= NULL;
	struct eth eth0_t;
	mqtt_ip_tcp_def set_dhcp_mqtt_ip_tcp;

	read_saveenv_cjson_mqttip_parameter(&set_dhcp_mqtt_ip_tcp);
	if(strcmp(set_dhcp_mqtt_ip_tcp.ip_acquisition_type,"dhcp") == 0){
		dhcp_ret = network_eth0_dhcp_status("eth0",&eth0_t);
		if(dhcp_ret != 0 ){
			strcpy(eth0_t.ip_adderss,set_dhcp_mqtt_ip_tcp.ip);
		}
	}else{
		strcpy(eth0_t.ip_adderss,set_dhcp_mqtt_ip_tcp.ip);
	}
	ip_data = ip_char_string_cove(eth0_t.ip_adderss);
	if(ip_data==NULL){
		log_e("cove read ip error !");
		free(ip_data);
		return 1 ;
	}

	ret = dw_ip_var_adderss(ip_data);
	if(ret <=0){
		log_e("show ip error !");
		free(ip_data);
		return 1 ;
	}
	free(ip_data);
	return ret ;
}

//int dw_show_netmask_adderss(void){
//	int ret = -1 ;
//	char *netmask = NULL;
//	int *netmask_data= NULL;
//
//	netmask=get_interfaces_netmask();
//	if(netmask==0){
//		log_e("read netmask error !");
//		free(netmask);
//		return 1 ;
//	}
//	netmask_data = ip_char_string_cove(netmask);
//	if(netmask_data==0){
//		log_e("cove read netmask error !");
//		free(netmask);
//		free(netmask_data);
//		return 1 ;
//	}
//	ret = dw_netmask_var(netmask_data);
//	if(ret <=0){
//		log_e("show netmask error !");
//		free(netmask);
//		free(netmask_data);
//		return 1 ;
//	}
//	free(netmask);
//	free(netmask_data);
//	return ret ;
//}
//
//int dw_show_gw_adderss(void){
//	int ret = -1 ;
//	char *gw = NULL;
//	int *gw_data= NULL;
//
//	gw=get_interfaces_route_gw();
//	if(gw==0){
//		log_e("read gw error !");
//		free(gw);
//		return 1 ;
//	}
//	gw_data = ip_char_string_cove(gw);
//	if(gw_data==0){
//		log_e("cove read gw_data error !");
//		free(gw);
//		free(gw_data);
//		return 1 ;
//	}
//	ret = dw_route_gw_var(gw_data);
//	if(ret <=0){
//		log_e("show gw error !");
//		free(gw);
//		free(gw_data);
//		return 1 ;
//	}
//	free(gw);
//	free(gw_data);
//	return ret ;
//}

//int dw_show_broadcast_adderss(void){
//	int ret = -1 ;
//	char *broadcast = NULL;
//	int *broadcast_data= NULL;
//
//	broadcast=get_interfaces_broadcast();
//	if(broadcast==0){
//		log_e("read broadcast error !");
//		 free(broadcast);
//		return 1 ;
//	}
//	broadcast_data = ip_char_string_cove(broadcast);
//	if(broadcast_data==0){
//		log_e("cove read broadcast_data error !");
//		free(broadcast_data);
//		free(broadcast);
//		return 1 ;
//	}
//	ret = dw_broadcast_var(broadcast_data);
//	if(ret <=0){
//		log_e("show broadcast error !");
//		free(broadcast_data);
//		free(broadcast);
//		return 1 ;
//	}
//	free(broadcast_data);
//	free(broadcast);
//	return ret ;
//}



int dw_show_time_adderss(void){
	int ret = -1 ;
	struct tm t;
	static int old_min = -1 ;

	read_sys_time( &t );
	if(old_min == t.tm_min){
		return 1;
	}
	old_min=t.tm_min;
	ret = dw_time_var(&t);
	if(ret <=0){
		log_e("show time error !");
		return -1 ;
	}

	return ret ;
}


int dw_show_eth_connect_state(uint8_t eth_state){
	int write_lent = -1 ;
	write_lent=dw_eth_connect_state(eth_state);
	return write_lent ;
}


int dw_show_cumulative_time(void){
	int write_lent = -1 ;
	write_lent=dw_cumulative_time(4332);
	return write_lent ;
}

int dw_show_external_temperature(void){
	int write_lent = -1 ;
	int tmp = 0 ;
	if( deal_transducer_masg_t.external_temperature_date < 0 ){
		tmp = ~(deal_transducer_masg_t.external_temperature_date-1) ;
		write_lent=dw_external_temperature(tmp);
	}else{
		write_lent=dw_external_temperature(deal_transducer_masg_t.external_temperature_date);
	}
	log_i("external temperature =%d",deal_transducer_masg_t.external_temperature_date);
	return write_lent ;
}

int dw_show_external_humidity(void){
	int write_lent = -1 ;
	write_lent=dw_external_humidity(deal_transducer_masg_t.external_humidity_date);
	log_i("external humidity =%d",deal_transducer_masg_t.external_humidity_date);
	return write_lent ;
}


int dw_show_interior_temperature(void){
	int write_lent = -1 ;
	int tmp = 0 ;
	if( deal_transducer_masg_t.internal_temperature_date <0){
		tmp = ~(deal_transducer_masg_t.internal_temperature_date-1) ;
		write_lent=dw_interior_temperature(tmp);
	}else{
		write_lent=dw_interior_temperature(deal_transducer_masg_t.internal_temperature_date);
	}
	log_i("internal temperature =%d",deal_transducer_masg_t.internal_temperature_date);
	return write_lent ;
}

int dw_show_interior_humidity(void){
	int write_lent = -1 ;
	write_lent=dw_interior_humidity(deal_transducer_masg_t.internal_humidity_date);
	log_i("internal humidity =%d",deal_transducer_masg_t.internal_humidity_date);
	return write_lent ;
}

int dw_show_illumination_transducer(uint8_t illumination_percentage){
	int illumination_grade = 0 ;
	int write_lent = -1 ;
	log_i("illumination percentage =%d",illumination_percentage);
	if( (illumination_percentage>=0)&&(illumination_percentage< 20)){
		illumination_grade = 0 ;
	}else if( (illumination_percentage>=20)&&(illumination_percentage<40)){
		illumination_grade = 1 ;
	}else if( (illumination_percentage>=40)&&(illumination_percentage<60)){
		illumination_grade = 2 ;
	}else if( (illumination_percentage>=60)&&(illumination_percentage<80)){
		illumination_grade = 3 ;
	}else{
		illumination_grade = 4 ;
	}
	write_lent=dw_illumination_transducer(illumination_grade);
	log_i("illumination grade =%d",illumination_grade);
	return write_lent ;
}

int dw_show_sleet_transducer(void){
	int write_lent = -1 ;
	write_lent=dw_sleet_transducer(deal_transducer_masg_t.sleet_state);
	log_i("external sleet =%d",deal_transducer_masg_t.sleet_state);
	return write_lent ;
}

int dw_show_switching_pages(Page_Number SWITCH_PAGE){
	int write_lent = -1 ;

 	if(MAX_PAGE_NUMBER > SWITCH_PAGE ){
 	 	write_lent=dw_switching_pages(SWITCH_PAGE); //切换页面
 	 	return write_lent ;
 	}

 	return 0 ;
}


void default_dw_show_moistureproof_close_state(void){
	animation_off_step =24 ;
}
int dw_show_moistureproof_close_state(uint16_t animation_time ,uint8_t refresh_flag){
	if(animation_off_step>=0){
		if(check_time_arrive(MOISTUREPROOF_ANIMATION_TIMER_NUMBER,animation_time)){
			clear_time_cnt(MOISTUREPROOF_ANIMATION_TIMER_NUMBER);
			if(refresh_flag)
				dw_moistureproof_state(animation_off_step);
			animation_off_step -- ;
		}
	}else{
		animation_off_step =0 ;
	}
	return animation_off_step ;
}

void default_dw_show_moistureproof_open_state(void){
	animation_on_step =0 ;
}
int dw_show_moistureproof_open_state(uint16_t animation_time,uint8_t refresh_flag){
	if(animation_on_step<=24){
		if(check_time_arrive(MOISTUREPROOF_ANIMATION_TIMER_NUMBER,animation_time)){
			clear_time_cnt(MOISTUREPROOF_ANIMATION_TIMER_NUMBER);
			if(refresh_flag)
				dw_moistureproof_state(animation_on_step);
			animation_on_step ++ ;
		}
	}else{
		animation_on_step =24 ;
	}

	return animation_on_step ;
}


static int *ip_char_string_cove(char* string ){
	int *cove_over_buff = NULL ;
	char* s1 = NULL ;
	char *s2 = NULL ;
	char* tmp = NULL ;

	if(string == NULL){
		log_e("input ip string cove error!!.");
		return 0 ;
	}
	cove_over_buff = (int *)malloc(sizeof(int) * 5 );
	if(cove_over_buff == NULL ){
		log_e("malloc error!!");
		return NULL ;
	}
	tmp = string;
	for(int i = 0 ; i<4;i++){
		s1 = strtok_r(tmp, ".",&s2);
		tmp = s2;
		sscanf(s1, "%d" , cove_over_buff+i);
	}
	return cove_over_buff;
}




