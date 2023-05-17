/*
 * dev_tty.c
 *
 *  Created on: 2023年2月9日
 *      Author: 好
 */
#define LOG_TAG    "dev_tty"
#include <dev_tty.h>

static int multi_delay=1;
/******************************************************************************
  Function:       tty_init
  Description:    initialize tty device
  Input:          tty    	--  tty device name, such as '/dev/ttyO0', '/dev/ttyO5'

  Output:
  Return:         int		-- return the tty fd
  Others:         NONE
*******************************************************************************/
int	tty_open_init(const char * tty)
{
	int fd;
#if _TTY_MODE_BLOCK_ ==1
	fd = open(tty, O_RDWR | O_NOCTTY );//����ʽ��д
#else
//	fd = open(tty,  O_RDWR|O_NOCTTY|O_NDELAY); //������ģʽ
	fd = open(tty,  O_RDWR|O_NOCTTY|O_NONBLOCK); //������ģʽ|
#endif
	if(fd < 0){
		perror("tty:");
		log_e("open %s error !!",tty);
		}
	return fd;
}


int tty_mode_set(int fd,  int mode)
{
	/*
	 * RS485�Զ����ƹܽ��л����򣬲ο���https://blog.csdn.net/liangtao_1996/article/details/114701554
	 * ����޸��ں˺��豸�������±�����¼
	 * 2022-09-14
	 */
	struct serial_rs485 rs485conf;
	int res;
	/* Get configure from device */
	res = ioctl(fd, TIOCGRS485, &rs485conf);
	if (res < 0) {
		perror("Ioctl error on getting 485 configure:");
		close(fd);
		return res;
	}

	/* Set enable/disable to configure */
	if(mode == TTY_RS485_MODE){
		// Enable rs485 mode
		rs485conf.flags |= SER_RS485_ENABLED;
		/* ����������ʱ, RTS Ϊ 1 */
		rs485conf.flags |= SER_RS485_RTS_ON_SEND;

		/* ���������ݺ�, RTS Ϊ 0 */
		rs485conf.flags &= ~(SER_RS485_RTS_AFTER_SEND);
//		rs485conf.delay_rts_before_send =  10 ;
//		rs485conf.delay_rts_after_send = 10 ;
		}
	else{
		// Disable rs485 mode
		rs485conf.flags &= ~(SER_RS485_ENABLED);
		rs485conf.flags &= ~(SER_RS485_RTS_ON_SEND);
		rs485conf.flags |= SER_RS485_RTS_AFTER_SEND;
		}

	rs485conf.delay_rts_before_send = 0x00000004;

	/* Set configure to device */
	res = ioctl(fd, TIOCSRS485, &rs485conf);
	if (res < 0) {
		perror("Ioctl error on setting 485 configure");
		close(fd);
	}

	return res;
}

