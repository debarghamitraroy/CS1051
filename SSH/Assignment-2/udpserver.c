/* udpserver.c */

#include <arpa/inet.h>
#include <netinet/in.h>
#include <stdio.h>
#include <stdlib.h>
#include <strings.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <unistd.h>

int main() {
    int sock;
    socklen_t addr_len;
    int bytes_read;
    char recv_data[1024];
    struct sockaddr_in server_addr, client_addr;

    if ((sock = socket(AF_INET, SOCK_DGRAM, 0)) == -1) {
        perror("Socket");
        exit(1);
    }
    printf("Socket Value %d\t\n", sock);

    server_addr.sin_family = AF_INET;
    server_addr.sin_port = htons(5000);
    server_addr.sin_addr.s_addr = inet_addr("127.0.0.1");
    bzero(&(server_addr.sin_zero), 8);

    if (bind(sock, (struct sockaddr *)&server_addr, sizeof(struct sockaddr))
        == -1) {
        perror("Bind");
        exit(1);
    }

    addr_len = sizeof(struct sockaddr);

    printf("\nUDPServer Waiting for client on port 5000");
    fflush(stdout);

    while (1) {
        bytes_read = recvfrom(sock, recv_data, 1024, 0,
                              (struct sockaddr *)&client_addr, &addr_len);

        recv_data[bytes_read] = '\0';

        // char *inet_ntoa(struct in_addr inaddr); Converts a 32-bit Internet
        // address in network byte order to a character string in dotted decimal
        // notation [slide Number 19 and 20]
        // ntohs : Network byte order to host byte order [Big endian to ?]
        // [slide number 12-17]

        printf("\n(%s , %d) said : ", inet_ntoa(client_addr.sin_addr),
               ntohs(client_addr.sin_port));
        printf("%s", recv_data);
        fflush(stdout); // Its purpose is to clear (or flush) the output buffer
                        // and move the buffered data to console
    }
    return 0;
}
