/**
 *  fffork
 *
 *  Solutions:
 *
 *      7410
 *      520
 *      30
 *
 *  The trick to solving this problem is understanding that when a process
 *  fork()s, its entire call stack is duplicated as well.  This detail matters
 *  for this program because fffork() is called recursively, so EACH prcoess
 *  will print while "rolling up" the stack.
 *
 *  As the program unfolds, child processes accumulate more of the recursive
 *  fffork() call stack, illustrated by the following table, which depicts the
 *  state of each process at the deepest point of recursion:
 *
 *      Process tree         PID    i     a    a_1   a_2   a_3
 *      -------------------------------------------------------
 *      fffork __o.......... 2000   3   "123"
 *       \_ fffork __o...... 2001   2   "456" "123"
 *           \_ fffork __o.. 2002   1   "789" "456" "123"
 *               \_ fffork _ 2003   0   NULL  "789" "456" "123"
 *
 *  The column named "a" represents what a points to in the current fffork()
 *  stack frame; "a_1" represents what a points to in the previous stack frame;
 *  "a_2" is the stack frame before that; "a_3" is the stack frame before that.
 *  Also note that only process with PID 2003 is executing at this point of
 *  fffork's execution; all its ancestors are blocked on their waitpid() calls,
 *  illustrated by the "o....".
 *
 *  fffork() returns immediately when *a is a NULL pointer, so we pop a stack
 *  frame off the stack:
 *
 *      Process tree         PID    i     a    a_1   a_2   a_3
 *      -------------------------------------------------------
 *      fffork __o.......... 2000   3   "123"
 *       \_ fffork __o...... 2001   2   "456" "123"
 *           \_ fffork __o.. 2002   1   "789" "456" "123"
 *               \_ fffork _ 2003   0   "789" "456" "123"
 *
 *  It's at this point in time when the first byte is printed, from:
 *
 *      print_char(a[0][i]);
 *
 *  This statement is executed by PID 2003.
 *
 *  This is the process tree that the question asks you to draw, omitting the
 *  prior stack frames and the extra "o...." notation:
 *
 *      Process tree         PID    i     a
 *      -------------------------------------
 *      fffork               2000   3   "123"
 *       \_ fffork           2001   2   "456"
 *           \_ fffork       2002   1   "789"
 *               \_ fffork   2003   0   "789"
 *
 *  At this point, PID's a points to "789" and i is 0, so the a[0][i] PID 2003
 *  prints is '7'.  PID 2003 continues to roll up the fffork() call stack:
 *
 *      Process tree         PID    i     a    a_1   a_2   a_3
 *      -------------------------------------------------------
 *      fffork __o.......... 2000   3   "123"
 *       \_ fffork __o...... 2001   2   "456" "123"
 *           \_ fffork __o.. 2002   1   "789" "456" "123"
 *               \_ fffork _ 2003   0   "456" "123"
 *
 *  printing '4'; then:
 *
 *      Process tree         PID    i     a    a_1   a_2   a_3
 *      -------------------------------------------------------
 *      fffork __o.......... 2000   3   "123"
 *       \_ fffork __o...... 2001   2   "456" "123"
 *           \_ fffork __o.. 2002   1   "789" "456" "123"
 *               \_ fffork _ 2003   0   "123"
 *
 *  printing '1'; then:
 *
 *      Process tree         PID    i     a    a_1   a_2   a_3
 *      -------------------------------------------------------
 *      fffork __o.......... 2000   3   "123"
 *       \_ fffork __o...... 2001   2   "456" "123"
 *           \_ fffork __o.. 2002   1   "789" "456" "123"
 *               \_ fffork x 2003   0
 *
 *  returns from fffork(), main(), and terminates.  To summarize, PID 2003
 *  printed '7', '4', and '1'.
 *
 *  PID 2003's termation unblocks PID 2002:
 *
 *      Process tree         PID    i     a    a_1   a_2   a_3
 *      -------------------------------------------------------
 *      fffork __o.......... 2000   3   "123"
 *       \_ fffork __o...... 2001   2   "456" "123"
 *           \_ fffork __o._ 2002   1   "789" "456" "123"
 *
 *  It continues executing after the waitpid() call, in the else branch of
 *  fffork(), printing '0' and '\n' before returning from the current fffork()
 *  stack frame:
 *
 *      Process tree         PID    i     a    a_1   a_2   a_3
 *      -------------------------------------------------------
 *      fffork __o.......... 2000   3   "123"
 *       \_ fffork __o...... 2001   2   "456" "123"
 *           \_ fffork __o._ 2002   1   "456" "123"
 *
 *  Keep in mind that when PID 2002 returns, it returns to the "then" (not else)
 *  branch of the stack frame, where the recursive call was made.  Here a points
 *  to "456" and i is 1, so PID 2002 prints '5', returns from fffork(), prints
 *  '2', returns from fffork(), returns from main(), and terminates.  To
 *  summarize, PID 2002 has printed '0', '\n', '5', and '2'.
 *
 *  PID 2001 unblocks now behaves the same as PID 2002, though it starts with
 *  one less stack frame, and with i = 2.  So it prints '0', '\n', '3', and
 *  terminates.  PID 2000 finally unblocks, and prints '0' and '\n'.
 *
 *  To put it all together, this program outputted the byte sequence '7', '4',
 *  '1', '0', '\n', '5', '2', '0' '\n', '3', '0', '\n', which looks like this in
 *  the terminal:
 *
 *      7410
 *      520
 *      30
 */
#include <stdio.h>
#include <unistd.h>
#include <sys/wait.h>

void print_char(char c) {
    fwrite(&c, 1, 1, stderr);
}

static int i = 3;

void fffork(char **a) {
    if (*a) {
        pid_t pid = fork();
        if (pid == 0) {
            // child process
            i--;
            fffork(a + 1);
            print_char(a[0][i]);
        } else {
            // parent process
            waitpid(pid, NULL, 0); // no status & no options
            print_char('0');
            print_char('\n');
        }
    }
}

int main(void) {
    char *a[4] = { "123", "456", "789", NULL };
    fffork(a);
    return 0;
}
