/*
 * transducer_modbus.c
 *
 *  Created on: 2023年2月8日
 *      Author: 好
 */

#define LOG_TAG    "transducer_modbus"


#include "../app/transducer_modbus.h"

static Transducer_Operation_Status pfnTransducerOperationStatusFunCb = NULL;
static Transducer_Operation_Status pfnSleetTransducerOperationStatusFunCb = NULL;


static external_para_def external_para;

//修改内外温湿度传感器任意地址为1、2、3
static int setting_temperature_transducer_default_adderss(uint8_t temperature_transducer_type);
//修改雨雪传感器地址为程序指定地址
static int setting_sleet_default_adderss(void);


void transducer_modbus_init(void){
	read_saveenv_cjson_external_parameter(&external_para);
	log_d("SetMaxIlluminationDate = %d",external_para.SetMaxIlluminationDate);
	log_d("SetMinIlluminationDate = %d",external_para.SetMinIlluminationDate);
}


uint16_t CRC16(uint8_t * ptr, uint8_t len)
{
	uint16_t crc = 0xffff;
	uint8_t i;
	while(len--)
	{
		crc ^= *ptr++;
		for(i = 0; i<8; i++)
		{
			if( crc & 0x01 ){
				crc>>=1;
				crc^=0xA001;
			}
			else{
				crc>>=1;
			}
		}
	}
	return crc;
}
int check_modbus_buffer_crc(uint8_t *check_buffer,uint16_t lent){
	uint8_t *buffer_tmp = NULL ;
	uint16_t crc_tmp = 0 ;

	crc_tmp=(uint16_t)( (check_buffer[lent-1]<<8) | check_buffer[lent-2] );
	buffer_tmp = (uint8_t *)malloc(sizeof(uint16_t) * lent+1 );
	if(buffer_tmp == NULL ){
		log_w("malloc error!!.\r");
		return 0;
	}
	memset(buffer_tmp,0, sizeof(uint16_t) * lent+1 );
	for(int i = 0 ; i<(lent-2);i++){
		buffer_tmp[i]= check_buffer[i];
	}
	if( ( CRC16(buffer_tmp,lent-2)) != crc_tmp ){
		log_d("check_modbus_buffer_crc ERROR.");
		log_d("input crc=%0x , check crc=%0x.",(uint16_t)( (check_buffer[lent-2]<<8) | check_buffer[lent-1] ),CRC16(buffer_tmp,lent-2));
		free(buffer_tmp);
		return 1;
	}
	free(buffer_tmp);
	return 0;
}


//写多个寄存器命令数据打包
static void package_write_more_rge_adderss_cmd(struct write_more_rge_adderss_cmd_msg check_device_address, uint8_t *packet){
	uint16_t crc16=0;
	packet[0]= check_device_address.slave_adderss;
	packet[1]= check_device_address.func_code;
	packet[2]=(uint8_t)( (( check_device_address.reg_addr & 0xFF00 )>> 8) );
	packet[3]=(uint8_t)( check_device_address.reg_addr & 0X00FF );
	packet[4]=(uint8_t)( (( check_device_address.read_reg_counts & 0xFF00 )>> 8) );
	packet[5]=(uint8_t)( check_device_address.read_reg_counts & 0X00FF );
 	crc16 = CRC16(packet, sizeof(check_device_address)-2);
 	packet[6]=crc16 & 0x00ff;
 	packet[7]=(crc16>>8) & 0x00ff;
}
////修改设备地址、波特率参数 打包
//static void modbus_package_send_temp_adderss_baud(struct write_temp_adderss_baud write_temp_adderss_baud_t, uint8_t *packet){
//	uint16_t crc16=0;
//	packet[0]= write_temp_adderss_baud_t.slave_adderss;
//	packet[1]= write_temp_adderss_baud_t.func_code;
//
//	packet[2]=(uint8_t)( (( write_temp_adderss_baud_t.reg_addr & 0xFF00 )>> 8) );
//	packet[3]=(uint8_t)( write_temp_adderss_baud_t.reg_addr & 0X00FF );
//
//	packet[4]=(uint8_t)( (( write_temp_adderss_baud_t.reg_number & 0xFF00 )>> 8) );
//	packet[5]=(uint8_t)( write_temp_adderss_baud_t.reg_number & 0X00FF );
//
//	packet[6]=(uint8_t)( (( write_temp_adderss_baud_t.slave_adderss_date & 0xFF00 )>> 8) );
//	packet[7]=(uint8_t)( write_temp_adderss_baud_t.slave_adderss_date & 0X00FF );
//
//	packet[8]=(uint8_t)( (( write_temp_adderss_baud_t.baud & 0xFF00 )>> 8) );
//	packet[9]=(uint8_t)( write_temp_adderss_baud_t.baud & 0X00FF );
//
// 	crc16 = CRC16(packet, sizeof(write_temp_adderss_baud_t)-2);
// 	packet[10]=crc16 & 0x00ff;
// 	packet[11]=(crc16>>8) & 0x00ff;
//}



