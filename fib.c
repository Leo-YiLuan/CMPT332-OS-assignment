#include "fib.h"
#include <processthreadsapi.h>
#include <stdio.h>
#include <inttypes.h>

int fib(int value){
    if (value < 0) {
        printf("Error in fib: value must be equal or greater than 0\n");
        return -1;
    }

    arr[threadIdx] = arr[threadIdx] + (uint64_t)1;

    if (value == 0)
    {
        return 0;
    }else if (value == 1){
        return 1;
    }else{
        return (fib(value - 1) + fib(value - 2));
    }


}
