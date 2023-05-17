/*
 * dw_adderss.h
 *
 *  Created on: 2023年2月14日
 *      Author: 好
 */

#ifndef DW_ADDERSS_H_
#define DW_ADDERSS_H_

#include "../common.h"

//主菜单页面功能编号
typedef enum  {
	PAGE_MAIN_NUMBER = 0,									//主页面
	PAGE_MAIN_SETTING_NUMBER,								//主菜单页面
	PAGE_EXTERNAL_SETTING_NUMBER,	                        //外部参数设置页面

	PAGE_EXTERNAL_TEMP_SETTING_NUMBER,	                    //外部参数-温度传感器设置页面
	PAGE_EXTERNAL_TEMP_DEV_ADDR_SETTING_NUMBER ,            //外部参数-温度传感器设置-设备地址复归页面
	PAGE_EXTERNAL_TEMP_COMPENSATION_SETTING_NUMBER ,        //外部参数-温度传感器设置-温度校验补偿页面
	PAGE_EXTERNAL_TEMP_ALARM_THRESHOLD_SETTING_NUMBER ,      //外部参数-温度传感器设置-高温报警阈值页面
	PAGE_EXTERNAL_TEMP_SAMPLE_RATE_SETTING_NUMBER ,		    //外部参数-温度传感器设置-温度采样速率页面

	PAGE_EXTERNAL_HUMIDITY_SETTING_NUMBER,				    //外部参数-湿度传感器设置页面
	PAGE_EXTERNAL_HUMIDITY_DEV_ADDR_SETTING_NUMBER , 		//外部参数-湿度传感器设置-设备地址复归页面
	PAGE_EXTERNAL_HUMIDITY_COMPENSATION_SETTING_NUMBER ,    //外部参数-湿度传感器设置-湿度校验补偿页面
	PAGE_EXTERNAL_HUMIDITY_ALARM_THRESHOLD_SETTING_NUMBER ,  //外部参数-湿度传感器设置-高湿报警阈值页面
	PAGE_EXTERNAL_HUMIDITY_SAMPLE_RATE_SETTING_NUMBER ,		//外部参数-湿度传感器设置-湿度采样速率页面

	PAGE_EXTERNAL_ILLUMINATION_SETTING_NUMBER,					//外部参数-光照传感器设置页面
	PAGE_EXTERNAL_ILLUMINATION_DEV_ADDR_SETTING_NUMBER , 		//外部参数-光照传感器设置-设备地址复归页面
	PAGE_EXTERNAL_ILLUMINATION_COMPENSATION_SETTING_NUMBER ,    //外部参数-光照传感器设置-光照校验补偿页面
	PAGE_EXTERNAL_ILLUMINATION_VEF_VALUE_SETTING_NUMBER ,  		//外部参数-光照传感器设置-光照基准值页面
	PAGE_EXTERNAL_ILLUMINATION_MIN_VALUE_SETTING_NUMBER ,  		//外部参数-光照传感器设置-最小光照值页面
	PAGE_EXTERNAL_ILLUMINATION_MAX_VALUE_SETTING_NUMBER ,  		//外部参数-光照传感器设置-最大光照值页面
	PAGE_EXTERNAL_ILLUMINATION_SAMPLE_RATE_SETTING_NUMBER ,		//外部参数-光照传感器设置-温度采样速率页面

	PAGE_EXTERNAL_SLEET_SETTING_NUMBER,							//外部参数-雨雪传感器设置页面
	PAGE_EXTERNAL_SLEET_DEV_ADDR_SETTING_NUMBER , 				//外部参数-雨雪传感器设置-设备地址复归页面
	PAGE_EXTERNAL_SLEET_SENSITIVITY_SETTING_NUMBER ,    		//外部参数-雨雪传感器设置-灵敏度设置页面
	PAGE_EXTERNAL_SLEET_HEATING_SETTING_NUMBER ,  				//外部参数-雨雪传感器设置-加热选择页面
	PAGE_EXTERNAL_SLEET_HEATING_LOW_LIMIT_SETTING_NUMBER ,  	//外部参数-雨雪传感器设置-加热设置-加热下限设置页面
	PAGE_EXTERNAL_SLEET_HEATING_HIGH_LIMIT_SETTING_NUMBER ,  	//外部参数-雨雪传感器设置-加热设置-加热上限设置页面
	PAGE_EXTERNAL_SLEET_DELAY_ALARM_RESET_SETTING_NUMBER ,  	//外部参数-雨雪传感器设置-报警复归延时设置页面
	PAGE_EXTERNAL_SLEET_SAMPLE_RATE_SETTING_NUMBER ,			//外部参数-雨雪传感器设置-采样速率页面

	PAGE_INTERNAL_SETTING_NUMBER,	                            //内部参数设置页面

	PAGE_INTERNAL_TEMP_SETTING_NUMBER,	                    //内部参数-温度传感器设置页面
	PAGE_INTERNAL_TEMP_DEV_ADDR_SETTING_NUMBER ,            //内部参数-温度传感器设置-设备地址复归页面
	PAGE_INTERNAL_TEMP_COMPENSATION_SETTING_NUMBER ,        //内部参数-温度传感器设置-温度校验补偿页面
	PAGE_INTERNAL_TEMP_ALARM_THRESHOLD_SETTING_NUMBER ,      //内部参数-温度传感器设置-高温报警阈值页面
	PAGE_INTERNAL_TEMP_SAMPLE_RATE_SETTING_NUMBER ,		    //内部参数-温度传感器设置-温度采样速率页面

	PAGE_INTERNAL_HUMIDITY_SETTING_NUMBER,				    //内部参数-湿度传感器设置页面
	PAGE_INTERNAL_HUMIDITY_DEV_ADDR_SETTING_NUMBER , 		//内部参数-湿度传感器设置-设备地址复归页面
	PAGE_INTERNAL_HUMIDITY_COMPENSATION_SETTING_NUMBER ,    //内部参数-湿度传感器设置-湿度校验补偿页面
	PAGE_INTERNAL_HUMIDITY_ALARM_THRESHOLD_SETTING_NUMBER ,  //内部参数-湿度传感器设置-高湿报警阈值页面
	PAGE_INTERNAL_HUMIDITY_SAMPLE_RATE_SETTING_NUMBER ,		//内部参数-湿度传感器设置-湿度采样速率页面

	PAGE_INTERNAL_WATER_SETTING_NUMBER,				      //内部参数-水浸传感器设置页面
	PAGE_INTERNAL_WATER_SAMPLE_RATE_SETTING_NUMBER ,	//内部参数-水浸传感器设置-水浸采样速率页面

	PAGE_INTERNAL_SMOKE_SETTING_NUMBER,				      //内部参数-烟雾传感器设置页面
	PAGE_INTERNAL_SMOKE_SAMPLE_RATE_SETTING_NUMBER ,	//内部参数-烟雾传感器设置-烟雾采样速率页面

	PAGE_SYSTEM_SETTING_NUMBER,	                        //系统参数设置页面
	PAGE_SYSTEM_TIME_SETTING_NUMBER,	                //系统参数-系统时间设置页面
	PAGE_SYSTEM_RUN_TIME_SETTING_NUMBER,	            //系统参数-系统时间-系统运行时间设置页面
	PAGE_AUTO_EXIT_TIME_SETTING_NUMBER,	            	//系统参数-系统时间-自动返回主页时间设置页面
	PAGE_SYSTEM_CLOCK_SETTING_NUMBER,	            	//系统参数-系统时间-系统时钟时间设置页面

	PAGE_SYSTEM_NETWORK_SETTING_NUMBER,	                //系统参数-系统网络设置页面
	PAGE_SYSTEM_AUTO_IP_ADDR_SETTING_NUMBER,	        //系统参数-系统网络-自动分配IP设置页面
	PAGE_SYSTEM_USER_IP_ADDR_SETTING_NUMBER,	        //系统参数-系统网络-手动分配IP设置页面

	PAGE_SYSTEM_COMMUNICATE_SETTING_NUMBER ,  			//系统参数-系统通信设置页面
	PAGE_SYSTEM_COMMUNICATE_SERVER_IP_SETTING_NUMBER ,	//系统参数-系统通信-服务端IP设置页面
	PAGE_SYSTEM_COMMUNICATE_PORT_SETTING_NUMBER ,  		//系统参数-系统通信-通信端口设置页面
	PAGE_SYSTEM_COMMUNICATE_ID_SETTING_NUMBER ,  		//系统参数-系统通信-通信ID设置页面
	PAGE_SYSTEM_COMMUNICATE_PASSWD_SETTING_NUMBER ,  	//系统参数-系统通信-登录密码设置页面

	PAGE_SYSTEM_CONTROL_FIRST_PAGE_SETTING_NUMBER ,		//系统参数-系统控制第一页设置页面
	PAGE_SYSTEM_CONTROL_LAST_PAGE_SETTING_NUMBER ,		//系统参数-系统控制第一页设置页面

	PAGE_SYSTEM_CONTROL_ILLUMINATION_SETTING_NUMBER ,	//系统参数-系统控制-光照强度控制选择设置页面
	PAGE_SYSTEM_CONTROL_TIMER_SETTING_NUMBER ,			//系统参数-系统控制-系统时间控制选择设置页面
	PAGE_SYSTEM_CONTROL_HUMIDITY_SETTING_NUMBER ,		//系统参数-系统控制-湿度差值控制选择设置页面
	PAGE_SYSTEM_CONTROL_TEMPERATURE_SETTING_NUMBER ,	//系统参数-系统控制-温度控制选择设置页面
	PAGE_SYSTEM_CONTROL_CLSOEDELAY_SETTING_NUMBER ,		//系统参数-系统控制-盖板关闭延时选择设置页面
	PAGE_SYSTEM_CONTROL_DISPLAY_SETTING_NUMBER ,		//系统参数-系统控制-系统屏幕选择设置页面

	PAGE_SYSTEM_CONTROL_ILLUMINATION_ENABLE_NUMBER ,	//系统参数-系统控制-光照强度-光照使能控制选择设置页面
	PAGE_SYSTEM_CONTROL_ILLUMINATION_CLOSE_NUMBER ,		//系统参数-系统控制-光照强度-光照关闭控制选择设置页面
	PAGE_SYSTEM_CONTROL_ILLUMINATION_OPEN_NUMBER ,		//系统参数-系统控制-光照强度-光照打开控制选择设置页面

	PAGE_SYSTEM_CONTROL_TIMER_ENABLE_NUMBER ,			//系统参数-系统控制-时间控制-时间控制使能选择设置页面
	PAGE_SYSTEM_CONTROL_TIMER_AM_OPEN_NUMBER ,			//系统参数-系统控制-时间控制-上午打开控制选择设置页面
	PAGE_SYSTEM_CONTROL_TIMER_PM_OPEN_NUMBER ,			//系统参数-系统控制-时间控制-下午打开控制选择设置页面

	PAGE_SYSTEM_CONTROL_HUMIDITY_CLOSE_NUMBER ,			//系统参数-系统控制-湿度控制-湿度关闭控制选择设置页面
	PAGE_SYSTEM_CONTROL_HUMIDITY_OPEN_NUMBER ,			//系统参数-系统控制-湿度控制-湿度打开控制选择设置页面

	PAGE_SYSTEM_CONTROL_IN_TEMPERATURE_CLOSE_NUMBER ,	 //系统参数-系统控制-温度控制-内温度关闭控制选择设置页面
	PAGE_SYSTEM_CONTROL_EX_TEMPERATURE_CLOSE_NUMBER ,	 //系统参数-系统控制-温度控制-外温度关闭控制选择设置页面
	PAGE_SYSTEM_CONTROL_TEMPERATURE_DIFFER_CLOSE_NUMBER ,//系统参数-系统控制-温度差控制-温度差关闭控制选择设置页面
	PAGE_SYSTEM_CONTROL_TEMPERATURE_DIFFER_OPEN_NUMBER , //系统参数-系统控制-温度差控制-温度差打开控制选择设置页面

	PAGE_SYSTEM_TEMPERATURE_DELAY_CLOSE_NUMBER , 		 //系统参数-系统控制-温度延时关闭-温度延时关闭设置页面
	PAGE_SYSTEM_HUMIDITY_DELAY_CLOSE_NUMBER , 		 	 //系统参数-系统控制-湿度延时关闭-湿度延时关闭设置页面
	PAGE_SYSTEM_ILLUMINATION_DELAY_CLOSE_NUMBER , 		 //系统参数-系统控制-光照延时关闭-光照延时关闭设置页面

	PAGE_SYSTEM_CONTROL_DISPLAY_LUMINANCE_NUMBER , 		 //系统参数-系统控制-系统屏幕控制-屏幕亮度设置页面
	PAGE_SYSTEM_CONTROL_DISPLAY_DELAY_CLOSE_NUMBER , 	 //系统参数-系统控制-系统屏幕控制-亮屏时间设置页面

	PAGE_CHECK_MENUCONFIG_PASSWORD_NUMBER ,				//菜单登录密码验证页面
	PAGE_OTHER_SETTING_NUMBER ,							//其他参数选择设置页面
	PAGE_SETTING_MENUCONFIG_PASSWORD_NUMBER ,			//其他参数--菜单登录密码设置页面

MAX_PAGE_NUMBER}Page_Number;

#define ETH_CONNECT_STATE_ADDERSS    				0x4001  //网络状态图标地址

#define CUMULATIVE_TIME_HEAD_ADDERSS 				0x4011	//累计时间数字变量首地址
#define CUMULATIVE_TIME_TAIL_ADDERSS 				0x4014	//累计时间数字变量尾地址

#define IP_VAR_HEARD_ADDERSS   						0x4031	//IP数字变量首地址
#define IP_VAR_TAIL_ADDERSS    						0x403C	//IP数字变量尾地址

#define NETMASK_VAR_HEARD_ADDERSS 					0x4031	//子网掩码数字变量首地址
#define NETMASK_VAR_TAIL_ADDERSS 					0x403C	//子网掩码数字变量尾地址

#define GW_VAR_HEARD_ADDERSS						0x4031	//网关数字变量首地址
#define GW_VAR_TAIL_ADDERSS		    				0x403C	//网关数字变量尾地址

#define BROADCAST_VAR_HEARD_ADDERSS					0x4031	//路由数字变量首地址
#define BROADCAST_VAR_TAIL_ADDERSS					0x403C	//路由数字变量尾地址

#define TIME_VAR_HEARD_ADDERSS 						0x4002	//日期数字变量首地址
#define TIME_VAR_TAIL_ADDERSS 						0x400D	//日期数字变量尾地址

#define WDAY_VAR_ADDERSS 							0x4015	//星期数字变量首地址

#define CHECK_MODE_VAR_ADDERSS      				0x4040  //工作模式显示图标

#define EXTERNAL_HUMITURE_ONLINE_VAR_ADDERSS 		0x4050  //显示外界温湿度在线状态情况
#define SLEET_GRADE_VAR_ADDERSS    			 		0x4051  //雨雪状态图标显示地址
#define INTERNAL_HUMITURE_ONLINE_VAR_ADDERSS 		0x4052  //显示内部温湿度在线状态情况
#define SMOKE_ALARM_VAR_ADDERSS     				0x4053  //烟雾状态图标显示地址
#define INTERIOR_TEMP_HEARD_ADDERSS 				0x4054	//内部温度数字变量首地址
#define INTERIOR_TEMP_TAIL_ADDERSS  				0x4055	//内部温度数字变量尾地址
#define EXTERNAL_TEMP_HEARD_ADDERSS 				0x4056	//外界温度数字变量首地址
#define EXTERNAL_TEMP_TAIL_ADDERSS  				0x4057	//外界温度数字变量尾地址

#define ILLUMINATION_GRADE_VAR_ADDERSS  			0x4061   //光照强度图标变量地址
#define WATER_ALARM_VAR_ADDERSS        		 		0x4063  //水浸状态图标显示地址
#define INTERIOR_HUMIDITY_HEARD_ADDERSS 			0x4064	//内部湿度数字变量首地址
#define INTERIOR_HUMIDITY_TAIL_ADDERSS  			0x4065	//内部湿度数字变量尾地址
#define EXTERNAL_HUMIDITY_HEARD_ADDERSS 			0x4066	//外界湿度数字变量首地址
#define EXTERNAL_HUMIDITY_TAIL_ADDERSS  			0x4067	//外界湿度数字变量尾地址

#define MOISTUREPROOF_ANIMATION_VAR_ADDERSS  		0x4020   //盖板状态动画变量地址

#define MOISTUREPROOF_STATE_VAR_ADDERSS      		0x403D   //盖板状态图标

#define FAN_MOTOR_ANIMATION_VAR_ADDERSS  		   	0x4021     //风机动画变量地址
#define FAN_MOTOR_ROTATE_HEARD_DATA_VAR_ADDERSS    	0x4042		//风机转速数字头变量地址
#define FAN_MOTOR_ROTATE_TAIL_DATA_VAR_ADDERSS     	0x4045		//风机转速数字尾变量地址





