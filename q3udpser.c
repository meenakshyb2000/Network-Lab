#include<stdio.h>
#include<string.h>
#include<sys/socket.h>
#include<unistd.h>
#include<stdlib.h>
#include<arpa/inet.h>
#include<netinet/in.h>
#include<sys/types.h>
void main()
{
	int sockid;
	char buffer[1024];
	struct sockaddr_in server,client;
	char * msg="Good Morning!";
	if((sockid=socket(AF_INET,SOCK_DGRAM,0))<0)
	{
		printf("Error");
		return;
	}
	memset(&server,0,sizeof(server));
	memset(&client,0,sizeof(client));
	server.sin_family=AF_INET;
	server.sin_port=htons(8080);
	server.sin_addr.s_addr=INADDR_ANY;
	bind(sockid,(struct sockaddr*)&server,sizeof(server));
	int len=sizeof(client);
	int n=recvfrom(sockid,(char*)buffer,1024,MSG_WAITALL,(struct sockaddr*)&client,&len);
	buffer[n]='\0';
	printf("%s\n",buffer);
	sendto(sockid,(char *)msg,strlen(msg),MSG_CONFIRM,(struct sockaddr*) &client,len);
	printf("Message has been sent!!\n"); 
	
}

