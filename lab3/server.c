#include <string.h>
#include <strings.h>
#include <unistd.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <netinet/in.h>
#include <stdlib.h>
#include <stdio.h>



#define PORT1 1315//recv
// #define PORT2 1313//send
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
	
	

	int pid;
	//recv server
		int sockfd1 = socket(AF_INET, SOCK_STREAM, 0);
		if(sockfd1< 0) ERROR();
		else printf("Socket1 created.\n");

		SA_IN server1;
		init_SA(&server1, AF_INET, htons(PORT1), htonl(INADDR_ANY));

		int bind_status1 = bind(sockfd1, (const SA*)&server1, sizeof(server1));
		if(bind_status1 < 0) ERROR();
		else printf("Socket1 bound.\n");

		int listen_status1= listen(sockfd1, 1);
		if(listen_status1 < 0) ERROR_CLOSE(sockfd1);
		else printf("Socket1 listening.\n");

		SA_IN client1;
		int client_len = sizeof(client1);

		int clientfd1 = accept(sockfd1, (SA*)&client1, &client_len);
		if(clientfd1 < 0) ERROR_CLOSE(sockfd1);
		else printf("Client1 connected.\n");

	pid=fork();
	if(pid!=0){
		

		while(1){
			char buffer1[BUFF_SIZE];
			int recv_status = recv(clientfd1, buffer1, sizeof(buffer1), 0);
			if(recv_status < 0) ERROR_CLOSE(sockfd1);
			else printf("client: %s \n", buffer1);
						memset(buffer1 , 0, sizeof(buffer1));

		}


	}
	else{

		//sending server
		

		while(1){
			//printf("\n");;
			char buffer2[BUFF_SIZE];
			scanf("%s",buffer2);
			int send_status2 = send(clientfd1, buffer2, sizeof(buffer2), 0);
			if(send_status2 < 0) ERROR_CLOSE(sockfd1);
			memset(buffer2,0,sizeof(buffer2));
			
		}


	}
}