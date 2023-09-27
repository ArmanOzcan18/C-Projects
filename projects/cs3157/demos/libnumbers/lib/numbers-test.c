#include <stdio.h>

#include "numbers.h"
// ^Since this test driver is in the same directory as the library header file,
//  we can just #include "numbers.h" instead of <numbers.h> with the -I flag.

int main(void) {
    printf("2^5 = %d\n", power(2, 5));
    printf("31 is prime: %d\n", is_prime(31));
    printf("57 is prime: %d\n", is_prime(57));
    return 0;
}
