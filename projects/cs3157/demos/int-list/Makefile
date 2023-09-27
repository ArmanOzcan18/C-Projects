CC = gcc
CFLAGS = -g -Wall -Wpedantic -std=c17
LDFLAGS =

int-list-test: int-list-test.o int-list.o

int-list-test.o: int-list-test.c int-list.h

int-list.o: int-list.c int-list.h

.PHONY: clean
clean:
	rm -rf *.o a.out int-list-test
