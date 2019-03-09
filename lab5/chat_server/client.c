#include <string.h>
#include <unistd.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <netinet/in.h>
#include <stdlib.h>
#include <stdio.h>

#define PORT 2300
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
	int sockfd = socket(AF_INET,SOCK_DGRAM,0);
	if(sockfd<0) ERROR();
	else printf("socket created\n");

	SA_IN server,client;
	init_SA(&server,AF_INET,htons(PORT),inet_addr("127.0.0.1"));
	init_SA(&client,AF_INET,htons(PORT+1),inet_addr("127.0.0.1"));
	
	int bind_status = bind(sockfd,(const SA*)&server,sizeof(server));
    if(bind_status<0) ERROR_CLOSE(sockfd);
    else
    {
        printf("bind completed\n");
    }
	int len;
    int pid=fork();
    if(pid > 0){
        while(1){
            scanf("%s",buffer1);
            int send_status=sendto(sockfd,(const char*)buffer1,sizeof(buffer1),0,(const SA*)&client,sizeof(client));
            if(send_status<0) ERROR_CLOSE(sockfd);
            memset(buffer1,0,sizeof(buffer1));
        }
        
    }
    else if(pid == 0){
        while(1){
            int recv_status=recvfrom(sockfd,buffer2,sizeof(buffer2),0,(SA*)&client,&len);
            if(recv_status < 0) ERROR_CLOSE(sockfd);
			else {
				printf("server : %s  \n",buffer2);
			}
			memset(buffer2,0,sizeof(buffer2));
        }
        
    }
    
	// int send_status=sendto(sockfd,(const char*)buffer,strlen(buffer),0,(const SA*)&server,sizeof(server));
	// if(send_status<0) ERROR_CLOSE(sockfd);
	// else printf("message sent\n");

	// char buffer_send[BUFF_SIZE];
	// int recv_status =recvfrom(sockfd,(char*)buffer_send,sizeof(buffer_send),0,(SA*)&server,&len);
	// if(recv_status<0) ERROR_CLOSE(sockfd);
	// else {
	// 	buffer_send[recv_status]='\0';
	// 	printf("Server : %s \n",buffer_send);
	// }

	close(sockfd);
	return 0 ;
    
}