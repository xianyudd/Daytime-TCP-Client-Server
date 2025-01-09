#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <sys/socket.h>
#include <errno.h>
#include <sys/time.h>
#include <fcntl.h>

#define BUF_SIZE 1024
#define PORT 13
#define SERVER_IP "127.0.0.1"

void error(const char *msg) {
    perror(msg);
    exit(1);
}

int main() {
    int sockfd;
    struct sockaddr_in serv_addr;
    char buffer[BUF_SIZE];
    struct timeval tv;

    printf("Creating socket...\n");
    sockfd = socket(AF_INET, SOCK_STREAM, 0);
    if (sockfd < 0) 
        error("ERROR opening socket");

    printf("Setting up server address...\n");
    memset(&serv_addr, 0, sizeof(serv_addr));
    serv_addr.sin_family = AF_INET;
    serv_addr.sin_port = htons(PORT);
    if (inet_pton(AF_INET, SERVER_IP, &serv_addr.sin_addr) <= 0)
        error("ERROR invalid address");

    printf("Connecting to server...\n");
    if (connect(sockfd, (struct sockaddr *)&serv_addr, sizeof(serv_addr)) < 0) 
        error("ERROR connecting");

    printf("Connection established. Reading from server...\n");

    int total_bytes = 0;
    int n;
    while ((n = read(sockfd, buffer + total_bytes, BUF_SIZE - 1 - total_bytes)) > 0) {
        total_bytes += n;
        printf("Received %d bytes\n", n);
    }

    if (n < 0) {
        if (errno == ECONNRESET) {
            printf("Server closed connection after sending data.\n");
        } else {
            error("ERROR reading from socket");
        }
    }

    if (total_bytes > 0) {
        buffer[total_bytes] = '\0';
        printf("Time from server: %s", buffer);
    } else {
        printf("No data received from server.\n");
    }

    printf("Closing socket...\n");
    close(sockfd);
    return 0;
}
