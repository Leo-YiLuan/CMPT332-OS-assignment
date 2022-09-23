#ifndef FIB_H
#define FIB_H
#include <stdint.h>

/*
 * Calculates the nth fibonacci number.
 * value: the fibonacci number to calculate. Value must be >= 0.
 * return: the nth fibonacci number. 
 */
int fib(int value);
extern int keepRunning;
extern uint64_t *arr;
extern __thread int threadIdx;
#endif /* FIB_h */