//发送获取读温湿度命
int send_get_temperature_humidity_illumination_cmd(uint8_t device_adderss,uint16_t reg_start_addr,uint16_t reg_lent){
	uint8_t write_pkt[8];
	int write_lent = 0 ;
	struct write_more_rge_adderss_cmd_msg send_read_temperature_humidity_cmd_msg_t;

	send_read_temperature_humidity_cmd_msg_t.slave_adderss = device_adderss ;
	send_read_temperature_humidity_cmd_msg_t.func_code = TEMP_HUMIDITY_TRANSDUCER_FUNCTION_CODE ;
	send_read_temperature_humidity_cmd_msg_t.reg_addr = reg_start_addr;
	send_read_temperature_humidity_cmd_msg_t.read_reg_counts = reg_lent;

	package_write_more_rge_adderss_cmd(send_read_temperature_humidity_cmd_msg_t, write_pkt);
	write_lent = transducer_device_send(write_pkt,sizeof(write_pkt));
	if(write_lent <= 0 ){
		log_e("tty write error !! ");
	}
	return write_lent ;
}

//发送获取温湿度、光照、雨雪传感器获取命令
int send_get_transducer_data_cmd( uint8_t transducer_type,uint8_t device_adderss){
	int write_lent = 0 ;
	if(transducer_type == external_temperature_transducer){
		write_lent=send_get_temperature_humidity_illumination_cmd(device_adderss,0x0000,0x0002);
	}else if(transducer_type == interior_temperature_transducer){
		write_lent=send_get_temperature_humidity_illumination_cmd(device_adderss,0x0000,0x0002);
	}else if(transducer_type == illumination_transducer){
		write_lent=send_get_temperature_humidity_illumination_cmd(device_adderss,0x0002,0x0002);
	}else if(transducer_type == sleet_transducer){
		write_lent=send_get_temperature_humidity_illumination_cmd(device_adderss,0x0000,0x0001);
	}else;
	return write_lent ;
}


//获取读温湿度数据解包
void modbus_package_send_read_temp_back_msg(struct send_read_temp_cmd_back_msg *modbus_back_masg_t, uint8_t *packet){
	modbus_back_masg_t->slave_adderss = packet[0];
	modbus_back_masg_t->func_code = packet[1];
	modbus_back_masg_t->data_size = packet[2];
	modbus_back_masg_t->temperature_data = (uint16_t)( (packet[3]<<8) | packet[4] );
	modbus_back_masg_t->humidity_data = (uint16_t)( (packet[5]<<8) | packet[6] );
	modbus_back_masg_t->crc16 = (uint16_t)( (packet[8]<<8) | packet[7] );
}
//获取光照强度数据解包
void modbus_package_send_read_illumination_back_msg(struct illumination_intensity_back_masg *illumination_intensity_back_masg_t, uint8_t *packet){
	illumination_intensity_back_masg_t->slave_adderss = packet[0];
	illumination_intensity_back_masg_t->func_code = packet[1];
	illumination_intensity_back_masg_t->data_size = packet[2];
	illumination_intensity_back_masg_t->illumination_intensity_hight = (uint16_t)( (packet[3]<<8) | packet[4] );
	illumination_intensity_back_masg_t->illumination_intensity_low = (uint16_t)( (packet[5]<<8) | packet[6] );
	illumination_intensity_back_masg_t->crc16 = (uint16_t)( (packet[8]<<8) | packet[7] );
}

//获取雨雪传感器状态数据解包
void modbus_package_send_read_sleet_state_back_msg(struct get_sleet_device_state *get_sleet_device_state_t, uint8_t *packet){
	get_sleet_device_state_t->slave_adderss = packet[0];
	get_sleet_device_state_t->func_code = packet[1];
	get_sleet_device_state_t->data_size = packet[2];
	get_sleet_device_state_t->sleet_state = (uint16_t)( (packet[3]<<8) | packet[4] );
	get_sleet_device_state_t->crc16 = (uint16_t)( (packet[6]<<8) | packet[5] );
}

