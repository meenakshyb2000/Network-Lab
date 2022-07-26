
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
        struct sockaddr_in server,client;
        int arr[5];
        int min,max;
        float avg,sum;
        if((sockid=socket(AF_INET,SOCK_DGRAM,0))<0)
        {
                printf("ERROR!!");
                return;
        }
        memset(&server,0,sizeof(server));
        memset(&client,0,sizeof(client));
        server.sin_family=AF_INET;
        server.sin_port=htons(8080);
        server.sin_addr.s_addr=INADDR_ANY;
        bind(sockid,(struct sockaddr*)&server,sizeof(server));
        int len=sizeof(client);
        int n=recvfrom(sockid,&arr,5*sizeof(int),MSG_WAITALL,(struct sockaddr*)&client,&len);
        int i=0;
        printf("\n----------ARRAY RECEIVED-----------\n");
        while(i<5)
        {
        	printf("%d ",arr[i]);
        	i++;
        }
        min=arr[0];
        max=arr[0];
        avg=arr[0];
        i=0;
        while(i<5)
        {
		if(arr[i]>max)
			max=arr[i];
		if(arr[i]<min)
			min=arr[i];
		sum+=arr[i];
		i++;
        }
        avg=sum/5;
        sendto(sockid,&min,sizeof(int),MSG_CONFIRM,(struct sockaddr*) &client,len);
        sendto(sockid,&max,sizeof(int),MSG_CONFIRM,(struct sockaddr*) &client,len);
        sendto(sockid,&avg,sizeof(float),MSG_CONFIRM,(struct sockaddr*) &client,len);
        printf("\nResult has been sent!!!\n"); 
        
}