/*****************************外界参数选择设置指示图标地址***********************************************/
#define EXTERNAL_TEMPERATURE_SET_CURSOR_ADDERSS  			    	0x4080 //外界参数-选择光标地址

/*****************************外界温度设置***********************************************/
#define EXTERNAL_TEMP_DEV_SETTING_CURSOR_ADDERSS       				0x4090  //外界参数-温度传感器设置选择光标地址

#define EXTERNAL_TEMP_DEV_ADDERSS_RESET_CURSOR_ADDERSS 				0x40A0  //外界参数-温度传感器-设备地址复归选择光标地址
#define EXTERNAL_TEMP_DEV_ADDR_RESET_WAIT_WINDOW_VAR_ADDERSS 		0x40A1   //外界温度传感器设备地址复归等待弹窗
#define EXTERNAL_TEMP_DEV_ADDR_RESET_SUCCESS_WINDOW_VAR_ADDERSS 	0x40A2   //外界温度传感器设备地址复归成功弹窗
#define EXTERNAL_TEMP_DEV_ADDR_RESET_ERROR_WINDOW_VAR_ADDERSS 		0x40A3   //外界温度传感器设备地址复归失败弹窗

#define EXTERNAL_TEMP_COMPENSATION_INPUT_SELECT_CURSOR_ADDERSS  	0x40B0	//外界参数-温度传感器-温度校验补偿输入参数选择光标地址
#define EXTERNAL_TEMP_COMPENSATION_INPUT_MINUS_VAR_ADDERSS      	0x40B1  //外界参数-温度传感器-温度校验补偿输入参负号图标地址
#define EXTERNAL_TEMP_COMPENSATION_DECADE_NUMBER_VAR_ADDERSS    	0x40B2  //外界参数-温度传感器-温度校验补偿输入参数十位数字图标地址
#define EXTERNAL_TEMP_COMPENSATION_DIGITS_NUMBER_VAR_ADDERSS    	0x40B3  //外界参数-温度传感器-温度校验补偿输入参数个位数字图标地址

#define EXTERNAL_TEMP_COMPENSATION_WAIT_WINDOW_VAR_ADDERSS 			0x40B5   //外界温度传感器温度校验补偿保存参数等待弹窗
#define EXTERNAL_TEMP_COMPENSATION_SUCCESS_WINDOW_VAR_ADDERSS 		0x40B6   //外界温度传感器温度校验补偿保存参数成功弹窗
#define EXTERNAL_TEMP_COMPENSATION_ERROR_WINDOW_VAR_ADDERSS 		0x40B7   //外界温度传感器温度校验补偿保存参数失败弹窗
#define EXTERNAL_TEMP_COMPENSATION_SELECT_CURSOR_ADDERSS        	0x40B8	 //外界参数-温度传感器-温度校验补偿选择光标地址


#define EXTERNAL_TEMP_ALARM_THERSHOLD_INPUT_SELECT_CURSOR_ADDERSS 	0x40C0	 //外界参数-温度传感器-高温报警阈值输入参数选择光标地址
#define EXTERNAL_TEMP_ALARM_THERSHOLD_DECADE_NUMBER_VAR_ADDERSS   	0x40C2  //外界参数-温度传感器-高温报警阈值输入参数十位数字图标地址
#define EXTERNAL_TEMP_ALARM_THERSHOLD_DIGITS_NUMBER_VAR_ADDERSS   	0x40C3  //外界参数-温度传感器-高温报警阈值输入参数个位数字图标地址

#define EXTERNAL_TEMP_ALARM_THERSHOLD_WAIT_WINDOW_VAR_ADDERSS     	0x40C5   //外界温度传感器高温报警阈值保存参数等待弹窗
#define EXTERNAL_TEMP_ALARM_THERSHOLD_SUCCESS_WINDOW_VAR_ADDERSS  	0x40C6   //外界温度传感器高温报警阈值保存参数成功弹窗
#define EXTERNAL_TEMP_ALARM_THERSHOLD_ERROR_WINDOW_VAR_ADDERSS 	  	0x40C7   //外界温度传感器高温报警阈值保存参数失败弹窗
#define EXTERNAL_TEMP_ALARM_THERSHOLD_SELECT_CURSOR_ADDERSS       	0x40C8	//外界参数-温度传感器-高温报警阈值选择光标地址


#define EXTERNAL_TEMP_SAMPLE_RATE_INPUT_SELECT_CURSOR_ADDERSS 		0x40D0	//外界参数-温度传感器-温度采样速率输入参数选择光标地址
#define EXTERNAL_TEMP_SAMPLE_RATE_DECADE_NUMBER_VAR_ADDERSS   		0x40D2    //外界参数-温度传感器-温度采样速率输入参数十位数字图标地址
#define EXTERNAL_TEMP_SAMPLE_RATE_DIGITS_NUMBER_VAR_ADDERSS   		0x40D3    //外界参数-温度传感器-温度采样速率输入参数个位数字图标地址

#define EXTERNAL_TEMP_SAMPLE_RATE_WAIT_WINDOW_VAR_ADDERSS    		0x40D5    //外界温度传感器温度采样速率保存参数等待弹窗
#define EXTERNAL_TEMP_SAMPLE_RATE_SUCCESS_WINDOW_VAR_ADDERSS  		0x40D6    //外界温度传感器温度采样速率保存参数成功弹窗
#define EXTERNAL_TEMP_SAMPLE_RATE_ERROR_WINDOW_VAR_ADDERSS 	 	 	0x40D7    //外界温度传感器温度采样速率保存参数失败弹窗
#define EXTERNAL_TEMP_SAMPLE_RATE_SELECT_CURSOR_ADDERSS       		0x40D8	//外界参数-温度传感器-温度采样速率选择光标地址

/*****************************外界湿度设置***********************************************/
#define EXTERNAL_HUMIDITY_DEV_SETTING_CURSOR_ADDERSS       			0x40E0  //外界参数-湿度传感器设置选择光标地址

#define EXTERNAL_HUMIDITY_DEV_ADDERSS_RESET_CURSOR_ADDERSS 			0x40F0   //外界参数-湿度传感器-设备地址复归选择光标地址
#define EXTERNAL_HUMIDITY_DEV_ADDR_RESET_WAIT_WINDOW_VAR_ADDERSS 	0x40F1   //外界湿度传感器设备地址复归等待弹窗
#define EXTERNAL_HUMIDITY_DEV_ADDR_RESET_SUCCESS_WINDOW_VAR_ADDERSS 0x40F2   //外界湿度传感器设备地址复归成功弹窗
#define EXTERNAL_HUMIDITY_DEV_ADDR_RESET_ERROR_WINDOW_VAR_ADDERSS 	0x40F3   //外界湿度传感器设备地址复归失败弹窗

#define EXTERNAL_HUMIDITY_COMPENSATION_INPUT_SELECT_CURSOR_ADDERSS  0x4100	//外界参数-湿度传感器-湿度校验补偿输入参数选择光标地址
#define EXTERNAL_HUMIDITY_COMPENSATION_INPUT_MINUS_VAR_ADDERSS      0x4101  //外界参数-湿度传感器-湿度校验补偿输入参负号图标地址
#define EXTERNAL_HUMIDITY_COMPENSATION_DECADE_NUMBER_VAR_ADDERSS    0x4102  //外界参数-湿度传感器-湿度校验补偿输入参数十位数字图标地址
#define EXTERNAL_HUMIDITY_COMPENSATION_DIGITS_NUMBER_VAR_ADDERSS    0x4103  //外界参数-湿度传感器-湿度校验补偿输入参数个位数字图标地址

#define EXTERNAL_HUMIDITY_COMPENSATION_WAIT_WINDOW_VAR_ADDERSS 		0x4105   //外界湿度传感器湿度校验补偿保存参数等待弹窗
#define EXTERNAL_HUMIDITY_COMPENSATION_SUCCESS_WINDOW_VAR_ADDERSS 	0x4106   //外界湿度传感器湿度校验补偿保存参数成功弹窗
#define EXTERNAL_HUMIDITY_COMPENSATION_ERROR_WINDOW_VAR_ADDERSS 	0x4107   //外界湿度传感器湿度校验补偿保存参数失败弹窗
#define EXTERNAL_HUMIDITY_COMPENSATION_SELECT_CURSOR_ADDERSS        0x4108	 //外界参数-湿度传感器-湿度校验补偿选择光标地址


#define EXTERNAL_HUMIDITY_ALARM_THERSHOLD_INPUT_SELECT_CURSOR_ADDERSS 0x4200  //外界参数-湿度传感器-湿度报警阈值输入参数选择光标地址
#define EXTERNAL_HUMIDITY_ALARM_THERSHOLD_DECADE_NUMBER_VAR_ADDERSS   0x4202  //外界参数-湿度传感器-湿度报警阈值输入参数十位数字图标地址
#define EXTERNAL_HUMIDITY_ALARM_THERSHOLD_DIGITS_NUMBER_VAR_ADDERSS   0x4203  //外界参数-湿度传感器-湿度报警阈值输入参数个位数字图标地址

#define EXTERNAL_HUMIDITY_ALARM_THERSHOLD_WAIT_WINDOW_VAR_ADDERSS     0x4205   //外界湿度传感器湿度报警阈值保存参数等待弹窗
#define EXTERNAL_HUMIDITY_ALARM_THERSHOLD_SUCCESS_WINDOW_VAR_ADDERSS  0x4206   //外界湿度传感器湿度报警阈值保存参数成功弹窗
#define EXTERNAL_HUMIDITY_ALARM_THERSHOLD_ERROR_WINDOW_VAR_ADDERSS 	  0x4207   //外界湿度传感器湿度报警阈值保存参数失败弹窗
#define EXTERNAL_HUMIDITY_ALARM_THERSHOLD_SELECT_CURSOR_ADDERSS       0x4208	//外界参数-湿度传感器-湿度报警阈值选择光标地址


#define EXTERNAL_HUMIDITY_SAMPLE_RATE_INPUT_SELECT_CURSOR_ADDERSS 0x40D0	//外界参数-湿度传感器-湿度采样速率输入参数选择光标地址
#define EXTERNAL_HUMIDITY_SAMPLE_RATE_DECADE_NUMBER_VAR_ADDERSS   0x40D2    //外界参数-湿度传感器-湿度采样速率输入参数十位数字图标地址
#define EXTERNAL_HUMIDITY_SAMPLE_RATE_DIGITS_NUMBER_VAR_ADDERSS   0x40D3    //外界参数-湿度传感器-湿度采样速率输入参数个位数字图标地址

#define EXTERNAL_HUMIDITY_SAMPLE_RATE_WAIT_WINDOW_VAR_ADDERSS     0x40D5    //外界湿度传感器湿度采样速率保存参数等待弹窗
#define EXTERNAL_HUMIDITY_SAMPLE_RATE_SUCCESS_WINDOW_VAR_ADDERSS  0x40D6    //外界湿度传感器湿度采样速率保存参数成功弹窗
#define EXTERNAL_HUMIDITY_SAMPLE_RATE_ERROR_WINDOW_VAR_ADDERSS 	  0x40D7    //外界湿度传感器湿度采样速率保存参数失败弹窗
#define EXTERNAL_HUMIDITY_SAMPLE_RATE_SELECT_CURSOR_ADDERSS       0x40D8	//外界参数-湿度传感器-湿度采样速率选择光标地址

/*****************************外界光照设置***********************************************/
#define EXTERNAL_ILLUMINATION_DEV_SETTING_CURSOR_ADDERSS       	        0x4400  //外界参数-湿度传感器设置选择光标地址

#define EXTERNAL_ILLUMINATION_DEV_ADDERSS_RESET_CURSOR_ADDERSS 			0x4500   //外界参数-湿度传感器-设备地址复归选择光标地址
#define EXTERNAL_ILLUMINATION_DEV_ADDR_RESET_WAIT_WINDOW_VAR_ADDERSS 	0x4501   //外界湿度传感器设备地址复归等待弹窗
#define EXTERNAL_ILLUMINATION_DEV_ADDR_RESET_SUCCESS_WINDOW_VAR_ADDERSS 0x4502   //外界湿度传感器设备地址复归成功弹窗
#define EXTERNAL_ILLUMINATION_DEV_ADDR_RESET_ERROR_WINDOW_VAR_ADDERSS 	0x4503   //外界湿度传感器设备地址复归失败弹窗

#define EXTERNAL_ILLUMINATION_COMPENSATION_INPUT_SELECT_CURSOR_ADDERSS  0x4600	//外界参数-湿度传感器-湿度校验补偿输入参数选择光标地址
#define EXTERNAL_ILLUMINATION_COMPENSATION_INPUT_MINUS_VAR_ADDERSS      0x4601  //外界参数-湿度传感器-湿度校验补偿输入参负号图标地址
#define EXTERNAL_ILLUMINATION_COMPENSATION_HUNDREDS_NUMBER_VAR_ADDERSS  0x4602  //外界参数-湿度传感器-湿度校验补偿输入参数百位数字图标地址
#define EXTERNAL_ILLUMINATION_COMPENSATION_DIGITS_NUMBER_VAR_ADDERSS    0x4603  //外界参数-湿度传感器-湿度校验补偿输入参数十位数字图标地址
#define EXTERNAL_ILLUMINATION_COMPENSATION_DECADE_NUMBER_VAR_ADDERSS    0x4604  //外界参数-湿度传感器-湿度校验补偿输入参数个位数字图标地址

#define EXTERNAL_ILLUMINATION_COMPENSATION_WAIT_WINDOW_VAR_ADDERSS 		0x4605   //外界湿度传感器温度校验补偿保存参数等待弹窗
#define EXTERNAL_ILLUMINATION_COMPENSATION_SUCCESS_WINDOW_VAR_ADDERSS 	0x4606   //外界湿度传感器温度校验补偿保存参数成功弹窗
#define EXTERNAL_ILLUMINATION_COMPENSATION_ERROR_WINDOW_VAR_ADDERSS 	0x4607   //外界湿度传感器温度校验补偿保存参数失败弹窗
#define EXTERNAL_ILLUMINATION_COMPENSATION_SELECT_CURSOR_ADDERSS        0x4608	 //外界参数-湿度传感器-湿度校验补偿选择光标地址

#define EXTERNAL_ILLUMINATION_REF_SETTING_CURSOR_ADDERSS       	        0x4700  //外界参数-湿度传感器设置选择光标地址

#define EXTERNAL_ILLUMINATION_REAL_TIME_ONE_HUNDRED_THOUSAND_NUMBER_VAR_ADDERSS  0x4800  //外界参数-光照传感器-外界实时光照强度-十万位数字图标地址
#define EXTERNAL_ILLUMINATION_REAL_TIME_THEN_THOUSAND_NUMBER_VAR_ADDERSS         0x4801 //外界参数-光照传感器-外界实时光照强度-万位数字图标地址
#define EXTERNAL_ILLUMINATION_REAL_TIME_THOUSAND_NUMBER_VAR_ADDERSS              0x4802 //外界参数-光照传感器-外界实时光照强度-千位数字图标地址
#define EXTERNAL_ILLUMINATION_REAL_TIME_HUNDRED_NUMBER_VAR_ADDERSS               0x4803 //外界参数-光照传感器-外界实时光照强度-百位数字图标地址
#define EXTERNAL_ILLUMINATION_REAL_TIME_DIGITS_NUMBER_VAR_ADDERSS                0x4804 //外界参数-光照传感器-外界实时光照强度-十位数字图标地址
#define EXTERNAL_ILLUMINATION_REAL_TIME_DECADE_NUMBER_VAR_ADDERSS                0x4805 //外界参数-光照传感器-外界实时光照强度-十位数字图标地址

#define EXTERNAL_ILLUMINATION_REF_MIN_INPUT_SELECT_CURSOR_ADDERSS  					  0x4806	//外界参数-光照传感器-光照校验补偿输入参数选择光标地址
//#define EXTERNAL_ILLUMINATION_INTPUT_REF_MIN_INPUT_MINUS_VAR_ADDERSS      			  0x4807  //外界参数-光照传感器-最小光照校验补偿输入参负号图标地址
#define EXTERNAL_ILLUMINATION_INTPUT_REF_MIN_ONE_HUNDRED_THOUSAND_NUMBER_VAR_ADDERSS  0x4808  //外界参数-光照传感器-外界最小光照强度-输入参数十万位数字图标地址
#define EXTERNAL_ILLUMINATION_INTPUT_REF_MIN_THEN_THOUSAND_NUMBER_VAR_ADDERSS         0x4809 //外界参数-光照传感器-外界最小光照强度-输入参数万位数字图标地址
#define EXTERNAL_ILLUMINATION_INTPUT_REF_MIN_THOUSAND_NUMBER_VAR_ADDERSS              0x480A //外界参数-光照传感器-外界最小光照强度-输入参数千位数字图标地址
#define EXTERNAL_ILLUMINATION_INTPUT_REF_MIN_HUNDRED_NUMBER_VAR_ADDERSS               0x480B //外界参数-光照传感器-外界最小光照强度-输入参数百位数字图标地址
#define EXTERNAL_ILLUMINATION_INTPUT_REF_MIN_DIGITS_NUMBER_VAR_ADDERSS                0x480C //外界参数-光照传感器-外界最小光照强度-输入参数十位数字图标地址
#define EXTERNAL_ILLUMINATION_INTPUT_REF_MIN_DECADE_NUMBER_VAR_ADDERSS                0x480D //外界参数-光照传感器-外界最小光照强度-输入参数十位数字图标地址

