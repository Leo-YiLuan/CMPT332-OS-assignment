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

.PHONY : all
all: mytestlist partA1 

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
	
list_movers.o : list_movers.c list.h
	$(CC) -o list_movers.o -c $(CFLAGS) $(CPPFLAGS) list_movers.c

list_adders.o : list_adders.c list.h
	$(CC) -o list_adders.o -c $(CFLAGS) $(CPPFLAGS) list_adders.c 

list_removers.o : list_removers.c list.h
	$(CC) -o list_removers.o -c $(CFLAGS) $(CPPFLAGS) list_removers.c

mytestlist.o: mytestlist.c list.h
	$(CC) -o mytestlist.o -c $(CFLAGS) $(CPPFLAGS) mytestlist.c

liblist.a : list_adders.o list_movers.o list_removers.o
	ar -r liblist.a list_movers.o list_adders.o list_removers.o

mytestlist: mytestlist.o liblist.a list.h
	$(CC) -o mytestlist $(CFLAGS) mytestlist.o -L. -llist

clear:
	rm -f *.o liblist.a mytestlist