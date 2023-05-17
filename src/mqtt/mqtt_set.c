/*
 * mqtt_set.c
 *
 *  Created on: 2023年4月11日
 *      Author: 好
 */
#define LOG_TAG    "mqtt_set"


#include "../mqtt/mqtt_set.h"
#include "../mqtt/mqtt_pub_packet.h"
#include "../mqtt/mqtt_topic.h"


static set_function_callback set_function_callback_t=NULL ;

extern pthread_mutex_t pthread_mutex_t_mqtt_t ;


void *Propret_Set_Sub_Masg_pthread(void *Propert_Set_String) {

    if (Propert_Set_String == NULL) {
        log_e("Propert_Set_String is NULL!!   ");
        pthread_exit(NULL);  //退出线程
    }
    struct  mosquitto  *Set_reply_mosq ;
    struct Propert_Set *p_propert_set_topic_masg = (struct Propert_Set*) Propert_Set_String  ;
    struct Propert_Set_Reply_Packet_Masg Propert_Set_Reply_Packet_Masg_t ;
    struct Propert_Set_Packet_Masg Propert_Set_Packet_Masg_t;

    pthread_mutex_lock(&pthread_mutex_t_mqtt_t);  //加锁

    //分配内存空间
    Propert_Set_Packet_Masg_t.string = (char*)malloc(strlen(p_propert_set_topic_masg->propert_set_string)+1 );
    if(Propert_Set_Packet_Masg_t.string == NULL ){
        log_e("Unable to allocate memory");
        free(p_propert_set_topic_masg->propert_set_string);
        free(p_propert_set_topic_masg);
        pthread_mutex_unlock(&pthread_mutex_t_mqtt_t);  //解锁
        pthread_exit(NULL);  //退出线程
    }
    memset(Propert_Set_Packet_Masg_t.string, 0, strlen(p_propert_set_topic_masg->propert_set_string)+1 );
    // 复制消息内容到结构体成员
    strncpy(Propert_Set_Packet_Masg_t.string, p_propert_set_topic_masg->propert_set_string,strlen(p_propert_set_topic_masg->propert_set_string) );
    Propert_Set_Packet_Masg_t.TimeStamp = p_propert_set_topic_masg->Time_Stamp;
    Set_reply_mosq = p_propert_set_topic_masg->mosq ;
    free(p_propert_set_topic_masg->propert_set_string);
    free(p_propert_set_topic_masg);
    Propert_Set_Packet_Masg_t.Set_Execut_Function = set_function_callback_t;  				//设置回调函数
    int mqtt_anlys_success_flag = Propert_Set_Analys_Packet(&Propert_Set_Packet_Masg_t); 	//解析topic 为set主题的消息
    if (mqtt_anlys_success_flag == 0) {			//成功
        Propert_Set_Reply_Packet_Masg_t.Code_Number = 200;
    }else if(mqtt_anlys_success_flag == -1) {	//正在运动
    	Propert_Set_Reply_Packet_Masg_t.Code_Number = 240;
    }else{										//远程控制无效
        Propert_Set_Reply_Packet_Masg_t.Code_Number = 250;
    }
    Propert_Set_Reply_Packet_Masg_t.TimeStamp = Propert_Set_Packet_Masg_t.TimeStamp;
    Propert_Set_Reply_Packet_Masg_t.Version = "V1.0.0";
    char *creat_set_reply_string = Propert_Set_Reply_Publish_Packet(&Propert_Set_Reply_Packet_Masg_t);
    if (creat_set_reply_string != NULL) {
        int ret = mosquitto_publish(Set_reply_mosq, NULL, Mqtt_Topic_Masg_t.propert_set_reply_topic, strlen(creat_set_reply_string), creat_set_reply_string, Mqtt_Topic_Masg_t.propert_set_reply_qos, 0);
        if (ret != MOSQ_ERR_SUCCESS) {
            log_e("Propert get publish error, error number is=%d ", ret);
        }
        free(creat_set_reply_string);
    }
    pthread_mutex_unlock(&pthread_mutex_t_mqtt_t);  //解锁
    pthread_exit(NULL);  //退出线程
}



void Set_Topic_Execute_Function_Register(set_function_callback pSetFun){
	if(pSetFun != NULL ){
		set_function_callback_t = pSetFun ;
	}
}

void Set_Topic_Execute_Function_UnRegister(void){
	set_function_callback_t = NULL ;
}