#define EXTERNAL_ILLUMINATION_INTPUT_REF_MIN_WAIT_WINDOW_VAR_ADDERSS 	0x480E   //外界光照传感器温度最小光照设置保存参数等待弹窗
#define EXTERNAL_ILLUMINATION_INTPUT_REF_MIN_SUCCESS_WINDOW_VAR_ADDERSS 0x480F   //外界光照传感器温度最小光照设置保存参数成功弹窗
#define EXTERNAL_ILLUMINATION_INTPUT_REF_MIN_ERROR_WINDOW_VAR_ADDERSS 	0x481A   //外界光照传感器温度最小光照设置保存参数失败弹窗
#define EXTERNAL_ILLUMINATION_INTPUT_REF_MIN_SELECT_CURSOR_ADDERSS      0x481F	 //外界参数-光照传感器-最小光照校验补偿选择光标地址

#define EXTERNAL_ILLUMINATION_REF_MAX_INPUT_SELECT_CURSOR_ADDERSS  					  0x4906	//外界参数-光照传感器-光照校验补偿输入参数选择光标地址
//#define EXTERNAL_ILLUMINATION_INTPUT_REF_MAX_INPUT_MINUS_VAR_ADDERSS      			  0x4907  //外界参数-光照传感器-最大光照校验补偿输入参负号图标地址
#define EXTERNAL_ILLUMINATION_INTPUT_REF_MAX_ONE_HUNDRED_THOUSAND_NUMBER_VAR_ADDERSS  0x4908  //外界参数-光照传感器-外界最大光照强度-输入参数十万位数字图标地址
#define EXTERNAL_ILLUMINATION_INTPUT_REF_MAX_THEN_THOUSAND_NUMBER_VAR_ADDERSS         0x4909 //外界参数-光照传感器-外界最大光照强度-输入参数万位数字图标地址
#define EXTERNAL_ILLUMINATION_INTPUT_REF_MAX_THOUSAND_NUMBER_VAR_ADDERSS              0x490A //外界参数-光照传感器-外界最大光照强度-输入参数千位数字图标地址
#define EXTERNAL_ILLUMINATION_INTPUT_REF_MAX_HUNDRED_NUMBER_VAR_ADDERSS               0x490B //外界参数-光照传感器-外界最大光照强度-输入参数百位数字图标地址
#define EXTERNAL_ILLUMINATION_INTPUT_REF_MAX_DIGITS_NUMBER_VAR_ADDERSS                0x490C //外界参数-光照传感器-外界最大光照强度-输入参数十位数字图标地址
#define EXTERNAL_ILLUMINATION_INTPUT_REF_MAX_DECADE_NUMBER_VAR_ADDERSS                0x490D //外界参数-光照传感器-外界最大光照强度-输入参数个位数字图标地址

#define EXTERNAL_ILLUMINATION_INTPUT_REF_MAX_WAIT_WINDOW_VAR_ADDERSS 	0x490E   //外界光照传感器温度最大光照设置保存参数等待弹窗
#define EXTERNAL_ILLUMINATION_INTPUT_REF_MAX_SUCCESS_WINDOW_VAR_ADDERSS 0x490F   //外界光照传感器温度最大光照设置保存参数成功弹窗
#define EXTERNAL_ILLUMINATION_INTPUT_REF_MAX_ERROR_WINDOW_VAR_ADDERSS 	0x491A   //外界光照传感器温度最大光照设置保存参数失败弹窗
#define EXTERNAL_ILLUMINATION_INTPUT_REF_MAX_SELECT_CURSOR_ADDERSS      0x491F	 //外界参数-光照传感器-最大光照校验补偿选择光标地址


#define EXTERNAL_ILLUMINATION_SAMPLE_RATE_INPUT_SELECT_CURSOR_ADDERSS 0x4A00	//外界参数-光照传感器-湿度采样速率输入参数选择光标地址
#define EXTERNAL_ILLUMINATION_SAMPLE_RATE_DECADE_NUMBER_VAR_ADDERSS   0x4A02    //外界参数-光照传感器-湿度采样速率输入参数十位数字图标地址
#define EXTERNAL_ILLUMINATION_SAMPLE_RATE_DIGITS_NUMBER_VAR_ADDERSS   0x4A03    //外界参数-光照传感器-湿度采样速率输入参数个位数字图标地址

#define EXTERNAL_ILLUMINATION_SAMPLE_RATE_WAIT_WINDOW_VAR_ADDERSS     0x4A05    //外界光照传感器温度采样速率保存参数等待弹窗
#define EXTERNAL_ILLUMINATION_SAMPLE_RATE_SUCCESS_WINDOW_VAR_ADDERSS  0x4A06    //外界光照传感器温度采样速率保存参数成功弹窗
#define EXTERNAL_ILLUMINATION_SAMPLE_RATE_ERROR_WINDOW_VAR_ADDERSS 	  0x4A07    //外界光照传感器温度采样速率保存参数失败弹窗
#define EXTERNAL_ILLUMINATION_SAMPLE_RATE_SELECT_CURSOR_ADDERSS       0x4A08	//外界参数-光照传感器-光照采样速率选择光标地址


/*****************************外界雨雪传感器图标地址 ***********************************************/
/**************外界雨雪传感器-外界雨雪传感器设置地址图标*************************/
#define EXTERNAL_SLEET_DEV_SETTING_CURSOR_ADDERSS       	        	0x4AFF  //外界参数-雨雪传感器设置选择光标地址
/**************外界雨雪传感器-外界雨雪传感器设备地址复归地址图标*************************/
#define EXTERNAL_SLEET_DEV_ADDERSS_RESET_CURSOR_ADDERSS 				0x4B00   //外界参数-雨雪传感器-设备地址复归选择光标地址
#define EXTERNAL_SLEET_DEV_ADDR_RESET_WAIT_WINDOW_VAR_ADDERSS 			0x4B01   //外界雨雪传感器设备地址复归等待弹窗
#define EXTERNAL_SLEET_DEV_ADDR_RESET_SUCCESS_WINDOW_VAR_ADDERSS 		0x4B02   //外界雨雪传感器设备地址复归成功弹窗
#define EXTERNAL_SLEET_DEV_ADDR_RESET_ERROR_WINDOW_VAR_ADDERSS 			0x4B03   //外界雨雪传感器设备地址复归失败弹窗
/**************外界雨雪传感器-外界雨雪传感器灵敏度设置地址图标*************************/
#define EXTERNAL_SLEET_SENSITIVITY_THOUSAND_NUMBER_VAR_ADDERSS      	0x4C00  //外界参数-雨雪传感器-雨雪灵敏度当前灵敏度千位数字图标地址
#define EXTERNAL_SLEET_SENSITIVITY_HUNDREDS_NUMBER_VAR_ADDERSS  		0x4C01  //外界参数-雨雪传感器-雨雪灵敏度当前灵敏度百位数字图标地址
#define EXTERNAL_SLEET_SENSITIVITY_DIGITS_NUMBER_VAR_ADDERSS    		0x4C02  //外界参数-雨雪传感器-雨雪灵敏度当前灵敏度十位数字图标地址
#define EXTERNAL_SLEET_SENSITIVITY_DECADE_NUMBER_VAR_ADDERSS    		0x4C03  //外界参数-雨雪传感器-雨雪灵敏度当前灵敏度个位数字图标地址

#define EXTERNAL_SLEET_SENSITIVITY_INPUT_SELECT_CURSOR_ADDERSS  		0x4C04	//外界参数-雨雪传感器-雨雪灵敏度输入参数选择光标地址
#define EXTERNAL_SLEET_SENSITIVITY_INPUT_THOUSAND_NUMBER_VAR_ADDERSS    0x4C05  //外界参数-雨雪传感器-雨雪灵敏度输入参数千位数字图标地址
#define EXTERNAL_SLEET_SENSITIVITY_INPUT_HUNDREDS_NUMBER_VAR_ADDERSS  	0x4C06  //外界参数-雨雪传感器-雨雪灵敏度输入参数百位数字图标地址
#define EXTERNAL_SLEET_SENSITIVITY_INPUT_DIGITS_NUMBER_VAR_ADDERSS    	0x4C07  //外界参数-雨雪传感器-雨雪灵敏度输入参数十位数字图标地址
#define EXTERNAL_SLEET_SENSITIVITY_INPUT_DECADE_NUMBER_VAR_ADDERSS    	0x4C08  //外界参数-雨雪传感器-雨雪灵敏度输入参数个位数字图标地址

#define EXTERNAL_SLEET_SENSITIVITY_WAIT_WINDOW_VAR_ADDERSS 				0x4C09   //外界雨雪传感器雨雪灵敏度保存参数等待弹窗
#define EXTERNAL_SLEET_SENSITIVITY_SUCCESS_WINDOW_VAR_ADDERSS 			0x4C0A   //外界雨雪传感器雨雪灵敏度保存参数成功弹窗
#define EXTERNAL_SLEET_SENSITIVITY_ERROR_WINDOW_VAR_ADDERSS 			0x4C0B   //外界雨雪传感器雨雪灵敏度保存参数失败弹窗

#define EXTERNAL_SLEET_SENSITIVITY_SETTING_CURSOR_ADDERSS       	    0x4C1F  //外界参数-雨雪传感器灵敏度选择设置光标地址
/**************外界雨雪传感器-外界雨雪传感器加热温度设置地址图标*************************/
#define EXTERNAL_SLEET_HEATTING_SETTING_CURSOR_ADDERSS       	        0x4D00  //外界参数-雨雪传感器加热选择设置选择光标地址
/**************外界雨雪传感器-外界雨雪传感器加热温度下限设置地址图标*************************/
#define EXTERNAL_SLEET_HEATTING_LOW_LIMIT_SETTING_CURSOR_ADDERSS       	      0x4E09  //外界参数-湿度传感器加热下限设置选择光标地址

#define EXTERNAL_SLEET_SHOW_HEATTING_LOW_LIMIT_DECADE_NUMBER_VAR_ADDERSS      0x4E00 //外界参数-雨雪传感器-加热温度下限设置—当前加热下限个位数字图标地址
#define EXTERNAL_SLEET_SHOW_HEATTING_LOW_LIMIT_DIGITS_NUMBER_VAR_ADDERSS      0x4E01 //外界参数-雨雪传感器-加热温度下限设置-当前加热下限十位数字图标地址

#define EXTERNAL_SLEET_SENSITIVITY_LOW_LIMIT_INPUT_SELECT_CURSOR_ADDERSS  	  0x4E02 //外界参数-雨雪传感器-加热温度下限设置输入参数选择光标地址
#define EXTERNAL_SLEET_INTPUT_HEATTING_LOW_LIMIT_DECADE_NUMBER_VAR_ADDERSS    0x4E03 //外界参数-雨雪传感器-加热温度下限设置-输入框个位数字图标地址
#define EXTERNAL_SLEET_INTPUT_HEATTING_LOW_LIMIT_DIGITS_NUMBER_VAR_ADDERSS    0x4E04 //外界参数-雨雪传感器-加热温度下限设置-输入框十位数字图标地址

#define EXTERNAL_SLEET_INTPUT_HEATTING_LOW_LIMIT_WAIT_WINDOW_VAR_ADDERSS 	  0x4E05 //外界参数-雨雪传感器-加热温度下限设置保存参数等待弹窗
#define EXTERNAL_SLEET_INTPUT_HEATTING_LOW_LIMIT_SUCCESS_WINDOW_VAR_ADDERSS   0x4E06 //外界参数-雨雪传感器-加热温度下限设置保存参数成功弹窗
#define EXTERNAL_ISLEET_INTPUT_HEATTING_LOW_LIMIT_ERROR_WINDOW_VAR_ADDERSS 	  0x4E07 //外界参数-雨雪传感器-加热温度下限设置保存参数失败弹窗

/**************外界雨雪传感器-外界雨雪传感器加热温度上限设置地址图标*************************/
#define EXTERNAL_SLEET_HEATTING_HIGH_LIMIT_SETTING_CURSOR_ADDERSS       	  0x4F09  //外界参数-湿度传感器加热上限设置选择光标地址

#define EXTERNAL_SLEET_SHOW_HEATTING_HIGH_LIMIT_DECADE_NUMBER_VAR_ADDERSS     0x4F00 //外界参数-雨雪传感器-加热温度上限设置—当前加热下限个位数字图标地址
#define EXTERNAL_SLEET_SHOW_HEATTING_HIGH_LIMIT_DIGITS_NUMBER_VAR_ADDERSS     0x4F01 //外界参数-雨雪传感器-加热温度上限设置-当前加热下限十位数字图标地址

#define EXTERNAL_SLEET_SENSITIVITY_HIGH_LIMIT_INPUT_SELECT_CURSOR_ADDERSS  	  0x4F02 //外界参数-雨雪传感器-加热温度上限设置输入参数选择光标地址
#define EXTERNAL_SLEET_INTPUT_HEATTING_HIGH_LIMIT_DECADE_NUMBER_VAR_ADDERSS   0x4F03 //外界参数-雨雪传感器-加热温度上限设置-输入框个位数字图标地址
#define EXTERNAL_SLEET_INTPUT_HEATTING_HIGH_LIMIT_DIGITS_NUMBER_VAR_ADDERSS   0x4F04 //外界参数-雨雪传感器-加热温度上限设置-输入框十位数字图标地址

#define EXTERNAL_SLEET_INTPUT_HEATTING_HIGH_LIMIT_WAIT_WINDOW_VAR_ADDERSS 	  0x4F05 //外界参数-雨雪传感器-加热温度上限设置保存参数等待弹窗
#define EXTERNAL_SLEET_INTPUT_HEATTING_HIGH_LIMIT_SUCCESS_WINDOW_VAR_ADDERSS  0x4F06 //外界参数-雨雪传感器-加热温度上限设置保存参数成功弹窗
#define EXTERNAL_SLEET_INTPUT_HEATTING_HIGH_LIMIT_ERROR_WINDOW_VAR_ADDERSS    0x4F07 //外界参数-雨雪传感器-加热温度上限设置保存参数失败弹窗

/**************外界雨雪传感器-外界雨雪传感器报警复归延时设置地址图标*************************/
#define EXTERNAL_SLEET_DELAY_ALARM_RESET_SETTING_CURSOR_ADDERSS       	     0x500F  //外界参数-湿度传感器报警复归延时设置选择光标地址

#define EXTERNAL_SLEET_DELAY_ALARM_RESET_SHOW_THOUSAND_NUMBER_VAR_ADDERSS    0x5000  //外界参数-雨雪传感器-当前报警复归延时参数千位数字图标地址
#define EXTERNAL_SLEET_DELAY_ALARM_RESET_SHOW_HUNDREDS_NUMBER_VAR_ADDERSS  	 0x5001  //外界参数-雨雪传感器-当前报警复归延时参数百位数字图标地址
#define EXTERNAL_SLEET_DELAY_ALARM_RESET_SHOW_DIGITS_NUMBER_VAR_ADDERSS    	 0x5002  //外界参数-雨雪传感器-当前报警复归延时参数十位数字图标地址
#define EXTERNAL_SLEET_DELAY_ALARM_RESET_SHOW_DECADE_NUMBER_VAR_ADDERSS    	 0x5003  //外界参数-雨雪传感器-当前报警复归延时参数个位数字图标地址

#define EXTERNAL_SLEET_DELAY_ALARM_RESET_INPUT_SELECT_CURSOR_ADDERSS  	     0x5004  //外界参数-雨雪传感器-报警复归延时输入参数选择光标地址
#define EXTERNAL_SLEET_DELAY_ALARM_RESET_INTPUT_THOUSAND_NUMBER_VAR_ADDERSS  0x5005  //外界参数-雨雪传感器-报警复归延时输入参数千位数字图标地址
#define EXTERNAL_SLEET_DELAY_ALARM_RESET_INTPUT_HUNDREDS_NUMBER_VAR_ADDERSS  0x5006  //外界参数-雨雪传感器-报警复归延时输入参数百位数字图标地址
#define EXTERNAL_SLEET_DELAY_ALARM_RESET_INTPUT_DIGITS_NUMBER_VAR_ADDERSS    0x5007  //外界参数-雨雪传感器-报警复归延时输入参数十位数字图标地址
#define EXTERNAL_SLEET_DELAY_ALARM_RESET_INTPUT_DECADE_NUMBER_VAR_ADDERSS    0x5008  //外界参数-雨雪传感器-报警复归延时输入参数个位数字图标地址

