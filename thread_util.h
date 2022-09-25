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
#ifndef THREAD_UTIL_H
#define THREAD_UTIL_H

/*
 * Parses the provided commandline arguments, printing to
 * stderr if incorrect number of args or values were provided.
 *
 * argc: The count of args in argv.
 * argv: A pointer to an array of null-terminated strings.
 * outThreads: A pointer to be filled with the requested num of threads.
 * outDeadline: A pointer to be filled with the num of seconds to run.
 * outSize: A pointer to be be filled with the nth fibonacci number
 *          to calculate.
 * return: 1 if arguments successfully parsed, 0 if error parsing args.
 */
int parse_args(int argc, char **argv, int *outThreads, int *outDeadline,
               int *outSize);

#endif /* THREAD_UTIL_H */
