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

    // TODO: implement tcp-dropbox-server

    return 0;
}
