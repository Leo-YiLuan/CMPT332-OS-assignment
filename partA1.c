/*
# NAME: Matthew Munro
# NSID: mam552
# STUDENT NUMBER: 11291769
# NAME: Li Yuan
# NSID: yil160
# STUDENT NUMBER: 11253856
# CMPT 332 2022
# A1 Phase 1
*/

#include <stdio.h>

#include "fib.h"
#include "thread_util.h"

int main(int argc, char **argv) {
    int threads = 0;
    int deadline = 0;
    int size = 0;

    if (!parse_args(argc, argv, &threads, &deadline, &size)) {
        return -1;
    }

    printf("Calling fib with valid parameter...\n");
    fib(15);
    printf("Calling fib with invalid parameter...\n");
    fib(-15);
    return 0;
}