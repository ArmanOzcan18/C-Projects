#define _GNU_SOURCE
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>
#include <unistd.h>
#include <signal.h>
#include <netdb.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <arpa/inet.h>

#define MAX_FILENAME_LEN 4094

/** Use perror() to print error message (obtaining reason errno) and exit(). */
static void die(const char *s) {
    perror(s);
    exit(1);
}

/** Variadic macro for reporting formatted errors and exit()ing with error.
 *
 *  Does not use perror()/check errno.
 */
#define err(...) do { \
        fprintf(stderr, "Error: "); \
        fprintf(stderr, __VA_ARGS__); \
        fprintf(stderr, "\n"); \
        exit(1); \
    } while (0)

int main(int argc, char **argv) {

    /*
     * Obtain command-line arguments and make sure filebase isn't too long.
     */

    if (argc != 3)
        err("usage: %s <server-port> <filebase>\n", argv[0]);


    const char *port = argv[1];
    const char *filebase = argv[2];

    if (strlen(filebase) + 100 > MAX_FILENAME_LEN)
        err("filebase is too long: %s", filebase);


    /*
     * Construct server socket to listen for connections from.
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
    if ((addr_err = getaddrinfo(NULL, port, &hints, &info)) != 0) {
        fprintf(stderr, "getaddrinfo: %s\n", gai_strerror(addr_err));
        exit(1);
    }

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
     * Accept and handle connections.
     */

    unsigned int filesuffix = 0;

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
        fprintf(stderr, "client ip: %s\n", inet_ntoa(clnt_addr.sin_addr));

        FILE *clnt_fpr = fdopen(clnt_fd, "rb");
        FILE *clnt_fpw = fdopen(dup(clnt_fd), "wb");

        // Time to handle client connection.


        /*
         * Open new file to write to, deriving file name from file base.
         */

        char filename[MAX_FILENAME_LEN + 2];

        snprintf(filename, sizeof(filename), "%s.%u", filebase, filesuffix++);
        if (strlen(filename) > MAX_FILENAME_LEN)
            err("file name is too long: %s", filename);

        fprintf(stderr, "file name: %s\n", filename);

        FILE *fp = fopen(filename, "wb");
        if (fp == NULL)
            die(filename);


        /*
         * First, receive file size.
         */

        uint32_t size, size_net;
        if (fread(&size_net, sizeof(size_net), 1, clnt_fpr) < 1) {
            fprintf(stderr, "connection closed prematurely");
            fclose(fp);
            goto cleanup;
        }

        size = ntohl(size_net); // convert it to host byte order
        fprintf(stderr, "file size received: %u\n", size);


        /*
         * Second, receive the file contents
         */

        int remaining = size;
        while (remaining > 0) {
            char buf[4096];
            int limit = remaining > sizeof(buf) ? sizeof(buf) : remaining;

            int received = fread(buf, 1, limit, clnt_fpr);
            if (received == 0) {
                fprintf(stderr, "connection closed prematurely");
                fclose(fp);
                goto cleanup;
            }

            remaining -= received;
            if (fwrite(buf, 1, received, fp) != received)
                err("fwrite (to %s) failed", filename);
        }

        // Close file first so we can stat() its file size.
        fclose(fp);


        /*
         * Third, send the file size back as acknowledgement.
         */

        struct stat st;
        if (stat(filename, &st) < 0)
            die("stat");
        size = st.st_size;
        fprintf(stderr, "file size on disk:  %u\n", size);
        size_net = htonl(size);

        if (fwrite(&size_net, sizeof(size_net), 1, clnt_fpw) < 1) {
            fprintf(stderr, "connection closed prematurely");
            goto cleanup;
        }

cleanup:
        /*
         * Finally, close the file and TCP connection, and go back to accept().
         */

        fclose(clnt_fpw);
        fclose(clnt_fpr);

        // Add blank line for prettier logging.
        fprintf(stderr, "\n");
    }

    /*
     * UNREACHABLE
     */
}
