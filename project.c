#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <errno.h>
#include <string.h>
#include <netdb.h>
#include <stdbool.h>
#include <sys/types.h>
#include <netinet/in.h>
#include <sys/socket.h>
#include <arpa/inet.h>

#define PORT 5000

bool tcpServerConnections(struct sockaddr_in server, int sockfd, char IP[])
{
    bool situation = false;
    // Socket Configurations
    if ((sockfd = socket(AF_INET, SOCK_STREAM, 0)) == -1)
    {
        perror("socket");
        exit(1);
    }
    
    //TCP Server Configurations
    server.sin_family = AF_INET;
    server.sin_port = htons(PORT);
    server.sin_addr.s_addr = inet_addr(IP);
    memset(&(server.sin_zero), '\0', 8);
    
    // Check Server
    if (connect(sockfd, (struct sockaddr *) &server, sizeof(struct sockaddr)) == 0)
    {
        printf("TCP Server.\n");
        situation = true;
    }
    
    // Closed Socket
    close(sockfd);
    return situation;
}

bool udpServerConnections()
{
    bool situation = false;
    
    
    
    
    return situation;
}

int main() 
{
    bool situation;
    char IP[16] = "192.168.245.129\0";
    int sockfd;
    struct sockaddr_in server;
    
    situation = tcpServerConnections(server, sockfd, IP);
    
    if(situation == false)
    {
        printf("Server is not TCP server.\nTrying UDP Server...\n");
        situation = udpServerConnections();
    }
    
    if(situation == false)
    {
        printf("Server is not UDP or TCP..\n");
    }
    
    return 0;
}



















