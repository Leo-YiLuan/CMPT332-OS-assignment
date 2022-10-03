# NAME: Matthew Munro
# NSID: mam552
# STUDENT NUMBER: 11291769
# NAME: Yi Luan
# NSID: yil160
# STUDENT NUMBER: 11253856
# CMPT 332 2022
# A1 Phase 2

CC=gcc
CFLAGS=-g
CPPFLAGS=-std=gnu90 -Wall -pedantic -Wextra
PTHREADS_INCLUDE=-I/student/cmpt332/pthreads/

.PHONY : all
all: mytestlist partA1 partA2 partA3 partA4 shell

ifeq ($(OS), Windows_NT)
# We are on Windows/MSYS, build the windows
# assignment.
partA1: partA1.o fib_win.o thread_util_win.o
	$(CC) $(CFLAGS) $(CPPFLAGS) -o partA1 partA1.o fib_win.o thread_util_win.o

partA1.o: partA1.c
	$(CC) -c $(CPPFLAGS) -o partA1.o partA1.c

else
# We are on Unix, build Unix specific stuff.
# Dummy rule
partA1:
	@echo "Not on Windows, skipping partA1..."
endif

# Build common stuff for A1.
# TODO: fix. Needs a seperate rule for win and linux.
fib_linux.o: fib.c fib.h
	$(CC) -o fib_linux.o -c $(CFLAGS) $(CPPFLAGS) fib.c

fib_win.o: fib.c fib.h
	$(CC) -o fib_win.o -c $(CFLAGS) $(CPPFLAGS) fib.c

thread_util_win.o: thread_util.c thread_util.h
	$(CC) -o thread_util_win.o -c $(CFLAGS) $(CPPFLAGS) thread_util.c

thread_util_linux.o: thread_util.c thread_util.h
	$(CC) -o thread_util_linux.o -c $(CFLAGS) $(CPPFLAGS) thread_util.c

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



ifeq ($(OS), Windows_NT)
mytestlist:
	@echo "On Windows, but assignment spec says PartC is linux only, skipping..."
partA2:
	@echo "On Windows, partA2 skipping..."
partA3:
	@echo "On Windows, partA3 skipping..."
partA4:
	@echo "On Windows, partA4 skipping..."
shell:
	@echo "On Windows, don't build shell..."

else

shell: shell.o
	$(CC) -o shell $(CFLAGS) $(CPPFLAGS) shell.o 

shell.o: shell.c
	$(CC) -o shell.o $(CPPFLAGS) $(CFLAGS) -c shell.c

mytestlist: mytestlist.o liblist.a list.h
	$(CC) -o mytestlist $(CFLAGS) $(CPPFLAGS) mytestlist.o -L. -llist

partA2: partA2.o fib_linux.o thread_util_linux.o
	$(CC) -o partA2 $(CFLAGS) $(CPPFLAGS) partA2.o  fib_linux.o thread_util_linux.o \
	-L/student/cmpt332/pthreads/lib/Linuxx86_64 -lpthreads

partA2.o: partA2.c
	$(CC) -o partA2.o -c $(CFLAGS) $(CPPFLAGS) partA2.c $(PTHREADS_INCLUDE) -I./

partA3: partA3.o fib_linux.o thread_util_linux.o
	$(CC) -o partA3 $(CFLAGS) $(CPPFLAGS) partA3.o fib_linux.o thread_util_linux.o -lpthread

partA3.o: partA3.c
	$(CC) -o partA3.o -c $(CFLAGS) $(CPPFLAGS) partA3.c

partA4: partA4.o fib_linux.o thread_util_linux.o
	$(CC) -o partA4 $(CFLAGS) $(CPPFLAGS) partA4.o fib_linux.o thread_util_linux.o

partA4.o: partA4.c
	$(CC) -o partA4.o -c $(CFLAGS) $(CPPFLAGS) partA4.c
endif

clean:
	rm -f *.o liblist.a mytestlist partA1 partA2 partA3 partA4 shell
