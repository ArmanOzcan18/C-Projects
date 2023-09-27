#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <assert.h>

int main(int argc, char **argv) {
    while (1) {
        if (*++argv == NULL) {
            exit(0);
        } else if (fork() == 0) {
            // Child process
            break;
        } else {
            // Parent process
            continue;
        }
    }

    sleep(2);  // Sleep for 2 seconds

    char buf[4];
    int pos = 0;
    int r;
    while (1) {
        FILE *f = fopen(*argv, "rb");
        assert(f);

        fseek(f, pos, SEEK_SET);
        r = fread(buf, 1, sizeof(buf), f);
        fclose(f);

        if (r == 0) {
            exit(0);
        } else if (fork() == 0) {
            break;
        } else {
            pos += r;
        }
    }

    sleep(2);  // Sleep for 2 seconds

    char name[128];
    sprintf(name, "%s.%d", *argv, pos);

    while (1) {
        if (r == 0) {
            exit(0);
        } else if (fork() == 0) {
            break;
        } else {
            r--;
        }
    }

    sleep(r * 2);  // Sleep for r * 2 seconds

    FILE *f = fopen(name, "ab");  // Open in append mode
    fwrite(buf + (r - 1), 1, 1, f);
    fclose(f);  // Also flushes f before closing

    return 0;
}
