/*
 * eth.c
 *
 *  Created on: 2022年12月30日
 *      Author: 好
 */
#define LOG_TAG    "eth"

#include <delay.h>
#include "../app/eth.h"
#include <ctype.h>

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/ioctl.h>
#include <net/if.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <linux/route.h> // 包含路由表相关的宏、结构体和函数定义

static struct eth eth0_gayther ={
		.eth_name = ETH ,
		.ip_dhcp_state = "static",
		.ip_adderss = ADDRESS ,
		.port = IP_PORT ,
		.ip_netmask = NETMASK ,
		.ip_gateway = GATEWAY ,

};

Eth_Connect_State_Cb pfnEthConnectStateNotifyFun ;
struct mosquitto *eth_mosq;

static int get_network_interfaces(struct eth *flie_network_eth0 );
static int eth_saveenv_interfaces(struct eth *eth0);
static int configure_network(struct eth *eth0);

//static int detect_eth_cable(char *eth);
static int get_eth0_state(void);


/**
  * @brief      注册网口检测动作改变时的通知回调函数
  *
  * @param[in]  eKey 指定按键, 取值为 @reg IoKeyType_e
  * @param[in]  pKeyFun 通知回调函数
  */
void Eth_Connect_State_Register(struct mosquitto *mosq,Eth_Connect_State_Cb pEthConnectStateFun){
	if(mosq !=NULL){
		pfnEthConnectStateNotifyFun = pEthConnectStateFun;
		eth_mosq = mosq ;
	}
}



/**
  * @brief      注销网口检测动作改变时的通知回调函数
  *
  * @param[in]  eKey 指定按键, 取值为 @reg IoKeyType_e
  */

void Eth_Connect_State_UnRegister(Eth_Connect_State_Cb pEthConnectStateFun){
	pfnEthConnectStateNotifyFun = NULL;
	eth_mosq = NULL;
}


void Eth_Scan_Loop_State(uint16_t scan_time){
	static uint8_t eth0_netup_state_flag = 0 ,eth0_netdown_state_flag = 0 ;

	if(check_time_arrive(CHECK_ETH_CONNECT_STATE_TIMER_NUMBER,scan_time)){
	if (get_eth0_state()) {
		if (eth0_netup_state_flag == 0) {
			eth0_netup_state_flag = 1;
			eth0_netdown_state_flag = 0;
			if(eth_mosq != NULL)
			pfnEthConnectStateNotifyFun(eth_mosq,1);
			log_i("Eth0 NETUP !!!.");
		}
	} else {
		if(eth0_netdown_state_flag == 0){
			eth0_netdown_state_flag = 1;
			eth0_netup_state_flag = 0;
			if(eth_mosq != NULL)
			pfnEthConnectStateNotifyFun(eth_mosq,0);
			log_e("Eth0 NETDOWN !!!.");
		}
	}
//	if(!detect_eth_cable(eth0_gayther.eth_name)){
//		pfnEthConnectStateNotifyFun(eth_mosq,0);
//		log_e("ethernet is down!!");
//	}
	clear_time_cnt(CHECK_ETH_CONNECT_STATE_TIMER_NUMBER);
	}
}



