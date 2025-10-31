CC = gcc
CFLAGS = -o

all: copy compare

copy: copy.c
	$(CC) copy.c $(CFLAGS) copy

compare: compare.c
	$(CC) compare.c $(CFLAGS) compare

clean:
	rm -f copy compare destination.bin
