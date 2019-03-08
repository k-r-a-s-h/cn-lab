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
char *strrev(char *str)
{
      char *p1, *p2;

      if (!  str || ! *str)
            return str;
      for (p1 = str, p2 = str + strlen(str) - 1; p2 > p1; ++p1, --p2)
      {
            *p1 ^= *p2;
            *p2 ^= *p1;
            *p1 ^= *p2;
      }
      return str;
}


int palin(char * a ){
	  char  b[100];
	  strcpy(b, a);  
	  strrev(b);  
	 
	  if (strcmp(a, b) == 0)  {
		return 1;
	}
	  else{
	 	return 0;
	 }
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
    
    while(1){


	int recv_status = recvfrom(sockfd,buffer, sizeof(buffer), 0,(SA*)&clientaddr,&len);

	char str1[100]="palindrome";
	char str2[100]="not palindrome";

	if(recv_status < 0) ERROR_CLOSE(sockfd);
	else {
		printf("Recieved: %s\n", buffer);
		int k=palin(buffer);
		if(k==1){
			//send ++
					int send_status = sendto(sockfd, (const char*)str1, sizeof(str1), 0,(const SA*)&clientaddr,len);
						if(send_status < 0) ERROR_CLOSE(sockfd);


		}
		else{
			//send --
					int send_status = sendto(sockfd, (const char*)str2, sizeof(str2), 0,(const SA*)&clientaddr,len);
						if(send_status < 0) ERROR_CLOSE(sockfd);


		}
	}
}



    close(sockfd);
    return 0;
}