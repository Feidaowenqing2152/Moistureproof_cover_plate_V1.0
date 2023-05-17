/*
 * eth.h
 *
 *  Created on: 2022年12月30日
 *      Author: 好
 */

#ifndef APP_ETH_H_
#define APP_ETH_H_

#include "../common.h"
//#define IP_FILE  "/root/S99Moistureproof_Update"
#define IP_FILE "/etc/network/interfaces"
#define ETH "eth0"

#define IP_PORT  1883
#define ADDRESS "192.168.2.200"
#define NETMASK "255.255.255.0"
#define GATEWAY "192.168.2.1"
//#define BROADCAST "192.168.0.255"

#define ETH_DHCP_DISABLE "static"    //以太网ip为静态
#define ETH_DHCP_ENABLE  "dhcp"      //以太网ip为dhcp自动动态分配

typedef void (*Eth_Connect_State_Cb)(struct mosquitto *mosq,uint8_t) ;

struct ethtool_value{
	uint32_t cmd;
	uint32_t data;
};
struct eth{
	char eth_name[10];
	char ip_dhcp_state[10];
	char ip_adderss[30];
	char ip_netmask[30];
	char ip_gateway[30];
	unsigned short  port;
};
//eth0_t eth0_gayther;
//extern eth0_t eth0_gayther;



void Eth_Connect_State_Register(struct mosquitto *mosq,Eth_Connect_State_Cb pEthConnectStateFun);
void Eth_Connect_State_UnRegister(Eth_Connect_State_Cb pEthConnectStateFun);
void Eth_Scan_Loop_State(uint16_t scan_time);


int set_sys_eth0_init(void);
void eth0_network_reset(void);
int set_sys_network(struct eth *eth0 ,char *eth0_select);

char *get_interfaces_ip_static_state(void);
char *get_interfaces_ipaddr(void);
//char *get_interfaces_netmask(void);
//char *get_interfaces_route_gw(void);
//char *get_interfaces_broadcast(void);
int network_eth0_dhcp_status(char* iface_name ,struct eth *dhcp_network);

#endif /* APP_ETH_H_ */
