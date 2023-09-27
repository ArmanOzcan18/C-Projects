Fall 2022 Final Exam: Problem 5
-------------------------------

Running
-------

To build everything, just run "make".

Then, run each executable:

  - 5.1: fork-and
  - 5.2: fork-or
  - 5.3: fork-buf


Exploring
---------

You might have a hard time reproducing the BAB output in the fork-and program.
You can make that outcome more likely by uncommenting the sleep() statement in
fork-and.c, which will let one of the child processes "randomly" sleep() for
a little longer (depending on whether the child process's PID happens to be even
or odd).
