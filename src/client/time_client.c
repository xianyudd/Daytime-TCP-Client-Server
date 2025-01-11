#include "unp.h"
#include <errno.h>

int main(int argc, char **argv) {
    int sockfd,n;
    struct sockaddr_in servaddr;
    char recvline[MAXLINE + 1];
    int ticks = 0;
    
    if (argc != 2) {
        fprintf(stderr, "usage: %s <IPaddress>\n", argv[0]);
        exit(1);
    }
    
    // 创建 TCP 套接字
    sockfd = Socket(AF_INET, SOCK_STREAM, 0);
    if (sockfd < 0) {
        fprintf(stderr, "socket error: %s (errno: %d)\n", 
                strerror(errno), errno);
        exit(1);
    }
    
    // 初始化服务器地址结构
    bzero(&servaddr, sizeof(servaddr));
    servaddr.sin_family = AF_INET;
    servaddr.sin_port = htons(13);  // daytime server
    if (inet_pton(AF_INET, argv[1], &servaddr.sin_addr) <= 0) {
        fprintf(stderr, "inet_pton error for %s\n", argv[1]);
        exit(1);
    }
    
    // 连接到服务器
    if (connect(sockfd, (SA *) &servaddr, sizeof(servaddr)) < 0) {
        fprintf(stderr, "connect error\n");
        exit(1);
    }
    
    // 读取并显示服务器发送的时间
    while ((n = read(sockfd, recvline, MAXLINE)) > 0) {
        recvline[n] = 0;    // null terminate
        ticks=ticks+1;
        if (fputs(recvline, stdout) == EOF) {
            fprintf(stderr, "fputs error\n");
            exit(1);
        }
    }
    printf("计数器的值:%d\n",ticks);
    if (n < 0) {
        fprintf(stderr, "read error\n");
        exit(1);
    }
    
    exit(0);
}
