#include <stdio.h>
#include <stdlib.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <unistd.h>
#include <string.h>
#include <arpa/inet.h>
#include <pthread.h>
#include <netinet/in.h>

void* receive(void* sockID){

	int cSocket=*((int *)sockID);
	int read;
	char data[1024];
	while(1)
	{
		read=recv(cSocket,data,1024,0);
		data[read]='\0';
		if(strcmp(data,"STOP")==0)
		    exit(1);
		printf("%s\n",data);
	}
}

void main(){

	int cSocket=socket(AF_INET, SOCK_STREAM, 0);
	struct sockaddr_in servaddr;
	servaddr.sin_family=AF_INET;
	servaddr.sin_port=htons(8080);
	servaddr.sin_addr.s_addr=INADDR_ANY;

	if(connect(cSocket,(struct sockaddr*)&servaddr,sizeof(servaddr))==-1) 
	   exit(1);

	printf("Connection established ..\n");

	pthread_t thread;
	pthread_create(&thread,NULL,receive,(void *)&cSocket);
        
	printf("Enter START to start and STOP to stop: \n");
	size_t len;
		
	while(1)
    {
		char *input=NULL;
		getline(&input,&len,stdin);
		strtok(input,"\n");
		send(cSocket,input,1024,0);
	}
}