////发送设置温湿度、光照传感器设备地址命令
int send_setting_temp_device_adderss_cmd(uint8_t transducer_adderss,uint8_t setting_transducer_adderss){
	uint8_t write_pkt[8];
	int write_lent = 0 ;
	struct write_more_rge_adderss_cmd_msg send_setting_device_adderss_t;
	send_setting_device_adderss_t.slave_adderss = transducer_adderss ;
	send_setting_device_adderss_t.func_code = TEMP_HUMIDITY_RESET_DEVICE_FUNCTION_CODE ;
	send_setting_device_adderss_t.reg_addr = 0x0064;
	send_setting_device_adderss_t.read_reg_counts = setting_transducer_adderss;
	package_write_more_rge_adderss_cmd(send_setting_device_adderss_t, write_pkt);
	write_lent = transducer_device_send(write_pkt,sizeof(write_pkt));
	if(write_lent <= 0 ){
		log_e("tty write error !! ");
	}
	return write_lent ;
}
//修改设备地址 解包
void analysis_temp_setting_device_adderss_back_masg(struct get_setting_device_adderss_back_msg *setting_device_adderss_back_msg, uint8_t *packet){
	setting_device_adderss_back_msg->old_slave_adderss = packet[0];
	setting_device_adderss_back_msg->func_code = packet[1];
	setting_device_adderss_back_msg->reg_addr = (uint16_t)( (packet[2]<<8) | packet[3] );
	setting_device_adderss_back_msg->new_slave_adderss = (uint16_t)( (packet[4]<<8) | packet[5] );
	setting_device_adderss_back_msg->crc16 = (uint16_t)( (packet[7]<<8) | packet[6] );
}





////修改设备地址、波特率参数
//int send_set_temp_gum_adderss_baud(uint8_t transducer_adderss,uint8_t setting_transducer_adderss,uint16_t baud){
//	uint8_t write_pkt[12];
//	int write_lent = 0 ;
//	struct write_temp_adderss_baud write_temp_adderss_baud_t;
//	write_temp_adderss_baud_t.slave_adderss = transducer_adderss;
//	deal_transducer_masg_t.dev_adderss[external_temperature_transducer] = setting_transducer_adderss ;
////	deal_transducer_masg_t.dev_adderss[external_temperature_transducer] = write_temp_adderss_baud_t.slave_adderss;
//	write_temp_adderss_baud_t.func_code = SETTING_DEV_ADDERSS_BAUD_FUNCTION_CODE;
//	write_temp_adderss_baud_t.reg_addr = 0x64;
//	write_temp_adderss_baud_t.reg_number = 0x02;
//	write_temp_adderss_baud_t.slave_adderss_date = setting_transducer_adderss;
//	write_temp_adderss_baud_t.baud = baud;
//	modbus_package_send_temp_adderss_baud( write_temp_adderss_baud_t ,write_pkt);
//	write_lent = transducer_device_send(write_pkt,sizeof(write_pkt));
//	if(write_lent <= 0 ){
//		log_e("tty write error !! ");
//	}
//	return write_lent ;
//}
////修改设备地址、波特率参数 解包
//void modbus_package_send_temp_adderss_baud_back(struct write_temp_adderss_baud *write_temp_adderss_baud_t, uint8_t *packet){
//	write_temp_adderss_baud_t->slave_adderss = packet[0];
//	write_temp_adderss_baud_t->func_code = packet[1];
//	write_temp_adderss_baud_t->reg_addr = (uint16_t)( (packet[2]<<8) | packet[3] );
//	write_temp_adderss_baud_t->reg_number = (uint16_t)( (packet[4]<<8) | packet[5] );
//	write_temp_adderss_baud_t->slave_adderss_date = (uint16_t)( (packet[6]<<8) | packet[7] );
//	write_temp_adderss_baud_t->baud = (uint16_t)( (packet[8]<<8) | packet[9] );
//	write_temp_adderss_baud_t->crc16 = (uint16_t)( (packet[11]<<8) | packet[10] );
//}



////发送查询温湿度设备地址命令
int send_inquire_device_adderss_cmd(void){
	uint8_t write_pkt[8];
	int write_lent = 0 ;
	struct write_more_rge_adderss_cmd_msg send_inquire_device_adderss_t;
	send_inquire_device_adderss_t.slave_adderss = 0xFF ;
	send_inquire_device_adderss_t.func_code = TEMP_HUMIDITY_TRANSDUCER_FUNCTION_CODE ;
	send_inquire_device_adderss_t.reg_addr = 0x0064;
	send_inquire_device_adderss_t.read_reg_counts = 0x0001;
	package_write_more_rge_adderss_cmd(send_inquire_device_adderss_t, write_pkt);
	write_lent = transducer_device_send(write_pkt,sizeof(write_pkt));
	if(write_lent <= 0 ){
		log_e("tty write error !! ");
	}
	return write_lent ;
}

//获取温湿度设备地址数据解包
void analysis_temp_device_adderss_back_masg(struct get_device_adderss_back_msg *device_adderss_masg_t, uint8_t *packet){
	device_adderss_masg_t->write_slave_adderss = packet[0];
	device_adderss_masg_t->func_code = packet[1];
	device_adderss_masg_t->data_size = packet[2];
	device_adderss_masg_t->back_slave_adderss = (uint16_t)( (packet[3]<<8) | packet[4] );
	device_adderss_masg_t->crc16 = (uint16_t)( (packet[6]<<8) | packet[5] );
}


