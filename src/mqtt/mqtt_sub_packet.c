/*
 * mqtt_sub_packet.c
 *
 *  Created on: 2023年4月11日
 *      Author: 好
 */

#define LOG_TAG    "mqtt_sub_packet"

#include "../mqtt/mqtt_sub_packet.h"
#include "../common/cJSON.h"

static 	const char* identifier_string[11]={
		"CurrentExternalTemperature","CurrentExternalHumidity","CurrentInternalTemperature","CurrentInternalHumidity",
		"CurrentExternalIllumination","CurrentExternalSleet","CurrentInternalWater","CurrentInternalSmoke",
		"CurrentFanVelocity","CurrentRunMode","CurrentBoardStatus",
};

struct Propert_Analys_Get_Masg Propert_Get_Analys_Packet( struct Propert_Get_Packet_Masg *Propert_Get_Packet_Masg_t){
	struct Propert_Analys_Get_Masg Propert_Analys_Get_Masg_t ;
	memset(Propert_Analys_Get_Masg_t.Sub_Identifier_Flag,0,12);
	char buffer[100];
	if(Propert_Get_Packet_Masg_t->propert_get_string == NULL ){
		return  Propert_Analys_Get_Masg_t;
	}
	log_d("get String_Json :%s",Propert_Get_Packet_Masg_t->propert_get_string);
	cJSON *cjson_root = cJSON_Parse(Propert_Get_Packet_Masg_t->propert_get_string);	//将JSON字符串转换成JSON结构体
	 if (cjson_root == NULL || !cJSON_IsObject(cjson_root)) { 						//判断转换是否成功
		log_w("Propert_Get_Packet is NULL !");
        goto cjson_error;
	}
	/* 依次根据名称提取JSON数据（键值对） */
	    cJSON* cjson_id = cJSON_GetObjectItem(cjson_root, "id");
	    if (cjson_id == NULL || !cJSON_IsString(cjson_id)) { //判断转换是否成功
	    	 log_e("id item error");
	    	 goto cjson_error;
	    }
	    if (cjson_id->valuestring != NULL) {
	    	long long int recv_timestamp = atoll(cjson_id->valuestring);   				//转换接收到的时间戳为长整形
	    	long long int now_timestamp = atoll(Propert_Get_Packet_Masg_t->TimeStamp);   //转换现在的时间戳为长整形
	    	log_d("recv_timestamp=%lld,now_timestamp=%lld",recv_timestamp,now_timestamp);
	        if(now_timestamp >recv_timestamp ){
	        	long long int error_timestamp_value = now_timestamp - recv_timestamp ;
	        	log_d("error_timestamp_value=%lld",error_timestamp_value);
	        	if(error_timestamp_value>MQTT_TIMESTAMP_ERROR_VALUE ){ //不在允许误差内
	        		log_w("Subject Topic-Get, timestamp error is greater than the specified error");
	        		log_w("recv timestamp=%lld,now timestamp=%lld,timestamp error value=%lld",recv_timestamp,now_timestamp,error_timestamp_value);
	        		goto cjson_error;
	        	}
	        }else if( now_timestamp < recv_timestamp ){
	        	long long int error_timestamp_value = recv_timestamp - now_timestamp;
	        	log_d("error_timestamp_value=%lld",error_timestamp_value);
	        	if(error_timestamp_value>MQTT_TIMESTAMP_ERROR_VALUE ){ //不在允许误差内
	        		log_w("Subject Topic-Get, timestamp error is greater than the specified error");
	        		log_w("recv timestamp=%lld,now timestamp=%lld,timestamp error value=%lld",recv_timestamp,now_timestamp,error_timestamp_value);
	        		goto cjson_error;
	        	}
	        }
	        Propert_Analys_Get_Masg_t.Sub_Identifier_Flag[0] = true ;
	        cJSON *cjson_data = cJSON_GetObjectItem(cjson_root,"params");		//解析父类对象
			if (cjson_data == NULL || !cJSON_IsArray(cjson_data)) { //判断转换是否成功
				log_e("params item error");
				goto cjson_error;
			}
			int  array_size   = cJSON_GetArraySize ( cjson_data );
			for(uint8_t i=0;i<array_size;i++){
				cJSON *object = cJSON_GetArrayItem(cjson_data,i);   //因为这个对象是个数组获取，且只有一个元素所以写下标为0获取
				if(NULL == object ){
					log_e("object is NULL ");
					continue ;
				}
				char * ivalue = object->valuestring ;
				for(uint8_t i=0;i<11;i++){
					memset(buffer,0,100);
					sprintf(buffer , "%s",identifier_string[i]);
					if( strcmp (ivalue,buffer ) == 0 ){
						Propert_Analys_Get_Masg_t.Sub_Identifier_Flag[i+1] = true ;
						log_d("identifier:%s", ivalue);
						break ; //continue
					}
				}
			}
    }
    cjson_error:
	 cJSON_Delete(cjson_root);
	 free(Propert_Get_Packet_Masg_t->propert_get_string);
   return Propert_Analys_Get_Masg_t;
}
int Propert_Set_Analys_Packet(struct Propert_Set_Packet_Masg* Propert_Set_Packet_Masg_t) {
	int ret = -1 ;
	if (Propert_Set_Packet_Masg_t->string== NULL) {
        log_w("input set masge is NULL !");
        return -2; // 输入参数错误
    }
	log_d("set String_Json :%s", Propert_Set_Packet_Masg_t->string);
    cJSON* cjson_root = cJSON_Parse(Propert_Set_Packet_Masg_t->string); //将JSON字符串转换成JSON结构体
    if (cjson_root == NULL || !cJSON_IsObject(cjson_root)) { //判断转换是否成功
        log_w("Propert_Set_Packet is NULL !");
        free(Propert_Set_Packet_Masg_t->string);
        return -2; // 解析失败
    }
    /* 依次根据名称提取JSON数据（键值对） */
    cJSON* cjson_id = cJSON_GetObjectItem(cjson_root, "id");
    if (cjson_id == NULL || !cJSON_IsString(cjson_id)) { //判断转换是否成功
    	 goto exit;
    }
    if (cjson_id->valuestring != NULL) {
    	long long int recv_timestamp = atoll(cjson_id->valuestring);   				//转换接收到的时间戳为长整形
    	long long int now_timestamp = atoll(Propert_Set_Packet_Masg_t->TimeStamp);   //转换现在的时间戳为长整形
        if(now_timestamp >recv_timestamp ){
        	long long int error_timestamp_value = now_timestamp - recv_timestamp ;
        	if( error_timestamp_value > MQTT_TIMESTAMP_ERROR_VALUE ){ //不在允许误差内
        		log_w("Subject Topic-Set, timestamp error is greater than the specified error");
        		log_w("recv timestamp=%lld,now timestamp=%lld,timestamp error value=%lld",recv_timestamp,now_timestamp,error_timestamp_value);
        		goto exit;
        	}
        }else if( now_timestamp < recv_timestamp ){
        	long long int error_timestamp_value = recv_timestamp - now_timestamp;
        	log_d("error_timestamp_value=%lld",error_timestamp_value);
        	if( error_timestamp_value > MQTT_TIMESTAMP_ERROR_VALUE ){ //不在允许误差内
        		log_w("Subject Topic-Set, timestamp error is greater than the specified error");
        		log_w("recv timestamp=%lld,now timestamp=%lld,timestamp error value=%lld",recv_timestamp,now_timestamp,error_timestamp_value);
        		goto exit;
        	}
        }
		cJSON* cjson_data = cJSON_GetObjectItem(cjson_root, "params"); //解析父类对象
		if (cjson_data == NULL || !cJSON_IsObject(cjson_data)) { //判断转换是否成功
			 goto exit;
		}
		/* 依次根据名称提取JSON数据（键值对） */
		cJSON* cjson_flag = cJSON_GetObjectItem(cjson_data, "RemoteEnterTestMode");
		if (cjson_flag == NULL || !cJSON_IsNumber(cjson_flag)) { //判断转换是否成功
			log_e("parms error !");
			 goto exit;
		}
		cJSON* cjson_cmd = cJSON_GetObjectItem(cjson_data, "RemoteControlAction");
		if (cjson_cmd == NULL || !cJSON_IsNumber(cjson_cmd)) { //判断转换是否成功
			log_e("parms error !");
			 goto exit;
		}
		cJSON* cjson_time = cJSON_GetObjectItem(cjson_data, "RemoteControlTimer");
		if (cjson_time == NULL || !cJSON_IsNumber(cjson_time)) { //判断转换是否成功
			log_e("parms error !");
			 goto exit;
		}
		ret = Propert_Set_Packet_Masg_t->Set_Execut_Function(cjson_flag->valueint, cjson_cmd->valueint, cjson_time->valueint);
		free(Propert_Set_Packet_Masg_t->string);
		cJSON_Delete(cjson_root); // 释放内存
		return ret;

    }
    exit:
	free(Propert_Set_Packet_Masg_t->string);
    cJSON_Delete(cjson_root); // 释放内存
    return -2;
}
