/* client.c */

#include <arpa/inet.h>
#include <netdb.h>
#include <netinet/in.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <unistd.h>

#define CHUNK_SIZE 1024 // UDP safe size per datagram
#define AUDIO_FILE "audio.wav" // Change to your audio file

int main() {
    int sock;
    struct sockaddr_in server_addr;
    struct hostent *host;
    FILE *audio_file;
    char buffer[CHUNK_SIZE];
    size_t bytes_read;

    // Resolve host
    if ((host = gethostbyname("127.0.0.1")) == NULL) {
        perror("gethostbyname");
        exit(1);
    }

    // Create UDP socket
    if ((sock = socket(AF_INET, SOCK_DGRAM, 0)) == -1) {
        perror("socket");
        exit(1);
    }

    // Set up server address
    server_addr.sin_family = AF_INET;
    server_addr.sin_port = htons(5000);
    server_addr.sin_addr = *((struct in_addr *)host->h_addr);
    memset(&(server_addr.sin_zero), 0, 8);

    // Open the audio file
    audio_file = fopen(AUDIO_FILE, "rb");
    if (audio_file == NULL) {
        perror("fopen");
        close(sock);
        exit(1);
    }

    // Read and send file in chunks
    while ((bytes_read = fread(buffer, 1, CHUNK_SIZE, audio_file)) > 0) {
        if (sendto(sock, buffer, bytes_read, 0, (struct sockaddr *)&server_addr,
                   sizeof(server_addr))
            == -1) {
            perror("sendto");
            break;
        }
    }

    // Send a special "EOF" message to indicate end of transmission
    const char *eof_msg = "EOF";
    sendto(sock, eof_msg, strlen(eof_msg), 0, (struct sockaddr *)&server_addr,
           sizeof(server_addr));

    printf("Audio file sent.\n");

    // Cleanup
    fclose(audio_file);
    close(sock);

    return 0;
}
