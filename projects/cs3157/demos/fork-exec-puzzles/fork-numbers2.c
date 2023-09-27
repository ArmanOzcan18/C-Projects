/**
 *  fork-numbers2
 *
 *  Solutions:
 *
 *    - How many lines does the program print?
 *
 *      8 lines.
 *
 *    - How many times is 0 printed?
 *
 *      1 times.
 *
 *    - How many times is 1 printed?
 *
 *      3 time.
 *
 *    - How many times is 2 printed?
 *
 *      3 times.
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
 *      No.
 *
 *    - How long does the program take to execute?
 *
 *      2 seconds.
 *
 *  Explanation:
 *
 *      There's two ways to solve this: stepping through each statement in full
 *      detail, or trying to solve it at a high level.  This explanation will
 *      take the latter approach and identify the high-level patterns you should
 *      be aware of, but you should always systematically step through the
 *      program by hand to double-check your solution!
 *
 *      The first thing to note is that the program calls fork() three times.
 *      Each call to fork() produces a parent and child, doubling the number of
 *      processes, so there will be 2^3 = 8 concurrent processes after all
 *      fork() calls.  The process tree will look something like this (with
 *      arbitrarily chosen PIDs):
 *
 *          PID 2000              # Original process
 *          |_  PID 2001          # Produced by first fork() of 2000
 *          |   |_  PID 2002      # Produced by second fork() of 2001
 *          |   |   |_  PID 2003  # Produced by third fork() of 2002
 *          |   |_  PID 2004      # Produced by third fork() of 2001
 *          |_  PID 2005          # Produced by second fork() of 2000
 *          |   |_  PID 2006      # Produced by third fork() of 2005
 *          |_  PID 2007          # Produced by third fork() of 2000
 *
 *      (If you find this diagram confusing, I recommend drawing out this
 *      process tree yourself in a different orientation to make sure you
 *      understand its structure.)
 *
 *      That process tree is produced by the following timeline of fork()s:
 *
 *                  1st fork()        2nd fork()        3rd fork()
 *
 *          PID 2000__________PID 2000__________PID 2000__________PID 2000
 *                  \                 \                 \_________PID 2004
 *                   \                 \________PID 2002__________PID 2002
 *                    \                                 \_________PID 2005
 *                     \______PID 2001__________PID 2001__________PID 2001
 *                                    \                 \_________PID 2006
 *                                     \________PID 2003__________PID 2003
 *                                                      \_________PID 2007
 *
 *      The return values of each fork() call are saved in variables p1, p2,
 *      and p3.  Since fork() returns zero to the child and non-zero to the
 *      parent, those variables now indicate whether the process was the parent
 *      or the child from the corresponding fork() call.  Note that we only care
 *      whether p1, p2, and p3 are non-zero here because, if we peek ahead, we
 *      can see that they are only used to compare against zero (e.g., p1 != 0).
 *
 *      For instance, the original process PID 2000 will receive non-zero return
 *      values for p1, p2, and p3, since at each fork(), it is the parent
 *      process to the newly spawned child.  Meanwhile, its third child PID 2007
 *      will inherit the same non-zero values for p1 and p2, but receive a zero
*       value for p3 due to it being the child process created by the third
*       fork().
 *
 *      It may be helpful to notice that the return values p1, p2, and p3 also
 *      correspond to that process's position in the process tree:
 *
 *
 *          PID 2000              # p1 != 0, p2 != 0, p3 != 0
 *          |_  PID 2001          # p1 == 0, p2 != 0, p3 != 0
 *          |   |_  PID 2002      # p1 == 0, p2 == 0, p3 != 0
 *          |   |   |_  PID 2003  # p1 == 0, p2 == 0, p3 == 0
 *          |   |_  PID 2004      # p1 == 0, p2 != 0, p3 == 0
 *          |_  PID 2005          # p1 != 0, p2 == 0, p3 != 0
 *          |   |_  PID 2006      # p1 != 0, p2 == 0, p3 == 0
 *          |_  PID 2007          # p1 != 0, p2 != 0, p3 == 0
 *
 *      (Once again, redrawing this process tree in a different orientation may
 *      help you better visualize the relationship between the fork() return
 *      values and the tree structure.)
 *
 *      x is assigned the number of non-zero return values from fork(), so we
 *      can simply count these up and find that:
 *
 *        - one process with three non-zero return values
 *          (PID 2000);
 *
 *        - three processes with a two non-zero return value
 *          (PIDs 2001, 2005, and 2007);
 *
 *        - three processes with a one non-zero return value
 *          (PIDs 2002, 2004, and 2006);
 *
 *        - one process whose return values are all zero
 *          (PID 2003).
 *
 *      The value of x is printed out by each program, leading to our answer.
 *      (Those mathematically inclined may notice that this distribution
 *      corresponds to the third row of Pascal's triangle.)  These processes
 *      will always print these same 8 lines, but since they execute
 *      concurrently, the order in which they print each line of x is not
 *      deterministic and may differ from run to run.
 *
 *      Note that so far, we have ignored the sleep() statements in our
 *      discussion.  Since the same control flow is duplicated across all of
 *      these resulting processes, each process sleep()s for 1 second, twice.
 *      They each complete execution after approximately 2s, and since time
 *      elapsed from concurrent sleep() statements do not add up, the overall
 *      execution time is also just 2s.
 */
#include <stdio.h>
#include <unistd.h>

int main(void) {
    int p1, p2, p3, x;
    p1 = fork(); sleep(1); p2 = fork(); sleep(1); p3 = fork();
    x = (p1 != 0) + (p2 != 0) + (p3 != 0);
    printf("%d\n", x);
    return 0;
}
