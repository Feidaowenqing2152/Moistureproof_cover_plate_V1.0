/*
 * deal_rs485_masg_task.c
 *
 *  Created on: 2023年1月5日
 *      Author: 好
 */
#define LOG_TAG    "deal_rs485_masg_task"

#include "../task/deal_rs485_masg_task.h"

#define FIFO_LEN 100

static  uint8_t deal_transducer_masg_buff[FIFO_LEN]={0};



void create_deal_rs485_masg_pthread_init(void){
	//(1)timer thread
	pthread_t deal_rs485_masg_id;
	for(uint8_t i =0 ; i<END_TRANSDUCER_NUMBER;i++){
		deal_transducer_masg_t.dev_online_state[i] = offline ;
		deal_transducer_masg_t.dev_online_ack_flag[i] = nack;
	}

	deal_transducer_fifo_t.uart_new_data_flag = 0;
	deal_transducer_fifo_t.deal_msg_lenght = 0 ;
	int deal_rs485_masg = pthread_create(&deal_rs485_masg_id,NULL,deal_rs485_msg_task,NULL);
	if(deal_rs485_masg){
		perror("deal_rs485_masg error:");
		log_e("deal_rs485_masg thread created error !.");
		exit(EXIT_FAILURE);
	}
	log_d("deal_rs485_masg_task thread created.");
}

static uint8_t deal_read_uart_annulus_fifo(void){

	if(deal_transducer_fifo_t.uart_new_data_flag){
		transducer_device_recv(deal_transducer_masg_buff,deal_transducer_fifo_t.deal_msg_lenght);

		deal_transducer_fifo_t.uart_new_data_flag = 0 ;
		 return 1 ;
	}
	 return 0 ;
}


static int deal_setting_transducer_operation(uint8_t *seeting_buffer){
	struct get_inquire_sleet_device_adderss_buad get_inquire_sleet_device_adderss_buad_t;
	struct get_setting_sleet_adderss get_setting_sleet_adderss_t;
	//struct get_device_adderss_back_msg device_adderss_back_msg_t ;
	//struct get_setting_device_adderss_back_msg setting_device_adderss_back_msg_t;

	//获取温湿度、光照设备恢复出厂设备状态
	if((deal_transducer_fifo_t.deal_msg_lenght ==8)&&(seeting_buffer[1]==TEMP_HUMIDITY_RESET_DEVICE_FUNCTION_CODE )&&(seeting_buffer[3]==0xF0)){
		transducer_decive_t.humiture_illumination_factory_ack_flag = 1 ;
		return 0 ;

	}
	//获取设备软复位状态
	else if((deal_transducer_fifo_t.deal_msg_lenght ==8)&&(seeting_buffer[1]==TEMP_HUMIDITY_RESET_DEVICE_FUNCTION_CODE )&&(seeting_buffer[3]==0xE0)){
		transducer_decive_t.humiture_illumination_soft_reset_ack_flag = 1 ;
		return 0 ;
	}
	//设置温湿度、光照设备地址成功
	else if((deal_transducer_fifo_t.deal_msg_lenght ==8)&&(seeting_buffer[1]==TEMP_HUMIDITY_RESET_DEVICE_FUNCTION_CODE )&&(seeting_buffer[3]==0x64)){
		transducer_decive_t.humiture_illumination_adderss_ack_flag =1 ;
		log_d("setting transducer adderss and buad success.");
		return 0;
	}
	//查询雨雪传感器成功
	else if((deal_transducer_fifo_t.deal_msg_lenght ==9)&&(seeting_buffer[1]==TEMP_HUMIDITY_TRANSDUCER_FUNCTION_CODE )&&(seeting_buffer[2]==0x04)){
		analysis_sleet_device_adderss_buad_back_masg( &get_inquire_sleet_device_adderss_buad_t,seeting_buffer);
		deal_transducer_masg_t.sleet_adderss= get_inquire_sleet_device_adderss_buad_t.now_slave_adderss;
		transducer_decive_t.sleet_trg_buad_flag =1 ;
		log_d(" get seleet transducer_adderss=%d. ",deal_transducer_masg_t.sleet_adderss);
		return 0 ;
	}
	//设置雨雪传感器设备地址成功
	else if((deal_transducer_fifo_t.deal_msg_lenght ==8)&&(seeting_buffer[1]==TEMP_HUMIDITY_RESET_DEVICE_FUNCTION_CODE )&&(seeting_buffer[3]==0xD0)){
		transducer_decive_t.sleet_adderss_alter_flag =1 ;
		analysis_setting_sleet_device_adderss_back_masg( &get_setting_sleet_adderss_t,seeting_buffer);
		deal_transducer_masg_t.sleet_adderss = get_setting_sleet_adderss_t.adderss;
		log_d(" setting seleet transducer_adderss=%d. ",deal_transducer_masg_t.sleet_adderss);
		return 0 ;

	}
	//设置雨雪传感器波特率成功
	else if((deal_transducer_fifo_t.deal_msg_lenght ==8)&&(seeting_buffer[1]==TEMP_HUMIDITY_RESET_DEVICE_FUNCTION_CODE )&&(seeting_buffer[3]==0xD1)){
		transducer_decive_t.sleet_buad_ack_flag =1 ;
		log_d(" recv setting seleet buad ack .");
		return 0 ;
	}
	else{
		return 1 ;
	}
	return 1 ;
}

