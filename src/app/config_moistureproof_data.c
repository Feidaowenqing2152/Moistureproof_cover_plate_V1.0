/*
 * config_moistureproof_data.c
 *
 *  Created on: 2023年1月5日
 *      Author: 好
 *      参考：https://blog.csdn.net/u010835747/article/details/125591049
 */


#define LOG_TAG    "config_moistureproof_data"

#include "../common/cJSON.h"
#include "../app/config_moistureproof_data.h"

//#include <fcntl.h>
static int checkefileexist(char *filename);
static int read_file(char *filename, char *buff, int len);
static int write_file(char *filename, char *buff, int len);
static int jsonparse(char *buff);
static int read_config_check(char *read_buff);
static int check_configguration_file(void);
static void cJSON_amend_string_to_object(cJSON * const object, const char * const name, const char * const string);


char *nConfigFile = "/etc/MoistureCoverPlate.config";



static char read_buff[MAX_READ_CONFIG_SIZE] = {0};

static config_para_def config_para;

static config_para_def default_para = {
	.mqtttcpipPoint.type = "char" ,
	.mqtttcpipPoint.ip_acquisition_type = "static" ,  //静态IP
	.mqtttcpipPoint.ip  = "192.168.2.200",
	.mqtttcpipPoint.Host = "1.117.140.105",
	.mqtttcpipPoint.gateway  = "192.168.2.1",
	.mqtttcpipPoint.netmask  = "255.255.255.0",

	.mqttportPoint.type = "short" ,
	.mqttportPoint.port  = 1883,
	.mqttportPoint.keep_alive = 60 ,
	.mqttportPoint.sacn_change_paramter_timer = 10 ,

	.mqttloginPoint.type = "char" ,
	.mqttloginPoint.username =  "MoistureproofCoverPlan-0001" ,
	.mqttloginPoint.password =  "12345678" ,

	.systemPoint.type= "int" ,
	.systemPoint.CumulativeRunningTime = 0 ,
	.systemPoint.AutoExitSetsPageTime = 30,

	.systemPoint.DisplayBrightnessDate = 100 ,
	.systemPoint.AutomaticallyExtinguishTimeDate = 30 ,

	.systemPoint.SetIlluminationControlEnable =1 ,
	.systemPoint.SetSystemTimeControlEnable =1 ,

	.systemPoint.SetCloseIlluminationLX1 = 5 ,
	.systemPoint.SetOpenIlluminationLX2 = 15 ,
	.systemPoint.SetCloseAMSysTimeDateS1 = 8 ,
	.systemPoint.SetClosePMSysTimeDateS2 = 17 ,
	.systemPoint.SetCloseHumidityDateK1 = 20 ,
	.systemPoint.SetOpeneHumidityDateK2 = 60 ,
	.systemPoint.SetCloseInternalTemperature = 25 ,
	.systemPoint.SetCloseExternalTemperature = 5 ,
	.systemPoint.SetCloseInternalTemperatureDifferenceC1 = 2 ,
	.systemPoint.SetOpenInternalTemperatureDifferenceC2 = 5 ,
	.systemPoint.SetCloseTemperatureDelayDateT1 = 10 ,
	.systemPoint.SetCloseIlluminationDelayDateT2 = 10 ,
	.systemPoint.SetCloseHumidityDelayDateT3 = 10 ,

	.externalPoint.type= "int" ,
	.externalPoint.ExternalTemperatureCompensationDate = -2 ,
	.externalPoint.ExternalHumidityCompensationDate = -1 ,
	.externalPoint.ExternalAlarmTemperature = 60 ,
	.externalPoint.ExternalAlarmHumidity = 90 ,
	.externalPoint.ExternalHumitureSampleRate = 1 ,
	.externalPoint.ExternalIlluminationCompensationDate = 0 ,
	.externalPoint.SetMaxIlluminationDate = 1000 ,
	.externalPoint.SetMinIlluminationDate = 0 ,
	.externalPoint.ExternalIlluminationSampleRate = 1 ,
	.externalPoint.ExternalSleetSensitivityDate = 800 ,
	.externalPoint.ExternalSleetHeatLowerLimitDate = 15 ,
	.externalPoint.ExternalSleetHeatHightLimitDate = 25 ,
	.externalPoint.ExternalSleetDelayAlarmRestDate = 1 ,
	.externalPoint.ExternalSleetSampleRateDate = 1 ,

	.internalPoint.type= "int" ,
	.internalPoint.InternalTemperatureCompensationDate = 0 ,
	.internalPoint.InternalHumidityCompensationDate = 0 ,
	.internalPoint.InternalAlarmTemperature = 40 ,
	.internalPoint.InternalAlarmHumidity = 80 ,
	.internalPoint.InternalHumitureSampleRate =1 ,
	.internalPoint.InternalSmokeSampleRate =1 ,
	.internalPoint.InternalWaterSampleRate =1 ,

	.otherPoint.type= "int" ,
	.otherPoint.login_menuconfig_passwd = 9999,

};



static int checkefileexist(char *filename)
{
    if((access(filename, F_OK)) == -1)
    {
        log_w("%s file not exist %s line:%d", filename, __FILE__, __LINE__);
        return (-1);
    }
    return 0;
}


static int read_file(char *filename, char *buff, int len)
{
	FILE *fp;
	int ret = 0;

	fp = fopen(filename, "r");
	if(fp == NULL){
		log_w("open file %s faild ", filename);
		return (-1);
	}

	ret = fread(buff, 1, len, fp);

	fclose(fp);

	return ret;
}

static int write_file(char *filename, char *buff, int len)
{
	FILE *fp;
	int ret;

	fp = fopen(filename, "w");
	if(fp == NULL){
		log_w("open file %s faild",filename);
		return 0;
	}

	ret = fwrite(buff, 1, len, fp);
	if(ret != len){
		log_w("write file %s faild",filename);
	}
	fclose(fp);
	return ret;
}


