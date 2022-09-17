# NAME: Matthew Munro
# NSID: mam552
# STUDENT NUMBER: 11291769
# NAME: Yi Luan
# NSID: yil160
# STUDENT NUMBER: 11253856
# CMPT 332 2022
# A1 Phase 1

CC=gcc
CFLAGS=-g
CPPFLAGS=-std=gnu90 -Wall -pedantic

ifeq ($(OS), Windows_NT)
# We are on Windows/MSYS, build the windows
# assignment.
partA1: partA1.c fib.o thread_util.o
	$(CC) $(CFLAGS) -o partA1 partA1.c fib.o thread_util.o
else 
# We are on Unix, build Unix specific stuff.
# Dummy rule
partA1: 
	@echo "Not on Windows, skipping partA1..."
endif

# Build common stuff for A1.
fib.o: fib.c fib.h
	$(CC) -o fib.o -c $(CFLAGS) $(CPPFLAGS) fib.c 

thread_util.o: thread_util.c thread_util.h
	$(CC) -o thread_util.o -c $(CFLAGS) $(CPPFLAGS) thread_util.c
