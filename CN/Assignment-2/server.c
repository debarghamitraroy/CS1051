#include <arpa/inet.h>
#include <netinet/in.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <unistd.h>

#define PORT 8080
#define MAX_SIZE 1024

int main() {
    int sock, connected, bytes_recieved, true = 1;
    char send_data[MAX_SIZE], recv_data[MAX_SIZE];
    struct sockaddr_in server_addr, client_addr;
    socklen_t sin_size;
    if ((sock = socket(AF_INET, SOCK_STREAM, 0)) == -1) {
        perror("Socket creation failed");
        exit(1);
    }
    if (setsockopt(sock, SOL_SOCKET, SO_REUSEADDR, &true, sizeof(int)) == -1) {
        perror("setsockopt error");
        exit(1);
    }
    server_addr.sin_family = AF_INET;
    server_addr.sin_port = htons(PORT);
    server_addr.sin_addr.s_addr = INADDR_ANY;
    bzero(&(server_addr.sin_zero), 8);
    if (bind(sock, (struct sockaddr *)&server_addr, sizeof(struct sockaddr)) == -1) {
        perror("Unable to bind");
        exit(1);
    }
    if (listen(sock, 5) == -1) {
        perror("Unable to listen");
        exit(1);
    }
    printf("TCP Server Waiting for client on port %d\n", PORT);
    fflush(stdout);
    while (1) {
        sin_size = sizeof(struct sockaddr_in);
        connected = accept(sock, (struct sockaddr *)&client_addr, &sin_size);
        printf("TCP server got connection from (%s , %d)\n", inet_ntoa(client_addr.sin_addr), ntohs(client_addr.sin_port));
        while (1) {
            printf("Send data (q or Q to quit): ");
            if (fgets(send_data, sizeof(send_data), stdin) == NULL) {
                perror("Input error");
                break;
            }
            send_data[strcspn(send_data, "\n")] = '\0';
            if (strcmp(send_data, "q") == 0 || strcmp(send_data, "Q") == 0) {
                send(connected, send_data, strlen(send_data), 0);
                close(connected);
                break;
            } else
                send(connected, send_data, strlen(send_data), 0);

            bytes_recieved = recv(connected, recv_data, 1024, 0);
            recv_data[bytes_recieved] = '\0';
            if (strcmp(recv_data, "q") == 0 || strcmp(recv_data, "Q") == 0) {
                close(connected);
                break;
            } else {
                printf("Received data: %s\n", recv_data);
                fflush(stdout);
            }
        }
    }
    close(sock);
    return 0;
}
