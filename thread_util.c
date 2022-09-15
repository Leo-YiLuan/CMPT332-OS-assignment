#include "thread_util.h"

#include <stdio.h>
#include <stdlib.h>

int parse_args(int argc, char **argv, int *outThreads, int *outDeadline, int *outSize) {
    if (argc != 4) {
        printf("Error: Incorrect number of arguments. Usage: ./partA1 <threads>"
        " <deadline> <size>\n");
        return 0;
    }

    *outThreads = (int)strtol(argv[1], NULL, 10);
    *outDeadline = (int)strtol(argv[2], NULL, 10);
    *outSize = (int)strtol(argv[3], NULL, 10);

    if (*outThreads <= 0 || *outDeadline <= 0 || *outSize <= 0) {
        printf("Error: Arguments supplied must be non-negative.");
        return 0;
    }
    return 1;
}