#define EXTERNAL_SLEET_DELAY_ALARM_RESET_WAIT_WINDOW_VAR_ADDERSS 	 		 0x5009 //外界参数-雨雪传感器-报警复归延时设置保存参数等待弹窗
#define EXTERNAL_SLEET_DELAY_ALARM_RESET_SUCCESS_WINDOW_VAR_ADDERSS  		 0x500A //外界参数-雨雪传感器-报警复归延时设置保存参数成功弹窗
#define EXTERNAL_SLEET_DELAY_ALARM_RESET_ERROR_WINDOW_VAR_ADDERSS   		 0x500B //外界参数-雨雪传感器-报警复归延时设置保存参数失败弹窗

/**************外界雨雪传感器-外界雨雪传感器采集速率设置地址图标*************************/
#define EXTERNAL_SLEET_SAMPLE_RATE_SELECT_CURSOR_ADDERSS       		 		 0x5018	//外界参数-光照传感器-光照采样速率选择光标地址

#define EXTERNAL_SLEET_SAMPLE_RATE_INPUT_SELECT_CURSOR_ADDERSS 		 		 0x5010	//外界参数-光照传感器-光照采样速率输入参数选择光标地址
#define EXTERNAL_SLEET_SAMPLE_RATE_DECADE_NUMBER_VAR_ADDERSS   		 		 0x5012 //外界参数-光照传感器-光照采样速率输入参数十位数字图标地址
#define EXTERNAL_SLEET_SAMPLE_RATE_DIGITS_NUMBER_VAR_ADDERSS   		 		 0x5013 //外界参数-光照传感器-光照采样速率输入参数个位数字图标地址

#define EXTERNAL_SLEET_SAMPLE_RATE_WAIT_WINDOW_VAR_ADDERSS     		 		 0x5015 //外界光照传感器光照-采样速率保存参数等待弹窗
#define EXTERNAL_SLEET_SAMPLE_RATE_SUCCESS_WINDOW_VAR_ADDERSS  		 		 0x5016 //外界光照传感器光照-采样速率保存参数成功弹窗
#define EXTERNAL_SLEET_SAMPLE_RATE_ERROR_WINDOW_VAR_ADDERSS 	  		 	 0x5017 //外界光照传感器光照-采样速率保存参数失败弹窗

/*****************************内部参数选择设置指示图标地址***********************************************/
#define INTERNAL_TEMPERATURE_SET_CURSOR_ADDERSS  					0x5020 //内部参数-选择光标地址

/*****************************内部温度设置***********************************************/
#define INTERNAL_TEMP_DEV_SETTING_CURSOR_ADDERSS       				0x5030  //内界参数-温度传感器设置选择光标地址

#define INTERNAL_TEMP_DEV_ADDERSS_RESET_CURSOR_ADDERSS 				0x5040  //内界参数-温度传感器-设备地址复归选择光标地址
#define INTERNAL_TEMP_DEV_ADDR_RESET_WAIT_WINDOW_VAR_ADDERSS 		0x5041   //内界温度传感器设备地址复归等待弹窗
#define INTERNAL_TEMP_DEV_ADDR_RESET_SUCCESS_WINDOW_VAR_ADDERSS 	0x5042   //内界温度传感器设备地址复归成功弹窗
#define INTERNAL_TEMP_DEV_ADDR_RESET_ERROR_WINDOW_VAR_ADDERSS 		0x5043   //内界温度传感器设备地址复归失败弹窗

#define INTERNAL_TEMP_COMPENSATION_INPUT_SELECT_CURSOR_ADDERSS  	0x5050	//内界参数-温度传感器-温度校验补偿输入参数选择光标地址
#define INTERNAL_TEMP_COMPENSATION_INPUT_MINUS_VAR_ADDERSS     	 	0x5051  //内界参数-温度传感器-温度校验补偿输入参负号图标地址
#define INTERNAL_TEMP_COMPENSATION_DECADE_NUMBER_VAR_ADDERSS    	0x5052  //内界参数-温度传感器-温度校验补偿输入参数十位数字图标地址
#define INTERNAL_TEMP_COMPENSATION_DIGITS_NUMBER_VAR_ADDERSS    	0x5053  //内界参数-温度传感器-温度校验补偿输入参数个位数字图标地址

#define INTERNAL_TEMP_COMPENSATION_WAIT_WINDOW_VAR_ADDERSS 		  	0x5055   //内界温度传感器温度校验补偿保存参数等待弹窗
#define INTERNAL_TEMP_COMPENSATION_SUCCESS_WINDOW_VAR_ADDERSS 	  	0x5056   //内界温度传感器温度校验补偿保存参数成功弹窗
#define INTERNAL_TEMP_COMPENSATION_ERROR_WINDOW_VAR_ADDERSS 	  	0x5057   //内界温度传感器温度校验补偿保存参数失败弹窗
#define INTERNAL_TEMP_COMPENSATION_SELECT_CURSOR_ADDERSS          	0x5058	 //内界参数-温度传感器-温度校验补偿选择光标地址


#define INTERNAL_TEMP_ALARM_THERSHOLD_INPUT_SELECT_CURSOR_ADDERSS 	0x5060	 //内界参数-温度传感器-高温报警阈值输入参数选择光标地址
#define INTERNAL_TEMP_ALARM_THERSHOLD_DECADE_NUMBER_VAR_ADDERSS   	0x5062  //内界参数-温度传感器-高温报警阈值输入参数十位数字图标地址
#define INTERNAL_TEMP_ALARM_THERSHOLD_DIGITS_NUMBER_VAR_ADDERSS   	0x5063  //内界参数-温度传感器-高温报警阈值输入参数个位数字图标地址

#define INTERNAL_TEMP_ALARM_THERSHOLD_WAIT_WINDOW_VAR_ADDERSS     	0x5065   //内界温度传感器高温报警阈值保存参数等待弹窗
#define INTERNAL_TEMP_ALARM_THERSHOLD_SUCCESS_WINDOW_VAR_ADDERSS  	0x5066   //内界温度传感器高温报警阈值保存参数成功弹窗
#define INTERNAL_TEMP_ALARM_THERSHOLD_ERROR_WINDOW_VAR_ADDERSS 	  	0x5067   //内界温度传感器高温报警阈值保存参数失败弹窗
#define INTERNAL_TEMP_ALARM_THERSHOLD_SELECT_CURSOR_ADDERSS       	0x5068	//内界参数-温度传感器-高温报警阈值选择光标地址


#define INTERNAL_TEMP_SAMPLE_RATE_INPUT_SELECT_CURSOR_ADDERSS 	  	0x5070	//内界参数-温度传感器-温度采样速率输入参数选择光标地址
#define INTERNAL_TEMP_SAMPLE_RATE_DECADE_NUMBER_VAR_ADDERSS   	  	0x5072    //内界参数-温度传感器-温度采样速率输入参数十位数字图标地址
#define INTERNAL_TEMP_SAMPLE_RATE_DIGITS_NUMBER_VAR_ADDERSS       	0x5073    //内界参数-温度传感器-温度采样速率输入参数个位数字图标地址

#define INTERNAL_TEMP_SAMPLE_RATE_WAIT_WINDOW_VAR_ADDERSS         	0x5075    //内界温度传感器温度采样速率保存参数等待弹窗
#define INTERNAL_TEMP_SAMPLE_RATE_SUCCESS_WINDOW_VAR_ADDERSS      	0x5076    //内界温度传感器温度采样速率保存参数成功弹窗
#define INTERNAL_TEMP_SAMPLE_RATE_ERROR_WINDOW_VAR_ADDERSS 	     	0x5077    //内界温度传感器温度采样速率保存参数失败弹窗
#define INTERNAL_TEMP_SAMPLE_RATE_SELECT_CURSOR_ADDERSS           	0x5078	//内界参数-温度传感器-温度采样速率选择光标地址


/*****************************内部湿度设置***********************************************/
#define INTERNAL_HUMIDITY_DEV_SETTING_CURSOR_ADDERSS       				0x5080  //内部参数-湿度传感器设置选择光标地址

#define INTERNAL_HUMIDITY_DEV_ADDERSS_RESET_CURSOR_ADDERSS 				0x5090   //内部参数-湿度传感器-设备地址复归选择光标地址
#define INTERNAL_HUMIDITY_DEV_ADDR_RESET_WAIT_WINDOW_VAR_ADDERSS 		0x5091   //内部湿度传感器设备地址复归等待弹窗
#define INTERNAL_HUMIDITY_DEV_ADDR_RESET_SUCCESS_WINDOW_VAR_ADDERSS 	0x5092   //内部湿度传感器设备地址复归成功弹窗
#define INTERNAL_HUMIDITY_DEV_ADDR_RESET_ERROR_WINDOW_VAR_ADDERSS 		0x5093   //内部湿度传感器设备地址复归失败弹窗

#define INTERNAL_HUMIDITY_COMPENSATION_INPUT_SELECT_CURSOR_ADDERSS  	0x50A0	//内部参数-湿度传感器-湿度校验补偿输入参数选择光标地址
#define INTERNAL_HUMIDITY_COMPENSATION_INPUT_MINUS_VAR_ADDERSS      	0x50A1  //内部参数-湿度传感器-湿度校验补偿输入参负号图标地址
#define INTERNAL_HUMIDITY_COMPENSATION_DECADE_NUMBER_VAR_ADDERSS    	0x50A2  //内部参数-湿度传感器-湿度校验补偿输入参数十位数字图标地址
#define INTERNAL_HUMIDITY_COMPENSATION_DIGITS_NUMBER_VAR_ADDERSS    	0x50A3  //内部参数-湿度传感器-湿度校验补偿输入参数个位数字图标地址

#define INTERNAL_HUMIDITY_COMPENSATION_WAIT_WINDOW_VAR_ADDERSS 			0x50A5   //内部湿度传感器湿度校验补偿保存参数等待弹窗
#define INTERNAL_HUMIDITY_COMPENSATION_SUCCESS_WINDOW_VAR_ADDERSS 		0x50A6   //内部湿度传感器湿度校验补偿保存参数成功弹窗
#define INTERNAL_HUMIDITY_COMPENSATION_ERROR_WINDOW_VAR_ADDERSS 		0x50A7   //内部湿度传感器湿度校验补偿保存参数失败弹窗
#define INTERNAL_HUMIDITY_COMPENSATION_SELECT_CURSOR_ADDERSS        	0x50A8	 //内部参数-湿度传感器-湿度校验补偿选择光标地址


#define INTERNAL_HUMIDITY_ALARM_THERSHOLD_INPUT_SELECT_CURSOR_ADDERSS 	0x50B0  //内部参数-湿度传感器-湿度报警阈值输入参数选择光标地址
#define INTERNAL_HUMIDITY_ALARM_THERSHOLD_DECADE_NUMBER_VAR_ADDERSS   	0x50B2  //内部参数-湿度传感器-湿度报警阈值输入参数十位数字图标地址
#define INTERNAL_HUMIDITY_ALARM_THERSHOLD_DIGITS_NUMBER_VAR_ADDERSS   	0x50B3  //内部参数-湿度传感器-湿度报警阈值输入参数个位数字图标地址

#define INTERNAL_HUMIDITY_ALARM_THERSHOLD_WAIT_WINDOW_VAR_ADDERSS     	0x50B5   //内部湿度传感器湿度报警阈值保存参数等待弹窗
#define INTERNAL_HUMIDITY_ALARM_THERSHOLD_SUCCESS_WINDOW_VAR_ADDERSS  	0x50B6   //内部湿度传感器湿度报警阈值保存参数成功弹窗
#define INTERNAL_HUMIDITY_ALARM_THERSHOLD_ERROR_WINDOW_VAR_ADDERSS 	  	0x50B7   //内部湿度传感器湿度报警阈值保存参数失败弹窗
#define INTERNAL_HUMIDITY_ALARM_THERSHOLD_SELECT_CURSOR_ADDERSS       	0x50B8	//内部参数-湿度传感器-湿度报警阈值选择光标地址


#define INTERNAL_HUMIDITY_SAMPLE_RATE_INPUT_SELECT_CURSOR_ADDERSS 		0x50C0	//内部参数-湿度传感器-湿度采样速率输入参数选择光标地址
#define INTERNAL_HUMIDITY_SAMPLE_RATE_DECADE_NUMBER_VAR_ADDERSS   		0x50C2    //内部参数-湿度传感器-湿度采样速率输入参数十位数字图标地址
#define INTERNAL_HUMIDITY_SAMPLE_RATE_DIGITS_NUMBER_VAR_ADDERSS   		0x50C3    //内部参数-湿度传感器-湿度采样速率输入参数个位数字图标地址

#define INTERNAL_HUMIDITY_SAMPLE_RATE_WAIT_WINDOW_VAR_ADDERSS     		0x50C5    //内部湿度传感器湿度采样速率保存参数等待弹窗
#define INTERNAL_HUMIDITY_SAMPLE_RATE_SUCCESS_WINDOW_VAR_ADDERSS  		0x50C6    //内部湿度传感器湿度采样速率保存参数成功弹窗
#define INTERNAL_HUMIDITY_SAMPLE_RATE_ERROR_WINDOW_VAR_ADDERSS 	  		0x50C7    //内部湿度传感器湿度采样速率保存参数失败弹窗
#define INTERNAL_HUMIDITY_SAMPLE_RATE_SELECT_CURSOR_ADDERSS       		0x50C8	//内部参数-湿度传感器-湿度采样速率选择光标地址

/*****************************内部水浸设置***********************************************/
#define INTERNAL_WATER_DEV_SETTING_CURSOR_ADDERSS       			0x50D0  	//内部参数-水浸传感器设置选择光标地址

#define INTERNAL_WATER_SAMPLE_RATE_INPUT_SELECT_CURSOR_ADDERSS 		0x50E0		//内部参数-水浸传感器-水浸采样速率输入参数选择光标地址
#define INTERNAL_WATER_SAMPLE_RATE_DECADE_NUMBER_VAR_ADDERSS   		0x50E2    	//内部参数-水浸传感器-水浸采样速率输入参数十位数字图标地址
#define INTERNAL_WATER_SAMPLE_RATE_DIGITS_NUMBER_VAR_ADDERSS   		0x50E3    	//内部参数-水浸传感器-水浸采样速率输入参数个位数字图标地址

#define INTERNAL_WATER_SAMPLE_RATE_WAIT_WINDOW_VAR_ADDERSS     		0x50E5    	//内部水浸传感器水浸采样速率保存参数等待弹窗
#define INTERNAL_WATER_SAMPLE_RATE_SUCCESS_WINDOW_VAR_ADDERSS  		0x50E6    	//内部水浸传感器水浸采样速率保存参数成功弹窗
#define INTERNAL_WATER_SAMPLE_RATE_ERROR_WINDOW_VAR_ADDERSS    		0x50E7   	//内部水浸传感器水浸采样速率保存参数失败弹窗
#define INTERNAL_WATER_SAMPLE_RATE_SELECT_CURSOR_ADDERSS       		0x50E8		//内部参数-水浸传感器-水浸采样速率选择光标地址

/*****************************内部烟雾设置***********************************************/
#define INTERNAL_SMOKE_DEV_SETTING_CURSOR_ADDERSS       			0x50F0  	//内部参数-烟雾传感器设置选择光标地址

#define INTERNAL_SMOKE_SAMPLE_RATE_INPUT_SELECT_CURSOR_ADDERSS 		0x5100		//内部参数-烟雾传感器-烟雾采样速率输入参数选择光标地址
#define INTERNAL_SMOKE_SAMPLE_RATE_DECADE_NUMBER_VAR_ADDERSS   		0x5102    	//内部参数-烟雾传感器-烟雾采样速率输入参数十位数字图标地址
#define INTERNAL_SMOKE_SAMPLE_RATE_DIGITS_NUMBER_VAR_ADDERSS   		0x5103    	//内部参数-烟雾传感器-烟雾采样速率输入参数个位数字图标地址

#define INTERNAL_SMOKE_SAMPLE_RATE_WAIT_WINDOW_VAR_ADDERSS     		0x5105    	//内部烟雾传感器烟雾采样速率保存参数等待弹窗
#define INTERNAL_SMOKE_SAMPLE_RATE_SUCCESS_WINDOW_VAR_ADDERSS  		0x5106    	//内部烟雾传感器烟雾采样速率保存参数成功弹窗
#define INTERNAL_SMOKE_SAMPLE_RATE_ERROR_WINDOW_VAR_ADDERSS    		0x5107   	//内部烟雾传感器烟雾采样速率保存参数失败弹窗
#define INTERNAL_SMOKE_SAMPLE_RATE_SELECT_CURSOR_ADDERSS       		0x5108		//内部参数-烟雾传感器-烟雾采样速率选择光标地址


