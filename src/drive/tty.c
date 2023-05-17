/*
 * tty.c
 *
 *  Created on: 2023年2月9日
 *      Author: 好
 */

#define LOG_TAG    "tty"

#include <tty.h>

/* 串口设备数据结构 */
typedef struct
{
//	uint8_t status;		/* 发送状态 */
	_fifo_t tx_fifo;	/* 发送fifo */
	_fifo_t rx_fifo;	/* 接收fifo */
	uint8_t *ttyrx_buf;	/* dma接收缓存 */
//	uint16_t ttyrx_buf_size;/* dma接收缓存大小*/
	uint8_t *ttytx_buf;	/* dma发送缓存 */
	//volatile uint32_t ttytx_buf_size;/* dma发送缓存大小 */
	/* 串口缓存 */
	uint8_t s_uart_tx_fifo_buf[UART_TX_BUF_SIZE];   //fifo发送缓存
	uint8_t s_uart_rx_fifo_buf[UART_RX_BUF_SIZE];  //fifo接收缓存
	uint8_t s_uart_send_buf[UART_TX_BUF_SIZE];     //串口发送数据缓存
	uint8_t s_uart_recv_buf[UART_RX_BUF_SIZE];		//串口接收数据缓存
	//UartSnedDateCb pfnUartSendDateFun;
	int tty_fd;                    //发送设备文件描述符
}uart_device_t;

pthread_mutex_t tty_fifo_lock;

/* 串口设备实例 */
static uart_device_t s_uart_dev[NED_FIFO_TYPE] ;

/* fifo上锁函数 */
static void fifo_lock(void)
{
	pthread_mutex_lock(&tty_fifo_lock);
}

/* fifo解锁函数 */
static void fifo_unlock(void)
{
	pthread_mutex_unlock(&tty_fifo_lock);
}


static void tty_device_init( uint8_t uart_id ){
	if(uart_id == rs485_bus_device ){
		s_uart_dev[rs485_bus_device].tty_fd=tty_init( RS485_TTY_NAME, RS485_DEFAULT_BAUDRATE ,TTY_RS485_MODE );
		if(s_uart_dev[rs485_bus_device].tty_fd<0){
			log_w("rs485 bus device %s failed!", RS485_TTY_NAME);
		}
		log_d("rs485 bus device name: %s",RS485_TTY_NAME);
	}else if( uart_id == tty_dw_device){
		s_uart_dev[tty_dw_device].tty_fd=tty_init( DW_TTY_NAME, DW_DEFAULT_BAUDRATE ,TTY_RS232_MODE );
		if(s_uart_dev[tty_dw_device].tty_fd<0){
			log_w("tty dw  device %s failed!", DW_TTY_NAME);
		}
		log_d("dw tty device name: %s",DW_TTY_NAME);
	}else;
}


/**
 * @brief  串口发送数据接口，实际是写入发送fifo，发送由dma处理
 * @param
 * @retval
 */
static uint16_t uart_write(uint8_t uart_id, const uint8_t *buf, uint32_t size)
{
	return fifo_write(&s_uart_dev[uart_id].tx_fifo, buf, size);
}

/**
 * @brief  串口读取数据接口，实际是从接收fifo读取
 * @param
 * @retval
 */
static uint16_t uart_read(uint8_t uart_id, uint8_t *buf, uint32_t size)
{
	return fifo_read(&s_uart_dev[uart_id].rx_fifo, buf, size);
}


/**
 * @brief  循环从串口发送fifo读出数据，放置于dma发送缓存，并启动dma传输
 * @param
 * @retval
 */
uint32_t uart_poll_dma_tx(uint8_t uart_id,uint32_t send_lent)
{
	uint32_t size = 0;

//	if (0x01 == s_uart_dev[uart_id].status)
//    {
//		log_w("being sent!!! ");
//        return 0;
//    }
	size = fifo_read(&s_uart_dev[uart_id].tx_fifo, s_uart_dev[uart_id].ttytx_buf,send_lent);
	if (size != 0)
	{
//		s_uart_dev[uart_id].status = 0x01;	/* DMA发送状态 */
		size = tty_write(s_uart_dev[uart_id].tty_fd , s_uart_dev[uart_id].ttytx_buf,size);
//		s_uart_dev[uart_id].status = 0x00;	/* DMA发送状态 */
		return size;
	}
	 return 0;
}

/**
 * @brief  串口发送数据接口，实际是写入发送fifo，发送由dma处理
 * @param  send_lent ：预想写入数据长度 ； write_lent_success ：实际写入成功数据长度
 * @retval
 */
