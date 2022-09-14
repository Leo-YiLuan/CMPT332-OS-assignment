#include "fib.h"

#include <stdio.h>

int fib(int value) {
    if (value < 0) {
        printf("Error in fib: value must be equal or greater than 0\n");
        return -1;
    }
    printf("Successfully called fib with value %d\n", value);
    return 0;
}