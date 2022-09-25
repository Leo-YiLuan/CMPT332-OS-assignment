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
#include "fib.h"
#include <stdio.h>
#include <inttypes.h>


int fib(int value){
    if (value < 0) {
        printf("Error in fib: value must be equal or greater than 0\n");
        return -1;
    }

    /* add count to index */
    countArr[threadIdx] = countArr[threadIdx] + (uint64_t)1;


    if (value == 0)
    {
        return 0;
    }else if (value == 1){
        return 1;
    }else{
        return (fib(value - 1) + fib(value - 2));
    }


}
