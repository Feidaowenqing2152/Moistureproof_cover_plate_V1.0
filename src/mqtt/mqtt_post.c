/*
 * mqtt_post.c
 *
 *  Created on: 2023年4月11日
 *      Author: 好
 */
#define LOG_TAG    "mqtt_post"

#include "../mqtt/mqtt_post.h"
#include "../mqtt/mqtt_pub_packet.h"
#include "../mqtt/mqtt_topic.h"


bool Propert_Post_Message( struct Propert_Post *Propert_Post_t){
	struct Propert_Post_Packet_Masg Propert_Post_Packet_Masg_t ;
	Propert_Post_Packet_Masg_t.Version = "V1.0.0";
	Propert_Post_Packet_Masg_t.TimeStamp = Propert_Post_t->Propert_Post_Packet_Masg_t.TimeStamp ;
	for(uint8_t i=0;i<Max_Publish_Type;i++){
		Propert_Post_Packet_Masg_t.Propert_Params_t[i].Publish_Params= Propert_Post_t->Propert_Post_Packet_Masg_t.Propert_Params_t[i].Publish_Params ;
	}
	char* buff = Propert_Post_Packet(&Propert_Post_Packet_Masg_t);
	if(buff == NULL ){
		return false ;
	}
	int ret = mosquitto_publish(Propert_Post_t->mosq, NULL, Mqtt_Topic_Masg_t.propert_post_topic, strlen(buff), buff, Mqtt_Topic_Masg_t.propert_post_qos, 0);
	free(buff);
	if(ret != MOSQ_ERR_SUCCESS ){
		log_e("Propert Post publish error,error number is=%d \r",ret);
		return false ;
	}
	return true ;
}

bool Event_Post_Massage( struct Event_Post *Event_Post_t){
	struct Event_Post_Packet_Masg Event_Post_Packet_Masg_t ;
	int enent_post_number = 0 ;
	Event_Post_Packet_Masg_t.Version = "V1.0.0";
	Event_Post_Packet_Masg_t.TimeStamp = Event_Post_t->Event_Post_Packet_Masg_t.TimeStamp ;
	for(uint8_t i=0;i<Max_Topic_Number;i++){
		Event_Post_Packet_Masg_t.Event_Params_t[i].Publish_Params= Event_Post_t->Event_Post_Packet_Masg_t.Event_Params_t[i].Publish_Params ;
	}
	char* buff = Event_Post_Packet(&Event_Post_Packet_Masg_t,&enent_post_number);
	if(buff == NULL ){
		return false ;
	}
	log_d("event_post_topic=%s \r",Mqtt_Topic_Masg_t.Mqtt_Event_Topic_t[enent_post_number].event_post_topic);
	log_d("buff=%s",buff);

	int ret = mosquitto_publish(Event_Post_t->mosq, NULL, Mqtt_Topic_Masg_t.Mqtt_Event_Topic_t[enent_post_number].event_post_topic, strlen(buff), buff, Mqtt_Topic_Masg_t.Mqtt_Event_Topic_t[enent_post_number].event_post_qos, 0);
	free(buff);
	if(ret != MOSQ_ERR_SUCCESS ){
		log_e("event Post publish error,error number is=%d \r",ret);
		return false ;
	}
	return true ;
}














