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

    char buffer[BUFF_SIZE];
    char buffer_send[BUFF_SIZE];
    int sockfd = socket(AF_INET,SOCK_DGRAM,0);
    if(sockfd<0) ERROR();
    else printf("Socket Created\n");

    SA_IN clientaddr,serveraddr;
    init_SA(&serveraddr,AF_INET,htons(PORT),htonl(INADDR_ANY));
    init_SA(&clientaddr,AF_INET,htons(PORT+1),htonl(INADDR_ANY));

    int bind_status = bind(sockfd,(const SA*)&clientaddr,sizeof(clientaddr));
    if(bind_status<0) ERROR_CLOSE(sockfd);
    else
    {
        printf("bind completed\n");
    }
    int len=sizeof(clientaddr);
    //change here
    int recv_status=recvfrom(sockfd,buffer,sizeof(buffer),0,(SA*)&serveraddr,&len);
    if(recv_status<0){
        printf("%d",recv_status);
        ERROR_CLOSE(sockfd);
    } 
    else {
        buffer[recv_status]='\0';
        printf("Client: %s \n",buffer);
    }
    
    char f_dig=buffer[0];
    int opt = f_dig-'0';

    int p = fork();
    if(p==0){
        if(opt==1){
            int dig_1=buffer[1]-'0';
            int dig_2=buffer[2]-'0';
            int val= dig_1*10 + dig_2;
            if(s1.r_number==val){
                strcat(buffer_send,s1.name);
                int send_status=sendto(sockfd,(const char*)buffer_send,strlen(buffer_send),0,(const SA*)&serveraddr,len);
                if(send_status<0) ERROR_CLOSE(sockfd);
            }
            else{
                char lol[]="Does not exsist";
                strcat(buffer_send,lol);
                int send_status=sendto(sockfd,(const char*)buffer_send,strlen(buffer_send),0,(const SA*)&serveraddr,len);
                if(send_status<0) ERROR_CLOSE(sockfd);
            }
             close(sockfd);
            exit(0);
        }
        else{
            exit(0);
        }
       
    }
    else{
        int pid=fork();
        if(pid==0){
            if(opt==2){
                int index=1;
                char name[BUFF_SIZE];
                while(buffer[index]!='\0'){
                    name[index-1]=buffer[index];
                    index++;
                }
                name[index]='\0';
               // printf("%s",name);
                //printf("%s",s1.name);

                if(!strcmp(name,s1.name)){
                    char str[2];
                    str[0]=s1.section;
                    str[1]='\0';
                    strcat(buffer_send,str);
                    int send_status=sendto(sockfd,(const char*)buffer_send,strlen(buffer_send),0,(const SA*)&serveraddr,len);
                    if(send_status<0) ERROR_CLOSE(sockfd);
                }
                else{
                    char lol[]="Does not exsist";
                    strcat(buffer_send,lol);
                    int send_status=sendto(sockfd,(const char*)buffer_send,strlen(buffer_send),0,(const SA*)&serveraddr,len);
                    if(send_status<0) ERROR_CLOSE(sockfd);

                }
                
            }
        
            else{
                exit(0);
        
            }
        }
    
        else{
            if(opt==3){
                int dig_1=buffer[1]-'0';
                int dig_2=buffer[2]-'0';
                int val=dig_1*10+dig_2;
                printf("%d",val);
                for(int i=0;i<5;i++){
                    if(s1.s_code[i]==val){
                        int marks=s1.marks[i];
                        int dig__2=marks%10;
                        marks/=10;
                        int dig__1=marks;
                        buffer_send[0]=dig__1+'0';
                        buffer_send[1]=dig__2+'0';
                        buffer_send[2]='\0';
                        int send_status=sendto(sockfd,(const char*)buffer_send,strlen(buffer_send),0,(const SA*)&serveraddr,len);
                        if(send_status<0) ERROR_CLOSE(sockfd);
                        close(sockfd);
                        exit(0);
                    }
                    
                }
                char lol[]="Does Not exsist";
                strcat(buffer_send,lol);
                int send_status=sendto(sockfd,(const char*)buffer_send,strlen(buffer_send),0,(const SA*)&serveraddr,len);
                if(send_status<0) ERROR_CLOSE(sockfd);
                close(sockfd);
                exit(0);
            }
            else{
                exit(0);
            }
        }
    }   



    

    //in between this
    close(sockfd);
    return 0;
}