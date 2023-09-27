#include "fast.h"

long arith1M(void) {
    long v = 0;
    for (long i = 1; i <= 1000000; i++)
        v += i;
    return v;
}

long arith2M(void) {
    long v = 0;
    for (long i = 1; i <= 2000000; i++)
        v += i;
    return v;
}

long arith10M(void) {
    long v = 0;
    for (long i = 1; i <= 10000000; i++)
        v += i;
    return v;
}

long arith(long lim) {
    long v = 0;
    for (long i = 1; i <= lim; i++)
        v += i;
    return v;
}
