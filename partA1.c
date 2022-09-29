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

/* flag of deadline */
int keepRunning = 1;

/* global array stores the counts */
ThreadEntry *countArr;
/* count how many times thread been created */
int threadCount = 0;

typedef struct Params Params;
struct Params {
    int size;
    int threads;
};

uint64_t PA_GetUID() {
    return GetCurrentThreadId();
}

/*
 * The entry point for all of our child threads.
 * paramP: Pointer to data supplied to the child thread via the Win32 API.
 * return: Unused, but required by the function signature to satisfy Win32.
 */
unsigned int thread_start(void *paramP) {

    /* system time start and end */
    SYSTEMTIME st;
    SYSTEMTIME et;
    Params *params = (Params*)paramP;

    /* time cost, calculated by system time */
    int timeCost;
    /* track the number of size when fib() end */
    int fibEnd;
    /* loop count */
    int i = 0;
    /* set the start time */
    GetSystemTime(&st);

    /* loop to call fib(1), fib(2),...,fib(n) */
    for(i = 1; i <= params->size; i++){
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
    for (i = 0; i < params->threads; i++) {
        if (countArr[i].uid == PA_GetUID()) {
            printf("thread ID: %lu, up to fib(%d) count is %"PRIu64", Real time"
            "is %ds\n",PA_GetUID(), fibEnd,countArr[i].count,timeCost);
        }
    }
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
    Params *params = malloc(sizeof(Params));
    /* transfer input arguments to need data type */
    if (!parse_args(argc, argv, &threads, &deadline, &size)) {
        return -1;
    }
    params->size = size;
    params->threads = threads;


    /* allocate memories to array stores count number */
    countArr = (ThreadEntry*) malloc(threads * sizeof(ThreadEntry));
    memset(countArr, 0, sizeof(threads * sizeof(ThreadEntry)));

    for (i=0; i<threads; i++){
        unsigned int threadID = 0;
        threadCount += 1;
        /* thread created and passing the size of fib() */
        CreateThread(NULL, 0, thread_start, params, 0, &threadID);
        countArr[i].uid = threadID;
        countArr[i].count = 0;
	}

    /* Convert seconds to ms */
    Sleep(deadline * 1000);

    keepRunning = 0;

    /* make main sleep for 3 sec to print the things */
    Sleep(3000);

    free(countArr);

    return 0;
}
