/* CMPT 332 GROUP 22 Change, Fall 2022 */
/* Tests threads */
/* TODO: Page fault sometimes. Related to wait and exit perhaps? Why? */

#include "kernel/types.h"
#include "kernel/stat.h"
#include "user/user.h"

#define STACK_SIZE 500

int global = 1;

void test(void *val) {
    int testStack = 42;
    int another = -4;
    printf("Reached thread main. parameter value: %d\n", (uint64)val);
    printf("Test a stack value: %d\n", testStack);
    printf("And another: %d\n", another);
    printf("Check global: %d\n", global);

   exit(0);
}

int
main(void)
{
    int testVal = 5;
    void *stack = malloc(STACK_SIZE);
    void *otherstack = 0;
    int ret = 0;
    stack += STACK_SIZE;
    ret = thread_create(test, stack, (void*)((uint64)testVal));
    printf("Successfully called thread_create, return: %d\n", ret);
    global = 17;
    printf("Modified global\n");

    thread_join(&otherstack);
    free(otherstack - STACK_SIZE);
    exit(0);
}