////发送软复位温湿度设备命令
int send_reset_temp_device_cmd(void){
	uint8_t write_pkt[8];
	int write_lent = 0 ;
	struct write_more_rge_adderss_cmd_msg send_reset_temp_device;

	send_reset_temp_device.slave_adderss = 0xFF ;
	send_reset_temp_device.func_code = TEMP_HUMIDITY_RESET_DEVICE_FUNCTION_CODE ;
	send_reset_temp_device.reg_addr = 0x00e0;
	send_reset_temp_device.read_reg_counts = 0x00;
	package_write_more_rge_adderss_cmd(send_reset_temp_device, write_pkt);
	write_lent = transducer_device_send(write_pkt,sizeof(write_pkt));
	if(write_lent <= 0 ){
		log_e("tty write error !! ");
	}
	return write_lent ;
}

//温湿度设备软复位复位返回数据解包
void analysis_temp_device_reset_back_masg(struct get_device_reset_back_msg *device_reset_back_msg, uint8_t *packet){
	device_reset_back_msg->write_slave_adderss = packet[0];
	device_reset_back_msg->func_code = packet[1];
	device_reset_back_msg->reg_adder = packet[2];
	device_reset_back_msg->write_adder_date = (uint16_t)( (packet[3]<<8) | packet[4] );
	device_reset_back_msg->crc16 = (uint16_t)( (packet[6]<<8) | packet[5] );
}

////发送恢复出厂设置温湿度设备命令
int send_factory_reset_temp_device_cmd(void){
	uint8_t write_pkt[8];
	int write_lent = 0 ;
	struct write_more_rge_adderss_cmd_msg send_factory_reset_temp_device;

	send_factory_reset_temp_device.slave_adderss = 0xFF ;
	send_factory_reset_temp_device.func_code = TEMP_HUMIDITY_RESET_DEVICE_FUNCTION_CODE ;
	send_factory_reset_temp_device.reg_addr = 0x00F0;
	send_factory_reset_temp_device.read_reg_counts = 0x00;
	package_write_more_rge_adderss_cmd(send_factory_reset_temp_device, write_pkt);
	write_lent = transducer_device_send(write_pkt,sizeof(write_pkt));
	if(write_lent <= 0 ){
		log_e("tty write error !! ");
	}
	return write_lent ;
}

//温湿度设备恢复出厂设置返回数据解包
void analysis_factory_reset_back_masg(struct get_device_reset_back_msg *device_factory_reset_back_msg, uint8_t *packet){
	device_factory_reset_back_msg->write_slave_adderss = packet[0];
	device_factory_reset_back_msg->func_code = packet[1];
	device_factory_reset_back_msg->reg_adder = packet[2];
	device_factory_reset_back_msg->write_adder_date = (uint16_t)( (packet[3]<<8) | packet[4] );
	device_factory_reset_back_msg->crc16 = (uint16_t)( (packet[6]<<8) | packet[5] );
}





