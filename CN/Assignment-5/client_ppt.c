#include <arpa/inet.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <time.h>
#include <unistd.h>

#define PORT 1819

int main(void) {
    int s, n;
    socklen_t len;
    char buffer[100], recvaddr[16];
    struct sockaddr_in saddr, caddr;
    time_t ticks;
    s = socket(AF_INET, SOCK_DGRAM, 0);
    if (s < 0) {
        perror("socket");
        exit(0);
    }
    saddr.sin_family = AF_INET;
    saddr.sin_port = htons(PORT);
    saddr.sin_addr.s_addr = htonl(INADDR_ANY);
    if (bind(s, (struct sockaddr *)&saddr, sizeof(saddr)) < 0) {
        perror("bind");
        exit(0);
    }
    while (1) {
        printf("Waiting for request...\n");
        len = sizeof(struct sockaddr_in);
        n = recvfrom(s, buffer, sizeof(buffer) - 1, 0, (struct sockaddr *)&caddr, &len);
        if (n < 0) {
            perror("recv");
            break;
        }
        buffer[n] = 0;
        inet_ntop(AF_INET, &caddr.sin_addr, recvaddr, sizeof(recvaddr));
        printf("\nReceived request from %s\n", recvaddr);
        if (strcasecmp(buffer, "time") != 0) {
            strcpy(buffer, "Unknown request.");
            printf("%s\n", buffer);
            if (sendto(s, buffer, strlen(buffer), 0, (struct sockaddr *)&caddr, len) < 0) {
                perror("send");
                break;
            }
            continue;
        }
        ticks = time(NULL);
        snprintf(buffer, sizeof(buffer), "%24s", ctime(&ticks));
        printf("Serving the request..\n");
        if (sendto(s, buffer, strlen(buffer), 0, (struct sockaddr *)&caddr, len) < 0) {
            perror("send");
            break;
        } else
            printf("Request served..\n\n");
    }
    close(s);
    return 0;
}