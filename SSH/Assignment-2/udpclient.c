/* udpclient.c */

#include <arpa/inet.h>
#include <netdb.h>
#include <netinet/in.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <unistd.h>

int main() {
    int sock;
    struct sockaddr_in server_addr;
    struct hostent *host;
    char send_data[1024];

    host = (struct hostent *)gethostbyname((char *)"127.0.0.1");

    if ((sock = socket(AF_INET, SOCK_DGRAM, 0)) == -1) {
        perror("socket");
        exit(1);
    }

    server_addr.sin_family = AF_INET;
    server_addr.sin_port = htons(5000);
    server_addr.sin_addr = *((struct in_addr *)host->h_addr);
    bzero(&(server_addr.sin_zero), 8);

    while (1) {
        printf("Type Something (q or Q to quit): ");
        if (fgets(send_data, sizeof(send_data), stdin) == NULL) {
            perror("Input error");
            break;
        }
        send_data[strcspn(send_data, "\n")] = '\0'; // remove newline

        if ((strcmp(send_data, "q") == 0) || (strcmp(send_data, "Q") == 0))
            break;
        else
            sendto(sock, send_data, strlen(send_data), 0,
                   (struct sockaddr *)&server_addr, sizeof(struct sockaddr));
    }
}
