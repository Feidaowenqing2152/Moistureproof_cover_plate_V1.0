/*
 * mqtt_topic.c
 *
 *  Created on: 2023年4月10日
 *      Author: 好
 */
#define LOG_TAG    "mqtt_topic"

#include "../mqtt/mqtt_topic.h"


int Topics_Init(struct Client_Name  *Client_Name_t){

	const char* Event_Topic[Max_Topic_Number]={
			"ExternalHumitureEvent","InternalHumitureEvent","IlluminationEvent","SleetEvent",
			"SmokeEvent","WaterEvent","RunModeEvent","BoardEvent","FanEvent","RemoteControlEvent",
	};

	sprintf(Mqtt_Topic_Masg_t.propert_post_topic,"/sys/%s/thing/event/property/post",Client_Name_t->Name);
	log_d("Propert Post Pub Topic=%s",Mqtt_Topic_Masg_t.propert_post_topic);
	sprintf(Mqtt_Topic_Masg_t.propert_post_reply_topic,"/sys/%s/thing/event/property/post_reply",Client_Name_t->Name);
	log_d("Propert Post_Reply Sub Topic=%s",Mqtt_Topic_Masg_t.propert_post_reply_topic);

	sprintf(Mqtt_Topic_Masg_t.propert_get_topic,"/sys/%s/thing/service/property/get",Client_Name_t->Name);
	log_d("Propert Get Sub Topic=%s",Mqtt_Topic_Masg_t.propert_get_topic);
	sprintf(Mqtt_Topic_Masg_t.propert_get_reply_topic,"/sys/%s/thing/service/property/get_reply",Client_Name_t->Name);
	log_d("Propert Get_Reply Pub Topic=%s",Mqtt_Topic_Masg_t.propert_get_reply_topic);

	sprintf(Mqtt_Topic_Masg_t.propert_set_topic,"/sys/%s/thing/service/property/set",Client_Name_t->Name);
	log_d("Propert Set Sub Topic=%s",Mqtt_Topic_Masg_t.propert_set_topic);
	sprintf(Mqtt_Topic_Masg_t.propert_set_reply_topic,"/sys/%s/thing/service/property/set_reply",Client_Name_t->Name);
	log_d("Propert Set_Reply Pub Topic=%s",Mqtt_Topic_Masg_t.propert_set_reply_topic);

	for(uint8_t i=0;i< Max_Topic_Number ;i++){
		sprintf(Mqtt_Topic_Masg_t.Mqtt_Event_Topic_t[i].event_post_topic,"/sys/%s/thing/event/%s/post",Client_Name_t->Name,Event_Topic[i]);
		log_d("Propert Event Post Pub Topic=%s",Mqtt_Topic_Masg_t.Mqtt_Event_Topic_t[i].event_post_topic);
		sprintf(Mqtt_Topic_Masg_t.Mqtt_Event_Topic_t[i].event_post_reply_topic,"/sys/%s/thing/event/%s/post_reply",Client_Name_t->Name,Event_Topic[i]);
		log_d("Propert Event Post_Reply Sub Topic=%s",Mqtt_Topic_Masg_t.Mqtt_Event_Topic_t[i].event_post_reply_topic);
	}
	return 0 ;
}