int set_sys_eth0_init(void){
	int ret = -1 ;
	mqtt_ip_tcp_def eth0_ip_parameter_t ;
	struct eth get_nerwork_eth0 ;
	struct eth write_nerwork_eth0 ;
	//eth0_network_reset();   //重启网卡
	read_saveenv_cjson_mqttip_parameter(&eth0_ip_parameter_t);
	strcpy(write_nerwork_eth0.eth_name, "eth0");
	strcpy(write_nerwork_eth0.ip_dhcp_state, eth0_ip_parameter_t.ip_acquisition_type);
	strcpy(write_nerwork_eth0.ip_adderss, eth0_ip_parameter_t.ip);
	strcpy(write_nerwork_eth0.ip_netmask, eth0_ip_parameter_t.netmask);
	strcpy(write_nerwork_eth0.ip_gateway, eth0_ip_parameter_t.gateway);

	if(strcmp(eth0_ip_parameter_t.ip_acquisition_type,"static") == 0) {
		log_i("eth0 network now is static");
		ret=  get_network_interfaces(&get_nerwork_eth0);	//获取 /etc/network/interfaces 网络配置信息
		if(!ret){
			if( (strcmp(eth0_ip_parameter_t.ip_acquisition_type,get_nerwork_eth0.ip_dhcp_state) != 0) || (strcmp(eth0_ip_parameter_t.ip,get_nerwork_eth0.ip_adderss) != 0) ||
				(strcmp(eth0_ip_parameter_t.netmask,get_nerwork_eth0.ip_netmask) != 0) || (strcmp(eth0_ip_parameter_t.gateway,get_nerwork_eth0.ip_gateway) != 0)	){
				ret = eth_saveenv_interfaces(&write_nerwork_eth0);
				if(ret ){
					log_e("1");
					configure_network(&eth0_gayther);
					return 0 ;
				}else{
					goto _set_network_static_jump;
				}
			}else{
				goto _set_network_static_jump;
			}
		}else{
			log_e("get /etc/network/interfaces file error.");
			goto _set_network_static_jump;
		}
	}else{
		log_i("eth0 network now is dhcp");
		return 0 ;
	}
_set_network_static_jump:
	configure_network(&write_nerwork_eth0);
//	eth0_network_reset();   //重启网卡
	return 0 ;
}

void eth0_network_reset(void){
	char cmd[100];
	int ret = 0;
	log_i("eth0 network reseting ...... ");
	sprintf(cmd,"ip link set dev %s down",eth0_gayther.eth_name);
	ret = system(cmd);
	if (ret == -1) {
		log_e("ip link set down failed:%s",strerror(errno));
	}
	milliseconds_sleep(100);
	sprintf(cmd,"ip link set dev %s up",eth0_gayther.eth_name);
	ret = system(cmd);
	if (ret == -1) {
		log_e("ip link set up failed:%s",strerror(errno));
	}
	milliseconds_sleep(100);
	log_i("eth0 network reset finish. ");
}


int set_sys_network(struct eth *eth0 ,char *eth0_select){
	int ret = 0 ;
	if(strcmp(eth0_select,"ip_dhcp_state") == 0){
		strcpy(eth0_gayther.ip_dhcp_state, eth0->ip_dhcp_state);
	}
	if(strcmp(eth0_select,"ip_adderss") == 0){
		strcpy(eth0_gayther.ip_adderss, eth0->ip_adderss);
	}
	if(strcmp(eth0_select,"ip_netmask") == 0){
		strcpy(eth0_gayther.ip_netmask, eth0->ip_netmask);
	}
	if(strcmp(eth0_select,"ip_gateway") == 0){
		strcpy(eth0_gayther.ip_gateway, eth0->ip_gateway);
	}
	ret = eth_saveenv_interfaces(&eth0_gayther);
	if(ret){
		log_e("ip saveenv error !!\r");
		return 1 ;
	}
	if(strcmp(eth0->ip_dhcp_state,"static") == 0){
		ret=configure_network(&eth0_gayther);
		if(ret){
			log_e("set ip error !!\r");
			return 1 ;
		}
	}
	eth0_network_reset();   //重启网卡
	return 0 ;
}



