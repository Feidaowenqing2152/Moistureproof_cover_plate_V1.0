/*
 * mqtt_post.h
 *
 *  Created on: 2023年4月11日
 *      Author: 好
 */

#ifndef MQTT_MQTT_POST_H_
#define MQTT_MQTT_POST_H_

#include "../common.h"
#include "../mqtt/mqtt_pub_packet.h"
struct Propert_Post{
	struct  mosquitto  *mosq ;
	struct Propert_Post_Packet_Masg Propert_Post_Packet_Masg_t ;
};

struct Event_Post{
	struct  mosquitto  *mosq ;
	struct Event_Post_Packet_Masg Event_Post_Packet_Masg_t ;
};





bool Propert_Post_Message( struct Propert_Post *Propert_Post_t);
bool Event_Post_Massage( struct Event_Post *Event_Post_t);



#endif /* MQTT_MQTT_POST_H_ */
