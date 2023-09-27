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
    if (argc != 4) {
        fprintf(stderr, "Usage: %s <echo-word> <server-addr> <server-port>\n",
                argv[0]);
        exit(1);
    }

    char *echo_word = argv[1];
    char *server_ip = argv[2];
    char *server_port = argv[3];

    /*
     * Obtain server address information using getaddrinfo().
     */

    // Define hints for getaddrinfo(), which we need to zero out first.
    struct addrinfo hints;
    memset(&hints, 0, sizeof(hints));

    // Specify what kind of connection we intend to make; these values tell
    // getaddrinfo() that we don't care about other kinds of addresses.
    hints.ai_family = AF_INET;        // Only accept IPv4 addresses
    hints.ai_socktype = SOCK_STREAM;  // stream socket for TCP connections
    hints.ai_protocol = IPPROTO_TCP;  // TCP protocol

    // Define where getaddrinfo() will return the information it found.
    struct addrinfo *info;

    // Call getaddrinfo(), specifying the server IP address and port as strings.
    // getaddrinfo() will parse those for us and point info to the result.
    int addr_err;
    if ((addr_err = getaddrinfo(server_ip, server_port, &hints, &info)) != 0) {
        fprintf(stderr, "getaddrinfo: %s\n", gai_strerror(addr_err));
        exit(1);
    }

    // N.B. info actually points to a linked list of address information
    // structures, to support hostnames that resolve to multiple addresses.
    // We will assume that the first address is sufficient and ignore the rest.

    /*
     * Create socket() and connect() it to server.
     */

    // Create socket() according to the address family, socket type, and
    // protocol of the address info.  Since we specified AF_INET, SOCK_STREAM,
    // and IPPROTO_TCP in the hints, this should be equivalent to just calling
    // socket(AF_INET, SOCK_STREAM, IPPROTO_TCP).
    int serv_fd = socket(info->ai_family, info->ai_socktype, info->ai_protocol);
    if (serv_fd < 0)
        die("socket");

    // Connect socket with server address; the IP address and port in
    // info->ai_addr should be the same address and port that getaddrinfo()
    // parsed from server_address and server_port.
    if (connect(serv_fd, info->ai_addr, info->ai_addrlen) < 0)
        die("connect");

    // BTW: we're done with the info retrieved by getaddrinfo(), so free it.
    freeaddrinfo(info);

    /*
     * send() echo_word string to server.
     */

    size_t send_len = strlen(echo_word);

    // send() is like write(), except there's an extra flags argument.
    //
    // Since we didn't pass any flags to send(), this is equivalent to
    // write(serv_fd, echo_word, send_len).
    if (send(serv_fd, echo_word, send_len, 0) != send_len)
        die("send");

    /*
     * recv() response from server, and print everything received.
     */

    // Keep track of bytes received.
    size_t recv_len = 0;

    // Don't stop until we receive everything we sent.
    while (recv_len < send_len) {
        int len;
        char buf[32];

        // recv() is like read(), except there's an extra flags argument.
        //
        // Since we didn't pass any flags to recv(), this is equivalent to
        // read(serv_fd, echo_word, send_len).
        if ((len = recv(serv_fd, buf, sizeof(buf) - 1, 0)) <= 0)
            die("recv");

        // Null-terminate the bytes received.
        buf[len] = '\0';

        // Print out the bytes received.
        fputs(buf, stdout);

        // Book-keeping.
        recv_len += len;
    }
    // Add newline after what we printed.
    fputs("\n", stdout);

    /*
     * Clean up and exit.
     */

    fprintf(stderr, "Sent (and received) %lu bytes in total\n", recv_len);

    // close() socket (and sever our connection to the server).
    close(serv_fd);

    return 0;
}
