#include <string.h>
#include <unistd.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <netinet/in.h>
#include <stdlib.h>
#include <stdio.h>
#include <time.h> 


#define PORT 8585
#define BUFF_SIZE 100

typedef struct sockaddr SA;
typedef struct sockaddr_in SA_IN;
typedef socklen_t LEN;

int binarySearch(int arr[], int l, int r, int x) 
{ 
    if (r >= l) { 
        int mid = l + (r - l) / 2; 
  
        // If the element is present at the middle 
        // itself 
        if (arr[mid] == x) 
            return mid; 
  
        // If element is smaller than mid, then 
        // it can only be present in left subarray 
        if (arr[mid] > x) 
            return binarySearch(arr, l, mid - 1, x); 
  
        // Else the element can only be present 
        // in right subarray 
        return binarySearch(arr, mid + 1, r, x); 
    } 
  
    // We reach here when element is not 
    // present in array 
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

	//creating a socket
	int sockfd = socket(AF_INET, SOCK_STREAM, 0);
	if(sockfd < 0) ERROR();
	else printf("Socket created.\n");
	//What is going on here?
	//sa stands for sockaddr
	//sa_in sockadddress_in
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
	//change the code here

	char str1[100]="enter the number";
	int arr[100];
	int num;

		int recv_status = recv(clientfd, &num, sizeof(num), 0);
		if(recv_status < 0) ERROR_CLOSE(sockfd);
		else printf("Recieved: %d\n", num);



		int i=0;
		int lol;
		for(i=0;i<num;i++){
			int recv_status = recv(clientfd, &lol, sizeof(lol), 0);
			if(recv_status < 0) ERROR_CLOSE(sockfd);
			else printf("Recieved: %d\n", lol);
			arr[i]=lol;	    	
		}

		recv_status=recv(clientfd,&lol,sizeof(lol),0);
		if(recv_status<0) ERROR_CLOSE(sockfd);
		else printf("Received: %d\n",lol);


		int n = num; 
		int x = lol;
    	int result = binarySearch(arr, 0, n - 1, x);


    	(result == -1) ? printf("Element is not present in array"): printf("Element is present at index %d",result); 

		int send_status=send(clientfd,&result,sizeof(result),0);
		if(send_status<0) ERROR_CLOSE(sockfd);


		close(sockfd);

		return 0;
}

