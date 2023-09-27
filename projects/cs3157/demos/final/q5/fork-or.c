#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>

int main(void)
{
    if (fork() || fork()) {
        waitpid(-1, NULL, 0); // Wait for any child, no status, blocking
        printf("A\n");
    } else {
        printf("B\n");
    }
}