static uint32_t uart_device_send(uint8_t uart_id,uint8_t *send_data,uint32_t send_lent)
{
	uint32_t write_lent_success = 0 ;
	write_lent_success = uart_write(uart_id, send_data, send_lent );
	write_lent_success = uart_poll_dma_tx(uart_id,write_lent_success);  /* 将fifo数据拷贝到dma buf，并启动dma传输 */
	return write_lent_success ;
}

/**
 * @brief  串口收读取数据接口，实际是从接收fifo读取
 * @param  recv_lent ：预想读取数据长度 ； recv_lent_success ：实际读取成功数据长度
 * @retval
 */
static uint32_t uart_device_recv( uint8_t uart_id,uint8_t *recv_data , uint32_t recv_lent )
{
	uint32_t recv_lent_success = 0 ;
	recv_lent_success = uart_read(uart_id, recv_data, recv_lent);
	return recv_lent_success ;
}


static void tty_setting_device(uint8_t uart_id,int buad){
	int ret = 0 ;
	if(uart_id== rs485_bus_device){
		ret = tty_setting(s_uart_dev[rs485_bus_device].tty_fd, buad, 8, TTY_RS485_MODE, 0, 'n', 1);
		if(ret < 0){
			log_e("setting tty rs485 devicefailed!");
			exit(EXIT_FAILURE);
		}
	}else if(uart_id== tty_dw_device){
		ret=tty_setting( s_uart_dev[tty_dw_device].tty_fd,  buad, 8, TTY_RS232_MODE, 0, 'n', 1);
		if(ret<0){
			log_e("setting tty dw devicefailed!");
			exit(EXIT_FAILURE);
		}
	}else;
}





void uart_device_init(uint8_t uart_id ){
	/* 配置串口1收发fifo */
	pthread_mutex_init(&tty_fifo_lock,NULL);


	fifo_register(&s_uart_dev[uart_id].tx_fifo, &s_uart_dev[uart_id].s_uart_tx_fifo_buf[0],
                  sizeof(s_uart_dev[uart_id].s_uart_tx_fifo_buf), fifo_lock, fifo_unlock);
	s_uart_dev[uart_id].ttytx_buf = &s_uart_dev[uart_id].s_uart_send_buf[0];

	fifo_register(&s_uart_dev[uart_id].rx_fifo, &s_uart_dev[uart_id].s_uart_rx_fifo_buf[0],
                  sizeof(s_uart_dev[uart_id].s_uart_rx_fifo_buf), fifo_lock, fifo_unlock);
	s_uart_dev[uart_id].ttyrx_buf = &s_uart_dev[uart_id].s_uart_recv_buf[0];

	tty_device_init(uart_id);


}

void transducer_setting_device(int buad){
	tty_setting_device(rs485_bus_device,buad);
}

void dw_setting_device(int buad){
	tty_setting_device(tty_dw_device,buad);
}

uint32_t listen_transducer_data_task(void ){
	int ret = -1 ;
	uint32_t recv_size = 0 ;
	ret =  tty_read( s_uart_dev[rs485_bus_device].tty_fd, s_uart_dev[rs485_bus_device].ttyrx_buf);
	if(ret<=0){
		log_w("listen_transducer_data null ");
		recv_size = 0 ;
	}else{
		recv_size = fifo_write(&s_uart_dev[rs485_bus_device].rx_fifo, s_uart_dev[rs485_bus_device].ttyrx_buf, ret);

	}
	return recv_size ;
}


uint32_t transducer_device_send(uint8_t *send_data,uint32_t send_lent){
	return uart_device_send(rs485_bus_device,send_data,send_lent);
}

uint32_t transducer_device_recv(uint8_t *recv_data,uint32_t send_lent){
	return uart_device_recv(rs485_bus_device,recv_data,send_lent);
}


uint32_t listen_dw_display_data_task( void ){
	int ret = -1 ;
	uint32_t recv_size = 0 ;
	ret =  tty_read( s_uart_dev[tty_dw_device].tty_fd, s_uart_dev[tty_dw_device].ttyrx_buf);
	if(ret<=0){
		log_w("tty_dw_device_date null ");
		recv_size = 0 ;
	}else{
		recv_size = fifo_write(&s_uart_dev[tty_dw_device].rx_fifo, s_uart_dev[tty_dw_device].ttyrx_buf, ret);
	}
	return recv_size ;
}

uint32_t dw_device_send(uint8_t *send_data,uint32_t send_lent){
	return uart_device_send(tty_dw_device,send_data,send_lent);
}


uint32_t dw_device_recv(uint8_t *recv_data,uint32_t send_lent){
	return uart_device_recv(tty_dw_device,recv_data,send_lent);
}














