/**
 *  myprogram
 *
 *  A simple program that prints its PID, PPID, and arguments.
 *
 *  Used in the fork-exec-myprogram example.
 */
#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>

int main(int argc, char **argv) {
    printf("Hello! This is just a simple test program.\n\n");
    printf("My PID is %d and my PPID is %d\n\n", getpid(), getppid());
    printf("I was passed %d argument(s).\n", argc);
    for (int i = 0; i < argc; i++)
        printf("    argv[%d]: %s\n", i, argv[i]);
    return 0;
}
