/*
 * transducer_modbus.h
 *
 *  Created on: 2023年2月8日
 *      Author: 好
 */

#ifndef APP_TRANSDUCER_MODBUS_H_
#define APP_TRANSDUCER_MODBUS_H_

#include "../common.h"

#define MIN_MEASUREMENT_TEMP  -40
#define MAX_MEASUREMENT_TEMP  80
#define MAX_MEASUREMENT_HUMID 100

#define TEMP_HUMIDITY_TRANSDUCER_FUNCTION_CODE   0x03    //读寄存器功能码
#define TEMP_HUMIDITY_RESET_DEVICE_FUNCTION_CODE 0x06    //写寄存器功能码
#define SETTING_DEV_ADDERSS_BAUD_FUNCTION_CODE   0x10


#define EXTERNAL_TEMP_HUMIDITY_TRANSDUCER_ADDERSS 0x01   //外部温湿度传感器设备地址
#define INTERIOR_TEMP_HUMIDITY_TRANSDUCER_ADDERSS 0x02   //内部温湿度传感器设备底座
#define ILLUMINATION_INTENSITY_TRANSDUCER_ADDERSS 0x03   //光照传感器设备地址
#define SLEET_TRANSDUCER_ADDERSS                  0x04   //雨雪传感器设备地址


#define SLEET_BADU_1200                          0x00
#define SLEET_BADU_4800                          0x01
#define SLEET_BADU_9600                          0x02
#define SLEET_BADU_19200                         0x03
#define SLEET_BADU_38400                         0x05
#define SLEET_BADU_115200                        0x06



typedef void (*Transducer_Operation_Status)(int);

typedef struct dw_set_prgam_date{

	uint32_t max_illumination_date;
	uint32_t min_illumination_date;

}dw_set_prgam_date_t;



struct write_more_rge_adderss_cmd_msg{
	uint8_t slave_adderss ;
	uint8_t func_code ;
	uint16_t reg_addr ;
	uint16_t read_reg_counts;
	uint16_t crc16;
};

//struct write_temp_adderss_baud{
//	uint8_t slave_adderss ;
//	uint8_t func_code ;
//	uint16_t reg_addr ;
//	uint16_t reg_number;
//	uint16_t slave_adderss_date ;
//	uint16_t baud;
//	uint16_t crc16;
//};


struct send_read_temp_cmd_back_msg{
	uint8_t slave_adderss ;
	uint8_t func_code ;
	uint8_t data_size ;
	uint16_t temperature_data;
	uint16_t humidity_data ;
	uint16_t crc16;
};

struct illumination_intensity_back_masg{
	uint8_t slave_adderss ;
	uint8_t func_code ;
	uint8_t data_size ;
	uint16_t illumination_intensity_hight;
	uint16_t illumination_intensity_low ;
	uint16_t crc16;
};


struct get_sleet_device_state{
	uint8_t slave_adderss ;
	uint8_t func_code ;
	uint8_t data_size ;
	uint16_t sleet_state;
	uint16_t crc16;
};

struct get_setting_device_adderss_back_msg{
	uint8_t old_slave_adderss ;
	uint8_t func_code ;
	uint16_t reg_addr ;
	uint16_t new_slave_adderss;
	uint16_t crc16;
};

struct get_device_adderss_back_msg{
	uint8_t write_slave_adderss ;
	uint8_t func_code ;
	uint8_t data_size ;
	uint16_t back_slave_adderss;
	uint16_t crc16;
};


struct get_device_reset_back_msg{
	uint8_t write_slave_adderss ;
	uint8_t func_code ;
	uint8_t reg_adder ;
	uint16_t write_adder_date;
	uint16_t crc16;
};

struct get_inquire_sleet_device_adderss_buad{
	uint8_t slave_adderss ;
	uint8_t func_code ;
	uint8_t reg_cnts ;
	uint16_t now_slave_adderss;
	uint16_t now_slave_buad ;
	uint16_t crc16;
};

struct get_setting_sleet_adderss{
	uint8_t slave_adderss ;
	uint8_t func_code ;
	uint16_t adderss_reg ;
	uint16_t adderss;
	uint16_t crc16;
};


struct get_setting_sleet_buad{
	uint8_t slave_adderss ;
	uint8_t func_code ;
	uint16_t buad_reg ;
	uint16_t buad;
	uint16_t crc16;
};


typedef struct transducer_decive{
	uint8_t dev_setting_flag ;        //传感器设置标志位
	uint8_t dev_adderss_alter_flag ;  //温湿度、光照传感器地址变动标志位

	uint8_t humiture_illumination_factory_ack_flag ; 		//温湿度、光照设备恢复出厂设置响应标志位
	uint8_t humiture_illumination_soft_reset_ack_flag ;  	//温湿度、光照设备软复位响应标志位
	uint8_t humiture_illumination_adderss_ack_flag ;         //温湿度、光照设备地址响应标志位

	uint8_t sleet_trg_buad_flag ;       //雨雪传感器波特率触发标志位
	uint8_t sleet_adderss_alter_flag ;  //雨雪传感器地址变动标志位
	uint8_t sleet_buad_ack_flag ;

}type_transducer_decive;
type_transducer_decive transducer_decive_t;
extern type_transducer_decive transducer_decive_t;