static int jsonparse(char *buff){
	#define ITEM_NUMBER 7
	static 	const char* json_item[ITEM_NUMBER]={
	"mqttip","mqttport","mqttloginPoint","systemparaPoint","externalparaPoint","internalparaPoint","OtherparaPoint",
	};
	cJSON* item[ITEM_NUMBER]={NULL};
    char *str_tmp = NULL;
    int int_tmp = 0;

    cJSON *cjson = cJSON_Parse(buff);		//将JSON字符串转换成JSON结构体
	if(cjson == NULL){						//判断转换是否成功
		 log_e("Invalid argument");
        return (-1);
	}

	/* 依次根据名称提取JSON数据（键值对） */
	cJSON *mqtttcp_json = cJSON_GetObjectItem(cjson,"mqtttcpPoint");		//解析父类对象
	for(uint8_t i=0;i<ITEM_NUMBER;i++){
		if(i<2){
			item[i] = cJSON_GetObjectItem(mqtttcp_json, json_item[i]);
		}else{
			item[i] = cJSON_GetObjectItem(cjson, json_item[i]);
		}
	    if (item[i] == NULL || !cJSON_IsObject(item[i])) {
	        log_w("Failed to get %s",json_item[i]);
	        cJSON_Delete(cjson);
	        return -1;
	    }
	}
    str_tmp = cJSON_GetObjectItem(item[0], "Type")->valuestring;	//解析子类对象中的字符串
    strcpy(config_para.mqtttcpipPoint.type, str_tmp);

    str_tmp = cJSON_GetObjectItem(item[0], "IpAcquisitionType")->valuestring;	//解析子类对象中的字符串
    strcpy(config_para.mqtttcpipPoint.ip_acquisition_type, str_tmp);

    str_tmp = cJSON_GetObjectItem(item[0], "Ip")->valuestring;	//解析子类对象中的字符串
    strcpy(config_para.mqtttcpipPoint.ip, str_tmp);
    log_d("ip:%s", str_tmp);
    str_tmp = cJSON_GetObjectItem(item[0], "Host")->valuestring;	//解析子类对象中的字符串
    strcpy(config_para.mqtttcpipPoint.Host, str_tmp);
    log_d("Host:%s", str_tmp);

    str_tmp = cJSON_GetObjectItem(item[0], "Gateway")->valuestring;	//解析子类对象中的字符串
    strcpy(config_para.mqtttcpipPoint.gateway, str_tmp);
    log_d("gateway:%s", str_tmp);

    str_tmp = cJSON_GetObjectItem(item[0], "Netmask")->valuestring;	//解析子类对象中的字符串
    strcpy(config_para.mqtttcpipPoint.netmask, str_tmp);
    log_d("netmask:%s", str_tmp);

    str_tmp = cJSON_GetObjectItem(item[1], "Type")->valuestring;	//解析子类对象中的字符串
    strcpy(config_para.mqttportPoint.type, str_tmp);

    int_tmp = cJSON_GetObjectItem(item[1], "Port")->valueint;	//解析子类对象中的整数
    if(int_tmp >=9999){
    	int_tmp = 9999 ;
    }else if(int_tmp <=0){
    	int_tmp = 1883 ;
    }

    config_para.mqttportPoint.port = int_tmp ;
    log_d("netmask:%d", int_tmp);
    int_tmp = cJSON_GetObjectItem(item[1], "Keep_Alive")->valueint;	//解析子类对象中的整数
    if(int_tmp >=300){
    	int_tmp = 300 ;
    }else  if(int_tmp <=10){
    	int_tmp = 10 ;
    }
    config_para.mqttportPoint.keep_alive = int_tmp ;
    log_d("Keep_Alive:%d", int_tmp);
    int_tmp = cJSON_GetObjectItem(item[1], "Sacn_Post_Timer")->valueint;	//解析子类对象中的整数
    if(int_tmp >=3000){
    	int_tmp = 3000 ;
    }else  if(int_tmp <=5){
    	int_tmp = 5 ;
    }
    config_para.mqttportPoint.sacn_change_paramter_timer = int_tmp ;
    log_d("Sacn_Post_Timer:%d", int_tmp);

    str_tmp = cJSON_GetObjectItem(item[2], "Type")->valuestring;	//解析父类对象中的字符串
    strcpy(config_para.mqttloginPoint.type, str_tmp);

    str_tmp = cJSON_GetObjectItem(item[2], "Username")->valuestring;	//解析父类对象中的字符串
    strcpy(config_para.mqttloginPoint.username, str_tmp);
    log_d("username:%s", str_tmp);

    str_tmp = cJSON_GetObjectItem(item[2], "Password")->valuestring;	//解析父类对象中的字符串
     strcpy(config_para.mqttloginPoint.password, str_tmp);
     log_d("password:%s", str_tmp);

     str_tmp = cJSON_GetObjectItem(item[3], "Type")->valuestring;	//解析父类对象中的字符串
     strcpy(config_para.systemPoint.type, str_tmp);

     int_tmp = cJSON_GetObjectItem(item[3], "CumulativeRunningTime")->valueint;	//解析父类对象中的整数
     if(int_tmp >=9999)
    	 int_tmp = 9999 ;
     config_para.systemPoint.CumulativeRunningTime = int_tmp ;
     log_d("CumulativeRunningTime:%d", int_tmp);
     int_tmp = cJSON_GetObjectItem(item[3], "AutoExitSetsPageTime")->valueint;	//解析父类对象中的整数
     if(int_tmp >= 300)
    	 int_tmp = 300 ;
     if(int_tmp<=3)
    	 int_tmp =3 ;
     config_para.systemPoint.AutoExitSetsPageTime = int_tmp ;
     log_d("AutoExitSetsPageTime:%d", int_tmp);

     int_tmp = cJSON_GetObjectItem(item[3], "DisplayBrightnessDate")->valueint;	//解析父类对象中的整数
     if(int_tmp >= 100)
    	 int_tmp = 100 ;
     if(int_tmp<=30)
    	 int_tmp =30 ;
     config_para.systemPoint.DisplayBrightnessDate = int_tmp ;
     log_d("DisplayBrightnessDate:%d", int_tmp);
     int_tmp = cJSON_GetObjectItem(item[3], "AutomaticallyExtinguishTimeDate")->valueint;	//解析父类对象中的整数
     if(int_tmp >= 90)
    	 int_tmp = 90 ;
     if(int_tmp<=1)
    	 int_tmp =1 ;
     config_para.systemPoint.AutomaticallyExtinguishTimeDate = int_tmp ;
     log_d("AutomaticallyExtinguishTimeDate:%d", int_tmp);

     int_tmp = cJSON_GetObjectItem(item[3], "SetIlluminationControlEnable")->valueint;	//解析父类对象中的整数
     if(int_tmp >=1)
    	 int_tmp = 1 ;
     else  if(int_tmp <=0)
    	 int_tmp = 0 ;
     else;
     config_para.systemPoint.SetIlluminationControlEnable = int_tmp ;
     log_d("SetIlluminationControlEnable:%d", int_tmp);

     int_tmp = cJSON_GetObjectItem(item[3], "SetSystemTimeControlEnable")->valueint;	//解析父类对象中的整数
     if(int_tmp >=1)
    	 int_tmp = 1 ;
     else  if(int_tmp <=0)
    	 int_tmp = 0 ;
     else;
     config_para.systemPoint.SetSystemTimeControlEnable = int_tmp ;
     log_d("SetSystemTimeControlEnable:%d", int_tmp);

     int_tmp = cJSON_GetObjectItem(item[3], "SetCloseIlluminationLX1")->valueint;	//解析父类对象中的整数
     if(int_tmp >=100)
    	 int_tmp = 100 ;
     config_para.systemPoint.SetCloseIlluminationLX1 = int_tmp ;
     log_d("SetCloseIlluminationLX1:%d", int_tmp);
     int_tmp = cJSON_GetObjectItem(item[3], "SetOpenIlluminationLX2")->valueint;	//解析父类对象中的整数
     if(int_tmp >=100)
    	 int_tmp =100 ;
     config_para.systemPoint.SetOpenIlluminationLX2 = int_tmp ;
     log_d("SetOpenIlluminationLX2:%d", int_tmp);
     int_tmp = cJSON_GetObjectItem(item[3], "SetCloseAMSysTimeDateS1")->valueint;	//解析父类对象中的整数
     if(int_tmp >=12)
    	 int_tmp =12 ;
     else if(int_tmp <0)
    	 int_tmp =0 ;
     else ;
     config_para.systemPoint.SetCloseAMSysTimeDateS1 = int_tmp ;
     log_d("SetCloseAMSysTimeDateS1:%d", int_tmp);
     int_tmp = cJSON_GetObjectItem(item[3], "SetClosePMSysTimeDateS2")->valueint;	//解析父类对象中的整数
     if(int_tmp >23)
    	 int_tmp =23 ;
     else if(int_tmp < 13)
    	 int_tmp =13 ;
     else;
     config_para.systemPoint.SetClosePMSysTimeDateS2 = int_tmp ;
     log_d("SetClosePMSysTimeDateS2:%d", int_tmp);
     int_tmp = cJSON_GetObjectItem(item[3], "SetCloseHumidityDateK1")->valueint;	//解析父类对象中的整数
     if(int_tmp >=100)
    	 int_tmp =100 ;
     else if(int_tmp <=0)
    	 int_tmp =0 ;
     else ;
     config_para.systemPoint.SetCloseHumidityDateK1 = int_tmp ;
     log_d("SetCloseHumidityDateK1:%d", int_tmp);
     int_tmp = cJSON_GetObjectItem(item[3], "SetOpeneHumidityDateK2")->valueint;	//解析父类对象中的整数
     if(int_tmp >=100)
    	 int_tmp =100 ;
     else if(int_tmp <=0)
    	 int_tmp =0 ;
     else ;
     config_para.systemPoint.SetOpeneHumidityDateK2 = int_tmp ;
     log_d("SetOpeneHumidityDateK2:%d", int_tmp);
     int_tmp = cJSON_GetObjectItem(item[3], "SetCloseInternalTemperature")->valueint;	//解析父类对象中的整数
     if(int_tmp >=80)
    	 int_tmp =80 ;
     else if(int_tmp <=-40)
    	 int_tmp = -40 ;
     else;
     config_para.systemPoint.SetCloseInternalTemperature = int_tmp ;
     log_d("SetCloseInternalTemperature:%d", int_tmp);
     int_tmp = cJSON_GetObjectItem(item[3], "SetCloseExternalTemperature")->valueint;	//解析父类对象中的整数
     if(int_tmp >=80)
    	 int_tmp =80 ;
     else if(int_tmp <=-40)
    	 int_tmp = -40 ;
     else;
     config_para.systemPoint.SetCloseExternalTemperature = int_tmp ;
     log_d("SetCloseExternalTemperature:%d", int_tmp);
     int_tmp = cJSON_GetObjectItem(item[3], "SetCloseInternalTemperatureDifferenceC1")->valueint;	//解析父类对象中的整数
     if(int_tmp >=80)
    	 int_tmp =80 ;
     else if(int_tmp <=-40)
    	 int_tmp = -40 ;
     else;
     config_para.systemPoint.SetCloseInternalTemperatureDifferenceC1 = int_tmp ;
     log_d("SetCloseInternalTemperatureDifferenceC1:%d", int_tmp);
     int_tmp = cJSON_GetObjectItem(item[3], "SetOpenInternalTemperatureDifferenceC2")->valueint;	//解析父类对象中的整数
     if(int_tmp >=80)
    	 int_tmp =80 ;
     else if(int_tmp <=-40)
    	 int_tmp = -40 ;
     else;
     config_para.systemPoint.SetOpenInternalTemperatureDifferenceC2 = int_tmp ;
     log_d("SetOpenInternalTemperatureDifferenceC2:%d", int_tmp);
     int_tmp = cJSON_GetObjectItem(item[3], "SetCloseTemperatureDelayDateT1")->valueint;	///解析父类对象中的整数
     config_para.systemPoint.SetCloseTemperatureDelayDateT1 = int_tmp ;
     log_d("SetCloseTemperatureDelayDateT1:%d", int_tmp);
     int_tmp = cJSON_GetObjectItem(item[3], "SetCloseIlluminationDelayDateT2")->valueint;	//解析父类对象中的整数
     config_para.systemPoint.SetCloseIlluminationDelayDateT2 = int_tmp ;
     log_d("SetCloseIlluminationDelayDateT2:%d", int_tmp);
     int_tmp = cJSON_GetObjectItem(item[3], "SetCloseHumidityDelayDateT3")->valueint;	//解析父类对象中的整数
     config_para.systemPoint.SetCloseHumidityDelayDateT3 = int_tmp ;
     log_d("SetCloseHumidityDelayDateT3:%d", int_tmp);

     str_tmp = cJSON_GetObjectItem(item[4], "Type")->valuestring;	//解析父类对象中的字符串
     strcpy(config_para.externalPoint.type, str_tmp);

     int_tmp = cJSON_GetObjectItem(item[4], "ExternalTemperatureCompensationDate")->valueint;	//解析父类对象中的整数
     if(int_tmp >=80)
    	 int_tmp =80 ;
     else if(int_tmp <=-40)
    	 int_tmp = -40 ;
     else;
     config_para.externalPoint.ExternalTemperatureCompensationDate = int_tmp ;
     log_d("ExternalTemperatureCompensationDate:%d", int_tmp);
     int_tmp = cJSON_GetObjectItem(item[4], "ExternalHumidityCompensationDate")->valueint;	//解析父类对象中的整数
     if(int_tmp >=100)
    	 int_tmp =100 ;
     else if(int_tmp <=0)
    	 int_tmp = 0 ;
     else;
     config_para.externalPoint.ExternalHumidityCompensationDate = int_tmp ;
     log_d("ExternalHumidityCompensationDate:%d", int_tmp);
     int_tmp = cJSON_GetObjectItem(item[4], "ExternalAlarmTemperature")->valueint;	//解析父类对象中的整数
     if(int_tmp >=80)
    	 int_tmp =80 ;
     else if(int_tmp <=-40)
    	 int_tmp = -40 ;
     else;
     config_para.externalPoint.ExternalAlarmTemperature = int_tmp ;
     log_d("ExternalAlarmTemperature:%d", int_tmp);
     int_tmp = cJSON_GetObjectItem(item[4], "ExternalAlarmHumidity")->valueint;	//解析父类对象中的整数
     if(int_tmp >=100)
    	 int_tmp =100 ;
     else if(int_tmp <=0)
    	 int_tmp = 0 ;
     else;
     config_para.externalPoint.ExternalAlarmHumidity = int_tmp ;
     log_d("ExternalAlarmHumidity:%d", int_tmp);
     int_tmp = cJSON_GetObjectItem(item[4], "ExternalHumitureSampleRate")->valueint;	//解析父类对象中的整数
     if(int_tmp >=20)
    	 int_tmp =20 ;
     else if(int_tmp <=1)
    	 int_tmp = 1 ;
     else;
     config_para.externalPoint.ExternalHumitureSampleRate = int_tmp ;
     log_d("ExternalHumitureSampleRate:%d", int_tmp);
     int_tmp = cJSON_GetObjectItem(item[4], "ExternalIlluminationCompensationDate")->valueint;	//解析父类对象中的整数
     if(int_tmp >=200000)
    	 int_tmp =200000 ;
     else if(int_tmp <=0)
    	 int_tmp = 0 ;
     else;
     config_para.externalPoint.ExternalIlluminationCompensationDate = int_tmp ;
     log_d("ExternalIlluminationCompensationDate:%d", int_tmp);
     int_tmp = cJSON_GetObjectItem(item[4], "SetMaxIlluminationDate")->valueint;	//解析父类对象中的整数
     if(int_tmp >=200000)
    	 int_tmp =200000 ;
     else if(int_tmp <=0)
    	 int_tmp = 0 ;
     else;
     config_para.externalPoint.SetMaxIlluminationDate = int_tmp ;
     log_d("SetMaxIlluminationDate:%d", int_tmp);
     int_tmp = cJSON_GetObjectItem(item[4], "SetMinIlluminationDate")->valueint;	//解析父类对象中的整数
     if(int_tmp >=200000)
    	 int_tmp =200000 ;
     else if(int_tmp <=0)
    	 int_tmp = 0 ;
     else;
     config_para.externalPoint.SetMinIlluminationDate = int_tmp ;
     log_d("SetMinIlluminationDate:%d", int_tmp);
     int_tmp = cJSON_GetObjectItem(item[4], "ExternalIlluminationSampleRate")->valueint;	//解析父类对象中的整数
      if(int_tmp >=20)
     	 int_tmp =20 ;
      else if(int_tmp <=1)
     	 int_tmp = 1 ;
      else;
      config_para.externalPoint.ExternalIlluminationSampleRate = int_tmp ;
      log_d("ExternalIlluminationSampleRate:%d", int_tmp);
      int_tmp = cJSON_GetObjectItem(item[4], "ExternalSleetSensitivityDate")->valueint;	//解析父类对象中的整数
       if(int_tmp >=3500)
      	 int_tmp =3500 ;
       else if(int_tmp <=500)
      	 int_tmp = 500 ;
       else;
       config_para.externalPoint.ExternalSleetSensitivityDate = int_tmp ;
       log_d("ExternalSleetSensitivityDate:%d", int_tmp);
       int_tmp = cJSON_GetObjectItem(item[4], "ExternalSleetHeatLowerLimitDate")->valueint;	//解析父类对象中的整数
        if(int_tmp >=70)
       	 int_tmp =70 ;
        else if(int_tmp <=-30)
       	 int_tmp = -30 ;
        else;
        config_para.externalPoint.ExternalSleetHeatLowerLimitDate = int_tmp ;
        log_d("ExternalSleetHeatLowerLimitDate:%d", int_tmp);
        int_tmp = cJSON_GetObjectItem(item[4], "ExternalSleetHeatHightLimitDate")->valueint;	//解析父类对象中的整数
         if(int_tmp >=70)
        	 int_tmp =70 ;
         else if(int_tmp <=0)
        	 int_tmp = 0 ;
         else;
	  config_para.externalPoint.ExternalSleetHeatHightLimitDate = int_tmp ;
	  log_d("ExternalSleetHeatHightLimitDate:%d", int_tmp);
	  int_tmp = cJSON_GetObjectItem(item[4], "ExternalSleetDelayAlarmRestDate")->valueint;	//解析父类对象中的整数
	  if(int_tmp >=60000)
		 int_tmp =60000 ;
	  else if(int_tmp <=0)
		 int_tmp = 0 ;
	  else;
	  config_para.externalPoint.ExternalSleetDelayAlarmRestDate = int_tmp ;
	  log_d("ExternalSleetDelayAlarmRestDate:%d", int_tmp);
	  int_tmp = cJSON_GetObjectItem(item[4], "ExternalSleetSampleRateDate")->valueint;	//解析父类对象中的整数
	   if(int_tmp >=10)
		 int_tmp =10 ;
	   else if(int_tmp <=1)
		 int_tmp = 1 ;
	   else;
	   config_para.externalPoint.ExternalSleetSampleRateDate = int_tmp ;
	   log_d("ExternalSleetSampleRateDate:%d", int_tmp);

     str_tmp = cJSON_GetObjectItem(item[5], "Type")->valuestring;					//解析父类对象中的字符串
     strcpy(config_para.internalPoint.type, str_tmp);

     int_tmp = cJSON_GetObjectItem(item[5], "InternalTemperatureCompensationDate")->valueint;	//解析父类对象中的整数
     if(int_tmp >=80)
    	 int_tmp =80 ;
     else if(int_tmp <=-40)
    	 int_tmp = -40 ;
     else;
     config_para.internalPoint.InternalTemperatureCompensationDate = int_tmp ;
     log_d("InternalTemperatureCompensationDate:%d", int_tmp);
     int_tmp = cJSON_GetObjectItem(item[5], "InternalHumidityCompensationDate")->valueint;	//解析父类对象中的整数
     if(int_tmp >=100)
    	 int_tmp =100 ;
     else if(int_tmp <=0)
    	 int_tmp = 0 ;
     else;
     config_para.internalPoint.InternalHumidityCompensationDate = int_tmp ;
     log_d("InternalHumidityCompensationDate:%d", int_tmp);
     int_tmp = cJSON_GetObjectItem(item[5], "InternalAlarmTemperature")->valueint;	//解析父类对象中的整数
     if(int_tmp >=80)
    	 int_tmp =80 ;
     else if(int_tmp <=-40)
    	 int_tmp = -40 ;
     else;
     config_para.internalPoint.InternalAlarmTemperature = int_tmp ;
     log_d("InternalAlarmTemperature:%d", int_tmp);
     int_tmp = cJSON_GetObjectItem(item[5], "InternalAlarmHumidity")->valueint;	//解析父类对象中的整数
     if(int_tmp >=100)
    	 int_tmp =100 ;
     else if(int_tmp <=0)
    	 int_tmp = 0 ;
     else;
     config_para.internalPoint.InternalAlarmHumidity = int_tmp ;
     log_d("InternalAlarmHumidity:%d", int_tmp);
     int_tmp = cJSON_GetObjectItem(item[5], "InternalHumitureSampleRate")->valueint;	//解析父类对象中的整数
     if(int_tmp >=20)
    	 int_tmp =20 ;
     else if(int_tmp <=1)
    	 int_tmp =1 ;
     else;
     config_para.internalPoint.InternalHumitureSampleRate = int_tmp ;
     log_d("InternalHumitureSampleRate:%d", int_tmp);
     int_tmp = cJSON_GetObjectItem(item[5], "InternalSmokeSampleRate")->valueint;	//解析父类对象中的整数
     if(int_tmp >=20)
    	 int_tmp =20 ;
     else if(int_tmp <=1)
    	 int_tmp =1 ;
     else;
     config_para.internalPoint.InternalSmokeSampleRate = int_tmp ;
     log_d("InternalSmokeSampleRate:%d", int_tmp);
     int_tmp = cJSON_GetObjectItem(item[5], "InternalWaterSampleRate")->valueint;	//解析父类对象中的整数
     if(int_tmp >=20)
    	 int_tmp =20 ;
     else if(int_tmp <=1)
    	 int_tmp =1 ;
     else;
     config_para.internalPoint.InternalWaterSampleRate = int_tmp ;
     log_d("InternalWaterSampleRate:%d", int_tmp);

     str_tmp = cJSON_GetObjectItem(item[6], "Type")->valuestring;	//解析子类对象中的字符串
     strcpy(config_para.otherPoint.type, str_tmp);
     int_tmp = cJSON_GetObjectItem(item[6], "LoginMenuconfigPasswd")->valueint;	//解析父类对象中的整数
     if( (int_tmp >0) && (int_tmp<=9999)){
         config_para.otherPoint.login_menuconfig_passwd = int_tmp ;
     }
     log_d("LoginMenuconfigPasswd:%d", int_tmp);


     cJSON_Delete(cjson);
    return 0;
}


