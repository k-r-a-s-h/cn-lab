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
    char buffer2[BUFF_SIZE];
    char buffer1[BUFF_SIZE];
    char buffer[BUFF_SIZE];
    int sockfd = socket(AF_INET,SOCK_DGRAM,0);
    if(sockfd<0) ERROR();
    else printf("Socket Created\n");

    SA_IN clientaddr,serveraddr;
    init_SA(&serveraddr,AF_INET,htons(PORT),htonl(INADDR_ANY));
    init_SA(&clientaddr,AF_INET,htons(PORT+1),htonl(INADDR_ANY));
    int bind_status = bind(sockfd,(const SA*)&clientaddr,sizeof(clientaddr));
    if(bind_status<0) ERROR_CLOSE(sockfd);
    else
    {
        printf("bind completed\n");
    }
    

    socklen_t len=sizeof(clientaddr);
    // int recv_status=recvfrom(sockfd,buffer,sizeof(buffer),0,(SA*)&clientaddr,&len);
    // if(recv_status<0){
    //     printf("%d",recv_status);
    //     ERROR_CLOSE(sockfd);

    // } 
    // else {
    //     buffer[recv_status]='\0';
    // }
    int pid=fork();
    if(pid > 0){
        while(1){
            int recv_status=recvfrom(sockfd,buffer1,sizeof(buffer1),0,(SA*)&serveraddr,&len);
            if(recv_status<0)ERROR_CLOSE(sockfd);
            else{
                printf("Client: %s \n",buffer1);
                memset(buffer1,0,sizeof(buffer1));
            }
        }
        
    }else if (pid == 0){
        
        while(1){
            scanf("%s",buffer2);
            int send_status=sendto(sockfd,(const char*)buffer2,sizeof(buffer2),0,(const SA*)&serveraddr,len);
            //hre we have th error.
                    // printf("Child process1");    

            if(send_status<0) ERROR_CLOSE(sockfd);
                    // printf("Child process2");    

            memset(buffer2,0,sizeof(buffer2));
        }
        
    }

    // char buffer_send[BUFF_SIZE];
    // printf("enter the message\n");
    // scanf("%s",buffer_send);

    // int snd_status=sendto(sockfd,(const char*)buffer_send,strlen(buffer_send),0,(const SA*)&clientaddr,len);
    // if(snd_status<0) ERROR_CLOSE(sockfd);
    // else printf("message sent");
    close(sockfd);
    return 0;
}