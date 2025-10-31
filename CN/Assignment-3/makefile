CC = gcc
CFLAGS = -o

all: server client

server: server.c
	$(CC) server.c $(CFLAGS) server

client: client.c
	$(CC) client.c $(CFLAGS) client
clean:
	rm -f server client
