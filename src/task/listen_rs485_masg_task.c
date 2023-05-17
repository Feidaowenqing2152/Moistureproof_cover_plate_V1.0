/*
 * listen_rs485_masg_task.c
 *
 *  Created on: 2023年1月5日
 *      Author: 好
 */

#define LOG_TAG    "listen_rs485_masg_task"

#include "../task/listen_rs485_masg_task.h"



void create_listen_rs485_masg_pthread_init(void){
	//(1)timer thread
	pthread_t listen_rs485_masg_id;


	int listen_rs485_masg = pthread_create(&listen_rs485_masg_id,NULL,listen_rs485_msg_task,NULL);
	if(listen_rs485_masg){
		perror("listen_rs485_masg_task error:");
		log_e("listen_rs485_masg_task thread created error !.");
		exit(EXIT_FAILURE);
	}
	log_d("listen_rs485_masg_task thread created.");
}


void* listen_rs485_msg_task(void *arg) {
	while(1){
		if( !deal_transducer_fifo_t.uart_new_data_flag ){
//			memset(recv_buf,0,TTY_READ_BUFFER_SIZE);
			deal_transducer_fifo_t.deal_msg_lenght = listen_transducer_data_task();
			if(deal_transducer_fifo_t.deal_msg_lenght){
				deal_transducer_fifo_t.uart_new_data_flag = 1 ;
			}
		}

	}
}

