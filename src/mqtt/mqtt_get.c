/*
 * mqtt_get.c
 *
 *  Created on: 2023年4月11日
 *      Author: 好
 */
#define LOG_TAG    "mqtt_get"

#include "../mqtt/mqtt_get.h"
#include "../mqtt/mqtt_pub_packet.h"
#include "../mqtt/mqtt_sub_packet.h"
#include "../mqtt/mqtt_topic.h"

extern pthread_mutex_t pthread_mutex_t_mqtt_t ;

 void* Propret_Get_Sub_Masg_pthread(void *Propert_Get_String) {
	if (Propert_Get_String == NULL) {
		log_w("Propert_Get_String is NULL!! \r  ");
		pthread_exit(NULL);  //退出线程
	}
	struct Propert_Get* p_propert_get_topic_masg = (struct Propert_Get*)Propert_Get_String;
	struct  mosquitto  *Get_reply_mosq ;
	struct Propert_Get_Packet_Masg Propert_Get_Packet_Masg_t ;
	struct Propert_Get_Reply_Packet_Masg Propert_Get_Reply_Packet_Masg_t ;
	struct Propert_Analys_Get_Masg Propert_Analys_Get_Masg_t ;

    pthread_mutex_lock(&pthread_mutex_t_mqtt_t);  //加锁

    //分配内存空间
    Propert_Get_Packet_Masg_t.propert_get_string = (char*)malloc(strlen(p_propert_get_topic_masg->propert_get_string)+1 );
    if( Propert_Get_Packet_Masg_t.propert_get_string  == NULL ){
        free(p_propert_get_topic_masg->propert_get_string);
        free(p_propert_get_topic_masg);
    	log_e("Unable to allocate memory");
        pthread_mutex_unlock(&pthread_mutex_t_mqtt_t);  //解锁
        pthread_exit(NULL);  //退出线程
    }
    memset( Propert_Get_Packet_Masg_t.propert_get_string , 0, strlen( p_propert_get_topic_masg->propert_get_string )+1 );

    // 复制消息内容到结构体成员
    strncpy(Propert_Get_Packet_Masg_t.propert_get_string, p_propert_get_topic_masg->propert_get_string,strlen((char *)(p_propert_get_topic_masg->propert_get_string)) +1);
	Propert_Get_Packet_Masg_t.TimeStamp = p_propert_get_topic_masg->Time_Stamp ;
	Get_reply_mosq = p_propert_get_topic_masg->mosq ;

	for(uint8_t i=0;i<Max_Publish_Type;i++){
		Propert_Get_Reply_Packet_Masg_t.Propert_Params_t[i].Publish_Params= p_propert_get_topic_masg->Propert_Params_t[i].Publish_Params ;
	}
    free(p_propert_get_topic_masg->propert_get_string);
    free(p_propert_get_topic_masg);

	Propert_Analys_Get_Masg_t= Propert_Get_Analys_Packet(&Propert_Get_Packet_Masg_t);
	for(uint8_t i=0;i<Max_Publish_Type+1;i++){
		Propert_Get_Reply_Packet_Masg_t.Pub_Identifier_Flag[i] = Propert_Analys_Get_Masg_t.Sub_Identifier_Flag[i];
	}
	Propert_Get_Reply_Packet_Masg_t.TimeStamp = Propert_Get_Packet_Masg_t.TimeStamp ;
	Propert_Get_Reply_Packet_Masg_t.Version = "V1.0.0";

	char* creat_get_reply_string = Propert_Get_Reply_Publish_Packet(&Propert_Get_Reply_Packet_Masg_t);
	if(creat_get_reply_string != NULL ){
		int ret = mosquitto_publish(Get_reply_mosq, NULL, Mqtt_Topic_Masg_t.propert_get_reply_topic, strlen(creat_get_reply_string), creat_get_reply_string, Mqtt_Topic_Masg_t.propert_get_reply_qos, 0);
		if(ret != MOSQ_ERR_SUCCESS ){
			log_e("Propert get publish error,error number is=%d \r",ret);
		}
		free(creat_get_reply_string);
	}
    pthread_mutex_unlock(&pthread_mutex_t_mqtt_t);  //解锁
    pthread_exit(NULL);  //退出线程

}



