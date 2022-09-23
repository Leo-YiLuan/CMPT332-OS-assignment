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
#include <stdint.h>
#include <inttypes.h>
#include "fib.h"
#include "thread_util.h"

// struct threadParameters
// {
//     int threadID;
//     int size;
// }TP;



int keepRunning = 1;
uint64_t *arr;
int indexO;

/*
 * The entry point for all of our child threads.
 * fibData: Pointer to data supplied to the child thread via the Win32 API.
 * return: Unused, but required by the function signature to satisfy Win32.
 */
unsigned int thread_start(void *paramP) {

    indexO = indexO+1;

    // struct threadParameters *tp = paramP;
    // int *index = paramP;
    // printf("Started thread with value: %d\n", tp->size);
    printf("ARRAY : %d \n", indexO);
    // arr[tp->threadID] = 0;
    fib(*(unsigned int *)paramP, indexO);

}

int main(int argc, char **argv) {
    int threads = 0;
    int deadline = 0;
    int size = 0;
    indexO=-1;
    // struct threadParameters tp;

    if (!parse_args(argc, argv, &threads, &deadline, &size)) {
        return -1;
    }

    // sizeO = size;
    arr = (uint64_t*) malloc(threads * sizeof(uint64_t));

    /* Test skeleton functions... */

    for (int i=0; i<threads; i++){
        // tp.threadID=i;
        arr[i] = (uint64_t)0;
        // printf("threadID is %d\n",tp.threadID);
        printf("ARRAY ENTRY: %"PRIu64" \n", arr[i]);
        CreateThread(NULL, 0, thread_start, &size, 0, NULL);

	}

    /* Convert seconds to ms */    

    Sleep(deadline * 1000);

    keepRunning = 0;

    // free(arr);
    for (int i=0; i<threads;i++){
        printf("%"PRIu64"\n",arr[i]);

    }

    
    return 0;
}

