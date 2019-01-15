#include <string.h>
#include <unistd.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <netinet/in.h>
#include <stdlib.h>
#include <stdio.h>
#include <time.h> 


#define PORT 1311
#define BUFF_SIZE 100

typedef struct sockaddr SA;
typedef struct sockaddr_in SA_IN;
typedef socklen_t LEN;

void delay(int number_of_seconds)
{
    // Converting time into milli_seconds
    int milli_seconds = 1000 * number_of_seconds;
  
    // Stroing start time
    clock_t start_time = clock();
  
    // looping till required time is not acheived
    while (clock() < start_time + milli_seconds)
        ;
} 

int binarySearch(int arr[], int l, int r, int x)
{
    while (l <= r) {
        int m = l + (r - l) / 2;
  
        // Check if x is present at mid
        if (arr[m] == x)
            return m;
  
        // If x greater, ignore left half
        if (arr[m] < x)
            l = m + 1;
  
        // If x is smaller, ignore right half
        else
            r = m - 1;
    }
  
    // if we reach here, then element was
    // not present
    return -1;
} 

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
	char buffer1[BUFF_SIZE];

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

	char str1[100]="enter the number";
	int arr[100];

	int recv_status = recv(clientfd, buffer, sizeof(buffer), 0);
		if(recv_status < 0) ERROR_CLOSE(sockfd);\
		else printf("Recieved: %s\n", buffer);

		int a=buffer[0]-'0';
		int i=0;
		for(i=0;i<a;i++){
			int send_status = send(clientfd, str1, sizeof(str1), 0);
			if(send_status < 0) ERROR_CLOSE(sockfd);

			delay(10); 
			
			int recv_status = recv(clientfd, buffer, sizeof(buffer), 0);
			if(recv_status < 0) ERROR_CLOSE(sockfd);\
			else printf("Recieved: %s\n", buffer);
			arr[i]=buffer[0]-'0';

		}


		int n = sizeof(arr) / sizeof(arr[0]); 
		int x = 12;
    	int result = binarySearch(arr, 0, n - 1, x);
    	(result == -1) ? printf("Element is not present"
                            " in array")
                   : printf("Element is present at "
                            "index %d",
                            result); 

	close(sockfd);
	return 0;
}

