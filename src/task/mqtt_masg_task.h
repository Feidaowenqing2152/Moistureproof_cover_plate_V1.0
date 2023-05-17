/*
 * mqtt_masg_task.h
 *
 *  Created on: 2023年4月20日
 *      Author: 好
 */

#ifndef TASK_MQTT_MASG_TASK_H_
#define TASK_MQTT_MASG_TASK_H_


#include "../common.h"




#define MSG_MAX_SIZE  			1024
#define MQTT_CLIENT_MAX_SIZE 	100

typedef struct Set_Mqtt_Clientm{
	uint8_t mqtt_username_change_flag ;
	uint8_t mqtt_password_change_flag ;
	uint8_t mqtt_host_change_flag ;
	uint8_t mqtt_port_change_flag ;
}Set_Mqtt_Client_System;


extern Set_Mqtt_Client_System Set_Mqtt_Client_System_t ;

struct Mqtt_Client_Date{
	struct  mosquitto    *mosq ;
    char    clientid[MQTT_CLIENT_MAX_SIZE];
    char    username[MQTT_CLIENT_MAX_SIZE];
    char    password[MQTT_CLIENT_MAX_SIZE];
    char    brokeraddress[MQTT_CLIENT_MAX_SIZE] ;
    int     brokerport;
    int     keep_alive ;
};






void create_mqtt_pub_pthread_init(void);
void* mqtt_pub_msg_task(void *arg) ;

#endif /* TASK_MQTT_MASG_TASK_H_ */
