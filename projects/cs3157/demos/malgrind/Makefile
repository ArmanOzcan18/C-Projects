CC = gcc
CFLAGS = -g -Wall -Wpedantic -std=c17
LDFLAGS =
LDLIBS =

.PHONY: default all clean
default: mgtest1 mgtest2 mgtest3
all: clean default
clean:
	rm -rf *.o a.out mgtest{1,2,3}

mgtest1: malgrind.o
mgtest2: malgrind.o
mgtest3: malgrind.o

malgrind.o:
mgtest1.o:
mgtest2.o:
mgtest3.o:
