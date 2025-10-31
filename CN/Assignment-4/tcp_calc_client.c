#include <arpa/inet.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>

#define PORT 8080

int main() {
    int sock = 0;
    struct sockaddr_in serv_addr;
    char expr[100], vars[200], buffer[1024] = {0};
    printf("Enter expression (e.g., a+b*c/d): ");
    fgets(expr, sizeof(expr), stdin);
    expr[strcspn(expr, "\n")] = 0;
    printf("Enter values (e.g., a=10,b=15,c=5,d=3): ");
    fgets(vars, sizeof(vars), stdin);
    vars[strcspn(vars, "\n")] = 0;
    if ((sock = socket(AF_INET, SOCK_STREAM, 0)) < 0) {
        perror("Socket creation error");
        return -1;
    }
    serv_addr.sin_family = AF_INET;
    serv_addr.sin_port = htons(PORT);
    if (inet_pton(AF_INET, "127.0.0.1", &serv_addr.sin_addr) <= 0) {
        perror("Invalid address");
        return -1;
    }
    if (connect(sock, (struct sockaddr *)&serv_addr, sizeof(serv_addr)) < 0) {
        perror("Connection Failed");
        return -1;
    }
    char send_data[512];
    snprintf(send_data, sizeof(send_data), "%s;%s", expr, vars);
    send(sock, send_data, strlen(send_data), 0);
    read(sock, buffer, sizeof(buffer));
    printf("Result from server: %s\n", buffer);
    close(sock);
    return 0;
}
