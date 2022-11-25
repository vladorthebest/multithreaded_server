#ifndef ERRPROC_H
#define ERRPROC_H
#include <sys/socket.h>

int Socket(int domain, int type, int protocol);

void Bind(int sockfd, const struct sockaddr *addr, socklen_t addrlen);

void Listen(int sock_desc, int backlog);

int Accept(int sockfd, struct sockaddr *adr, socklen_t *addrlen);

#endif