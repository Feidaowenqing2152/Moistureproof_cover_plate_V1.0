/*
 * app_smoke.h
 *
 *  Created on: 2023年2月17日
 *      Author: 好
 */

#ifndef APP_APP_SMOKE_H_
#define APP_APP_SMOKE_H_

#include "../common.h"


struct smoke_transducer_paramer{
	bool smoke_status ;
	bool smoke_online ;
};

void app_smoke_init(void);

struct smoke_transducer_paramer loop_scan_smoke_sate_task(uint16_t scan_timer);



#endif /* APP_APP_SMOKE_H_ */
