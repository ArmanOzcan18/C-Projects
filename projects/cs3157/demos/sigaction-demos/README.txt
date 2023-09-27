sigaction() Demos
-----------------

This repo contains a collection of sigaction() examples demonstrating how
processes can configure their signal handlers.  As usual, run 'make' to build.

Each example contains detailed comments in the source code illustrating what's
going on, but here's also a short table of contents:

  - sigint-ignore: a toy example demonstrating how to ignore a signal.

  - sigint-handler: a toy example demonstrating a basic signal handler function.

  - sigchld-handler: a toy example demonstrating using SIGCHLD to automatically
    reap two children.

  - parenting: a demo demonstrating how SIGCHLD can be used to automatically
    reap any number of children while reading from user input.
