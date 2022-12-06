#include <sys/socket.h>  
#include <netinet/in.h>  
#include <stdio.h>  
#include <string.h> 
#include <stdlib.h>  
#include <arpa/inet.h> 
#include <unistd.h>
#include "errproc.h"
#include <pthread.h>

#define SERVERPORT 15151
#define BUFSIZE 3000

void childProc(int pipeio[2]){
    char buf[BUFSIZE];
    int intbuf[100];
    close(pipeio[1]);
    int i=0;
    while (1) {
        read(pipeio[0], buf, sizeof(buf));
        
        // Exit
        if (strcmp(buf, "exit\n") == 0){
            break;
        } 
        // Input Data
        else if (strcmp(buf, "data\n") == 0){
            
        }
    }
}


void parentProc(int newSocket, int pipeio[2]){
    // Buffer
    size_t nread;
    char buf[BUFSIZE];
    char *p_buf;
    int k, len_buf;

    close(pipeio[0]);

    while (1) {
        // Reading
        nread = recv(newSocket, buf, BUFSIZE, 0);
        printf("%s", buf);
        write(pipeio[1], buf, (strlen(buf)+1));
        if (strcmp(buf, "exit\n") == 0){
            break;
        }
    }
}

void * socketThread (void *arg){
    // New Socket
    int newSocket = *((int *)arg);

    // Pipe
    int pipeio[2];
    pipe(pipeio);

    // New Process
    pid_t pid = fork();

    if (pid == 0){
        // Child
        childProc(pipeio);

    } else if (pid > 0) {
        // Parent
        parentProc(newSocket, pipeio);
        
    } else {
        printf("fork() failed!\n");
    }
    close(newSocket);
    pthread_exit(NULL);
}

int main(int argc, char **argv)
{
    // create Listen Socket
    int socket_user = Socket(AF_INET, SOCK_STREAM, 0);

    // setting Socket
    struct sockaddr_in adr;
    adr.sin_family = AF_INET; // IPv4
    adr.sin_addr.s_addr = INADDR_ANY;  
    adr.sin_port = htons(SERVERPORT); 
    Bind(socket_user, (struct sockaddr*)&adr, sizeof(adr));

    // Listen
    if (listen(socket_user, 10) == 0) {
        printf("Listening\n");
    }
    else {
        printf("Error\n");
    }

    // Date for new socket
    pthread_t tid[10];
    int i = 0;
    struct sockaddr_in serverStorage;
    int newSocket;
    socklen_t addr_size;

    while(1)
    {
        // Accept
        addr_size = sizeof serverStorage;
        newSocket = Accept(socket_user, (struct sockaddr*)&serverStorage, &addr_size);

        if( pthread_create(&tid[i++], NULL, socketThread, &newSocket) != 0 ){
            printf("Failed to create thread\n");
        }

        if(i >= 10){
            i = 0;
            while(i<10){
                pthread_join(tid[i++],NULL);
            }
            i = 0;
        }
           
    }
    return 0;
}
