#include <string.h>
#include <unistd.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <netinet/in.h>
#include <stdlib.h>
#include <stdio.h>

#define PORT 8585
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

	int num;
	printf("Enter the size of array:\n");
	scanf("%d", &num);
	
	int send_status = send(sockfd, &num, sizeof(num), 0);
	if(send_status < 0) ERROR_CLOSE(sockfd);
	int i=0;
	int lol=0;
	for (i=0;i<num;i++){
		printf("enter the number ");
		scanf("%d",&lol);

		int send_status = send(sockfd, &lol, sizeof(lol), 0);
		if(send_status < 0) ERROR_CLOSE(sockfd);
	}
	printf("enter the number to be searched in the araay ");
	scanf("%d",&lol);

	send_status=send(sockfd,&lol,sizeof(lol),0);
	if(send_status<0) ERROR_CLOSE(sockfd);

	int flag;
	int recv_status=recv(sockfd,&flag,sizeof(flag),0);
	if(recv_status<0) ERROR_CLOSE(sockfd);

	if(flag==-1){
		printf("\nElement Not found");
	}
	else{
		printf("\nElemen found at %d",flag);
	}


	close(sockfd);
	return 0;
}