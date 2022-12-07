// Default Lib
#include <stdio.h>  
#include <string.h>  
#include <stdlib.h>
#include <unistd.h>

// My lib 
#include "errproc.h"

// Lib for sockets
#include <sys/socket.h>  
#include <netinet/in.h>  
#include <arpa/inet.h> 

#define SERVERPORT 15151
#define BUFSIZE 3000
#define IP "127.0.0.1"

int main(){
    int fb = Socket(AF_INET, SOCK_STREAM, 0);
    struct sockaddr_in adr;
    adr.sin_family = AF_INET;
    adr.sin_addr.s_addr = inet_addr(IP);  
    adr.sin_port = htons(SERVERPORT);
    Connect(fb, (struct sockaddr*)&adr, sizeof adr);
    

    // Buffer
    char buf[BUFSIZE ];
    char c = '\n';
    char *p_buf;
    int k, len;

    while(1) {
        // Make Message
        fgets(buf, BUFSIZE, stdin);
        len = strlen(buf) + 1;
        p_buf = buf;

        // Sending
        while (len > 0)
        {
            k = send(fb, p_buf, len, 0); 
            if (k == -1)
            {
                printf("cannot write to server!\n");
                break;
            }
            p_buf += k;
            len -= k;
        }


        if (strcmp(buf, "exit\n") == 0){
            printf("End working...");
            close(fb);
            break;
        }   
    }

    return 0;
}