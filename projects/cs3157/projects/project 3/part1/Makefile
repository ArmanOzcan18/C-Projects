# Same C compiler and compiler flags as before:
CC = gcc
CFLAGS = -g -Wall -Wpedantic -std=c17

# No linker flags, though these will later come in handy for the library user.
LDFLAGS =
LDLIBS =

# We will use the ar utility to create archive files from object files, so it's
# good practice to explicitly specify the "ar" command we would like to use:
AR = ar

# We can use the ARFLAGS variable to pass flags to the ar program.  For reasons
# beyond our control and beyond the scope of this course, we need to add the -U
# flag to ensure that Make doesn't try to rebuild the library archive when it
# doesn't need to.  You can read more about why we need the -U flag here:
# https://stackoverflow.com/a/73912307/10497710.
ARFLAGS += -U

# We can link archive files directly with object files; the linker command
# produced by the Make implicit rule will look something like:
#
#   gcc  mylist-test.o  libmylist.a  -o mylist-test
#
mylist-test: mylist-test.o libmylist.a

# This is the rule for building the libmylist.a archive file.  This rule says
# that the libmylist.a archive file should contain one object file---mylist.o
#---and should be updated whenever mylist.o is updated.
#
# We rely on Make's implicit rules to update libmylist.a when necessary.  The
# template recipe for the implicit rule looks something like this:
#
#   $(AR)  $(ARFLAGS)  <archive-file.a>  <member-object-file.o>
#
# Our archive rule will lead to a recipe for each of the member object files,
# which will turn out to be:
#
#   ar  rv -U  libmylist.a mylist.o
#
# The "r" flag tells ar to add mylist.o to libmylist.a with
# (r)eplacement (i.e., add it, and replace it if already present).
#
# The "v" flag tells ar to be verbose, i.e., output information about what it's
# doing.
#
# The "-U" flag tells ar to preseve timestamps for archive members; this is
# necessary so that Make doesn't try to replace archive members unnecessarily.
libmylist.a: libmylist.a(mylist.o)

# We use implicit rules to deal with object files, like before:
mylist.o: mylist.c mylist.h
mylist-test.o: mylist-test.c mylist.h

# The usual .PHONY target for cleaning up the build directory; we also delete
# any archive files built here.
.PHONY: clean
clean:
	rm -rf mylist-test *.o *.a a.out


#.PHONY: compare
#compare: 
#	./mylist-test > actualoutput.txt
#	diff actualoutput.txt mylist-test-output.txt
