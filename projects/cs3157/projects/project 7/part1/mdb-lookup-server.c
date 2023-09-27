#define _GNU_SOURCE
#include <arpa/inet.h>
#include <linux/limits.h>
#include <netdb.h>
#include <signal.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <time.h>
#include <unistd.h>
#include <mylist.h>
#include "mdb.h"

#define KeyMax 5
#define MAX_LINE_LENGTH 1024  // Maximum line length for request and headers
#define DISK_IO_BUF_SIZE 4096 // Size of buffer for reading and sending files

static void die(const char *message)
{
    perror(message);
    exit(1);
}

static void handle_client(char *database, int clnt_fd){

        /*
         * Handle client connection.
         */

        // Open the database file
        FILE *fp = fopen(database, "rb");
        if (fp == NULL){
            perror("fopen");
            return;
        }
        /*
        * Open client file descriptor as FILE pointers.
        */
        FILE *clnt_r = fdopen(clnt_fd, "rb");
        if (clnt_r == NULL)
            die("fdopen");

        FILE *clnt_w = fdopen(dup(clnt_fd), "wb");
        if (clnt_w == NULL)
            die("fdopen");

        /*
         * read all records into memory
         */

        struct List list;
        initList(&list);

        int loaded = loadmdb(fp, &list);
        if (loaded < 0)
            die("loadmdb");   
   
        if (fclose(fp) < 0)
            perror("file");
        
        /*
         * lookup loop
         */
              
        char line[1024];
        char key[KeyMax + 1];
         
        while(fgets(line, sizeof(line), clnt_r) != NULL){
  
            /*
             * clean up user input
             */
            
            if(strlen(line) >= 2 && line[strlen(line)-2] == '\r'){
                line[strlen(line)-2] = '\n';
                line[strlen(line)-1] = 0;
            }

            // must null-terminate the string manually after strncpy().
            strncpy(key, line, sizeof(key) - 1);
            key[sizeof(key) - 1] = '\0';

            // if newline is within the first KeyMax characters, remove it.
            size_t last = strlen(key) - 1;
            if (key[last] == '\n')
                key[last] = '\0';

            // user might have typed more than sizeof(line) - 1 characters in line;
            // continue fgets()ing until we encounter a newline.
            while (line[strlen(line) - 1] != '\n' && fgets(line, sizeof(line), clnt_r))
                ;

            /*
             * search with key
             */

            // traverse the list, printing out the matching records
            struct Node *node = list.head;
            int recNo = 1;
            while (node) {
                struct MdbRec *rec = (struct MdbRec *)node->data;

                if (strstr(rec->name, key) || strstr(rec->msg, key))
                    fprintf(clnt_w, "%4d: {%s} said {%s}\n", recNo, rec->name, rec->msg);

                node = node->next;
                recNo++;
                fflush(clnt_w);
            }
            
            fprintf(clnt_w, "\n");

            fflush(clnt_w);
        
        }
       
        // see if fgets() produced error CHECK THIS! SHOULD YOU DIE?
        if (ferror(clnt_r))
            perror("clnt_r");

        /*
         * clean up and quit
         */
 
        freemdb(&list);

       /*
        * Done with client request; close the connection and log the transaction.
        */

        // Closing can FILE pointers can also produce errors, which we log.
        if (fclose(clnt_w) < 0)
            perror("clnt_w");

        if (fclose(clnt_r) < 0)
            perror("clnt_r");

        return;
        // Resume server loop to handle next client connection.
}

static void sigchld_handler(int sig)
{
    // Keep reaping dead children until there aren't any to reap.
    while (waitpid(-1, NULL, WNOHANG) > 0)
        ;
}


int main(int argc, char **argv) {

    /*
     * Configure signal-handling.
     */

    struct sigaction sa;
    memset(&sa, 0, sizeof(sa));

    // Ignore SIGPIPE so that we don't terminate when we call
    // send() on a disconnected socket.
    sigemptyset(&sa.sa_mask);
    sa.sa_flags = 0;
    sa.sa_handler = SIG_IGN;
    if (sigaction(SIGPIPE, &sa, NULL))
        die("sigaction(SIGPIPE)");

    // Install a handler for the SIGCHLD signal so that we can reap children
    // who have finished processing their requests.
    sigemptyset(&sa.sa_mask);
    sa.sa_flags = SA_RESTART | SA_NOCLDSTOP;
    sa.sa_handler = &sigchld_handler;
    if (sigaction(SIGCHLD, &sa, NULL))
        die("sigaction(SIGCHLD)");

    /*
     * Check and obtain command-line arguments
     */
    if (argc != 3) {
        fprintf(stderr, "Usage: %s <server-port> <database>\n", argv[0]);
        exit(1);
    }

    char *server_port = argv[1];
    char *database = argv[2];

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
        
        pid_t pid = fork();
        if (pid < 0)
            die("fork");

        if (pid > 0) {
            /*
             * Parent process:
             *
             * Close client socket and continue accept()ing connections.
             */

            close(clnt_fd);

            continue;
        }

        /*
         * Child process:
         *
         * Close server socket, handle the client, and exit.
         */

        close(serv_fd);

        // clnt_addr is populated with information about the client.
        fprintf(stderr, "Connection started: %s\n",
                inet_ntoa(clnt_addr.sin_addr));

        handle_client(database, clnt_fd);

        fprintf(stderr, "Connection terminated: %s\n",
                inet_ntoa(clnt_addr.sin_addr));
       
        exit(0);
    }
   
   /*
    * UNREACHABLE
    */
    
    close(serv_fd);
    return 0;
}
