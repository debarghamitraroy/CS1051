// client.c
// Usage: ./client

#include <arpa/inet.h>
#include <netinet/in.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <unistd.h>

#define PAYLOAD_SIZE 1024 // Maximum payload size would be 65480
#define PORT 8080

/* Defination of Packet */
typedef struct Packet {
    int file_id;
    int seq;
    int pkt_type; // 0 = FileName, 1 = Content, 2 = EOF
    size_t data_len; // last chunk size
    char data[PAYLOAD_SIZE];
} Packet;

/* Defination of Acknowledgement */
typedef struct Ack {
    int seq;
} Ack;

/* Create and store client log messages */
void client_log() {
    const char *clientLog = "client_log.log";
    // Try to open (or create) client log file
    FILE *clientFile = fopen(clientLog, "a");
    if (clientFile == NULL) {
        perror("Error creating/opening client log file");
        return;
    } else
        fprintf(clientFile, "Client log is file ready: %s\n", clientLog);
    fprintf(clientFile, "Client is connected.\n");
    // Close the client log file
    fflush(clientFile);
    fclose(clientFile);
}

/* Create received data folder */
void create_folder() {
    const char *clientLog = "client_log.log";
    // Open client log file
    FILE *clientFile = fopen(clientLog, "a");
    const char *folderName = "received_data";
    struct stat st = {0};
    // Check if the folder exists
    if (stat(folderName, &st) == -1) {
        // Folder does not exist, create it
        if (mkdir(folderName, 0700) == 0) {
            fprintf(clientFile, "Folder '%s' created successfully.\n", folderName);
        } else {
            perror("Error creating folder");
            fprintf(clientFile, "Error creating folder");
        }
    } else
        fprintf(clientFile, "Folder '%s' already exists.\n", folderName);
    // Close the client log file
    fflush(clientFile);
    fclose(clientFile);
}

int main() {
    // Create/open client log file
    client_log();
    const char *clientLog = "client_log.log";
    FILE *clientFile = fopen(clientLog, "a");

    create_folder();

    int sockfd;
    struct sockaddr_in servaddr;
    socklen_t len = sizeof(servaddr);

    sockfd = socket(AF_INET, SOCK_DGRAM, 0);
    if (sockfd < 0) {
        perror("socket");
        return 1;
    }

    memset(&servaddr, 0, sizeof(servaddr));
    servaddr.sin_family = AF_INET;
    servaddr.sin_port = htons(PORT);
    servaddr.sin_addr.s_addr = inet_addr("127.0.0.1");

    // Receive Timeout
    struct timeval tv = {10, 0}; // 10 sec
    setsockopt(sockfd, SOL_SOCKET, SO_RCVTIMEO, &tv, sizeof(tv));

    char request_folder[256];
    printf("Enter filename/folder to request: ");
    scanf("%255s", request_folder);

    // Send filename/folder request to server
    sendto(sockfd, request_folder, strlen(request_folder) + 1, 0, (struct sockaddr *)&servaddr, len);

    FILE *outFile = NULL;
    Packet pkt;
    int expected_seq = 0;

    while (1) {
        ssize_t n = recvfrom(sockfd, &pkt, sizeof(pkt), 0, (struct sockaddr *)&servaddr, &len);
        if (n <= 0) {
            fprintf(clientFile, "No more packets received or timeout.\n");
            break;
        }

        // Always ACK
        Ack ack = {pkt.seq};
        sendto(sockfd, &ack, sizeof(ack), 0, (struct sockaddr *)&servaddr, len);

        // Handle packet based on type
        if (pkt.seq == expected_seq) {
            // filename packet
            if (pkt.pkt_type == 0) {
                size_t outpath_len = strlen("./received_data/") + strlen(pkt.data) + 1;
                char *outpath = malloc(outpath_len);
                if (!outpath) {
                    perror("malloc failed");
                    fprintf(clientFile, "malloc failed\n");
                    break;
                }
                snprintf(outpath, outpath_len, "./received_data/%s", pkt.data);
                outFile = fopen(outpath, "wb");
                if (!outFile) {
                    perror("Failed to open output file");
                    fprintf(clientFile, "Failed to open output file\n");
                    free(outpath);
                    break;
                }
                printf("Receiving file: %s\n", pkt.data);
                fprintf(clientFile, "Receiving file: %s\n", pkt.data);
                free(outpath);
            }
            // content packet
            else if (pkt.pkt_type == 1) {
                if (outFile && pkt.data_len > 0) {
                    fwrite(pkt.data, 1, pkt.data_len, outFile);
                    printf("Received packet seq=%d (%zu bytes)\n", pkt.seq, pkt.data_len);
                    fprintf(clientFile, "Received packet seq=%d (%zu bytes)\n", pkt.seq, pkt.data_len);
                }
            }
            // EOF packet
            else if (pkt.pkt_type == 2) {
                if (outFile) {
                    fclose(outFile);
                    outFile = NULL;
                    printf("File transfer complete.\n");
                    fprintf(clientFile, "File transfer complete.\n");
                }
                expected_seq = 0;
                continue;
            }
            expected_seq ^= 1; // toggle sequence
        } else {
            printf("Duplicate packet %d ignored\n", pkt.seq);
            fprintf(clientFile, "Duplicate packet %d ignored\n", pkt.seq);
        }
    }

    if (outFile)
        fclose(outFile);
    close(sockfd);

    // Close the client log file
    fflush(clientFile);
    fclose(clientFile);
    return 0;
}