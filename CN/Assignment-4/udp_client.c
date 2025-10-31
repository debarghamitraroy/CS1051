#include <arpa/inet.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

int main() {
    int sockfd;
    struct sockaddr_in servaddr;
    char buffer[1024];
    char message[256];
    int PORT = 8080;
    if ((sockfd = socket(AF_INET, SOCK_DGRAM, 0)) < 0) {
        perror("socket creation failed");
        exit(EXIT_FAILURE);
    }
    memset(&servaddr, 0, sizeof(servaddr));
    servaddr.sin_family = AF_INET;
    servaddr.sin_port = htons(PORT);
    servaddr.sin_addr.s_addr = inet_addr("127.0.0.1");
    printf("Enter a string (max 256 character): ");
    fgets(message, sizeof(message), stdin);
    message[strcspn(message, "\n")] = 0;
    sendto(sockfd, message, strlen(message), 0, (const struct sockaddr *)&servaddr, sizeof(servaddr));
    int n;
    socklen_t len = sizeof(servaddr);
    n = recvfrom(sockfd, buffer, 1024, 0, (struct sockaddr *)&servaddr, &len);
    buffer[n] = '\0';
    printf("Server replied: %s\n", buffer);
    close(sockfd);
    return 0;
}
