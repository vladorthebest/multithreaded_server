# ARG
CC = gcc #compiler
SERVER = server
CLIENT = client
 
all: errproc.o server.o timer.o technical_task.o
	$(CC) server.c technical_task.c timer.c errproc.c -o $(SERVER) -lm

client: errproc.o client_user.o
	$(CC) client_user.c errproc.c -o $(CLIENT)
cleanall:
	rm *.o
	rm $(SERVER)
	rm $(CLIENT)

cleanser:
	rm errproc.o server.o timer.o technical_task.o
	rm $(SERVER)
	
cleancli:
	rm client_user.o
	rm $(CLIENT)