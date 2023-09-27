/**
 *  fork-numbers1
 *
 *  Solutions:
 *
 *    - How many lines does the program print?
 *
 *      3 lines.
 *
 *    - How many times is 0 printed?
 *
 *      0 times.
 *
 *    - How many times is 1 printed?
 *
 *      2 time.
 *
 *    - How many times is 2 printed?
 *
 *      0 times.
 *
 *    - How many times is 3 printed?
 *
 *      1 times.
 *
 *    - How many times is 4 printed?
 *
 *      0 times.
 *
 *    - Is order of the printed lines always the same?
 *
 *      Yes.
 *
 *    - How long does the program take to execute?
 *
 *      4 seconds.
 *
 *  Explanation:
 *
 *      The program starts by calling fork(), producing a child process running
 *      the same program.  fork() returns a non-zero PID to the parent, who
 *      enters the if-statement, and calls waitpid() to block until the child
 *      terminates.
 *
 *      In the meantime, fork() returns zero to the child, so the child does not
 *      enter the if-statement.  It sleeps for 2 seconds, prints "1", and exits.
 *
 *      At this point (i.e., 2 seconds later), the parent unblocks from
 *      waitpid() and prints "3".  It continues executing the statements after
 *      the if-statement (the same statements its child had executed earlier),
 *      sleeping another 2 seconds before printing another "1".
 *
 *      All in all, this leads to the following output (with times annotated):
 *
 *          $ ./fork-numbers1
 *          1           # Printed 2 seconds after start time
 *          3           # Printed 2 seconds after start time
 *          1           # Printed 4 seconds after start time
 *
 *      Note that the behavior of this program is deterministic (i.e., the
 *      output never changes) because the parent and child never try to print
 *      things at the same time; the parent blocks on waitpid() until its
 *      terminates, essentially synchronizing itself agains the termination of
 *      its child.
 */
#include <stdio.h>
#include <unistd.h>
#include <sys/wait.h>

int main(void) {
    pid_t pid = fork();
    if (pid) {
        // Parent process
        waitpid(pid, NULL, 0);
        printf("3\n");
    }
    sleep(2);
    printf("1\n");
    return 0;
}