int network_eth0_dhcp_status(char* iface_name ,struct eth *dhcp_network){
	int fd  = -1;
	struct ifreq ifr;
	struct sockaddr_in *sin;
	unsigned char *p;
	unsigned long ip, mask, gw;
//	char *iface = "eth0"; // 更换为实际的网络接口名

	fd = socket(AF_INET, SOCK_DGRAM, 0);
	if(fd<0){
		log_e("socket SOCK_DGRAM error:%s",strerror(errno));
		return -1;
	}
	memset(&ifr, 0, sizeof(ifr));
	strncpy(ifr.ifr_name, iface_name, IFNAMSIZ-1);

	// 获取网络接口配置信息
	if (ioctl(fd, SIOCGIFADDR, &ifr) != 0) {
		log_e("ioctl SIOCGIFADDR:%s",strerror(errno));
		close(fd);
		return -1;
	}
	// 判断是否为DHCP分配的IP地址，如果是，则说明DHCP获取成功
	sin = (struct sockaddr_in *)&ifr.ifr_addr;
	if (sin->sin_addr.s_addr == INADDR_ANY) { //检测获取到的地址是否为DHCP
		log_e("DHCP ERROR");
		close(fd);
		return 1;
	}
	strcpy(dhcp_network->eth_name, iface_name);
	strcpy(dhcp_network->ip_dhcp_state, "dhcp");
	p = (unsigned char *)&sin->sin_addr.s_addr;
	ip = ((unsigned long)p[3] << 24) | ((unsigned long)p[2] << 16) |
		 ((unsigned long)p[1] << 8) | (unsigned long)p[0];
	log_i("DHCP IP address: %s", inet_ntoa(*(struct in_addr *)&ip));
	strcpy(dhcp_network->ip_adderss, inet_ntoa(*(struct in_addr *)&ip));


	if (ioctl(fd, SIOCGIFNETMASK, &ifr) < 0) {
		log_i("ioctl SIOCGIFNETMASK error:%s",strerror(errno));
		close(fd);
		return -1;
	}
	sin = (struct sockaddr_in *)&ifr.ifr_addr;
	p = (unsigned char *)&sin->sin_addr.s_addr;
	mask = ((unsigned long)p[3] << 24) | ((unsigned long)p[2] << 16) |
		   ((unsigned long)p[1] << 8) | (unsigned long)p[0];
	log_i("DHCP Netmask: %s", inet_ntoa(*(struct in_addr *)&mask));
	strcpy(dhcp_network->ip_netmask, inet_ntoa(*(struct in_addr *)&mask));

	if (ioctl(fd, SIOCGIFBRDADDR, &ifr) < 0) {
		log_i("ioctl SIOCGIFBRDADDR error:%s",strerror(errno));
		close(fd);
		return -1;
	}
	sin = (struct sockaddr_in *)&ifr.ifr_broadaddr;
	p = (unsigned char *)&sin->sin_addr.s_addr;
	gw = ((unsigned long)p[3] << 24) | ((unsigned long)p[2] << 16) |
		 ((unsigned long)p[1] << 8) | (unsigned long)p[0];
	log_i("DHCP Gateway: %s", inet_ntoa(*(struct in_addr *)&gw));
	strcpy(dhcp_network->ip_gateway, inet_ntoa(*(struct in_addr *)&gw));

	close(fd);
	return 0;
}


/**
  * @brief      设置系统eth，并立刻生效
  *
  * @param[in]  struct eth *eth0 网络相关信息结构体入参
  */
