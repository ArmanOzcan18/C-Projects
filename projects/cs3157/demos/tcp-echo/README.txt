TCP Echo Client and Server
--------------------------

These examples show how to construct a client and server connection using the
POSIX sockets API.

Run make to build both the client and server.

To run this example, first run the server and tell it to listen on a port:

    server$ ./tcp-echo-server 3157

(If it complains about "Address already in use", pick another port number.)

Then, in another terminal, run the client, and tell it to connect to the IP
address of your server with your chosen port number; if you're running both on
CLAC, you can use the "loopback" address 127.0.0.1:

    client$ ./tcp-echo-client "hi there" 127.0.0.1 3157
    hi there
    Sent (and received) 8 bytes in total

You can also specify a domain name like clac.cs.columbia.edu:

    client$ ./tcp-echo-client "hi there" clac.cs.columbia.edu 3157
    hi there
    Sent (and received) 8 bytes in total

You can also use netcat for either side of the connection; I recommend trying
this out and constructing your own input to the TCP connection.
