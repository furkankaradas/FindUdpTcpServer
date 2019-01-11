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

// TCP Server Connections
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
        situation = true;
    }
    
    // Closed Socket
    close(sockfd);
    return situation;
}

// UDP Server Connections
bool udpServerConnections()
{
    bool situation = false;
    
    
    
    
    return situation;
}

// Display Function
void display(struct sockaddr_in server, int sockfd, char IP[])
{
    bool situation;
    situation = tcpServerConnections(server, sockfd, IP);
    
    if(situation == false)
    {
        printf("Server is not TCP server.\nTrying UDP Server...\n");
        situation = udpServerConnections();
    }
    else 
    {
        printf("TCP Server.\n");
        exit(1);
    }
    
    if(situation == false)
    {
        printf("Server is not UDP server.\n");
    }
    else
    {
        printf("UDP Server.\n");
        exit(1);
    }
}

int main() 
{
    char IP[16] = "192.168.245.129\0";
    int sockfd;
    struct sockaddr_in server;
    
    display(server, sockfd, IP);
    
    return 0;
}



















