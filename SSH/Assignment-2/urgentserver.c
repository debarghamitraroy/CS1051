/* urgentserver.c */

#include <arpa/inet.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <unistd.h>

#define PORT 8080

int main() {
    int server_fd, new_socket;
    struct sockaddr_in address;
    int addrlen = sizeof(address);
    char buffer[1024] = {0};

    server_fd = socket(AF_INET, SOCK_STREAM, 0);
    if (server_fd < 0) {
        perror("socket failed");
        exit(EXIT_FAILURE);
    }

    address.sin_family = AF_INET;
    address.sin_addr.s_addr = INADDR_ANY;
    address.sin_port = htons(PORT);

    if (bind(server_fd, (struct sockaddr *)&address, sizeof(address)) < 0) {
        perror("bind failed");
        exit(EXIT_FAILURE);
    }

    listen(server_fd, 3);
    printf("Server listening on port %d...\n", PORT);

    new_socket
        = accept(server_fd, (struct sockaddr *)&address, (socklen_t *)&addrlen);
    if (new_socket < 0) {
        perror("accept failed");
        exit(EXIT_FAILURE);
    }

    // Receive normal data
    recv(new_socket, buffer, sizeof(buffer), 0);
    printf("Normal data received: %s\n", buffer);

    // Receive urgent (out-of-band) data
    memset(buffer, 0, sizeof(buffer));
    recv(new_socket, buffer, sizeof(buffer), MSG_OOB);
    printf("Urgent data received: %s\n", buffer);

    close(new_socket);
    close(server_fd);
    return 0;
}