static int read_config_check(char *read_buff){
	int ret = 0;
    ret = checkefileexist(nConfigFile);
    if(ret != 0)
    {
    	config_para = default_para;
    }
    else
    {
        memset(read_buff, 0, MAX_READ_CONFIG_SIZE);
        ret = read_file(nConfigFile, read_buff, MAX_READ_CONFIG_SIZE);
        if(ret == -1)
        {
            log_w("read file error ");
            config_para = default_para;
            return (-1);
        }
    }
    return ret ;
}

static int check_configguration_file(void){  //判断配置文件是否存在
	int ret = -1 ;
	 ret = access(nConfigFile, F_OK | R_OK) ;
	if(ret != 0){
		config_para = default_para;
		return 1 ;
	}
	return 0 ;
}

static void cJSON_amend_string_to_object(cJSON * const object, const char * const name, const char * const string){
    cJSON *item;
    if (object == NULL || name == NULL || string == NULL){
        return;
    }

    item = cJSON_GetObjectItemCaseSensitive(object, name);
    if (item == NULL){ // item not exist
        //cJSON_AddStringToObject(object, name, string);  // just addstring
    	log_w("item not exist ");
        return;
    }
    else { // item exist
        cJSON_free(item->valuestring); // free present valuestring
        item->valuestring = strdup(string); // malloc and init new valuestring
        log_d("free present valuestring ");
    }
}



