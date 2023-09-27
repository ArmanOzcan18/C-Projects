#!/usr/bin/env bash

run () {
    msg="$1"
    shift
    echo "---- $@ ----"
    if ! eval "$@" ; then
        echo
        echo ">>>> $msg <<<<"
        echo
        return 1
    else
        echo
        return 0
    fi
}

do_test () {
    local fgn="$1"
    echo "==== Testing $fgn ===="
    echo

    run "$fgn: COMPILE FGTEST ERROR" gcc -c "$fgn.c" -o "$fgn.o" || return
    run "$fgn: COMPILE FREEGRIND ERROR" gcc -c freegrind.c -o freegrind.o || return
    run "$fgn: LINK ERROR" gcc "$fgn.o" freegrind.o -o "$fgn" || return
    run "$fgn: RUNTIME ERROR" valgrind "./$fgn" ">$fgn.out" "2>/dev/null" || return
    if ! diff fgtest.out "$fgn.out" >/dev/null ; then
        echo ">>> $fgn: DIFFERENT OUTPUT <<<"
    else
        echo ">>> $fgn: SAME OUTPUT <<<"
    fi
}

echo "==== Setup (building and running original fgtest) ===="
echo
run "UNEXPECTED COMPILE FGTEST ERROR" gcc -c fgtest.c -o fgtest.o
run "UNEXPECTED COMPILE FREEGRIND ERROR" gcc -c freegrind.c -o freegrind.o
run "UNEXPECTED LINK ERROR" gcc fgtest.o freegrind.o -o fgtest
run "UNEXPECTED RUNTIME ERROR" valgrind ./fgtest ">fgtest.out" "2>/dev/null"

for i in fgtest{1..6} ; do
    do_test "$i"
    echo
done
