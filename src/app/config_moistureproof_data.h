/*
 * config_moistureproof_data.h
 *
 *  Created on: 2023年1月5日
 *      Author: 好
 */

#ifndef APP_CONFIG_MOISTUREPROOF_DATA_H_
#define APP_CONFIG_MOISTUREPROOF_DATA_H_

#include "../common.h"
#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>

#define MAX_READ_CONFIG_SIZE 4096

#define MAX_INTERNAL_TEMPERATURE_COMPENSATION_DATE 	80
#define MIN_INTERNAL_TEMPERATURE_COMPENSATION_DATE 	-40
#define MAX_INTERNAL_HUMIDITY_COMPENSATION_DATE 	100
#define MIN_INTERNAL_HUMIDITY_COMPENSATION_DATE 	0
#define MAX_INTERNAL_ALARM_TEMPERATURE 				80
#define MIN_INTERNAL_ALARM_TEMPERATURE 				-40
#define MAX_INTERNAL_ALARM_HUMIDITY     			100
#define MIN_INTERNAL_ALARM_HUMIDITY     			0
#define MAX_INTERNAL_HUMITURE_SAMPLE_RATE 			20
#define MIN_INTERNAL_HUMITURE_SAMPLE_RATE 			1
#define MAX_INTERNAL_SMOKE_SAMPLE_RATE   			20
#define MIN_INTERNAL_SMOKE_SAMPLE_RATE   			1
#define MAX_INTERNAL_WATER_SAMPLE_RATE   			20
#define MIN_INTERNAL_WATER_SAMPLE_RATE   			1

typedef struct{
	char type[10];
	char ip_acquisition_type[10]; 	//IP获取类型 自动获取/静态IP
    char ip[32];       				//IP地址
    char gateway[32];				//网关
    char netmask[32];				//子网掩码
	char Host[32];             		//mqtt服务器ip
}mqtt_ip_tcp_def;

typedef struct{
	char type[10];
	int port;						//端口号
	int keep_alive ;                //mqtt链接，保活时间,默认60秒
	int sacn_change_paramter_timer; //扫描盖板所有参数变动时间间隔,秒
}mqtt_port_tcp_def;


typedef struct{
	char type[10];
    char username[128];           	//用户名
    char password[128];          	//密码
}mqtt_login_def;

typedef struct{
	char type[10];
	int  login_menuconfig_passwd ; //登录菜单密码
}other_para_def;


typedef struct{
	char type[10];
	int CumulativeRunningTime ;         			//累积运行时间
	int AutoExitSetsPageTime ;          			//自动退出设置页面时间

	int DisplayBrightnessDate ;         			//屏幕亮度值
	int AutomaticallyExtinguishTimeDate ;  			//自动熄灭屏幕时间值

	int SetIlluminationControlEnable ;				//光照强度控制使能位
	int SetSystemTimeControlEnable ;				//时间控制使能位

	int SetCloseIlluminationLX1 ;      				//设置关闭盖板光照强度LX1
	int SetOpenIlluminationLX2 ;      				//设置打开盖板光照强度LX2
	int SetCloseAMSysTimeDateS1 ;       			//设置上午盖板关闭时间S1
	int SetClosePMSysTimeDateS2 ;       			//设置下午盖板关闭时间S2
	int SetCloseHumidityDateK1 ;        			//设置湿度关闭值K1
	int SetOpeneHumidityDateK2 ;					//设置湿度打开值K2
	int SetCloseInternalTemperature ;   			//设置内部温度关闭值
	int SetCloseExternalTemperature ;   			//设置外界温度关闭值
	int SetCloseInternalTemperatureDifferenceC1 ; 	//设置关闭温差值C1
	int SetOpenInternalTemperatureDifferenceC2 ;  	//设置打开温差值C2
	int SetCloseTemperatureDelayDateT1 ;          	//设置温度延时关闭值T1
	int SetCloseIlluminationDelayDateT2 ;         	//设置光照延时关闭值T2
	int SetCloseHumidityDelayDateT3 ;             	//设置湿度延时关闭值T3

	int SetSystemClcokYearsDate ;                   //设置系统年值
	int SetSystemClcokMonthDate ;                   //设置系统月值
	int SetSystemClcokDaysDate ;                   	//设置系统日值
	int SetSystemClcokHousDate ;                   	//设置系统时值
	int SetSystemClcokMinuteDate ;                 	//设置系统分值
	int SetSystemClcokSecondDate ;                  //设置系统秒值

}system_para_def;