/******************************************************************************
  Function:       tty_setting
  Description:    set the tty device's mode and bitrate
  Input:          fd       --  tty device fd
  				  bitrate --  tty baudrate
  				  mode	   --  tty mode, 1: rs485; 0: rs232
  				  flow	   --  cts/rts flow control
  				  par	   --  odd/even
  				  stop	   --  number of stop bits

  Output:
  Return:         int 	   --  tty setting status 0:success
  Others:         NONE
*******************************************************************************/
int tty_setting(int fd, int bitrate, int datasize, int mode, int flow, int par, int stop)
{
	struct termios newtio;

	/* ignore modem control lines and enable receiver */
	memset(&newtio, 0, sizeof(newtio));
	newtio.c_cflag |= CLOCAL | CREAD;
	if(flow == 1)
	{
		newtio.c_cflag |= CLOCAL | CREAD | CRTSCTS;
	}

	newtio.c_cflag &= ~CSIZE;

	/* set character size */
	switch (datasize) {
	case 8:
		newtio.c_cflag |= CS8;
		break;
	case 7:
		newtio.c_cflag |= CS7;
		break;
	case 6:
		newtio.c_cflag |= CS6;
		break;
	case 5:
		newtio.c_cflag |= CS5;
		break;
	default:
		newtio.c_cflag |= CS8;
		break;
	}

	/* set the parity */
	switch (par) {
	case 'o':
	case 'O':
		newtio.c_cflag |= PARENB;
		newtio.c_cflag |= PARODD;
		newtio.c_iflag |= (INPCK | ISTRIP);
		break;
	case 'e':
	case 'E':
		newtio.c_cflag |= PARENB;
		newtio.c_cflag &= ~PARODD;
		newtio.c_iflag |= (INPCK | ISTRIP);
		break;
	case 'n':
	case 'N':
		newtio.c_cflag &= ~PARENB;
		break;
	default:
		newtio.c_cflag &= ~PARENB;
		break;
	}

	/* set the stop bits */
	switch (stop) {
	case 1:
		newtio.c_cflag &= ~CSTOPB;
		break;
	case 2:
		newtio.c_cflag |= CSTOPB;
		break;
	default:
		newtio.c_cflag &= ~CSTOPB;
		break;
	}

	/* set output and input baud rate */
	switch (bitrate) {
	case 0:
		cfsetospeed(&newtio, B0);
		cfsetispeed(&newtio, B0);
		break;
	case 50:
		cfsetospeed(&newtio, B50);
		cfsetispeed(&newtio, B50);
		break;
	case 75:
		cfsetospeed(&newtio, B75);
		cfsetispeed(&newtio, B75);
		break;
	case 110:
		cfsetospeed(&newtio, B110);
		cfsetispeed(&newtio, B110);
		break;
	case 134:
		cfsetospeed(&newtio, B134);
		cfsetispeed(&newtio, B134);
		break;
	case 150:
		cfsetospeed(&newtio, B150);
		cfsetispeed(&newtio, B150);
		break;
	case 200:
		cfsetospeed(&newtio, B200);
		cfsetispeed(&newtio, B200);
		break;
	case 300:
		cfsetospeed(&newtio, B300);
		cfsetispeed(&newtio, B300);
		break;
	case 600:
		cfsetospeed(&newtio, B600);
		cfsetispeed(&newtio, B600);
		multi_delay = 10;
		break;
	case 1200:
		cfsetospeed(&newtio, B1200);
		cfsetispeed(&newtio, B1200);
		multi_delay = 9;
		break;
	case 1800:
		cfsetospeed(&newtio, B1800);
		cfsetispeed(&newtio, B1800);
		multi_delay = 8;
		break;
	case 2400:
		cfsetospeed(&newtio, B2400);
		cfsetispeed(&newtio, B2400);
		multi_delay = 7;
		break;
	case 4800:
		cfsetospeed(&newtio, B4800);
		cfsetispeed(&newtio, B4800);
		multi_delay = 6;
		break;
	case 9600:
		cfsetospeed(&newtio, B9600);
		cfsetispeed(&newtio, B9600);
		multi_delay = 5;
		break;
	case 19200:
		cfsetospeed(&newtio, B19200);
		cfsetispeed(&newtio, B19200);
		multi_delay = 4;
		break;
	case 38400:
		cfsetospeed(&newtio, B38400);
		cfsetispeed(&newtio, B38400);
		multi_delay = 3;
		break;
	case 57600:
		cfsetospeed(&newtio, B57600);
		cfsetispeed(&newtio, B57600);
		multi_delay = 2;
		break;
	case 115200:
		cfsetospeed(&newtio, B115200);
		cfsetispeed(&newtio, B115200);
		multi_delay = 1;
		break;
	case 230400:
		cfsetospeed(&newtio, B230400);
		cfsetispeed(&newtio, B230400);
		multi_delay = 1;
		break;
	default:
		cfsetospeed(&newtio, B115200);
		cfsetispeed(&newtio, B115200);
		multi_delay = 1;
		break;
	}
#if _TTY_MODE_BLOCK_ == 1
	/* set timeout in deciseconds for non-canonical read */
	newtio.c_cc[VTIME] = 30;	//ÿ����λ��0.1��  20����2��
	/* set minimum number of characters for non-canonical read */
	newtio.c_cc[VMIN] = 10;	//Ϊ0��Ϊ�������������Ϊ����ֵ������ ������������Ч
#else
	/* set timeout in deciseconds for non-canonical read */
	newtio.c_cc[VTIME] = 0;	//ÿ����λ��0.1��  20����2��
	/* set minimum number of characters for non-canonical read */
	newtio.c_cc[VMIN] = 1;	//Ϊ0��Ϊ�������������Ϊ����ֵ������ ������������Ч[�ֽ�]
#endif


	/* flushes data received but not read */
	tcflush(fd, TCIFLUSH);
	/* set the parameters associated with the terminal from
	   the termios structure and the change occurs immediately */
	if((tcsetattr(fd, TCSANOW, &newtio))!=0) {
		log_w("set_tty/tcsetattr");
		return -1;
	}

	tty_mode_set(fd, mode);
	return 0;
}

