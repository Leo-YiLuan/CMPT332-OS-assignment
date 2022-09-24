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
CPPFLAGS=-std=gnu90 -Wall -pedantic -Wextra

.PHONY : all
all: mytestlist partA1 partA2 partA3 partA4

ifeq ($(OS), Windows_NT)
# We are on Windows/MSYS, build the windows
# assignment.
partA1: partA1.c fib.o thread_util.o
	$(CC) $(CFLAGS) $(CPPFLAGS) -o partA1 partA1.c fib.o thread_util.o
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

list_data.o: list_data.c
	$(CC) -o list_data.o -c $(CFLAGS) $(CPPFLAGS) list_data.c

mytestlist.o: mytestlist.c list.h
	$(CC) -o mytestlist.o -c $(CFLAGS) $(CPPFLAGS) mytestlist.c

liblist.a : list_adders.o list_movers.o list_removers.o list_data.o
	ar -r liblist.a list_movers.o list_adders.o list_removers.o list_data.o

partA2.o: partA2.c
	$(CC) -o partA2.o -c $(CFLAGS) $(CPPFLAGS) partA2.c -I/student/cmpt332/pthreads/ -I./

partA3.o: partA3.c
	$(CC) -o partA3.o -c $(CFLAGS) $(CPPFLAGS) partA3.c

partA4.o: partA4.c
	$(CC) -o partA4.o -c $(CFLAGS) $(CPPFLAGS) partA4.c

ifeq ($(OS), Windows_NT)
mytestlist:
	@echo "On Windows, but assignment spec says PartC is linux only, skipping..."
partA2:
	@echo "On Windows, partA2 skipping..."
else
mytestlist: mytestlist.o liblist.a list.h
	$(CC) -o mytestlist $(CFLAGS) $(CPPFLAGS) mytestlist.o -L. -llist

partA2: partA2.o fib.o thread_util.o
	$(CC) -o partA2 $(CFLAGS) $(CPPFLAGS) partA2.o  fib.o thread_util.o -L/student/cmpt332/pthreads/lib/Linuxx86_64 -lpthreads

partA3: partA3.o fib.o thread_util.o
	$(CC) -o partA3 $(CFLAGS) $(CPPFLAGS) partA3.o fib.o thread_util.o -lpthread

partA4: partA4.o
	$(CC) -o partA4 $(CFLAGS) $(CPPFLAGS) partA4.o fib.o thread_util.o
endif

clean:
	rm -f *.o liblist.a mytestlist partA1 partA2 partA3 partA4