//修改内外温湿度传感器任意地址为1、2、3
static int setting_temperature_transducer_default_adderss(uint8_t temperature_transducer_type){
#define HUMITURE_ILLUMINATION_BUAD_MAX_NUMBER 7
	const int humiture_illumination_uart_scan_buad[HUMITURE_ILLUMINATION_BUAD_MAX_NUMBER]={1200,2400,4800,9600,19200,38400,57600};
	int recv_timout = 200 ;
	transducer_decive_t.dev_setting_flag = 1 ;		//设置状态标准位置位
	pfnTransducerOperationStatusFunCb(1);           //等待
	//2、记录接收返回回来的地址
	if(temperature_transducer_type== external_temperature_transducer )
		transducer_decive_t.dev_adderss_alter_flag = 1 ;   //外部温湿度
	else if( temperature_transducer_type == interior_temperature_transducer)
		transducer_decive_t.dev_adderss_alter_flag = 2 ;   //内部温湿度
	else
		transducer_decive_t.dev_adderss_alter_flag = 3 ;	  //光照强度

	//3、使用不同波特率查询温湿度当前设备地址
	for(uint8_t k=0;k<HUMITURE_ILLUMINATION_BUAD_MAX_NUMBER;k++){
		transducer_setting_device(humiture_illumination_uart_scan_buad[k]);	//设置发送系统波特率
		for(uint8_t i = 0 ; i<3;i++){
			send_factory_reset_temp_device_cmd();								//发送设备恢复出厂设置命令
			do{
				milliseconds_sleep(5);
			}while((!transducer_decive_t.humiture_illumination_factory_ack_flag)&&( recv_timout--));
			if(transducer_decive_t.humiture_illumination_factory_ack_flag){
				log_d("wait transducer factory ack,response buad is %d ",humiture_illumination_uart_scan_buad[k]);
				break ;
			}else{
				if(recv_timout<=0){
					recv_timout = 200 ;
					log_d("wait transducer factory ack timout ,timout counts=%d.fail response buad is %d",i,humiture_illumination_uart_scan_buad[k]);
				}
			}
		}
		if( transducer_decive_t.humiture_illumination_factory_ack_flag ){
			milliseconds_sleep(500);
			recv_timout = 200 ;
			for(uint8_t i = 0 ; i<3;i++){
				send_reset_temp_device_cmd();									//发送设备软复位命令
				do{
					milliseconds_sleep(5);
				}while((!transducer_decive_t.humiture_illumination_soft_reset_ack_flag)&&( recv_timout--));
				if(transducer_decive_t.humiture_illumination_soft_reset_ack_flag){
					log_d("response transducer soft reset ack. ");
					break ;
				}else{
					if(recv_timout<=0){
						recv_timout = 200 ;
						log_d("wait transducer soft reset ack timout ,counts=%d",i);
					}
				}
			}
			if(transducer_decive_t.humiture_illumination_soft_reset_ack_flag){
				seconds_sleep(3);
				recv_timout = 200 ;
				for(uint8_t i = 0 ; i<3;i++){
					switch( temperature_transducer_type ){
					case 0 :
						send_setting_temp_device_adderss_cmd(0x0001 ,EXTERNAL_TEMP_HUMIDITY_TRANSDUCER_ADDERSS );
						log_d("send setting external humitrue transducer default_adderss cmd.  ");
						break ;
					case 1 :
						send_setting_temp_device_adderss_cmd(0x0001 , INTERIOR_TEMP_HUMIDITY_TRANSDUCER_ADDERSS  );
						log_d("send setting internal humitrue transducer default_adderss cmd.  ");
						break ;
					case 2 :
						send_setting_temp_device_adderss_cmd(0x0001 ,ILLUMINATION_INTENSITY_TRANSDUCER_ADDERSS );
						log_d("send setting illumination transducer default_adderss cmd.  ");
						break ;
					default:
						break ;
					}
					do{
						milliseconds_sleep(5);
					}while((!transducer_decive_t.humiture_illumination_adderss_ack_flag)&&( recv_timout--));
					if(transducer_decive_t.humiture_illumination_adderss_ack_flag){
						log_d(" response setting transducer  adderss ack. ");
						goto _setting_addr_success_jump;
					}else{
						if(recv_timout<=0){
							recv_timout = 200 ;
							log_d("wait setting transducer  adderss ack timout ,counts=%d",i);
						}
					}
				}

			}
		}
	}
_setting_addr_success_jump:
	transducer_setting_device(9600);
	milliseconds_sleep(100);
	transducer_decive_t.dev_setting_flag = 0 ;
	if(transducer_decive_t.humiture_illumination_factory_ack_flag && transducer_decive_t.humiture_illumination_soft_reset_ack_flag && \
			transducer_decive_t.humiture_illumination_adderss_ack_flag ){
		transducer_decive_t.humiture_illumination_factory_ack_flag = 0  ;
		transducer_decive_t.humiture_illumination_soft_reset_ack_flag = 0 ;
		transducer_decive_t.humiture_illumination_adderss_ack_flag = 0 ;
		pfnTransducerOperationStatusFunCb(2);           //成功
		log_d("setting setting transducer adderss success ");
		return 1 ;
	}else{
		transducer_decive_t.humiture_illumination_factory_ack_flag = 0  ;
		transducer_decive_t.humiture_illumination_soft_reset_ack_flag = 0 ;
		transducer_decive_t.humiture_illumination_adderss_ack_flag = 0 ;
		pfnTransducerOperationStatusFunCb(3);           //失败
		log_e("setting setting transducer adderss error ");
		return 0 ;
	}
}


////发送查询雨雪传感器设备地址和波特率
int send_inquire_sleet_device_adderss_buad(int uart_buad){
	uint8_t write_pkt[8];
	int write_lent = 0 ;
	struct write_more_rge_adderss_cmd_msg send_inquire_device_adderss_t;
	send_inquire_device_adderss_t.slave_adderss = 0xFF ;
	send_inquire_device_adderss_t.func_code = TEMP_HUMIDITY_TRANSDUCER_FUNCTION_CODE ;
	send_inquire_device_adderss_t.reg_addr = 0x07D0;
	send_inquire_device_adderss_t.read_reg_counts = 0x0002;
	package_write_more_rge_adderss_cmd(send_inquire_device_adderss_t, write_pkt);
	transducer_setting_device(uart_buad);
	write_lent = transducer_device_send(write_pkt,sizeof(write_pkt));
	if(write_lent <= 0 ){
		log_e("tty write error !! ");
	}
	return write_lent ;
}
//查询雨雪传感器波特率和地址返回数据解包
void analysis_sleet_device_adderss_buad_back_masg(struct get_inquire_sleet_device_adderss_buad *sleet_device_adderss_buad, uint8_t *packet){
	sleet_device_adderss_buad->slave_adderss = packet[0];
	sleet_device_adderss_buad->func_code = packet[1];
	sleet_device_adderss_buad->reg_cnts = packet[2];
	sleet_device_adderss_buad->now_slave_adderss = (uint16_t)( (packet[3]<<8) | packet[4] );
	sleet_device_adderss_buad->now_slave_buad = (uint16_t)( (packet[5]<<8) | packet[6] );
	sleet_device_adderss_buad->crc16 = (uint16_t)( (packet[8]<<8) | packet[7] );
}


