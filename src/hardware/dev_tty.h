/*
 * dev_tty.h
 *
 *  Created on: 2023年2月9日
 *      Author: 好
 */

#ifndef HARDWARE_DEV_TTY_H_
#define HARDWARE_DEV_TTY_H_

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <termios.h>
#include <errno.h>
#include <string.h>



#include <linux/serial.h>
#include <asm-generic/ioctls.h> /* TIOCGRS485 + TIOCSRS485 ioctl definitions */

#include <fcntl.h>
#include <sys/ioctl.h>
#include <linux/ioctl.h>

#include "../common.h"

#define TTY_DEFAULT_BAUDRATE  	9600




#define _TTY_MODE_BLOCK_ 		0

#if _TTY_MODE_BLOCK_ == 0
#define TTY_READ_TIMEOUT_MSEC	1000
#endif


#define TTY_READ_BUFFER_SIZE	128


#define B115200_ONE_BYTE_TIME 	90   //us
#define B57600_ONE_BYTE_TIME 	160   //us
#define B38400_ONE_BYTE_TIME 	280   //us
#define B19200_ONE_BYTE_TIME 	530   //us
#define B9600_ONE_BYTE_TIME 	1100   //us
#define B4800_ONE_BYTE_TIME 	2100   //us
#define B2400_ONE_BYTE_TIME 	4200   //us
#define B1800_ONE_BYTE_TIME 	5600   //us
#define B1200_ONE_BYTE_TIME 	8370   //us
#define B600_ONE_BYTE_TIME 		20000   //us




#define TTY_RS485_MODE			1
#define TTY_RS232_MODE			0



#ifndef TIOCSRS485
    #define TIOCSRS485     0x542F
#endif

#ifndef TIOCGRS485
    #define TIOCGRS485     0x542E
#endif
/*
struct tty_dev
{
	char tty_dev[MAX_INPUT];
	int bitrate;
	int datasize;
	char par;
	int stop;
	int flow;
	int rs485_mode;
};
typedef struct tty_dev tty_dev_t;*/

/******************************************************************************
  Function:       tty_init
  Description:    initialize tty device
  Input:          tty    	--  tty device name, such as '/dev/ttyO0', '/dev/ttyO5'

  Output:
  Return:         int		-- return the tty fd
  Others:         NONE
*******************************************************************************/
int	 tty_init(const char * tty,unsigned int baudrate,int mode);

int tty_setting(int fd, int bitrate, int datasize, int mode, int flow, int par, int stop);
int	tty_write(int fd, unsigned char *frame, int len);
int	tty_read(int fd, unsigned char *frame);

#endif /* HARDWARE_DEV_TTY_H_ */