//static int eht_set_sys_network_cmd(struct eth *eth0){
//	int ret=0;
//	char cmd[100];
//
//	sprintf(cmd,"ifconfig %s %s netmask %s",eth0->eth_name,eth0->ip_adderss,eth0->ip_netmask);
//	ret=system(cmd);
//	if(1==ret){
//		log_e("The program command is empty");
//		perror("errno");
//		return 1 ;
//	} else if(-1==ret){
//		log_e("Failed to create the command child process");
//		perror("errno");
//		return 1 ;
//	}else if(0x7f00==ret){
//		log_e("Command error, unable to execute");
//		perror("errno");
//		return 1 ;
//	}
//	milliseconds_sleep(1000);
//	sprintf(cmd,"route add default gw %s",eth0->ip_gateway);
//	ret=system(cmd);
//	if(1==ret){
//		log_e("The program command is empty");
//		perror("errno");
//		return 1 ;
//	} else if(-1==ret){
//		log_e("Failed to create the command child process");
//		perror("errno");
//		return 1 ;
//	}else if(0x7f00==ret){
//		log_e("Command error, unable to execute");
//		perror("errno");
//		return 1 ;
//	}
//	return 0 ;
//}
static int configure_network(struct eth *eth0) {
    if (!eth0 || !eth0->eth_name || !eth0->ip_adderss || !eth0->ip_netmask || !eth0->ip_gateway) {
        log_e("Invalid input parameters.");
        return -1;
    }

    int sockfd = socket(AF_INET, SOCK_DGRAM, 0);
    if (sockfd == -1) {
        log_e("Failed to create socket:%s",strerror(errno));
        return -1;
    }

    struct ifreq ifr;
    struct sockaddr_in sin;

    memset(&ifr, 0, sizeof(ifr));
    strncpy(ifr.ifr_name, eth0->eth_name, IFNAMSIZ-1);

    sin.sin_family = AF_INET;
    if (inet_aton(eth0->ip_adderss, &sin.sin_addr) == 0) {
        log_e( "Invalid IP address: %s", eth0->ip_adderss);
        close(sockfd);
        return -1;
    }
    memcpy(&ifr.ifr_addr, &sin, sizeof(ifr.ifr_addr));

    if (ioctl(sockfd, SIOCSIFADDR, &ifr) == -1) {
    	log_e("Failed to set IP address:%s",strerror(errno));
        close(sockfd);
        return -1;
    }

    memset(&ifr, 0, sizeof(ifr));
    strncpy(ifr.ifr_name, eth0->eth_name, IFNAMSIZ-1);

    sin.sin_family = AF_INET;
    if (inet_aton(eth0->ip_netmask, &sin.sin_addr) == 0) {
        log_e("Invalid subnet mask: %s", eth0->ip_netmask);
        close(sockfd);
        return -1;
    }
    memcpy(&ifr.ifr_addr, &sin, sizeof(ifr.ifr_addr));

    if (ioctl(sockfd, SIOCSIFNETMASK, &ifr) == -1) {
        log_e("Failed to set subnet mask:%s",strerror(errno));
        close(sockfd);
        return -1;
    }

    struct rtentry route;
    memset(&route, 0, sizeof(route));
    route.rt_dst.sa_family = AF_INET;
    ((struct sockaddr_in *)&route.rt_dst)->sin_addr.s_addr = htonl(INADDR_ANY);
    route.rt_flags = RTF_UP;

    ((struct sockaddr_in *)&route.rt_gateway)->sin_addr.s_addr = inet_addr(eth0->ip_gateway);
    if (ioctl(sockfd, SIOCADDRT, &route) == -1) {
        if (errno != EEXIST) { /* ignore "File exists" error */
            log_e("Failed to add default route",strerror(errno));
            close(sockfd);
            return -1;
        }
    }

    log_i("Network configuration completed successfully.");
    close(sockfd);

    return 0;
}

/**
  * @brief      储存设置的eth信息到系统/etc/network/interfaces 中
  *
  * @param[in]  struct eth *eth0 网络相关信息结构体入参
  */
static int eth_saveenv_interfaces(struct eth *eth0){
	char cmd[300];
	int ipaddr_fd = 0 ;
	if(strcmp(eth0->ip_dhcp_state,"static") == 0){
		sprintf(cmd,\
				"auto lo\niface lo inet loopback\nauto %s\niface %s inet static\naddress %s\nnetmask %s\ngateway %s\n ",	\
				eth0->eth_name,eth0->eth_name,eth0->ip_adderss,eth0->ip_netmask,eth0->ip_gateway);
	}else{
		log_d("now is dhcp !!!");
		sprintf(cmd,\
				"auto lo\niface lo inet loopback\nauto %s\niface %s inet dhcp\n ",	\
				eth0->eth_name,eth0->eth_name);
		log_d("%s",cmd);
	}

	ipaddr_fd = open(IP_FILE, O_RDWR);
	if(ipaddr_fd<0){
		log_e("open set ipaddr file error:%s.",strerror(errno));
		return 1 ;
	}
	ftruncate(ipaddr_fd,0);				//清空文件
	lseek(ipaddr_fd,0,SEEK_SET);		//光标复位
	write(ipaddr_fd,cmd,strlen(cmd));	//将修改后的数据写回元文件
	close(ipaddr_fd);					//将文件从动态区返回静态

	return 0 ;
}





/**
  * @brief      获取系统/etc/network/interfaces 中动态/静态信息
  *
  * @param[in]
  */


