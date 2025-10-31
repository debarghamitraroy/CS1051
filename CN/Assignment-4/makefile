CC = gcc
CFLAGS = -o

all: server client tcp_server tcp_client udp_server udp_client tcp_calc_server tcp_calc_client

server: server.c
	$(CC) server.c $(CFLAGS) server

tcp_server: tcp_server.c
	$(CC) tcp_server.c $(CFLAGS) tcp_server

udp_server: udp_server.c
	$(CC) udp_server.c $(CFLAGS) udp_server

tcp_calc_server: tcp_calc_server.c
	$(CC) tcp_calc_server.c $(CFLAGS) tcp_calc_server

client: client.c
	$(CC) client.c $(CFLAGS) client

tcp_client: tcp_client.c
	$(CC) tcp_client.c $(CFLAGS) tcp_client

udp_client: udp_client.c
	$(CC) udp_client.c $(CFLAGS) udp_client

tcp_calc_client: tcp_calc_client.c
	$(CC) tcp_calc_client.c $(CFLAGS) tcp_calc_client

clean:
	rm -f server client tcp_server tcp_client udp_server udp_client tcp_calc_server tcp_calc_client *.log
