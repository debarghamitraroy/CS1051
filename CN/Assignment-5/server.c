// server.c
// Usage: ./server

#include <arpa/inet.h>
#include <dirent.h>
#include <netinet/in.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <unistd.h>

#define PAYLOAD_SIZE 1024 // Maximum payload size would be 65480
#define PORT 8080

/* Defination of Packet */
typedef struct Packet {
    int file_id;
    int seq;
    int pkt_type; // 0: filename, 1: content, 2: EOF
    size_t data_len; // last chunk size
    char data[PAYLOAD_SIZE];
} Packet;

/* Defination of Acknowledgement */
typedef struct Ack {
    int seq;
} Ack;

/* Create and store server log messages */
void server_log() {
    const char *serverLog = "server_log.log";
    // Try to open (or create) server log file
    FILE *serverFile = fopen(serverLog, "w");
    if (serverFile == NULL) {
        perror("Error creating/opening server log file");
        return;
    } else
        fprintf(serverFile, "Server log file is ready: %s\n", serverLog);
    // Server starting message
    fprintf(serverFile, "Server is started successfully.\n");
    // Close the server log file
    fflush(serverFile);
    fclose(serverFile);
}

int transfer(int sockfd, Packet pkt, struct sockaddr_in cliaddr, socklen_t addr_len, int seq, size_t bytesRead) {
    // Try to open (or create) server log file
    const char *serverLog = "server_log.log";
    FILE *serverFile = fopen(serverLog, "a");

    int acked = 0;
    while (!acked) {
        // Send packet
        ssize_t sent = sendto(sockfd, &pkt, sizeof(pkt), 0, (struct sockaddr *)&cliaddr, addr_len);
        if (sent < 0) {
            perror("sendto failed");
            // fprintf(serverFile, "sendto failed");
            exit(1);
        }
        printf("Sent packet seq=%d (%zu bytes)\n", pkt.seq, bytesRead);
        // fprintf(serverFile, "Sent packet seq=%d (%zu bytes)\n", pkt.seq, bytesRead);

        // Wait for ACK
        Ack ack;
        ssize_t n = recvfrom(sockfd, &ack, sizeof(ack), 0, (struct sockaddr *)&cliaddr, &addr_len);

        // timeout -> retransmit
        if (n < 0) {
            printf("Timeout waiting for ACK. Retransmitting seq=%d...\n", pkt.seq);
            // fprintf(serverFile, "Timeout waiting for ACK. Retransmitting seq=%d...\n", pkt.seq);
        } else if (ack.seq == pkt.seq) {
            printf("Received ACK for seq=%d\n", ack.seq);
            // fprintf(serverFile, "Received ACK for seq=%d\n", ack.seq);
            acked = 1; // success
            seq ^= 1; // toggle 0 <-> 1
        }
    }
    return seq;

    // Close the server log file
    fflush(serverFile);
    fclose(serverFile);
}

void transfer_file(int sockfd, struct sockaddr_in cliaddr, socklen_t addr_len, char path[256], char *filename, int file_id) {
    // Open server log file
    const char *serverLog = "server_log.log";
    FILE *serverFile = fopen(serverLog, "a");

    int seq = 0;

    // Send filename
    Packet fname_pkt;
    fname_pkt.pkt_type = 0;
    fname_pkt.file_id = file_id; // file_id=1 for simplicity
    fname_pkt.seq = seq; // initial sequence
    fname_pkt.data_len = strlen(filename) + 1; // include null terminator
    memcpy(fname_pkt.data, filename, fname_pkt.data_len);
    seq = transfer(sockfd, fname_pkt, cliaddr, addr_len, seq, fname_pkt.data_len);
    printf("\n name done\n");
    // fprintf(serverFile, "\n name done\n");

    // Send file content
    FILE *file = fopen(path, "rb");
    if (!file) {
        perror("Error opening file");
        // fprintf(serverFile, "Error opening file\n");
        exit(1);
    }

    // Set timeout for ACKs
    struct timeval tv;
    tv.tv_sec = 2; // 2 sec timeout
    tv.tv_usec = 0;
    if (setsockopt(sockfd, SOL_SOCKET, SO_RCVTIMEO, &tv, sizeof(tv)) < 0) {
        perror("Error setting timeout");
        // fprintf(serverFile, "Error setting timeout\n");
        exit(1);
    }

    // Send file in packets
    size_t bytesRead;
    char buffer[PAYLOAD_SIZE];

    while ((bytesRead = fread(buffer, 1, PAYLOAD_SIZE, file)) > 0) {
        Packet pkt;
        pkt.pkt_type = 1;
        pkt.file_id = file_id;
        pkt.seq = seq;
        pkt.data_len = bytesRead;
        memcpy(pkt.data, buffer, bytesRead);
        printf("\n content transferring...\n");
        // fprintf(serverFile, "\n content transferring...\n");
        seq = transfer(sockfd, pkt, cliaddr, addr_len, seq, bytesRead);
    }
    printf("Content transferring done\n");
    // fprintf(serverFile, "Content transferring done\n");

    // send EOF signal
    Packet eof_pkt;
    eof_pkt.pkt_type = 2;
    eof_pkt.file_id = 1; // same file_id
    eof_pkt.seq = seq; // current sequence number
    eof_pkt.data_len = 0;
    seq = transfer(sockfd, eof_pkt, cliaddr, addr_len, seq, 0);
    printf("File transfer complete.\n");
    // fprintf(serverFile, "File transfer complete.\n");

    fclose(file);
    fflush(serverFile);
    fclose(serverFile);
}

