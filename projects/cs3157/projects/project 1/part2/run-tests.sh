#!/usr/bin/env bash

set -eu

mkdir -p test-output
rm -rf test-output/*

errors=0

for test in tests/*.test ; do
  test=${test%.test} # Strip off .test suffix from $test
  test=${test#tests/} # Strip off .test suffix from $test

  # echo "Arguments: $(cat tests/$test.test)"
  # echo Input:
  # cat tests/$test.in
  # echo

  echo -n "Running test case: $test ... "

  if ./wordle $(cat tests/$test.test) <tests/$test.in >test-output/$test.out 2>test-output/$test.err; then
    echo "Ok"
  else
    echo "Failed"
    errors="$((errors + 1))"
    continue
  fi

  echo -n "Comparing output:  $test ... "

  if ! [ -f tests/$test.out ]; then
    echo "No output file found"
    errors="$((errors + 1))"
    continue
  fi

  if diff test-output/$test.out tests/$test.out >/dev/null 2>/dev/null ; then
    echo "Ok"
  else
    echo "Failed"
    errors="$((errors + 1))"
  fi
done

echo
echo "Encountered $errors error(s)."

if [ "$errors" -eq 0 ]; then
  exit 0
else
  exit 1
fi
