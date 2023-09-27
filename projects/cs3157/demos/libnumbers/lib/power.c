#include "numbers.h"

int power(int x, int n) {
    int a = x;
    while (n--)
        a *= x;
    return a;
}
