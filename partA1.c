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
#include <processthreadsapi.h>
#include <synchapi.h>

#include "fib.h"
#include "thread_util.h"

unsigned int thread_start(void *fibData) {
    /* Skeleton thread... would normally call fib */
    printf("Start thread with value: %d\n", *(unsigned int*)fibData);
}

LPDWORD create_thread(unsigned int size) {
    LPDWORD id = NULL;
    id = CreateThread(NULL, 0, thread_start, &size, 0, id);
    return id;
}

int main(int argc, char **argv) {
    int threads = 0;
    int deadline = 0;
    int size = 0;

    if (!parse_args(argc, argv, &threads, &deadline, &size)) {
        return -1;
    }

    /* Test skeleton functions... */
    fib(15);
    create_thread(size);

    /* Convert seconds to ms */
    Sleep(deadline * 1000);

    return 0;
}