/*****************************系统参数选择设置指示图标地址***********************************************/
#define SYSTEM_SET_SELECT_CURSOR_ADDERSS  							0x5110 		//系统参数-选择光标地址

/*****************************系统参数-系统时间选择设置指示图标地址***********************************************/
#define SYSTEM_TIME_SET_SELECT_CURSOR_ADDERSS  						0x5120 		//系统参数-系统时间选择光标地址

/*****************************系统参数-系统时间-系统运行时间选择设置指示图标地址***********************************************/
#define SYSTEM_RUN_TIME_SET_SELECT_CURSOR_ADDERSS  					0x5130 		//系统参数-系统时间-系统运行时间选择光标地址

#define SYSTEM_RUN_TIME_INTPUT_SELECT_CURSOR_VAR_ADDERSS       		0x5134		//系统参数-系统时间-自系统运行时间输入参数选择光标地址

#define SYSTEM_RUN_TIME_ADJ_WAIT_WINDOW_VAR_ADDERSS     			0x5131    	//系统参数-系统时间-系统运行时间清零等待弹窗
#define SYSTEM_RUN_TIME_ADJ_SUCCESS_WINDOW_VAR_ADDERSS  			0x5132    	//系统参数-系统时间-系统运行时间清零成功弹窗
#define SYSTEM_RUN_TIME_ADJ_ERROR_WINDOW_VAR_ADDERSS    			0x5133   	//系统参数-系统时间-系统运行时间清零失败弹窗

#define SYSTEM_RUN_TIME_SAVEENV_WAIT_WINDOW_VAR_ADDERSS     		0x5134    	//系统参数-系统时间-系统运行时间保存参数等待弹窗
#define SYSTEM_RUN_TIME_SAVEENV_SUCCESS_WINDOW_VAR_ADDERSS  		0x5135    	//系统参数-系统时间-系统运行时间保存参数成功弹窗
#define SYSTEM_RUN_TIME_SAVEENV_ERROR_WINDOW_VAR_ADDERSS    		0x5136   	//系统参数-系统时间-系统运行时间保存参数失败弹窗

/*****************************系统参数-系统时间-自动返回主页时间选择设置指示图标地址***********************************************/
#define AUTO_EXIT_TIME_INTPUT_SELECT_CURSOR_VAR_ADDERSS       		0x5140		//系统参数-系统时间-自动返回主页时间输入参数选择光标地址
#define AUTO_EXIT_INTPUT_TIME_DECADE_NUMBER_VAR_ADDERSS   			0x5142    	//系统参数-系统时间-自动返回主页时间输入参数十位数字图标地址
#define AUTO_EXIT_INTPUT_TIME_DIGITS_NUMBER_VAR_ADDERSS   			0x5143    	//系统参数-系统时间-自动返回主页时间输入参数个位数字图标地址

#define AUTO_EXIT_TIME_WAIT_WINDOW_VAR_ADDERSS     					0x5145    	//系统参数-系统时间-自动返回主页保存参数等待弹窗
#define AUTO_EXIT_TIME_SUCCESS_WINDOW_VAR_ADDERSS  					0x5146    	//系统参数-系统时间-自动返回主页保存参数成功弹窗
#define AUTO_EXIT_TIME_ERROR_WINDOW_VAR_ADDERSS    					0x5147   	//系统参数-系统时间-自动返回主页保存参数失败弹窗

#define AUTO_EXIT_SET_PAGE_SELECT_CURSOR_ADDERSS  					0x5148 		//系统参数-系统时间-系统运行时间选择光标地址

/*****************************系统参数-系统时间-系统时钟选择设置指示图标地址***********************************************/
#define SYSTEM_TIME_INTPUT_SELECT_CURSOR_VAR_ADDERSS       			0x5150		//系统参数-系统时间-系统时钟输入参数选择光标地址
#define SYSTEM_TIME_INTPUT_YEARS_DIGITS_NUMBER_VAR_ADDERSS   		0x5151    	//系统参数-系统时间-系统时钟输入参数个位数字图标地址
#define SYSTEM_TIME_INTPUT_YEARS_DECADE_NUMBER_VAR_ADDERSS   		0x5152    	//系统参数-系统时间-系统时钟输入参数十位数字图标地址
#define SYSTEM_TIME_INTPUT_MONTH_DIGITS_NUMBER_VAR_ADDERSS   		0x5153    	//系统参数-系统时间-系统时钟输入参数个位数字图标地址
#define SYSTEM_TIME_INTPUT_MONTH_DECADE_NUMBER_VAR_ADDERSS   		0x5154    	//系统参数-系统时间-系统时钟输入参数十位数字图标地址
#define SYSTEM_TIME_INTPUT_DAYS_DIGITS_NUMBER_VAR_ADDERSS   		0x5155    	//系统参数-系统时间-系统时钟输入参数个位数字图标地址
#define SYSTEM_TIME_INTPUT_DAYS_DECADE_NUMBER_VAR_ADDERSS   		0x5156    	//系统参数-系统时间-系统时钟输入参数十位数字图标地址
#define SYSTEM_TIME_INTPUT_HOUR_DIGITS_NUMBER_VAR_ADDERSS   		0x5157    	//系统参数-系统时间-系统时钟输入参数个位数字图标地址
#define SYSTEM_TIME_INTPUT_HOUR_DECADE_NUMBER_VAR_ADDERSS   		0x5158    	//系统参数-系统时间-系统时钟输入参数十位数字图标地址
#define SYSTEM_TIME_INTPUT_MINUTE_DIGITS_NUMBER_VAR_ADDERSS   		0x5159    	//系统参数-系统时间-系统时钟输入参数个位数字图标地址
#define SYSTEM_TIME_INTPUT_MINUTE_DECADE_NUMBER_VAR_ADDERSS   		0x515A    	//系统参数-系统时间-系统时钟输入参数十位数字图标地址

#define SYSTEM_TIME_WAIT_WINDOW_VAR_ADDERSS     					0x515B    	//系统参数-系统时间-系统时钟保存参数等待弹窗
#define SYSTEM_TIME_SUCCESS_WINDOW_VAR_ADDERSS  					0x515C    	//系统参数-系统时间-系统时钟保存参数成功弹窗
#define SYSTEM_TIME_ERROR_WINDOW_VAR_ADDERSS    					0x515D   	//系统参数-系统时间-系统时钟保存参数失败弹窗

#define SYSTEM_TIME_PAGE_SELECT_CURSOR_ADDERSS  					0x515F 		//系统参数-系统时间-系统时钟选择光标地址

/*****************************系统参数-系统网络选择设置指示图标地址***********************************************/
#define SYSTEM_NETWORK_SET_SELECT_CURSOR_ADDERSS  					0x5160 		//系统参数-系统网络选择光标地址

/*****************************系统参数-系统网络-自动分配IP地址选择设置指示图标地址***********************************************/
#define SYSTEM_AUTO_IP_INTPUT_SELECT_CURSOR_VAR_ADDERSS       		0x5170		//系统参数-系系统网络-自动分配IP地址输入参数选择光标地址

#define SYSTEM_AUTO_IP_INDICATE_VAR_ADDERSS       					0x5171		//系统参数-系系统网络-自动分配IP指示图标地址
#define SYSTEM_AUTO_IP_WAIT_WINDOW_VAR_ADDERSS     					0x5172    	//系统参数-系系统网络-自动分配IP保存参数等待弹窗
#define SYSTEM_AUTO_IP_SUCCESS_WINDOW_VAR_ADDERSS  					0x5173    	//系统参数-系系统网络-自动分配IP保存参数成功弹窗
#define SYSTEM_AUTO_IP_ERROR_WINDOW_VAR_ADDERSS    					0x5174   	//系统参数-系系统网络-自动分配IP保存参数失败弹窗

#define SYSTEM_AUTO_SET_IP_SELECT_CURSOR_ADDERSS  					0x517F 		//系统参数-系统网络-自动分配IP地址选择光标地址

/*****************************系统参数-系统网络-使用设置IP地址选择设置指示图标地址***********************************************/
/*****************************系统参数-系统网络-使用设置IP地址-IP地址选择设置指示图标地址***********************************************/
#define SYSTEM_USER_IP_ADDR_INTPUT_SELECT_CURSOR_VAR_ADDERSS       	0x5180		//系统参数-系系统网络-手动分配IP地址输入参数选择光标地址
#define SYSTEM_USER_IP_ADDR1_INTPUT_DIGITS_NUMBER_VAR_ADDERSS   	0x5181    	//系统参数-系系统网络-手动分配IP地址1输入参数个位数字图标地址
#define SYSTEM_USER_IP_ADDR1_INTPUT_DECADE_NUMBER_VAR_ADDERSS   	0x5182    	//系统参数-系系统网络-手动分配IP地址1输入参数十位数字图标地址
#define SYSTEM_USER_IP_ADDR1_INTPUT_HUNDRED_NUMBER_VAR_ADDERSS   	0x5183    	//系统参数-系系统网络-手动分配IP地址1输入参数百位数字图标地址
#define SYSTEM_USER_IP_ADDR2_INTPUT_DIGITS_NUMBER_VAR_ADDERSS   	0x5184    	//系统参数-系系统网络-手动分配IP地址2输入参数个位数字图标地址
#define SYSTEM_USER_IP_ADDR2_INTPUT_DECADE_NUMBER_VAR_ADDERSS   	0x5185    	//系统参数-系系统网络-手动分配IP地址2输入参数十位数字图标地址
#define SYSTEM_USER_IP_ADDR2_INTPUT_HUNDRED_NUMBER_VAR_ADDERSS   	0x5186    	//系统参数-系系统网络-手动分配IP地址2输入参数百位数字图标地址
#define SYSTEM_USER_IP_ADDR3_INTPUT_DIGITS_NUMBER_VAR_ADDERSS   	0x5187    	//系统参数-系系统网络-手动分配IP地址3输入参数个位数字图标地址
#define SYSTEM_USER_IP_ADDR3_INTPUT_DECADE_NUMBER_VAR_ADDERSS   	0x5188    	//系统参数-系系统网络-手动分配IP地址3输入参数十位数字图标地址
#define SYSTEM_USER_IP_ADDR3_INTPUT_HUNDRED_NUMBER_VAR_ADDERSS   	0x5189    	//系统参数-系系统网络-手动分配IP地址3输入参数百位数字图标地址
#define SYSTEM_USER_IP_ADDR4_INTPUT_DIGITS_NUMBER_VAR_ADDERSS   	0x518A    	//系统参数-系系统网络-手动分配IP地址4输入参数个位数字图标地址
#define SYSTEM_USER_IP_ADDR4_INTPUT_DECADE_NUMBER_VAR_ADDERSS   	0x518B    	//系统参数-系系统网络-手动分配IP地址4输入参数十位数字图标地址
#define SYSTEM_USER_IP_ADDR4_INTPUT_HUNDRED_NUMBER_VAR_ADDERSS   	0x518C    	//系统参数-系系统网络-手动分配IP地址4输入参数百位数字图标地址

#define SYSTEM_USER_IP_ADDR_WAIT_WINDOW_VAR_ADDERSS     			0x518D    	//系统参数-系系统网络-手动分配IP保存参数等待弹窗
#define SYSTEM_USER_IP_ADDR_SUCCESS_WINDOW_VAR_ADDERSS  			0x518E    	//系统参数-系系统网络-手动分配IP保存参数成功弹窗
#define SYSTEM_USER_IP_ADDR_ERROR_WINDOW_VAR_ADDERSS    			0x518F   	//系统参数-系系统网络-手动分配IP保存参数失败弹窗
/*****************************系统参数-系统网络-使用设置IP地址-IP子网掩码选择设置指示图标地址***********************************************/
#define SYSTEM_USER_IP_MASK_INTPUT_SELECT_CURSOR_VAR_ADDERSS       	0x5190		//系统参数-系系统网络-手动分配IP子网掩码输入参数选择光标地址
#define SYSTEM_USER_IP_MASK1_INTPUT_DIGITS_NUMBER_VAR_ADDERSS   	0x5191    	//系统参数-系系统网络-手动分配IP子网掩码1输入参数个位数字图标地址
#define SYSTEM_USER_IP_MASK1_INTPUT_DECADE_NUMBER_VAR_ADDERSS   	0x5192    	//系统参数-系系统网络-手动分配IP子网掩码1输入参数十位数字图标地址
#define SYSTEM_USER_IP_MASK1_INTPUT_HUNDRED_NUMBER_VAR_ADDERSS   	0x5193    	//系统参数-系系统网络-手动分配IP子网掩码1输入参数百位数字图标地址
#define SYSTEM_USER_IP_MASK2_INTPUT_DIGITS_NUMBER_VAR_ADDERSS   	0x5194    	//系统参数-系系统网络-手动分配IP子网掩码2输入参数个位数字图标地址
#define SYSTEM_USER_IP_MASK2_INTPUT_DECADE_NUMBER_VAR_ADDERSS   	0x5195    	//系统参数-系系统网络-手动分配IP子网掩码2输入参数十位数字图标地址
#define SYSTEM_USER_IP_MASK2_INTPUT_HUNDRED_NUMBER_VAR_ADDERSS   	0x5196    	//系统参数-系系统网络-手动分配IP子网掩码2输入参数百位数字图标地址
#define SYSTEM_USER_IP_MASK3_INTPUT_DIGITS_NUMBER_VAR_ADDERSS   	0x5197    	//系统参数-系系统网络-手动分配IP子网掩码3输入参数个位数字图标地址
#define SYSTEM_USER_IP_MASK3_INTPUT_DECADE_NUMBER_VAR_ADDERSS   	0x5198    	//系统参数-系系统网络-手动分配IP子网掩码3输入参数十位数字图标地址
#define SYSTEM_USER_IP_MASK3_INTPUT_HUNDRED_NUMBER_VAR_ADDERSS   	0x5199    	//系统参数-系系统网络-手动分配IP子网掩码3输入参数百位数字图标地址
#define SYSTEM_USER_IP_MASK4_INTPUT_DIGITS_NUMBER_VAR_ADDERSS   	0x519A    	//系统参数-系系统网络-手动分配IP子网掩码4输入参数个位数字图标地址
#define SYSTEM_USER_IP_MASK4_INTPUT_DECADE_NUMBER_VAR_ADDERSS   	0x519B    	//系统参数-系系统网络-手动分配IP子网掩码4输入参数十位数字图标地址
#define SYSTEM_USER_IP_MASK4_INTPUT_HUNDRED_NUMBER_VAR_ADDERSS   	0x519C    	//系统参数-系系统网络-手动分配IP子网掩码4输入参数百位数字图标地址

#define SYSTEM_USER_IP_MASK_WAIT_WINDOW_VAR_ADDERSS     			0x519D    	//系统参数-系系统网络-手动分配子网掩码保存参数等待弹窗
#define SYSTEM_USER_IP_MASK_SUCCESS_WINDOW_VAR_ADDERSS  			0x519E    	//系统参数-系系统网络-手动分配子网掩码保存参数成功弹窗
#define SYSTEM_USER_IP_MASK_ERROR_WINDOW_VAR_ADDERSS    			0x519F   	//系统参数-系系统网络-手动分配子网掩码保存参数失败弹窗
/*****************************系统参数-系统网络-使用设置IP地址-IP网关选择设置指示图标地址***********************************************/
#define SYSTEM_USER_IP_GATEWAY_INTPUT_SELECT_CURSOR_VAR_ADDERSS     0x51A0		//系统参数-系系统网络-手动分配IP网关输入参数选择光标地址
#define SYSTEM_USER_IP_GATEWAY1_INTPUT_DIGITS_NUMBER_VAR_ADDERSS   	0x51B1    	//系统参数-系系统网络-手动分配IP网关1输入参数个位数字图标地址
#define SYSTEM_USER_IP_GATEWAY1_INTPUT_DECADE_NUMBER_VAR_ADDERSS   	0x51B2    	//系统参数-系系统网络-手动分配IP网关1输入参数十位数字图标地址
#define SYSTEM_USER_IP_GATEWAY1_INTPUT_HUNDRED_NUMBER_VAR_ADDERSS   0x51B3    	//系统参数-系系统网络-手动分配IP网关1输入参数百位数字图标地址
#define SYSTEM_USER_IP_GATEWAY2_INTPUT_DIGITS_NUMBER_VAR_ADDERSS   	0x51B4    	//系统参数-系系统网络-手动分配IP网关2输入参数个位数字图标地址
#define SYSTEM_USER_IP_GATEWAY2_INTPUT_DECADE_NUMBER_VAR_ADDERSS   	0x51B5    	//系统参数-系系统网络-手动分配IP网关2输入参数十位数字图标地址
#define SYSTEM_USER_IP_GATEWAY2_INTPUT_HUNDRED_NUMBER_VAR_ADDERSS   0x51B6    	//系统参数-系系统网络-手动分配IP网关2输入参数百位数字图标地址
#define SYSTEM_USER_IP_GATEWAY3_INTPUT_DIGITS_NUMBER_VAR_ADDERSS   	0x51B7    	//系统参数-系系统网络-手动分配IP网关3输入参数个位数字图标地址
#define SYSTEM_USER_IP_GATEWAY3_INTPUT_DECADE_NUMBER_VAR_ADDERSS   	0x51B8    	//系统参数-系系统网络-手动分配IP网关3输入参数十位数字图标地址
#define SYSTEM_USER_IP_GATEWAY3_INTPUT_HUNDRED_NUMBER_VAR_ADDERSS   0x51B9    	//系统参数-系系统网络-手动分配IP网关3输入参数百位数字图标地址
#define SYSTEM_USER_IP_GATEWAY4_INTPUT_DIGITS_NUMBER_VAR_ADDERSS   	0x51BA    	//系统参数-系系统网络-手动分配IP网关4输入参数个位数字图标地址
#define SYSTEM_USER_IP_GATEWAY4_INTPUT_DECADE_NUMBER_VAR_ADDERSS   	0x51BB    	//系统参数-系系统网络-手动分配IP网关4输入参数十位数字图标地址
#define SYSTEM_USER_IP_GATEWAY4_INTPUT_HUNDRED_NUMBER_VAR_ADDERSS   0x51BC    	//系统参数-系系统网络-手动分配IP网关4输入参数百位数字图标地址

