#define _GNU_SOURCE
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdint.h>
#include <sys/types.h>
#include <unistd.h>
#include <sys/wait.h>
#define MIN_ALLOC_SIZE 5



/* Basic skeleton program for the shell.
   Right now all it does it store the stdin into
   memory, and then echo the command right back out to
   the user.
*/
int main() {
    char *command = NULL;
    size_t maxTokenCount = MIN_ALLOC_SIZE;
    char **tokenArr = malloc(maxTokenCount * sizeof(char*));
    size_t cmdSize = 0;
    size_t tokenIndex = 0;
    char *path[] = {"./","/bin/","/usr/bin/",""};
    size_t pathNum = 4;
    /*char *argv[] = {"ls",NULL};*/
    char *concatCommand;
    size_t pathLen;
    size_t cmdLen;
    int id;
    size_t i=0;

    while (1) {
        char *strtokRes = NULL;
        /* Resetting some vars in prep for the next cotokenArrmmand */
        tokenIndex = 0;
        cmdSize = 0;
        printf("> ");
        /* Grab the next command from stdin */
        getline(&command, &cmdSize, stdin);;

        tokenIndex = 0;
        /* This should never happen, but just to be safe...*/
        if (!command) { break; }
        command[strlen(command)-1]='\0';
        /* Main tokenizer code. */
        tokenArr[0] = strtok(command, " ");
        if (!tokenArr[0]) {
            /* There were no tokens, skip. */
            continue;
        }
        while ((strtokRes = strtok(NULL, " "))) {
            tokenIndex += 1;
            if (tokenIndex + 1 > maxTokenCount) {
                maxTokenCount *= 2;
                tokenArr = realloc(tokenArr, maxTokenCount * sizeof(char*));
            }
            tokenArr[tokenIndex] = strtokRes;
        }
        /* Our token array must be null-terminated, according to man exec. */
        tokenIndex += 1;
        if (tokenIndex + 1 > maxTokenCount) {
            maxTokenCount += 1;
            tokenArr = realloc(tokenArr, maxTokenCount * sizeof(char*));
        }
        tokenArr[tokenIndex] = NULL;


        /* TODO: Probably where we would fork processes and set up pipes. */
        /* For now, just print tokens back to stdout... */
        {
            size_t i = 0;
            for (i = 0; i < tokenIndex; i++) {
                printf("%s\n", tokenArr[i]);
            }

        }
        if (memcmp(tokenArr[0],"/",1)==0 || memcmp(tokenArr[0],".",1)==0) {
          printf("get to / branch %s\n",tokenArr[0] );

          id = fork();
          if (id==0) {
            if (execv(tokenArr[0],tokenArr)) {
              perror("");
            }
            exit(0);
          }
        }else{
          printf("get to concat Branch \n");
          printf("MAIN PID is %d\n", getpid() );

            id = fork();

            if (id==0) {
              printf("CPID is %d\n", getpid() );

              for (i = 0; i < pathNum; i++) {
                pathLen = strlen(path[i]);
                cmdLen = strlen(tokenArr[0]);
                concatCommand = malloc(pathLen+cmdLen+1);
                memmove(concatCommand, path[i], pathLen);
                memmove(&concatCommand[pathLen],tokenArr[0],cmdLen);
                if (execv(concatCommand,tokenArr)==-1) {
                    if (i==pathNum-1) {
                      perror("");
                      exit(0);
                    }
                  }
                }
              }
          printf("OPID is%d\n", getpid() );


        }

        wait(NULL);

        /* Free the old cmd string now that we are done with it. */
        free(command);
        command = NULL;
    }

    /* Shouldn't matter, but might as well do it. */
    free(tokenArr);
    return 0;
}
