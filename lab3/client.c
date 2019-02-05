#include <string.h>
#include <strings.h>
#include <unistd.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <netinet/in.h>
#include <stdlib.h>
#include <stdio.h>



#define PORT1 1315//send
// #define PORT2 1313//recv
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

int main(){
	char buffer1[BUFF_SIZE];
	char buffer2[BUFF_SIZE];

	int pid;

		int sockfd1 = socket(AF_INET, SOCK_STREAM, 0);
		if(sockfd1 < 0) ERROR();
		else printf("Socket1 created.\n");

		SA_IN server1;
		init_SA(&server1, AF_INET, htons(PORT1), inet_addr("127.0.0.1"));
		int server1_len = sizeof(server1);

		int connect_status1 = connect(sockfd1, (SA*)&server1, sizeof(server1));
		if(connect_status1< 0) ERROR();
		else printf("Connected to server1.\n");


	pid=fork();


	if(pid!=0){
		//send process
		
		while(1){
			scanf("%s", buffer1);
			int send_status = send(sockfd1, buffer1, sizeof(buffer1), 0);
			if(send_status < 0) ERROR_CLOSE(sockfd1);
			memset(buffer1 , 0, sizeof(buffer1));
		}

	}
	else{
		

		while(1){
			// printf("\n" );
			int recv_status = recv(sockfd1, buffer2, sizeof(buffer2), 0);
			if(recv_status < 0) ERROR_CLOSE(sockfd1);
			else {
				printf(" server : %s  \n",buffer2);
			}
			memset(buffer2,0,sizeof(buffer2));
		}

	}
}