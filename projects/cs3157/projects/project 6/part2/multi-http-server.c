#define _GNU_SOURCE
#include <arpa/inet.h>
#include <netdb.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <signal.h>
#include <sys/wait.h>

#define BUF_SIZE 4096

static void die(const char *msg)
{
    perror(msg);
    exit(1);
}

static void usage_and_exit(char *argv0)
{
    fprintf(stderr, "usage: %s <server-port> <web-root>\n", argv0);
    fprintf(stderr, "   ex) %s 8888 ~/html\n", argv0);
    exit(1);
}

void reap_children(int sig){
    while (waitpid(-1, NULL, WNOHANG) > 0)
        ;
}

static void handle_client(int clnt_fd, char *web_root, char *ip_address){

    FILE *clnt_r = fdopen(clnt_fd, "rb");
    FILE *clnt_w = fdopen(dup(clnt_fd), "wb");
    int pid = (int) getpid();

     /*
     * Receive the HTTP response.
     */
    
    char *method = NULL;
    char *requestURI = NULL;
    char *httpVersion = NULL;    
    char *token_separators = "\t \r\n"; // tab, space, new line
   
    char buf[BUF_SIZE];

    // Reads the initial request line.
    if (fgets(buf, sizeof(buf), clnt_r) == NULL) {       
        
        fprintf(clnt_w, "HTTP/1.0 400 Bad Request\r\n\r\n"
                "<html><body><h1>400 Bad Request</h1></body></html>\r\n");
        fprintf(stderr, "%s (%d) \"%s %s %s\" 400 Bad Request\n",
                ip_address, pid, method, requestURI, httpVersion);

        buf[0] = 0;
        fclose(clnt_r);
        fclose(clnt_w);
        return;
    }

    method = strtok(buf, token_separators);
    requestURI = strtok(NULL, token_separators);
    httpVersion = strtok(NULL, token_separators);
    char * extra = strtok(NULL, token_separators);


    // If the initial request line is not complete or there is an extra word at the end
    // Or the URI doesn't start with '/' or there exists 
    if(method == NULL || requestURI == NULL || httpVersion == NULL || extra != NULL || strncmp("/", requestURI, 1) != 0 || strstr(requestURI, "/../") != NULL  || ( (strlen(requestURI) >= 3) && *(requestURI + strlen(requestURI) - 1) == '.' && *(requestURI + strlen(requestURI) - 2) == '.' && *(requestURI + strlen(requestURI) - 3) == '/') ){

        fprintf(clnt_w, "HTTP/1.0 400 Bad Request\r\n\r\n"
                "<html><body><h1>400 Bad Request</h1></body></html>\r\n");
        fprintf(stderr, "%s (%d) \"%s %s %s\" 400 Bad Request\n",
                ip_address, pid, method, requestURI, httpVersion);

        buf[0] = 0; 
        fclose(clnt_r);
        fclose(clnt_w);
        return;
    }

    // If the request is not GET or the HTTP version is not HTTP/1.0 or HTTP/1.1
    if (strcmp("GET", method) != 0 || !(strcmp("HTTP/1.0", httpVersion) == 0 || strcmp("HTTP/1.1", httpVersion) == 0)) {
        fprintf(clnt_w,
            "HTTP/1.0 501 Not Implemented\r\n\r\n"
            "<html><body><h1>501 Not Implemented</h1></body></html>\r\n");
        fprintf(stderr, "%s (%d) \"%s %s %s\" 501 Not Implemented\n",
               ip_address, pid, method, requestURI, httpVersion);
    
        buf[0] = 0;
        fclose(clnt_r);
        fclose(clnt_w);
        return;
    }
        
    char buf3[BUF_SIZE];
    
    while(1){
	 if (fgets(buf3, sizeof(buf3), clnt_r) == NULL) {       
       		fprintf(clnt_w, "HTTP/1.0 400 Bad Request\r\n\r\n"
                	    "<html><body><h1>400 Bad Request</h1></body></html>\r\n");
        	fprintf(stderr, "%s (%d) \"%s %s %s\" 400 Bad Request\n",
                        ip_address, pid, method, requestURI, httpVersion);
 
                buf[0] = 0;
        	fclose(clnt_r);
        	fclose(clnt_w);
        	return;
    	}

	if(strlen(buf3) <= 2  && buf3[strlen(buf3)-1] == '\n' )
 		break;

    }

    //From this point on, we can assume that HTTP request has correct structure
  
    fprintf(stderr, "%s (%d) \"%s %s %s\" ", ip_address, pid, method, requestURI, httpVersion);
    buf[0] = 0;

    // If URI ends with /, append index.html
    if (strlen(requestURI) > 0 && (*(requestURI + strlen(requestURI) - 1))  == '/')         
        strcat(requestURI, "index.html"); 
         
        
    strcat(web_root, requestURI);

    struct stat st;
    if (stat(web_root, &st) == 0 && S_ISDIR(st.st_mode)) {
        fprintf(clnt_w, "HTTP/1.0 301 Moved Permanently\r\n"
                "Location: %s/\r\n\r\n" 
                "<html><body>\r\n"
                "<h1>301 Moved Permanently</h1>\r\n"
                "<p>The document has moved <a href=\"%s/\">here</a>.</p>\r\n"
                "</body></html>\r\n", requestURI, requestURI);
        fprintf(stderr, "301 Moved Permanently\n");
       
        fclose(clnt_w);
        fclose(clnt_r);
        *(web_root + strlen(web_root) - strlen(requestURI)) = '\0';
        return; 
    }

    // Open up file_name for reading.
    FILE *file = fopen(web_root, "rb");
    if(file == NULL){
        fprintf(clnt_w, "HTTP/1.0 404 Not Found\r\n\r\n"
                "<html><body><h1>404 Not Found</h1></body></html>\r\n");
        fprintf(stderr, "404 Not Found\n");
       
        fclose(clnt_w);
        fclose(clnt_r);
        *(web_root + strlen(web_root) - strlen(requestURI)) = '\0';
        return;
    }

    // Bring back web_root to its original content
    *(web_root + strlen(web_root) - strlen(requestURI)) = '\0'; 
        
    char buf2[BUF_SIZE];
       
    // Use fread()/fwrite() so that we can upload binary files.


    fprintf(clnt_w, "HTTP/1.0 200 OK\r\n\r\n");
    fprintf(stderr, "200 OK\n");
    size_t n;
    while ((n = fread(buf2, 1, sizeof(buf2), file)) > 0  && !(ferror(file)) ) {
        if (fwrite(buf2, 1, n, clnt_w) != n) {
            // Don't crash the server and move to the next client.
            fclose(clnt_w);
            fclose(clnt_r);
            fclose(file);
            perror("send bytes to client");
            return;
        }
        fflush(clnt_w);
    }


    // fread() returns 0 on EOF or on error, so we need to check for errors.
    if (ferror(file)) {
        // Don't crash the server and move to the next client.
        fclose(clnt_w);
        fclose(clnt_r);
        fclose(file);
        perror("read from the file requested");
        return;
    } 


    /*
    * All done, clean up.
    */

    // Close FILE * for output file.
    fclose(file);       

    // Close client connection.
    fclose(clnt_r);
    fclose(clnt_w);

    // Resume server loop to handle next client connection.
    return;

}



