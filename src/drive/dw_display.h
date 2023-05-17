/*
 * dw_display.h
 *
 *  Created on: 2023年2月10日
 *      Author: 好
 */

#ifndef DRIVE_DW_DISPLAY_H_
#define DRIVE_DW_DISPLAY_H_

#include "../common.h"









#define DW_TTY_NAME		"/dev/ttymxc2"
#define DW_DEFAULT_BAUDRATE  115200

#define DW_FH   0x5AA5        //迪文屏幕帧头



/************************** 主页面参数图标地址 *******************************************************/
//typedef enum{
//
//
//}MAIN_PAGE_PARAMETER_VAR_ADDR;



typedef struct msg_write_var{
	uint16_t head;
	uint8_t  length;
	uint8_t  cmd;
	uint16_t var_adderss;
	uint16_t var_data ;
//	uint16_t crc16;
}msg_write_var_t;

typedef struct msg_write_page{
	uint16_t head;
	uint8_t  length;
	uint8_t  cmd;
	uint16_t sys_var_adderss;
	uint16_t sys_switch_page_adderss;
	uint16_t switch_page_number ;
//	uint16_t crc16;
}msg_write_page_t;




typedef struct msg_read_cmd{
	uint16_t head;
	uint8_t  length;
	uint8_t  cmd;
	uint16_t var_adderss;
	uint8_t  var_lent ;
//	uint16_t crc16;
}msg_read_cmd_t;


typedef struct msg_read_data{
	uint16_t head;
	uint8_t  length;
	uint8_t  cmd;
	uint16_t var_adderss;
	uint8_t  read_lent ;
	uint16_t read_data;
//	uint16_t crc16;
}msg_read_data_t;





int dw_ip_var_adderss(int *ip_buffer );
int dw_netmask_var(int *netmask_buffer );
int dw_route_gw_var(int *gw_buffer );
int dw_broadcast_var(int *broadcast_buffer );
int dw_time_var(struct tm *time );
int dw_eth_connect_state(uint8_t eth_state);
int dw_cumulative_time(uint16_t cumulative_time);
int dw_external_temperature(uint16_t external_temperature );
int dw_external_humidity(uint16_t external_humidity );
int dw_interior_temperature(uint16_t interior_temperature);
int dw_interior_humidity(uint16_t interior_humidity );
int dw_illumination_transducer(int illumination_grade);
int dw_sleet_transducer(int sleet_state);


int dw_by_oneself_adderss_var_display(int var_adderss,int var_data);
int dw_switching_pages(int page_number);

int dw_setting_slect_var( int var_addr ,uint8_t var_state);
int dw_moistureproof_state(uint8_t moistureproof_state);
int dw_moistureproof_state_var(uint8_t moistureproof_state_var);

int dw_fan_motor_rotate_data_var(uint16_t rotate_data);
int dw_fan_motor_animation_state_var(uint8_t moistureproof_state_var);

int dw_smoke_state_var(uint8_t state);
int dw_water_state_var(uint8_t state);

int dw_check_mode_state_var(uint8_t state);
int dw_external_humiture_online_state_var(uint8_t state);
int dw_internal_humiture_online_state_var(uint8_t state);

//int dw_external_temp_dev_addr_reset_window( uint8_t set_var);

int dw_input_parameter_hint_window( uint8_t set_var,int InputParHintWaitWindownAddr ,int InputParHintSuccessWindownAddr ,int InputParHintErrorWindownAddr);

/**************************************************温度相关参数度显示************************************************************************/
int show_ex_temp_compensation_date(int val);
int show_ex_temp_alarm_threshold_date(int val);
int show_ex_temp_humiture_sample_rate_date(int val);
/*************************************************湿度相关参数度显示************************************************************************/
int show_ex_humill_compensation_date(int val);
int show_ex_humill_alarm_threshold_date(int val);

/**************************************************光照相关参数度显示************************************************************************/
int show_Illumi_compensation_date(int val);
int show_Illumi_real_time_date(int val);
int show_Illumi_intput_min_date(int val);
int show_Illumi_intput_max_date(int val);
int show_Illumi_sample_rate_date(int val);

