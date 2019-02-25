#include <string.h>
#include <strings.h>
#include <unistd.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <netinet/in.h>
#include <stdlib.h>
#include <stdio.h>



#define PORT1 1315//recv
// #define PORT2 1313//send
#define BUFF_SIZE 100


typedef struct sockaddr SA;
typedef struct sockaddr_in SA_IN;
typedef socklen_t LEN;

struct student
{
    int r_number;
    char name[BUFF_SIZE];
    int s_code[5];
    int marks[5];
    char dept[3];
    char section;
    
};


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
	char buffer1[BUFF_SIZE];
    char send_buffer[BUFF_SIZE];

    struct student s1;
    s1.r_number=12;
    s1.name[0]='k';
    s1.name[1]='r';
    s1.name[2]='i';
    s1.name[3]='s';
    s1.name[4]='h';
    s1.name[5]='n';
    s1.name[6]='a';
    s1.name[7]='\0';
    
    s1.marks[0]=99;
    s1.marks[1]=95;
    s1.marks[2]=88;
    s1.marks[3]=78;
    s1.marks[4]=90;
    
    s1.dept[0]='I';
    s1.dept[1]='T';
    s1.dept[3]='\0';

    s1.s_code[0]=10;
    s1.s_code[1]=11;
    s1.s_code[2]=12;
    s1.s_code[3]=13;
    s1.s_code[4]=14;

    s1.section='B';


	//recv server
    int sockfd1 = socket(AF_INET, SOCK_STREAM, 0);
    if(sockfd1< 0) ERROR();
    else printf("Socket1 created.\n");

    SA_IN server1;
    init_SA(&server1, AF_INET, htons(PORT1), htonl(INADDR_ANY));

    int bind_status1 = bind(sockfd1, (const SA*)&server1, sizeof(server1));
    if(bind_status1 < 0) ERROR();
    else printf("Socket1 bound.\n");

    int listen_status1= listen(sockfd1, 1);
    if(listen_status1 < 0) ERROR_CLOSE(sockfd1);
    else printf("Socket1 listening.\n");

    SA_IN client1;
    int client_len = sizeof(client1);

    int clientfd1 = accept(sockfd1, (SA*)&client1, &client_len);
    if(clientfd1 < 0) ERROR_CLOSE(sockfd1);
    else printf("Client1 connected.\n");

    int recv_status = recv(clientfd1, buffer1, sizeof(buffer1), 0);
	if(recv_status < 0) ERROR_CLOSE(sockfd1);\
	else printf("Recieved: %s\n", buffer1);

    char f_dig=buffer1[0];
    int opt=f_dig-'0';

    int p =fork();
    if(p==0){
        //child process 1
        if(opt==1){
            int dig_1=buffer1[1]-'0';
            int dig_2=buffer1[2]-'0';
            int val=dig_1*10+dig_2;

            if(s1.r_number==val){
                strcat(send_buffer,s1.name);
                int send_status=send(clientfd1,send_buffer,sizeof(send_buffer),0);
		        if(send_status<0) ERROR_CLOSE(sockfd1);
                
            }else
            {
                char lol[]="Does not exsist";
                strcat(send_buffer,lol);
                int send_status=send(clientfd1,send_buffer,sizeof(send_buffer),0);
		        if(send_status<0) ERROR_CLOSE(sockfd1);
                int pid=getpid();
                    send_status=send(clientfd1,&pid,sizeof(int),0);
                    if(send_status<0)ERROR_CLOSE(sockfd1);
            }
            close(sockfd1);
            exit(0);
            
        }
        else
        {
            /* code */
            exit(0);
        }
        
        
    }
    else{
        //parent process 2
        int pid= fork();
        if(pid==0){
            // child process 3
            if(opt==2){
                int index =1;
                char name[BUFF_SIZE];
                while(buffer1[index]!='\0'){
                    name[index-1]=buffer1[index];
                    index++;
                }
                name[index]='\0';
                printf("%s",name);
                printf("%s",s1.name);
                if(!strcmp(name,s1.name)){
                    char str[2];
                    str[0]=s1.section;
                    str[1]='\0';
                    strcat(send_buffer,str);
                    int send_status=send(clientfd1,send_buffer,sizeof(send_buffer),0);
		            if(send_status<0) ERROR_CLOSE(sockfd1);

                    int pid=getpid();
                    send_status=send(clientfd1,&pid,sizeof(int),0);
                    if(send_status<0)ERROR_CLOSE(sockfd1);
                    close(sockfd1);

                }
                else{
                    
                    char lol[]="Does not exsist";
                strcat(send_buffer,lol);
                int send_status=send(clientfd1,send_buffer,sizeof(send_buffer),0);
		        if(send_status<0) ERROR_CLOSE(sockfd1);
                int pid=getpid();
                    send_status=send(clientfd1,&pid,sizeof(int),0);
                    if(send_status<0)ERROR_CLOSE(sockfd1);
                }
                

            }
            else{
                exit(0);
            }
            
        }
        else{
            //parent process  2
            if(opt==3){
                printf("This was write");
                int dig_1=buffer1[1]-'0';
                int dig_2=buffer1[2]-'0';
                int val=dig_1*10+dig_2;

                for(int i=0;i<5;i++){
                    if(s1.s_code[i]==val){
                        int marks=s1.marks[i];
                        int dig__2=marks%10;
                        marks/=10;
                        int dig__1=marks;
                        buffer1[0]=dig__1+'0';
                        buffer1[1]=dig__2+'0';
                        buffer1[2]='\0';
                        printf("%s",buffer1);
                        int send_status=send(clientfd1,buffer1,sizeof(buffer1),0);
		                if(send_status<0) ERROR_CLOSE(sockfd1);

                        int pid=getpid();
                        send_status=send(clientfd1,&pid,sizeof(int),0);
                        if(send_status<0)ERROR_CLOSE(sockfd1); 
                        break;
                    }
                    else
                    {
                        char lol[]="Does not exsist";
                        strcat(send_buffer,lol);
                        int send_status=send(clientfd1,send_buffer,sizeof(send_buffer),0);
                        if(send_status<0) ERROR_CLOSE(sockfd1);
                        int pid=getpid();
                        send_status=send(clientfd1,&pid,sizeof(int),0);
                        if(send_status<0)ERROR_CLOSE(sockfd1);
                    }
                    
                }
                close(sockfd1);
                exit(0);
            }
            else{

                exit(0);

            }
            

        }
        
    }


    close(sockfd1);
    return 0;

}