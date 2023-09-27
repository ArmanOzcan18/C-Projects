String Objects
--------------

Directory structure:

  - Makefile: Tells Make how to build everything.

  - mystr.h: Struct definition and method declarations for struct mystr.  You
    should not modify this.

  - mystr.c: Where methods for struct mystr are implemented.  Your job is to
    modify this file and replace method definitions with your own.

  - mystr-test.c: A test driver for your mystr implementation; this defines
    a main() function which performs some mystr operations.  You may adapt this
    as it suits you to better test or understand your code.

  - mystr-solutions.c: Contains my solution code for each of the methods.  You
    should not modify this file, but you are welcome to read it if you would
    like to study how I implemented each of the methods.

Here are some handy Make targets:

 -  Run 'make' to build.

 -  Run 'make test' to run the test suite.

 -  Run 'make vg' to run the test suite with Valgrind.
