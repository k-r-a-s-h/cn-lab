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
	int len;
    //change here

      printf("\n1)RegNO\n2)NameOfStudent\n3)SubjectCode");
        int input;
        scanf("%d",&input);
        buffer[0]=input+'0';
        switch (input)
        {
            case 1:
                printf("\nEnter the registration number(2 digit)\n");
                int r_number;
                scanf("%d",&r_number);
                int dig2= r_number%10;
                r_number/=10;
                int dig1=r_number;
                char dig11=dig1+'0';
                char dig22=dig2+'0';
                buffer[1]=dig11;
                buffer[2]=dig22;
                break;
            case 2:
                printf("\nEnter the name of the student\n");
                char name[BUFF_SIZE];
                scanf("%s",name);
                strcat(buffer,name);
                break;
            case 3:
                printf("\nEnter the subject code(2 digit)\n");
                int sub;
                scanf("%d",&sub);
                int dig_2=sub%10;
                sub/=10;
                int dig_1=sub;
                char dig111=dig_1+'0';
                char dig222=dig_2+'0';
                buffer[1]=dig111;
                buffer[2]=dig222;
                break;
            default:
                break;
        }
	int send_status=sendto(sockfd,(const char*)buffer,strlen(buffer),0,(const SA*)&client,sizeof(client));
	if(send_status<0) ERROR_CLOSE(sockfd);

	char buffer_send[BUFF_SIZE];
	int recv_status =recvfrom(sockfd,(char*)buffer_send,sizeof(buffer_send),0,(SA*)&client,&len);
	if(recv_status<0) ERROR_CLOSE(sockfd);
	else {
		buffer_send[recv_status]='\0';
		printf("Server : %s \n",buffer_send);
	}
    //till here

	close(sockfd);
	return 0 ;
    
}