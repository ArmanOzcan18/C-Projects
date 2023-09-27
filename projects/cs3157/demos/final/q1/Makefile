CC        = gcc
CFLAGS    = -g
LDFLAGS   = -L.
LDLIBS    = -lfg
AR        = ar
ARFLAGS  += -U

.PHONY: default
default: libfg.a fgtest
	./fgtest

fgtest: fgtest.o
fgtest.o: fgtest.c
libfg.a: libfg.a(freegrind.o)
libfg.a(freegrind.o): freegrind.o
freegrind.o: freegrind.c

.PHONY: clean
clean:
	rm -rf *.o *.a a.out fgtest
