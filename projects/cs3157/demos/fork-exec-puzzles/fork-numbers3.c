/**
 *  fork-numbers3
 *
 *  Solutions:
 *
 *    - How many lines does the program print?
 *
 *      7 lines.
 *
 *    - How many times is 0 printed?
 *
 *      0 times.
 *
 *    - How many times is 1 printed?
 *
 *      1 time.
 *
 *    - How many times is 2 printed?
 *
 *      2 times.
 *
 *    - How many times is 3 printed?
 *
 *      4 times.
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
 *      3 seconds.
 *
 *  Explanation:
 *
 */
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>

int main(int argc, char **argv) {
    if (argc != 2) {
        char *a[] = { argv[0], "1", NULL };
        execv(*a, a);
    }

    int n = atoi(argv[1]);
    if (n > 3)
        return 0;

    sleep(1);

    printf("%d\n", n);
    sprintf(argv[1], "%d", n + 1);

    pid_t pid = fork();
    execv(*argv, argv);
    if (pid) {
        waitpid(pid, NULL, 0);
        printf("%d\n", 0);
    }

    return 0;
}
