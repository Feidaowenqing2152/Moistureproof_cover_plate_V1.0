/*
 * dw_function.h
 *
 *  Created on: 2023年2月10日
 *      Author: 好
 */

#ifndef APP_DW_FUNCTION_H_
#define APP_DW_FUNCTION_H_

#include "../common.h"




typedef struct dw_switch_ico{
	uint8_t eth_connect_state; 				//  网口状态
	uint8_t cascading_connection_state;		//  级联状态
	uint8_t work_mode_state;				//  工作状态
	uint8_t open_state;						//  盖板状态

}dw_switch_ico;
dw_switch_ico type_dw_switch_ico;
extern dw_switch_ico type_dw_switch_ico;





int dw_function_init(void);
int dw_show_eth_connect_state(uint8_t eth_state);
int dw_show_ip_adderss(void);
int dw_show_netmask_adderss(void);
int dw_show_gw_adderss(void);
int dw_show_broadcast_adderss(void);
int dw_show_time_adderss(void);

int dw_show_cumulative_time(void);
int dw_show_external_temperature(void);
int dw_show_external_humidity(void);

int dw_show_interior_temperature(void);
int dw_show_interior_humidity(void);
int dw_show_illumination_transducer(uint8_t illumination_percentage);
int dw_show_sleet_transducer(void);

int dw_show_switching_pages(Page_Number SWITCH_PAGE);

void default_dw_show_moistureproof_open_state(void);
int dw_show_moistureproof_open_state(uint16_t animation_time,uint8_t refresh_flag);
void default_dw_show_moistureproof_close_state(void);
int dw_show_moistureproof_close_state(uint16_t animation_time,uint8_t refresh_flag);




//void dw_show_setting_slect_var( uint8_t Main_Setting_Page_Number_t,uint8_t restore_default_enable );
#endif /* APP_DW_FUNCTION_H_ */
