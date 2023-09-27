#define _GNU_SOURCE
#include <stdio.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netdb.h>

int main(void) {

    struct addrinfo hints = {0}, *info;
    hints.ai_family = AF_INET;
    hints.ai_socktype = SOCK_STREAM;
    hints.ai_protocol = IPPROTO_TCP;

    getaddrinfo("12.34.56.78", "9", &hints, &info);
    struct sockaddr_in *addr = (struct sockaddr_in *) info->ai_addr;

    uint32_t na = addr->sin_addr.s_addr,                // IP addr, big-endian
             ha = ntohl(addr->sin_addr.s_addr);
    uint16_t a = addr->sin_port,                        // Port num, big-endian
             b = htons(addr->sin_port),
             c = *(uint16_t *) &addr->sin_addr.s_addr;

    char *p;

    p = (char *) &na;
    printf("na: %2d | %2d | %2d | %2d\n", p[0], p[1], p[2], p[3]);
    p = (char *) &ha;
    printf("ha: %2d | %2d | %2d | %2d\n", p[0], p[1], p[2], p[3]);

    p = (char *) &a;
    printf("a: %2d | %2d\n", p[0], p[1]);

    p = (char *) &b;
    printf("b: %2d | %2d\n", p[0], p[1]);

    p = (char *) &c;
    printf("c: %2d | %2d\n", p[0], p[1]);

    freeaddrinfo(info);

    return 0;
}
