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
elif [ "$binary" != "partA1" ] && [ "$OS" == "Windows_NT" ]
then
    printf "Error: All executables besides partA1 can only be run on Linux!\n"
    exit 1
fi

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
    
    readarray -d " " arr < <(echo -n "$line")
    if [ ${arr[0]} -lt 0 ] || [ ${arr[1]} -lt 0 ] || [ ${arr[2]} -lt 0 ]
    then
        printf "Error: Input $1 must be non-negative...\n"
        return 1
    fi
    ./$binary ${arr[0]} ${arr[1]} ${arr[2]}

    printf "Completed run of executable.\n"
done

printf "End of file reached. Goodbye.\n"
exit 0