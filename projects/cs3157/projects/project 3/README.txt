This file should contain:

  - Arman Ozcan
  - ao2794
  - lab 3
  - My program should work as it should. 
  
The description should indicate whether your solution for the part is
working or not.  You may also want to include anything else you would
like to communicate to the grader such as extra functionalities you
implemented or how you tried to fix your non-working code.
==64906== Memcheck, a memory error detector
==64906== Copyright (C) 2002-2017, and GNU GPL'd, by Julian Seward et al.
==64906== Using Valgrind-3.18.1 and LibVEX; rerun with -h for copyright info
==64906== Command: ./mylist-test
==64906== 
testing addFront(): 9.0 8.0 7.0 6.0 5.0 4.0 3.0 2.0 1.0 
testing flipSignDouble(): -9.0 -8.0 -7.0 -6.0 -5.0 -4.0 -3.0 -2.0 -1.0 
testing flipSignDouble() again: 9.0 8.0 7.0 6.0 5.0 4.0 3.0 2.0 1.0 
testing findNode(): OK
popped 9.0, the rest is: [ 8.0 7.0 6.0 5.0 4.0 3.0 2.0 1.0 ]
popped 8.0, the rest is: [ 7.0 6.0 5.0 4.0 3.0 2.0 1.0 ]
popped 7.0, the rest is: [ 6.0 5.0 4.0 3.0 2.0 1.0 ]
popped 6.0, the rest is: [ 5.0 4.0 3.0 2.0 1.0 ]
popped 5.0, the rest is: [ 4.0 3.0 2.0 1.0 ]
popped 4.0, the rest is: [ 3.0 2.0 1.0 ]
popped 3.0, the rest is: [ 2.0 1.0 ]
popped 2.0, the rest is: [ 1.0 ]
popped 1.0, the rest is: [ ]
testing addAfter(): 1.0 2.0 3.0 4.0 5.0 6.0 7.0 8.0 9.0 
popped 1.0, and reversed the rest: [ 9.0 8.0 7.0 6.0 5.0 4.0 3.0 2.0 ]
popped 9.0, and reversed the rest: [ 2.0 3.0 4.0 5.0 6.0 7.0 8.0 ]
popped 2.0, and reversed the rest: [ 8.0 7.0 6.0 5.0 4.0 3.0 ]
popped 8.0, and reversed the rest: [ 3.0 4.0 5.0 6.0 7.0 ]
popped 3.0, and reversed the rest: [ 7.0 6.0 5.0 4.0 ]
popped 7.0, and reversed the rest: [ 4.0 5.0 6.0 ]
popped 4.0, and reversed the rest: [ 6.0 5.0 ]
popped 6.0, and reversed the rest: [ 5.0 ]
popped 5.0, and reversed the rest: [ ]
==64906== 
==64906== HEAP SUMMARY:
==64906==     in use at exit: 0 bytes in 0 blocks
==64906==   total heap usage: 19 allocs, 19 frees, 1,312 bytes allocated
==64906== 
==64906== All heap blocks were freed -- no leaks are possible
==64906== 
==64906== For lists of detected and suppressed errors, rerun with: -s
==64906== ERROR SUMMARY: 0 errors from 0 contexts (suppressed: 0 from 0)
==243798== Memcheck, a memory error detector
==243798== Copyright (C) 2002-2017, and GNU GPL'd, by Julian Seward et al.
==243798== Using Valgrind-3.18.1 and LibVEX; rerun with -h for copyright info
==243798== Command: ./revecho arman is a dude
==243798== 
dude
a
is
arman

dude found
==243798== 
==243798== HEAP SUMMARY:
==243798==     in use at exit: 0 bytes in 0 blocks
==243798==   total heap usage: 5 allocs, 5 frees, 2,624 bytes allocated
==243798== 
==243798== All heap blocks were freed -- no leaks are possible
==243798== 
==243798== For lists of detected and suppressed errors, rerun with: -s
==243798== ERROR SUMMARY: 0 errors from 0 contexts (suppressed: 0 from 0)
