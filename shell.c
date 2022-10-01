#define _GNU_SOURCE
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdint.h>
#include <sys/types.h>
#include <unistd.h>
#include <sys/wait.h>
#define MIN_ALLOC_SIZE 5

void execute(char ** tokenArr, char ** path){
  char *concatCommand;
  size_t pathLen;
  size_t cmdLen;
  size_t i=0;
  if (memcmp(tokenArr[0],"/",1)==0 || memcmp(tokenArr[0],".",1)==0) {

      if (execv(tokenArr[0],tokenArr)==-1) {
        perror("");
      }
      exit(0);

  }else{

        /* iterate all path in the array */
        while (path[i]!=NULL){
          pathLen = strlen(path[i]);
          cmdLen = strlen(tokenArr[0]);
          concatCommand = malloc(pathLen+cmdLen+2);
          memmove(concatCommand, path[i], pathLen);
          memmove(&concatCommand[pathLen], "/",1);
          memmove(&concatCommand[pathLen+1],tokenArr[0],cmdLen);
          printf("%s\n",concatCommand);
          /* execute, if not success, keep trying by loop */
          if (execv(concatCommand,tokenArr)==-1) {
            /* print error message and exit process
            if it's the last path */

              if (path[i+1]==NULL) {
                perror("");
                exit(0);
              }
            }
            i++;

        }
  }

}

void pipingExe(char** tokenArrWr, char** tokenArrRe, char** path){
  int fd[2];
  pid_t inProcess;
  pipe(fd);

  inProcess = fork();
  if (inProcess == 0) {
    close(fd[1]);
    dup2(fd[0],STDIN_FILENO);
    execute(tokenArrRe,path);

  }else if(inProcess>0){
    close(fd[0]);
    dup2(fd[1],STDOUT_FILENO);
    execute(tokenArrWr,path);

  }


}

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
    char *path[] = {".","usr/local/bin","/usr/local/sbin",
    "/usr/bin","/usr/sbin",NULL};

    size_t j = 0;
    int pipeCount = 0;
    size_t pipeIndex;
    pid_t id;
    while (1) {
        char *strtokRes = NULL;
        /* Resetting some vars in prep for the next cotokenArrmmand */
        tokenIndex = 0;
        cmdSize = 0;
        j = 0;
        pipeCount = 0;
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

        /* Test if we were given a builtin command */
        if (strcmp(tokenArr[0], "exit") == 0) {
          exit(0);
        }
        while(tokenArr[j] != NULL){
          if (memcmp(tokenArr[j],"|",1) == 0 && strlen(tokenArr[j]) == 1) {
            pipeCount++;
            pipeIndex = j;
          }
          j++;
        }

        if (pipeCount>1) {
          fprintf(stderr,"Number of pipe character is greater than 1, "
          "can not handle\n" );
        }else if (pipeCount==1) {
          char **tokenArrIn = malloc((pipeIndex+1) * sizeof(char*));
          tokenArr[pipeIndex] = NULL;
          memmove(tokenArrIn,tokenArr,(pipeIndex+1)*sizeof(char*));
          id = fork();
          if (id==0) {
          pipingExe(tokenArrIn,&tokenArr[pipeIndex+1],path);
          }
        }else{
          id = fork();
          if (id==0) {
            execute(tokenArr,path);
          }
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