/**************************************************雨雪相关参数度显示************************************************************************/
int show_sleet_real_time_sensitivity_date(int val);
int show_sleet_intput_sensitivity_date(int val);
int show_sleet_real_time_heat_lower_limit_date(int val);
int show_sleet_intput_heat_lower_limit_date(int val);
int show_sleet_real_time_heat_hight_limit_date(int val);
int show_sleet_intput_heat_hight_limit_date(int val);
int show_sleet_real_time_delay_alarm_reset_date(int val);
int show_sleet_intput_delay_alarm_reset_date(int val);
int show_sleet_sample_rate_date(int val);

/**************************************************内部温度相关参数度显示************************************************************************/
int show_in_temp_compensation_date(int val);
int show_in_temp_alarm_threshold_date(int val);
int show_in_temp_humiture_sample_rate_date(int val);
/**************************************************内部湿度相关参数度显示************************************************************************/
int show_in_humill_compensation_date(int val);
int show_in_humill_alarm_threshold_date(int val);
/**************************************************内部烟雾相关参数度显示************************************************************************/
int show_in_smoke_sample_rate_date(int val);
/**************************************************内部水浸相关参数度显示************************************************************************/
int show_in_water_sample_rate_date(int val);
/**************************************************自动返回主页相关参数度显示************************************************************************/
int show_sy_auto_exit_date(int val);
/**************************************************系统时钟相关参数度显示************************************************************************/
int show_sy_system_clock_years_date(int val);
int show_sy_system_clock_month_date(int val);
int show_sy_system_clock_days_date(int val);
int show_sy_system_clock_hours_date(int val);
int show_sy_system_clock_minute_date(int val);
/**************************************************系统网络相关参数度显示************************************************************************/
int show_system_ip_dhcp_state_date(int val);

int show_system_ip_addr1_intput_date(int val);
int show_system_ip_addr2_intput_date(int val);
int show_system_ip_addr3_intput_date(int val);
int show_system_ip_addr4_intput_date(int val);

int show_system_ip_mask1_intput_date(int val);
int show_system_ip_mask2_intput_date(int val);
int show_system_ip_mask3_intput_date(int val);
int show_system_ip_mask4_intput_date(int val);

int show_system_ip_gateway1_intput_date(int val);
int show_system_ip_gateway2_intput_date(int val);
int show_system_ip_gateway3_intput_date(int val);
int show_system_ip_gateway4_intput_date(int val);


int show_system_server_ip_addr1_intput_date(int val);
int show_system_server_ip_addr2_intput_date(int val);
int show_system_server_ip_addr3_intput_date(int val);
int show_system_server_ip_addr4_intput_date(int val);
int show_system_communicate_port_date(int val);
int show_system_login_id_date(int val);
int show_system_login_passwd_date(int val);
/**************************************************系统控制-光照强度控制参数度显示************************************************************************/

int show_system_control_illumination_disable_state_date(int val);
int show_system_present_control_illumination_clsoe_value_date(int val);
int show_system_intput_control_illumination_clsoe_value_date(int val);
int show_system_present_control_illumination_open_value_date(int val);
int show_system_intput_control_illumination_open_value_date(int val);
/**************************************************系统控制-系统时间控制参数度显示************************************************************************/
int show_system_control_timer_disable_state_date(int val);
int show_system_intput_control_timer_am_open_value_date(int val);
int show_system_intput_control_timer_pm_open_value_date(int val);
/**************************************************系统控制-温度差控制参数度显示************************************************************************/
int show_system_intput_control_humidity_close_value_date(int val);
int show_system_intput_control_humidity_open_value_date(int val);
/**************************************************系统控制-温度控制参数度显示************************************************************************/
int show_system_intput_control_in_temperature_close_value_date(int val);
int show_system_intput_control_ex_temperature_close_value_date(int val);
int show_system_intput_control_temperature_differ_close_value_date(int val);
int show_system_intput_control_temperature_differ_open_value_date(int val);
/**************************************************系统控制-盖板延时关闭参数度显示************************************************************************/
int show_system_temperature_delay_close_value_date(int val);
int show_system_humidity_delay_close_value_date(int val);
int show_system_illumination_delay_close_value_date(int val);
/**************************************************系统控制-屏幕控制参数度显示************************************************************************/
int show_system_control_display_luminance_value_date(int val);
int show_system_control_display_delay_close_value_date(int val);
int dw_control_display_luminance_date(int display_luminance_date);

/**************************************************其他参数-设置密码显示************************************************************************/
int show_set_menuconfig_passwd_date(int val);
int show_enter_menuconfig_passwd_date(int val);
#endif /* DRIVE_D
W_DISPLAY_H_ */


