#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include<unistd.h>
#include<sys/socket.h>
#include<arpa/inet.h>
#include<netinet/in.h>
#include<sys/types.h>
void main()
{
        int sockid;
        int min,max;
        float avg;
        int arr[]={5,2,3,1,4};
        struct sockaddr_in server;
        if((sockid=socket(AF_INET,SOCK_DGRAM,0))<0)
        {
                printf("Error!!\n");
                return;
        }
        memset(&server,0,sizeof(server));
        server.sin_port=htons(8080);
        server.sin_family=AF_INET;
        server.sin_addr.s_addr=INADDR_ANY;
        sendto(sockid,&arr,5*sizeof(int),MSG_CONFIRM,(struct sockaddr*)&server,sizeof(server));
        printf("\nArray has been sent!!");
        int len=sizeof(struct sockaddr_in);
        recvfrom(sockid,&min,sizeof(int),MSG_WAITALL,(struct sockaddr*)&server,&len);
        recvfrom(sockid,&max,sizeof(int),MSG_WAITALL,(struct sockaddr*)&server,&len);
        recvfrom(sockid,&avg,sizeof(float),MSG_WAITALL,(struct sockaddr*)&server,&len);
        printf("\n---------RESULTS--------\n");
        printf("  MINIMUM :%d\n  MAXIMUM : %d\n  AVERAGE: %f\n",min,max,avg);
        printf("\nClosing...\n");
        close(sockid);
}