int read_config( void)
{
    int ret = 0;

    ret = checkefileexist(nConfigFile);
    if(ret == 0){
        memset(read_buff, 0, MAX_READ_CONFIG_SIZE);
        ret = read_file(nConfigFile, read_buff, MAX_READ_CONFIG_SIZE);
        if(ret == -1){
            log_w("read file error");
            return (-1);
        }else {
            ret = jsonparse(read_buff);
            return ret ;
        }
    }
    return 0;
}





//https://blog.csdn.net/Mculover666/article/details/103796256

int write_config(config_para_def config_para)
{
	cJSON *config_json = cJSON_CreateObject(); //创建根录

	cJSON *mqtttcp_json = cJSON_CreateObject(); //创建一个父类

    cJSON *mqtttip_json	=  cJSON_CreateObject();				//创建一个子类对象
    cJSON_AddStringToObject(mqtttip_json,"Type", config_para.mqtttcpipPoint.type);	//添加字符串
	cJSON_AddStringToObject(mqtttip_json,"IpAcquisitionType", config_para.mqtttcpipPoint.ip_acquisition_type);	//添加字符串
    cJSON_AddStringToObject(mqtttip_json,"Ip", config_para.mqtttcpipPoint.ip);	//添加字符串
	cJSON_AddStringToObject(mqtttip_json,"Host", config_para.mqtttcpipPoint.Host);	//添加字符串
    cJSON_AddStringToObject(mqtttip_json,"Gateway", config_para.mqtttcpipPoint.gateway);	//添加字符串
    cJSON_AddStringToObject(mqtttip_json,"Netmask", config_para.mqtttcpipPoint.netmask);	//添加字符串
	cJSON_AddItemToObject(mqtttcp_json, "mqttip", mqtttip_json);        //将子类插入到父类中
 	cJSON_AddItemToObject(config_json, "mqtttcpPoint", mqtttcp_json);   //将父类插入到根录中

 	cJSON *mqtttport_json= cJSON_CreateObject();				//创建一个子类对象
	cJSON_AddStringToObject(mqtttport_json,"Type", config_para.mqttportPoint.type);	//添加字符串
	cJSON_AddNumberToObject(mqtttport_json,"Port", config_para.mqttportPoint.port);	//添加整型数字
	cJSON_AddNumberToObject(mqtttport_json,"Keep_Alive", config_para.mqttportPoint.keep_alive);	//添加整型数字
	cJSON_AddNumberToObject(mqtttport_json,"Sacn_Post_Timer", config_para.mqttportPoint.sacn_change_paramter_timer);	//添加整型数字
	cJSON_AddItemToObject(mqtttcp_json, "mqttport", mqtttport_json);	//将子类插入到父类中
 	cJSON_AddItemToObject(config_json, "mqtttcpPoint", mqtttcp_json);	//将父类插入到根录中


    cJSON *mqttlogin_json	= cJSON_CreateObject();				//创建一个父类对象
    cJSON_AddStringToObject(mqttlogin_json,"Type", config_para.mqttloginPoint.type);	//添加字符串
	cJSON_AddStringToObject(mqttlogin_json,"Username", config_para.mqttloginPoint.username);	//添加字符串
	cJSON_AddStringToObject(mqttlogin_json,"Password", config_para.mqttloginPoint.password);	//添加字符串
 	cJSON_AddItemToObject(config_json, "mqttloginPoint", mqttlogin_json);

    cJSON *systempara_json	= cJSON_CreateObject();				//创建一个父类对象
    cJSON_AddStringToObject(systempara_json,"Type", config_para.systemPoint.type);	//添加字符串
    cJSON_AddNumberToObject(systempara_json,"CumulativeRunningTime", config_para.systemPoint.CumulativeRunningTime);	//添加整型数字
    cJSON_AddNumberToObject(systempara_json,"AutoExitSetsPageTime", config_para.systemPoint.AutoExitSetsPageTime);	//添加整型数字

    cJSON_AddNumberToObject(systempara_json,"DisplayBrightnessDate", config_para.systemPoint.DisplayBrightnessDate) ;	//添加整型数字
    cJSON_AddNumberToObject(systempara_json,"AutomaticallyExtinguishTimeDate", config_para.systemPoint.AutomaticallyExtinguishTimeDate);	//添加整型数字

    cJSON_AddNumberToObject(systempara_json,"SetIlluminationControlEnable", config_para.systemPoint.SetIlluminationControlEnable);	//添加整型数字
    cJSON_AddNumberToObject(systempara_json,"SetSystemTimeControlEnable", config_para.systemPoint.SetSystemTimeControlEnable);	//添加整型数字

    cJSON_AddNumberToObject(systempara_json,"SetCloseIlluminationLX1", config_para.systemPoint.SetCloseIlluminationLX1);	//添加整型数字
    cJSON_AddNumberToObject(systempara_json,"SetOpenIlluminationLX2", config_para.systemPoint.SetOpenIlluminationLX2);	//添加整型数字
    cJSON_AddNumberToObject(systempara_json,"SetCloseAMSysTimeDateS1", config_para.systemPoint.SetCloseAMSysTimeDateS1);	//添加整型数字
    cJSON_AddNumberToObject(systempara_json,"SetClosePMSysTimeDateS2", config_para.systemPoint.SetClosePMSysTimeDateS2);	//添加整型数字
    cJSON_AddNumberToObject(systempara_json,"SetCloseHumidityDateK1", config_para.systemPoint.SetCloseHumidityDateK1);	//添加整型数字
    cJSON_AddNumberToObject(systempara_json,"SetOpeneHumidityDateK2", config_para.systemPoint.SetOpeneHumidityDateK2);	//添加整型数字
    cJSON_AddNumberToObject(systempara_json,"SetCloseInternalTemperature", config_para.systemPoint.SetCloseInternalTemperature);	//添加整型数字
    cJSON_AddNumberToObject(systempara_json,"SetCloseExternalTemperature", config_para.systemPoint.SetCloseExternalTemperature);	//添加整型数字
    cJSON_AddNumberToObject(systempara_json,"SetCloseInternalTemperatureDifferenceC1", config_para.systemPoint.SetCloseInternalTemperatureDifferenceC1);	//添加整型数字
    cJSON_AddNumberToObject(systempara_json,"SetOpenInternalTemperatureDifferenceC2", config_para.systemPoint.SetOpenInternalTemperatureDifferenceC2);	//添加整型数字
    cJSON_AddNumberToObject(systempara_json,"SetCloseTemperatureDelayDateT1", config_para.systemPoint.SetCloseTemperatureDelayDateT1);	//添加整型数字
    cJSON_AddNumberToObject(systempara_json,"SetCloseIlluminationDelayDateT2", config_para.systemPoint.SetCloseIlluminationDelayDateT2);	//添加整型数字
    cJSON_AddNumberToObject(systempara_json,"SetCloseHumidityDelayDateT3", config_para.systemPoint.SetCloseHumidityDelayDateT3);	//添加整型数字
    cJSON_AddItemToObject(config_json, "systemparaPoint", systempara_json);

    cJSON *externalpara_json	= cJSON_CreateObject();			//创建一个父类对象
    cJSON_AddStringToObject(externalpara_json,"Type", config_para.externalPoint.type);	//添加字符串
    cJSON_AddNumberToObject(externalpara_json,"ExternalTemperatureCompensationDate", config_para.externalPoint.ExternalTemperatureCompensationDate);	//添加整型数字
    cJSON_AddNumberToObject(externalpara_json,"ExternalHumidityCompensationDate", config_para.externalPoint.ExternalHumidityCompensationDate);	//添加整型数字
    cJSON_AddNumberToObject(externalpara_json,"ExternalAlarmTemperature", config_para.externalPoint.ExternalAlarmTemperature);	//添加整型数字
    cJSON_AddNumberToObject(externalpara_json,"ExternalAlarmHumidity", config_para.externalPoint.ExternalAlarmHumidity);	//添加整型数字
    cJSON_AddNumberToObject(externalpara_json,"ExternalHumitureSampleRate", config_para.externalPoint.ExternalHumitureSampleRate);	//添加整型数字
    cJSON_AddNumberToObject(externalpara_json,"ExternalIlluminationCompensationDate", config_para.externalPoint.ExternalIlluminationCompensationDate);	//添加整型数字
    cJSON_AddNumberToObject(externalpara_json,"SetMaxIlluminationDate", config_para.externalPoint.SetMaxIlluminationDate);	//添加整型数字
    cJSON_AddNumberToObject(externalpara_json,"SetMinIlluminationDate", config_para.externalPoint.SetMinIlluminationDate);	//添加整型数字
    cJSON_AddNumberToObject(externalpara_json,"ExternalIlluminationSampleRate", config_para.externalPoint.ExternalIlluminationSampleRate);	//添加整型数字
    cJSON_AddNumberToObject(externalpara_json,"ExternalSleetSensitivityDate", config_para.externalPoint.ExternalSleetSensitivityDate);	//添加整型数字
    cJSON_AddNumberToObject(externalpara_json,"ExternalSleetHeatLowerLimitDate", config_para.externalPoint.ExternalSleetHeatLowerLimitDate);	//添加整型数字
    cJSON_AddNumberToObject(externalpara_json,"ExternalSleetHeatHightLimitDate", config_para.externalPoint.ExternalSleetHeatHightLimitDate);	//添加整型数字
    cJSON_AddNumberToObject(externalpara_json,"ExternalSleetDelayAlarmRestDate", config_para.externalPoint.ExternalSleetDelayAlarmRestDate);	//添加整型数字
    cJSON_AddNumberToObject(externalpara_json,"ExternalSleetSampleRateDate", config_para.externalPoint.ExternalSleetSampleRateDate);	//添加整型数字
    cJSON_AddItemToObject(config_json, "externalparaPoint", externalpara_json);

    cJSON *internalpara_json	= cJSON_CreateObject();				//创建一个父类对象
    cJSON_AddStringToObject(internalpara_json,"Type", config_para.internalPoint.type);	//添加字符串
    cJSON_AddNumberToObject(internalpara_json,"InternalTemperatureCompensationDate", config_para.internalPoint.InternalTemperatureCompensationDate);	//添加整型数字
    cJSON_AddNumberToObject(internalpara_json,"InternalHumidityCompensationDate", config_para.internalPoint.InternalHumidityCompensationDate);	//添加整型数字
    cJSON_AddNumberToObject(internalpara_json,"InternalAlarmTemperature", config_para.internalPoint.InternalAlarmTemperature);	//添加整型数字
    cJSON_AddNumberToObject(internalpara_json,"InternalAlarmHumidity", config_para.internalPoint.InternalAlarmHumidity);	//添加整型数字
    cJSON_AddNumberToObject(internalpara_json,"InternalHumitureSampleRate", config_para.internalPoint.InternalHumitureSampleRate);	//添加整型数字
    cJSON_AddNumberToObject(internalpara_json,"InternalSmokeSampleRate", config_para.internalPoint.InternalSmokeSampleRate);	//添加整型数字
    cJSON_AddNumberToObject(internalpara_json,"InternalWaterSampleRate", config_para.internalPoint.InternalWaterSampleRate);	//添加整型数字
    cJSON_AddItemToObject(config_json, "internalparaPoint", internalpara_json);

    cJSON *otherpara_json	= cJSON_CreateObject();				//创建一个父类对象
    cJSON_AddStringToObject(otherpara_json,"Type", config_para.otherPoint.type);	//添加字符串
    cJSON_AddNumberToObject(otherpara_json,"LoginMenuconfigPasswd", config_para.otherPoint.login_menuconfig_passwd);	//添加整型数字
    cJSON_AddItemToObject(config_json, "OtherparaPoint", otherpara_json);

    char *json_data = cJSON_Print(config_json);	//JSON数据结构转换为JSON字符串

    write_file(nConfigFile, json_data, strlen(json_data));
	cJSON_Delete(config_json);//清除结构体
	cJSON_free(json_data);
    return 0;
}




