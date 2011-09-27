
#include <stdio.h>
#include <string.h>
#include <unistd.h>

#include <sys/ioctl.h>
#include <arpa/inet.h>
#include <sys/socket.h>
#include <linux/if.h>


#include <poll.h>
#include <errno.h>
#include <signal.h>
#include <stdarg.h>

#include <net/ethernet.h>
#include <netpacket/packet.h>
#include <netinet/if_ether.h>
#include <netinet/ip.h>

#include <netinet/ip6.h>
#include <netinet/ip_icmp.h>
#include <netinet/tcp.h>
#include <netinet/udp.h>

#ifndef ETHERTYPE_IPV6
#define ETHERTYPE_IPV6 0x86dd
#endif



int debug_printf(char *format, ...);
int debug_perror(char *msg);


/*
 * Initialize Raw Socket
 *
 * @param *eth ethernet name
 * @return sockfd socket descriptor
 */
int init_raw_socket(char *eth) {

	struct ifreq ifrq;
	struct sockaddr_ll sa;
	int sockfd;

	printf("inti_raw_socket\n");

	sockfd = socket(PF_PACKET, SOCK_RAW, htons(ETH_P_IP));

	memset(&ifrq, 0, sizeof(struct ifreq));

	/* Get ethernet interface index */
	strncpy(ifrq.ifr_name, eth, sizeof(ifrq.ifr_name)-1);
	if (ioctl(sockfd, SIOCGIFINDEX, &ifrq) < 0) return(-1);
	
	/* Create socket address */
	sa.sll_family = PF_PACKET;
	sa.sll_protocol = htons(ETH_P_IP);
	sa.sll_ifindex = ifrq.ifr_ifindex;

	if (bind(sockfd, (struct sockaddr *)&sa, sizeof(sa)) < 0) return(-1);
	
	/* Set promiss cast ON */
	if(ioctl(sockfd, SIOCGIFFLAGS, &ifrq) < 0) return(-1);
	ifrq.ifr_flags = ifrq.ifr_flags|IFF_PROMISC;
	if(ioctl(sockfd, SIOCSIFFLAGS, &ifrq) < 0) return(-1);

	printf("inti_raw_socket end\n");
	return(sockfd);
}



/* 
 * Get ether header (Mac address)
 *
 * @param *hwaddr
 * @param *buf
 * @param size
 */
char *get_ether_address(u_char *hwaddr, char *buf, socklen_t size) {
	snprintf(buf, size, "%02x:%02x:%02x:%02x:%02x:%02x",
			hwaddr[0], hwaddr[1], hwaddr[2], hwaddr[3], hwaddr[4], hwaddr[5]);
	return(buf);
}

/* 
 * Print ether header
 *
 * @param *eth ethernet packet 
 * @param *fp standard out file descripteor
 * @return 0 success or fail
 */
int print_ether_header(struct ether_header *eth, FILE *fp) {
	char buf[80];

	fprintf(fp, "ethernet packet header***************************\n");
	fprintf(fp, "ethernet destination host Mac address = %s\n", get_ether_address(eth->ether_dhost, buf, sizeof(buf)));
	fprintf(fp, "ethernet sender 			host Mac address = %s\n", get_ether_address(eth->ether_shost, buf, sizeof(buf)));
	fprintf(fp, "ethernet type 				= %02x\n", ntohs(eth->ether_type));
	switch (ntohs(eth->ether_type)) {
		case ETH_P_IP:
			fprintf(fp, "(IP)\n");
			break;
		case ETH_P_IPV6:
			fprintf(fp, "(IPV6)\n");
			break;
		case ETH_P_ARP:
			fprintf(fp, "(ARP)\n");
			break;
		default:
			fprintf(fp, "(unknown)\n");
			break;
	}
	return(0);
}

int print_ip_header() {
	
	return(0);
}


int debug_printf(char *format, ...) {
	if (1) {
		va_list args;
		va_start(args, format);
		vfprintf(stderr, format, args);
		va_end(args);
	}
	return(0);
}

int debug_perror(char *msg) {
	if(1) {
		fprintf(stderr, "%s : %s\n", msg, strerror(errno));
	}
	return(0);
}


int disable_ip_forward(){
	FILE *fp;
	
	if ((fp=fopen("/proc/sys/net/ipv4/ip_forward\n", "w")) == NULL) {
		debug_printf("can not open /ip\n");
		return(-1);
	}
	fputs("0", fp);
	fclose(fp);
	return(0);
}


int end_flag = 0;
void end_signal(int sig) {
	end_flag = 1;
}
