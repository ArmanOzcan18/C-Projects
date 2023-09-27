// Multiplying by 2^n is the same as bit-shifting to the left by n;
// 8 is 2^3, so x * 8 is the same as x << 3.
// Also note that dividing 2^n is the same as bit-shifting to the right by n.
#define ANSWER_3_1_1      x << 3

// 0x1 looks like 0000.....0001 in binary; bitwise ORing it with x set the LSB
// to 1, and leaves the other bits untouched.
#define ANSWER_3_1_2      x | 0x1

// To determine if a signed two's complement integer is negative, we just need
// to test its MSB.  We construct a bitmask that looks like 1000...0000 by
// left-shifting 0x1 by 31 (i.e., 1 less than the size of x in bits).
// sizeof(x) gives us the size of x in bytes, so we need to multiply it by
// 8 (equivalently, bit-shift left by 3) to obtain its size in bits.
#define ANSWER_3_1_3      x & (0x1 << ((sizeof(x) << 3) - 1))

// To set the nth bit of x to 1, create a bitmask with the nth bit as 1 and
// 0 everywhere else, and bit-wise OR it with x.
#define ANSWER_3_1_4      x | (0x1 << n)

// To set the nth bit of x to 0, create a bitmask where all the bits are
// 1 except for the nth bit, and bit-wise AND it with x.
#define ANSWER_3_1_5      x & ~(0x1 << n)
