Command-line demos
------------------

A collection of command-line implementations, showcasing the fork() + exec()
pattern, non-blocking waitpid(), and signal handlers.

Run "make" to build the following programs:

  - jsh-basic: a bare-bones shell implementation; showcases fork() + exec().

  - jsh: a usable shell implementation (supports cd and command-line arguments);
    also showcases fork() + exec(), but is slightly more complicated.

  - jsh-io: a "real" shell implementation that also supports pipes, file
    redirection, and ignoring SIGINT.  Give it a try!

Common helper functions for parsing the command-line buffer are defined in
cmdline.c, primarily because string parsing is ugly and I didn't want that to
distract from the main loop logic of each program.
