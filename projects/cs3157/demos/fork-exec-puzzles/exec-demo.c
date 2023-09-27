/**
 *  exec-demo
 *
 *  Solution:
 *
 *      $ ./exec-demo 4 100
 *      110
 *
 *  Explanation:
 *
 *      First, note that the printf() statement after execv() is unreachable,
 *      because execv() does not return.  We can ignore that print statement
 *      altogether.
 *
 *      This program executes itself, but with different arguments each time,
 *      until the first argument (n1) reaches zero.  When n1 is non-zero,
 *      it uses atoi() to convert each argument into integers, performs some
 *      arithmetic, and converts the results back into strings with sprintf().
 *      Then, it uses those computed to perform the recursive call.
 *
 *      Logically, it works similar to this recursive function:
 *
 *          int exec_func(int n1, int n2) {.
 *              if (n1 > 0)
 *                  exec_func(n1 - 1, n2 + n1);
 *              else
 *                  return n2;
 *          }
 *
 *      At each iteration, it decrements the first argument, and adds the first
 *      argument to the second argument, until the first argument reaches zero.
 *      Thus, exec-demo is executed a total of 4 times, like this:
 *
 *          ./exec-demo 4 100     # from command line
 *          ./exec-demo 3 104
 *          ./exec-demo 2 107
 *          ./exec-demo 1 109
 *          ./exec-demo 0 110
 *
 *      At the last iteration, exec-demo simply prints the integer value of the
 *      second argument, printing "110".
 */
#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <unistd.h>

int main(int argc, char **argv) {
    assert(argc == 3);

    int n1 = atoi(argv[1]);
    int n2 = atoi(argv[2]);

    if (n1 > 0) {
        char s1[100]; sprintf(s1, "%d", n1 - 1);  argv[1] = s1;
        char s2[100]; sprintf(s2, "%d", n2 + n1); argv[2] = s2;
        execv(*argv, argv);
        printf("%d\n", n1);
    }
    printf("%d\n", n2);
    return 0;
}
