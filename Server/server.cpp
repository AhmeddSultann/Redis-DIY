//
// Created by Ahmed Sultan on 2025-05-19.
//

#include "server.h"
#include <cstdint>
#include <cstdlib>
#include <cstring>
#include <cstdio>
#include <cerrno>
#include <unistd.h>
#include <arpa/inet.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <netinet/ip.h>

using namespace std;

static void die(const char *msg) {

}

int main() {
	int fd = socket(AF_INET, SOCK_STREAM, 0);

	int val = 1;
	setsocketopt(fd, SOL_SOCKET, SO_REUSEADDR, &val, sizeof(val));

	// bind: this is the code that deals with the IPv4 address
	struct sockaddr_in addr = {};
	addr.sin_family = AF_NET;
	addr.sin_port = ntohs(1234);
	addr.sin_addr.s_addr = ntohl(0); // Wildcard address of 0.0.0.0
	int rv = bind(fd, (const sockaddr *) &addr, sizeof(addr));
	if (rv) {
		die("bind()");
	}

	// Listen
	int rv = listen(fd, SOMAXCONN);
	if (rv) {
		die("listen")
	}
}

