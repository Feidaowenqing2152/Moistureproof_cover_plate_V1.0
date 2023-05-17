/*
 * tty.h
 *
 *  Created on: 2023年2月9日
 *      Author: 好
 */

#ifndef DRIVE_TTY_H_
#define DRIVE_TTY_H_

#include <annulus_fifo.h>
#include <stdbool.h>
#include <stdint.h>
#include "../common.h"

//typedef void (*tty_lock_fun)(void);
/* 串口缓存大小 */
#define UART_TX_BUF_SIZE           255
#define UART_RX_BUF_SIZE           255



#define RS485_DEFAULT_BAUDRATE 		9600   //RS485波特率为115200bps
#define RS485_TTY_NAME				"/dev/ttymxc1"

typedef int (*UartSnedDateCb)(int ,uint8_t * ,int) ;






enum fifo_type{
	rs485_bus_device = 0, //rs485总线串口设备
	tty_dw_device,        //迪文串口屏幕设备

NED_FIFO_TYPE};	






void uart_device_init(uint8_t uart_id);

void transducer_setting_device(int buad);
void dw_setting_device(int buad);

uint32_t uart_poll_dma_tx(uint8_t uart_id,uint32_t send_lent);

uint32_t listen_transducer_data_task( void );
uint32_t transducer_device_send(uint8_t *send_data,uint32_t send_lent);
uint32_t transducer_device_recv(uint8_t *recv_data,uint32_t send_lent);
uint32_t listen_dw_display_data_task( void );
uint32_t dw_device_send(uint8_t *send_data,uint32_t send_lent);
uint32_t dw_device_recv(uint8_t *recv_data,uint32_t send_lent);





#endif /* DRIVE_TTY_H_ */
