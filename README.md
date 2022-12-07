# Unidirectional multithreaded server for UNIX system
## Developer: Nosov Vladyslav

### The project was developed during the OSRT course

## The goal of the project is to learn how to work with:
1. Socket
2. Process
3. Thread
4. Pipe
5. Makefile
6. Signals
7. Timer

## Project tools:
- GIT
- C

## IDE:
- VSCode
- Linux Ubuntu
  
## SERVER:
#### Server compilation
Write in Linux (UNIX) terminal 
``` make ```
#### Run Server
Write in Linux (UNIX) terminal 
``` ./server ```
#### Close Server
Press in Linux (UNIX) terminal 
``` ctrl+c ```
#### Server settings
- TIMERSEC - how long will it be idle without Users
- BUFSIZE - buffer size
- SERVERPORT - port for socket configuration

## Client:
#### Client compilation
``` make client ```
#### Run Client
Write in Linux (UNIX) terminal 
``` ./client ```
#### Server settings:
- SERVERPORT - port for socket configuration
- IP - IP for socket configuration
- BUFSIZE - buffer size

### Commands for Server:
#### AVG(array)
Input command:
    ``` avg ```
Input size array (for exemple 3):
    ``` 3 ```
Input date:
    ``` 2 ``` + Enter + ``` 4 ``` + Enter + ...
#### IsPrime
Input command:
    ` isprime `
Input number (for exemple 3):
    ``` 3 ```

#### Run Server
Write in Linux (UNIX) terminal 
``` ./server ```
#### Close Server
Press in Linux (UNIX) terminal 
``` ctrl+c ```
#### Close Client
Input in client terminal 
``` exit ```