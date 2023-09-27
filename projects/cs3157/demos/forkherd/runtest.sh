#!/usr/bin/env bash

set -e

##################
#  Proc helpers  #
##################

# Helper function to get the number of running processes associated with the
# current tty
procs () { ps -T -o "pid=" | wc -l ; }

# Establish how many processes are currently running.
baseline="$(procs)"

# Count the number of procs currently running.
# NOTE: we need extra -1 to account for the Bash subshell process...
forkherd-procs () { echo $(( $(procs) - $baseline - 1 )) ; }

##############
#  Clean up  #
##############

# Make sure these A and B exist and contain the expected contents.
echo "0123456789" > A
echo "0123456789abcdef0123456789" > B

# Clean out any leftover junk.
rm -rf A.* B.*

##############
#  Run test  #
##############

# Run forkherd in the background.
./forkherd A B &

sleep 1
echo "#### 1 second after executing forkherd... ####"

echo "1.1 Number of forkherd processes: $(forkherd-procs)"

echo
sleep 2
echo "#### 3 seconds after executing forkherd... ####"

echo "1.2 Number of forkherd processes: $(forkherd-procs)"

echo
sleep 2
echo "#### 5 seconds after executing forkherd... ####"

echo "1.3 Number of forkherd processes: $(forkherd-procs)"

echo -n "2.1 Output of \"ls A.*\": "
if find A.* -quit >/dev/null 2>&1 ; then
    ls -x A.*
else
    echo "NONE"
fi

echo -n "2.4 Output of \"ls B.*\": "
if find B.* -quit >/dev/null 2>&1 ; then
    ls -x B.*
else
    echo "NONE"
fi

echo
sleep 2
echo "#### 7 seconds after executing forkherd... ####"

echo "1.4 Number of forkherd processes: $(forkherd-procs)"

echo -n "2.2 Output of \"ls A.*\": "
if find A.* -quit >/dev/null 2>&1 ; then
    ls -x A.*
else
    echo "NONE"
fi

echo -n "2.4 Output of \"ls B.*\": "
if find B.* -quit >/dev/null 2>&1 ; then
    ls -x B.*
else
    echo "NONE"
fi

echo
sleep 2
echo "#### 9 seconds after executing forkherd... ####"

echo "1.5 Number of forkherd processes: $(forkherd-procs)"

echo -n "2.3 Output of \"ls A.*\": "
if find A.* -quit >/dev/null 2>&1 ; then
    ls -x A.*
else
    echo "NONE"
fi

echo -n "2.6 Output of \"ls B.*\": "
if find B.* -quit >/dev/null 2>&1 ; then
    ls -x B.*
else
    echo "NONE"
fi

echo "3.1 Output of \"cat A.0\": $(cat A.0)"

echo "3.4 Output of \"cat B.8\": $(cat B.8)"

echo
sleep 2
echo "#### 11 seconds after executing forkherd... ####"

echo "1.6 Number of forkherd processes: $(forkherd-procs)"

echo "3.2 Output of \"cat A.0\": $(cat A.0)"

echo "3.5 Output of \"cat B.8\": $(cat B.8)"

echo
sleep 2
echo "#### 13 seconds after executing forkherd... ####"

echo "1.7 Number of forkherd processes: $(forkherd-procs)"

echo "3.3 Output of \"cat A.0\": $(cat A.0)"

echo "3.6 Output of \"cat B.8\": $(cat B.8)"

echo
sleep 2
echo "#### 15 seconds after executing forkherd... ####"

echo "1.8 Number of forkherd processes: $(forkherd-procs)"
