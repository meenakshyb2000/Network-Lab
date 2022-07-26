#include <netinet/in.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <unistd.h>
#include <arpa/inet.h>
#define PORT 8080
int main(int argc, char const* argv[])
{
    int sockfd, new_socket, valread;
    struct sockaddr_in address;
    int addrlen = sizeof(address);
 float no;
 float add=1.5;
    if ((sockfd = socket(AF_INET, SOCK_STREAM, 0))
        == 0) {
        printf("socket failed");
        return -1;
    }
 

    address.sin_family = AF_INET;
    address.sin_addr.s_addr = inet_addr("127.0.0.1");
    address.sin_port = htons(PORT);
 
  
    if (bind(sockfd, (struct sockaddr*)&address,
             sizeof(address))
        < 0) {
        printf("bind failed");
        return -1;
    }
    if (listen(sockfd, 3) < 0) {
        printf("listen");
        return -1;
    }
    if ((new_socket= accept(sockfd, (struct sockaddr*)&address,(socklen_t*)&addrlen))< 0) {
        printf("accept");
        return -1;
    }
    valread = read(new_socket,&no,sizeof(float));
    printf("The number received is: %f\n",no);
    no=no+add;
    if (listen(sockfd, 3) < 0) 
    {
        perror("listen");
        exit(EXIT_FAILURE);
    }
 
    if ((new_socket
         = accept(sockfd, (struct sockaddr*)&address,(socklen_t*)&addrlen))< 0) 
    {
        perror("accept");
        exit(EXIT_FAILURE);
    }
    printf("Sending to client 2...\n");	
    send(new_socket,&no, sizeof(float), 0);
    return 0;
}

