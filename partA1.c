/*
# NAME: Matthew Munro
# NSID: mam552
# STUDENT NUMBER: 11291769
# NAME: Yi Luan
# NSID: yil160
# STUDENT NUMBER: 11253856
# CMPT 332 2022
# A1 Phase 2
*/

#include <stdio.h>
#include <processthreadsapi.h>
#include <synchapi.h>
#include <stdint.h>
#include <inttypes.h>
#include "fib.h"
#include "thread_util.h"
#include <windows.h>

uint64_t PA_GetUID() {
    return threadIdx;
}

/* flag of deadline */
int keepRunning = 1;

/* global array stores the counts */
uint64_t *countArr;

DWORD *idArr;

/* thread variable that fib use to find the index */
__thread int threadIdx = -1;

/* index counter, +1 when thread_start() calls */
int threadCount = -1;

/*
 * The entry point for all of our child threads.
 * paramP: Pointer to data supplied to the child thread via the Win32 API.
 * return: Unused, but required by the function signature to satisfy Win32.
 */
unsigned int thread_start(void *paramP) {

    /* system time start and end */
    SYSTEMTIME st;
    SYSTEMTIME et;

    /* time cost, calculated by system time */
    int timeCost;
    /* track the number of size when fib() end */
    int fibEnd;
    /* loop count */
    int i = 0;
    /* set the start time */
    GetSystemTime(&st);

    /* the order this thread created */
    threadCount ++ ;

    /* save the order of the thread to a tread variable, use as index */
    threadIdx = threadCount;

    /* save current thread's id to idArr with it's index */
    idArr[threadIdx] = GetCurrentThreadId();

    /* loop to call fib(1), fib(2),...,fib(n) */
    for(i = 1; i <= *(int *)paramP; i++){
        fib(i);
        /* save fib() size, use to print */
        fibEnd = i;
        /* check the deadline flag for threads */
        if (keepRunning == 0){
            /* break the loop when deadline occurs */
            break;
        }
    }
    /* get the end time */
    GetSystemTime(&et);
    /* calculate the time cost */
    timeCost = et.wSecond-st.wSecond + 60*(et.wMinute-st.wMinute);
    /* print information */
    printf("thread ID: %u, up to fib(%d) count is %"PRIu64", Real time"
    "is %ds\n",idArr[threadIdx], fibEnd,countArr[threadIdx],timeCost);
    return 0;
}

int main(int argc, char **argv) {
    /*
        threads: number of thread will created
        deadline: the deadline in sec
        size: the size of the fib()
    */
    int threads = 0;
    int deadline = 0;
    int size = 0;
    int i = 0 ;
    /* transfer input arguments to need data type */
    if (!parse_args(argc, argv, &threads, &deadline, &size)) {
        return -1;
    }


    /* allocate memories to array stores count number */
    countArr = (uint64_t*) malloc(threads * sizeof(uint64_t));
    /* allocate memories to array stores id of thread */
    idArr = (DWORD *) malloc(threads * sizeof(DWORD));

    for (i=0; i<threads; i++){
        /* make sure all counts are 0 */
        countArr[i] = (uint64_t)0;

        /* thread created and passing the size of fib() */
        CreateThread(NULL, 0, thread_start, &size, 0, NULL);

	}

    /* Convert seconds to ms */
    Sleep(deadline * 1000);

    keepRunning = 0;

    /* make main sleep for 3 sec to print the things */
    Sleep(3000);

    free(countArr);



    return 0;
}
