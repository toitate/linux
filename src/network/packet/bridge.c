
#include <stdio.h>
#include <string.h>
#include <unistd.h>

#include <poll.h>
#include <errno.h>
#include <signal.h>
#include <stdarg.h>

#include <arpa/inet.h>
#include <sys/socket.h>

#include <netinet/if_ether.h>

#include "netutils.h"

typedef struct {
	char *ether01;
	char *ether02;
	int debug_out;
} PARAM;
PARAM param = {"eth0", "eth1", 0};

typedef struct {
	int sockfd;
} DEVICE;
DEVICE device[2];

int end_flag = 0;

int disable_ip_forward();
int analyze_packet_bridge(int device, u_char *data, int size);
int bridge();
void end_signal(int sig);


int main() {


	printf("init_start\n");
	if((device[0].sockfd=init_raw_socket(param.ether01)) == -1) return(-1);
	printf("eth1 is OK");
	if((device[1].sockfd=init_raw_socket(param.ether02)) == -1) return(-1);

	printf("eth0 is OK");
	disable_ip_forward();

	signal(SIGINT, end_signal);
	signal(SIGTERM, end_signal);
	signal(SIGQUIT, end_signal);
	signal(SIGPIPE, end_signal);
	signal(SIGTTIN, end_signal);
	signal(SIGTTOU, end_signal);

	bridge();


	close(device[0].sockfd);
	close(device[1].sockfd);
	return(0);

}


int analyze_packet_bridge(int device, u_char *data, int size) {
	u_char *mdata = data;
	int msize = size;
	struct ether_header *eth;

	if (size < sizeof(struct ether_header)) {
		debug_printf("eth is %d : size is %d\n", device, msize);
		return(-1);
	}
	eth = (struct ether_header *)mdata;
	debug_printf("eth is %d\n", device);
	if (param.debug_out) {
		print_ether_header(eth, stderr);	
	}
	return(0);
}

int bridge(){
	struct pollfd targets[2];
	int nready;
	int i;
	int size;
	u_char buf[2048];

	targets[0].fd = device[0].sockfd;
	targets[0].events = POLLIN|POLLERR;

	targets[1].fd = device[1].sockfd;
	targets[1].events = POLLIN|POLLERR;

	while (end_flag == 0) {
		switch (nready = poll(targets, 2, 100)) {
			case -1:
				if (errno != EINTR) perror("poll");
				break;
			case 0:
				break;
			default:
				for (i=0; i<2; i++) {
					if (targets[i].revents&(POLLIN|POLLERR)) {
						if ((size=read(device[i].sockfd, buf, sizeof(buf))) <= 0) {
							perror("read");
						} else {
							if (analyze_packet_bridge(i, buf, size) != -1) {
								if (size = write(device[!i].sockfd, buf, size) <= 0) {
									perror("write");
								}
							}
						}
					}
				}
				break;
		}
	}

	return(0);
}

