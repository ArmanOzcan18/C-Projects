This file should contain:

  - Arman Ozcan
  - ao2794
  - lab6
  - It should work! And I set up my web page.

The description should indicate whether your solution for the part is
working or not.  You may also want to include anything else you would
like to communicate to the grader such as extra functionalities you
implemented or how you tried to fix your non-working code.
==68827== Memcheck, a memory error detector
==68827== Copyright (C) 2002-2017, and GNU GPL'd, by Julian Seward et al.
==68827== Using Valgrind-3.18.1 and LibVEX; rerun with -h for copyright info
==68827== Command: ./http-server 10125 /mnt/disks/students229/ao2794/html
==68827== 
34.145.159.110 "GET /cs3157/ HTTP/1.0" 200 OK
34.145.159.110 "GET /cs3157/ HTTP/1.5" 501 Not Implemented
34.145.159.110 "GET /cs3157/ HTTP/1.5" 501 Not Implemented
34.145.159.110 "GET /cs3157 HTTP/1.1" 301 Moved Permanently
==68827== 
==68827== Process terminating with default action of signal 2 (SIGINT)
==68827==    at 0x498A5D7: accept (accept.c:26)
==68827==    by 0x10A1AF: main (http-server.c:283)
==68827== 
==68827== HEAP SUMMARY:
==68827==     in use at exit: 0 bytes in 0 blocks
==68827==   total heap usage: 19 allocs, 19 frees, 37,592 bytes allocated
==68827== 
==68827== All heap blocks were freed -- no leaks are possible
==68827== 
==68827== For lists of detected and suppressed errors, rerun with: -s
==68827== ERROR SUMMARY: 0 errors from 0 contexts (suppressed: 0 from 0)
==115292== Memcheck, a memory error detector
==115292== Copyright (C) 2002-2017, and GNU GPL'd, by Julian Seward et al.
==115292== Using Valgrind-3.18.1 and LibVEX; rerun with -h for copyright info
==115292== Command: ./multi-http-server 10129 /mnt/disks/students229/ao2794/html
==115292== 
34.145.159.110 (116118) "GET /cs3157/photos.jpg HTTP/1.1" 404 Not Found
==116118== 
==116118== HEAP SUMMARY:
==116118==     in use at exit: 0 bytes in 0 blocks
==116118==   total heap usage: 6 allocs, 6 frees, 9,672 bytes allocated
==116118== 
==116118== All heap blocks were freed -- no leaks are possible
==116118== 
==116118== For lists of detected and suppressed errors, rerun with: -s
==116118== ERROR SUMMARY: 0 errors from 0 contexts (suppressed: 0 from 0)
34.145.159.110 (117352) "GET /cs3157/images/photos.jpg HTTP/1.1" 404 Not Found
==117352== 
==117352== HEAP SUMMARY:
==117352==     in use at exit: 0 bytes in 0 blocks
==117352==   total heap usage: 6 allocs, 6 frees, 9,672 bytes allocated
==117352== 
==117352== All heap blocks were freed -- no leaks are possible
==117352== 
==117352== For lists of detected and suppressed errors, rerun with: -s
==117352== ERROR SUMMARY: 0 errors from 0 contexts (suppressed: 0 from 0)
34.145.159.110 (117760) "GET /cs3157/images/photo.jpg HTTP/1.1" 200 OK
==117760== 
==117760== HEAP SUMMARY:
==117760==     in use at exit: 0 bytes in 0 blocks
==117760==   total heap usage: 7 allocs, 7 frees, 17,864 bytes allocated
==117760== 
==117760== All heap blocks were freed -- no leaks are possible
==117760== 
==117760== For lists of detected and suppressed errors, rerun with: -s
==117760== ERROR SUMMARY: 0 errors from 0 contexts (suppressed: 0 from 0)
==115292== 
==115292== Process terminating with default action of signal 2 (SIGINT)
==115292==    at 0x498A5D7: accept (accept.c:26)
==115292==    by 0x10A2A7: main (multi-http-server.c:291)
==115292== 
==115292== HEAP SUMMARY:
==115292==     in use at exit: 0 bytes in 0 blocks
==115292==   total heap usage: 1 allocs, 1 frees, 64 bytes allocated
==115292== 
==115292== All heap blocks were freed -- no leaks are possible
==115292== 
==115292== For lists of detected and suppressed errors, rerun with: -s
==115292== ERROR SUMMARY: 0 errors from 0 contexts (suppressed: 0 from 0)
