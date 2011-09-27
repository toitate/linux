
#include <stdio.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <netdb.h>


int
main(int argc, char *argv[])
{
	int sock;
	char buf[32];
	int PORT = 12345;
    struct sockaddr_in server;

	unsigned int **addrptr;

	if (argc != 2) {
		printf("Usage : %s dest\n", argv[0]);
		return 1;
	}

	if ((sock=socket(AF_INET, SOCK_STREAM, 0)) < 0) {
		perror("socket");
		return 1;
	}

	server.sin_family = AF_INET;
	server.sin_port = htons(PORT);
	server.sin_addr.s_addr = inet_addr(argv[1]);
	if (server.sin_addr.s_addr == 0xffffffff) {
		struct hostent *host;
		host = gethostbyname(argv[1]);
		if (host == NULL) {
			if (h_errno == HOST_NOT_FOUND) {
				printf("host not found : %s\n", argv[1]);
			} else {
				printf("%s : %s\n", hstrerror(h_errno), argv[1]);
			}
			return 1;
		}

	 	addrptr = (unsigned int **)host->h_addr_list;
	 	while (*addrptr != NULL) {
			server.sin_addr.s_addr = *(*addrptr);

			if (connect(sock, (struct sockaddr *)&server, sizeof(server)) == 0) {
				break;
			}
			addrptr++;
		}
		if (*addrptr == NULL) {
			perror("connect");
			return 1;
		}
	} else {
		if ((connect(sock,(struct sockaddr *)&server, sizeof(server))) != 0) {
			perror("connect");
			return 1;
		}
	}
	memset(buf, 0, sizeof(buf));
	snprintf(buf, sizeof(buf), "GET / HTTP/1.0\r\n\r\n");

	int n = write(sock, buf, sizeof(buf));
	if (n < 0) {
		perror("write");
		return 1;
	}

	printf("Send : %d %send\n", n, buf);
	while (n > 0) {
		memset(buf, 0, sizeof(buf));
		n = read(sock, buf, sizeof(buf));
		if (n < 0) {
			perror("read");
			return 1;
		}
		write(1, buf, n);
	}
	close(sock);
	return 0;
}

