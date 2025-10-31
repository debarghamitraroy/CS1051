#include <arpa/inet.h>
#include <netinet/in.h>
#include <stdio.h>
#include <stdlib.h>
#include <strings.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <unistd.h>

#define PORT 8080
#define MAX_SIZE 1024

int main() {
    int sock;
    socklen_t addr_len;
    int bytes_read;
    char recv_data[MAX_SIZE];
    struct sockaddr_in server_addr, client_addr;
    if ((sock = socket(AF_INET, SOCK_DGRAM, 0)) == -1) {
        perror("Socket creation failed");
        exit(1);
    }
    server_addr.sin_family = AF_INET;
    server_addr.sin_port = htons(PORT);
    server_addr.sin_addr.s_addr = inet_addr("127.0.0.1");
    bzero(&(server_addr.sin_zero), 8);
    if (bind(sock, (struct sockaddr *)&server_addr, sizeof(struct sockaddr))
        == -1) {
        perror("Unable to bind");
        exit(1);
    }
    addr_len = sizeof(struct sockaddr);
    printf("UDP server Waiting for client on port %d\n", PORT);
    fflush(stdout);
    while (1) {
        bytes_read = recvfrom(sock, recv_data, 1024, 0, (struct sockaddr *)&client_addr, &addr_len);
        recv_data[bytes_read] = '\0';
        printf("(%s , %d) said: ", inet_ntoa(client_addr.sin_addr), ntohs(client_addr.sin_port));
        printf("%s\n", recv_data);
        fflush(stdout);
    }
    close(sock);
    return 0;
}
