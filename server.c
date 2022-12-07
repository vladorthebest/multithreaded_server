#include <sys/socket.h>  
#include <netinet/in.h>  
#include <stdio.h>
#include <sys/types.h>  
#include <string.h> 
#include <stdlib.h>  
#include <arpa/inet.h> 
#include <unistd.h>
#include "errproc.h"
#include "technical_task.h"
#include <pthread.h>
#include <signal.h>
#include <sys/wait.h>

#define SERVERPORT 15151
#define BUFSIZE 3000

int socket_user;

void sig_handler(int signo)
{
  if (signo == SIGINT)
    printf("Close server\n");
    close(socket_user);
    exit(0);
}

void childProc(int pipeSC[2], int pipeCS[2]){
    char buf[BUFSIZE];
    int intbuf[100];
    close(pipeSC[1]);
    close(pipeCS[0]);
    int readPipe = pipeSC[0];
    int writePipe = pipeCS[1];
    pthread_t tid;
    // Read parent tid
    pid_t parent = getppid();
    data listAvg;
    float* avg;

    while (strcmp(buf, "exit\n") != 0) {
        read(readPipe, buf, sizeof(buf));
        printf("%s", buf);
        if (strcmp(buf, "avg\n") == 0){
            int size;
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
            pthread_create(&tid, NULL, threadAvg, &listAvg);
            pthread_join(tid, (void **)&avg);
            gcvt(*avg, 6,buf);
            printf("Result: %s\n", buf);
            write(writePipe, buf, (strlen(buf)+1));
        }
    }
}

void parentProc(int newSocket, int pipeSC[2], int pipeCS[2], pid_t pidC){
    // Buffer
    size_t nread;
    char buf[BUFSIZE];
    char *p_buf;
    int k, len_buf;

    close(pipeSC[0]);
    close(pipeCS[1]);
    int writePipe = pipeSC[1];
    int readPipe = pipeCS[0];

    while (1) {
        // Reading
        nread = recv(newSocket, buf, BUFSIZE, 0);
        // printf("%s", buf);
        if (strcmp(buf, "exit\n") == 0){
            kill(pidC, SIGKILL);
            break;
        } else if (strcmp(buf, "res\n") == 0){
            break;
        }
        // send to client from pipe
        write(writePipe, buf, (strlen(buf)+1));

    }
    while(1){
        read(readPipe, buf, sizeof(buf));
        printf("%s", buf);
        // send(newSocket, buf, BUFSIZE, 0);
    }
    
}

void * socketThread (void *arg){
    // New Socket
    int newSocket = *((int *)arg);

    // Pipe
    int pipeSC[2];
    pipe(pipeSC); // Server -> Client
    int pipeCS[2];
    pipe(pipeCS); // Client -> Server

    // New Process
    pid_t pid = fork();

    if (pid == 0){
        // Child
        childProc(pipeSC, pipeCS);

    } else if (pid > 0) {
        // Parent
        signal(SIGINT, sig_handler);
        parentProc(newSocket, pipeSC, pipeCS, pid);
    } else {
        printf("fork() failed!\n");
    }
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