//发送设置雨雪传感器设备地址码
int send_setting_sleet_device_adderss_cmd(uint8_t transducer_adderss,uint8_t setting_transducer_adderss){
	uint8_t write_pkt[8];
	int write_lent = 0 ;
	struct write_more_rge_adderss_cmd_msg send_setting_sleet_device_adderss_t;

	send_setting_sleet_device_adderss_t.slave_adderss = transducer_adderss ;
	send_setting_sleet_device_adderss_t.func_code = TEMP_HUMIDITY_RESET_DEVICE_FUNCTION_CODE ;
	send_setting_sleet_device_adderss_t.reg_addr = 0x07D0;
	send_setting_sleet_device_adderss_t.read_reg_counts = setting_transducer_adderss;
	package_write_more_rge_adderss_cmd(send_setting_sleet_device_adderss_t, write_pkt);
	write_lent = transducer_device_send(write_pkt,sizeof(write_pkt));
	if(write_lent <= 0 ){
		log_e("tty write error !! ");
	}
	return write_lent ;
}

//设置雨雪传感器地址码返回数据解包
void analysis_setting_sleet_device_adderss_back_masg(struct get_setting_sleet_adderss *setting_sleet_adderss, uint8_t *packet){
	setting_sleet_adderss->slave_adderss = packet[0];
	setting_sleet_adderss->func_code = packet[1];
	setting_sleet_adderss->adderss_reg = (uint16_t)( (packet[2]<<8) | packet[3] );
	setting_sleet_adderss->adderss = (uint16_t)( (packet[4]<<8) | packet[5] );
	setting_sleet_adderss->crc16 = (uint16_t)( (packet[7]<<8) | packet[6] );
}


//发送设置雨雪传感器波特率
int send_setting_sleet_device_buad_cmd(uint8_t device_adderss,uint16_t set_buad){
	uint8_t write_pkt[8];
	int write_lent = 0 ;
	struct write_more_rge_adderss_cmd_msg send_write_sleet_set_buad_cmd_msg_t;

	send_write_sleet_set_buad_cmd_msg_t.slave_adderss = device_adderss ;
	send_write_sleet_set_buad_cmd_msg_t.func_code = TEMP_HUMIDITY_RESET_DEVICE_FUNCTION_CODE ;
	send_write_sleet_set_buad_cmd_msg_t.reg_addr = 0x07D1;
	send_write_sleet_set_buad_cmd_msg_t.read_reg_counts = set_buad;

	package_write_more_rge_adderss_cmd(send_write_sleet_set_buad_cmd_msg_t, write_pkt);
	write_lent = transducer_device_send(write_pkt,sizeof(write_pkt));
	if(write_lent <= 0 ){
		log_e("tty write error !! ");
	}
	return write_lent ;
}

//设置雨雪传感器波特率返回数据解包
void analysis_setting_sleet_device_buad_back_masg(struct get_setting_sleet_buad *sleet_device_setting_buad, uint8_t *packet){
	sleet_device_setting_buad->slave_adderss = packet[0];
	sleet_device_setting_buad->func_code = packet[1];
	sleet_device_setting_buad->buad_reg = (uint16_t)( (packet[2]<<8) | packet[3] );
	sleet_device_setting_buad->buad = (uint16_t)( (packet[4]<<8) | packet[5] );
	sleet_device_setting_buad->crc16 = (uint16_t)( (packet[7]<<8) | packet[6] );
}

