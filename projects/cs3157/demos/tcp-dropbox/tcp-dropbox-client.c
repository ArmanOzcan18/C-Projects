#define _GNU_SOURCE
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>
#include <unistd.h>

#include <netdb.h>
#include <arpa/inet.h>
#include <sys/wait.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <sys/socket.h>

static void die(const char *s) {
    perror(s);
    exit(1);
}

int main(int argc, char **argv) {
    if (argc != 4) {
        fprintf(stderr, "usage: %s <server-ip> <server-port> <file>\n",
                argv[0]);
        exit(1);
    }

    const char *ip = argv[1];
    const char *port = argv[2];
    const char *filename = argv[3];


    /*
     * Open file to send.
     *
     * Do this first to make sure it can be opened before attempting network
     * connection.
     */

    FILE *fp = fopen(filename, "rb");
    if (fp == NULL)
        die(filename);


    /*
     * Connect to server, and obtain FILE pointers for socket connection.
     */

    struct addrinfo hints, *info;
    memset(&hints, 0, sizeof(hints));
    hints.ai_family = AF_INET;        // Only accept IPv4 addresses
    hints.ai_socktype = SOCK_STREAM;  // stream socket for TCP connections
    hints.ai_protocol = IPPROTO_TCP;  // TCP protocol

    int addr_err;
    if ((addr_err = getaddrinfo(ip, port, &hints, &info)) != 0) {
        fprintf(stderr, "getaddrinfo: %s\n", gai_strerror(addr_err));
        exit(1);
    }

    int sock = socket(info->ai_family, info->ai_socktype, info->ai_protocol);
    if (sock < 0)
        die("socket");

    if (connect(sock, info->ai_addr, info->ai_addrlen) < 0)
        die("connect");

    freeaddrinfo(info);

    /*
     * Initiate tcp-dropbox protocol.
     */

    struct stat st;
    if (stat(filename, &st) < 0)
        die("stat");
    uint32_t size = st.st_size;
    fprintf(stderr, "file size:  %u\n", size);
    uint32_t size_net = htonl(size);

    /*
     * Open the file to send.
     */

    if (send(sock, &size_net, sizeof(size_net), 0) != sizeof(size_net))
        die("send(size)");

    char buf[4096];
    unsigned int n;
    unsigned int total = 0;

    while ((n = fread(buf, 1, sizeof(buf), fp)) > 0) {
        if (send(sock, buf, n, 0) != n)
            die("send(content)");
        else
            total += n;
    }

    // fread() returns 0 on EOF or error, so check if an error occurred.
    if (ferror(fp))
        die("fread");

    fclose(fp);
    fprintf(stderr, "bytes sent: %u\n", total);


    uint32_t ack, ack_net;

    int r = recv(sock, &ack_net, sizeof(ack_net), MSG_WAITALL);
    if (r < 0)
        die("recv");
    else if (r != sizeof(ack_net))
        die("connection closed prematurely");

    ack = ntohl(ack_net);
    if (ack != size)
        die("ack != size");


    /*
     * Clean-up.
     */

    // Optional step: check that the server closed the TCP connection after
    // completing the tcp-dropbox protocol.

    char x;
    r = recv(sock, &x, 1, 0);
    if (r != 0)
        die("server didn't close connection");

    close(sock);

    return 0;
}