int Mqtt_Subscribe_Topic(struct mosquitto *mosq){  //订阅主题函数
	int ret = 0 ;
	ret = mosquitto_subscribe(mosq, NULL, Mqtt_Topic_Masg_t.propert_post_reply_topic,Mqtt_Topic_Masg_t.propert_post_reply_qos);
	if(ret != MOSQ_ERR_SUCCESS ){  //订阅主题
		const char *error_str = mosquitto_strerror(ret);
		log_e("subscribe topic error=%s,error code=%s!",Mqtt_Topic_Masg_t.propert_post_reply_topic,error_str);
	}else{
		log_d("subscribe topic success=%s",Mqtt_Topic_Masg_t.propert_post_reply_topic);
	}
	ret = mosquitto_subscribe(mosq, NULL, Mqtt_Topic_Masg_t.propert_get_topic,Mqtt_Topic_Masg_t.propert_get_qos) ;
	if(ret != MOSQ_ERR_SUCCESS ){  //订阅主题
		const char *error_str = mosquitto_strerror(ret);
		log_e("subscribe topic error=%s,error code=%s!",Mqtt_Topic_Masg_t.propert_get_topic,error_str);
	}else{
		log_d("subscribe topic success=%s",Mqtt_Topic_Masg_t.propert_get_topic);
	}
	ret = mosquitto_subscribe(mosq, NULL, Mqtt_Topic_Masg_t.propert_set_topic,Mqtt_Topic_Masg_t.propert_set_qos);
	if(ret != MOSQ_ERR_SUCCESS ){  //订阅主题
		const char *error_str = mosquitto_strerror(ret);
		log_e("subscribe topic error=%s,error code=%s!",Mqtt_Topic_Masg_t.propert_set_topic,error_str);
	}else{
		log_d("subscribe topic success=%s",Mqtt_Topic_Masg_t.propert_set_topic);
	}

	for(uint8_t i = 0 ;i<Max_Topic_Number-1;i++){
		ret = mosquitto_subscribe(mosq, NULL, Mqtt_Topic_Masg_t.Mqtt_Event_Topic_t[i].event_post_reply_topic, Mqtt_Topic_Masg_t.Mqtt_Event_Topic_t[i].event_post_reply_qos);
		if(ret != MOSQ_ERR_SUCCESS ){  //订阅post回应主题
			const char *error_str = mosquitto_strerror(ret);
			log_e("subscribe topic error=%s,error code=%s!",Mqtt_Topic_Masg_t.Mqtt_Event_Topic_t[i].event_post_reply_topic,error_str);
		}else{
			log_d("subscribe topic success=%s",Mqtt_Topic_Masg_t.Mqtt_Event_Topic_t[i].event_post_reply_topic);
		}
	}
	return 0 ;
}


int Set_Mqtt_Message_Quality_Init(void){
	for(uint8_t i=0;i<Max_Topic_Number ; i++){
		Mqtt_Topic_Masg_t.Mqtt_Event_Topic_t[i].event_post_qos = qos_1 ;
		Mqtt_Topic_Masg_t.Mqtt_Event_Topic_t[i].event_post_reply_qos = qos_1 ;
	}
	Mqtt_Topic_Masg_t.propert_post_qos = qos_0 ;
	Mqtt_Topic_Masg_t.propert_post_reply_qos = qos_0 ;

	Mqtt_Topic_Masg_t.propert_get_qos = qos_1 ;
	Mqtt_Topic_Masg_t.propert_get_reply_qos = qos_1 ;

	Mqtt_Topic_Masg_t.propert_set_qos = qos_2 ;
	Mqtt_Topic_Masg_t.propert_set_reply_qos = qos_2 ;
	return 0 ;
}

char *Greate_Time_Stamp(void){
	static char Time_Stamp_Buff[100];
	struct timeval Time_Stamp;
	gettimeofday(&Time_Stamp,NULL);
	long long Time_Stamp_Date = (long long)Time_Stamp.tv_sec * 1000 + (long long)Time_Stamp.tv_usec / 1000;
	sprintf( Time_Stamp_Buff ,"%lld",Time_Stamp_Date);
	return Time_Stamp_Buff ;
}

struct Client_Id_Date Greate_Client_Id(struct Client_Id_Name  *Client_Id_t){
	static struct Client_Id_Date  ClientDate_t ;
	char *time_stamp_t =NULL;
	time_stamp_t = Greate_Time_Stamp();
	sprintf(ClientDate_t.Time_Stamp,time_stamp_t,100);
	sprintf( ClientDate_t.Client_Id ,"%s|%s",Client_Id_t->UserName,time_stamp_t);
	return ClientDate_t ;
}

