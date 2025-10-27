/* tcpclient.c */

#include <netdb.h>
#include <netinet/in.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <unistd.h>

#define PORT 8080
#define MAX_SIZE 1024

// struct hostent {
//     char *h_name;
//     char **h_aliases;
//     int h_addrtype;
//     int h_length;
//     char **h_addr_list;
// };

// #define h_addr h_addr_list[0]

// A zero-terminated array of network addresses for the host. Host addresses are returned in network byte order. A #define statement is used to define the following: h_addr, The first address in h_addr_list. This is for backward compatibility.

// struct in_addr {
//     u_long s_addr; // 32-bit netid/hostid
// };

int main() {
    int sock, bytes_recieved;
    char send_data[MAX_SIZE], recv_data[MAX_SIZE];
    struct hostent *host;
    struct sockaddr_in server_addr;

    host = gethostbyname("127.0.0.1");

    if ((sock = socket(AF_INET, SOCK_STREAM, 0)) == -1) {
        perror("Socket");
        exit(1);
    }

    server_addr.sin_family = AF_INET;
    server_addr.sin_port = htons(PORT);
    server_addr.sin_addr = *((struct in_addr *)host->h_addr);
    bzero(&(server_addr.sin_zero), 8);

    if (connect(sock, (struct sockaddr *)&server_addr, sizeof(struct sockaddr))
        == -1) {
        perror("Connect");
        exit(1);
    }

    while (1) {
        bytes_recieved = recv(sock, recv_data, 1024, 0);
        recv_data[bytes_recieved] = '\0';

        if (strcmp(recv_data, "q") == 0 || strcmp(recv_data, "Q") == 0) {
            close(sock);
            break;
        } else
            printf("\nRecieved data = %s ", recv_data);

        printf("\nSEND (q or Q to quit) : ");
        if (fgets(send_data, sizeof(send_data), stdin) == NULL) {
            perror("Input error");
            break;
        }
        send_data[strcspn(send_data, "\n")] = '\0';

        if (strcmp(send_data, "q") != 0 && strcmp(send_data, "Q") != 0) {
            send(sock, send_data, strlen(send_data), 0);
        } else {
            send(sock, send_data, strlen(send_data), 0);
            close(sock);
            break;
        }
    }
    close(sock);
    return 0;
}
