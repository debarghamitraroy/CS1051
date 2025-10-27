#include <arpa/inet.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <time.h>
#include <unistd.h>

#define PORT 1819

int main(int argc, char *argv[]) {
    int s, n;
    char buffer[100];
    struct sockaddr_in saddr;
    if (argc != 2) {
        printf("Usage::<%s> <Server_IP>\n", argv[0]);
        exit(0);
    }
    s = socket(AF_INET, SOCK_DGRAM, 0);
    if (s < 0) {
        perror("socket");
        exit(0);
    }
    saddr.sin_family = AF_INET;
    saddr.sin_port = htons(PORT);
    if (inet_pton(AF_INET, argv[1], &saddr.sin_addr) <= 0) {
        printf("Error. Invalid IP address\n");
        exit(0);
    }
    strcpy(buffer, "time");
    printf("Sending request to server %s\n", argv[1]);
    if (sendto(s, buffer, strlen(buffer), 0, (struct sockaddr *)&saddr,
               sizeof(saddr))) {
        perror("Send");
        exit(0);
    }
    printf("Waiting for response...\n");
    n = recvfrom(s, buffer, sizeof(buffer) - 1, 0, NULL, NULL);
    if (n < 0) {
        perror("Receive");
        exit(0);
    }
    buffer[n] = 0;
    printf("Reply from server %s is %s\n", argv[1], buffer);
    close(s);
    return (0);
}