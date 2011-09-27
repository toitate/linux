
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

#ifndef ETHERTYPE_IPV6
#define ETHERTYPE_IPV6 0x86dd
#endif

int IPFLAG = 1;

int analyze_packet(u_char *data, int size);
int analyze_arp	  (u_char *data, int size);
int analyze_ip	  (u_char *data, int size);

int print_icmp(u_char *data, int size);

/* analyze packet *********************************************************/

/*
 *
 */
int analyze_packet(u_char *data, int size) {
	u_char *mdata = data;
	int    msize  = size;
	struct ether_header *eth = (struct ether_header *)mdata;

	if (msize < sizeof(struct ether_header)) return(-1);

	if (ntohs(eth->ether_type) == ETHERTYPE_ARP) { 
		fprintf(stdout, "Ethertype ARP Packet = %d bytes\n", size);
		//print_ether_header(eth, stdout);
		analyze_arp(mdata+sizeof(struct ether_header), msize-sizeof(struct ether_header)); 
	}
	else if (ntohs(eth->ether_type) == ETHERTYPE_IP) { 
		if (IPFLAG == 1) {
			fprintf(stdout, "Ethertype IP Packet = %d bytes\n", size);
			print_ether_header(eth, stdout);
			analyze_ip(mdata+sizeof(struct ether_header), msize-sizeof(struct ether_header)); 
		}
	}
	else if (ntohs(eth->ether_type) == ETHERTYPE_IPV6) { 
		fprintf(stdout, "EtherType IPv6 Packet = %d bytes\n", size);
	} else {
		fprintf(stdout, "Unknown Packet = %d bytes\n", size);
	}

	return(0);
}


int analyze_arp(u_char *data, int size) {
	
	u_char *mdata = data;
	int msize = size;
	struct ether_arp *arp;

	if (msize < sizeof(struct ether_arp)) return(-1);

	arp = (struct ether_arp *)mdata;
	mdata += sizeof(struct ether_arp); // TODO No need
	msize -= sizeof(struct ether_arp); // TODO No need
	
	//print_arp(arp, stdout);
	printf("arp packet\n");

	return(0);
}

int analyze_ip(u_char *data, int size) {
	
	u_char *mdata = data;
	int msize = size;
	struct iphdr *miphdr = (struct iphdr *)mdata;

	u_char *option;
	int option_len;
	int length;
	unsigned short sum;
	
	if (msize < sizeof(struct iphdr)) return(-1);

	miphdr = (struct iphdr *)mdata;
	mdata += sizeof(struct iphdr);
	msize -= sizeof(struct iphdr);

	option_len = miphdr->ihl*4 - sizeof(struct iphdr); // TODO 
	if ( option_len > 0 ) {
		if ( option_len >= 1500 ) return(-1);
		option = mdata;
		mdata += option_len;
		msize -= option_len;
	}

//	if (checksum_ip(miphdr, option, option_len) == 0) return(-1);
	
//	print_ip_header(miphdr, option, option_len, stdout);

	if (miphdr->protocol == IPPROTO_ICMP) {
		printf("ICMP\n");
		print_icmp(mdata+sizeof(struct iphdr), msize-sizeof(struct iphdr)); 
	} else if (miphdr->protocol == IPPROTO_TCP) {

		printf("TCP\n");
	} else if (miphdr->protocol == IPPROTO_UDP) {

		printf("UDP\n");
	}

	return(0);
}


int print_icmp(u_char *data, int size) {
	return(0);
}
