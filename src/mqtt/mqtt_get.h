/*
 * mqtt_get.h
 *
 *  Created on: 2023年4月11日
 *      Author: 好
 */

#ifndef MQTT_MQTT_GET_H_
#define MQTT_MQTT_GET_H_

#include "../common.h"
#include "../mqtt/mqtt_pub_packet.h"

struct Propert_Get{
//	pthread_mutex_t *mqtt_deal_get_topic_mutex;//定义全局变量，初始化锁
	struct Propert_Params Propert_Params_t[Max_Publish_Type];
	struct  mosquitto  *mosq ;
	char* Time_Stamp ;
	char* propert_get_string;
};

 void* Propret_Get_Sub_Masg_pthread(void *Propert_Get_String);


#endif /* MQTT_MQTT_GET_H_ */
