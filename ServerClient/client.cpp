//
// Created by sultaniko on 5/30/25.
//

#include "client.h"

#include <cstdio>
#include <cstdlib>
#include <unistd.h>
#include <netinet/in.h>
#include <sys/socket.h>

#define PORT 1222

using namespace std;

static void die(const char *msg) {
    perror(msg);
    exit(EXIT_FAILURE);
}

int main() {
    const int fd = socket(AF_INET, SOCK_STREAM, 0);

    const int val = 1;
    setsockopt(fd, SOL_SOCKET, SO_REUSEADDR, &val, sizeof(val));

    // bind: this is the code that deals with the IPv4 address
    struct sockaddr_in addr = {};
    addr.sin_family = AF_INET;
    addr.sin_port = ntohs(PORT);
    addr.sin_addr.s_addr = ntohl(INADDR_LOOPBACK); // Address of 127.0.0.1
    int rv = connect(fd, (const sockaddr *) &addr, sizeof(addr));
    if (rv) {
        die("connect()");
    }

    char msg[] = "hello";
    write(fd, msg, sizeof(msg));

    char rbuf[64] = {};
    ssize_t bytes_read = read(fd, rbuf, sizeof(rbuf) - 1);
    if (bytes_read < 0) {
        die("read error");
    }

    printf("Server replied: %s\n", rbuf);
    close(fd);
    return 0;
}
