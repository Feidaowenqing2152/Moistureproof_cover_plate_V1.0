/*
 * mqtt_set.h
 *
 *  Created on: 2023年4月11日
 *      Author: 好
 */

#ifndef MQTT_MQTT_SET_H_
#define MQTT_MQTT_SET_H_

#include "../common.h"
#include "../mqtt/mqtt_sub_packet.h"
#include "../mqtt/mqtt_pub_packet.h"

typedef int (*set_function_callback)(int,int,int);
struct Propert_Set{
//	pthread_mutex_t *mqtt_deal_set_topic_mutex;//定义全局变量，初始化锁
	struct  mosquitto  *mosq ;
	char* propert_set_string;
	char* Time_Stamp ;

};

void* Propret_Set_Sub_Masg_pthread(void* Propert_Set_String);
void Set_Topic_Execute_Function_Register(set_function_callback pSetFun);
void Set_Topic_Execute_Function_UnRegister(void);
#endif /* MQTT_MQTT_SET_H_ */
