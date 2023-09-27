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
        fprintf(stderr, "Usage: %s <host> <port-number> <URI>\n",
                argv[0]);
        exit(1);
    }

    char *host = argv[1];
    char *port_number = argv[2];
    char *URI = argv[3];

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
    if ((addr_err = getaddrinfo(host, port_number, &hints, &info)) != 0) {
        fprintf(stderr, "getaddrinfo: %s\n", gai_strerror(addr_err));
        exit(1);
    }

    int serv_fd = socket(info->ai_family, info->ai_socktype, info->ai_protocol);
    if (serv_fd < 0)
       die("socket");

    if (connect(serv_fd, info->ai_addr, info->ai_addrlen) < 0)
        die("connect");

    // BTW: we're done with the info retrieved by getaddrinfo(), so free it.
    freeaddrinfo(info);
   
    FILE *sock_fp = fdopen(serv_fd, "rb");  
        

    send(serv_fd, "GET ", 4, 0);
    send(serv_fd, URI, strlen(URI), 0);
    send(serv_fd, " HTTP/1.0\r\n", 11, 0);
    send(serv_fd, "Host: ", 6, 0);
    send(serv_fd, host, strlen(host), 0);
    send(serv_fd, ":", 1, 0);
    send(serv_fd, port_number, strlen(port_number), 0);
    send(serv_fd, "\r\n", 2, 0);
    send(serv_fd, "Accept: */*\r\n", 13, 0);
    send(serv_fd, "\r\n", 2, 0);
    

    char buf[1000] = {0};
    int i = 0;

    while((buf[i++]=fgetc(sock_fp)) != ' '); //to move the stream pointer to the first char of the status code of the HTTP response header

    char a;

    if((a = fgetc(sock_fp)) != '2'){ // if there is an error
       buf[i++] = (char) a;
 
       while(buf[i-2] != '\r' || buf[i-1] != '\n'){
           buf[i++] = fgetc(sock_fp);
       }
       buf[i-2] = '\n';
       buf[i-1] = 0;

       printf("%s\n",buf);
       //fflush(stdout);

       fclose(sock_fp);
       exit(1); //ask about this to John 1 or 0
    }

    char *name = strrchr(URI,'/');

    if(name == NULL){
        printf("wrong URI\n");
        fclose(sock_fp);
        exit(1);
    }

    name++; // increment the address pointer to skip

    FILE *file = fopen(name, "wb");     
    if(file == NULL){
        fclose(sock_fp);
        die("fopen");
    }

    char check[4] = {0}; // I will store the most recent four bytes of the HTTP response until I get /r/n/r/n
    i = 0;
   
    //char msg[1000] = {0}; 
    //int j = 0;

    while(check[i] != '\r' || check[(i + 1) % 4] != '\n' || check[(i + 2) % 4] != '\r' || check[(i + 3) % 4] != '\n'){
        check[i] = fgetc(sock_fp);
        // msg[j++] = check[i];   
        i = (i + 1) % 4;
    }
    
    //msg[j] = '\n';

    //printf("%s", msg);

    int len;
    int len2;
    char inputBuf[1000] = {0};

    while((len = fread(inputBuf, 1, sizeof(inputBuf), sock_fp))>0){
         if(ferror(sock_fp)){
             fclose(sock_fp);
             fclose(file);
             die("error in reading from a socket file");
         }   

        if((len2 = fwrite(inputBuf, 1, len, file) < len)) {
            fclose(sock_fp);
            fclose(file);
            die("error in writing to a file");
        }
    } 

    if(ferror(sock_fp)){
        fclose(sock_fp);
        fclose(file);
        die("error in reading from a socket file");
    }
        
    fclose(sock_fp);
    fclose(file);
}
