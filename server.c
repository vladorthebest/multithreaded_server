#include <sys/socket.h>  
#include <netinet/in.h>  
#include <stdio.h>  
#include <string.h> 
#include <stdlib.h>  
#include <arpa/inet.h> 
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

int main(int argc, char **argv)
{
    // create Socket
    int server = Socket(AF_INET, SOCK_STREAM, 0);

    // setting Socket
    struct sockaddr_in adr;
    adr.sin_family = AF_INET;
    adr.sin_addr.s_addr = INADDR_ANY;  
    adr.sin_port = htons(15151); 
    Bind(server, (struct sockaddr*)&adr, sizeof(adr));

    // Listen
    Listen(server, 4);

    // Accept
    struct sockaddr_in client;  
    memset(&client, 0, sizeof(client));  
    socklen_t len = sizeof(client); 
    int fb = Accept(server, (struct sockaddr*)&client, &len);

    // Reading
    size_t nread;
    char buf[256];
    nread = recv(fb, buf, 256, 0);
    if(nread == -1){
        perror("read failed!\n");
        exit(EXIT_FAILURE);
    }
    else if(nread == 0){
        printf("\nclient disconnected.\n");
    }
    else{
        printf("%s", buf);
    }

    close(server);
    close(fb);
    return 0;
}