int set_rs485_waste_time( int set_baud  , int send_data_len )
{
	int send_all_data_over_time =0;   //����һ���ֽ�������Ҫʱ�� ��λ:us
	switch( set_baud )
	{
	case 1:		//115200
		send_all_data_over_time = send_data_len * B115200_ONE_BYTE_TIME ; break ;
	case 2:		//57600
		send_all_data_over_time = send_data_len * B57600_ONE_BYTE_TIME ; break ;
	case 3 :	//38400
		send_all_data_over_time = send_data_len * B38400_ONE_BYTE_TIME ; break ;
	case 4 :	//19200
		send_all_data_over_time = send_data_len * B19200_ONE_BYTE_TIME ; break ;
	case 5 :	//9600
		send_all_data_over_time = send_data_len * B9600_ONE_BYTE_TIME ; break ;
	case 6 :	//4800
		send_all_data_over_time = send_data_len * B4800_ONE_BYTE_TIME ; break ;
	case 7 :	//2400
		send_all_data_over_time = send_data_len * B2400_ONE_BYTE_TIME ; break ;
	case 8 :	//1800
		send_all_data_over_time = send_data_len * B1800_ONE_BYTE_TIME ; break ;
	case 9 :	//1200
		send_all_data_over_time = send_data_len * B1200_ONE_BYTE_TIME ; break ;
	case 10 :	//600
		send_all_data_over_time = send_data_len * B600_ONE_BYTE_TIME ; break ;
	default : log_w( "Cover Badu Error Timer ");break ;
	}
	return send_all_data_over_time ;
}


int	tty_read(int fd, unsigned char *frame){
	int rxlen = -1;
	fd_set readfds;
	//	struct timeval  selecttime;
	/*
	函数原型：
	int select(int maxfdp, fd_set *readfds, fd_set *writefds, fd_set *errorfds, struct timeval *timeout);
	参数说明：
	maxfdp：集合中所有文件描述符的范围，需设置为所有文件描述符中的最大值加1。
	readfds：要进行监听的是否可以读文件的文件描述符集合。
	writefds：要进行监听的是否可以写文件的文件描述符集合。
	errorfds：要进行监听的是否发生异常的文件描述符集合。
	timeval：select的超时时间，它可以使select处于三种状态：
	1、若将NULL以形参传入，即不传入时间结构，就是将select至于阻塞状态，一定要等到监视的文件描述符集合中某个文件描述符发生变化为止。
	2、若将时间值设为0秒0毫秒，就变成一个纯粹的非阻塞函数，不管文件描述符是否发生变化，都立刻返回继续执行，文件无变化返回0，有变化返回一个正值。
	3、timeout的值大于0，这就是等待的超时时间，即select在timeout时间内阻塞，超时时间之内有事件到来就返回，否则在超时后不管怎样一定返回。
	返回值：
	>0：表示被监视的文件描述符有变化。
	-1：表示select出错。
	0：表示超时。
	参考博客网站:https://blog.csdn.net/weixin_39888281/article/details/116890137
	 */
	//	selecttime.tv_sec = TTY_READ_TIMEOUT_MSEC/1000;
	//	selecttime.tv_usec = (TTY_READ_TIMEOUT_MSEC%1000)*1000; //select�ȴ�1�룬1����ѯ��Ҫ����������0

		FD_ZERO(&readfds);
		FD_SET(fd, &readfds);
	//	switch( select(fd+1, &readfds, NULL, NULL, &selecttime) ){
	switch( select(fd+1, &readfds, NULL, NULL, NULL) ){
		case -1 : log_w("[Warning]uart select error 2"); return -1;break;
		case 0 :  break ;
		default:
			if( FD_ISSET(fd, &readfds) ) //���ӵ��ļ��б䶯
			{
				microseconds_sleep( set_rs485_waste_time(multi_delay, TTY_READ_BUFFER_SIZE )); //�ȴ��Զ����ݷ������
				rxlen = read(fd, frame,TTY_READ_BUFFER_SIZE);
				if( rxlen<= 0 ){
					log_e("[Warning]uart recv error !!");
					return -1;
				}else{
					return rxlen;
				}
			} break ;
	}
	perror("uaet recv");
	   return -1;
}


int tty_write(int fd,unsigned char * frame,int len){
	int ret = 0;
	ret = write(fd , frame, len);
	if(ret <= 0){
		perror("Write tty devicef failed :");
		log_e("Write tty device failed!");
		close(fd);
		return 0;
	}
	return ret;
//	else{
//		tcdrain(fd); /* 使程序阻塞，直到输出缓冲区的数据全部发送完毕*/
//		tcflush(fd, TCOFLUSH); /* 用于清空输入/输出缓冲区*/
//		return ret;
//	}
}



int	tty_init(const char * tty,unsigned int baudrate,int mode){
	int ret=0;
	int tty_fd = -1;

	tty_fd = tty_open_init(tty);
	if( tty_fd < 0){
		perror("Initialize tty devicef failed :");
		log_e("Initialize tty device %s failed!", tty);
		exit(EXIT_FAILURE);
	}
	ret = tty_setting(tty_fd, baudrate, 8, mode, 0, 'n', 1);
	if(ret < 0){
		perror("setting tty devicef failed :");
		log_e("setting tty device %s failed!", tty);
		exit(EXIT_FAILURE);
		}
	return tty_fd;
}


