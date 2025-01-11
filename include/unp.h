/* unp.h - Unix Network Programming Header */
#ifndef __UNP_H
#define __UNP_H

/* Standard system includes */
#include <sys/types.h>      /* basic system data types */
#include <sys/socket.h>     /* basic socket definitions */
#include <sys/time.h>       /* timeval{} for select() */
#include <time.h>           /* timespec{} for pselect() */
#include <netinet/in.h>     /* sockaddr_in{} and other Internet defns */
#include <arpa/inet.h>      /* inet(3) functions */
#include <errno.h>          /* error definitions and errno */
#include <fcntl.h>          /* for nonblocking */
#include <netdb.h>          /* for getaddrinfo() */
#include <signal.h>         /* for signal handling */
#include <stdio.h>          /* for standard I/O */
#include <stdlib.h>         /* for various utilities */
#include <string.h>         /* for string handling */
#include <sys/stat.h>       /* for S_xxx file mode constants */
#include <sys/uio.h>        /* for iovec{} and readv/writev */
#include <unistd.h>         /* for various utilities */
#include <sys/wait.h>       /* for waitpid() */
#include <sys/un.h>         /* for Unix domain sockets */

/* Following shortens all the type casts of pointer arguments */
#define SA struct sockaddr

/* Maximum size of a fully-qualified domain name */
#define MAXLINE     4096    /* max text line length */
#define MAXSOCKADDR  128    /* max socket address structure size */
#define BUFFSIZE    8192    /* buffer size for reads and writes */
#define LISTENQ     1024    /* 2nd argument to listen() */

/* Wrapper functions to handle errors */
int Socket(int family, int type, int protocol) {
    int n;
    if ((n = socket(family, type, protocol)) < 0) {
        perror("socket error");
        exit(1);
    }
    return(n);
}

void Bind(int fd, const struct sockaddr *sa, socklen_t salen) {
    if (bind(fd, sa, salen) < 0) {
        perror("bind error");
        exit(1);
    }
}

void Listen(int fd, int backlog) {
    if (listen(fd, backlog) < 0) {
        perror("listen error");
        exit(1);
    }
}

int Accept(int fd, struct sockaddr *sa, socklen_t *salenptr) {
    int n;
    if ((n = accept(fd, sa, salenptr)) < 0) {
        perror("accept error");
        exit(1);
    }
    return(n);
}

void Write(int fd, void *ptr, size_t nbytes) {
     ssize_t n;
     if ((n = write(fd, ptr, nbytes)) != (ssize_t)nbytes){
	perror("write error");
        exit(1);
    }
}

void Close(int fd) {
    if (close(fd) == -1) {
        perror("close error");
        exit(1);
    }
}

/* Utility functions */
void bzero(void *ptr, size_t n) {
    memset(ptr, 0, n);
}

#endif  /* __UNP_H */
