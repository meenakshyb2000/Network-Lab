#include<stdio.h>
#include<string.h>
#include<unistd.h>
#include<sys/socket.h>
#include<arpa/inet.h>
void main()
{
	int sockid;
	char *msg="CLIENT SAYS HI";
	char msg2[100];
	struct sockaddr_in server;
	sockid=socket(AF_INET,SOCK_STREAM,0);
	if(sockid<0)
	{
		printf("Error occured");
		return;
	}
	server.sin_family=AF_INET;
	server.sin_port=htons(8080);
	server.sin_addr.s_addr=inet_addr("172.20.32.111"); 
	//client and server on the diff machine, server's ip address given in inet
	//server.sin_addr.s_addr=inet_addr("127.0.01"); //client and server on the same machine
	connect(sockid,(struct sockaddr*)&server,sizeof(server));
	printf("Connection established!!\n");
	send(sockid,msg,strlen(msg),0);
	printf("Sent HI\n");
	recv(sockid,msg2,1024,0);
	printf("%s\n",msg2);
	printf("\nTerminating connection...\n");
	close(sockid);
}
