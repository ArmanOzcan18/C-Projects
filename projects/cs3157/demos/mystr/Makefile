CC = gcc
CFLAGS = -g -Wall -Wpedantic -std=c17
LDFLAGS =
LDLIBS =

mystr-test: mystr-test.o mystr.o mystr-solutions.o

mystr-test.o: mystr-test.c mystr.h

mystr.o: mystr.c mystr.h

mystr-solutions.o: mystr-solutions.c mystr.h

.PHONY: test
test: mystr-test
	./mystr-test

.PHONY: vg
vg: mystr-test
	valgrind --leak-check=yes ./mystr-test

.PHONY: clean
clean:
	rm -rf mystr-test *.o a.out
