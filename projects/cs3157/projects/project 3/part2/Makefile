# As usual, we define the C compiler we would like to use:
CC = gcc

# In addition to the usual C compilation flags, we also write -I../part1 to tell
# the C compiler to look in ../part1 for header files.  This is what allows us to
# #include <mylist.h>.
CFLAGS = -g -Wall -Wpedantic -std=c17 -I../part1

# We pass the -L../part1 flag to the linker to tell it to look in ../part1 for
# library archive files.  This is what allows us to use -lmylist.
LDFLAGS = -L../part1

# We also give the linker the -lmylist flag to tell it to look in libmylist.a
# for missing symbol definitions.
LDLIBS = -lmylist

# Note that there are two separate Make variables used to configure the linker:
# LDFLAGS and LDLIBS.  This is because for historical reasons, LDFLAGS needs to
# be appear before object files, whereas LDLIBS needs to appear afterwards.
# The implicit rule for linking looks like this:
#
#     $(CC)  $(LDFLAGS)  <objects>  -o <output-name>  $(LDLIBS)
#
# So, with the above variables, the linking command that is run will be:
#
#     gcc  -L../part1  revecho.o  -o revecho  -lmylist
#
revecho: revecho.o

revecho.o: revecho.c

.PHONY: clean
clean:
	rm -rf revecho *.o a.out
