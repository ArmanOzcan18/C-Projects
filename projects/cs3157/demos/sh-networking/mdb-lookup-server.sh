#!/bin/sh

# Get rid of mypipe if it aleady exists
rm -f mypipe

# Create myipe
mkfifo mypipe

# Print out useful information
echo Listening on port number $1

nc -l $1 < mypipe | ~j-hui/cs3157-pub/bin/mdb-lookup-cs3157 > mypipe

# NOTE: this won't run if you exit this script with Ctrl-C
rm -f mypipe
