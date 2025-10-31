#include <arpa/inet.h>
#include <fcntl.h>
#include <signal.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#define PORT 8080

int client_fd;

void sig_urg_handler(int signo) {
    char oob_data;
    recv(client_fd, &oob_data, 1, MSG_OOB);
    printf("Urgent data received: %c\n", oob_data);
}

int main() {
    int server_fd;
    struct sockaddr_in address;
    char buffer[1024];
    socklen_t addrlen = sizeof(address);
    server_fd = socket(AF_INET, SOCK_STREAM, 0);
    if (server_fd < 0) {
        perror("Socket creation failed");
        exit(EXIT_FAILURE);
    }
    address.sin_family = AF_INET;
    address.sin_addr.s_addr = INADDR_ANY;
    address.sin_port = htons(PORT);
    if (bind(server_fd, (struct sockaddr *)&address, sizeof(address)) < 0) {
        perror("Unable to bind");
        exit(EXIT_FAILURE);
    }
    listen(server_fd, 3);
    printf("Server listening on port %d...\n", PORT);
    client_fd = accept(server_fd, (struct sockaddr *)&address, &addrlen);
    if (client_fd < 0) {
        perror("accept error");
        exit(EXIT_FAILURE);
    }
    fcntl(client_fd, F_SETOWN, getpid());
    signal(SIGURG, sig_urg_handler);
    printf("Connected to client. Waiting for data...\n");
    while (1) {
        int n = recv(client_fd, buffer, sizeof(buffer) - 1, 0);
        if (n <= 0)
            break;
        buffer[n] = '\0';
        printf("Normal data received: %s\n", buffer);
    }
    close(client_fd);
    close(server_fd);
    return 0;
}
