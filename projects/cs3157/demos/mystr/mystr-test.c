#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "mystr.h"

// Print helper because I'm lazy.
void println(const char *s) {
    printf("[TEST] %s\n", s);
}

int main(void) {
    println("Creating a set of mystrs...");
    struct mystr *hello = mystr_new("hello");
    struct mystr *space = mystr_new(" ");
    struct mystr *world = mystr_new("world");
    struct mystr *empty = mystr_new("");
    struct mystr *whoa = mystr_new("!");
    struct mystr *newline = mystr_new("\n");

    println("The following should print 'hello world!\\n'. Here it comes:");
    mystr_print(hello);
    mystr_print(space);
    mystr_print(world);
    mystr_print(empty);
    mystr_print(whoa);
    mystr_print(newline);

    // Testing equals() and copy()...

    println("Creating a new mystr hello2 that just says 'hello'...");
    struct mystr *hello2 = mystr_new("hello");

    println("Here it is:");
    mystr_print(hello2);
    mystr_print(newline);

    println("Checking that 'hello' == 'hello'...");
    assert(mystr_equals(hello, hello2));

    println("Double-checking that 'hello' == 'hello'...");
    assert(mystr_equals(hello2, hello));

    println("Checking that 'hello' != 'world'...");
    assert(!mystr_equals(hello, world));

    println("Checking that '' == ''...");
    assert(mystr_equals(empty, empty));

    println("Making copy of hello2...");
    struct mystr *hello2_copy = mystr_copy(hello2);

    println("Checking copy of 'hello' still equal to hello2...");
    assert(mystr_equals(hello2, hello2_copy));

    println("Destroying hello2...");
    mystr_delete(hello2);

    println("Checking copy of 'hello' still equal to original 'hello'...");
    assert(mystr_equals(hello, hello2_copy));

    println("Destroying hello2's copy...");
    mystr_delete(hello2_copy);

    // Now testing append() and truncate()

    println("Building one big mystr s from an empty one...\n");
    struct mystr *s = mystr_new("");

    println("Here is s now (should say ''):");
    mystr_print(s);
    mystr_print(newline);

    println("Appending 'hello'...");
    mystr_append(s, hello);

    println("Here is s now (should say 'hello'):");
    mystr_print(s);
    mystr_print(newline);

    println("Appending ' ' and 'world'...");
    mystr_append(s, space);
    mystr_append(s, world);

    println("Here is s now (should say 'hello world'):");
    mystr_print(s);
    mystr_print(newline);

    println("Appending '!', '!', and '\\n'...");
    mystr_append(s, whoa);
    mystr_append(s, whoa);
    mystr_append(s, newline);

    println("Here is s now (should say 'hello world!!\\n'):");
    mystr_print(s);
    mystr_print(newline);

    println("Dropping 'hello ' from s...");
    mystr_truncate(s, 6, s->len);

    println("Here is s now (should say 'world!!\\n'):");
    mystr_print(s);
    mystr_print(newline);

    println("Dropping '!!\\n' from s...");
    mystr_truncate(s, 0, 5);

    println("Here is s now (should say 'world'):");
    mystr_print(s);
    mystr_print(newline);

    println("Dropping the rest of the characters from s...");
    mystr_truncate(s, s->len, s->len);

    println("Checking that s is indeed empty now...");
    assert(mystr_equals(s, empty));

    println("Deleting s...");
    mystr_delete(s);

    println("Deleting the rest of the strings...");
    mystr_delete(hello);
    mystr_delete(space);
    mystr_delete(world);
    mystr_delete(empty);
    mystr_delete(whoa);
    mystr_delete(newline);

    println("All tests passed.");
    return 0;
}
