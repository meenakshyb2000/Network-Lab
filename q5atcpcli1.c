#include <arpa/inet.h>
#include <stdio.h>
#include <string.h>
#include <sys/socket.h>
#include <unistd.h>
#define PORT 8080
 
int main(int argc, char const* argv[])
{
    int sock = 0, valread;
    struct sockaddr_in serv_addr;
    char* hello;
	printf("Enter the message: ");
	scanf("%s",hello);

    char buffer[1024] = { 0 };
    if ((sock = socket(AF_INET, SOCK_STREAM, 0)) < 0) {
        printf("\n Socket creation error!!! \n");
        return -1;
    }
    serv_addr.sin_family = AF_INET;
    serv_addr.sin_port = htons(PORT);
    serv_addr.sin_addr.s_addr=inet_addr("127.0.0.1");
    if (connect(sock, (struct sockaddr*)&serv_addr,sizeof(serv_addr))< 0) 
    {
        printf("\nConnection Failed!! \n");
        return -1;
    }
    send(sock, hello, strlen(hello), 0);
    printf("Message sent to server!!!\n");
    return 0;
}
