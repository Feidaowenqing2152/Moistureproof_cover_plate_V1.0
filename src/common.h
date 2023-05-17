/*
 * common.h
 *
 *  Created on: 2023年1月4日
 *      Author: 好
 */

#ifndef COMMON_H_
#define COMMON_H_




/************************ sys ***********************************************/
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>
#include <getopt.h>
#include <unistd.h>
#include <fcntl.h>
#include <string.h>
#include <sys/types.h>
#include <sys/ioctl.h>
#include <sys/stat.h>
#include <sys/time.h>
#include <sys/select.h>
#include <sys/socket.h>
#include <time.h>
#include <stdbool.h>
#include <pthread.h>
#include <errno.h>
#include <net/if.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <signal.h>
#include <linux/rtc.h>
#include <errno.h>

#include <mosquitto.h>
#include <elog.h>


#include "../dw_adderss.h"

/************************ hardware ***********************************************/
#include "../hardware/dev_rtc.h"
#include "../hardware/dev_tty.h"
//#include "../hardware/dev_buttons.h"
//#include "../hardware/dev_motor.h"
#include "../hardware/dev_buzz.h"
#include "../hardware/dev_rgb_led.h"

/************************ drive ***********************************************/
#include "../drive/buttons.h"
#include "../drive/tty.h"
#include "../drive/dw_display.h"
#include "../drive/timer.h"
#include "../drive/motor.h"
#include "../drive/water_alarm.h"
#include "../drive/smoke_alarm.h"
#include "../drive/check_mode.h"
#include "../drive/dw_display.h"
#include "../drive/rtc.h"
#include "../drive/rgb_led.h"

/************************ app ***********************************************/
#include "../app/config_moistureproof_data.h"
#include "../app/eth.h"
#include "../app/transducer_modbus.h"
#include "../app/dw_function.h"
#include "../app/app_motor.h"
#include "../app/app_fan_motor.h"
#include "../app/app_smoke.h"
#include "../app/app_water.h"
#include "../app/app_check_mode.h"

/************************ common ***********************************************/
#include "../easylogger/user_elog.h"
#include "../common/annulus_fifo.h"
#include "../common/cJSON.h"
#include "../common/delay.h"

/************************ hmi ***********************************************/
#include "../himi/menu/menu.h"
#include "../himi/hmi_enter_menuconfig.h"
#include "../himi/hmi_menuconfig_set.h"
#include "../himi/common/hmi_common.h"


#include "../himi/external/hmi_external_set.h"
#include "../himi/external/hmi_humi.h"
#include "../himi/external/hmi_illumi.h"
#include "../himi/external/hmi_sleet.h"
#include "../himi/external/hmi_temp.h"

#include "../himi/internal/hmi_internal_set.h"
#include "../himi/internal/hmi_temp.h"
#include "../himi/internal/hmi_humi.h"
#include "../himi/internal/hmi_water.h"
#include "../himi/internal/hmi_smoke.h"

#include "../himi/sys/hmi_system_set.h"
#include "../himi/sys/hmi_SysTime.h"
#include "../himi/sys/hmi_SysNet.h"
#include "../himi/sys/hmi_SysCommunicate.h"
#include "../himi/sys/hmi_SysControl.h"
#include "../himi/sys/hmi_SysControl/hmi_SysControl_Illumination.h"
#include "../himi/sys/hmi_SysControl/hmi_SysControl_Timer.h"
#include "../himi/sys/hmi_SysControl/hmi_SysControl_Humidity.h"
#include "../himi/sys/hmi_SysControl/hmi_SysControl_Temperature.h"
#include "../himi/sys/hmi_SysControl/hmi_SysControl_CloseDelay.h"
#include "../himi/sys/hmi_SysControl/hmi_SysControl_Display.h"

#include "../himi/other/hmi_other_set.h"
#include "../himi/other/hmi_menuconfig_passwd.h"

/************************ mqtt ***********************************************/


//#include "../mqtt/mqtt_packet.h"
//#include "../mqtt/mqtt_topic.h"
/************************ task ***********************************************/
#include "../task/deal_rs485_masg_task.h"
#include "../task/dw_display_task.h"
#include "../task/scan_event_task.h"
#include "../task/listen_rs485_masg_task.h"
#include "../task/main.h"
#include "../task/timer_task.h"
#include "../task/mqtt_masg_task.h"


#define TRANSDUCER_OFFLINE_TIMEOUT 6 *1000         //传感器超时掉线检测时间 10s

#define MQTT_TIMESTAMP_ERROR_VALUE 3600 * 1000  //mqtt时间戳误差值为3600秒，即1小时

#define POSITIVE_CONVERT_MINUS(X)  ((X)>(0) ? (~(X-1)):(X) )
#define MINUS_CONVERT_POSITIVE(X)  ((X)<(0) ? (~X+1):(X)  )

#ifndef NULL
#define NULL   (void *)0
#endif

#endif /* COMMON_H_ */