#define SYSTEM_USER_IP_GATEWAY_WAIT_WINDOW_VAR_ADDERSS     			0x51BD    	//系统参数-系系统网络-手动分配网关保存参数等待弹窗
#define SYSTEM_USER_IP_GATEWAY_SUCCESS_WINDOW_VAR_ADDERSS  			0x51BE    	//系统参数-系系统网络-手动分配网关保存参数成功弹窗
#define SYSTEM_USER_IP_GATEWAY_ERROR_WINDOW_VAR_ADDERSS    			0x51BF   	//系统参数-系系统网络-手动分配网关保存参数失败弹窗

#define SYSTEM_USER_SET_IP_SELECT_CURSOR_ADDERSS  					0x51C0 		//系统参数-系统网络-手动分配IP选择光标地址

/*****************************系统参数-系统通信设置选择设置指示图标地址***********************************************/
#define SYSTEM_SYS_COMMUNICATE_SELECT_CURSOR_ADDERSS  				0x51D0 		//系统参数-系统通信设置选择图标

/*****************************系统参数-系统通信-服务端IP设置选择设置指示图标地址***********************************************/
#define SYSTEM_SYS_COMMUNICATE_SERVER_IP_INTPUT_SELECT_CURSOR_VAR_ADDERSS    		0x51D2		//系统参数-系统通信-服务端IP输入参数选择光标地址
#define SYSTEM_SYS_COMMUNICATE_SERVER_IP_ADDR1_INTPUT_DIGITS_NUMBER_VAR_ADDERSS   	0x51D3    	//系统参数-系系统网络-服务端IP地址1输入参数个位数字图标地址
#define SYSTEM_SYS_COMMUNICATE_SERVER_IP_ADDR1_INTPUT_DECADE_NUMBER_VAR_ADDERSS   	0x51D4    	//系统参数-系系统网络-服务端IP地址1输入参数十位数字图标地址
#define SYSTEM_SYS_COMMUNICATE_SERVER_IP_ADDR1_INTPUT_HUNDRED_NUMBER_VAR_ADDERSS   	0x51D5    	//系统参数-系系统网络-服务端IP地址1输入参数百位数字图标地址
#define SYSTEM_SYS_COMMUNICATE_SERVER_IP_ADDR2_INTPUT_DIGITS_NUMBER_VAR_ADDERSS   	0x51D6   	//系统参数-系系统网络-服务端IP地址2输入参数个位数字图标地址
#define SYSTEM_SYS_COMMUNICATE_SERVER_IP_ADDR2_INTPUT_DECADE_NUMBER_VAR_ADDERSS   	0x51D7    	//系统参数-系系统网络-服务端IP地址2输入参数十位数字图标地址
#define SYSTEM_SYS_COMMUNICATE_SERVER_IP_ADDR2_INTPUT_HUNDRED_NUMBER_VAR_ADDERSS   	0x51D8    	//系统参数-系系统网络-服务端IP地址2输入参数百位数字图标地址
#define SYSTEM_SYS_COMMUNICATE_SERVER_IP_ADDR3_INTPUT_DIGITS_NUMBER_VAR_ADDERSS   	0x51D9    	//系统参数-系系统网络-服务端IP地址3输入参数个位数字图标地址
#define SYSTEM_SYS_COMMUNICATE_SERVER_IP_ADDR3_INTPUT_DECADE_NUMBER_VAR_ADDERSS   	0x51DA    	//系统参数-系系统网络-服务端IP地址3输入参数十位数字图标地址
#define SYSTEM_SYS_COMMUNICATE_SERVER_IP_ADDR3_INTPUT_HUNDRED_NUMBER_VAR_ADDERSS   	0x51DB    	//系统参数-系系统网络-服务端IP地址3输入参数百位数字图标地址
#define SYSTEM_SYS_COMMUNICATE_SERVER_IP_ADDR4_INTPUT_DIGITS_NUMBER_VAR_ADDERSS   	0x51DC    	//系统参数-系系统网络-服务端IP地址4输入参数个位数字图标地址
#define SYSTEM_SYS_COMMUNICATE_SERVER_IP_ADDR4_INTPUT_DECADE_NUMBER_VAR_ADDERSS   	0x51DD    	//系统参数-系系统网络-服务端IP地址4输入参数十位数字图标地址
#define SYSTEM_SYS_COMMUNICATE_SERVER_IP_ADDR4_INTPUT_HUNDRED_NUMBER_VAR_ADDERSS   	0x51DE    	//系统参数-系系统网络-服务端IP地址4输入参数百位数字图标地址

#define SYSTEM_SYS_COMMUNICATE_SERVER_IP_ADDR_WAIT_WINDOW_VAR_ADDERSS     			0x51EA    	//系统参数-系系统网络-服务端IP保存参数等待弹窗
#define SYSTEM_SYS_COMMUNICATE_SERVER_IP_ADDR_SUCCESS_WINDOW_VAR_ADDERSS  			0x51EB   	//系统参数-系系统网络-服务端IP保存参数成功弹窗
#define SYSTEM_SYS_COMMUNICATE_SERVER_IP_ADDR_ERROR_WINDOW_VAR_ADDERSS    			0x51EC   	//系统参数-系系统网络-服务端IP保存参数失败弹窗

#define SYSTEM_SYS_COMMUNICATE_SERVER_IP_SELECT_CURSOR_ADDERSS  					0x51D1		//系统参数-系统通信-服务端IP设置选择图标

/*****************************系统参数-系统通信-系统通信端口设置选择设置指示图标地址***********************************************/
#define SYSTEM_SYS_COMMUNICATE_PORT_INTPUT_SELECT_CURSOR_VAR_ADDERSS    0x51E0		//系统参数-系统通信-系统通信端口输入参数选择光标地址
#define SYSTEM_SYS_COMMUNICATE_PORT_INTPUT_DECADE_NUMBER_VAR_ADDERSS  	0x51E1  	//系统参数-系统通信-系统通信端口输入参数个位数字图标地址
#define SYSTEM_SYS_COMMUNICATE_PORT_INTPUT_DIGITS_NUMBER_VAR_ADDERSS  	0x51E2  	//系统参数-系统通信-系统通信端口输入参数十位数字图标地址
#define SYSTEM_SYS_COMMUNICATE_PORT_INTPUT_HUNDREDS_NUMBER_VAR_ADDERSS  0x51E3  	//系统参数-系统通信-系统通信端口输入参数百位数字图标地址
#define SYSTEM_SYS_COMMUNICATE_PORT_INTPUT_THOUSAND_NUMBER_VAR_ADDERSS  0x51E4  	//系统参数-系统通信-系统通信端口输入参数千位数字图标地址

#define SYSTEM_SYS_COMMUNICATE_PORT_WAIT_WINDOW_VAR_ADDERSS     		0x51E5    	//系统参数-系统通信-系统通信端口保存参数等待弹窗
#define SYSTEM_SYS_COMMUNICATE_PORT_SUCCESS_WINDOW_VAR_ADDERSS  		0x51E6    	//系统参数-系统通信-系统通信端口保存参数成功弹窗
#define SYSTEM_SYS_COMMUNICATE_PORT_ERROR_WINDOW_VAR_ADDERSS    		0x51E7   	//系统参数-系统通信-系统通信端口保存参数失败弹窗

#define SYSTEM_SYS_COMMUNICATE_PORT_SELECT_CURSOR_ADDERSS  				0x51EF 		//系统参数-系统通信-系统通信端口设置选择图标
/*****************************系统参数-系统通信-系统通信ID设置选择设置指示图标地址***********************************************/
#define SYSTEM_SYS_COMMUNICATE_ID_INTPUT_SELECT_CURSOR_VAR_ADDERSS    	0x51F0	//系统参数-系统通信-系统通信ID输入参数选择光标地址
#define SYSTEM_SYS_COMMUNICATE_ID_INTPUT_DECADE_NUMBER_VAR_ADDERSS  	0x51F1  	//系统参数-系统通信-系统通信ID输入参数个位数字图标地址
#define SYSTEM_SYS_COMMUNICATE_ID_INTPUT_DIGITS_NUMBER_VAR_ADDERSS  	0x51F2  	//系统参数-系统通信-系统通信ID输入参数十位数字图标地址
#define SYSTEM_SYS_COMMUNICATE_ID_INTPUT_HUNDREDS_NUMBER_VAR_ADDERSS    0x51F3  	//系统参数-系统通信-系统通信ID输入参数百位数字图标地址
#define SYSTEM_SYS_COMMUNICATE_ID_INTPUT_THOUSAND_NUMBER_VAR_ADDERSS    0x51F4  	//系统参数-系统通信-系统通信ID输入参数千位数字图标地址

#define SYSTEM_SYS_COMMUNICATE_ID_WAIT_WINDOW_VAR_ADDERSS     		  	0x51F5    	//系统参数-系统通信-系统通信ID保存参数等待弹窗
#define SYSTEM_SYS_COMMUNICATE_ID_SUCCESS_WINDOW_VAR_ADDERSS  		  	0x51F6    	//系统参数-系统通信-系统通信ID保存参数成功弹窗
#define SYSTEM_SYS_COMMUNICATE_ID_ERROR_WINDOW_VAR_ADDERSS    		  	0x51F7   	//系统参数-系统通信-系统通信ID保存参数失败弹窗

#define SYSTEM_SYS_COMMUNICATE_ID_SELECT_CURSOR_ADDERSS  			  	0x51FF 		//系统参数-系统通信-系统通信端口设置选择图标

/*****************************系统参数-系统通信-系统登录密码设置选择设置指示图标地址***********************************************/
#define SYSTEM_SYS_COMMUNICATE_PASSWD_INTPUT_SELECT_CURSOR_VAR_ADDERSS    0x5200	//系统参数-系统通信-系统登录密码输入参数选择光标地址
#define SYSTEM_SYS_COMMUNICATE_PASSWD_INTPUT_1_NUMBER_VAR_ADDERSS  		  0x5201  	//系统参数-系统通信-系统登录密码第一位输入参数数字图标地址
#define SYSTEM_SYS_COMMUNICATE_PASSWD_INTPUT_2_NUMBER_VAR_ADDERSS  		  0x5202  	//系统参数-系统通信-系统登录密码第二位输入参数数字图标地址
#define SYSTEM_SYS_COMMUNICATE_PASSWD_INTPUT_3_NUMBER_VAR_ADDERSS  		  0x5203  	//系统参数-系统通信-系统登录密码第三位输入参数数字图标地址
#define SYSTEM_SYS_COMMUNICATE_PASSWD_INTPUT_4_NUMBER_VAR_ADDERSS  		  0x5204  	//系统参数-系统通信-系统登录密码第四位输入参数数字图标地址
#define SYSTEM_SYS_COMMUNICATE_PASSWD_INTPUT_5_NUMBER_VAR_ADDERSS  		  0x5205  	//系统参数-系统通信-系统登录密码第五位输入参数数字图标地址
#define SYSTEM_SYS_COMMUNICATE_PASSWD_INTPUT_6_NUMBER_VAR_ADDERSS  		  0x5206  	//系统参数-系统通信-系统登录密码第六位输入参数数字图标地址
#define SYSTEM_SYS_COMMUNICATE_PASSWD_INTPUT_7_NUMBER_VAR_ADDERSS  		  0x5207  	//系统参数-系统通信-系统登录密码第七位输入参数数字图标地址
#define SYSTEM_SYS_COMMUNICATE_PASSWD_INTPUT_8_NUMBER_VAR_ADDERSS  		  0x5208  	//系统参数-系统通信-系统登录密码第八位输入参数数字图标地址

#define SYSTEM_SYS_COMMUNICATE_PASSWD_WAIT_WINDOW_VAR_ADDERSS     		  0x5209    //系统参数-系统通信-系统登录密码保存参数等待弹窗
#define SYSTEM_SYS_COMMUNICATE_PASSWD_SUCCESS_WINDOW_VAR_ADDERSS  		  0x520A    //系统参数-系统通信-系统登录密码保存参数成功弹窗
#define SYSTEM_SYS_COMMUNICATE_PASSWD_ERROR_WINDOW_VAR_ADDERSS    		  0x520B   	//系统参数-系统通信-系统登录密码保存参数失败弹窗

#define SYSTEM_SYS_COMMUNICATE_PASSWD_SELECT_CURSOR_ADDERSS  			  0x520F 	//系统参数-系统通信-系系统登录密码设置选择图标

/*****************************系统参数-系统控制选择设置指示图标地址***********************************************/
#define SYSTEM_SYS_CONTROL_PAGE1_SELECT_CURSOR_ADDERSS  			  	 0x5210 	//系统参数-系统控制选择页面1设置选择图标
#define SYSTEM_SYS_CONTROL_PAGE2_SELECT_CURSOR_ADDERSS  			  	 0x5220 	//系统参数-系统控制选择页面1设置选择图标

/*****************************系统参数-系统控制-光照强度控制选择设置指示图标地址***********************************************/
#define SYSTEM_SYS_ILLUMINATION_CONTROL_SELECT_CURSOR_ADDERSS  			  0x5230 	//系统参数-系统控制-光照强度控制设置选择图标

/*****************************系统参数-系统控制-系统时间控制选择设置指示图标地址***********************************************/
#define SYSTEM_SYS_TIMER_CONTROL_SELECT_CURSOR_ADDERSS  			  	  0x5240 	//系统参数-系统控制-系统时间控制设置选择图标

/*****************************系统参数-系统控制-湿度差控制选择设置指示图标地址***********************************************/
#define SYSTEM_SYS_HUMIDITY_CONTROL_SELECT_CURSOR_ADDERSS  			  	  0x5250 	//系统参数-系统控制-湿度差控制设置选择图标
/*****************************系统参数-系统控制-温度控制选择设置指示图标地址***********************************************/
#define SYSTEM_SYS_TEMPERATURE_CONTROL_SELECT_CURSOR_ADDERSS  			  0x5260 	//系统参数-系统控制-温度控制设置选择图标

/*****************************系统参数-系统控制-盖板关闭延时选择设置指示图标地址***********************************************/
#define SYSTEM_SYS_CLOSE_DELAY_CONTROL_SELECT_CURSOR_ADDERSS  			  0x5270 	//系统参数-系统控制-盖板关闭延时控制设置选择图标
/*****************************系统参数-系统控制-盖板关闭延时选择设置指示图标地址***********************************************/
#define SYSTEM_SYS_DISPLAY_CONTROL_SELECT_CURSOR_ADDERSS  			  	  0x5280 	//系统参数-系统控制-系统时间控制设置选择图标

/*****************************系统参数-系统控制-光照强度-光照强度使能控制选择设置指示图标地址***********************************************/
#define SYSTEM_SYS_ILLUMINATION_CONTROL_ENAABLE_INTPUT_SELECT_CURSOR_VAR_ADDERSS    0x5290	//系统参数-系统控制-光照强度-光照强度使能输入参数选择光标地址
#define SYSTEM_SYS_ILLUMINATION_CONTROL_DISABLE_CURSOR_VAR_ADDERSS  	  			0x5291 	//系统参数-系统控制-光照强度-光照强度失能图标

