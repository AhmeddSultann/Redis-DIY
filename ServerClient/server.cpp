//
// Created by Ahmed Sultan on 2025-05-19.
//

#include "server.h"
#include <cstdint>
#include <cstdlib>
#include <cstring>
#include <cstdio>
#include <iterator>
#include <unistd.h>
#include <arpa/inet.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <netinet/ip.h>

#define PORT 1222


using namespace std;

static void die(const char *msg) {
	perror(msg);
	exit(EXIT_FAILURE);
}

static void do_something_with_client(int connfd) {
	char buffer[64] = {};
	ssize_t bytes_read = read(connfd, buffer, sizeof(buffer) - 1);
	if (bytes_read < 0) {
		perror("read() error");
		return;
	}

	printf("client sent: %s\n", buffer);

	char wbuffer[] = "world";
	write(connfd, wbuffer, sizeof(wbuffer));
}

int main() {
	const int fd = socket(AF_INET, SOCK_STREAM, 0);

	const int val = 1;
	setsockopt(fd, SOL_SOCKET, SO_REUSEADDR, &val, sizeof(val));

	// bind: this is the code that deals with the IPv4 address
	struct sockaddr_in addr = {};
	addr.sin_family = AF_INET;
	addr.sin_port = ntohs(PORT);
	addr.sin_addr.s_addr = ntohl(0); // Wildcard address of 0.0.0.0
	int rv = bind(fd, (const sockaddr *) &addr, sizeof(addr));
	if (rv) {
		die("bind()");
	}

	// Listen
	rv = listen(fd, SOMAXCONN);
	if (rv) {
		die("listen()");
	}

	while (true) {
		struct sockaddr_in client_addr = {};
		socklen_t client_addr_len = sizeof(client_addr);
		int connfd = accept(fd, (struct sockaddr *) &client_addr, &client_addr_len);
		if (connfd < 0) {
			die("accept()");
		}

		do_something_with_client(connfd);
		close(connfd);
	}

	return 0;
}

