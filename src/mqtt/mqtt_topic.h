/*
 * mqtt_topic.h
 *
 *  Created on: 2023年4月10日
 *      Author: 好
 */

#ifndef MQTT_MQTT_TOPIC_H_
#define MQTT_MQTT_TOPIC_H_

#include "../common.h"

#define TOPIC_MAX_SIZE 100

#define POST_METHOD  		"thing.event.property.post"
#define POST_REPLY_METHOD   "thing.event.property.post_reply"

#define GET_METHOD			"thing.service.property.get"
#define GET_REPLY_METHOD	"thing.service.property.get_reply"

#define SET_METHOD			"thing.service.property.set"
#define SET_REPLY_METHOD	"thing.service.property.set_reply"

typedef enum{
	qos_0 = 0 ,
	qos_1 ,
	qos_2 ,
}Mqtt_Qos;

typedef enum{
	External_Humiture_Event_Topic=0 ,    
	Internal_Humiture_Event_Topic ,    
	Illumination_Event_Topic ,    
	Sleet_Event_Topic ,    
	Water_Event_Topic ,    
	Smoke_Event_Topic ,    
	Local_Run_Mode_Event_Topic ,    
	Board_Status_Event_Topic ,    
	Fan_Velocity_Event_Topic ,    
	Remote_Control_Event_Topic ,  
	
	Max_Topic_Number
}Device_Event_Topic;

typedef enum{
	External_Temperature =0 ,
	External_Humidity ,
	Internal_Temperature  ,
	Internal_Humidity ,
	External_Illumination ,
	External_Sleet ,
	Internal_Water ,
	Internal_Smoke ,
	Fan_Velocity , 
	Run_Mode , 
	Board_Status ,
	
	Max_Publish_Type
}Publish_Type;




struct Mqtt_Event_Topic{
	char    event_post_topic[TOPIC_MAX_SIZE];				//设备事件上报主题
	char    event_post_reply_topic[TOPIC_MAX_SIZE];			//设备事件上报应答主题
	int     event_post_qos;
	int     event_post_reply_qos;
};



struct Mqtt_Topic_Masg{
	struct Mqtt_Event_Topic Mqtt_Event_Topic_t[Max_Topic_Number];//设备事件上报主题
	char    propert_post_topic[TOPIC_MAX_SIZE];					//设备属性上报主题
	char    propert_post_reply_topic[TOPIC_MAX_SIZE];			//设备属性上报应答主题
	int     propert_post_qos;
	int     propert_post_reply_qos;
	
	char    propert_get_topic[TOPIC_MAX_SIZE];					//设备属性获取主题
	char    propert_get_reply_topic[TOPIC_MAX_SIZE];			//设备属性获取应答主题
	int     propert_get_qos;
	int     propert_get_reply_qos;
	
	char    propert_set_topic[TOPIC_MAX_SIZE];					//设备属性设置主题
	char    propert_set_reply_topic[TOPIC_MAX_SIZE];			//设备属性设置应答主题
	int     propert_set_qos;
	int     propert_set_reply_qos;
	
};


struct Mqtt_Topic_Masg  Mqtt_Topic_Masg_t;
extern struct Mqtt_Topic_Masg  Mqtt_Topic_Masg_t; ;

struct Client_Name{
	char *Name ;
};

struct Client_Id_Name{
	char* UserName ;
};

struct Client_Id_Date{
	char Client_Id[256] ;
	char Time_Stamp[100] ;
};

char *Greate_Time_Stamp(void);
struct Client_Id_Date Greate_Client_Id(struct Client_Id_Name  *Client_Id_t);

int Topics_Init(struct Client_Name  *Client_Name_t);	//初始化主题
int Mqtt_Subscribe_Topic(struct mosquitto *mosq);		//订阅主题函数
int Set_Mqtt_Message_Quality_Init(void);				//初始化qos消息服务质量
#endif /* MQTT_MQTT_TOPIC_H_ */


