/*
 * app_water.h
 *
 *  Created on: 2023年2月17日
 *      Author: 好
 */

#ifndef APP_APP_WATER_H_
#define APP_APP_WATER_H_

#include "../common.h"

struct water_transducer_paramer{
	bool water_status ;
	bool water_online ;
};



void app_water_init(void);
struct water_transducer_paramer loop_scan_water_sate_task(uint16_t scan_timer);



#endif /* APP_APP_WATER_H_ */