int main(int argc, char **argv)
{

    struct sigaction sa;
    memset(&sa, 0, sizeof(sa));         // Zero-initialize sigaction structure
    
    sigemptyset(&sa.sa_mask);           // Don't mask any signals
    sa.sa_handler = SIG_IGN;            // Ignore the signal
    if (sigaction(SIGPIPE, &sa, NULL))
        die("sigaction");

    sigemptyset(&sa.sa_mask);           // Don't mask any signals
    sa.sa_flags = SA_RESTART;             // Restart interrupted system calls
    sa.sa_handler = &reap_children;      // Reap children upon receiving signal
    if (sigaction(SIGCHLD, &sa, NULL)) 
       die("sigaction");
    
    /*
     * Parse arguments and determine output file name.
     */

    if (argc != 3)
        usage_and_exit(argv[0]);

    char *server_port = argv[1];
    char *web_root = argv[2];


    /*
     * Obtain socket address structure from server name and port number.
     */

    struct addrinfo hints, *info;
    memset(&hints, 0, sizeof(hints));

    hints.ai_family = AF_INET;       // Only accept IPv4 addresses
    hints.ai_socktype = SOCK_STREAM; // Stream socket for TCP connections
    hints.ai_protocol = IPPROTO_TCP; // TCP protocol
    hints.ai_flags = AI_PASSIVE;     // Construct socket address for bind()ing

    int aerr;
    if ((aerr = getaddrinfo(NULL, server_port, &hints, &info)) != 0) {
        fprintf(stderr, "getaddrinfo: %s\n", gai_strerror(aerr));
        exit(1);
    }

    /*
     * Create a socket(), bind() it to the server, and wrap in FILE *s.
     */

    int serv_fd = socket(info->ai_family, info->ai_socktype, info->ai_protocol);
    if (serv_fd < 0)
        die("socket");

    if (bind(serv_fd, info->ai_addr, info->ai_addrlen) < 0)
        die("bind");
   
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
        
        char *ip_address = inet_ntoa(clnt_addr.sin_addr);
            
        // clnt_addr is now populated with information about the client.
        //fprintf(stderr, "Accepted connection from %s\n",ip_address);

        pid_t pid = fork();

        // Both the parent and child will resume execution here.
        if (pid == 0){
            
            // Child process
            close(serv_fd);
            handle_client(clnt_fd, web_root, ip_address);
            exit(0);

        }else{
            
            close(clnt_fd);
            // Parent process
        }
         
    }

    /*
     * UNREACHABLE
     */

    // Theoretically, if we want our server to handle graceful termination, we
    // should also close() the server socket here too:
    close(serv_fd);

    return 0;
}

