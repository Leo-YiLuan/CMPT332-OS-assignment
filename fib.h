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
#ifndef FIB_H
#define FIB_H
#include <stdint.h>

typedef struct ThreadEntry ThreadEntry;
struct ThreadEntry {
    uint64_t uid;
    uint64_t count;
    uint64_t startTime; /* For partA2, A3, A4 only */
};

/*
 * Calculates the nth fibonacci number.
 * value: the fibonacci number to calculate. Value must be >= 0.
 * return: the nth fibonacci number.
 */
int fib(int value);
#endif /* FIB_h */
