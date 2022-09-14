# NAME: Matthew Munro
# NSID: mam552
# STUDENT NUMBER: 11291769
# NAME: Li Yuan
# NSID: yil160
# STUDENT NUMBER: 11253856
# CMPT 332 2022
# A1 Phase 1

CC=gcc
CLAGS=-g
CPPFLAGS=-std=gnu90 -Wall -pedantics

ifeq ($(OS), Windows_NT)
# We are on Windows/MSYS, build the windows
# assignment.
partA1: partA1.c fib.o
	$(CC) -o partA1 partA1.c fib.o
else 
# We are on Unix, build Unix specific stuff.

endif

# Build common stuff for A1.
fib.o: fib.c fib.h
	$(CC) -o fib.o -c $(CPPFLAGS) fib.c 
