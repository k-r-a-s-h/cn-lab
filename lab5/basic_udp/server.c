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
    char buffer[BUFF_SIZE];
    int sockfd = socket(AF_INET,SOCK_DGRAM,0);
    if(sockfd<0) ERROR();
    else printf("Socket Created\n");

    SA_IN clientaddr,serveraddr;
    init_SA(&serveraddr,AF_INET,htons(PORT),htonl(INADDR_ANY));

    int bind_status = bind(sockfd,(const SA*)&serveraddr,sizeof(serveraddr));
    if(bind_status<0) ERROR_CLOSE(sockfd);
    else
    {
        printf("bind completed\n");
    }
    

    int len=sizeof(clientaddr);
    int recv_status=recvfrom(sockfd,buffer,sizeof(buffer),0,(SA*)&clientaddr,&len);
    if(recv_status<0){
        printf("%d",recv_status);
        ERROR_CLOSE(sockfd);

    } 
    else {
        buffer[recv_status]='\0';
    }

    printf("Client: %s \n",buffer);

    char buffer_send[BUFF_SIZE];
    printf("enter the message\n");
    scanf("%s",buffer_send);

    int snd_status=sendto(sockfd,(const char*)buffer_send,strlen(buffer_send),0,(const SA*)&clientaddr,len);
    if(snd_status<0) ERROR_CLOSE(sockfd);
    else printf("message sent");
    close(sockfd);
    return 0;
}