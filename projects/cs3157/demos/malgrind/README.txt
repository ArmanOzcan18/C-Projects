Malgrind
--------

Run "make" to build all malgrind tests.


Solutions
---------

mgtest1:

    $ valgrind ./mgtest1
    GOOD

    $ valgrind ./mgtest1
    0, 1, 2, 3, 4, OOPS

mgtest2:

    $ valgrind ./mgtest2
    LEAK

    $ valgrind ./mgtest2
    1, 2, 3, -1, NULL

mgtest3:

    $ valgrind ./mgtest3
    GOOD

    $ valgrind ./mgtest3
    16, 16, 0, 1, 2, 3, -1, -1, OKAY


Explanation
-----------

MALLOC() allocates additional space on the heap to store 8 bytes before and
after the caller-requested space.  For example, MALLOC(10) leads to a memory
layout that looks something like this:

    |-- 4B -|-- 4B -|------- 10B -------|------ 8B -----|
    |    "size"     | requested buffer  |     "magic"   |
    v               v                   v               v
    +-------+-------+-------------------+---------------+
    |  10   |  10   |   uninitialized   |   0xffffffff  |
    +-------+-------+-------------------+---------------+
    ^       ^       ^                   ^
    |       |       |                   |
    |       head[1] |                   |
    head[0]         returned to user    |
    |               |                   |
    p               p + WAD             p + WAD + n

Notice that the size, reprsented as a 4B integer, is written twice to the first
8 bytes of this heap memory, i.e., the "size" portion.  Meanwhile, the "magic"
value of 0xffff (~0), i.e., a number with all ones, is written to the last
8 bytes of this heap memory.  A pointer to the middle portion is returned to the
caller, so that it may use that space like any heap-allocated buffer.

The purpose of this memory layout is to detect heap invalid writes.  In
particular, the "magic" portion at the end helps detect heap buffer overflows,
since those bytes will get overwritten during the overflow.  The duplicated size
in the "size" portion is also useful for detecting heap buffer underflows.  The
FREE() function checks for and reports on the integrity of these canary values
before free()ing the overall heap buffer.

> Which following describe the potential benefits of using MALLOC() and FREE()
> instead of the malloc() and free() functions they wrap?

Answer: D. Using MALLOC() and FREE() can help detect invalid writes, for the
reasons explained above.  FREE() also checks against free()ing NULL, which is
not strictly speaking an invalid free() (since you are technically FREE()ing
a pointer that MALLOC() returned).

None of the mgtests lead to Valgrind reporting a memory error, because they
never read from uninitialized memory, nor do they ever write to any memory
outside of what malloc() allocated for them.  It may be tempting to consider the
out-of-bounds buffer write in mgtest1 as an invalid write, but remember that
Valgrind does not know about the semantics of MALLOC(); it only knows about
memory allocated by the underlying malloc(), whose extra space tolerates small
buffer over- and underflows.

The number -1 appears in the output of mgtest2 and mgtest3 because that is the
signed (two's complement) integer interpretation of 0xffff, the first 4 bytes of
the "magic" value written at the end of the buffer allocated by MALLOC().

The number 16 appears twice in the output of mgtest3 because that's the size
written to the 8 bytes before the address returned by MALLOC().

mgtest1 leads to an OOPS because the out-of-bounds write overwrites the first
4 bytes of the magic value.  mgtest2 leads to a NULL because *a has the numeric
value of 0, and is thus a NULL pointer when cast to void *.  mgtest3 is OKAY
because it never writes out of bounds.  Note that FREE() was unable to detect
that mgtest2 and mgtest3 read out-of-bounds, since it only works with
out-of-bounds writes.