static int deal_recv_temperature_humidity_illumination_data_operation(uint8_t *transducer_data_buffer,uint8_t deal_transducer_type){
	struct send_read_temp_cmd_back_msg modbus_back_masg_t;
	//struct get_setting_device_adderss_back_msg setting_device_adderss_back_msg_t;
	//struct write_temp_adderss_baud write_temp_adderss_baud_t;
	struct illumination_intensity_back_masg illumination_intensity_back_masg_t ;
	switch( transducer_data_buffer[1]){
	case TEMP_HUMIDITY_TRANSDUCER_FUNCTION_CODE:
		if(transducer_data_buffer[2]==0x04){ //获取温湿度数据
			if(deal_transducer_type==external_temperature_transducer ){
				modbus_package_send_read_temp_back_msg( &modbus_back_masg_t ,transducer_data_buffer);
				temperature_humidity_cove( modbus_back_masg_t.temperature_data , modbus_back_masg_t.humidity_data , \
						&deal_transducer_masg_t.external_temperature_date, &deal_transducer_masg_t.external_humidity_date);
				deal_transducer_masg_t.dev_online_ack_flag[external_temperature_transducer] = ack ;
				return 0;
			}else if(deal_transducer_type==interior_temperature_transducer ){
				modbus_package_send_read_temp_back_msg( &modbus_back_masg_t ,transducer_data_buffer);
				temperature_humidity_cove( modbus_back_masg_t.temperature_data , modbus_back_masg_t.humidity_data , \
						&deal_transducer_masg_t.internal_temperature_date, &deal_transducer_masg_t.internal_humidity_date);
				deal_transducer_masg_t.dev_online_ack_flag[interior_temperature_transducer] = ack ;
				return 0;
			}else if(deal_transducer_type==illumination_transducer ){
				modbus_package_send_read_illumination_back_msg( &illumination_intensity_back_masg_t ,transducer_data_buffer);
				illumination_intensity_cove( illumination_intensity_back_masg_t.illumination_intensity_hight ,illumination_intensity_back_masg_t.illumination_intensity_low , \
						&deal_transducer_masg_t.illumination_par_t.illumination_date,&deal_transducer_masg_t.illumination_par_t.illumination_percentage);
				deal_transducer_masg_t.dev_online_ack_flag[illumination_transducer] = ack ;
				return 0;
			}else{
				return 1;
			}
		}
		break;
//	case TEMP_HUMIDITY_RESET_DEVICE_FUNCTION_CODE : //温湿度设备地址能码
//			if( transducer_data_buffer[3] == 0x64 ){
//				analysis_temp_setting_device_adderss_back_masg( &setting_device_adderss_back_msg_t ,transducer_data_buffer);
//				if(deal_transducer_type==external_temperature_transducer ){
//					deal_transducer_masg_t.dev_adderss[external_temperature_transducer] = setting_device_adderss_back_msg_t.new_slave_adderss;
//					log_d(" external_transducer new adderss =%d. ",deal_transducer_masg_t.dev_adderss[external_temperature_transducer]);
//					return 0;
//				}else if(deal_transducer_type==interior_temperature_transducer ){
//					deal_transducer_masg_t.dev_adderss[interior_temperature_transducer] = setting_device_adderss_back_msg_t.new_slave_adderss;
//					log_d(" interior_transducer new adderss =%d. ",deal_transducer_masg_t.dev_adderss[interior_temperature_transducer]);
//					return 0;
//				}else if(deal_transducer_type==illumination_transducer ){
//					deal_transducer_masg_t.dev_adderss[illumination_transducer] = setting_device_adderss_back_msg_t.new_slave_adderss;
//					log_d(" illumination_transducer new adderss =%d. ",deal_transducer_masg_t.dev_adderss[illumination_transducer]);
//					return 0;
//				}else{
//					return 1 ;
//				}
//			}else if( transducer_data_buffer[3] == 0xE0 ){
//				if(deal_transducer_type==external_temperature_transducer ){
//					log_d(" external_transducer device reset success. ");
//					return 0;
//				}else if(deal_transducer_type==interior_temperature_transducer ){
//					log_d(" interior_transducer device reset success. ");
//					return 0;
//				}else if(deal_transducer_type==illumination_transducer ){
//					log_d(" illumination_transducer device reset success. ");
//					return 0;
//				}else {
//					return 1;
//				}
//			}else if( transducer_data_buffer[3] == 0xF0 ){
//				if(deal_transducer_type==external_temperature_transducer ){
//					log_d(" external_transducer device factory reset success. ");
//					return 0;
//				}else if(deal_transducer_type==interior_temperature_transducer ){
//					log_d(" interior_transducer device factory reset success. ");
//					return 0;
//				}else if(deal_transducer_type==illumination_transducer ){
//					log_d("illumination_transducer device factory reset success. ");
//					return 0;
//				}else {
//					return 1;
//				}
//			}else{
//				return 1;
//			}
//
//		break;
//	case SETTING_DEV_ADDERSS_BAUD_FUNCTION_CODE : //温湿度设备地址和波特率功能码
//		modbus_package_send_temp_adderss_baud_back( &write_temp_adderss_baud_t ,transducer_data_buffer);
//		if(deal_transducer_type==external_temperature_transducer ){
//			deal_transducer_masg_t.dev_adderss[external_temperature_transducer] = write_temp_adderss_baud_t.slave_adderss_date;
//			log_d(" external transducer new adderss =%d,buad=%d. ",deal_transducer_masg_t.dev_adderss[external_temperature_transducer],write_temp_adderss_baud_t.baud);
//			return 0;
//		}else if(deal_transducer_type==interior_temperature_transducer ){
//			deal_transducer_masg_t.dev_adderss[interior_temperature_transducer] = write_temp_adderss_baud_t.slave_adderss_date;
//			log_d(" interior transducer new adderss =%d,buad=%d. ",deal_transducer_masg_t.dev_adderss[interior_temperature_transducer],write_temp_adderss_baud_t.baud);
//			return 0;
//		}else if(deal_transducer_type==illumination_transducer ){
//			deal_transducer_masg_t.dev_adderss[illumination_transducer] = write_temp_adderss_baud_t.slave_adderss_date;
//			log_d(" illumination_transducer new adderss =%d,buad=%d. ",deal_transducer_masg_t.dev_adderss[illumination_transducer],write_temp_adderss_baud_t.baud);
//			return 0;
//		}else {
//			return 1;
//		}
//		break;
	default :
		return 1;
		break;
	}
	return 1;
}

