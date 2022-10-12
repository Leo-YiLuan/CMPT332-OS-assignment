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
PTHREADS_DIR=/student/cmpt332/pthreads/
PTHREADS_LIB=/student/cmpt332/pthreads/lib/Linuxx86_64/
RTTHREADS_DIR=/student/cmpt332/rtt/include/
RTTHREADS_LIB=/student/cmpt332/rtt/lib/Linuxx86_64/

.PHONY : all
all: reader_writer_test s-chat

reader_writer_test: libMonitor.a liblist.a reader_writer.o reader_writer_monitor.o
	$(CC) -o reader_writer_test $(CFLAGS) $(CPPFLAGS) -L. -L$(PTHREADS_LIB) reader_writer.o reader_writer_monitor.o -lMonitor -lpthreads -llist

libMonitor.a: Monitor.o
	ar -r libMonitor.a Monitor.o

Monitor.o: Monitor.c Monitor.h
	$(CC) -o Monitor.o -c $(CFLAGS) $(CPPFLAGS) -I$(PTHREADS_DIR) Monitor.c

reader_writer_monitor.o: reader_writer_monitor.c
	$(CC) -o reader_writer_monitor.o -c $(CFLAGS) $(CPPFLAGS) -I. reader_writer_monitor.c

reader_writer.o: reader_writer.c reader_writer_monitor.h
	$(CC) -o reader_writer.o -c $(CFLAGS) $(CPPFLAGS) -I$(PTHREADS_DIR) -I. reader_writer.c

s-chat.o: s-chat.c
	$(CC) -o s-chat.o -c $(CFLAGS) $(CPPFLAGS) -I$(RTTHREADS_DIR) -I/usr/include/tirpc -I. s-chat.c

s-chat: s-chat.o
	$(CC) -o s-chat $(CFLAGS) $(CPPFLAGS) -L. -L$(RTTHREADS_LIB) s-chat.o -ltirpc -lRtt -llist
 
liblist.a : list_adders.o list_movers.o list_removers.o
	ar -r liblist.a list_movers.o list_adders.o list_removers.o

list_movers.o : list_movers.c list.h
	$(CC) -o list_movers.o -c $(CFLAGS) $(CPPFLAGS) list_movers.c

list_adders.o : list_adders.c list.h
	$(CC) -o list_adders.o -c $(CFLAGS) $(CPPFLAGS) list_adders.c

list_removers.o : list_removers.c list.h
	$(CC) -o list_removers.o -c $(CFLAGS) $(CPPFLAGS) list_removers.c

clean:
	rm -f *.o liblist.a libMonitor.a reader_writer_test
