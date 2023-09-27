# As usual, we define the C compiler we would like to use:
CC = gcc

# In addition to the usual C compilation flags, we also write -I../lib to tell
# the C compiler to look in ../lib for header files.  This is what allows us to
# #include <numbers.h>.
CFLAGS = -g -Wall -Wpedantic -std=c17 -I../lib

# We pass the -L../lib flag to the linker to tell it to look in ../lib for
# library archive files.  This is what allows us to use -lnumbers.
LDFLAGS = -L../lib

# We also give the linker the -lnumbers flag to tell it to look in libnumbers.a
# for missing symbol definitions.
LDLIBS = -lnumbers

# Note that there are two separate Make variables used to configure the linker:
# LDFLAGS and LDLIBS.  This is because for historical reasons, LDFLAGS needs to
# be appear before object files, whereas LDLIBS needs to appear afterwards.
# The implicit rule for linking looks like this:
#
#     $(CC)  $(LDFLAGS)  <objects>  -o <output-name>  $(LDLIBS)
#
# So, with the above variables, the linking command that is run will be:
#
#     gcc  -L../lib  numbers-program.o  -o numbers-program  -lnumbers
#
numbers-program: numbers-program.o

numbers-program.o: numbers-program.c

.PHONY: clean
clean:
	rm -rf numbers-program *.o a.out
