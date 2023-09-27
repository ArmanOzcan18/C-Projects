Solutions to Recitation 8
-------------------------

For this recitation, it's much more important to complete the exercise than to
study the solutions.  However, this repository provides some commentary about
what you should expect, and some supplementary code where appropriate.

8.0 hello.sh
------------

You can find my hello.sh script in this repo, documented in the comments.

8.1 mdb-lookup-server.sh
------------------------

You can find my mdb-lookup-server.sh script in this repo, documented in the
comments.

8.2 Exploring HTTP with netcat
------------------------------

To send nc -l 8888 an HTTP request (replacing 8888 with your own port number):

  - Using curl:

        $ curl http://clac.cs.columbia.edu:8888/~j-hui/cs3157/index.html

    Or:

        $ curl -v http://clac.cs.columbia.edu:8888/~j-hui/cs3157/index.html

    Specifying the -v flag will tell curl to also print out additional
    information about bytes over the TCP connection throughout the HTTP session,
    with lines sent prefixed with '>' and lines received prefixed with '<'.

  - Using wget:

        $ wget http://clac.cs.columbia.edu:8888/~j-hui/cs3157/index.html

  - In your browser, type the following address into the address bar:

        http://clac.cs.columbia.edu:8888/~j-hui/cs3157/index.html

    Make sure you specify "http://"; otherwise, your browser will default to
    HTTPS (i.e., "https://").

In doing so, you should see an HTTP request appear in your netcat server;
a sample HTTP request is included in this repo, saved as request.txt.  You can
redirect this request into netcat when connecting with a real server, e.g.,:

    $ nc clac.cs.columbia.edu 80 < request.txt

Alternatively, you can manually construct a request with only the request line,
and feed that to netcat.  Here's how you can do so using echo:

    $ echo -e -n 'GET /~j-hui/cs3157/index.html HTTP/1.0\r\n\r\n' | \
        nc clac.cs.columbia.edu

Alternatively, use the -C flag (to send \r\n instead of \n) and type in the
request manually:

    $ nc -C clac.cs.columbia.edu 80
    GET /~j-hui/cs3157/index.html HTTP/1.0


You must send a blank line, to indicate the end of the request, before the
server will respond.

When you send an HTTP request a real HTTP server, the server will respond with
a response like the sample HTTP response in this repo, response.txt.

When you look at a request or response using a hexdump tool (like hexyl or xxd),
you will find that lines end with the bytes 0d and 0a (written in hexadecimal),
which correspond to the ASCII bytes for '\r' and '\n':

    $ xxd request.txt
    00000000: 4745 5420 2f7e 6a2d 6875 692f 6373 3331  GET /~j-hui/cs31
    00000010: 3537 2f69 6e64 6578 2e68 746d 6c20 4854  57/index.html HT
    00000020: 5450 2f31 2e31 0d0a 486f 7374 3a20 636c  TP/1.1..Host: cl
    00000030: 6163 2e63 732e 636f 6c75 6d62 6961 2e65  ac.cs.columbia.e
    00000040: 6475 3a38 3838 380d 0a55 7365 722d 4167  du:8888..User-Ag
    00000050: 656e 743a 2063 7572 6c2f 372e 3831 2e30  ent: curl/7.81.0
    00000060: 0d0a 4163 6365 7074 3a20 2a2f 2a0d 0a0d  ..Accept: */*...
    00000070: 0a

This line-ending format is required for HTTP request and response lines;
however, it is NOT required for the payload of the GET response payload (which
may not even be textual).

You can obtain another file simply by modifying the URI in the request (e.g.,
modifying /~j-hui/cs3157/index.html to /index.html).  See request-index.txt (and
compare it to request.txt) for an example of this.

You can obtain a 404 response by modifying the URI to a resource that does not
exist.  See request-404.txt for an example of this.

You can obtain a 400 response by simply sending a malformed request;
see request-400.txt for an example of this.
