#include <netinet/in.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <unistd.h>
#include <arpa/inet.h>
#define PORT 8080
void reverse(char * start,char *end)
{
    while(start != end)
    {
        char t = *start;
        *start = *end;
        *end = t;

        start++;
        end--;
    }
}
int main(int argc, char const* argv[])
{
    int sockfd, new_socket, valread;
    struct sockaddr_in address;
    int addrlen = sizeof(address);
    char buffer[1024] = { 0 };
    if ((sockfd = socket(AF_INET, SOCK_STREAM, 0))== 0) 
    {
        printf("Socket creation error!!");
        return -1;
    }
    address.sin_family = AF_INET;
    address.sin_addr.s_addr = inet_addr("127.0.0.1");
    address.sin_port = htons(PORT);
    if (bind(sockfd, (struct sockaddr*)&address,sizeof(address))< 0) 
    {
        printf("Bind failed!!");
        return -1;
    }
    listen(sockfd, 3);
    if ((new_socket= accept(sockfd, (struct sockaddr*)&address,(socklen_t*)&addrlen))< 0) 
    {
        printf("Connection accepted");
        exit(EXIT_FAILURE);
    }
    valread = read(new_socket, buffer, 1024);
    printf("\n------STRING RECEIVED-------\n%s\n",buffer);
    reverse(buffer,buffer+valread-1);
    listen(sockfd, 3);
    if ((new_socket= accept(sockfd, (struct sockaddr*)&address,(socklen_t*)&addrlen))< 0) {
        printf("Connection accepted");
        exit(EXIT_FAILURE);
    }
 
    send(new_socket, buffer, strlen(buffer), 0);
    return 0;
}
