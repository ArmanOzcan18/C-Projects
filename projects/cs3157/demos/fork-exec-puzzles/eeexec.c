/**
 *  eeexec
 *
 *  Solutions:
 *
 *      A 4
 *      A 3
 *      A 2
 *      A 1
 *      C 0
 *
 *  The trick to solving this problem is noticing that, unlike with fork(),
 *  calling exec() does NOT preserve the call stack; instead, exec() simply
 *  wipes the entire address of the calling process.
 *
 *  A 4 through A 1 are printed as a result of four successive calls to eeexec()
 *  with decreasing n.  On the 5th call to eeexec(), n = 0, so eeexec() returns
 *  immediately without printing anything.  The program continues to execute in
 *  the fourth stack frame of eeexec(), where n = 1.
 *
 *  The sprintf() call puts the string "0" into buf.  eeexec then exec()s itself
 *  with "0" as the argument, using execv(); this is the same as calling
 *  ./eeexec 0.  Note that exec() never returns, so the printf("B %d\n", n); is
 *  never executed.
 *
 *  On the execution of ./eeexec 0, main() calls eeexec() with n = 0, which does
 *  nothing.  Upon returning from eeexec(), main() prints C 0, and terminates,
 *  concluding the output of this program.
 */
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <assert.h>

void eeexec(char *cmd, int n) {
    if (n > 0) {
        printf("A %d\n", n);

        eeexec(cmd, n - 1);

        char buf[100];
        sprintf(buf, "%d", n - 1);

        char *a[3] = { cmd, buf, NULL };
        execv(*a, a);

        printf("B %d\n", n);
    }
}

int main(int argc, char **argv) {
    assert(argc == 2);
    eeexec(argv[0], atoi(argv[1]));
    printf("C %s\n", argv[1]);
    return 0;
}