static int deal_sleet_transducer_data_operation(uint8_t *sleet_buffer){
	struct get_sleet_device_state get_sleet_device_state_t;

	switch( sleet_buffer[1]){
	case TEMP_HUMIDITY_TRANSDUCER_FUNCTION_CODE:
		if((sleet_buffer[2]==0x02)&&(sleet_buffer[3]==0x00)){ //查询雨雪传感器雨雪状态返回值
			modbus_package_send_read_sleet_state_back_msg(&get_sleet_device_state_t,sleet_buffer);
			deal_transducer_masg_t.sleet_state = get_sleet_device_state_t.sleet_state;
			deal_transducer_masg_t.dev_online_ack_flag[sleet_transducer] = ack ;
			//log_d("recv sleet transducer data. ");
			return 0 ;
		}else{
			return 1 ;
		}
	break;
	case TEMP_HUMIDITY_RESET_DEVICE_FUNCTION_CODE:
		if((sleet_buffer[2]==0x07)&&(sleet_buffer[3]==0xd1)){ //设置雨雪传感器波特率成功返回值
			log_d("setting sleet buad success=%d",sleet_buffer[5]);
			return 0 ;
		}else if((sleet_buffer[2]==0x07)&&(sleet_buffer[3]==0xd0)){ //设置雨雪传感器地址成功返回值
			log_d("setting sleet adderss success=%d",sleet_buffer[5]);
			return 0 ;
		}else if((sleet_buffer[2]==0x00)&&(sleet_buffer[3]==0x33)){ //设置雨雪传感器告警复归延时成功返回值
			log_d("setting sleet Alarm return delay success=%dS",sleet_buffer[5]);
			return 0 ;
		}else{
			return 1 ;
		}
	break;
	default:
		return 1 ;
	break;
	}
	return 1 ;
}

int recv_deal_transducer_data(uint8_t *buffer){

	if(check_modbus_buffer_crc(buffer, deal_transducer_fifo_t.deal_msg_lenght)){
		log_d(" CRC ERROR ");
		return 0;
	}
	if( transducer_decive_t.dev_setting_flag ){
		deal_setting_transducer_operation(buffer);
//		transducer_decive_t.dev_setting_flag = 0 ;
	}
	else{
		switch(buffer[0]){
			case EXTERNAL_TEMP_HUMIDITY_TRANSDUCER_ADDERSS: //获取外界温湿度
				deal_recv_temperature_humidity_illumination_data_operation(buffer,external_temperature_transducer);
				break;
			case INTERIOR_TEMP_HUMIDITY_TRANSDUCER_ADDERSS: //获取内部温湿度
				deal_recv_temperature_humidity_illumination_data_operation(buffer,interior_temperature_transducer);
				break; //illumination_intensity
			case ILLUMINATION_INTENSITY_TRANSDUCER_ADDERSS: //获取光照强度
				deal_recv_temperature_humidity_illumination_data_operation(buffer,illumination_transducer);
				break;
			case SLEET_TRANSDUCER_ADDERSS:					//获取雨雪状态
				deal_sleet_transducer_data_operation(buffer);
				break;
			default :
				break;
		}
	}
	return 1;
}

void* deal_rs485_msg_task(void *arg) {
	while(1){
		if(deal_read_uart_annulus_fifo()){
			recv_deal_transducer_data(deal_transducer_masg_buff);
		}
	}
}









