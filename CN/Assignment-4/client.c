#include <arpa/inet.h>
#include <dirent.h>
#include <netinet/in.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <unistd.h>

#define PAYLOAD_SIZE 1024 // Maximum payload size: 65480
#define PORT 8080
#define MAX_FILES 1000
#define MAX_NAME_LEN 256

typedef struct Packet {
    int file_id;
    int seq;
    int pkt_type;
    size_t data_len;
    char data[PAYLOAD_SIZE];
} Packet;

typedef struct Ack {
    int seq;
} Ack;

int file_exists_in_list(char files[][MAX_NAME_LEN], int count, const char *name) {
    for (int i = 0; i < count; i++) {
        if (strcmp(files[i], name) == 0)
            return 1;
    }
    return 0;
}

int read_directory_files(const char *path, char files[][MAX_NAME_LEN]) {
    DIR *dir;
    struct dirent *entry;
    int count = 0;
    dir = opendir(path);
    if (dir == NULL) {
        perror("Unable to open directory");
        return -1;
    }
    while ((entry = readdir(dir)) != NULL) {
        if (strcmp(entry->d_name, ".") == 0 || strcmp(entry->d_name, "..") == 0)
            continue;
        strncpy(files[count++], entry->d_name, MAX_NAME_LEN);
        if (count >= MAX_FILES)
            break;
    }
    closedir(dir);
    return count;
}

void client_log() {
    const char *clientLog = "client_log.log";
    FILE *clientFile = fopen(clientLog, "w");
    if (clientFile == NULL) {
        perror("Error creating/opening client log file");
        return;
    } else
        fprintf(clientFile, "Client log is file ready: %s\n", clientLog);
    fprintf(clientFile, "Client is connected.\n");
    fflush(clientFile);
    fclose(clientFile);
}

int main() {
    client_log();
    const char *clientLog = "client_log.log";
    FILE *clientFile = fopen(clientLog, "a");
    char folder1[256], folder2[256];
    char files1[MAX_FILES][MAX_NAME_LEN], files2[MAX_FILES][MAX_NAME_LEN];
    printf("Enter path of folder-1: ");
    scanf("%255s", folder1);
    printf("Enter path of folder-2: ");
    scanf("%255s", folder2);
    int count1 = read_directory_files(folder1, files1);
    int count2 = read_directory_files(folder2, files2);
    if (count1 < 0 || count2 < 0) {
        fclose(clientFile);
        return 1;
    }
    fprintf(clientFile, "\nFiles in %s but not in %s:\n", folder1, folder2);
    for (int i = 0; i < count1; i++) {
        if (!file_exists_in_list(files2, count2, files1[i]))
            fprintf(clientFile, "%s\n", files1[i]);
    }
    fprintf(clientFile, "\nFiles in %s but not in %s:\n", folder2, folder1);
    for (int i = 0; i < count2; i++) {
        if (!file_exists_in_list(files1, count1, files2[i])) {
            fprintf(clientFile, "%s\n", files2[i]);
        }
    }
    printf("\nComparison complete! Results saved in %s\n\n", clientLog);
    fprintf(clientFile, "Comparison complete! Results saved in %s\n", clientLog);
    DIR *dir1, *dir2;
    dir1 = opendir(folder1);
    dir2 = opendir(folder2);
    int sockfd = socket(AF_INET, SOCK_DGRAM, 0);
    struct sockaddr_in servaddr;
    socklen_t len = sizeof(servaddr);
    if (sockfd < 0) {
        perror("socket");
        return 1;
    }
    memset(&servaddr, 0, sizeof(servaddr));
    servaddr.sin_family = AF_INET;
    servaddr.sin_port = htons(PORT);
    servaddr.sin_addr.s_addr = inet_addr("127.0.0.1");
    struct timeval tv = {10, 0};
    setsockopt(sockfd, SOL_SOCKET, SO_RCVTIMEO, &tv, sizeof(tv));
    char request_folder[256];
    printf("Enter filename/folder to request: ");
    scanf("%255s", request_folder);
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
        Ack ack = {pkt.seq};
        sendto(sockfd, &ack, sizeof(ack), 0, (struct sockaddr *)&servaddr, len);
        if (pkt.seq == expected_seq) {
            if (pkt.pkt_type == 0) {
                size_t outpath_len;
                if (strcmp(request_folder, "folder1") == 0)
                    outpath_len = strlen("./folder1/") + strlen(pkt.data) + 1;
                else
                    outpath_len = strlen("./folder2/") + strlen(pkt.data) + 1;
                char *outpath = malloc(outpath_len);
                if (!outpath) {
                    perror("malloc failed");
                    fprintf(clientFile, "malloc failed\n");
                    break;
                }
                if (strcmp(request_folder, "folder1") == 0)
                    snprintf(outpath, outpath_len, "./folder2/%s", pkt.data);
                else
                    snprintf(outpath, outpath_len, "./folder1/%s", pkt.data);
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
            } else if (pkt.pkt_type == 1) {
                if (outFile && pkt.data_len > 0) {
                    fwrite(pkt.data, 1, pkt.data_len, outFile);
                    printf("Received packet seq=%d (%zu bytes)\n", pkt.seq, pkt.data_len);
                    fprintf(clientFile, "Received packet seq=%d (%zu bytes)\n", pkt.seq, pkt.data_len);
                }
            } else if (pkt.pkt_type == 2) {
                if (outFile) {
                    fclose(outFile);
                    outFile = NULL;
                    printf("\nFile transfer complete.\n");
                    fprintf(clientFile, "\nFile transfer complete.\n");
                }
                expected_seq = 0;
                continue;
            }
            expected_seq ^= 1;
        } else {
            printf("Duplicate packet %d ignored\n", pkt.seq);
            fprintf(clientFile, "Duplicate packet %d ignored\n", pkt.seq);
        }
    }
    if (outFile)
        fclose(outFile);
    close(sockfd);
    closedir(dir1);
    closedir(dir2);
    printf("Server socket terminated\n");
    fprintf(clientFile, "Server socket terminated\n");
    fflush(clientFile);
    fclose(clientFile);
    return 0;
}