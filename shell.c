#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdint.h>

#define MIN_ALLOC_SIZE 10

/* Basic skeleton program for the shell.
   Right now all it does it store the stdin into 
   memory, and then echo the command right back out to
   the user.
*/
int main() {
    size_t commandSize = 0;
    /* How big to initially construct our char buffer */
    size_t bufSize = MIN_ALLOC_SIZE * sizeof(uint8_t);
    uint8_t *buf = malloc(bufSize);
    uint8_t charInput = 0;

    if (buf == NULL) { 
        printf("Error: Could not allocate memory for "
        "dynamic command buffer.\n");
        return -1;
    }

    /* Basic shell prompt - placeholder */
    printf("> ");
    while (1) {
        /* 
         Blocking function - waits until the user is done entering
         a command in stdin. We use getchar to pull in the characters 
         one at a time because this allows us to count the size of 
         the command and dynamically resize our buffer as necessary 
         to support arbitrary-length commands. 
         */
        charInput = getchar();
        /* 
         Each char we pull in helps tell us how much memory we 
         will need to store this command. 
        */
        commandSize += 1;

        /*
         We've discovered that the user's command is larger
         than we can fit into our buffer - we have to resize 
         to accomodate. A simple doubling of the buffer size 
         each time we run out of space is used. 
         */
        if (commandSize > bufSize) {
            bufSize *= 2;
            if (realloc(buf, bufSize) == NULL) {
                printf("Error: Failed to dynamically resize "
                "command buffer!\n");
                return -1;
            }
        }

        /*
          A newline indicates that we have finished receiving the entire 
          command from getchar(). We would then begin tokenizing the command
          here. For now it just has placeholder code that echoes back the 
          command to stdout. 
         */
        if (charInput == '\n') {
            commandSize = 0;
            /* Don't forget to null terminate our array */
            buf[commandSize - 1] = 0;
            printf("%s\n", buf);
            printf("> ");
            /* Erase our buffer to prep for the next command */
            memset(buf, 0, bufSize);
        }

        buf[commandSize - 1] = (uint8_t)charInput;
    }

    return 0;
}