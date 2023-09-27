#include <stdio.h>

#include <numbers.h>
// ^Since numbers.h is not in the same directory, we #include <numbers.h> and
//  rely on the -I flag to specify the right search path.

int main(void) {
    printf("5^3 = %d\n", power(5, 3));
    printf("363 is prime: %d\n", is_prime(363));
    return 0;
}
