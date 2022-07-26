#include<stdio.h>
#include<string.h>
#include<arpa/inet.h>
#include<unistd.h>
#include<sys/socket.h>
#include<arpa/inet.h> //for inet_addr
void main()
{
        int sockid,cliid,n;
        int arr[100];
        int min,max;
        float avg,sum;
        struct sockaddr_in server,client;
        sockid=socket(AF_INET,SOCK_STREAM,0);
        if(sockid<0)
        {
                printf("Error\n");
                return;
        }
        server.sin_family=AF_INET;
        server.sin_port=htons(8080);
        server.sin_addr.s_addr=INADDR_ANY; //same machine
        //server.sin_addr.s_addr=inet_addr("172.20.35.144");
        if(bind(sockid,(struct sockaddr*)&server,sizeof(server))<0)
        {
                printf("SORRY!!Bind failed!!\n");
                return;
        }
        printf("Listening for a client....\n");
        listen(sockid,3);
        int c=sizeof(struct sockaddr_in);
        cliid=accept(sockid,(struct sockaddr*)&server,(socklen_t *)&c);
        printf("Connection accepted!!\n");
        recv(cliid,&n,sizeof(int),0);
        recv(cliid,&arr,n*sizeof(int),0);
        int i=0;
        printf("\n----------ARRAY RECEIVED-----------\n");
        while(i<n)
        {
        	printf("%d ",arr[i]);
        	i++;
        }
        min=arr[0];
        max=arr[0];
        avg=arr[0];
        i=0;
        sum=0;
        while(i<n)
        {
                if(arr[i]<min)
                        min=arr[i];
                else if(arr[i]>max)
                        max=arr[i];
                sum+=arr[i];
                i++;
        }
        avg=sum/n;
        send(cliid,&min,sizeof(int),0);
        send(cliid,&max,sizeof(int),0);
        send(cliid,&avg,sizeof(float),0);
        printf("\n\nConnection terminated!!\n");
        close(sockid);
}
