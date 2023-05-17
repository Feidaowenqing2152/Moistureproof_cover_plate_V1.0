/*
 * deal_rs485_masg_task.h
 *
 *  Created on: 2023年1月5日
 *      Author: 好
 */

#ifndef TASK_DEAL_RS485_MASG_TASK_H_
#define TASK_DEAL_RS485_MASG_TASK_H_

#include "../common.h"

typedef enum {
	external_temperature_transducer=0,
	interior_temperature_transducer,
	illumination_transducer,
	sleet_transducer,
	smoke_transducer,
	water_transducer,
END_TRANSDUCER_NUMBER}transducer_number;

typedef enum
{
    offline = 0,
	online =  !offline,
	online_error = 2 ,
}Transducer_State;

typedef enum
{
    nack = 0,
	ack =  !nack,
	ack_error = 2 ,
}Transducer_Reply_State;

typedef struct deal_transducer_fifo{
    int uart_new_data_flag ;
	int deal_msg_lenght ;
}type_deal_transducer_fifo;

type_deal_transducer_fifo deal_transducer_fifo_t;
extern type_deal_transducer_fifo deal_transducer_fifo_t;

struct illumination_par{
	uint8_t illumination_percentage ;  //光照百分比
	uint32_t illumination_date ;   //实际光照值
};

typedef struct deal_transducer_masg{
	int dev_online_ack_flag[END_TRANSDUCER_NUMBER];
	int dev_online_state[END_TRANSDUCER_NUMBER];//设备在线情况
	int external_temperature_date;
	int external_humidity_date;
	int internal_temperature_date;
	int internal_humidity_date;
	int sleet_adderss ;
	int sleet_state ;
	int smoke_state ;
	int water_state ;
	int local_run_mode ;
	int board_status ;
	int fan_velocity ;
	struct illumination_par illumination_par_t;

}type_deal_transducer_masg;
type_deal_transducer_masg deal_transducer_masg_t;
extern type_deal_transducer_masg deal_transducer_masg_t;

void create_deal_rs485_masg_pthread_init(void);
void* deal_rs485_msg_task(void *arg);
//int illumination_intensity_cove(uint16_t illumination_intensity_data_h,uint16_t illumination_intensity_data_l ,uint8_t *percentage_illumination);
#endif /* TASK_DEAL_RS485_MASG_TASK_H_ */