int mqttip_amend_config( const char * const name ,const char * const string){
	if((name ==NULL) || (string== NULL )){
		return 1 ;
	}
	read_config_check(read_buff);
    //解析我们读到的Json字符串
    cJSON* config_json = cJSON_Parse(read_buff);
    if( config_json == NULL ){
        	cJSON_Delete(config_json);//清除结构体
        	return 1 ;
        }
	 //定位到mqttloginPoint的节点，并修改其值
    cJSON* mqtttcpPoint = cJSON_GetObjectItem(config_json,"mqtttcpPoint");
    if( mqtttcpPoint == NULL ){
    	cJSON_Delete(config_json);//清除结构体
    	return 1 ;
    }
    cJSON* mqttip = cJSON_GetObjectItem(mqtttcpPoint,"mqttip");
    if( mqttip == NULL){
    	cJSON_Delete(config_json);//清除结构体
    }else{
    	cJSON_amend_string_to_object(mqttip,name,string);
    }

    if(strcmp(name,"IpAcquisitionType") == 0){
    	strcpy(config_para.mqtttcpipPoint.ip_acquisition_type, string);
    }else if(strcmp(name,"Ip") == 0){
    	 if(strcmp("000.000.000.000",string) == 0){
    		 cJSON_Delete(config_json);//清除结构体
    		 return 1 ;
    	 }
    	strcpy(config_para.mqtttcpipPoint.ip, string);
    }else if(strcmp(name,"Host") == 0){
		 if(strcmp("000.000.000.000",string) == 0){
			 cJSON_Delete(config_json);//清除结构体
			 return 1 ;
		 }
    	strcpy(config_para.mqtttcpipPoint.Host, string);
    	log_d("change Host:%s",config_para.mqtttcpipPoint.Host);
    }else if(strcmp(name,"Gateway") == 0){
		 if(strcmp("000.000.000.000",string) == 0){
			 cJSON_Delete(config_json);//清除结构体
			 return 1 ;
		 }
    	strcpy(config_para.mqtttcpipPoint.gateway, string);
    }else if(strcmp(name,"Netmask") == 0){
		 if(strcmp("000.000.000.000",string) == 0){
			 cJSON_Delete(config_json);//清除结构体
			 return 1 ;
		 }
    	strcpy(config_para.mqtttcpipPoint.netmask, string);
    }else{
    	cJSON_Delete(config_json);//清除结构体
    	return 1 ;
    }
    char *json_data = cJSON_Print(config_json);	//JSON数据结构转换为JSON字符串
    write_file(nConfigFile, json_data, strlen(json_data));
	cJSON_Delete(config_json);//清除结构体
	cJSON_free(json_data);
	return 0 ;
}



