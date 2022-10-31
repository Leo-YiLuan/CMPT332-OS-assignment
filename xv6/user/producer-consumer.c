/* CMPT 332 GROUP 22 Change, Fall 2022 */
/* Tests threads */
/* TODO: Page fault sometimes. Related to wait and exit perhaps? Why? */

#include "kernel/types.h"
#include "kernel/stat.h"
#include "user/user.h"

#define STACK_SIZE 500

int global = 1;
int buffer = 0;
int bufSize = 300;
int mtxID;

void consumer() {
  for (int i = 0; i < 5000; i++) {
    mtx_lock(mtxID);
    if (buffer>0) {
      buffer --;
      bufSize ++;
      printf("Buffer consume %d\n",buffer);
    }
    mtx_unlock(mtxID);
    }
  exit(0);
}

void producer(){
  for (int i = 0; i < 5000; i++) {
    mtx_lock(mtxID);
    if (bufSize>0) {
      buffer ++;
      bufSize--;
      printf("Buffer produce %d\n",buffer);

    }
    mtx_unlock(mtxID);
  }
  exit(0);

}
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

    mtxID = mtx_create(0);

    void *stack1 = malloc(STACK_SIZE);
    int ret1 = 0;
    stack1 += STACK_SIZE;

    void *stack2 = malloc(STACK_SIZE);
    int ret2 = 0;
    stack2 += STACK_SIZE;
    ret1 = thread_create(producer, stack1, (void*)((uint64)testVal));
    ret2 = thread_create(consumer, stack2, (void*)((uint64)testVal));
    printf("Successfully called thread_create, return: %d\n", ret1);
    printf("Successfully called thread_create, return: %d\n", ret2);


    thread_join(&otherstack);





    exit(0);
}
