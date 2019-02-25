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
	char buffer[BUFF_SIZE];
    char recv_buffer[BUFF_SIZE];
	

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

        int send_status = send(sockfd1, buffer, sizeof(buffer), 0);
	    if(send_status < 0) ERROR_CLOSE(sockfd1);

        int recv_status = recv(sockfd1, recv_buffer, sizeof(recv_buffer), 0);
			if(recv_status < 0) ERROR_CLOSE(sockfd1);
			else {
				printf("server : %s  \n",recv_buffer);
			}


        int piid;
        recv_status=recv(sockfd1,&piid,sizeof(piid),0);
        if(recv_status<0)ERROR_CLOSE(sockfd1);
        else
        {
            printf("PPid: %d\n",piid);
        }
        


        close(sockfd1);
        return 0 ;

}