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
	else printf("socket created");

	SA_IN server,client;
	init_SA(&server,AF_INET,htons(PORT),inet_addr("127.0.0.1"));
    init_SA(&client,AF_INET,htons(PORT+1),inet_addr("127.0.0.1"));
	
	int bind_status = bind(sockfd,(const SA*)&server,sizeof(server));
    if(bind_status<0) ERROR_CLOSE(sockfd);
    else
    {
        printf("bind completed\n");
    }
    //change here

	int len;
    printf("Enter the file to open:\n");
	scanf("%s", buffer);
    int send_status=sendto(sockfd,buffer,sizeof(buffer),0,(const SA*)&client,sizeof(client));
    if(send_status<0) ERROR_CLOSE(sockfd);

    int flag,tap;
    tap=1;
    int recv_status=recvfrom(sockfd,&flag,sizeof(flag),0,(SA*)&client,&len);
    if(recv_status<0) ERROR_CLOSE(sockfd);

    if(flag==1){
        while(tap==1){
            int lol;
            printf("\n1)Write File\n2)Read File\n3)Update\n4)Exit");
			scanf("%d",&lol);

            send_status=sendto(sockfd,&lol,sizeof(lol),0,(const SA*)&client,sizeof(client));
            if(send_status<0)ERROR_CLOSE(sockfd);

            switch (lol)
            {
                case 1:
                        ;
                        char buf1[BUFF_SIZE];
                        int index =0 ;
                        printf("enter the content to be writeen \n");
                        scanf("%s",buf1);

                        send_status=sendto(sockfd,buf1,sizeof(buf1),0,(const SA*)&client,sizeof(client));
                        if(send_status<0) ERROR_CLOSE(sockfd);
                    break;
                case 2:
                        ;
                        char buf2[BUFF_SIZE];
                        recv_status=recvfrom(sockfd,buf2,sizeof(buf2),0,(SA*)&client,&len);
                        if(recv_status<0) ERROR_CLOSE(sockfd);
                        printf("%s",buf2);
                        break;
                case 3:
                        ;
						char buf3[BUFF_SIZE];
						printf("enter the content to be written");
						scanf("%s",buf3);
                        send_status=sendto(sockfd,buf3,sizeof(buf3),0,(const SA*)&client,sizeof(client));
                        if(send_status<0) ERROR_CLOSE(sockfd);
                        break;
                case 4: 
                        ;
                        tap=0;
                        break;
                default:
                    break;
            }
        }
        
    }
    else
    {
        printf("file doesn't exsist");
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