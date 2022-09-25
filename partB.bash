# NAME: Matthew Munro
# NSID: mam552
# STUDENT NUMBER: 11291769
# NAME: Yi Luan
# NSID: yil160
# STUDENT NUMBER: 11253856
# CMPT 332 2022
# A1 Phase 2

#!/bin/bash

binary="$1"
if [ -z "$binary" ]
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
        printf "Error: Argument $1 failed to match any known executables!\n"
        exit 1
esac

# Validate we are on correct platform for partA1
if [ "$binary" = "partA1" ] && [ "$OS" != "Windows_NT" ]
then
    printf "Error: Cannot run partA1 on Linux!\n"
    exit 1
fi

# Used to confirm the user input for the executable is valid.
validate_arg() {
    # redirect stderr to stdout so we can catch it in this var
    # if there's a way to catch stderr into a var directly,
    # I am not aware of it.
    err=$(test "$1" -lt 0 2>&1)
    if [ ! -z "$err" ]
    then
        printf "Error: Could not understand non-numeric arg $1...\n"
        return 1
    fi

    if [ $1 -lt 0 ]
    then
        printf "Error: Input $1 must be non-negative...\n"
        return 1
    fi

    return 0
}

printf "If executing interactively, please enter one set of "
printf "arguments for each run. \nEnter quit or q to end the loop\n"

# Continue while we havent hit an eof
while read line
do
    # Bail early if interactive user chooses to quit.
    if [ "$line" = "q" ] || [ "$line" = "quit" ]
    then
        printf "Interactive user chose to quit. Goodbye.\n"
        exit 0
    fi

    # Grab each input seperately, so we can test
    # for invalid input.
    threads=$(echo "$line" | cut -d " " -f 1)
    validate_arg $threads
    rc1=$?
    deadline=$(echo "$line" | cut -d " " -f 2)
    validate_arg $deadline
    rc2=$?
    size=$(echo "$line" | cut -d " " -f 3)
    validate_arg $size
    rc3=$?

    if [ $rc1 = 1 ] || [ $rc2 = 1 ] || [ $rc3 = 1 ]
    then
        printf "Error parsing input, skipping this input...\n"
        continue
    fi
    ./$binary $line
    printf "Completed run of executable.\n"
done

# Do this one more time, because we hit a line with eof.
# does bash have some kind of do while?
threads=$(echo "$line" | cut -d " " -f 1)
validate_arg $threads
rc1=$?
deadline=$(echo "$line" | cut -d " " -f 2)
validate_arg $deadline
rc2=$?
size=$(echo "$line" | cut -d " " -f 3)
validate_arg $size
rc3=$?

if [ $rc1 = 1 ] || [ $rc2 = 1 ] || [ $rc3 = 1 ]
then
    printf "Error parsing input, skipping this input...\n"
    printf "End of file reached. Goodbye.\n"
    # Don't forget to read a new line, or we end up
    # in an infinite loop.
    exit 0
fi

./$binary $line
printf "End of file reached. Goodbye.\n"
exit 0
