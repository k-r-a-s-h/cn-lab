#include <string.h>
#include <unistd.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <netinet/in.h>
#include <stdlib.h>
#include <stdio.h>

#define PORT 1311
#define BUFF_SIZE 100

typedef struct sockaddr SA;
typedef struct sockaddr_in SA_IN;
typedef socklen_t LEN;

void init_SA(SA_IN *obj, int family, int port, int address) {
	obj->sin_family = family;
	obj->sin_port = port;
	obj->sin_addr.s_addr = address;
}

void ERROR() {
	printf("An error occured.\n");
	exit(0);
}

void ERROR_CLOSE(int sockfd) {
	printf("An error occured. Closing socket.\n");
	close(sockfd);
	exit(0);
}

int main() {
	char buffer[BUFF_SIZE];

	int sockfd = socket(AF_INET, SOCK_STREAM, 0);
	if(sockfd < 0) ERROR();
	else printf("Socket created.\n");

	SA_IN server;
	init_SA(&server, AF_INET, htons(PORT), inet_addr("127.0.0.1"));
	int server_len = sizeof(server);

	int connect_status = connect(sockfd, (SA*)&server, sizeof(server));
	if(connect_status < 0) ERROR();
	else printf("Connected to server.\n");


//change here
	printf("Enter the file to open:\n");
	scanf("%s", buffer);
	
	int send_status = send(sockfd, buffer, sizeof(buffer), 0);
	if(send_status < 0) ERROR_CLOSE(sockfd);

	

	// int recv_status = recv(sockfd, buffer, sizeof(buffer), 0);
	// if(recv_status < 0) ERROR_CLOSE(sockfd);
	// else printf("Recieved: %s\n", buffer);

	close(sockfd);
	return 0;
}