/* client.c */

#include <arpa/inet.h>
#include <math.h>
#include <netinet/in.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/select.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <time.h>

#define data_per_packet 1024

/* File Handling */
// fread(msg, 1, file_len, fl);
// fwrite(msg, 1, file_len, fl);
// fopen(file_name, mode);

/* Declaring file transfer parameters */
long file_len; // file size
int buffer_size = data_per_packet; // data per packet

/* Frame structure */
typedef struct frame {
    int frame_kind; // 0: sequence or data frame, 1: termination connection, 2: calibration
    int seq_no; // sequence number
    int ack; // acknowledgement number
    int buffer_size;
    char data[data_per_packet]; // given only 1KB of data can be transferred per frame
    char file_name[250]; // file name
    int size_in_bytes; // message length (file size in byte)
} Frame;

int main() {
    /* Structures and datatypes used in select() */
    fd_set rset; // set of sockets structure to be monitor via select()
    struct timeval tv; // used for specifying the timeout period in the select() call;
    FD_ZERO(&rset); // setting the set of sockets to 0
    FD_SET(client_socket, &rset); // putting out socket into the set to be monitored by select()

    /* Creating a socket */
    int client_socket = socket(AF_INET, SOCK_DGRAM, 0);

    struct sockaddr _in server_address;
    server_address.sin_family = AF_INET;
    server_address.sin_port = htons(5000);
    server_address.sin_addr.s_addr = IN_ADDR_ANY;

    char file_name[250];
    printf("Enter file name to send: ");
    gets(file_name);

    FILE *fl = fopen(file_name, "rb"); // read binary
    fseek(fl, 0, SEEK_END); // file pointer goes to the end of the file
    file_len = ftell(f1); // ftell() returns the current address of the file pointer
    fseek(f1, 0, SEEK_SET); // file pointer goes to the very beginning
    printf("File size (in bytes): %ld\n", file_len);

    /* Number of frame calculation */
    float temp = (float)file_len / (float)buffer_size;
    int frame_count = ceil(temp) + 1;
    int frame_count_org = frame_count;
    printf("No. of frames: %d\n", frame_count);

    /* Initializing the frame, ack and log control variables */
    int frame_no = 0;
    Frame frame_send
}