#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdint.h>

#define MIN_ALLOC_SIZE 5



/* Basic skeleton program for the shell.
   Right now all it does it store the stdin into 
   memory, and then echo the command right back out to
   the user.
*/
int main() {
    char *command = NULL;
    char **tokenArr = malloc(MIN_ALLOC_SIZE * sizeof(char*));
    size_t cmdSize = 0;
    int tokenCount = 0;
    char *start = NULL;
    char *charPos = NULL;

    printf("> ");
    while (1) {
        /* Resetting some vars in prep for the next command */
        start = NULL;
        charPos = NULL;
        tokenCount = 0;
        cmdSize = 0;
        /* Grab the next command from stdin */
        getline(&command, &cmdSize, stdin);
        charPos = command;
        start = charPos;
        /* Main tokenizer loop */
        while (1) {
            /* This should never happen, but just to be safe...*/
            if (!command) { break; }
            
            /* 
             Our two delimiters - \n is used because it marks 
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

                /* Add our completed token */
                tokenArr[tokenCount] = start;
                start = charPos;
                tokenCount += 1;

                /* placeholder, printing tokens back to stdout */
                printf("%s\n", tokenArr[tokenCount - 1]);
            }

            /* We've reached the end of the command string, done... */
            if (*charPos == '\0') { break; }
        };

        /* TODO: Probably where we would fork processes and set up pipes. */

        /* Free the old cmd string now that we are done with it. */
        free(command);
        command = NULL;
        /* Reprint the prompt in preparation for next user command */
        printf("> ");
    }

    /* Shouldn't matter, but might as well do it. */
    free(tokenArr);
    return 0;
}