int mqttport_amend_config( const char * const name , int param){
	int tmp = 0 ;
	if(name ==NULL){
		return 1 ;
	}
	tmp = param ;
    if(strcmp(name,"Port") == 0){
    	if( (tmp >0)&&(tmp <=9999)){
    		config_para.mqttportPoint.port = tmp ;
    	}else{
    		return 1 ;
    	}
    }else if(strcmp(name,"Keep_Alive") == 0){
    	if( (tmp >5)&&(tmp <=3000)){
    		config_para.mqttportPoint.keep_alive = tmp ;
    	}else{
    		return 1 ;
    	}
    }else if(strcmp(name,"Sacn_Post_Timer") == 0){
    	if( (tmp >0)&&(tmp <=300)){
    		config_para.mqttportPoint.sacn_change_paramter_timer = tmp ;
    	}else{
        	return 1 ;
        }
    }else{
    	return 1 ;
    }
	read_config_check(read_buff);
    //解析我们读到的Json字符串
    cJSON* config_json = cJSON_Parse(read_buff);
    if( config_json == NULL ){
        	cJSON_Delete(config_json);//清除结构体
        	return 1 ;
        }
	 //定位到mqttloginPoint的节点，并修改其值
    cJSON* mqtttcpPoint = cJSON_GetObjectItem(config_json,"mqtttcpPoint");
    if( mqtttcpPoint == NULL ){
    	cJSON_Delete(config_json);//清除结构体
    	return 1 ;
    }
    cJSON* mqttport = cJSON_GetObjectItem(mqtttcpPoint,"mqttport");
    if( mqttport == NULL ){
    	cJSON_Delete(config_json);//清除结构体
    	return 1 ;
    }
    cJSON* paramdate = cJSON_GetObjectItem(mqttport,name);
    if( paramdate == NULL ){
    	cJSON_Delete(config_json);//清除结构体
    	return 1 ;
    }else{
    	cJSON_SetNumberValue(paramdate,tmp);
    }
    char *json_data = cJSON_Print(config_json);	//JSON数据结构转换为JSON字符串
    write_file(nConfigFile, json_data, strlen(json_data));
	cJSON_Delete(config_json);//清除结构体
	cJSON_free(json_data);
	return 0 ;
}


int mqttloginPoint_amend_config( const char * const name , char * string){
	if( (name == NULL) || (string == NULL) ){
		return 1 ;
	}
	 if(strcmp("00000000",string) == 0){
		 return 1 ;
	 }
    if(strcmp(name,"Type") == 0){
    	strcpy(config_para.mqttloginPoint.type, string);
    }else if(strcmp(name,"Username") == 0){
    	strcpy(config_para.mqttloginPoint.username,string);
    }else if(strcmp(name,"Password") == 0){
    	strcpy(config_para.mqttloginPoint.password, string);

    }else{
    	return 1 ;
    }

	read_config_check(read_buff);
    //解析我们读到的Json字符串
    cJSON* config_json = cJSON_Parse(read_buff);
    if( config_json == NULL ){
        	cJSON_Delete(config_json);//清除结构体
        	return 1 ;
        }
	 //定位到mqttloginPoint的节点，并修改其值
    cJSON* mqttloginPoint = cJSON_GetObjectItem(config_json,"mqttloginPoint");
    if( mqttloginPoint == NULL){
    	cJSON_Delete(config_json);//清除结构体
    	return 1 ;
    }else{
    	cJSON_amend_string_to_object(mqttloginPoint,name,string);
    }
    char *json_data = cJSON_Print(config_json);	//JSON数据结构转换为JSON字符串
    write_file(nConfigFile, json_data, strlen(json_data));
	cJSON_Delete(config_json);//清除结构体
	cJSON_free(json_data);
	return 0 ;
}



