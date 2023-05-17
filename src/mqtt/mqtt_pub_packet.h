/*
 * mqtt_packet.h
 *
 *  Created on: 2023年4月6日
 *      Author: 好
 */

#ifndef MQTT_MQTT_PUB_PACKET_H_
#define MQTT_MQTT_PUB_PACKET_H_

#include "../common.h"
#include "../mqtt/mqtt_topic.h"


struct Propert_Params{
	int Publish_Params ; 
};

struct Event_Params{
	int Publish_Params ; 
};





struct Propert_Post_Packet_Masg{
	char* TimeStamp ;
	char* Version ;
	struct Propert_Params Propert_Params_t[Max_Publish_Type];
};

struct Event_Post_Packet_Masg{
	char* TimeStamp ;
	char* Version ;
	struct Event_Params Event_Params_t[Max_Topic_Number];
};




struct Propert_Get_Reply_Packet_Masg{
	char* TimeStamp ;
	char* Version ;
	
	int Pub_Identifier_Flag[Max_Publish_Type+1] ;
	struct Propert_Params Propert_Params_t[Max_Publish_Type];
};

struct Propert_Set_Reply_Packet_Masg{
	char* TimeStamp ;
	char* Version ;
	int Code_Number ; 
};

char* Propert_Post_Packet( struct Propert_Post_Packet_Masg *Propert_Post_Packet_Masg_t);
char* Propert_Get_Reply_Publish_Packet( struct Propert_Get_Reply_Packet_Masg *Propert_Get_Reply_Packet_Masg_t);
char *Propert_Set_Reply_Publish_Packet(struct Propert_Set_Reply_Packet_Masg *Propert_Set_Reply_Packet_Masg_t);
char* Event_Post_Packet(struct Event_Post_Packet_Masg *Event_Post_Packet_Masg_t ,int *Event_Number);

#endif /* MQTT_MQTT_PACKET_H_ */


