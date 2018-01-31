#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <netinet/tcp.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <netinet/in.h>
#include<arpa/inet.h>
#include <netdb.h>

#define BUFFER_SIZE 1024
int main(int argc, char *argv[]){
	int fd;
	char buffer[BUFFER_SIZE];
	int on = 1, sock;
	struct sockaddr_in addr;

    addr.sin_addr.s_addr = inet_addr("14.35.235.162") ;
	addr.sin_port = htons(80);
	addr.sin_family = AF_INET;
	sock = socket(PF_INET, SOCK_STREAM, IPPROTO_TCP);
	setsockopt(sock, IPPROTO_TCP, TCP_NODELAY, (const char *)&on, sizeof(int));

	if(sock == -1){
		perror("setsockopt");
		exit(1);
	}
	if(connect(sock, (struct sockaddr *)&addr, sizeof(struct sockaddr_in)) == -1){
		perror("connect");
		exit(1);
	}
	write(sock, "GET / HTTP/1.0\r\nHost: 14.35.235.162\r\n\r\n\r\n", strlen("GET / HTTP/1.0\r\nHost: 14.35.235.162\r\n\r\n\r\n"));
	bzero(buffer, BUFFER_SIZE);

	while(read(sock, buffer, BUFFER_SIZE - 1) != 0){
		fprintf(stderr, "%s", buffer);
		bzero(buffer, BUFFER_SIZE);
	}
	shutdown(sock, SHUT_RDWR);
	close(sock);
	return 0;

}

