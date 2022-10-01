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
#include <stdlib.h>
#include <time.h>
#include <string.h>
#include "fib.h"
#include "thread_util.h"
#include <sys/types.h>
#include <unistd.h>
#include <sys/wait.h>

/* 
 Processes are a unique case - we still need to conform to the interface 
 we chose for every other section of part A, but here we can always return
 an array index of zero since fork() uses copy-on-write. All child processes
 just index the first element without conflict. 
 */
size_t PA_GetUID() {
    return 0;
}

ThreadEntry *countArr;
int threadCount = 1;

/* Global vars needed by signal handler */
int size = 0;
pid_t parentProc = 0;
time_t parentStart = 0;

void handler (int signum) {
  time_t end = 0;
  time_t dur = 0;
  if (getpid() == parentProc) {
    return; /* Don't print, parent will be killed when its children are. */
  }

  time(&end);
  dur = end - countArr[0].startTime;
  printf("pid: %d early term with sig %d, fib(%d) is called "
  "with %ld invocations in %ld sec.\n", getpid(), signum,size, 
  countArr[0].count, dur);
  exit(-1);
}

/* Note: use sigaction because cmpt332 notes recommend it over signal */
int main(int argc, char **argv){
  int processes = 0;
  int deadline = 0;
  pid_t *fibproc = NULL;
  pid_t timerproc = 0;
  int i=0;
  struct sigaction action = {0};
  action.sa_handler = handler;
  parentProc = getpid();

  /* Register parent */
  sigaction(SIGALRM, &action, NULL);

  /* check arguments (usage) */
  if (! parse_args(argc,argv,&processes,&deadline,&size)) {
      return -1;
  }

  fibproc = malloc(processes * sizeof(pid_t));
  memset(fibproc, 0, sizeof(processes * sizeof(pid_t)));
  /* 
   Note we only allocate space for a single ThreadEntry in this array.
   This is because this array is never accessed until after fork(),
   so each fib proc will do a copy on write and can write to the 
   first entry without conflict. 
   */
  countArr = malloc(sizeof(ThreadEntry));
  memset(countArr, 0, sizeof(ThreadEntry));

  /* create child processes */
  for(i = 0; i < processes; i++) {
    time_t start = 0;
    time_t end = 0;
    time_t dur = 0;
    fibproc[i] = fork();
    if(fibproc[i] == 0) {
      /* in fib() process */
      /* Register child */
      sigaction(SIGALRM, &action, NULL);
      time(&start);
      countArr[0].startTime = start;
      for (i = 1; i <= size; i++) {
        fib(i);
      }
      time(&end);
      dur = end - start;
      printf("pid: %d, fib(%d) called with %ld invocations in "
      "%ld sec. Exited normally.\n",getpid(),size, countArr[0].count, dur);
      exit(0);
    }
  }

  /* create timer process */
  timerproc = fork();
  if (timerproc == 0) {
    /* In timer proc */
    /* sleep until the deadline before we send signals. */
    sleep(deadline);
    for (i = 0; i < processes; i++) {
      kill(fibproc[i], SIGALRM);
    }
    /* Don't forget to signal the parent too, as per the assignment spec. */
    kill(getppid(), SIGALRM);
  }

  /* Only parent should do this, disallow timerproc. */
  if (timerproc != 0) {
    /* Wait on all children to exit. */
    for (i = 0; i < processes; i++) {
      wait(&fibproc[i]);
    }
    kill(timerproc, SIGKILL);
  }

  return 0;
}