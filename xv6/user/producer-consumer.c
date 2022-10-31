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
  for (int i = 0; i < 50; i++) {
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
  for (int i = 0; i < 50; i++) {
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

int
main(void)
{

    void *otherstack = 0;

    mtxID = mtx_create(0);
    void *stack1 = malloc(STACK_SIZE);
    stack1 += STACK_SIZE;

    void *stack2 = malloc(STACK_SIZE);
    stack2 += STACK_SIZE;
    thread_create(producer, stack1, (void*)(0));
    thread_create(consumer, stack2, (void*)(0));


    thread_join(&otherstack);
    free(otherstack-STACK_SIZE);

    thread_join(&otherstack);
    free(otherstack-STACK_SIZE);

    exit(0);
}
