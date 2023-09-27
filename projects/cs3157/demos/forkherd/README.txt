forkherd
--------

To build forkherd, run make.

To run the program according to the question and obtain a chronological account
of the number of processes, the directory contents, and the file contents, run
"make run" (or just use the ./runtest.sh script after building forkherd).  This
produces a timeline of events, i.e., the answers are sorted chronologically
instead of by question.

To sort the output of ./runtest.sh by question, run "make answer". Note that
this will appear to hang (do nothing) for about 15 seconds, so wait patiently!


Explanation
-----------

(Note: in code snippets, some lines of C code are compacted for brevity.)

forkherd starts with the following code segment:

    while (1) {
        if (*++argv == NULL) 
            exit(0);
         else if (fork() == 0) // Child process
            break;
         else // Parent process
            continue;
    }

    sleep(2);  // Sleep for 2 seconds

The while loop produces a child process for each argument other than argv[0],
and terminates the parent process.  One child process has argv pointing to "A",
while the other child process has argv pointing to "B".  Let's call these two
processes "pA" and "pB"

Then, pA and pB each sleep for 2 seconds.  At the 1 second mark, both processes
are still sleeping, which is why the answer to 1.1 is 2.

Next, we have the following code:

    char buf[4];  int pos = 0;  int r;
    while (1) {
        FILE *f = fopen(*argv, "rb");  assert(f);
        fseek(f, pos, SEEK_SET);
        r = fread(buf, 1, sizeof(buf), f);
        fclose(f);

        if (r == 0)
            exit(0);
        else if (fork() == 0)
            break;
        else
            pos += r;
    }

    sleep(2);  // Sleep for 2 seconds

The program declares three variables that will become important later in the
question:

  - buf holds the contents read from either A or B
  - pos keeps track of how much of the file has been read between iterations.
  - r records how many bytes were read from the file.

pA and pB independently execute this loop, for a different number of iterations.
That number of iterations depends on the size of the files A and B, which pA and
pB respectively read from, 4 bytes at a time.  Each loop iteration produces
a new child process.

 - pA executes the loop 3 times, reading in "0123" the first time, "4567" the
   second, and "89\n" the last time.  For reasons that will become clear later,
   let's call the three children produced "pA0", "pA4", and "pA8", whose bufs
   hold the contents of read in at each loop iteration.

 - pB executes the loop 7 times, reading in "0123", "4567", "89ab", "cdef",
   "0123", "4567", and "89\n".  We will call these children "pB0", "pB4",
   "pB8", "pB12", "pB16", "pB20", and "pB24".

The two parent processes, "pA" and "pB", both exit(), leaving behind the
following 10 processes that sleep for 2 seconds:

    Name      buf contents          r value     *argv points to     pos value
    ----      ------------          -------     ---------------     ---------
    pA0       '0' '1' '2' '3'       4           "A"                 0
    pA4       '4' '5' '6' '7'       4           "A"                 4
    pA8       '8' '9' '\n' '7'      3           "A"                 8
    pB0       '0' '1' '2' '3'       4           "B"                 0
    pB4       '4' '5' '6' '7'       4           "B"                 4
    pB8       '8' '9' 'a' 'b'       4           "B"                 8
    pB12      'c' 'd' 'e' 'f'       4           "B"                 12
    pB16      '0' '1' '2' '3'       4           "B"                 16
    pB20      '4' '5' '6' '7'       4           "B"                 20
    pB24      '8' '9' '\n' '7'      3           "B"                 24

These 10 processes are still sleeping at the 3 second mark, which is why the
answer for 1.2 is 10.  They all wake up approximately 4 seconds after forkherd
was first called.

Note that we've named each process after the value of pos they break out of the
loop with.  This becomes important in the next couple of lines of code, where
they each format a string using *argv and pos:

    char name[128];
    sprintf(name, "%s.%d", *argv, pos);

So, for pA0, whose *argv points to "A" and whose pos value is 0, its name buffer
will be populated with the string "A.0"; for pB8, its name buffer will contain
"B.8".

In the next loop, each one of these 10 processes will fork() some more children:

    while (1) {
        if (r == 0)
            exit(0);
        else if (fork() == 0)
            break;
        else
            r--;
    }

    sleep(r * 2);  // Sleep for r * 2 seconds

The number of children each process fork()s depends on its value of r.  For
instance, pA0 has r = 4, so it will produce 4 children, carrying r values of 4,
3, 2, and 1.  pA8, whose r = 3, will produce 3 children, carrying r values of 3,
2, and 1.  The 10 parent processes will exit() when their r reaches 0.

The total number of child processes left behind is the sum of all the process's
r values in the previous table, which is 38.  Each of these child processes have
r > 0, so they will each sleep for greater than 2 seconds.  So, at the 5 second
mark, the number of sleeping processes is 38, the answer for 1.3.

Also, at the 5 second mark, no process has created any new files yet, so the
answer to 2.1 and 2.4 is NONE (i.e., at this time, there aren't any files
beginning with "A." or "B.").

Recall that each of the 10 processes created at the 2 second mark (i.e., pA0,
pA4, pA8, pB0, pB4, pB8, pB12, pB16, pB20, and pB24) created children with
different values of r.  In particular, each one of them has a child with r = 1;
those 10 processes wake up from sleep(r * 2) 6 seconds after we started running
this demented program, and execute the last part of forkherd.c:

    FILE *f = fopen(name, "ab");  // Open in append mode
    fwrite(buf + (r - 1), 1, 1, f);
    fclose(f);  // Also flushes f before closing

    return 0;

They each fopen() name ("A.0", "A.4", etc.) in append mode---note that this
creates an empty file if it didn't already exist---and write the first byte of
buf to those files.  Each of those processes opens a different file name, so
there is no uncertainty involved here with regards to what order those writes
happen in.  For the child of pA0 where r = 1, buf still contains "0123", so the
first byte of that (i.e., pointed to by buf + (r - 1)) is '0', written to "A.0".

These 10 children then exit, bringing the number of processes down to 28; those
remaining processes have r > 1, and are still sleeping at the 7 second mark,
which is why the answer to 1.4 is 28.  Also, now that each process has created
a file according to the formatted name, we now have the files A.0, A.4, A.8,
B.0, B.4, B.8, B.12, B.16, B.20, and B.24 in the current directory, leading to
the answer for 2.2 and 2.5.  They aren't ever deleted, so the answer for 2.3 and
2.6 are the same.

At the 8 second mark, 10 more processes wake up, this time each with r = 2.
Running the same code shown above, they each fopen() their respective file, and
append the second byte of buf to each file.  Then, they terminate, bringing the
process count down to 18.

At the 9 second mark, those remaining 18 processes (with r = 3 and r = 4) are
still sleeping, leading to the answer for 1.5.  A.0 now contains the first two
bytes of A, 01, and B.8 now contains the eighth and ninth byte of B, 89, leading
to the answers for 3.1 and 3.2.

At the 10 second mark, 10 more processes wake up, with r = 3.  After they finish
writing a byte to their respective files and terminate, the process count is now
down to 8.  At 11 seconds, those 8 sleeping processes (with r = 4) lead to the
answer for 1.6; A.0 now contains three characters, 012, and B.8 contains 89a.

At the 12 second mark, the remaining 8 processes with r = 4 wake up and do their
business.  By 13 seconds, 0 processes are left (1.7), A.0 contains 0123, and
B.8 contains 89ab.  At 15 seconds, all is quiet on the Western front: there are
still 0 processes (1.8).
