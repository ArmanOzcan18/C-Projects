Make Tutorial
-------------

The Makefile in this repository is heavily commented and self-documenting.
Please read it to learn about the syntax and basic features of Makefiles.

You can run Make in any directory with a Makefile.  For example, in this
directory:

    $ make
    gcc -g -Wall -Wpedantic -std=c17   -c -o myprogram.o myprogram.c
    gcc -g -Wall -Wpedantic -std=c17   -c -o myadd.o myadd.c
    gcc -g -Wall -Wpedantic -std=c17   -c -o mymod.o mymod.c
    gcc   myprogram.o myadd.o mymod.o   -o myprogram

Make prints out the commands that it runs.  Run ls to confirm that these
commands successfully produced myprogram.o, myadd.o, mymod.o, and myprogram.

Note that Make builds myprogram because that is the first target in the
Makefile; it builds myprogram.o, myadd.o, and mymod.o because they are
dependencies of myprogram.

If you run make again, it won't do anything, since the timestamp of myprogram is
later than its dependencies (the .o files).

    $ make
    make: 'myprogram' is up to date.

We can use the touch command (man touch) to update the timestamp of a dependency
and trick Make into rebuilding myprogram:

    $ touch myadd.c     # update time stamp of myadd.c
    $ make
    gcc -g -Wall -Wpedantic -std=c17   -c -o myadd.o myadd.c
    gcc   myprogram.o myadd.o mymod.o   -o myprogram

We can also force Make to rebuild everything using "make all", which first
cleans up all build artifacts, before building everything again:

    $ make all
    rm -f *.o a.out core myprogram
    gcc -g -Wall -Wpedantic -std=c17   -c -o myprogram.o myprogram.c
    gcc -g -Wall -Wpedantic -std=c17   -c -o myadd.o myadd.c
    gcc -g -Wall -Wpedantic -std=c17   -c -o mymod.o mymod.c
    gcc   myprogram.o myadd.o mymod.o   -o myprogram