typedef struct{
	char type[10];
	int ExternalTemperatureCompensationDate; 	//外界温度补偿值
	int ExternalHumidityCompensationDate;   	//外界湿度补偿值
	int ExternalAlarmTemperature ;     			//外界报警温度
	int ExternalAlarmHumidity ;       			//外界报警湿度
	int ExternalHumitureSampleRate ; 			//外界温湿度采集速率
	int ExternalIlluminationCompensationDate;   //外界光照补偿值
	int SetMaxIlluminationDate ;       	 		//最大光照亮度
	int SetMinIlluminationDate ;       	 		//最小光照亮度
	int ExternalIlluminationSampleRate ; 		//外界光照采样速率
	int ExternalSleetSensitivityDate ;   		//外界雨雪灵敏度值
	int ExternalSleetHeatLowerLimitDate ;		//外界雨雪加热下限值
	int ExternalSleetHeatHightLimitDate ;		//外界雨雪加热上限值
	int ExternalSleetDelayAlarmRestDate ;		//外界雨雪报警复归值
	int ExternalSleetSampleRateDate ;    		//外界雨雪状态采样速率
}external_para_def;

typedef struct{
	char type[10];
	int InternalTemperatureCompensationDate; //内部温度补偿值
	int InternalHumidityCompensationDate;   //内部湿度补偿值
	int InternalAlarmTemperature ;		//内部报警温度
	int InternalAlarmHumidity ;		   //内部报警湿度
	int InternalHumitureSampleRate ; //内部温湿度采集速率
	int InternalSmokeSampleRate ;    //内部烟雾传感器采集速率
	int InternalWaterSampleRate ;    //内部水浸传感器采集速率
}internal_para_def;


typedef struct {
	mqtt_ip_tcp_def     mqtttcpipPoint;
	mqtt_port_tcp_def   mqttportPoint;
	mqtt_login_def   	mqttloginPoint;
	system_para_def  	systemPoint ;
	external_para_def 	externalPoint ;
	internal_para_def 	internalPoint ;
	other_para_def		otherPoint ;
}config_para_def;

//extern config_para_def config_para;

int read_config( void);
int write_config(config_para_def config_para);
int mqttip_amend_config( const char * const name ,const char * const string);
int mqttport_amend_config( const char * const name , int param);
int mqttloginPoint_amend_config( const char * const name , char * string);
int systemparaPoint_amend_config( const char * const name ,int systempara);
int externalparaPoint_amend_config( const char * const name ,int systempara);
int internalparaPoint_amend_config( const char * const name ,int systempara);
int OtherparaPoint_amend_config( const char * const name ,int systempara);
int config_init(void);

int read_saveenv_cjson_mqttip_parameter( mqtt_ip_tcp_def *mqtt_ip_parameter_t);
int read_saveenv_cjson_mqttport_parameter( mqtt_port_tcp_def *mqtt_port_parameter_t);
int read_saveenv_cjson_mqttlogin_parameter( mqtt_login_def *mqtt_login_parameter_t);
int read_saveenv_cjson_system_parameter( system_para_def *system_parameter_t);
int read_saveenv_cjson_external_parameter (external_para_def *external_parameter_t);
int read_saveenv_cjson_internal_parameter (internal_para_def *internal_parameter_t);

int read_saveenv_cjson_other_parameter( other_para_def *other_para_def_t);

#endif /* APP_CONFIG_MOISTUREPROOF_DATA_H_ */


