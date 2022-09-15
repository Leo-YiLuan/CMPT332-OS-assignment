# NAME: Matthew Munro
# NSID: mam552
# STUDENT NUMBER: 11291769
# NAME: Li Yuan
# NSID: yil160
# STUDENT NUMBER: 11253856
# CMPT 332 2022
# A1 Phase 1

#!/bin/bash

if [ -z $1 ]
then
    printf "Error: Provide an argument., eg: ./partB.bash <executable>\n"
    exit 0
fi

# Test to confirm the argument given corresponds to a real binary.
case $1 in
    partA1)
    ;;
    partA2)
    ;;
    partA3)
    ;;
    partA4)
    ;;
    *)
        printf "Error: Argument $1 failed to match any known executables\n"
        exit 0
esac 

# Validate we are on correct platform for partA1
if [ "$1" = "partA1" ] & [ "$OS" != "Windows_NT" ]
then 
    printf "Error: Cannot run partA1 on Linux!\n"
    exit 0
fi

printf "If executing interactively, please enter one set of "
printf "arguments for each run. Enter quit or q to end the loop\n"

read line

# Continue while we havent hit an eof
while [ $? -eq 0 ]
do
    # Bail early if interactive user chooses to quit.
    if [ "$line" = "q" ] | [ "$line" = "quit" ]
    then 
        exit 0
    fi

    ./$1 $line
    read line
done

# One last time, because this last line had the eof
./$1 $line