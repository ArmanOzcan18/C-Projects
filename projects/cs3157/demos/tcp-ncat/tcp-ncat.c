#define _GNU_SOURCE

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#include <sys/types.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <netdb.h>

static void die(char *msg) {
    perror(msg);
    exit(1);
}

static void handle_client_ncat(int clnt_fd) {
    // Construct a FILE pointer for reading from the client,
    // using clnt_fd as the underlying file descriptor.
    FILE *fpr = fdopen(clnt_fd, "r");
    if (fpr == NULL)
        die("fdopen (for reading)");

    // Construct a separate FILE pointer for writing to the client;
    // we dup(clnt_fd) to make sure this FILE stream uses a different
    // underlying file desciptor (referring to the same socket).
    FILE *fpw = fdopen(dup(clnt_fd), "a");
    if (fpw == NULL)
        die("fdopen (for writing)");

    // FILE pointers are block-buffered by default;
    // configure fpw to be line-buffered.
    setlinebuf(fpw);

    char buf[128];
    int lineno = 0;

    // Read in one line at a time.
    while (fgets(buf, sizeof(buf), fpr) != NULL) {
        // Send back line with line number to the client.
        fprintf(fpw, "[%4d]", ++lineno);
        fputs(buf, fpw);

        // Read and send back the rest of the line, if any.
        while (buf[strlen(buf) - 1] != '\n' &&
                fgets(buf, sizeof(buf), fpr) != NULL)
            fputs(buf, fpw);

        // We would need to fflush() each line if fpw weren't line-buffered.
        // fflush(fpw);
    }

    // fclose() both FILE pointers; doing so also will also close() each
    // underlying file descriptor.
    fclose(fpw);
    fclose(fpr);

    // No need to close() clnt_fd (or its dup()); fclose() did that for us.

    fprintf(stderr, "Finished handling client, sent %d lines.\n", lineno);
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

    struct addrinfo hints;

    memset(&hints, 0, sizeof(hints));

    hints.ai_family = AF_INET;
    hints.ai_socktype = SOCK_STREAM;
    hints.ai_protocol = IPPROTO_TCP;
    hints.ai_flags = AI_PASSIVE;

    struct addrinfo *info;

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

    int serv_fd = socket(info->ai_family, info->ai_socktype, info->ai_protocol);
    if (serv_fd < 0)
        die("socket");

    if (bind(serv_fd, info->ai_addr, info->ai_addrlen) < 0)
        die("bind");

    freeaddrinfo(info);

    if (listen(serv_fd, 8) < 0)
        die("listen");

    /*
     * Server loop runs forever.
     */
    for (;;) {

        /*
         * accept() connection from client.
         */

        struct sockaddr_in clnt_addr;
        socklen_t clnt_addr_len = sizeof(clnt_addr);

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

        handle_client_ncat(clnt_fd);
    }

    /*
     * UNREACHABLE
     */

    return 0;
}