int systemparaPoint_amend_config( const char * const name ,int systempara){
	if( name == NULL ){
		return 1 ;
	}
	int tmp = 0 ;
	tmp = systempara ;
    if(strcmp(name,"CumulativeRunningTime") == 0){
    	if( tmp >=0){
    		config_para.systemPoint.CumulativeRunningTime = tmp ;
    	}else{
    		return 1 ;
    	}
    }else if(strcmp(name,"AutoExitSetsPageTime") == 0){
    	if( (tmp>=3)&&(tmp<=300)){
    		config_para.systemPoint.AutoExitSetsPageTime = tmp ;
    	}else{
    		return 1 ;
    	}
    }else if(strcmp(name,"DisplayBrightnessDate") == 0){
    	if( (tmp>=30)&&(tmp<=100)){
    		config_para.systemPoint.DisplayBrightnessDate = tmp ;
    	}else{
    		return 1 ;
    	}
    }else if(strcmp(name,"AutomaticallyExtinguishTimeDate") == 0){
    	if( (tmp>=1)&&(tmp<=90)){
    		config_para.systemPoint.AutomaticallyExtinguishTimeDate = tmp ;
    	}else{
    		return 1 ;
    	}
    }else if(strcmp(name,"SetIlluminationControlEnable") == 0){
    	if( (tmp>=0)&&(tmp<=1)){
    		config_para.systemPoint.SetIlluminationControlEnable = tmp ;
    	}else{
    		return 1 ;
    	}
    }else if(strcmp(name,"SetSystemTimeControlEnable") == 0){
    	if( (tmp>=0)&&(tmp<=1)){
    		config_para.systemPoint.SetSystemTimeControlEnable = tmp ;
    	}else{
    		return 1 ;
    	}
    }else if(strcmp(name,"SetCloseIlluminationLX1") == 0){
    	if( (tmp>=0)&&(tmp<=100)){
    		if(tmp< config_para.systemPoint.SetOpenIlluminationLX2 ){
    			config_para.systemPoint.SetCloseIlluminationLX1 = tmp ;
    		}else{
        		return 1 ;
        	}
    	}else{
    		return 1 ;
    	}
    }else if(strcmp(name,"SetOpenIlluminationLX2") == 0){
    	if( (tmp>=0)&&(tmp<=100)){
    		if(tmp> config_para.systemPoint.SetCloseIlluminationLX1 ){
    			config_para.systemPoint.SetOpenIlluminationLX2 = tmp ;
    		}else{
        		return 1 ;
        	}
    	}else{
    		return 1 ;
    	}
    }else if(strcmp(name,"SetCloseAMSysTimeDateS1") == 0){
    	if( (tmp>=0)&&(tmp<=12)){
    		if(tmp < config_para.systemPoint.SetClosePMSysTimeDateS2){
    			config_para.systemPoint.SetCloseAMSysTimeDateS1 = tmp ;
    		}else{
        		return 1 ;
        	}
    	}else{
    		return 1 ;
    	}
    }else if(strcmp(name,"SetClosePMSysTimeDateS2") == 0){
    	if( (tmp>12)&&(tmp<=23)){
    		if(tmp > config_para.systemPoint.SetCloseAMSysTimeDateS1	){
    			config_para.systemPoint.SetClosePMSysTimeDateS2 = tmp ;
    		}else{
        		return 1 ;
        	}
    	}else{
    		return 1 ;
    	}
    }else if(strcmp(name,"SetCloseHumidityDateK1") == 0){
    	if( (tmp>=0)&&(tmp<=100)){
    		if(tmp < config_para.systemPoint.SetOpeneHumidityDateK2 ){
    			config_para.systemPoint.SetCloseHumidityDateK1 = tmp ;
    		}else{
        		return 1 ;
        	}
    	}else{
    		return 1 ;
    	}
    }else if(strcmp(name,"SetOpeneHumidityDateK2") == 0){
    	if( (tmp>=0)&&(tmp<=100)){
    		if(tmp > config_para.systemPoint.SetCloseHumidityDateK1 ){
    			config_para.systemPoint.SetOpeneHumidityDateK2 = tmp ;
    		}else{
        		return 1 ;
        	}
    	}else{
    		return 1 ;
    	}
    }else if(strcmp(name,"SetCloseInternalTemperature") == 0){
    	if( (tmp>=-40)&&(tmp<=80)){
    		config_para.systemPoint.SetCloseInternalTemperature = tmp ;
    	}else{
    		return 1 ;
    	}
    }else if(strcmp(name,"SetCloseExternalTemperature") == 0){
    	if( (tmp>=-40)&&(tmp<=80)){
    		config_para.systemPoint.SetCloseExternalTemperature = tmp ;
    	}else{
    		return 1 ;
    	}
    }else if(strcmp(name,"SetCloseInternalTemperatureDifferenceC1") == 0){
    	if( (tmp>=-40)&&(tmp<=80)){
    		if( tmp < config_para.systemPoint.SetOpenInternalTemperatureDifferenceC2){
    	    	config_para.systemPoint.SetCloseInternalTemperatureDifferenceC1 = tmp ;
    		}else{
        		return 1 ;
        	}
    	}else{
    		return 1 ;
    	}
    }else if(strcmp(name,"SetOpenInternalTemperatureDifferenceC2") == 0){
    	if( (tmp>=-40)&&(tmp<=80)){
    		if( tmp > config_para.systemPoint.SetCloseInternalTemperatureDifferenceC1){
    	    	config_para.systemPoint.SetOpenInternalTemperatureDifferenceC2 = tmp ;
    		}else{
        		return 1 ;
        	}
    	}else{
    		return 1 ;
    	}
    }else if(strcmp(name,"SetCloseTemperatureDelayDateT1") == 0){
    	if( (tmp>=5)&&(tmp<=7200)){
    		config_para.systemPoint.SetCloseTemperatureDelayDateT1 = tmp ;
    	}else{
    		return 1 ;
    	}
    }else if(strcmp(name,"SetCloseIlluminationDelayDateT2") == 0){
    	if( (tmp>=5)&&(tmp<=7200)){
    		config_para.systemPoint.SetCloseIlluminationDelayDateT2 = tmp ;
    	}else{
    		return 1 ;
    	}
    }else if(strcmp(name,"SetCloseHumidityDelayDateT3") == 0){
    	if( (tmp>=5)&&(tmp<=7200)){
    		config_para.systemPoint.SetCloseHumidityDelayDateT3 = tmp ;
    	}else{
    		return 1 ;
    	}
    }else{
    	return 1 ;
    }
	read_config_check(read_buff);
    //解析我们读到的Json字符串
    cJSON* config_json = cJSON_Parse(read_buff);
    if( config_json == NULL ){
        	cJSON_Delete(config_json);//清除结构体
        	return 1 ;
        }
	 //定位到mqttloginPoint的节点，并修改其值
    cJSON* systemparaPoint = cJSON_GetObjectItem(config_json,"systemparaPoint");
    if( systemparaPoint == NULL ){
    	cJSON_Delete(config_json);//清除结构体
    	return 1 ;
    }

    cJSON* systemparadate = cJSON_GetObjectItem(systemparaPoint,name);
    if( systemparadate == NULL ){
    	cJSON_Delete(config_json);//清除结构体
    	return 1 ;
    }else{
    	cJSON_SetNumberValue(systemparadate,systempara);
    }
    char *json_data = cJSON_Print(config_json);	//JSON数据结构转换为JSON字符串
    write_file(nConfigFile, json_data, strlen(json_data));
	cJSON_Delete(config_json);//清除结构体
	cJSON_free(json_data);
	return 0 ;
}


int externalparaPoint_amend_config( const char * const name ,int systempara){
	int tmp = 0 ;
	if( name == NULL){
		return 1 ;
	}
    tmp = systempara ;
    if(strcmp(name,"ExternalTemperatureCompensationDate") == 0){
    	if( (tmp<=80)&&(tmp>=-40)){
    		config_para.externalPoint.ExternalTemperatureCompensationDate = tmp;
    	}else{
    		return 1 ;
    	}
    }else if(strcmp(name,"ExternalHumidityCompensationDate") == 0){
    	if( (tmp<=100)&&(tmp>=0)){
    		config_para.externalPoint.ExternalHumidityCompensationDate = tmp;
    	}else{
    		return 1 ;
    	}
    }else if(strcmp(name,"ExternalAlarmTemperature") == 0){
    	if( (tmp<=80)&&(tmp>=-40)){
    		config_para.externalPoint.ExternalAlarmTemperature = tmp;
    	}else{
    		return 1 ;
    	}
    }else if(strcmp(name,"ExternalAlarmHumidity") == 0){
    	if( (tmp<=100)&&(tmp>=0)){
    		config_para.externalPoint.ExternalAlarmHumidity = tmp;
    	}else{
    		return 1 ;
    	}
    }else if(strcmp(name,"ExternalHumitureSampleRate") == 0){
    	if( (tmp<=20)&&(tmp>=1)){
    		config_para.externalPoint.ExternalHumitureSampleRate = tmp;
    	}else{
    		return 1 ;
    	}
    }else if(strcmp(name,"ExternalIlluminationCompensationDate") == 0){
    	if( (tmp<=200000)&&(tmp>=0)){
    		config_para.externalPoint.ExternalIlluminationCompensationDate = tmp;
    	}else{
    		return 1 ;
    	}
    }else if(strcmp(name,"SetMaxIlluminationDate") == 0){
    	if( (tmp<=200000)&&(tmp>=0)){
    		config_para.externalPoint.SetMaxIlluminationDate = tmp;
    	}else{
    		return 1 ;
    	}
    }else if(strcmp(name,"SetMinIlluminationDate") == 0){
    	if( (tmp<=200000)&&(tmp>=0)){
    		config_para.externalPoint.SetMinIlluminationDate = tmp;
    	}else{
    		return 1 ;
    	}
    }else if(strcmp(name,"ExternalIlluminationSampleRate") == 0){
    	if( (tmp<=20)&&(tmp>=1)){
    		config_para.externalPoint.ExternalIlluminationSampleRate = tmp;
    	}else{
    		return 1 ;
    	}
    }else if(strcmp(name,"ExternalSleetSensitivityDate") == 0){
    	if( (tmp<=3500)&&(tmp>=500)){
    		config_para.externalPoint.ExternalSleetSensitivityDate = tmp;
    	}else{
    		return 1 ;
    	}
    }else if(strcmp(name,"ExternalSleetHeatLowerLimitDate") == 0){
    	if( (tmp<=70)&&(tmp>=-30)){
    		config_para.externalPoint.ExternalSleetHeatLowerLimitDate = tmp;
    	}else{
    		return 1 ;
    	}
    }else if(strcmp(name,"ExternalSleetHeatHightLimitDate") == 0){
    	if( (tmp<=70)&&(tmp>=0)){
    		config_para.externalPoint.ExternalSleetHeatHightLimitDate = tmp;
    	}else{
    		return 1 ;
    	}
    }else if(strcmp(name,"ExternalSleetDelayAlarmRestDate") == 0){
    	if( (tmp<=60000)&&(tmp>=0)){
    		config_para.externalPoint.ExternalSleetDelayAlarmRestDate = tmp;
    	}else{
    		return 1 ;
    	}
    }else if(strcmp(name,"ExternalSleetSampleRateDate") == 0){
    	if( (tmp<=20)&&(tmp>=1)){
    		config_para.externalPoint.ExternalSleetSampleRateDate = tmp;
    	}else{
    		return 1 ;
    	}
    }else{
    	return 1 ;
    }
	read_config_check(read_buff);
    //解析我们读到的Json字符串
    cJSON* config_json = cJSON_Parse(read_buff);
    if( config_json == NULL ){
        	cJSON_Delete(config_json);//清除结构体
        	return 1 ;
        }
	 //定位到mqttloginPoint的节点，并修改其值
    cJSON* externalparaPoint = cJSON_GetObjectItem(config_json,"externalparaPoint");
    if( externalparaPoint == NULL ){
    	cJSON_Delete(config_json);//清除结构体
    	return 1 ;
    }
    cJSON* externalparadate = cJSON_GetObjectItem(externalparaPoint,name);
    if( externalparadate == NULL ){
    	cJSON_Delete(config_json);//清除结构体
    	return 1 ;
    }else{
    	cJSON_SetNumberValue(externalparadate,systempara);
    }
    char *json_data = cJSON_Print(config_json);	//JSON数据结构转换为JSON字符串
    write_file(nConfigFile, json_data, strlen(json_data));
	cJSON_Delete(config_json);//清除结构体
	cJSON_free(json_data);
	return 0 ;
}


