/*
 * mqtt_pub_packet.c
 *
 *  Created on: 2023年4月11日
 *      Author: 好
 */


#define LOG_TAG    "mqtt_pub_packet"

#include "../mqtt/mqtt_pub_packet.h"
#include "../common/cJSON.h"
#include "../mqtt/mqtt_topic.h"


static 	const char* identifier_string[Max_Publish_Type]={
		"CurrentExternalTemperature","CurrentExternalHumidity","CurrentInternalTemperature","CurrentInternalHumidity",
		"CurrentExternalIllumination","CurrentExternalSleet","CurrentInternalWater","CurrentInternalSmoke",
		"CurrentFanVelocity","CurrentRunMode","CurrentBoardStatus",
};

static 	const char* Event_identifier_string[Max_Topic_Number]={
		"OnlineStatus","OnlineStatus","OnlineStatus","OnlineStatus",
		"OnlineStatus","OnlineStatus","Error","Error","Error","Error",
};

char* Propert_Post_Packet( struct Propert_Post_Packet_Masg *Propert_Post_Packet_Masg_t){
	static int old_params[Max_Publish_Type]={-20,-20,-20,-20,-20,-20,-20,-20,-20,-20,-20};

	cJSON *root = NULL ;
	cJSON *Item = NULL ;

	for(uint8_t i=0;i<Max_Publish_Type;i++){
		if( Propert_Post_Packet_Masg_t->Propert_Params_t[i].Publish_Params != old_params[i]) {
			if(root == NULL ){
				root = cJSON_CreateObject(); //创建根录
				cJSON_AddStringToObject(root,"method", POST_METHOD);
				cJSON_AddStringToObject(root,"version", Propert_Post_Packet_Masg_t->Version);
				cJSON_AddStringToObject(root,"id", Propert_Post_Packet_Masg_t->TimeStamp);
				Item = cJSON_CreateObject();
			}
			cJSON_AddNumberToObject(Item,identifier_string[i], Propert_Post_Packet_Masg_t->Propert_Params_t[i].Publish_Params);
			old_params[i] = Propert_Post_Packet_Masg_t->Propert_Params_t[i].Publish_Params;
		}
	}
	if(Item == NULL){
		return NULL ;
	}else{
		cJSON_AddItemToObject(root, "params", Item); //将"properties"插入到根目录中
		char* String_Json  = cJSON_Print(root);	//JSON数据结构转换为JSON字符串
		char* String_buffer = (char*)(malloc(MSG_MAX_SIZE));
	    if(String_buffer == NULL ){
	    	log_e("malloc error ! ");
	    	return 0;
	    }
	    memset(String_buffer,0,MSG_MAX_SIZE);
		strncpy(String_buffer,String_Json,MSG_MAX_SIZE);
		cJSON_Delete(root);							//清除结构体
		cJSON_free(String_Json);
		return String_buffer ;
	}
	return NULL ;
}


char* Event_Post_Packet(struct Event_Post_Packet_Masg *Event_Post_Packet_Masg_t ,int *Event_Number){
	static int old_event_params[Max_Topic_Number]={0};
	char mothod[100];
	for(uint8_t i=0;i<Max_Topic_Number;i++){
		if( Event_Post_Packet_Masg_t->Event_Params_t[i].Publish_Params != old_event_params[i]) {
			char* mothod_topic =strstr(Mqtt_Topic_Masg_t.Mqtt_Event_Topic_t[i].event_post_topic,"thing");
			if(mothod_topic ==NULL)
				return NULL ;
			strncpy(mothod,mothod_topic,100);
			for(uint8_t i=0;i<3;i++){
				char* mothod_name =strstr(mothod,"/");
				*mothod_name = '.';
			}
			cJSON * root = cJSON_CreateObject(); //创建根录
			cJSON_AddStringToObject(root,"method", mothod);
			cJSON_AddStringToObject(root,"version", Event_Post_Packet_Masg_t->Version);
			cJSON_AddStringToObject(root,"id", Event_Post_Packet_Masg_t->TimeStamp);
			cJSON * Item = cJSON_CreateObject();
			cJSON_AddNumberToObject(Item,Event_identifier_string[i], Event_Post_Packet_Masg_t->Event_Params_t[i].Publish_Params);
			old_event_params[i] = Event_Post_Packet_Masg_t->Event_Params_t[i].Publish_Params;
			cJSON_AddItemToObject(root, "params", Item); //将"properties"插入到根目录中
			char* String_Json  = cJSON_Print(root);	//JSON数据结构转换为JSON字符串
			char* String_buffer = (char*)(malloc(MSG_MAX_SIZE));
		    if(String_buffer == NULL ){
		    	log_e("malloc error ! ");
		    	return NULL;
		    }
		    memset(String_buffer,0,MSG_MAX_SIZE);
			strncpy(String_buffer,String_Json,MSG_MAX_SIZE);
			cJSON_Delete(root);							//清除结构体
			cJSON_free(String_Json);
			*Event_Number = i ;
			return String_buffer ;
		}
	}
	return NULL ;
}