void transducer_modbus_init(void);

uint16_t CRC16(uint8_t * ptr, uint8_t len);
int check_modbus_buffer_crc(uint8_t *check_buffer,uint16_t lent);

//发送获取读温湿度命
int send_get_temperature_humidity_illumination_cmd(uint8_t device_adderss,uint16_t reg_start_addr,uint16_t reg_lent);
//发送获取温湿度、光照、雨雪传感器获取命令
int send_get_transducer_data_cmd( uint8_t transducer_type,uint8_t device_adderss);
//获取读温湿度数据解包
void modbus_package_send_read_temp_back_msg(struct send_read_temp_cmd_back_msg *modbus_back_masg_t, uint8_t *packet);
//获取光照强度数据解包
void modbus_package_send_read_illumination_back_msg(struct illumination_intensity_back_masg *illumination_intensity_back_masg_t, uint8_t *packet);
//获取雨雪传感器状态数据解包
void modbus_package_send_read_sleet_state_back_msg(struct get_sleet_device_state *get_sleet_device_state_t, uint8_t *packet);
////发送设置温湿度、光照传感器设备地址命令
int send_setting_temp_device_adderss_cmd(uint8_t transducer_adderss,uint8_t setting_transducer_adderss);
//修改设备地址 解包
void analysis_temp_setting_device_adderss_back_masg(struct get_setting_device_adderss_back_msg *setting_device_adderss_back_msg, uint8_t *packet);
//修改设备地址、波特率参数
int send_set_temp_gum_adderss_baud(uint8_t transducer_adderss,uint8_t setting_transducer_adderss,uint16_t baud);
//修改设备地址、波特率参数 解包
//void modbus_package_send_temp_adderss_baud_back(struct write_temp_adderss_baud *write_temp_adderss_baud_t, uint8_t *packet);
////发送查询温湿度设备地址命令
int send_inquire_device_adderss_cmd(void);
//获取温湿度设备地址数据解包
void analysis_temp_device_adderss_back_masg(struct get_device_adderss_back_msg *device_adderss_masg_t, uint8_t *packet);
////发送软复位温湿度设备命令
int send_reset_temp_device_cmd(void);
//温湿度设备软复位复位返回数据解包
void analysis_temp_device_reset_back_masg(struct get_device_reset_back_msg *device_reset_back_msg, uint8_t *packet);
////发送恢复出厂设置温湿度设备命令
int send_factory_reset_temp_device_cmd(void);
//温湿度设备恢复出厂设置返回数据解包
void analysis_factory_reset_back_masg(struct get_device_reset_back_msg *device_factory_reset_back_msg, uint8_t *packet);

////发送查询雨雪传感器设备地址和波特率
int send_inquire_sleet_device_adderss_buad(int uart_buad);
//查询雨雪传感器波特率和地址返回数据解包
void analysis_sleet_device_adderss_buad_back_masg(struct get_inquire_sleet_device_adderss_buad *sleet_device_adderss_buad, uint8_t *packet);
//发送设置雨雪传感器设备地址码
int send_setting_sleet_device_adderss_cmd(uint8_t transducer_adderss,uint8_t setting_transducer_adderss);
//设置雨雪传感器地址码返回数据解包
void analysis_setting_sleet_device_adderss_back_masg(struct get_setting_sleet_adderss *setting_sleet_adderss, uint8_t *packet);
//发送设置雨雪传感器波特率
int send_setting_sleet_device_buad_cmd(uint8_t device_adderss,uint16_t set_buad);
//设置雨雪传感器波特率返回数据解包
void analysis_setting_sleet_device_buad_back_masg(struct get_setting_sleet_buad *sleet_device_setting_buad, uint8_t *packet);
//修改传感器地址为程序指定地址
void Setting_Dev_Transducer_Reset_Addr(uint8_t Transducer_number);


int temperature_humidity_cove(uint16_t temperature,uint16_t humidity,int *temperature_cov,int *humidity_cov);
int illumination_intensity_cove(uint16_t illumination_intensity_data_h,uint16_t illumination_intensity_data_l,uint32_t *illumination_date,uint8_t *illumination_percentage);

//发送获取传感器数据命令
 void send_get_transducer_cmd(uint16_t ExTempHumitureTimer,uint16_t ExSleetTimer,uint16_t ExIllumTimer, uint16_t InTempHumitureTimer );

 void Transducer_Operation_Status_UnRegister(bool sleet_type);
 void Transducer_Operation_Status_Register(bool sleet_type,Transducer_Operation_Status pfnTransducerOperationStatusFunCb_t);

#endif /* APP_TRANSDUCER_MODBUS_H_ */