#define SYSTEM_SYS_ILLUMINATION_CONTROL_ENAABLE_WAIT_WINDOW_VAR_ADDERSS     		0x5292    //系统参数-系统控制-光照强度-光照强度保存参数等待弹窗
#define SYSTEM_SYS_ILLUMINATION_CONTROL_ENAABLE_SUCCESS_WINDOW_VAR_ADDERSS  		0x5293    //系统参数-系统控制-光照强度-光照强度保存参数成功弹窗
#define SYSTEM_SYS_ILLUMINATION_CONTROL_ENAABLE_ERROR_WINDOW_VAR_ADDERSS    		0x5294   	//系统参数-系统控制-光照强度-光照强度保存参数失败弹窗

#define SYSTEM_SYS_ILLUMINATION_CONTROL_ENAABLE_SELECT_CURSOR_ADDERSS  	  			0x5295 	//系统参数-系统控制-光照强度-光照强度使能控制设置选择图标

/*****************************系统参数-系统控制-光照强度-光照强度关闭阈值设置指示图标地址***********************************************/
#define SYSTEM_ILLUMINATION_CONTROL_SHOW_CLOSE_VALUE_DECADE_NUMBER_VAR_ADDERSS  	0x52A0  	//系统参数-系统控制-光照强度关闭显示参数个位数字图标地址
#define SYSTEM_ILLUMINATION_CONTROL_SHOW_CLOSE_VALUE_DIGITS_NUMBER_VAR_ADDERSS  	0x52A1  	//系统参数-系统控制-光照强度关闭显示参数十位数字图标地址

#define SYSTEM_ILLUMINATION_CONTROL_CLOSE_VALUE_INTPUT_SELECT_CURSOR_VAR_ADDERSS    0x52A2		//系统参数-系统控制-光照强度-光照强度关闭输入参数选择光标地址

#define SYSTEM_ILLUMINATION_CONTROL_CLOSE_INTPUT_DECADE_NUMBER_VAR_ADDERSS  		0x52A3  	//系统参数-系统控制-光照强度关闭输入参数个位数字图标地址
#define SYSTEM_ILLUMINATION_CONTROL_CLOSE_INTPUT_DIGITS_NUMBER_VAR_ADDERSS  		0x52A4  	//系统参数-系统控制-光照强度关闭输入参数十位数字图标地址

#define SYSTEM_ILLUMINATION_CONTROL_CLOSE_WAIT_WINDOW_VAR_ADDERSS     				0x52A5    //系统参数-系统控制-光照强度关闭保存参数等待弹窗
#define SYSTEM_ILLUMINATION_CONTROL_CLOSE_SUCCESS_WINDOW_VAR_ADDERSS  				0x52A6    //系统参数-系统控制-光照强度关闭保存参数成功弹窗
#define SYSTEM_ILLUMINATION_CONTROL_CLOSE_ERROR_WINDOW_VAR_ADDERSS    				0x52A7    //系统参数-系统控制-光照强度关闭保存参数失败弹窗

#define SYSTEM_ILLUMINATION_CONTROL_CLOSE_SELECT_CURSOR_ADDERSS  			        0x52AF 	 //系统参数-系统控制-光照强度关闭设置选择图标

/*****************************系统参数-系统控制-光照强度-光照强度打开阈值设置指示图标地址***********************************************/
#define SYSTEM_ILLUMINATION_CONTROL_SHOW_OPEN_VALUE_DECADE_NUMBER_VAR_ADDERSS  		0x52B0  	//系统参数-系统控制-光照强度打开显示参数个位数字图标地址
#define SYSTEM_ILLUMINATION_CONTROL_SHOW_OPEN_VALUE_DIGITS_NUMBER_VAR_ADDERSS  		0x52B1  	//系统参数-系统控制-光照强度打开显示参数十位数字图标地址

#define SYSTEM_ILLUMINATION_CONTROL_OPEN_VALUE_INTPUT_SELECT_CURSOR_VAR_ADDERSS    	0x52B2		//系统参数-系统控制-光照强度-光照强度打开输入参数选择光标地址

#define SYSTEM_ILLUMINATION_CONTROL_OPEN_INTPUT_DECADE_NUMBER_VAR_ADDERSS  			0x52B3  	//系统参数-系统控制-光照强度打开输入参数个位数字图标地址
#define SYSTEM_ILLUMINATION_CONTROL_OPEN_INTPUT_DIGITS_NUMBER_VAR_ADDERSS  			0x52B4  	//系统参数-系统控制-光照强度打开输入参数十位数字图标地址

#define SYSTEM_ILLUMINATION_CONTROL_OPEN_WAIT_WINDOW_VAR_ADDERSS     				0x52B5    //系统参数-系统控制-光照强度打开保存参数等待弹窗
#define SYSTEM_ILLUMINATION_CONTROL_OPEN_SUCCESS_WINDOW_VAR_ADDERSS  				0x52B6    //系统参数-系统控制-光照强度打开保存参数成功弹窗
#define SYSTEM_ILLUMINATION_CONTROL_OPEN_ERROR_WINDOW_VAR_ADDERSS    				0x52B7    //系统参数-系统控制-光照强度打开保存参数失败弹窗

#define SYSTEM_ILLUMINATION_CONTROL_OPEN_SELECT_CURSOR_ADDERSS  			        0x52BF 	 //系统参数-系统控制-光照强度打开设置选择图标


/*****************************系统参数-系统控制-系统时间-系统时间使能控制选择设置指示图标地址***********************************************/
#define SYSTEM_SYS_TIMER_CONTROL_ENAABLE_INTPUT_SELECT_CURSOR_VAR_ADDERSS			0x52C0		//系统参数-系统控制-系统时间-系统时间使能输入参数选择光标地址
#define SYSTEM_SYS_TIMER_CONTROL_DISABLE_CURSOR_VAR_ADDERSS  	  					0x52C1 		//系统参数-系统控制-系统时间-系统时间失能图标

#define SYSTEM_SYS_TIMER_CONTROL_ENAABLE_WAIT_WINDOW_VAR_ADDERSS     				0x52C2    	//系统参数-系统控制-系统时间-系统时间使能保存参数等待弹窗
#define SYSTEM_SYS_TIMER_CONTROL_ENAABLE_SUCCESS_WINDOW_VAR_ADDERSS  				0x52C3    	//系统参数-系统控制-系统时间-系统时间使能保存参数成功弹窗
#define SYSTEM_SYS_TIMER_CONTROL_ENAABLE_ERROR_WINDOW_VAR_ADDERSS    				0x52C4   	//系统参数-系统控制-系统时间-系统时间使能保存参数失败弹窗

#define SYSTEM_SYS_TIMER_CONTROL_ENAABLE_SELECT_CURSOR_ADDERSS  	  				0x52CF 		//系统参数-系统控制-系统时间-系统时间使能控制设置选择图标


/*****************************系统参数-系统控制-系统时间-系统时间上午打开设置指示图标地址***********************************************/
#define SYSTEM_TIMER_AM_OPEN_CONTROL_INTPUT_SELECT_CURSOR_VAR_ADDERSS   			0x52D0		//系统参数-系统控制-系统时间-系统时间关闭输入参数选择光标地址

#define SYSTEM_TIMER_AM_OPEN_CONTROL_CLOSE_INTPUT_DECADE_NUMBER_VAR_ADDERSS  		0x52D1  	//系统参数-系统控制-系统时间关闭输入参数个位数字图标地址
#define SYSTEM_TIMER_AM_OPEN_CONTROL_CLOSE_INTPUT_DIGITS_NUMBER_VAR_ADDERSS  		0x52D2  	//系统参数-系统控制-系统时间关闭输入参数十位数字图标地址

#define SYSTEM_TIMER_AM_OPEN_CONTROL_CLOSE_WAIT_WINDOW_VAR_ADDERSS     				0x52D3    	//系统参数-系统控制-系统时间关闭保存参数等待弹窗
#define SYSTEM_TIMER_AM_OPEN_CONTROL_CLOSE_SUCCESS_WINDOW_VAR_ADDERSS  				0x52D4    	//系统参数-系统控制-系统时间关闭保存参数成功弹窗
#define SYSTEM_TIMER_AM_OPEN_CONTROL_CLOSE_ERROR_WINDOW_VAR_ADDERSS    				0x52D5    	//系统参数-系统控制-系统时间关闭保存参数失败弹窗

#define SYSTEM_TIMER_AM_OPEN_CONTROL_CLOSE_SELECT_CURSOR_ADDERSS  			        0x52DF 	 	//系统参数-系统控制-系统时间关闭设置选择图标


/*****************************系统参数-系统控制-系统时间-系统时间下午打开设置指示图标地址***********************************************/
#define SYSTEM_TIMER_PM_OPEN_CONTROL_INTPUT_SELECT_CURSOR_VAR_ADDERSS   			0x52E0		//系统参数-系统控制-系统时间-系统时间关闭输入参数选择光标地址

#define SYSTEM_TIMER_PM_OPEN_CONTROL_CLOSE_INTPUT_DECADE_NUMBER_VAR_ADDERSS  		0x52E1  	//系统参数-系统控制-系统时间关闭输入参数个位数字图标地址
#define SYSTEM_TIMER_PM_OPEN_CONTROL_CLOSE_INTPUT_DIGITS_NUMBER_VAR_ADDERSS  		0x52E2  	//系统参数-系统控制-系统时间关闭输入参数十位数字图标地址

#define SYSTEM_TIMER_PM_OPEN_CONTROL_CLOSE_WAIT_WINDOW_VAR_ADDERSS     				0x52E3    	//系统参数-系统控制-系统时间关闭保存参数等待弹窗
#define SYSTEM_TIMER_PM_OPEN_CONTROL_CLOSE_SUCCESS_WINDOW_VAR_ADDERSS  				0x52E4    	//系统参数-系统控制-系统时间关闭保存参数成功弹窗
#define SYSTEM_TIMER_PM_OPEN_CONTROL_CLOSE_ERROR_WINDOW_VAR_ADDERSS    				0x52E5    	//系统参数-系统控制-系统时间关闭保存参数失败弹窗

#define SYSTEM_TIMER_PM_OPEN_CONTROL_CLOSE_SELECT_CURSOR_ADDERSS  			        0x52EF 	 	//系统参数-系统控制-系统时间关闭设置选择图标

/*****************************系统参数-系统控制-湿度差控制-湿度差控制关闭设置指示图标地址***********************************************/
#define SYSTEM_HUMIDITY_CLOSE_CONTROL_INTPUT_SELECT_CURSOR_VAR_ADDERSS   			0x52F0		//系统参数-系统控制-湿度差控制-湿度差控制关闭输入参数选择光标地址

#define SYSTEM_HUMIDITY_CLOSE_CONTROL_INTPUT_DECADE_NUMBER_VAR_ADDERSS  			0x52F1  	//系统参数-系统控制-湿度差控制关闭输入参数个位数字图标地址
#define SYSTEM_HUMIDITY_CLOSE_CONTROL_INTPUT_DIGITS_NUMBER_VAR_ADDERSS  			0x52F2  	//系统参数-系统控制-湿度差控制关闭输入参数十位数字图标地址

#define SYSTEM_HUMIDITY_CLOSE_CONTROL_WAIT_WINDOW_VAR_ADDERSS     					0x52F3    	//系统参数-系统控制-湿度差控制关闭保存参数等待弹窗
#define SYSTEM_HUMIDITY_CLOSE_CONTROL_SUCCESS_WINDOW_VAR_ADDERSS  					0x52F4    	//系统参数-系统控制-湿度差控制关闭保存参数成功弹窗
#define SYSTEM_HUMIDITY_CLOSE_CONTROL_ERROR_WINDOW_VAR_ADDERSS    					0x52F5    	//系统参数-系统控制-湿度差控制关闭保存参数失败弹窗

#define SYSTEM_HUMIDITY_CLOSE_CONTROL_SELECT_CURSOR_ADDERSS  			        	0x52FF 	 	//系统参数-系统控制-湿度差控制关闭设置选择图标


/*****************************系统参数-系统控制-湿度差控制-湿度差控制打开设置指示图标地址***********************************************/
#define SYSTEM_HUMIDITY_OPEN_CONTROL_INTPUT_SELECT_CURSOR_VAR_ADDERSS   			0x5300		//系统参数-系统控制-湿度差控制-湿度差控制关闭输入参数选择光标地址

#define SYSTEM_HUMIDITY_OPEN_CONTROL_INTPUT_DECADE_NUMBER_VAR_ADDERSS  				0x5301  	//系统参数-系统控制-湿度差控制关闭输入参数个位数字图标地址
#define SYSTEM_HUMIDITY_OPEN_CONTRO_INTPUT_DIGITS_NUMBER_VAR_ADDERSS  				0x5302  	//系统参数-系统控制-湿度差控制关闭输入参数十位数字图标地址

#define SYSTEM_HUMIDITY_OPEN_CONTROL_WAIT_WINDOW_VAR_ADDERSS     					0x5303    	//系统参数-系统控制-湿度差控制关闭保存参数等待弹窗
#define SYSTEM_HUMIDITY_OPEN_CONTROL_SUCCESS_WINDOW_VAR_ADDERSS  					0x5304    	//系统参数-系统控制-湿度差控制关闭保存参数成功弹窗
#define SYSTEM_HUMIDITY_OPEN_CONTROL_ERROR_WINDOW_VAR_ADDERSS    					0x5305    	//系统参数-系统控制-湿度差控制关闭保存参数失败弹窗

#define SYSTEM_HUMIDITY_OPEN_CONTROL_SELECT_CURSOR_ADDERSS  			        	0x530F 	 	//系统参数-系统控制-湿度差控制关闭设置选择图标

/*****************************系统参数-系统控制-温度控制-内部温度控制关闭设置指示图标地址***********************************************/
#define SYSTEM_IN_TEMPERATURE_CLOSE_CONTROL_INTPUT_SELECT_CURSOR_VAR_ADDERSS   		0x5310		//系统参数-系统控制-温度控制-内部温度控制关闭输入参数选择光标地址

#define SYSTEM_IN_TEMPERATURE_CLOSE_CONTROL_INTPUT_DECADE_NUMBER_VAR_ADDERSS  		0x5311  	//系统参数-系统控制-内部温度控制关闭输入参数个位数字图标地址
#define SYSTEM_IN_TEMPERATURE_CLOSE_CONTROL_INTPUT_DIGITS_NUMBER_VAR_ADDERSS  		0x5312  	//系统参数-系统控制-内部温度控制关闭输入参数十位数字图标地址

#define SYSTEM_IN_TEMPERATURE_CLOSE_CONTROL_WAIT_WINDOW_VAR_ADDERSS     			0x5313    	//系统参数-系统控制-内部温度控制关闭保存参数等待弹窗
#define SYSTEM_IN_TEMPERATURE_CLOSE_CONTROL_SUCCESS_WINDOW_VAR_ADDERSS  			0x5314    	//系统参数-系统控制-内部温度控制关闭保存参数成功弹窗
#define SYSTEM_IN_TEMPERATURE_CLOSE_CONTROL_ERROR_WINDOW_VAR_ADDERSS    			0x5315    	//系统参数-系统控制-内部温度控制关闭保存参数失败弹窗

#define SYSTEM_IN_TEMPERATURE_CLOSE_CONTROL_SELECT_CURSOR_ADDERSS  			        0x531F 	 	//系统参数-系统控制-内部温度控制关闭设置选择图标
/*****************************系统参数-系统控制-温度控制-外界温度控制关闭设置指示图标地址***********************************************/
#define SYSTEM_EX_TEMPERATURE_CLOSE_CONTROL_INTPUT_SELECT_CURSOR_VAR_ADDERSS   		0x5320		//系统参数-系统控制-温度控制-外界温度控制关闭输入参数选择光标地址

#define SYSTEM_EX_TEMPERATURE_CLOSE_CONTROL_INTPUT_DECADE_NUMBER_VAR_ADDERSS  		0x5321  	//系统参数-系统控制-外界温度控制关闭输入参数个位数字图标地址
#define SYSTEM_EX_TEMPERATURE_CLOSE_CONTROL_INTPUT_DIGITS_NUMBER_VAR_ADDERSS  		0x5322  	//系统参数-系统控制-外界温度控制关闭输入参数十位数字图标地址

#define SYSTEM_EX_TEMPERATURE_CLOSE_CONTROL_WAIT_WINDOW_VAR_ADDERSS     			0x5323    	//系统参数-系统控制-外界温度控制关闭保存参数等待弹窗
#define SYSTEM_EX_TEMPERATURE_CLOSE_CONTROL_SUCCESS_WINDOW_VAR_ADDERSS  			0x5324    	//系统参数-系统控制-外界温度控制关闭保存参数成功弹窗
#define SYSTEM_EX_TEMPERATURE_CLOSE_CONTROL_ERROR_WINDOW_VAR_ADDERSS    			0x5325    	//系统参数-系统控制-外界温度控制关闭保存参数失败弹窗