int internalparaPoint_amend_config( const char * const name ,int systempara){
	int tmp = 0 ;
	if( name == NULL){
		return 1 ;
	}
    tmp = systempara ;
    if(strcmp(name,"InternalTemperatureCompensationDate") == 0){
    	if( (tmp<=MAX_INTERNAL_TEMPERATURE_COMPENSATION_DATE)&&(tmp>=MIN_INTERNAL_TEMPERATURE_COMPENSATION_DATE)){
    		config_para.internalPoint.InternalTemperatureCompensationDate = tmp;
    	}else{
    		return 1 ;
    	}
    }else if(strcmp(name,"InternalHumidityCompensationDate") == 0){
    	if( (tmp<=MAX_INTERNAL_HUMIDITY_COMPENSATION_DATE)&&(tmp>=MIN_INTERNAL_HUMIDITY_COMPENSATION_DATE)){
    		config_para.internalPoint.InternalHumidityCompensationDate = tmp;
    	}else{
    		return 1 ;
    	}
    }else if(strcmp(name,"InternalAlarmTemperature") == 0){
    	if( (tmp<=MAX_INTERNAL_ALARM_TEMPERATURE)&&(tmp>=MIN_INTERNAL_ALARM_TEMPERATURE)){
    		config_para.internalPoint.InternalAlarmTemperature = tmp;
    	}else{
    		return 1 ;
    	}
    }else if(strcmp(name,"InternalAlarmHumidity") == 0){
    	if( (tmp<=MAX_INTERNAL_ALARM_HUMIDITY)&&(tmp>=MIN_INTERNAL_ALARM_HUMIDITY)){
    		config_para.internalPoint.InternalAlarmHumidity = tmp;
    	}else{
    		return 1 ;
    	}
    }else if(strcmp(name,"InternalHumitureSampleRate") == 0){
    	if( (tmp<=MAX_INTERNAL_HUMITURE_SAMPLE_RATE)&&(tmp>=MIN_INTERNAL_HUMITURE_SAMPLE_RATE)){
    		config_para.internalPoint.InternalHumitureSampleRate = tmp;
    	}else{
    		return 1 ;
    	}
    }else if(strcmp(name,"InternalSmokeSampleRate") == 0){
    	if( (tmp<=MAX_INTERNAL_SMOKE_SAMPLE_RATE)&&(tmp>=MIN_INTERNAL_SMOKE_SAMPLE_RATE)){
    		config_para.internalPoint.InternalSmokeSampleRate = tmp;
    	}else{
    		return 1 ;
    	}
    }else if(strcmp(name,"InternalWaterSampleRate") == 0){
    	if( (tmp<=MAX_INTERNAL_WATER_SAMPLE_RATE)&&(tmp>=MIN_INTERNAL_WATER_SAMPLE_RATE)){
    		config_para.internalPoint.InternalWaterSampleRate = tmp;
    	}else{
    		return 1 ;
    	}
    }else{
    	return 1 ;
    }
	read_config_check(read_buff);
    //解析我们读到的Json字符串
    cJSON* config_json = cJSON_Parse(read_buff);
    if( config_json == NULL ){
        	cJSON_Delete(config_json);//清除结构体
        	return 1 ;
        }
	 //定位到mqttloginPoint的节点，并修改其值
    cJSON* internalparaPoint = cJSON_GetObjectItem(config_json,"internalparaPoint");
    if( internalparaPoint == NULL ){
    	cJSON_Delete(config_json);//清除结构体
    	return 1 ;
    }
    cJSON* internalparadate = cJSON_GetObjectItem(internalparaPoint,name);
    if( internalparadate == NULL ){
    	cJSON_Delete(config_json);//清除结构体
    	return 1 ;
    }else{
    	cJSON_SetNumberValue(internalparadate,systempara);
    }
    char *json_data = cJSON_Print(config_json);	//JSON数据结构转换为JSON字符串
    write_file(nConfigFile, json_data, strlen(json_data));
	cJSON_Delete(config_json);//清除结构体
	cJSON_free(json_data);
	return 0 ;
}


int OtherparaPoint_amend_config( const char * const name ,int systempara){
	int tmp = 0 ;
	if( name == NULL){
		log_e("name is NULL !!");
		return 1 ;
	}
    tmp = systempara ;
    if(strcmp(name,"LoginMenuconfigPasswd") == 0){
    	if( (tmp<=9999)&&(tmp>0)){
    		config_para.otherPoint.login_menuconfig_passwd = tmp;
    	}else{
    		log_e("parameter error!!");
    		return 1 ;
    	}
    }else{
    	log_e("name error!!");
    	return 1 ;
    }
	read_config_check(read_buff);
    //解析我们读到的Json字符串
    cJSON* config_json = cJSON_Parse(read_buff);
    if( config_json == NULL ){
		cJSON_Delete(config_json);//清除结构体
		log_e("parse error error!!");
		return 1 ;
    }
	 //定位到mqttloginPoint的节点，并修改其值
    cJSON* OtherparaPoint = cJSON_GetObjectItem(config_json,"OtherparaPoint");
    if( OtherparaPoint == NULL ){
    	cJSON_Delete(config_json);//清除结构体
    	log_e("parse error error!!");
    	return 1 ;
    }
    cJSON* otherparadate = cJSON_GetObjectItem(OtherparaPoint,name);
    if( otherparadate == NULL ){
    	cJSON_Delete(config_json);//清除结构体
    	log_e("parse error error!!");
    	return 1 ;
    }else{
    	cJSON_SetNumberValue(otherparadate,systempara);
    }
    char *json_data = cJSON_Print(config_json);	//JSON数据结构转换为JSON字符串
    write_file(nConfigFile, json_data, strlen(json_data));
	cJSON_Delete(config_json);//清除结构体
	cJSON_free(json_data);
	return 0 ;
}




int config_init(void){
	if(check_configguration_file()){
		log_w("File open error! %s", nConfigFile );
		log_w("start write default config!!! ");
		write_config( default_para );
		log_i("write default config success. ");
	}
	read_config();

	return 0 ;
}

int read_saveenv_cjson_mqttip_parameter( mqtt_ip_tcp_def *mqtt_ip_parameter_t){
	*mqtt_ip_parameter_t = config_para.mqtttcpipPoint;
	return 0 ;
}

int read_saveenv_cjson_mqttport_parameter( mqtt_port_tcp_def *mqtt_port_parameter_t){
	*mqtt_port_parameter_t = config_para.mqttportPoint;
	return 0 ;
}

int read_saveenv_cjson_mqttlogin_parameter( mqtt_login_def *mqtt_login_parameter_t){
	*mqtt_login_parameter_t = config_para.mqttloginPoint;
	return 0 ;
}

int read_saveenv_cjson_system_parameter( system_para_def *system_parameter_t){
	*system_parameter_t = config_para.systemPoint;
	return 0 ;
}

int read_saveenv_cjson_external_parameter (external_para_def *external_parameter_t){
	*external_parameter_t = config_para.externalPoint;
	return 0 ;
}

int read_saveenv_cjson_internal_parameter (internal_para_def *internal_parameter_t){
	*internal_parameter_t = config_para.internalPoint;
	return 0 ;
}

int read_saveenv_cjson_other_parameter( other_para_def *other_para_def_t){
	*other_para_def_t = config_para.otherPoint;
	return 0 ;
}





