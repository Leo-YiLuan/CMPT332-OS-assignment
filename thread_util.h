#ifndef THREAD_UTIL_H
#define THREAD_UTIL_H

/*
 * Parses the provided commandline arguments, printing to 
 * stderr if incorrect number of args or values were provided.
 * 
 * param argc: The count of args in argv.
 * param argv: A pointer to an array of null-terminated strings.
 * param outThreads: A pointer that will be filled with the 
 *                   requested number of threads to create.
 * param outDeadline: A pointer that will be filled with the number 
 *                    of seconds to run.
 * param outSize: A pointer that will be filled with the nth
 *                fibonacci number to calculate. 
 * return: 1 if arguments successfully parsed, 0 if error parsing args.
 */
int parse_args(int argc, char **argv, int *outThreads, int *outDeadline, 
               int *outSize);

#endif /* THREAD_UTIL_H */