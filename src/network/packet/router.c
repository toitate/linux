/*

net-newbie.com/tcpip/packets.html

TCP Packet

"struct ether_header {}" + 
	"struct iphder {}" + 
		"data"

*/

#include <stdio.h>
#include <string.h>
#include <unistd.h>

#include <sys/ioctl.h>
#include <arpa/inet.h>
#include <sys/socket.h>
#include <linux/if.h>

#include <net/ethernet.h>
#include <netpacket/packet.h>
#include <netinet/if_ether.h>
#include <netinet/ip.h>

#include <netinet/ip6.h>
#include <netinet/ip_icmp.h>
#include <netinet/tcp.h>
#include <netinet/udp.h>

#include "netutils.h"
#include "analyze.h"

#include "router.h"

/*
 * 
 * 
 * "Domain" 		= PF_PACKET
 * 		"Socket Address" = struct sockaddr_ll
 * "Type" 		= SOCK_RAW
 * "Protocol" 	= ETH_P_IP, ETH_P_ALL
 * "Interface" 
 * "Promiss Cast" = NO, OFF
 *
 */

typedef struct {
	char *device1;
	char *device2;
	char *next_router;
} PARAM;
PARAM Param = {"eth1", "eth2", "192.168.1.101"};

struct in_addr next_router;

DEVICE Device[2];

int end_flag = 0;

pthread_t buftid;

int main() {

	int sockfd;
	int size;
	u_char buf[65535];

	if((sockfd=init_raw_socket("eth1")) == -1) return(-1);

/*	get_ether_info() {
	}*/
	
	while (1) {
		if((size=read(sockfd, buf, sizeof(buf))) <= 0) perror("read()");		
		analyze_packet(buf, size);
	}

	close(sockfd);
	return(0);

}

