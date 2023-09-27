fork()/exec() Demos
-------------------

This repo contains a collection of fork()/exec() examples demonstrating how they
work and how they can be used.  As usual, run 'make' to build all examples.

Each example contains detailed comments in the source code illustrating what's
going on, but here's also a short table of contents:

  - fork-hello: a basic fork() example.
  - fork-negotiate: a fork() example demonstrating the nondeterministic
    interleaving between the concurrent parent and child processes.
  - fork-wait: an example demonstrating a parent blocking to reap its child
    using waitpid().
  - fork-wait-many: an example demonstrating a parent using waitpid() in
    non-blocking mode to periodically poll for any zombie children.
  - exec-test: an exec() example where the program exec()s itself.
  - fork-exec-echo: an example demonstrating the fork() + exec() pattern, where
    the parent waits for the child to execute the echo program.
  - fork-exec-ls: an example demonstrating the fork() + exec() pattern, where
    the parent waits for the child to execute the ls program.
  - fork-exec-myprogram: an example demonstrating the fork() + exec() pattern,
    where the parent waits for the child to execute myprogram.
  - myprogram: a program that prints its PID, PPID, and arguments.
