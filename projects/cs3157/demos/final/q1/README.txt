Fall 2022 Final Exam: Problem 1
-------------------------------

Running
-------

To run the code for this problem, just run:

    $ make
     gcc -g   -c -o freegrind.o freegrind.c
     ar rv -U libfg.a freegrind.o
     ar: creating libfg.a
     a - freegrind.o
     gcc -g   -c -o fgtest.o fgtest.c
     gcc -L.  fgtest.o  -lfg -o fgtest
     ./fgtest
     0

The output of fgtest will appear a little weird (and you may hear a bell noise),
as a result of it outputting non-ASCII characters directly to the terminal.

You can check the permissions of the fgtest executable using:

    $ ls -la fgtest
    -rwxr-xr-x 1 j-hui j-hui 20216 Dec 21 17:15 fgtest

In octal notation, -rwx------ is written as 0700 (or 700 for short).

As usual, you can clean up all build artifacts and start fresh by running:

    $ make clean
    rm -rf *.o *.a a.out fgtest


Exploring
---------

You should try to modify the relevant parts of fgtest.c and the Makefile to see
what would have happened if you had written something different.  For example,
writing:

    default: fgtest

Would have failed to build in a clean directory, because libfg.a is missing.

You can also explore the effects of setting the Makefile variables to different
values; those will be visible in the output of running make (since Make prints
out the commands and flags of everything it executes).
