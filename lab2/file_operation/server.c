#include <string.h>
#include <strings.h>
#include <unistd.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <netinet/in.h>
#include <stdlib.h>
#include <stdio.h>

#define PORT 1311
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

int main() {
	char buffer[BUFF_SIZE];

	int sockfd = socket(AF_INET, SOCK_STREAM, 0);
	if(sockfd < 0) ERROR();
	else printf("Socket created.\n");

	SA_IN server;
	init_SA(&server, AF_INET, htons(PORT), htonl(INADDR_ANY));

	int bind_status = bind(sockfd, (const SA*)&server, sizeof(server));
	if(bind_status < 0) ERROR();
	else printf("Socket bound.\n");

	int listen_status = listen(sockfd, 1);
	if(listen_status < 0) ERROR_CLOSE(sockfd);
	else printf("Socket listening.\n");

	SA_IN client;
	int client_len = sizeof(client);

	int clientfd = accept(sockfd, (SA*)&client, &client_len);
	if(clientfd < 0) ERROR_CLOSE(sockfd);
	else printf("Client connected.\n");


	//change here

	int recv_status = recv(clientfd, buffer, sizeof(buffer), 0);
	if(recv_status < 0) ERROR_CLOSE(sockfd);\
	else printf("Recieved: %s\n", buffer);

	//enter the checking if file exisist code

	char dataToBeWritten[BUFF_SIZE]  ; 
	FILE *filePointer=fopen(buffer,"w");
	if ( filePointer == NULL )
    {	
    	int send34 =0;
        printf( "file failed to open." ) ;
        int send_status = send(clientfd,&send34,sizeof(int),0);
    	if(send_status<0) ERROR_CLOSE(sockfd); 

    }
	//open the file

    else{
    	int what;
    	int send12 =1;
    	int send_status = send(clientfd,&send12,sizeof(int),0);
    	if(send_status<0) ERROR_CLOSE(sockfd); 
    	fclose(filePointer);



    	while (1){
    		recv_status = recv(clientfd, &what, sizeof(what), 0);
			if(recv_status <= 0) ERROR_CLOSE(sockfd);

	    	switch(what){
	    		case 1 ://write code 
	    				;
	    				char dataToBeWritten12[BUFF_SIZE]  ; 
						FILE *filePointer1=fopen(buffer,"w");
	    				recv_status = recv(clientfd, dataToBeWritten12, sizeof(dataToBeWritten12), 0);
						if(recv_status < 0) ERROR_CLOSE(sockfd);\
						else printf("Recieved: %s\n", dataToBeWritten12);
						// writing in the file using fputs()
	            		fputs(dataToBeWritten12, filePointer1) ;   
	            		fputs("\n", filePointer1) ;
	            		fclose(filePointer1);

	            		break;
	           	case 2: //read code
	           			;
	           			
						FILE *filePointer2=fopen(buffer,"r");
						char buffer_send[BUFF_SIZE];
						char file_buff[100];
						while(fgets(file_buff,255,(FILE*)filePointer2)){
							strcat(buffer_send,file_buff);
						}
						int snd_status =send(clientfd,buffer_send,sizeof(buffer_send),0);
						if(snd_status<0)ERROR_CLOSE(sockfd);

						fclose(filePointer2);
	           			break;
	           	case 3://update code

	           			break;
	    		
	    	}
    }

    	
}
	close(sockfd);
	return 0;
}

