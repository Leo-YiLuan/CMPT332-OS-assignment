/*
# NAME: Matthew Munro
# NSID: mam552
# STUDENT NUMBER: 11291769
# NAME: Yi Luan
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

/*
 * The entry point for all of our child threads. 
 * fibData: Pointer to data supplied to the child thread via the Win32 API.
 * return: Unused, but required by the function signature to satisfy Win32.
 */
unsigned int thread_start(void *fibData) {
    /* Skeleton thread... would normally call fib */
    printf("Started thread with value: %d\n", *(unsigned int*)fibData);
}

int main(int argc, char **argv) {
    int threads = 0;
    int deadline = 0;
    int size = 0;

    if (!parse_args(argc, argv, &threads, &deadline, &size)) {
        return -1;
    }

    /* Test skeleton functions... */
    fib(size);
    LPDWORD id = CreateThread(NULL, 0, thread_start, &size, 0, id);

    /* Convert seconds to ms */
    Sleep(deadline * 1000);

    return 0;
}