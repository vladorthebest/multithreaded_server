// Default Lib
#include <stdio.h>
#include <string.h> 
#include <stdlib.h> 
#include <unistd.h>

// My lib 
#include "errproc.h"
#include "technical_task.h"

// Lib for sockets
#include <sys/socket.h>  
#include <netinet/in.h>
#include <sys/types.h>
#include <arpa/inet.h> 

// Lib for sig and thread
#include <pthread.h>
#include <signal.h>

// Const
#define SERVERPORT 15151
#define BUFSIZE 3000

//Socket
int socket_user;

// Signal
void sig_parent(int signo)
{
  if (signo == SIGINT)
    printf("Close server\n");
    close(socket_user);
    exit(0);
}

void childProc(int pipeSC[2]){
    char buf[BUFSIZE];
    int intbuf[100];

    close(pipeSC[1]);
    int readPipe = pipeSC[0];

    // Arg for AVG
    data listAvg;
    float* avg;
    int size;
    pthread_t tidavg;

    // isPrime
    int num;
    int* isPrime;
    pthread_t tidpri;

    while (strcmp(buf, "exit\n") != 0) {
        read(readPipe, buf, sizeof(buf));
        printf("%s", buf);

        // AVG
        if (strcmp(buf, "avg\n") == 0){
            read(readPipe, buf, sizeof(buf));
            printf("Size: %s", buf);
            size = atoi(buf);
            // Input Data
            for(int i=0;i<size;i++){
                read(readPipe, buf, sizeof(buf));
                printf("Data %d: %s", i+1, buf);
                intbuf[i] = atoi(buf);
            }

            // avg thread
            listAvg.size = size;
            listAvg.arr = &intbuf[0];
            pthread_create(&tidavg, NULL, threadAvg, &listAvg);
            pthread_join(tidavg, (void **)&avg);
            gcvt(*avg, 6,buf);
            printf("Result: %s\n", buf);
        }

        // IsPrime
        if (strcmp(buf, "isprime\n") == 0){
            read(readPipe, buf, sizeof(buf));
            printf("Number: %s", buf);
            num = atoi(buf);

            pthread_create(&tidpri, NULL, threadisPrime, &num);
            pthread_join(tidpri, (void **)&isPrime);
            gcvt(*isPrime, 1,buf);
            printf("Result: %s\n", buf);

        }
    }
}

void parentProc(int newSocket, int pipeSC[2], pid_t pidC){
    // Buffer
    size_t nread;
    char buf[BUFSIZE];
    char *p_buf;
    int k, len_buf;

    // Pipe
    close(pipeSC[0]);
    int writePipe = pipeSC[1];


    while (1) {
        // Reading
        nread = recv(newSocket, buf, BUFSIZE, 0);
        
        write(writePipe, buf, (strlen(buf)+1));

        if (strcmp(buf, "exit\n") == 0){
            kill(pidC, SIGKILL);
            break;
        } 

    }
}

void * socketThread (void *arg){
    // New Socket
    int newSocket = *((int *)arg);

    // Pipe
    int pipeSC[2];
    pipe(pipeSC); // Server -> Client

    // New Process
    pid_t pid = fork();

    if (pid == 0){
        // Child
        childProc(pipeSC);

    } else if (pid > 0) {
        // Parent
        signal(SIGINT, sig_parent);
        parentProc(newSocket, pipeSC, pid);
    } else {
        printf("fork() failed!\n");
    }

    printf("Client end work!\n");
    close(newSocket);
    pthread_exit(NULL);
}



int main(int argc, char **argv)
{   
    
    // create Listen Socket
    socket_user = Socket(AF_INET, SOCK_STREAM, 0);

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
