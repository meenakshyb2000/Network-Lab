#include<stdio.h>
#include<string.h>
#include<arpa/inet.h>
#include<unistd.h>
#include<sys/socket.h>
void main()
{
	int sockid,cliid;
	char buf1[100];
	char *buf2="SERVER SAYS HI";
	struct sockaddr_in server,client;
	sockid=socket(AF_INET,SOCK_STREAM,0);
	if(sockid<0)
	{
		printf("Error");
		return;
	}
	server.sin_family=AF_INET;
	server.sin_port=htons(8080);
	server.sin_addr.s_addr=inet_addr("172.20.35.144"); //my ip
	if(bind(sockid,(struct sockaddr*)&server,sizeof(server))<0)
	{
		printf("Bind failed");
		return;
	}
	listen(sockid,3);
	int c=sizeof(struct sockaddr_in);
	cliid=accept(sockid,(struct sockaddr*)&server,(socklen_t *)&c);
	recv(cliid,buf1,1024,0);
	printf("%s\n",buf1);
	send(cliid,buf2,strlen(buf2),0);
	printf("Sent HI\n");
	close(sockid);
}