char* Propert_Get_Reply_Publish_Packet( struct Propert_Get_Reply_Packet_Masg *Propert_Get_Reply_Packet_Masg_t){

	cJSON *root = cJSON_CreateObject(); //创建根录
	cJSON_AddStringToObject(root,"method", GET_REPLY_METHOD);
	cJSON_AddStringToObject(root,"version", Propert_Get_Reply_Packet_Masg_t->Version);
	cJSON_AddStringToObject(root,"id", Propert_Get_Reply_Packet_Masg_t->TimeStamp);
	cJSON *Item = cJSON_CreateObject();
	if(Propert_Get_Reply_Packet_Masg_t->Pub_Identifier_Flag[0] == true){	//id正确
		for(uint8_t i=0;i<Max_Publish_Type;i++){
			if( Propert_Get_Reply_Packet_Masg_t->Pub_Identifier_Flag[i+1] == true ){
				cJSON_AddNumberToObject(Item,identifier_string[i], Propert_Get_Reply_Packet_Masg_t->Propert_Params_t[i].Publish_Params) ;
			}
		}
	 }else{
		 cJSON_AddStringToObject(Item ,"params:","error !");
	 }
	cJSON_AddItemToObject(root, "data", Item); //将"properties"插入到根目录中
	char* String_Great_Json  = cJSON_Print(root);	//JSON数据结构转换为JSON字符串
	log_d("String_Json=%s",String_Great_Json);
	char* String_buffer = (char*)(malloc(MSG_MAX_SIZE));
    if(String_buffer == NULL ){
    	log_e("malloc error ! ");
    	return NULL;
    }
    memset(String_buffer,0,MSG_MAX_SIZE);
	strncpy(String_buffer,String_Great_Json,MSG_MAX_SIZE);
	cJSON_Delete(root);							//清除结构体
	cJSON_free(String_Great_Json);
	return String_buffer ;
}


char *Propert_Set_Reply_Publish_Packet(struct Propert_Set_Reply_Packet_Masg *Propert_Set_Reply_Packet_Masg_t){
	cJSON *root = cJSON_CreateObject(); //创建根录
	if(root == NULL ){
		return NULL ;
	}
	cJSON_AddNumberToObject(root,"code", Propert_Set_Reply_Packet_Masg_t->Code_Number);
	cJSON_AddStringToObject(root,"id", Propert_Set_Reply_Packet_Masg_t->TimeStamp);
	cJSON *Item = cJSON_CreateObject();
	cJSON_AddItemToObject(root, "data", Item); //将"properties"插入到根目录中
	if(Propert_Set_Reply_Packet_Masg_t->Code_Number == 200  ){	//id正确
		 cJSON_AddStringToObject(root ,"message:","success");
	 }else if(Propert_Set_Reply_Packet_Masg_t->Code_Number == 240  ){
		 cJSON_AddStringToObject(root ,"message:","On the move !!");
	 }
	else{
		cJSON_AddStringToObject(root ,"message:","Ineffective control");
	 }
	cJSON_AddStringToObject(root,"method", SET_REPLY_METHOD);
	cJSON_AddStringToObject(root,"version", Propert_Set_Reply_Packet_Masg_t->Version);

	char* Ceart_Set_Reply_String_Json  = cJSON_Print(root);	//JSON数据结构转换为JSON字符串
	char* String_buffer = (char*)(malloc(MSG_MAX_SIZE));
    if(String_buffer == NULL ){
    	log_e("malloc error ! ");
    	return NULL;
    }
    memset(String_buffer,0,MSG_MAX_SIZE);
	strncpy(String_buffer,Ceart_Set_Reply_String_Json,MSG_MAX_SIZE);
	cJSON_free(Ceart_Set_Reply_String_Json);
	cJSON_Delete(root);							//清除结构体
	return String_buffer ;
}



