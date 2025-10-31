CC = gcc
CFLAGS = -o

all: server client urgent_server urgent_client

server: server.c
	$(CC) server.c $(CFLAGS) server

urgent_server: urgent_server.c
	$(CC) urgent_server.c $(CFLAGS) urgent_server

client: client.c
	$(CC) client.c $(CFLAGS) client

urgent_client: urgent_client.c
	$(CC) urgent_client.c $(CFLAGS) urgent_client

clean:
	rm -f server client urgent_server urgent_client
