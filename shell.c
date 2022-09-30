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
    char *start = NULL;
    char *charPos = NULL;
    char *path[] = {"/usr/bin/","","",""};
    /*char *argv[] = {"ls",NULL};*/
    char *concatCommand;
    size_t pathLen;
    size_t cmdLen;
    int id;
    char *test[] = {NULL};

    printf("> ");
    while (1) {
        /* Resetting some vars in prep for the next command */
        start = NULL;
        charPos = NULL;
        tokenIndex = 0;
        cmdSize = 0;
        printf("> ");
        /* Grab the next command from stdin */
        getline(&command, &cmdSize, stdin);
        charPos = command;
        start = charPos;

        /* Main tokenizer loop */
        while (1) {

            /* This should never happen, but just to be safe...*/
            if (!command) { break; }

            /*
             Our two delimiters - \n is used because it mar        size_t pathLen = strlen(path[0]);
        size_t cmdLen = strlen(tokenArr[0]);ksargv
             that the user hit enter and submitted a command.
             Is it safe to always assume a command ends with a \n?
             */
            if (*charPos != ' ' && *charPos != '\n') {
                /* Seek through the char pointer by one space. */
                charPos += 1;
            } else {
                /* We've found the end of a single token - null terminate it */
                *charPos = '\0';
                charPos += 1;
                /* ignore additional whitespace */
                while (*charPos == ' ') {
                    charPos += 1;
                }

                /* Count is one plus current index. */
                if (tokenIndex + 1 > maxTokenCount) {
                    maxTokenCount *= 2;
                    tokenArr = realloc(tokenArr, maxTokenCount * sizeof(char *));
                    if (!tokenArr) {
                        printf("Fatal error allocating memory, must quit...\n");
                        return -1;
                    }
                }
                /* Add our completed token */
                tokenArr[tokenIndex] = start;
                start = charPos;
                tokenIndex += 1;
            }

            /* We've reached the end of the command string, done... */
            if (*charPos == '\0') { break; }
        };

        /* TODO: Probably where we would fork processes and set up pipes. */
        /* For now, just print tokens back to stdout... */
        {
            size_t i = 0;
            for (i = 0; i < tokenIndex; i++) {
                printf("%s\n", tokenArr[i]);
            }
        }4

        pathLen = strlen(path[0]);
        cmdLen = strlen(tokenArr[0]);
        concatCommand = malloc(pathLen+cmdLen+1);
        memmove(concatCommand, path[0], pathLen);
        memmove(&concatCommand[pathLen],tokenArr[0],cmdLen);
        printf("%s\n",concatCommand );


        id = fork();
        if (id==0) {
          execv(concatCommand,test);
        }
        wait(NULL);

        /* Free the old cmd string now that we are done with it. */
        free(command);
        command = NULL;
        /* Reprint the prompt in preparation for next user command */
    }

    /* Shouldn't matter, but might as well do it. */
    free(tokenArr);
    return 0;
}
