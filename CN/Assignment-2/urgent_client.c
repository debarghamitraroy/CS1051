#include <arpa/inet.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>

#define PORT 8080

int main() {
    int sock = 0;
    struct sockaddr_in serv_addr;
    char normal[100], urgent_char;
    if ((sock = socket(AF_INET, SOCK_STREAM, 0)) < 0) {
        perror("Socket creation failed");
        return -1;
    }
    serv_addr.sin_family = AF_INET;
    serv_addr.sin_port = htons(PORT);
    inet_pton(AF_INET, "127.0.0.1", &serv_addr.sin_addr);
    if (connect(sock, (struct sockaddr *)&serv_addr, sizeof(serv_addr)) < 0) {
        perror("Connection error");
        return -1;
    }
    printf("Enter normal message: ");
    fgets(normal, sizeof(normal), stdin);
    normal[strcspn(normal, "\n")] = 0;
    send(sock, normal, strlen(normal), 0);
    printf("Sent normal data: %s\n", normal);
    printf("Enter a single urgent character: ");
    scanf(" %c", &urgent_char);
    send(sock, &urgent_char, 1, MSG_OOB);
    printf("Sent urgent data: %c\n", urgent_char);
    close(sock);
    return 0;
}
