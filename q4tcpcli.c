#include<stdio.h>
#include<string.h>
#include<unistd.h>
#include<sys/socket.h>
#include<arpa/inet.h>
void main()
{
        int sockid,n;
        int arr[100];
        //={1,3,6,11,8,9,7,2,10,38};
        printf("Enter the size of the array: ");
        scanf("%d",&n);
        printf("Enter the array: ");
        for(int i=0;i<n;i++)
        {
        	scanf("%d",&arr[i]);
        }
        
        float avg;
        int min,max;
        struct sockaddr_in server;
        sockid=socket(AF_INET,SOCK_STREAM,0);
        if(sockid<0)
        {
                printf("ERROR!!\n");
                return;
        }
        server.sin_family=AF_INET;
        server.sin_port=htons(8080);
        server.sin_addr.s_addr=inet_addr("127.0.0.1"); //same machine
        //server.sin_addr.s_addr=inet_addr("172.20.32.228");
        if(connect(sockid,(struct sockaddr*)&server,sizeof(server))>0);
        	printf("Connection established!!\n");
        send(sockid,&n,sizeof(int),0);
        send(sockid,&arr,n*sizeof(int),0);
        recv(sockid,&min,sizeof(int),0);
        recv(sockid,&max,sizeof(int),0);
        recv(sockid,&avg,sizeof(float),0);
        printf("\n---------RESULTS--------\n");
        printf("  MINIMUM :%d\n  MAXIMUM : %d\n  AVERAGE: %f\n",min,max,avg);
        printf("\nTerminating connection...\n");
        close(sockid);
}