int main() {
    // Create/open server log file
    server_log();
    const char *serverLog = "server_log.log";
    FILE *serverFile = fopen(serverLog, "a");

    struct sockaddr_in servaddr, cliaddr;
    socklen_t addr_len = sizeof(cliaddr);

    int sockfd = socket(AF_INET, SOCK_DGRAM, 0);
    if (sockfd < 0) {
        perror("socket creation failed");
        // fprintf(serverFile, "socket creation failed\n");
        exit(1);
    }

    servaddr.sin_family = AF_INET;
    servaddr.sin_addr.s_addr = INADDR_ANY;
    servaddr.sin_port = htons(PORT);

    int opt = 1;
    if (setsockopt(sockfd, SOL_SOCKET, SO_REUSEADDR, &opt, sizeof(opt)) < 0) {
        perror("setsockopt failed");
        // fprintf(serverFile, "setsockopt failed\n");
    }

    if (bind(sockfd, (struct sockaddr *)&servaddr, sizeof(servaddr)) < 0) {
        perror("bind failed");
        // fprintf(serverFile, "bind failed\n");
        exit(1);
    }

    printf("Server listening on port %d...\n", PORT);
    fprintf(serverFile, "Server listening on port %d...\n", PORT);

    // Receive file request from client
    char foldername[256];
    ssize_t n = recvfrom(sockfd, foldername, sizeof(foldername), 0, (struct sockaddr *)&cliaddr, &addr_len);
    if (n < 0) {
        perror("recvfrom failed");
        fprintf(serverFile, "recvfrom failed\n");
        exit(1);
    }
    foldername[n] = '\0';
    printf("Client requested folder: %s\n", foldername);
    fprintf(serverFile, "Client requested folder: %s\n", foldername);

    char *path = ".";
    char folderpath[512];
    snprintf(folderpath, sizeof(folderpath), "%s/%s", path, foldername);
    printf("\n%s\n", folderpath);
    fprintf(serverFile, "%s\n", folderpath);
    DIR *dr = opendir(folderpath);
    if (!dr) {
        perror("opendir");
        fprintf(serverFile, "opendir\n");
        exit(1);
    }

    struct dirent *de;
    int file_id = 1;

    while ((de = readdir(dr)) != NULL) {
        if (de->d_type != DT_REG)
            continue; // skip directories
        // char fullpath[512];
        size_t fullpath_len = strlen(folderpath) + strlen(de->d_name) + 2;
        char *fullpath = malloc(fullpath_len);
        if (!fullpath) {
            perror("malloc failed");
            fprintf(serverFile, "malloc failed\n");
            exit(1);
        }
        snprintf(fullpath, fullpath_len, "%s/%s", folderpath, de->d_name);
        printf("\n%s", fullpath);
        fprintf(serverFile, "\n%s\n", fullpath);
        char *filename = de->d_name;
        transfer_file(sockfd, cliaddr, addr_len, fullpath, filename, file_id);
        ++file_id;
    }
    close(sockfd);

    /* Close the server socket */
    printf("Server socket terminated\n");
    fprintf(serverFile, "Server socket terminated\n");

    // Close the client log file
    fflush(serverFile);
    fclose(serverFile);
    return 0;
}