//修改雨雪传感器地址为程序指定地址
static int setting_sleet_default_adderss(void){
#define SLEET_BUAD_MAX_NUMBER 3
	const int sleet_uart_scan_buad[SLEET_BUAD_MAX_NUMBER]={2400,4800,9600};
	int recv_timout = 200 ;
	transducer_decive_t.dev_setting_flag = 1 ;
	pfnSleetTransducerOperationStatusFunCb(1);
	//1、使用不同波特率查询雨雪传感器的设备地址和当前波特率
	for(uint8_t k=0;k<SLEET_BUAD_MAX_NUMBER;k++){
		for(uint8_t i = 0 ; i < 3;i++){
			send_inquire_sleet_device_adderss_buad(sleet_uart_scan_buad[k]);
			do{
				milliseconds_sleep(5);
			}while((!transducer_decive_t.sleet_trg_buad_flag)&&( recv_timout--));
			if( transducer_decive_t.sleet_trg_buad_flag ){
				log_d("response sleet check buad and addr ack. ");
				break;
			}else{
				if(recv_timout<=0){
					recv_timout = 200 ;
					log_d("wait sleet  buad and addr ack timout!,timout cnt=%d,buad=%d,",i,sleet_uart_scan_buad[k]);
				}
			}
		}
		if( transducer_decive_t.sleet_trg_buad_flag ){
			milliseconds_sleep(500);
			recv_timout = 200 ;
			for(uint8_t i = 0 ; i < 3;i++){
				send_setting_sleet_device_adderss_cmd(deal_transducer_masg_t.sleet_adderss,SLEET_TRANSDUCER_ADDERSS);
				do{
					milliseconds_sleep(5);
				}while((!transducer_decive_t.sleet_adderss_alter_flag)&&( recv_timout--));
				if( transducer_decive_t.sleet_adderss_alter_flag ){
					log_d("setting sleet  adderss success. ");
					break;
				}else{
					if(recv_timout<=0){
						recv_timout = 200 ;
						log_d("wait setting sleet  adderss ack timout ,counts=%d",i);
					}
				}
			}
			if( transducer_decive_t.sleet_adderss_alter_flag ){
				milliseconds_sleep(500);
				recv_timout = 200 ;
				for(uint8_t i = 0 ; i < 3;i++){
					send_setting_sleet_device_buad_cmd(deal_transducer_masg_t.sleet_adderss,SLEET_BADU_9600);
					do{
						milliseconds_sleep(5);
					}while((!transducer_decive_t.sleet_buad_ack_flag)&&( recv_timout--));
					if( transducer_decive_t.sleet_buad_ack_flag ){
						log_d("setting sleet  buad success. ");
						goto _sleet_set_success_jump;
					}else{
						if(recv_timout<=0){
							recv_timout = 200 ;
							log_d("wait setting sleet buad ack timout ,counts=%d",i);
						}
					}
				}
			}

		}
	}
	_sleet_set_success_jump:
	transducer_decive_t.dev_setting_flag = 0 ;
	milliseconds_sleep(100);
	transducer_setting_device(9600);
	if(transducer_decive_t.sleet_trg_buad_flag && transducer_decive_t.sleet_adderss_alter_flag && transducer_decive_t.sleet_buad_ack_flag ){
		transducer_decive_t.sleet_trg_buad_flag = 0 ;
		transducer_decive_t.sleet_adderss_alter_flag = 0 ;
		transducer_decive_t.sleet_buad_ack_flag = 0 ;
		pfnSleetTransducerOperationStatusFunCb(2);
		log_d("setting sleet adderss and buad success");
		return 1 ;
	}else{
		transducer_decive_t.sleet_trg_buad_flag = 0 ;
		transducer_decive_t.sleet_adderss_alter_flag = 0 ;
		transducer_decive_t.sleet_buad_ack_flag = 0 ;
		pfnSleetTransducerOperationStatusFunCb(3);
		log_e("setting sleet adderss and buad error");
		return 0 ;
	}
}



int temperature_humidity_cove(uint16_t temperature,uint16_t humidity,int *temperature_cov,int *humidity_cov){
	int temp_tmp = 0 ;

	temp_tmp = (uint8_t)((temperature & 0x7FFF)/10) ; //去除零下和零上温度符号 去除温度小数点

	if(( temperature & 0x8000 ) ){  //负温度
		*temperature_cov =POSITIVE_CONVERT_MINUS(temp_tmp) ;  //正数转负数
		log_d("now temperature is %d",*temperature_cov);
		if( (*temperature_cov <= MIN_MEASUREMENT_TEMP) ){
			*temperature_cov = MIN_MEASUREMENT_TEMP ;
			log_d("temperature The lower limit of measurement is exceeded ");
			return 0 ;
		}
	}else{
		if( (*temperature_cov > MAX_MEASUREMENT_TEMP) ){
			*temperature_cov = MAX_MEASUREMENT_TEMP ;
			log_d("temperature The upper limit of measurement is exceeded ");
			return 0 ;
		}
		*temperature_cov = temp_tmp;
	}
	*humidity_cov = (uint8_t)(humidity/10);
	if( (*humidity_cov > MAX_MEASUREMENT_HUMID) ){
		*humidity_cov = MAX_MEASUREMENT_HUMID ;
		log_d("humidity The lower limit of measurement is exceeded ");
		return 0 ;
	}
	return 1 ;
}


