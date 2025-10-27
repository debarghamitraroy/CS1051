/* server.c */

#include <arpa/inet.h>
#include <netinet/in.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <unistd.h>

#define BUFFER_SIZE 1024
#define OUTPUT_FILE "received_audio.wav"

int main() {
    int sock;
    socklen_t addr_len;
    ssize_t bytes_read;
    char buffer[BUFFER_SIZE];
    struct sockaddr_in server_addr, client_addr;
    FILE *fp;

    if ((sock = socket(AF_INET, SOCK_DGRAM, 0)) == -1) {
        perror("Socket");
        exit(1);
    }
    printf("Socket Value %d\n", sock);

    server_addr.sin_family = AF_INET;
    server_addr.sin_port = htons(5000);
    server_addr.sin_addr.s_addr = inet_addr("127.0.0.1");
    memset(&(server_addr.sin_zero), 0, 8);

    if (bind(sock, (struct sockaddr *)&server_addr, sizeof(server_addr))
        == -1) {
        perror("Bind");
        close(sock);
        exit(1);
    }

    addr_len = sizeof(struct sockaddr);

    // Open file to write received audio data
    fp = fopen(OUTPUT_FILE, "wb");
    if (fp == NULL) {
        perror("File open");
        close(sock);
        exit(1);
    }

    printf("UDP Server waiting for audio data on port 5000...\n");

    while (1) {
        bytes_read = recvfrom(sock, buffer, BUFFER_SIZE, 0,
                              (struct sockaddr *)&client_addr, &addr_len);

        if (bytes_read == -1) {
            perror("recvfrom");
            break;
        }

        // Check for end of file transfer message ("EOF")
        if (bytes_read == 3 && memcmp(buffer, "EOF", 3) == 0) {
            printf("\nReceived EOF. File transfer complete.\n");
            break;
        }

        // Write received bytes to file
        size_t bytes_written = fwrite(buffer, 1, bytes_read, fp);
        if (bytes_written != bytes_read) {
            perror("fwrite");
            break;
        }

        printf("Received %zd bytes from %s:%d\n", bytes_read,
               inet_ntoa(client_addr.sin_addr), ntohs(client_addr.sin_port));
    }

    fclose(fp);
    close(sock);

    printf("Audio file saved as %s\n", OUTPUT_FILE);

    return 0;
}