static int get_network_interfaces(struct eth *flie_network_eth0 ){
	 FILE *file;
	 char *token;
	 char line[256];

	file = fopen("/etc/network/interfaces", "r");
	if (file == NULL) {
		log_e("Failed to open file.\n");
		return 1;
	}
	while (fgets(line, sizeof(line), file)) {
		if (strstr(line, "iface eth0 inet") != NULL){	// 提取IP获取状态为static还是dhcp
			token = strtok(line, " ");					// 使用空格作为分隔符
			while (token != NULL){
				int lent = strlen(token);
				 while ((lent > 0) && (isspace(token[lent - 1]))) {
					 lent--;
				    }
				  // 去除尾部空格
				 token[lent] = '\0';
				if ((strcmp(token, "dhcp") == 0) || (strcmp(token, "static") == 0)){
					strcpy(flie_network_eth0->ip_dhcp_state, token);
				}
				token = strtok(NULL, " ");
			}
		}
		// 提取address、netmask和gateway
		else if (strstr(line, "address") != NULL) {
			sscanf(line, "    address %s\n", flie_network_eth0->ip_adderss);
		}
		else if (strstr(line, "netmask") != NULL){
			sscanf(line, "    netmask %s\n", flie_network_eth0->ip_netmask);
		}
		else if (strstr(line, "gateway") != NULL){
			sscanf(line, "    gateway %s\n", flie_network_eth0->ip_gateway);
		}
	}
	fclose(file);
	return 0 ;
}




/**
  * @brief      获取系统/etc/network/interfaces 中动态/静态信息
  *
  * @param[in]
  */
//
//char *get_interfaces_ip_static_state(void){
//	int ipaddr_fd = 0 ;
//	char * readBuffer = NULL;
//	int ip_size = 0  ;
//	char *ipbuffer =NULL;
//	ipaddr_fd = open(IP_FILE, O_RDWR);
//	if(ipaddr_fd<0){
//		log_w("open get route gw file error!!.");
//		return 0;
//	}
//	int size = lseek(ipaddr_fd,0,SEEK_END);						//用lseek函数返回文件的大小
//	lseek(ipaddr_fd,0,SEEK_SET);								//上面的函数会将光标移至末尾，用SEEK_SET,将光标返回文件
//	readBuffer = (char *)malloc(sizeof(char) * size + 64 ); //为存放原文件代码开辟空间（后面加八作为缓冲区）
//	if(readBuffer==NULL){
//		log_e("malloc error !! ");
//		return 0;
//	}
//	memset(readBuffer,0,sizeof(char) * size + 64);
//	read(ipaddr_fd,readBuffer,size);				//将原文件的数据保存到readBuffer
//	lseek(ipaddr_fd,0,SEEK_SET);								//光标复位
//	close(ipaddr_fd);										//将文件从动态区返回静态
//	char *ip_start = strstr(readBuffer,"iface eth0 inet");		//调用strstr函数找到第一次出现“LENGTH=”的位置，将光标移至L处
//	if(ip_start == NULL ){
//		log_w("find iface eth0 inet error!!.\r");
//		free(readBuffer);
//		return 0;
//	}
//	ip_start = ip_start + strlen("iface eth0 inet ");
//
//	char *ip_end = strstr(readBuffer,"address");		//调用strstr函数找到第一次出现“LENGTH=”的位置，将光标移至L处
//	if(ip_end == NULL ){
//		log_w("find address error!!.\r");
//		free(readBuffer);
//		return 0;
//	}
//	ip_size =  (sizeof(char) *(ip_end - ip_start)) -1; //计算ip的长度
//	ipbuffer = (char *)malloc( ip_size+64 ); //为存放原文件代码开辟空间（后面加八作为缓冲区）
//	if(ipbuffer==NULL){
//		log_e("malloc error !! ");
//		return 0;
//	}
//	memset(ipbuffer,0,ip_size + 64);
//    for(int i = 0 ; i<ip_size ;i++ ){ 				//将光标向后偏移至要修改的位置
//    	ipbuffer[i]=*(ip_start+i);
//    }
//    free(readBuffer);
//	return ipbuffer ;
//}