int illumination_intensity_cove(uint16_t illumination_intensity_data_h,uint16_t illumination_intensity_data_l,uint32_t *illumination_date,uint8_t *illumination_percentage){
	uint32_t illumination_intensity_data = 0 ;
	illumination_intensity_data = (uint32_t)((illumination_intensity_data | illumination_intensity_data_h) << 16 );
	illumination_intensity_data = (uint32_t)( (illumination_intensity_data| illumination_intensity_data_l) );
	illumination_intensity_data = illumination_intensity_data / 1000;
	*illumination_date = illumination_intensity_data ;
	read_saveenv_cjson_external_parameter(&external_para);
	if( illumination_intensity_data >= external_para.SetMinIlluminationDate  ){
		illumination_intensity_data -=  external_para.SetMinIlluminationDate;
		if( external_para.SetMaxIlluminationDate <= external_para.SetMinIlluminationDate){
			log_e("input max and min illumination Error !!!");
			return 0 ;
		}
		*illumination_percentage = (illumination_intensity_data*100)/(external_para.SetMaxIlluminationDate - external_para.SetMinIlluminationDate);
		if(*illumination_percentage >100)
			*illumination_percentage = 100 ;
		else if(*illumination_percentage<0)
			*illumination_percentage = 0 ;
	}else{
		*illumination_percentage = 0 ;
		log_w(" Set minimum light intensity, does not adapt to the current environment!!  ");
		return 0 ;
	}
	return 1 ;
}





//发送获取传感器数据命令
 void send_get_transducer_cmd(uint16_t ExTempHumitureTimer,uint16_t ExSleetTimer,uint16_t ExIllumTimer, uint16_t InTempHumitureTimer ){
	 static uint8_t send_transducer_step = 0 ;
	 switch( send_transducer_step){
	 case 0 :
		 if(check_time_arrive(SEND_GET_TRANSDUCER_CMD_TIMER_NUMBER,ExTempHumitureTimer)){
				send_get_transducer_data_cmd( send_transducer_step,EXTERNAL_TEMP_HUMIDITY_TRANSDUCER_ADDERSS);
				send_transducer_step = 1 ;
				clear_time_cnt(SEND_GET_TRANSDUCER_CMD_TIMER_NUMBER);
		 }
		 break ;
	 case 1 :
		 if(check_time_arrive(SEND_GET_TRANSDUCER_CMD_TIMER_NUMBER,ExSleetTimer)){
				send_get_transducer_data_cmd( send_transducer_step,INTERIOR_TEMP_HUMIDITY_TRANSDUCER_ADDERSS);
				//log_d("send get internal humiture cmd");
				send_transducer_step = 2 ;
				clear_time_cnt(SEND_GET_TRANSDUCER_CMD_TIMER_NUMBER);
		 }
		 break ;
	 case 2 :
		 if(check_time_arrive(SEND_GET_TRANSDUCER_CMD_TIMER_NUMBER,ExIllumTimer)){
				send_get_transducer_data_cmd( send_transducer_step,ILLUMINATION_INTENSITY_TRANSDUCER_ADDERSS);
				//log_d("send get illumination cmd");
				send_transducer_step = 3 ;
				clear_time_cnt(SEND_GET_TRANSDUCER_CMD_TIMER_NUMBER);
		 }
		 break ;
	 case 3 :
		 if(check_time_arrive(SEND_GET_TRANSDUCER_CMD_TIMER_NUMBER,InTempHumitureTimer)){
				send_get_transducer_data_cmd( send_transducer_step,SLEET_TRANSDUCER_ADDERSS);
				//log_d("send get sleet cmd");
				send_transducer_step = 0 ;
				clear_time_cnt(SEND_GET_TRANSDUCER_CMD_TIMER_NUMBER);
		 }
		 break ;
	 default:
		 break;
	 }
}


void Setting_Dev_Transducer_Reset_Addr(uint8_t Transducer_number){
	if((Transducer_number == external_temperature_transducer)||( Transducer_number == interior_temperature_transducer)||( Transducer_number == illumination_transducer) ){
		setting_temperature_transducer_default_adderss( Transducer_number );
	}else{
		 setting_sleet_default_adderss();
	}
}

void Transducer_Operation_Status_UnRegister(bool sleet_type){
	if(sleet_type){
		pfnSleetTransducerOperationStatusFunCb = NULL ;
	}else{
		pfnTransducerOperationStatusFunCb = NULL ;
	}
}

void Transducer_Operation_Status_Register(bool sleet_type,Transducer_Operation_Status pfnTransducerOperationStatusFunCb_t){
	if(pfnTransducerOperationStatusFunCb_t != NULL){
		if(sleet_type){
			pfnSleetTransducerOperationStatusFunCb = pfnTransducerOperationStatusFunCb_t ;
		}else{
			pfnTransducerOperationStatusFunCb = pfnTransducerOperationStatusFunCb_t ;
		}
	}

}


