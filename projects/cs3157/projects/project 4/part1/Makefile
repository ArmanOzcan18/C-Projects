CC = gcc
CFLAGS = -g -Wall -Wpedantic -std=c17 -I/home/j-hui/cs3157-pub/include

LDFLAGS = -L/home/j-hui/cs3157-pub/lib
LDLIBS = -lmylist

mdb-lookup: mdb-lookup.o
mdb-lookup.o: mdb-lookup.c mdb.h

.PHONY: clean
clean:
	rm -f *.o *~ a.out core mdb-lookup

.PHONY: all
all: clean mdb-lookup
