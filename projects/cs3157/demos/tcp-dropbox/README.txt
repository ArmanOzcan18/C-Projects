TCP Dropbox
-----------

This repository should build two programs: tcp-dropbox-client and
tcp-dropbox-server (though it also includes and builds tcp-dropbox-server-sol,
the solutions for tcp-dropbox-server).  tcp-dropbox-server is not fully
implemented; your task is to complete it.

As usual, run "make" to build all executables.


Usage
-----

You should start the tcp-dropbox-server like this:

    $ tcp-dropbox-server <server-port> <filebase>

tcp-dropbox-server will listen for TCP connections from on <server-port>.
Then, you can upload a file using tcp-dropbox-client like this:

    $ tcp-dropbox-client <server-ip> <server-port> <file>

It will connect with the server and send the contents of <file> to
tcp-dropbox-server, according to our own tcp-dropbox protocol.
tcp-dropbox-server will then write those file contents to a file named
<filebase>.<N>, where <N> is the number of connections it has received since it
started running.  For example, if you run tcp-dropbox-server with "hello" as
your <filebase>, then tcp-dropbox-server will write uploaded file content to
"hello.0", "hello.1", "hello.2", etc. for each client connection.


Protocol
--------

WARNING: spoilers ahead.  Try to figure this out yourself first by reading the
implementation of tcp-dropbox-client, and compare with below!

This is client-server protocol; the client uploads files to a server, while the
server reads those files and saves them to disk.  The client and server exchange
additional information to ensure the integrity of the sent file.

After a client establishes a connection with a listening server, the protocol
proceeds in three stages:

1.  The client sends the server the file size of the file it will send as
    a 4-byte integer in network byte order.

2.  The client sends the contents of the file.

3.  The server responds with the file size of what it just received, as a 4-byte
    integer in network byte order, to acknowledge receipt of all bytes.

After this exchange, the server should close the connection and proceed to
handle subsequent client connections.