/**
  * @brief      获取系统/etc/network/interfaces 中IP地址信息
  *
  * @param[in]
  */
//char *get_interfaces_ipaddr(void){
//	int ipaddr_fd = 0 ;
//	char * readBuffer = NULL;
//	int ip_size = 0  ;
//	char *ipbuffer =NULL;
//	ipaddr_fd = open(IP_FILE, O_RDWR);
//	if(ipaddr_fd<0){
//		log_w("open get ipaddr file error!!.");
//		return 0;
//	}
//	int size = lseek(ipaddr_fd,0,SEEK_END);						//用lseek函数返回文件的大小
//	lseek(ipaddr_fd,0,SEEK_SET);								//上面的函数会将光标移至末尾，用SEEK_SET,将光标返回文件
//	readBuffer = (char *)malloc(sizeof(char) * size + 64 ); //为存放原文件代码开辟空间（后面加八作为缓冲区）
//	if(readBuffer==NULL){
//		log_e("malloc error !! ");
//		return 0;
//	}
//	memset(readBuffer,0,sizeof(char) * size + 64);
//	read(ipaddr_fd,readBuffer,size);				//将原文件的数据保存到readBuffer
//	lseek(ipaddr_fd,0,SEEK_SET);								//光标复位
//	close(ipaddr_fd);										//将文件从动态区返回静态
//	char *ip_start = strstr(readBuffer,"address");		//调用strstr函数找到第一次出现“LENGTH=”的位置，将光标移至L处
//	if(ip_start == NULL ){
//		log_w("find address error!!.\r");
//		free(readBuffer);
//		return 0;
//	}
//	ip_start = ip_start + strlen("address ");
//
//	char *ip_end = strstr(readBuffer,"netmask");		//调用strstr函数找到第一次出现“LENGTH=”的位置，将光标移至L处
//	if(ip_end == NULL ){
//		log_w("find netmask error!!.\r");
//		free(readBuffer);
//		return 0;
//	}
//	ip_size =  (sizeof(char) *(ip_end - ip_start)) -1; //计算ip的长度
//	ipbuffer = (char *)malloc( ip_size+64 ); //为存放原文件代码开辟空间（后面加八作为缓冲区）
//	if(ipbuffer==NULL){
//		log_e("malloc error !! ");
//		return 0;
//	}
//	memset(ipbuffer,0,ip_size + 64);
//    for(int i = 0 ; i<ip_size ;i++ ){ 				//将光标向后偏移至要修改的位置
//    	ipbuffer[i]=*(ip_start+i);
//    }
//    free(readBuffer);
//	return ipbuffer ;
//}
//
///**
//  * @brief      获取系统/etc/network/interfaces 中子网掩码信息
//  *
//  * @param[in]
//  */
//
//char *get_interfaces_netmask(void){
//	int ipaddr_fd = 0 ;
//	char * readBuffer = NULL;
//	int ip_size = 0  ;
//	char *ipbuffer =NULL;
//	ipaddr_fd = open(IP_FILE, O_RDWR);
//	if(ipaddr_fd<0){
//		log_e("open get netmask file error!!.");
//		return 0;
//	}
//	int size = lseek(ipaddr_fd,0,SEEK_END);						//用lseek函数返回文件的大小
//	lseek(ipaddr_fd,0,SEEK_SET);								//上面的函数会将光标移至末尾，用SEEK_SET,将光标返回文件
//	readBuffer = (char *)malloc(sizeof(char) * size + 64 ); //为存放原文件代码开辟空间（后面加八作为缓冲区）
//	if(readBuffer == NULL ){
//		log_e("malloc error!!.\r");
//		return 0;
//	}
//	memset(readBuffer,0,sizeof(char) * size + 64);
//	read(ipaddr_fd,readBuffer,size);				//将原文件的数据保存到readBuffer
//	lseek(ipaddr_fd,0,SEEK_SET);								//光标复位
//	close(ipaddr_fd);										//将文件从动态区返回静态
//	char *ip_start = strstr(readBuffer,"netmask");		//调用strstr函数找到第一次出现“LENGTH=”的位置，将光标移至L处
//	if(ip_start == NULL ){
//		log_e("find netmask error!!.\r");
//		return 0;
//	}
//	ip_start = ip_start + strlen("netmask ");
//
//	char *ip_end = strstr(readBuffer,"network");		//调用strstr函数找到第一次出现“LENGTH=”的位置，将光标移至L处
//	if(ip_end == NULL ){
//		log_e("find network error!!.\r");
//		return 0;
//	}
//	ip_size =  (sizeof(char) *(ip_end - ip_start)) -1; //计算ip的长度
//	ipbuffer = (char *)malloc( ip_size+64 ); //为存放原文件代码开辟空间（后面加八作为缓冲区）
//	if(ipbuffer == NULL ){
//		log_e("malloc error!!.\r");
//		return 0;
//	}
//	memset(ipbuffer,0,ip_size + 64);
//    for(int i = 0 ; i<ip_size ;i++ ){ 				//将光标向后偏移至要修改的位置
//    	ipbuffer[i]=*(ip_start+i);
//    }
//	return ipbuffer ;
//}

