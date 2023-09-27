CC = gcc

# Without compiler optimizations
CFLAGS ?= -g -Wall -Wpedantic -std=c17

LDFLAGS =
LDLIBS =

main: ilist.o ivec.o

main.o: ilist.h ivec.h
ilist.o: ilist.h
ivec.o: ivec.h

.PHONY: clean
clean:
	rm -f *.o *~ a.out core main

.PHONY: all
all: clean main
