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

#define PORT_START 4950
#define PORT_END 5050

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
    
    for(int i = PORT_START; i <= PORT_END; i++)
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
bool udpServerConnections(int *port, int server_port)
{
    bool situation = false;
    int sock, addr_len, rval, result = 0;
    fd_set s;
    struct sockaddr_in server_addr;
    char IP[16] = "192.168.245.129\0";
    struct timeval timeout;

    if ((sock = socket(AF_INET, SOCK_DGRAM, IPPROTO_UDP)) == -1)
    {
        perror("socket");
        exit(1);
    }
    
    server_addr.sin_family = AF_INET;
    server_addr.sin_port = htons(server_port);
    server_addr.sin_addr.s_addr = inet_addr(IP);
    bzero(&(server_addr.sin_zero), 8);
    
    if(connect(sock, (struct sockaddr *)&server_addr, sizeof(struct sockaddr_in)) == -1)
    {
        perror("connect");
        exit(1);
    }
    
    send(sock, "hello", 6, 0);
    timeout.tv_sec = 0;
    timeout.tv_usec = 450000;
    
    result = select(sock + 1, &s, NULL, NULL, &timeout);
    
    if(result == 0)
    {
        situation = true;
        *port = server_port;
    }
    
    switch(result) 
    {
        case 1:
            //printf("Timeout\n");
            break;

        case 0: 
            situation = true;
            *port = server_port;
            break;
    }
    
    close(sock);
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
    }
    else 
    {
        printf("%d Port Open in TCP Server.\n", port);
        exit(1);
    }
    
    if(situation == false)
    {
        for(int i = PORT_START; i <= PORT_END; i++)
        {
            situation = udpServerConnections(&port, i);
            if(situation == true)
            {
                printf("%d Port Open in UDP Server.\n", port);
                break;
            }
        }
    }
    
    if(situation == false)
        printf("Server is not UDP Server.\n");
}

int main() 
{
    char IP[16] = "192.168.245.129\0";
    int sockfd;
    struct sockaddr_in server;
    
    display(server, sockfd, IP);
    
    return 0;
}