/**
  * @brief      获取系统/etc/network/interfaces 中网关信息
  *
  * @param[in]
  */

//char *get_interfaces_route_gw(void){
//	int ipaddr_fd = 0 ;
//	char * readBuffer = NULL;
//	int ip_size = 0  ;
//	char *ipbuffer =NULL;
//	ipaddr_fd = open(IP_FILE, O_RDWR);
//	if(ipaddr_fd<0){
//		log_e("open get route gw file error!!.");
//		return 0;
//	}
//	int size = lseek(ipaddr_fd,0,SEEK_END);						//用lseek函数返回文件的大小
//	lseek(ipaddr_fd,0,SEEK_SET);								//上面的函数会将光标移至末尾，用SEEK_SET,将光标返回文件
//	readBuffer = (char *)malloc(sizeof(char) * size + 64 ); //为存放原文件代码开辟空间（后面加八作为缓冲区）
//	if(readBuffer == NULL ){
//		log_e("malloc error!!.\r");
//		return 0;
//	}
//	memset(readBuffer,0,sizeof(char) * size + 64);
//	read(ipaddr_fd,readBuffer,size);				//将原文件的数据保存到readBuffer
//	lseek(ipaddr_fd,0,SEEK_SET);								//光标复位
//	close(ipaddr_fd);										//将文件从动态区返回静态
//	char *ip_start = strstr(readBuffer,"network");		//调用strstr函数找到第一次出现“LENGTH=”的位置，将光标移至L处
//	if(ip_start == NULL ){
//		log_e("find network error!!.\r");
//		free(readBuffer);
//		return 0;
//	}
//	ip_start = ip_start + strlen("network ");
//
//	char *ip_end = strstr(readBuffer,"broadcast");		//调用strstr函数找到第一次出现“LENGTH=”的位置，将光标移至L处
//	if(ip_end == NULL ){
//		log_e("find broadcast error!!.\r");
//		free(readBuffer);
//		return 0;
//	}
//	free(readBuffer);
//	ip_size =  (sizeof(char) *(ip_end - ip_start)) -1; //计算ip的长度
//	ipbuffer = (char *)malloc( ip_size+64 ); //为存放原文件代码开辟空间（后面加八作为缓冲区）
//	if(ipbuffer == NULL ){
//		log_e("malloc error!!.\r");
//		return 0;
//	}
//	memset(ipbuffer,0,ip_size + 64);
//    for(int i = 0 ; i<ip_size ;i++ ){ 				//将光标向后偏移至要修改的位置
//    	ipbuffer[i]=*(ip_start+i);
//    }
//	return ipbuffer ;
//}
/**
  * @brief      获取系统/etc/network/interfaces 中路由信息
  *
  * @param[in]
  */

