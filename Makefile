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
PARTB_INCLUDE=-I/student/cmpt332/pthreads/ -I.
PARTB_LIBS=-L. -L/student/cmpt332/pthreads/lib/Linuxx86_64/
RTTHREADS_DIR=/student/cmpt332/rtt/include/
RTTHREADS_LIB=/student/cmpt332/rtt/lib/Linuxx86_64/
RTTHREADS_LIB_PPC=/student/cmpt332/rtt/lib/Linuxppc/
RTTHREADS_LIB_ARM=/student/cmpt332/rtt/lib/Linuxarmv7l/

RWT_DEPS=libMonitor.a liblist_Linuxx86_64.a reader_writer.o reader_writer_monitor.o

#x86_64
#armv7l
#ppc
ARCH=$(shell uname -m)

.PHONY : all
all: s-chat reader_writer_test

ifeq ($(ARCH), x86_64)
.PHONY : s-chat
s-chat: s-chat_Linuxx86_64

s-chat_Linuxx86_64: liblist_Linuxx86_64.a s-chat_Linuxx86_64.o
	@echo build on linux
	$(CC) -o s-chat_Linuxx86_64 $(CFLAGS) $(CPPFLAGS) -L. -L$(RTTHREADS_LIB) s-chat_Linuxx86_64.o \
	-ltirpc -lRtt -llist_Linuxx86_64 -lRttUtils

s-chat_Linuxx86_64.o: s-chat.c
	$(CC) -o s-chat_Linuxx86_64.o -c $(CFLAGS) $(CPPFLAGS) -I$(RTTHREADS_DIR) \
	-I/usr/include/tirpc -I. s-chat.c

reader_writer_test: $(RWT_DEPS)
	$(CC) -o reader_writer_test $(CFLAGS) $(CPPFLAGS) $(PARTB_LIBS) \
	reader_writer.o reader_writer_monitor.o -lMonitor -lpthreads -llist_Linuxx86_64

libMonitor.a: Monitor.o
	ar -r libMonitor.a Monitor.o

Monitor.o: Monitor.c Monitor.h
	$(CC) -o Monitor.o -c $(CFLAGS) $(CPPFLAGS) $(PARTB_INCLUDE) Monitor.c 

reader_writer_monitor.o: reader_writer_monitor.c 
	$(CC) -o reader_writer_monitor.o -c $(CFLAGS) $(CPPFLAGS) -I. \
	reader_writer_monitor.c 

reader_writer.o: reader_writer.c reader_writer_monitor.h
	$(CC) -o reader_writer.o -c $(CFLAGS) $(CPPFLAGS) $(PARTB_INCLUDE) \
	reader_writer.c 

liblist_Linuxx86_64.a : list_adders_Linuxx86_64.o list_movers_Linuxx86_64.o list_removers_Linuxx86_64.o
	ar -r liblist_Linuxx86_64.a list_movers_Linuxx86_64.o list_adders_Linuxx86_64.o list_removers_Linuxx86_64.o

list_movers_Linuxx86_64.o : list_movers.c list.h
	$(CC) -o list_movers_Linuxx86_64.o -c $(CFLAGS) $(CPPFLAGS) list_movers.c

list_adders_Linuxx86_64.o : list_adders.c list.h
	$(CC) -o list_adders_Linuxx86_64.o -c $(CFLAGS) $(CPPFLAGS) list_adders.c

list_removers_Linuxx86_64.o : list_removers.c list.h
	$(CC) -o list_removers_Linuxx86_64.o -c $(CFLAGS) $(CPPFLAGS) list_removers.c


else ifeq ($(ARCH), ppc)
reader_writer_test:
	@echo Not on x86 architecture, skipping partB...

.PHONY : s-chat
s-chat: s-chat_Linuxppc

s-chat_Linuxppc: liblist_Linuxppc.a s-chat_Linuxppc.o
	@echo build on ppc
	$(CC) -o s-chat_Linuxppc $(CFLAGS) $(CPPFLAGS) -L. -L$(RTTHREADS_LIB_PPC) s-chat_Linuxppc.o \
	-lRtt -ltirpc -llist_Linuxppc -lRttUtils

s-chat_Linuxppc.o: s-chat.c
	$(CC) -o s-chat_Linuxppc.o -c $(CFLAGS) $(CPPFLAGS) -I$(RTTHREADS_DIR) \
	-I/usr/include/tirpc -I. s-chat.c

liblist_Linuxppc.a : list_adders_Linuxppc.o list_movers_Linuxppc.o list_removers_Linuxppc.o
	ar -r liblist_Linuxppc.a list_movers_Linuxppc.o list_adders_Linuxppc.o list_removers_Linuxppc.o

list_movers_Linuxppc.o : list_movers.c list.h
	$(CC) -o list_movers_Linuxppc.o -c $(CFLAGS) $(CPPFLAGS) list_movers.c

list_adders_Linuxppc.o : list_adders.c list.h
	$(CC) -o list_adders_Linuxppc.o -c $(CFLAGS) $(CPPFLAGS) list_adders.c

list_removers_Linuxppc.o : list_removers.c list.h
	$(CC) -o list_removers_Linuxppc.o -c $(CFLAGS) $(CPPFLAGS) list_removers.c

else ifeq ($(ARCH), armv7l)

reader_writer_test:
	@echo Not on x86 architecture, skipping partB...

.PHONY : s-chat
s-chat: s-chat_arm

s-chat_arm: liblist_arm.a s-chat_arm.o
	$(CC) -o s-chat_arm $(CFLAGS) $(CPPFLAGS) -L. -L$(RTTHREADS_LIB_ARM) s-chat_arm.o \
	-lRtt -ltirpc -llist_arm -lRttUtils

s-chat_arm.o: s-chat.c
	$(CC) -o s-chat_arm.o -c $(CFLAGS) $(CPPFLAGS) -I$(RTTHREADS_DIR) \
	-I/usr/include/tirpc -I. s-chat.c

liblist_arm.a : list_adders_arm.o list_movers_arm.o list_removers_arm.o
	ar -r liblist_arm.a list_movers_arm.o list_adders_arm.o list_removers_arm.o

list_movers_arm.o : list_movers.c list.h
	$(CC) -o list_movers_arm.o -c $(CFLAGS) $(CPPFLAGS) list_movers.c

list_adders_arm.o : list_adders.c list.h
	$(CC) -o list_adders_arm.o -c $(CFLAGS) $(CPPFLAGS) list_adders.c

list_removers_arm.o : list_removers.c list.h
	$(CC) -o list_removers_arm.o -c $(CFLAGS) $(CPPFLAGS) list_removers.c
endif

clean:
	rm -f *.o *.a reader_writer_test s-chat_Linuxx86_64 s-chat_Linuxppc
