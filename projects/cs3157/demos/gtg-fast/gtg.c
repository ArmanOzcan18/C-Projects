#define _GNU_SOURCE
#include <assert.h>
#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <time.h>
#include <unistd.h>

#include "fast.h"

// Convert timespec to double-precision floating point number, in nanoseconds.
#define ts2double(ts) ((double)(ts).tv_sec * 1000000000. + (double)(ts).tv_nsec)

static void die(const char *msg) {
    perror(msg);
    exit(1);
}

int main(int argc, char **argv) {

    const char *spec;
    long result;
    struct timespec before, after, duration;

    if (argc < 2)
      goto do_nothing;

    switch (argv[1][0]) {

      case 'a':
        spec = "arith1M()";
        if (clock_gettime(CLOCK_MONOTONIC, &before) < 0)
            die("clock_gettime");

        result = arith1M();

        if (clock_gettime(CLOCK_MONOTONIC, &after) < 0)
            die("clock_gettime");

        break;

      case 'b':
        spec = "arith2M()";

        if (clock_gettime(CLOCK_MONOTONIC, &before) < 0)
            die("clock_gettime");

        result = arith2M();

        if (clock_gettime(CLOCK_MONOTONIC, &after) < 0)
            die("clock_gettime");

        break;

      case 'c':
        spec = "arith10M()";

        if (clock_gettime(CLOCK_MONOTONIC, &before) < 0)
            die("clock_gettime");

        result = arith10M();

        if (clock_gettime(CLOCK_MONOTONIC, &after) < 0)
            die("clock_gettime");

        break;

      case 'A':
        spec = "arith(1000000)";

        if (clock_gettime(CLOCK_MONOTONIC, &before) < 0)
            die("clock_gettime");

        result = arith(1000000);

        if (clock_gettime(CLOCK_MONOTONIC, &after) < 0)
            die("clock_gettime");

        break;

      case 'B':
        spec = "arith(2000000)";

        if (clock_gettime(CLOCK_MONOTONIC, &before) < 0)
            die("clock_gettime");

        result = arith(2000000);

        if (clock_gettime(CLOCK_MONOTONIC, &after) < 0)
            die("clock_gettime");

        break;

      case 'C':
        spec = "arith(10000000)";

        if (clock_gettime(CLOCK_MONOTONIC, &before) < 0)
            die("clock_gettime");

        result = arith(10000000);

        if (clock_gettime(CLOCK_MONOTONIC, &after) < 0)
            die("clock_gettime");

        break;

      default:
      do_nothing:
        spec = "do nothing";

        if (clock_gettime(CLOCK_MONOTONIC, &before) < 0)
            die("clock_gettime");

        result = 0;

        if (clock_gettime(CLOCK_MONOTONIC, &after) < 0)
            die("clock_gettime");

        break;
    }

    duration.tv_sec = after.tv_sec - before.tv_sec;
    duration.tv_nsec = after.tv_nsec - before.tv_nsec;

    printf("Scenario: %s\n", spec);
    printf("Result: %ld\n", result);
    printf("Duration: %.3lfus\n", ts2double(duration) / 1000.);

    return 0;
}
