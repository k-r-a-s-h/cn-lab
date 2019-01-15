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
	init_SA(&server, AF_INET, htons(PORT), htonl(INADDR_ANY));

	int bind_status = bind(sockfd, (const SA*)&server, sizeof(server));
	if(bind_status < 0) ERROR();
	else printf("Socket bound.\n");

	int listen_status = listen(sockfd, 1);
	if(listen_status < 0) ERROR_CLOSE(sockfd);
	else printf("Socket listening.\n");

	SA_IN client;
	int client_len = sizeof(client);

	int clientfd = accept(sockfd, (SA*)&client, &client_len);
	if(clientfd < 0) ERROR_CLOSE(sockfd);
	else printf("Client connected.\n");

	int recv_status = recv(clientfd, buffer, sizeof(buffer), 0);
	if(recv_status < 0) ERROR_CLOSE(sockfd);\
	else printf("Recieved: %s\n", buffer);

	printf("Enter your message:\n");
	scanf("%s", buffer);

	int send_status = send(clientfd, buffer, sizeof(buffer), 0);
	if(send_status < 0) ERROR_CLOSE(sockfd);

	close(sockfd);
	return 0;
}

