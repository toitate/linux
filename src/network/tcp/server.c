
#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>

/*
Domain = AF_INET;
Type = SOCK_STREAM;
Protocol = TCP;

*/

#define MAXDATA 2048

void parse_request(char in_buf[]);
void create_response(char out_buf[], int size);
void replay_thread(void *fd);

int
main()
{
	int s_sock;
	int c_sock;
	struct sockaddr_in s_addr;
	struct sockaddr_in c_addr;

	pthread_t tcp_thread;

	int PORT = 12345;

	int c_len;
	int option = 1;

	char in_buf[MAXDATA];
	char out_buf[MAXDATA];
    
	if ((s_sock = socket(AF_INET, SOCK_STREAM, 0)) < 0) {
		perror("socket");
		return 1;
	}

	s_addr.sin_family = AF_INET;
	s_addr.sin_port = htons(PORT);
	s_addr.sin_addr.s_addr = INADDR_ANY;//TODO

	setsockopt(s_sock,SOL_SOCKET, SO_REUSEADDR, (const char *)&option, sizeof(option)); // TODO option

	if (bind(s_sock, (struct sockaddr *)&s_addr, sizeof(s_addr)) != 0) {
		perror("bind");
		return 1;
	}

	if (listen(s_sock, 5) != 0) {
		perror("listen");
		return 1;
	}

	while (1) {
		c_len = sizeof(c_addr);
		if ((c_sock=accept(s_sock, (struct sockaddr *)&c_addr, (socklen_t *)&c_len)) < 0) {
			perror("accept");
			break;
		}

		if (pthread_create( &tcp_thread, NULL, (void *)replay_thread, (void *)c_sock) != 0) {
			perror("pthread_create");
			exit(EXIT_FAILURE);
		}
		pthread_detach(tcp_thread);
	}
	close(s_sock);
	return 0;
}


void replay_thread(void *fd) {
	int c_sock = (int)fd;
	char in_buf[MAXDATA];
	char out_buf[MAXDATA];
	int size;

	// TODO
	/*while(1) {
		memset(in_buf, 0, sizeof(in_buf));
		size = 0;
		size = read(c_sock, in_buf, sizeof(in_buf));
		if (size == 0) {
			break;
		} else if (size == -1) {
			perror("read");
			exit(EXIT_FAILURE);
		} else {
			parse_request(in_buf);
		}
	}*/

	memset(in_buf, 0, sizeof(in_buf));
	size = read(c_sock, in_buf, sizeof(in_buf));
	parse_request(in_buf);

	memset(out_buf, 0, sizeof(out_buf));
	create_response(out_buf, sizeof(out_buf));
	write(c_sock, out_buf, sizeof(out_buf));

	if ( close(c_sock) < 0) {
		perror("close");
		exit(EXIT_FAILURE);
	}
	printf("Thread Connection closed.\n");
}

void parse_request(char in_buf[]) {

	printf("%s", in_buf);
}

void create_response(char out_buf[], int size) {

	snprintf(out_buf, size,
		"HTTP/1.0 200 OK\r\n"
		"Content-Length: 20\r\n"
		"Content-Type: text/html\r\n"
		"\r\n"
		"Oitate Server\r\n");
}


