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

    SA_IN server;
    init_SA(&server,htonl(INADDR_ANY),AF_INET,htons(PORT));

    int bind_status=bind(sockfd,(const SA*)&server,sizeof(server));
    if(bind_status<0) ERROR_CLOSE(sockfd);
    else printf("Bind Completed\n");

    int listen_status=listen(sockfd,1);
    if(listen_status<0) ERROR_CLOSE(sockfd);
    else printf("listening...");

    SA_IN client;
    int length=sizeof(client);
    int clientfd=accept(sockfd,(SA *)&client,&length);
    if(clientfd<0) ERROR_CLOSE(sockfd);
    else printf("Client Connected");

    char buffer[BUFF_SIZE];

    int recv_status=recv(clientfd,buffer,sizeof(buffer),0);
    if(recv_status<0) ERROR_CLOSE(sockfd);
    else{
        FILE *fp=fopen(buffer,"r");
        if(fp==NULL){
            int send11 =0;
            int send_status=send(clientfd,&send11,sizeof(int),0);
            if(send_status<0) ERROR_CLOSE(sockfd);

        }
        else{
            printf("This executed\n");
            int send11 =1;
            int send_status=send(clientfd,&send11,sizeof(int),0);
            if(send_status<0) ERROR_CLOSE(sockfd);
            fclose(fp);
        }
        
    }

    // memset(buffer,0,sizeof(buffer));
    int recv_option;
    recv_status=recv(clientfd,&recv_option,sizeof(int),0);
    if(recv_status<0) ERROR_CLOSE(sockfd);
    
    switch (recv_option)
    {
        case 1: ;
            /* code */
            char datatobewritten[BUFF_SIZE];        
            recv_status=recv(clientfd,datatobewritten,sizeof(datatobewritten),0);
            if(recv_status<0) ERROR_CLOSE(sockfd);

            FILE * fp1=fopen(buffer,"w");
            fputs(datatobewritten,fp1);
            fputs("\n",fp1);
            fclose(fp1);
        
            break;
        case 2: ;
            
            char datatobesent[BUFF_SIZE];

            FILE * fp2=fopen(buffer,"r");
            int index=0;
            char ch;
            while((ch=fgetc(fp2))!=EOF){

                datatobesent[index]=(char)ch;
                index++;
            }
            datatobesent[index]='\0';

            fclose(fp2);
            
            int send_status=send(clientfd,datatobesent,sizeof(datatobesent),0);
            if(send_status<0) ERROR_CLOSE(sockfd);

    
        default:
            break;
    }
    // int recv11=0;
    // int recv_status=recv(clientfd,&recv11,sizeof(int),0);
    // if(recv_status<0) ERROR_CLOSE(sockfd);
    // else printf("%d",recv11);

    // int send11=12345;
    // int send_status=send(clientfd,&send11,sizeof(int),0);
    // if(send_status<0) ERROR_CLOSE(sockfd);
    // else printf("Mss sent");

    close(sockfd);

    
}