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
    init_SA(&clientaddr,AF_INET,htons(PORT+1),htonl(INADDR_ANY));


    int bind_status = bind(sockfd,(const SA*)&clientaddr,sizeof(clientaddr));
    if(bind_status<0) ERROR_CLOSE(sockfd);
    else
    {
        printf("bind completed\n");
    }
    

    int len=sizeof(clientaddr);

    //change here
    int recv_status=recvfrom(sockfd,buffer,sizeof(buffer),0,(SA*)&serveraddr,&len);
    if(recv_status<0){
        printf("%d",recv_status);
        ERROR_CLOSE(sockfd);

    } 
    else {
        buffer[recv_status]='\0';
    }

    printf("Client: %s \n",buffer);

    char dataToBeWritten[BUFF_SIZE]  ; 
	FILE *filePointer=fopen(buffer,"r");
	if ( filePointer == NULL )
    {	
    	int send34 =0;
        printf( "file failed to open." ) ;
        int send_status = sendto(sockfd,&send34,sizeof(int),0,(SA*)&serveraddr,len);
    	if(send_status<0) ERROR_CLOSE(sockfd); 
    }
    else{
        int what;
        int send12=1;
        int send_status=sendto(sockfd,&send12,sizeof(int),0,(SA*)&serveraddr,len);
        if(send_status<0) ERROR_CLOSE(sockfd);
        fclose(filePointer);
        int flag=1;

        while(flag==1){
            recv_status=recvfrom(sockfd,&what,sizeof(what),0,(SA*)&serveraddr,&len);
            if(recv_status<0) ERROR_CLOSE(sockfd);

            switch (what)
            {
                case 1:
                        ;
                        //write code
                        char dataToBeWritten12[BUFF_SIZE];
                        FILE *filePointer1=fopen(buffer,"w");
                        recv_status=recvfrom(sockfd,dataToBeWritten12,sizeof(dataToBeWritten12),0,(SA*)&serveraddr,&len);
                        if(recv_status<0) ERROR_CLOSE(sockfd);
                        else printf("Received: %s\n",dataToBeWritten12);

                        fputs(dataToBeWritten12,filePointer1);
                        fputs("\n",filePointer1);
                        memset(dataToBeWritten12,0,sizeof dataToBeWritten12);
                        fclose(filePointer1);
                    break;
                case 2://read code
                        ;
                        FILE *filePointer2=fopen(buffer,"r");
						char buffer_send[100];
						int index=0;
						char file_buff[100];
						char ch;
						while((ch = fgetc(filePointer2)) != EOF){
							/* code */
							printf("%c",ch);
							
							if((ch >='a' && ch <='z') || (ch>='A' && ch<='Z') ){
								buffer_send[index] = (char) ch;
								index++;
							}
							
						}
						
						buffer_send[index]='\0';
						printf("%s",buffer_send);
                        int snd_status=sendto(sockfd,buffer_send,sizeof(buffer_send),0,(SA*)&serveraddr,len);
                        if(snd_status<0) ERROR_CLOSE(sockfd);
                        fclose(filePointer2);
                        break;
                case 3://update code
                        ;
                        FILE *filePointer3 =fopen(buffer,"a");
						char dataToBeWritten13[BUFF_SIZE] ;
                        recv_status =recvfrom(sockfd,dataToBeWritten13,sizeof(dataToBeWritten13),0,(SA*)&serveraddr,&len);
                        if(recv_status<0)ERROR_CLOSE(sockfd);
                        else printf("Received: %s\n",dataToBeWritten13);
                        fputs(dataToBeWritten13,filePointer3);
                        fputs("\n",filePointer3);
                        memset(dataToBeWritten12,0,sizeof dataToBeWritten13);
                        fclose(filePointer3);
                        break;
                case 4 :
                        ;
                        flag=0;
                        break;
            
                default:
                    break;
            }
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