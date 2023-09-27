ncat over TCP
-------------

This example shows how to wrap a socket file descriptor with a FILE pointer.
This server reads lines of text from connected clients, and responds with the
same lines of text annotated with line numbers (like the ncat, except over TCP).

Run make to build the server executable.

To run this example, run the server and tell it to listen on some port:

    server$ ./tcp-ncat 3157

(If it complains about "Address already in use", pick another port number.)

Then, in another terminal, connect with the server, and send over some text.
Here's how you can do so with netcat (nc), e.g., with the short word list from
Lab 1:

    client$ nc -N clac.cs.columbia.edu 3157 < ~j-hui/cs3157-pub/lab1/part2/words/short-list
    [   1]hello
    [   2]world
    [   3]words
    [   4]tests
    [   5]bread
    [   6]onion
    [   7]mouse
    [   8]memes
    [   9]apply
    [  10]sorry
    [  11]phone
    [  12]party
    [  13]fruit
    [  14]pasta
    [  15]swamp
    [  16]stage
    [  17]funky
    [  18]music
    [  19]quick
    [  20]achoo

Note that we pass the -N flag to nc so that it closes the TCP connection when it
finishes reading from stdin.
