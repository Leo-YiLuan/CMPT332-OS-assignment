# NAME: Matthew Munro
# NSID: mam552
# STUDENT NUMBER: 11291769
# NAME: Li Yuan
# NSID: yil160
# STUDENT NUMBER: 11253856
# CMPT 332 2022
# A1 Phase 1

#!/bin/bash

printf "If executing interactively, please enter one set of "
printf "arguments for each run. Enter quit or q to end the loop\n"

read line

# Continue while we havent hit an eof
while [ $? -eq 0 ]
do
    # Bail early if interactive user chooses to quit.
    if [ $line = "q" ] || [ $line = "quit" ]
    then 
        exit 0
    fi
    printf "$line\n" 
    read line
done

# one more time, since the last line had eof.
printf "$line\n"