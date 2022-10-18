/*
  NAME: Matthew Munro
  NSID: mam552
  STUDENT NUMBER: 11291769
  NAME: Yi Luan
  NSID: yil160
  STUDENT NUMBER: 11253856
  CMPT 332 2022
  A2*/

#include <rtthreads.h>
#include <stdio.h>
#include "list.h"
#include <sys/socket.h>
#include <errno.h>
#include <arpa/inet.h>
#include <netdb.h>

RttSem recSem;
RttSem sendSem;
RttSem recSemHave;
RttSem sendSemHave;
int portServeNum, portClientNum;
int sockfdServ, sockfdCli;
LIST* sendQueue;
LIST* receivedQueue;
void sendMsg();
void receiveMsg();
void pStdout();
void rKeyboard();
struct sockaddr_in servaddr, cliaddr;
struct sockaddr *destinationClient = NULL;

void debug_printaddr(struct sockaddr_in *addrIn) {
  char string[INET6_ADDRSTRLEN];
  inet_ntop(AF_INET, (void*)&addrIn->sin_addr, string, sizeof(string));
  printf("%s\n", string);
}

struct addrinfo* get_host_info(char *hostname, char *port) {
  int err = 0;
  struct addrinfo *info = NULL;
  struct addrinfo hints = {0};
  hints.ai_family = AF_INET;
  hints.ai_socktype = SOCK_DGRAM;
  hints.ai_flags = hostname == NULL ? AI_PASSIVE : 0;

  err = getaddrinfo(hostname, port, (const struct addrinfo*)&hints, &info);
  if (err != 0) {
    return NULL;
  }

  return info;
}

int create_listen_socket(char *port) {
  struct addrinfo *info = NULL;
  int err = 0;
  int localSocketFd = 0;

  info = get_host_info(NULL, port);
  localSocketFd = socket(PF_INET, SOCK_DGRAM, 0);
  if (localSocketFd == -1) {
    return -1;
  }

  err = bind(localSocketFd, info->ai_addr, info->ai_addrlen);
  if (err == -1) {
    return -1;
  }

  debug_printaddr((struct sockaddr_in*)info->ai_addr);
  freeaddrinfo(info);
  return localSocketFd;
}

void mainp(int argc, char** argv){
    RttTimeValue rttime;
    RttSchAttr rtschattr;
    RttThreadId rttid;
    int listenSocket = 0;
    int err = 0;
    receivedQueue = ListCreate();
    sendQueue = ListCreate();

    /* Create semaphores for received and sending queue */
    RttAllocSem(&recSem, 1, RTTFCFS);
    RttAllocSem(&sendSem, 1, RTTFCFS);
    RttAllocSem(&recSemHave, 0, RTTFCFS);
    RttAllocSem(&sendSemHave, 0, RTTFCFS);

    /* Check the usage */
    if (argc != 4) {
      fprintf(stderr, "Error:  Incorrect number of arguments. Usage: "
      "s-chat <Your port> <Guest machine name> <Guest ports>\n");
      exit(0);
    }

    /* setUp rt thread variable */
    rttime.seconds = 1;
    rttime.microseconds = 1000;
    rtschattr.startingtime = rttime;
    rtschattr.priority = 0;
    rtschattr.deadline=rttime;

    /* Set up a "listen" socket for incoming data */
    listenSocket = create_listen_socket(argv[1]);
    if (listenSocket == -1) {
      printf("ERR: Failed to create listen socket.\n");
      exit(EXIT_FAILURE);
    }

    /* We need socket info on the destination client so that we can send that info with sendto */
    {
      struct addrinfo *info = get_host_info(argv[2], argv[3]);
      if (!info) {
        printf("Failed to get remote client info\n");
        exit(EXIT_FAILURE);
      }
      destinationClient = info->ai_addr;
      freeaddrinfo(info);
    }

    /* Test send data */
    {
      int *msg = malloc(sizeof(int));
      *msg = 7;
      err = sendto(listenSocket, (const void*)msg, sizeof(int), 0, destinationClient, sizeof(*destinationClient));
      if (err == -1) {
        printf("Error: Failed sending test data\n");
      }
    }

    /* Test receive data. Wait in an infinite loop to get it. */
    while (1) {
      int a = 0;
      struct sockaddr from = {0};
      socklen_t fromlen = sizeof(from);

      err = recvfrom(listenSocket, (void*)&a, sizeof(int), 0, &from, &fromlen);
      if (err > 0) {
        printf("Received integer %d from address ", a);
        debug_printaddr((struct sockaddr_in*)&from);
      }
    }

    /* Create the four threads */
    RttCreate(&rttid ,sendMsg ,16000, "send", NULL, rtschattr, RTTUSR);
    RttCreate(&rttid ,receiveMsg ,16000, "send", NULL, rtschattr, RTTUSR);
    RttCreate(&rttid ,rKeyboard ,16000, "send", NULL, rtschattr, RTTUSR);
    RttCreate(&rttid ,pStdout ,16000, "send", NULL, rtschattr, RTTUSR);
}

void sendMsg() {
  while (1) {
    char* sendBuffer;
    RttP(sendSemHave);
    RttP(sendSem);
    sendBuffer = (char* )ListTrim(sendQueue);
    sendto(sockfdServ, sendBuffer, strlen(sendBuffer),
    MSG_CONFIRM, (const struct sockaddr *) &servaddr,
    sizeof(servaddr));

    RttV(sendSem);
  }
}

void receiveMsg() {
  while (1) {
    char buffer[100];
    int size;
    RttP(recSem);
    size = recvfrom(sockfdCli, (char *)buffer, 100,
    MSG_WAITALL, (struct sockaddr *) &cliaddr,
    NULL);
    buffer[size] = '\0';
    ListPrepend(receivedQueue,&buffer);
    RttV(recSem);
    RttV(recSemHave);
  }
}

void rKeyboard() {
  while (1) {
    char keyBuffer[100];
    scanf("%s\n", keyBuffer);
    RttP(sendSem);
    ListPrepend(sendQueue,&keyBuffer);
    RttV(sendSem);
    RttV(sendSemHave);
  }
}

void pStdout() {
  while (1) {
    char *printBuffer;
    RttP(recSemHave);
    RttP(recSem);
    printBuffer = (char*)ListTrim(receivedQueue);
    printf("%p\n", printBuffer);
    RttV(recSem);
  }
}
