// Because we are using POSIX features that aren't part of the C standard, we
// need to #define this macro before #including standard library headers to be
// granted access to POSIX-specific definitions such as struct addrinfo.
#define _GNU_SOURCE

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#include <sys/types.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <netdb.h>

/*
 * Convenient error handler for printing errno-associated message and exit(1).
 */
static void die(char *msg) {
    perror(msg);
    exit(1);
}

int main(int argc, char **argv) {
    /*
     * Check and obtain command-line arguments
     */
    if (argc != 2) {
        fprintf(stderr, "Usage: %s <server-port>\n", argv[0]);
        exit(1);
    }

    char *server_port = argv[1];

    /*
     * Construct socket address information using getaddrinfo().
     */

    // Define hints for getaddrinfo(), which we need to zero out first.
    struct addrinfo hints;

    memset(&hints, 0, sizeof(hints));

    hints.ai_family = AF_INET;        // Only accept IPv4 addresses
    hints.ai_socktype = SOCK_STREAM;  // stream socket for TCP connections
    hints.ai_protocol = IPPROTO_TCP;  // TCP protocol
    hints.ai_flags = AI_PASSIVE;      // Construct socket address for bind()ing

    // Define where getaddrinfo() will return the information it found.
    struct addrinfo *info;

    // Call getaddrinfo(), specifying the server IP address and port as strings.
    // getaddrinfo() will parse those for us and point info to the result.
    int addr_err;
    if ((addr_err = getaddrinfo(NULL, server_port, &hints, &info)) != 0) {
        fprintf(stderr, "getaddrinfo: %s\n", gai_strerror(addr_err));
        exit(1);
    }

    // N.B. info actually points to a linked list of address information
    // structures; assume that the first is sufficient and ignore the rest.

    /*
     * Create socket() and prepare it to accept() connections.
     */

    // Create socket() according to the address family, socket type, and
    // protocol of the address info.  Since we specified AF_INET, SOCK_STREAM,
    // and IPPROTO_TCP in the hints, this should be equivalent to just calling
    // socket(AF_INET, SOCK_STREAM, IPPROTO_TCP).
    int serv_fd = socket(info->ai_family, info->ai_socktype, info->ai_protocol);
    if (serv_fd < 0)
        die("socket");

    // bind() socket to a port on the server; the port in info->ai_addr should
    // be the same port that getaddrinfo() parsed from server_port.
    if (bind(serv_fd, info->ai_addr, info->ai_addrlen) < 0)
        die("bind");

    // BTW: we're done with the info retrieved by getaddrinfo(), so free it.
    freeaddrinfo(info);

    // Start listen()ing for connections on this socket, maintaining a queue of
    // at most 8 pending connections.
    if (listen(serv_fd, 8) < 0)
        die("listen");

    /*
     * Server loop runs forever (writing "for (;;)" is the same as "while(1)")
     */
    for (;;) {

        /*
         * accept() connection from client.
         */

        // Define space to receive client address info.
        struct sockaddr_in clnt_addr;
        socklen_t clnt_addr_len = sizeof(clnt_addr);

        // accept() blocks until a client connects with the server, and returns
        // a NEW socket file descriptor for interacting with the client.
        int clnt_fd = accept(serv_fd, (struct sockaddr *) &clnt_addr,
                             &clnt_addr_len);
        if (clnt_fd < 0)
            die("accept");

        // clnt_addr is now populated with information about the client.
        fprintf(stderr, "Accepted connection from %s\n",
                inet_ntoa(clnt_addr.sin_addr));

        /*
         * Handle client connection.
         */

        // Keep track of how many bytes we've received.
        size_t recv_len = 0;

        int len;
        char buf[32];

        // recv() is like read(), except there's an extra flags argument.
        //
        // Since we didn't pass any flags to recv(), this is equivalent to
        // read(clnt_fd, buf, sizeof(buf)).
        if ((len = recv(clnt_fd, buf, sizeof(buf), 0)) < 0)
            die("recv");

        while (len > 0) {
            // Book-keeping.
            recv_len += len;

            // send() is like write(), except there's an extra flags argument.
            //
            // Since we didn't pass any flags to send(), this is equivalent to
            // write(clnt_fd, buf, len).
            if (send(clnt_fd, buf, len, 0) != len)
                die("send");

            // recv() might not have read everything the client sent, so we need
            // to continue recv()ing.
            if ((len = recv(clnt_fd, buf, sizeof(buf), 0)) < 0)
                die("recv");
        }

        fprintf(stderr, "Received (and sent) %lu bytes in total\n", recv_len);

        // Close client connection.
        close(clnt_fd);

        // Resume server loop to handle next client connection.
    }

    /*
     * UNREACHABLE
     */

    // Theoretically, if we want our server to handle graceful termination, we
    // should also close() the server socket here too:
    close(serv_fd);

    return 0;
}
