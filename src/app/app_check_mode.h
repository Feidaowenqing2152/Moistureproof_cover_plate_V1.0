/*
 * app_check_mode.h
 *
 *  Created on: 2023年2月17日
 *      Author: 好
 */

#ifndef APP_APP_CHECK_MODE_H_
#define APP_APP_CHECK_MODE_H_

#include "../common.h"

void app_check_mode_init(void);
bool loop_scan_check_mode_sate_task(uint16_t scan_timer);

#endif /* APP_APP_CHECK_MODE_H_ */