//char *get_interfaces_broadcast(void){
//	int ipaddr_fd = 0 ;
//	char * readBuffer = NULL;
//	int ip_size = 0  ;
//	char *ipbuffer =NULL;
//	ipaddr_fd = open(IP_FILE, O_RDWR);
//	if(ipaddr_fd<0){
//		log_e("open broadcast file error!!.");
//		return 0;
//	}
//	int size = lseek(ipaddr_fd,0,SEEK_END);						//用lseek函数返回文件的大小
//	lseek(ipaddr_fd,0,SEEK_SET);								//上面的函数会将光标移至末尾，用SEEK_SET,将光标返回文件
//	readBuffer = (char *)malloc(sizeof(char) * size + 64 ); //为存放原文件代码开辟空间（后面加八作为缓冲区）
//	if(readBuffer == NULL ){
//		log_e("malloc error!!.\r");
//		return 0;
//	}
//	memset(readBuffer,0,sizeof(char) * size + 64);
//	read(ipaddr_fd,readBuffer,size);				//将原文件的数据保存到readBuffer
//	lseek(ipaddr_fd,0,SEEK_SET);								//光标复位
//	close(ipaddr_fd);										//将文件从动态区返回静态
//	char *ip_start = strstr(readBuffer,"#");		//调用strstr函数找到第一次出现“LENGTH=”的位置，将光标移至L处
//	if(ip_start == NULL ){
//		free(readBuffer);
//		log_e("find # error!!.\r");
//		return 0;
//	}
//
//	char *ip_end = strstr(readBuffer,"broadcast");		//调用strstr函数找到第一次出现“LENGTH=”的位置，将光标移至L处
//	if(ip_end == NULL ){
//		log_e("find broadcast error!!.\r");
//		free(readBuffer);
//		return 0;
//	}
//	ip_size = size - (sizeof(char) *(ip_end - ip_start))+strlen("broadcast ")-3; //计算ip的长度
//	ipbuffer = (char *)malloc( ip_size+64 ); //为存放原文件代码开辟空间（后面加八作为缓冲区）
//	if(ipbuffer == NULL ){
//		log_e("malloc error!!.\r");
//		return 0;
//	}
//	memset(ipbuffer,0,ip_size + 64);
//    for(int i = 0 ; i<ip_size ;i++ ){ 				//将光标向后偏移至要修改的位置
//    	if(*(ip_start+(sizeof(char) *(ip_end - ip_start))+strlen("broadcast ")+i+1) == '\0'){  //剔除 换行
////    		log_w("exit 1 ipbuffer.");
//    		break ;
//    	}
//    	ipbuffer[i]=*(ip_start+(sizeof(char) *(ip_end - ip_start))+strlen("broadcast ")+i);
//    }
//    free(readBuffer);
//    return ipbuffer ;
//}







static int get_eth0_state(void) {
	int eth0_fd = -1;
	char path[64] = { 0 };
	char eth0_state[3] = { 0 };
	sprintf(path, "/sys/class/net/eth0/carrier");
	eth0_fd = open(path, O_RDONLY);
	if (eth0_fd < 0) {
		log_e("Failed to open eth0 value for reading!");
		return -1;
	}
	if (read(eth0_fd, eth0_state, 1) < 0) {
		close(eth0_fd);
		log_e("Failed to read eth0 value!");
		return -1;
	}
	close(eth0_fd);
	return (atoi(eth0_state));
}



//static int detect_eth_cable(char *eth){
//    struct ethtool_value edata;
//    int fd = -1, err = 0;
//    struct ifreq ifr;
//
//    fd = socket(AF_INET, SOCK_DGRAM, 0);
//    if (fd < 0) {
//		perror("Cannot get control socket");
//		return 0;
//    }
//    memset(&ifr, 0, sizeof(ifr));
//    strcpy(ifr.ifr_name, eth);
//    edata.cmd = 0x0000000a;
//    ifr.ifr_data = (caddr_t)&edata;
//    err = ioctl(fd, 0x8946, &ifr);
//    if (err == 0) {
//    	close(fd);
//        return edata.data;
//    }else if(err < 0){
//    	close(fd);
//    	perror("Cannot get link status");
//    }
//
//   return 0;
//}


