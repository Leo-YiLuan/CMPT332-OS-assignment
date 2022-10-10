# NAME: Matthew Munro
# NSID: mam552
# STUDENT NUMBER: 11291769
# NAME: Yi Luan
# NSID: yil160
# STUDENT NUMBER: 11253856
# CMPT 332 2022
# A2

CC=gcc
CFLAGS=-g
CPPFLAGS=-std=gnu90 -Wall -pedantic -Wextra

.PHONY : all
all: liblist.a

liblist.a : list_adders.o list_movers.o list_removers.o
	ar -r liblist.a list_movers.o list_adders.o list_removers.o

list_movers.o : list_movers.c list.h
	$(CC) -o list_movers.o -c $(CFLAGS) $(CPPFLAGS) list_movers.c

list_adders.o : list_adders.c list.h
	$(CC) -o list_adders.o -c $(CFLAGS) $(CPPFLAGS) list_adders.c

list_removers.o : list_removers.c list.h
	$(CC) -o list_removers.o -c $(CFLAGS) $(CPPFLAGS) list_removers.c

clean:
	rm -f *.o liblist.a
