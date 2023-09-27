#include "numbers.h"

int is_prime(int x) {
    if (x < 2)
        // Neither 0 nor 1 are prime; ignore negative numbers.
        return 0;

    for (int m = 2; m < x; m++)
        if (x % m == 0)
            // x is a multiple of m; not prime.
            return 0;

    // x is not a multiple of anything; it is prime.
    return 1;
}
