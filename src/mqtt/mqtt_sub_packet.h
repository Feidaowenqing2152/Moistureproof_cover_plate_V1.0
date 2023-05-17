/*
 * mqtt_sub_packet.h
 *
 *  Created on: 2023年4月11日
 *      Author: 好
 */

#ifndef MQTT_MQTT_SUB_PACKET_H_
#define MQTT_MQTT_SUB_PACKET_H_

#include "../common.h"
#include "../mqtt/mqtt_topic.h"

struct Propert_Get_Packet_Masg{
	char* TimeStamp ;
	char* propert_get_string ;
};

struct Propert_Analys_Get_Masg{
	bool Sub_Identifier_Flag[Max_Publish_Type+1];
};


struct Propert_Set_Packet_Masg{
	char* TimeStamp ;
	char *string;
	int (*Set_Execut_Function)(int,int,int);

};



int Propert_Set_Analys_Packet( struct Propert_Set_Packet_Masg *Propert_Set_Packet_Masg_t);
struct Propert_Analys_Get_Masg Propert_Get_Analys_Packet( struct Propert_Get_Packet_Masg *Propert_Get_Packet_Masg_t );

#endif /* MQTT_MQTT_SUB_PACKET_H_ */
