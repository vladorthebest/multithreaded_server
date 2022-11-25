#include "errproc.h"

#include <sys/socket.h>  
#include <stdio.h>  
#include <string.h> 
#include <stdlib.h>  
#include <unistd.h> 

int Socket(int domain, int type, int protocol){
    int sock_desc = socket(domain, type, protocol);
    if (sock_desc == -1)
    {
        perror("cannot create socket!\n");
        exit(EXIT_FAILURE);
    }
    return sock_desc;
}

void Bind(int sockfd, const struct sockaddr *addr, socklen_t addrlen){
    if (bind(sockfd, addr, addrlen) == -1)
    {
        perror("bind failed\n");
        close(sockfd);  
        exit(EXIT_FAILURE);
    }
}

void Listen(int sock_desc, int backlog){
    if (listen(sock_desc, backlog) == -1)
    {
        perror("listen failed!\n");
        close(sock_desc);  
        exit(EXIT_FAILURE);
    }
}

int Accept(int sockfd, struct sockaddr *adr, socklen_t *addrlen){
    int fb = accept(sockfd, adr, addrlen);
    if ( fb == -1)
    {
        printf("cannot accept client!\n");
        close(sockfd);  
        exit(EXIT_FAILURE);
    }
    return fb;
}
