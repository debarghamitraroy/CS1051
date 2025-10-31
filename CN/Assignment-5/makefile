CC = gcc
CFLAGS = -o

all: sender receiver server1 client1 threads

sender: sender.c common.h
	$(CC) sender.c $(CFLAGS) sender

receiver: receiver.c common.h 
	$(CC) receiver.c $(CFLAGS) receiver

server1: server/server.c
	$(CC) server/server.c $(CFLAGS) server/server

client1: client/client.c
	$(CC) client/client.c $(CFLAGS) client/client

threads: pthreads.c
	$(CC) pthreads.c $(CFLAGS) pthreads

clean:
	rm -f sender receiver pthreads *.o
	rm -f server/server client/client
	rm -f server/server_log.log client/client_log.log
	rm -f client/*.jpg client/*.pdf client/*.txt client/*.bin
	rm -f client/*.doc client/*.mp3 client/*.mp4 client/*.png
	rm -f client/*.ppt client/*.wav client/*.xls
	rm -rf output/*