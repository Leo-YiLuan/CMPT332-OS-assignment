#ifndef FIB_H
#define FIB_H
#include <stdint.h>

/*
 * Calculates the nth fibonacci number.
 * value: the fibonacci number to calculate. Value must be >= 0.
 * return: the nth fibonacci number. 
 */
int fib(int value,int index);
extern int keepRunning;
extern uint64_t *arr;
#endif /* FIB_h */