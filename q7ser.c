#include <stdio.h>
#include <stdlib.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <unistd.h>
#include <string.h>
#include <arpa/inet.h>
#include <pthread.h>
#include <netinet/in.h>


struct client{
    int index;
    int sockID;
    struct sockaddr_in cliaddr;
    int len;
};

int cCtr = 0; //client counter

struct client Client[1024];
pthread_t thread[1024];

void* texting(void* ClDetail){

    struct client* cDetail=(struct client*) ClDetail;
    int index=cDetail->index;
    int cSocket=cDetail->sockID;

    printf("\nClient %d connected.\n",index+1);
    int f=0;
    while(1){

	char data[1024];
	int read = recv(cSocket,data,1024,0);
	data[read] = '\0';
    int len=0;

	char *output="Start communicating!!\n";

	if(strcmp(data,"START") == 0){
                f++;
		send(cSocket,output,strlen(output)*sizeof(char),0);
	}else{
	    char *output="Invalid!!\n";
	    send(cSocket,output,strlen(output)*sizeof(char),0);
	}
	    
	while(f==1) //if start
	{
		recv(cSocket,data,1024,0);
		data[read] = '\0';
		len+=strlen(data);
		if(len>25){
		      char* output="STOP";
		      send(cSocket,output,strlen(output)*sizeof(char),0);
		      printf("\nClient%d exceeded their daily limit \n",index+1);
		      close(cSocket);
		      return NULL;
		}
                printf("Client%d: %s\n",index+1,data);
                if(strcmp(data,"STOP")==0){
                     send(cSocket,data,1024,0);
                     printf("\nClient%d stopped communicating..\n",index+1);
                     close(cSocket);
                     return NULL;
                }
		send(cSocket,data,1024,0);			
	}
    }
    return NULL;
}

void main(){

     int sSocket=socket(AF_INET,SOCK_STREAM,0);
     if(sSocket<0)
	 {
        perror("Socket creation failed\n");
        exit(0);
     }else
        printf("Socket  created\n");
        
     struct sockaddr_in servaddr;
     
     servaddr.sin_family=AF_INET;
     servaddr.sin_port=htons(8080);
     servaddr.sin_addr.s_addr=INADDR_ANY;


     if(bind(sSocket,(struct sockaddr *)&servaddr,sizeof(servaddr))==-1)
	 {
         perror("Bind failed..\n");
         exit(0);
     }else
         printf("Bind successfull\n");

     if(listen(sSocket,1024)==-1)
	 {
         perror("Listen failed\n");
         exit(0);
     }else
         printf("Server started listenting ...\n");

     while(1){

	Client[cCtr].sockID=accept(sSocket,(struct sockaddr*)&Client[cCtr].cliaddr, &Client[cCtr].len);
	Client[cCtr].index=cCtr;

	pthread_create(&thread[cCtr],NULL,texting,(void *)&Client[cCtr]);
	cCtr ++;
   }
     
     for(int i=0;i<cCtr;i++)
	 pthread_join(thread[i],NULL);
     
     close(sSocket);
}
