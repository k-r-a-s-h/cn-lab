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

void swap(int *xp, int *yp) 
{ 
	int temp = *xp; 
	*xp = *yp; 
	*yp = temp; 
} 
int partition (int arr[], int low, int high)
{
    int pivot = arr[high];    
    int i = (low - 1);  
  	int j;
    for ( j = low; j <= high- 1; j++)
    {
        
        if (arr[j] <= pivot)
        {
            i++;    
            swap(&arr[i], &arr[j]);
        }
    }
    swap(&arr[i + 1], &arr[high]);
    return (i + 1);
}
  

void quickSort(int arr[], int low, int high)
{
    if (low < high)
    {
    
        int pi = partition(arr, low, high);
  
        
        quickSort(arr, low, pi - 1);
        quickSort(arr, pi + 1, high);
    }
} 



void printArray(int arr[], int size) 
{ 
	int i; 
	for (i=0; i < size; i++) 
		printf("%d ", arr[i]); 
	printf("\n"); 
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

    int arr[100];
    int i,size,num;
    int recv_status=recv(clientfd,&size,sizeof(size),0);
    if(recv_status<0) ERROR_CLOSE(sockfd);
    else printf("Size: %d\n",size);

    for(i=0;i<size;i++){
        recv_status=recv(clientfd,&num,sizeof(num),0);
        if(recv_status<0) ERROR_CLOSE(sockfd);
        else {
            printf("Number at %d %d\n",i,num);
            arr[i]=num;
        }
    }
    quickSort(arr,0,size-1);
    printArray(arr,size);


    int send_status=send(clientfd,arr,sizeof(arr),0);
    if(send_status<0) ERROR_CLOSE(sockfd);
    



	close(sockfd);
	return 0;
}