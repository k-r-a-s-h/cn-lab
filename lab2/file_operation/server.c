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

	int recv_status = recv(clientfd, buffer, sizeof(buffer), 0);//file name stored in buffer
	if(recv_status < 0) ERROR_CLOSE(sockfd);\
	else printf("Recieved: %s\n", buffer);

	//enter the checking if file exisist code

	char dataToBeWritten[BUFF_SIZE]  ; 
	FILE *filePointer=fopen(buffer,"r");
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

		int flag=1;

    	while (flag==1){
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
						memset(dataToBeWritten12 , 0, sizeof dataToBeWritten12);
	            		fclose(filePointer1);

	            		break;
	           	case 2: //read code
	           			;
	           			
						FILE *filePointer2=fopen(buffer,"r");
						char buffer_send[100];
						int index=0;
						char file_buff[100];

						//read code here 
						// while(fgets(file_buff,100,(FILE*)filePointer2)){ //tis is wrong
						// 	strcat(buffer_send,file_buff);
						// }
						char ch;
						while((ch = fgetc(filePointer2)) != EOF){
							/* code */
							printf("%c",ch);
							buffer_send[index] = (char) ch;
							index++;
						}
						
						buffer_send[index]='\0';

						printf("%s",buffer_send);
						int snd_status =send(clientfd,buffer_send,sizeof(buffer_send),0);
						if(snd_status<0)ERROR_CLOSE(sockfd);
						
						fclose(filePointer2);
									
	           			break;
	           	case 3://update code
				   	;
						FILE *filePointer3 =fopen(buffer,"a");
						char dataToBeWritten13[BUFF_SIZE]  ;
						recv_status = recv(clientfd, dataToBeWritten13, sizeof(dataToBeWritten13), 0);
						if(recv_status < 0) ERROR_CLOSE(sockfd);\
						else printf("Recieved: %s\n", dataToBeWritten13);
						fputs(dataToBeWritten13, filePointer3) ;   
	            		fputs("\n", filePointer3) ;
						memset(dataToBeWritten12 , 0, sizeof dataToBeWritten13);
	            		fclose(filePointer3);


	           			break;
				case 4: 
						;

						flag=0;
	    		
	    	}
    }

    	
}
	close(sockfd);
	return 0;
}

