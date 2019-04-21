#include <string.h>
#include <unistd.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <netinet/in.h>
#include <stdio.h>
#include <stdio.h>

#define PORT 2100
#define BUFF_SIZE 100 
typedef struct sockaddr SA;
typedef struct sockaddr_in SA_IN;

void init_SA(SA_IN* obj,int address,int family,int port){
    obj->sin_family=family;
    obj->sin_port=port;
    obj->sin_addr.s_addr=address;
}

void ERROR(){
    printf("error occured.\n");
    exit(0);
}

void ERROR_CLOSE(int sockfd){
    printf("Error occured Closing Socket\n");
    close(sockfd);
    exit(0);
}

int main(){
    int sockfd=socket(AF_INET,SOCK_STREAM,0);
    if(sockfd<0) ERROR();
    else printf("Socket Created.\n");

    SA_IN client;
    init_SA(&client,inet_addr("127.0.0.1"),AF_INET,htons(PORT));
    int connect_status=connect(sockfd,(SA *)&client,sizeof(client));
    if(connect_status<0) ERROR_CLOSE(sockfd);
    char buffer[BUFF_SIZE]; 
    printf("enter te file name");
    scanf("%s",buffer);

    int send_status=send(sockfd,buffer,sizeof(buffer),0);
    if(send_status<0)ERROR_CLOSE(sockfd);
    int recv11;
    int recv_status=recv(sockfd,&recv11,sizeof(int),0);

    if(recv11==1){
        printf("This file is valid\n");
        printf("1)Write to file\n2)Read File\n");
        int opt;
        scanf("%d",&opt);
        switch (opt)
        {
            case 1:;
                /* code */
                send_status=send(sockfd,&opt,sizeof(int),0);
                if (send_status<0) ERROR_CLOSE(sockfd);

                char data[BUFF_SIZE];
                scanf("%s",data);
                send_status=send(sockfd,data,sizeof(data),0);
                if (send_status<0) ERROR_CLOSE(sockfd);

                printf("write completed\n");
                
                break;
            case 2: ;
                send_status=send(sockfd,&opt,sizeof(int),0);
                if (send_status<0) ERROR_CLOSE(sockfd);
                char datatobeprinted[100];
                recv_status=recv(sockfd,datatobeprinted,sizeof(datatobeprinted),0);
                if(recv_status<0) ERROR_CLOSE(sockfd);

                printf("%s",datatobeprinted);

            default:
                break;
        }
    }

    else{
        printf("Not Vlaid");
    }
    // int send11=1;
    // int send_status=send(sockfd,&send11,sizeof(send11),0);
    // if(send_status<0) ERROR_CLOSE(sockfd);
    // else printf("Message Sent\n");
    // int recv11;
    // int recv_status=recv(sockfd,&recv11,sizeof(int),0);
    // if(recv_status<0) ERROR_CLOSE(sockfd);
    // else printf("%d \n",recv11);

    close(sockfd);
    return 0 ;
    
}