#define SYSTEM_EX_TEMPERATURE_CLOSE_CONTROL_SELECT_CURSOR_ADDERSS  			        0x532F 	 	//系统参数-系统控制-外界温度控制关闭设置选择图标
/*****************************系统参数-系统控制-温度控制-温度差控制关闭设置指示图标地址***********************************************/
#define SYSTEM_TEMPERATURE_DIFFERENCE_CLOSE_CONTROL_INTPUT_SELECT_CURSOR_VAR_ADDERSS   	0x5330		//系统参数-系统控制-温度控制--温度差控制关闭输入参数选择光标地址

#define SYSTEM_TEMPERATURE_DIFFERENCE_CLOSE_CONTROL_INTPUT_DECADE_NUMBER_VAR_ADDERSS  	0x5331  	//系统参数-系统控制--温度差控制关闭输入参数个位数字图标地址
#define SYSTEM_TEMPERATURE_DIFFERENCE_CLOSE_CONTROL_INTPUT_DIGITS_NUMBER_VAR_ADDERSS  	0x5332  	//系统参数-系统控制--温度差控制关闭输入参数十位数字图标地址

#define SYSTEM_TEMPERATURE_DIFFERENCE_CLOSE_CONTROL_WAIT_WINDOW_VAR_ADDERSS     		0x5333    	//系统参数-系统控制--温度差控制关闭保存参数等待弹窗
#define SYSTEM_TEMPERATURE_DIFFERENCE_CLOSE_CONTROL_SUCCESS_WINDOW_VAR_ADDERSS  		0x5334    	//系统参数-系统控制--温度差控制关闭保存参数成功弹窗
#define SYSTEM_TEMPERATURE_DIFFERENCE_CLOSE_CONTROL_ERROR_WINDOW_VAR_ADDERSS    		0x5335    	//系统参数-系统控制--温度差控制关闭保存参数失败弹窗

#define SYSTEM_TEMPERATURE_DIFFERENCE_CLOSE_CONTROL_SELECT_CURSOR_ADDERSS  			    0x533F 	 	//系统参数-系统控制--温度差控制关闭设置选择图标
/*****************************系统参数-系统控制-温度控制-温度差控制打开设置指示图标地址***********************************************/
#define SYSTEM_TEMPERATURE_DIFFERENCE_OPEN_CONTROL_INTPUT_SELECT_CURSOR_VAR_ADDERSS   	0x5340		//系统参数-系统控制-温度控制--温度差控制打开输入参数选择光标地址

#define SYSTEM_TEMPERATURE_DIFFERENCE_OPEN_CONTROL_INTPUT_DECADE_NUMBER_VAR_ADDERSS  	0x5341  	//系统参数-系统控制--温度差控制打开输入参数个位数字图标地址
#define SYSTEM_TEMPERATURE_DIFFERENCE_OPEN_CONTROL_INTPUT_DIGITS_NUMBER_VAR_ADDERSS  	0x5342  	//系统参数-系统控制--温度差控制打开输入参数十位数字图标地址

#define SYSTEM_TEMPERATURE_DIFFERENCE_OPEN_CONTROL_WAIT_WINDOW_VAR_ADDERSS     			0x5343    	//系统参数-系统控制--温度差控制打开保存参数等待弹窗
#define SYSTEM_TEMPERATURE_DIFFERENCE_OPEN_CONTROL_SUCCESS_WINDOW_VAR_ADDERSS  			0x5344    	//系统参数-系统控制--温度差控制打开保存参数成功弹窗
#define SYSTEM_TEMPERATURE_DIFFERENCE_OPEN_CONTROL_ERROR_WINDOW_VAR_ADDERSS    			0x5345    	//系统参数-系统控制--温度差控制打开保存参数失败弹窗

#define SYSTEM_TEMPERATURE_DIFFERENCE_OPEN_CONTROL_SELECT_CURSOR_ADDERSS  			    0x534F 	 	//系统参数-系统控制--温度差控制打开设置选择图标

/*****************************系统参数-系统控制-延时关闭-温度延时关闭指示图标地址***********************************************/
#define SYSTEM_TEMPERATURE_DELAY_CLOSE_CONTROL_INTPUT_SELECT_CURSOR_VAR_ADDERSS   		0x5350		//系统参数-系统控制-延时关闭--温度延时关闭打开输入参数选择光标地址

#define SYSTEM_TEMPERATURE_DELAY_CLOSE_CONTROL_INTPUT_DECADE_NUMBER_VAR_ADDERSS  		0x5351  	//系统参数-系统控制--温度延时关闭打开输入参数个位数字图标地址
#define SYSTEM_TEMPERATURE_DELAY_CLOSE_CONTROL_INTPUT_DIGITS_NUMBER_VAR_ADDERSS  		0x5352  	//系统参数-系统控制--温度延时关闭打开输入参数十位数字图标地址
#define SYSTEM_TEMPERATURE_DELAY_CLOSE_CONTROL_INTPUT_HUNDREDS_NUMBER_VAR_ADDERSS  		0x5353  	//系统参数-系统控制--温度延时关闭打开输入参数百位数字图标地址

#define SYSTEM_TEMPERATURE_DELAY_CLOSE_CONTROL_WAIT_WINDOW_VAR_ADDERSS     				0x5354    	//系统参数-系统控制--温度延时关闭打开保存参数等待弹窗
#define SYSTEM_TEMPERATURE_DELAY_CLOSE_CONTROL_SUCCESS_WINDOW_VAR_ADDERSS  				0x5355    	//系统参数-系统控制--温度延时关闭打开保存参数成功弹窗
#define SYSTEM_TEMPERATURE_DELAY_CLOSE_CONTROL_ERROR_WINDOW_VAR_ADDERSS    				0x5356    	//系统参数-系统控制--温度延时关闭打开保存参数失败弹窗

#define SYSTEM_TEMPERATURE_DELAY_CLOSE_CONTROL_SELECT_CURSOR_ADDERSS  			    	0x535F 	 	//系统参数-系统控制--温度延时关闭打开设置选择图标

/*****************************系统参数-系统控制-延时关闭-湿度延时关闭指示图标地址***********************************************/
#define SYSTEM_HUMIDITY_DELAY_CLOSE_CONTROL_INTPUT_SELECT_CURSOR_VAR_ADDERSS   			0x5360		//系统参数-系统控制-延时关闭--湿度延时关闭打开输入参数选择光标地址

#define SYSTEM_HUMIDITY_DELAY_CLOSE_CONTROL_INTPUT_DECADE_NUMBER_VAR_ADDERSS  			0x5361  	//系统参数-系统控制--湿度延时关闭打开输入参数个位数字图标地址
#define SYSTEM_HUMIDITY_DELAY_CLOSE_CONTROL_INTPUT_DIGITS_NUMBER_VAR_ADDERSS  			0x5362  	//系统参数-系统控制--湿度延时关闭打开输入参数十位数字图标地址
#define SYSTEM_HUMIDITY_DELAY_CLOSE_CONTROL_INTPUT_HUNDREDS_NUMBER_VAR_ADDERSS  		0x5363  	//系统参数-系统控制--湿度延时关闭打开输入参数百位数字图标地址

#define SYSTEM_HUMIDITY_DELAY_CLOSE_CONTROL_WAIT_WINDOW_VAR_ADDERSS     				0x5364    	//系统参数-系统控制--湿度延时关闭打开保存参数等待弹窗
#define SYSTEM_HUMIDITY_DELAY_CLOSE_CONTROL_SUCCESS_WINDOW_VAR_ADDERSS  				0x5365    	//系统参数-系统控制--湿度延时关闭打开保存参数成功弹窗
#define SYSTEM_HUMIDITY_DELAY_CLOSE_CONTROL_ERROR_WINDOW_VAR_ADDERSS    				0x5366    	//系统参数-系统控制--湿度延时关闭打开保存参数失败弹窗

#define SYSTEM_HUMIDITY_DELAY_CLOSE_CONTROL_SELECT_CURSOR_ADDERSS  			    		0x536F 	 	//系统参数-系统控制--湿度延时关闭打开设置选择图标

/*****************************系统参数-系统控制-延时关闭-光照延时关闭指示图标地址***********************************************/
#define SYSTEM_ILLUMIAATION_DELAY_CLOSE_CONTROL_INTPUT_SELECT_CURSOR_VAR_ADDERSS   		0x5370		//系统参数-系统控制-延时关闭--光照延时关闭打开输入参数选择光标地址

#define SYSTEM_ILLUMIAATION_DELAY_CLOSE_CONTROL_INTPUT_DECADE_NUMBER_VAR_ADDERSS  		0x5371  	//系统参数-系统控制--光照延时关闭打开输入参数个位数字图标地址
#define SYSTEM_ILLUMIAATION_DELAY_CLOSE_CONTROL_INTPUT_DIGITS_NUMBER_VAR_ADDERSS  		0x5372  	//系统参数-系统控制--光照延时关闭打开输入参数十位数字图标地址
#define SYSTEM_ILLUMIAATION_DELAY_CLOSE_CONTROL_INTPUT_HUNDREDS_NUMBER_VAR_ADDERSS  	0x5373  	//系统参数-系统控制--光照延时关闭打开输入参数百位数字图标地址

#define SYSTEM_ILLUMIAATION_DELAY_CLOSE_CONTROL_WAIT_WINDOW_VAR_ADDERSS     			0x5374    	//系统参数-系统控制--光照延时关闭打开保存参数等待弹窗
#define SYSTEM_ILLUMIAATION_DELAY_CLOSE_CONTROL_SUCCESS_WINDOW_VAR_ADDERSS  			0x5375    	//系统参数-系统控制--光照延时关闭打开保存参数成功弹窗
#define SYSTEM_ILLUMIAATION_DELAY_CLOSE_CONTROL_ERROR_WINDOW_VAR_ADDERSS    			0x5376    	//系统参数-系统控制--光照延时关闭打开保存参数失败弹窗

#define SYSTEM_ILLUMIAATION_DELAY_CLOSE_CONTROL_SELECT_CURSOR_ADDERSS  			    	0x537F 	 	//系统参数-系统控制--光照延时关闭打开设置选择图标
/*****************************系统参数-系统控制-屏幕控制-屏幕亮度设置指示图标地址***********************************************/
#define SYSTEM_DISPLAY_LUMINANCE_CONTROL_INTPUT_SELECT_CURSOR_VAR_ADDERSS   			0x5380		//系统参数-系统控制-屏幕控制--光屏幕亮度设置输入参数选择光标地址

#define SYSTEM_DISPLAY_LUMINANCE_CONTROL_INTPUT_DECADE_NUMBER_VAR_ADDERSS  				0x5381  	//系统参数-系统控制--屏幕亮度设置输入参数个位数字图标地址
#define SYSTEM_DISPLAY_LUMINANCE_CONTROL_INTPUT_DIGITS_NUMBER_VAR_ADDERSS  				0x5382  	//系统参数-系统控制--屏幕亮度设置输入参数十位数字图标地址
#define SYSTEM_DISPLAY_LUMINANCE_CONTROL_INTPUT_HUNDREDS_NUMBER_VAR_ADDERSS  			0x5383  	//系统参数-系统控制--屏幕亮度设置输入参数百位数字图标地址

#define SYSTEM_DISPLAY_LUMINANCE_CONTROL_WAIT_WINDOW_VAR_ADDERSS     					0x5384    	//系统参数-系统控制--屏幕亮度设置保存参数等待弹窗
#define SYSTEM_DISPLAY_LUMINANCE_CONTROL_SUCCESS_WINDOW_VAR_ADDERSS  					0x5385    	//系统参数-系统控制--屏幕亮度设置保存参数成功弹窗
#define SYSTEM_DISPLAY_LUMINANCE_CONTROL_ERROR_WINDOW_VAR_ADDERSS    					0x5386    	//系统参数-系统控制--屏幕亮度设置保存参数失败弹窗

#define SYSTEM_DISPLAY_LUMINANCE_CONTROL_SELECT_CURSOR_ADDERSS  			    		0x538F 	 	//系统参数-系统控制--屏幕亮度设置选择图标

/*****************************系统参数-系统控制-屏幕控制-亮屏时间设置指示图标地址***********************************************/
#define SYSTEM_DISPLAY_TIMER_CONTROL_INTPUT_SELECT_CURSOR_VAR_ADDERSS   				0x5390		//系统参数-系统控制-屏幕控制--亮屏时间设置输入参数选择光标地址

#define SYSTEM_DISPLAY_TIMER_CONTROL_INTPUT_DECADE_NUMBER_VAR_ADDERSS  					0x5391  	//系统参数-系统控制--亮屏时间设置输入参数个位数字图标地址
#define SYSTEM_DISPLAY_TIMER_CONTROL_INTPUT_DIGITS_NUMBER_VAR_ADDERSS  					0x5392  	//系统参数-系统控制--亮屏时间设置输入参数十位数字图标地址

#define SYSTEM_DISPLAY_TIMER_CONTROL_WAIT_WINDOW_VAR_ADDERSS     						0x5393    	//系统参数-系统控制--亮屏时间设置保存参数等待弹窗
#define SYSTEM_DISPLAY_TIMER_CONTROL_SUCCESS_WINDOW_VAR_ADDERSS  						0x5394    	//系统参数-系统控制--亮屏时间设置保存参数成功弹窗
#define SYSTEM_DISPLAY_TIMER_CONTROL_ERROR_WINDOW_VAR_ADDERSS    						0x5395    	//系统参数-系统控制--亮屏时间设置保存参数失败弹窗

#define SYSTEM_DISPLAY_TIMER_CONTROL_SELECT_CURSOR_ADDERSS  			    			0x539F 	 	//系统参数-系统控制--亮屏时间选择图标


/*****************************其他参数-选择设置指示图标地址***********************************************/
#define OTHER_SETTING_SELECT_CURSOR_ADDERSS  											0x53B0 		//其他参数选择光标地址

/*****************************其他参数-设置密码***********************************************/
#define TITLE_SETTING_LOGIN_PASSWD_VAR_ADDERSS											0x53C8		//其他参数-设置登录密码-标题图标地址

#define SETTING_LOGIN_PASSWD_INTPUT_SELECT_CURSOR_VAR_ADDERSS    						0x53C0		//其他参数-设置登录密码输入参数选择光标地址

#define SETTING_LOGIN_PASSWD_INTPUT_THOUSAND_NUMBER_VAR_ADDERSS  						0x53C1  	//其他参数-设置登录密码输入参数千位数字图标地址
#define SETTING_LOGIN_PASSWD_INTPUT_HUNDREDS_NUMBER_VAR_ADDERSS  						0x53C2  	//其他参数-设置登录密码输入参数百位数字图标地址
#define SETTING_LOGIN_PASSWD_INTPUT_DIGITS_NUMBER_VAR_ADDERSS  							0x53C3  	//其他参数-设置登录密码输入参数十位数字图标地址
#define SETTING_LOGIN_PASSWD_INTPUT_DECADE_NUMBER_VAR_ADDERSS  							0x53C4  	//其他参数-设置登录密码输入参数个位数字图标地址

#define SETTING_LOGIN_PASSWD_SUCCESS_WINDOW_VAR_ADDERSS  								0x53C6    	//其他参数-设置登录密码设置保存参数成功弹窗
#define SETTING_LOGIN_PASSWD_ERROR_WINDOW_VAR_ADDERSS    								0x53C5    	//其他参数-设置登录密码设置保存参数失败弹窗

#define SETTING_LOGIN_PASSWD_SELECT_CURSOR_ADDERSS  			   						0x53C7 	 	//其他参数-设置登录密码开设置选择图标


/*****************************进入菜单，输入密码界面***********************************************/
#define ENTER_MENUCONFIG_PASSWD_INTPUT_SELECT_CURSOR_VAR_ADDERSS    					0x53A0		//进入菜单，密码输入参数选择光标地址

#define ENTER_MENUCONFIG_PASSWD_INTPUT_THOUSAND_NUMBER_VAR_ADDERSS  					0x53A1  	//进入菜单，密码输入参数千位数字图标地址
#define ENTER_MENUCONFIG_PASSWD_INTPUT_HUNDREDS_NUMBER_VAR_ADDERSS  					0x53A2  	//进入菜单，密码输入参数百位数字图标地址
#define ENTER_MENUCONFIG_PASSWD_INTPUT_DIGITS_NUMBER_VAR_ADDERSS  						0x53A3  	//进入菜单，密码输入参数十位数字图标地址
#define ENTER_MENUCONFIG_PASSWD_INTPUT_DECADE_NUMBER_VAR_ADDERSS  						0x53A4  	//进入菜单，密码输入参数个位数字图标地址

#define ENTER_MENUCONFIG_PASSWD_ERROR_WINDOW_VAR_ADDERSS    							0x53A5    	//进入菜单，密码失败弹窗

#define ENTER_MENUCONFIG_PASSWD_SELECT_CURSOR_ADDERSS  			   						0x53A6 	 	//进入菜单，密码选择图标




#endif /* DW_ADDERSS_H_ */









