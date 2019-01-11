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

#define PORT_START 4000
#define PORT_END 6000

// TCP Server Connections
bool tcpServerConnections(struct sockaddr_in server, int sockfd, char IP[], int *port)
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
    server.sin_addr.s_addr = inet_addr(IP);
    memset(&(server.sin_zero), '\0', 8);
    
    for(int i=PORT_START;i<=PORT_END;i++)
    {
        server.sin_port = htons(i);
        // Check Server
        if (connect(sockfd, (struct sockaddr *) &server, sizeof(struct sockaddr)) == 0)
        {
            situation = true;
            *port = i;
            break;
        }
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
    int port;
    bool situation;
    situation = tcpServerConnections(server, sockfd, IP, &port);
    
    if(situation == false)
    {
        printf("Server is not TCP server.\nTrying UDP Server...\n");
        situation = udpServerConnections();
    }
    else 
    {
        printf("%d Port Open in TCP Server.\n", port);
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



















