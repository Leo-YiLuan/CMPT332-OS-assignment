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
#include <RttCommon.h>
#include <stdio.h>
#include "list.h"
#include <sys/socket.h>
#include <errno.h>
#include <arpa/inet.h>
#include <netdb.h>
#include <time.h>

RttSem recSem;
RttSem sendSem;
RttSem recSemHave;
RttSem sendSemHave;
LIST* sendQueue;
LIST* receivedQueue;
struct sockaddr *destinationClient = NULL;
struct sockaddr *myClient = NULL;
int listenSocket = 0;
void sendMsg();
void receiveMsg();
void pStdout();
void rKeyboard();

char *concat_time(char *msg) {
  char *timefmt = malloc(35 + strlen(msg) + 1);
  struct timeval value;
  gettimeofday(&value, NULL);
  sprintf(timefmt, "%ld.%ld - ", value.tv_sec, value.tv_usec);

  return strcat(timefmt, msg);
}

char *sent_succeed_msg() {
  char *timefmt = malloc(35);
  struct timeval value;
  gettimeofday(&value, NULL);
  sprintf(timefmt, "Msg sent @%ld.%ld", value.tv_sec, value.tv_usec);
  return timefmt;
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

  myClient = info->ai_addr;
  return localSocketFd;
}

void mainp(int argc, char** argv){
    RttTimeValue rttime;
    RttSchAttr rtschattr;
    RttThreadId rttid;
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

    /* Set up a "listen" socket for incoming data. Also sets myClient global */
    listenSocket = create_listen_socket(argv[1]);
    if (listenSocket == -1) {
      printf("ERR: Failed to create listen socket.\n");
      exit(EXIT_FAILURE);
    }

    /* We need socket info on the destination client so that we can send 
    that info with sendto */
    {
      struct addrinfo *info = get_host_info(argv[2], argv[3]);
      if (!info) {
        printf("Failed to get remote client info\n");
        exit(EXIT_FAILURE);
      }
      destinationClient = info->ai_addr;
    }

    /* Create the four threads */
    RttCreate(&rttid ,sendMsg ,16000, "send", NULL, rtschattr, RTTUSR);
    RttCreate(&rttid ,receiveMsg ,16000, "recv", NULL, rtschattr, RTTUSR);
    RttCreate(&rttid ,rKeyboard ,16000, "rkb", NULL, rtschattr, RTTUSR);
    RttCreate(&rttid ,pStdout ,16000, "sout", NULL, rtschattr, RTTUSR);

    printf("Finished init, please type your messages.\n");
}

void sendMsg() {
  while (1) {
    char* msg;
    char *buf;
    int res = 0;
    RttP(sendSemHave);
    RttP(sendSem);
    msg = (char*)ListTrim(sendQueue);
    /* Send to remote client */
    buf = concat_time(msg);
    res = sendto(listenSocket, (const void*)buf, strlen(buf) + 1,
    0, destinationClient, sizeof(*destinationClient));
    if (res > 0) {
      char *succeed = sent_succeed_msg();
      /* Send confirmation message. */
      res = sendto(listenSocket, (const void*)succeed, strlen(succeed) + 1,
      0, myClient, sizeof(*myClient));
    }
    free(buf);
    RttV(sendSem);
  }
}

void receiveMsg() {
  while (1) {
    int err = 0;
    struct sockaddr from = {0};
    socklen_t fromlen = sizeof(from);
    char *buf = malloc(10);
    int bufSize = 10;
    int received = 0;

    while (1) {
      err = recvfrom(listenSocket, (void*)buf, bufSize, MSG_PEEK, &from, 
                     &fromlen);
      if (err == -1) {
        break;
      }

      if (err == bufSize) {
        bufSize += 10;
        buf = realloc(buf, bufSize);
      } else {
        err = recvfrom(listenSocket, (void*)buf, bufSize, 0, &from, &fromlen);
        received = 1;
      }
    }

    if (received) {
      RttP(recSem);

      ListPrepend(receivedQueue, (void*)buf);

      RttV(recSem);
      RttV(recSemHave);
      
    }
    /* Reset to having not received anything. */
    received = 0;

    /* Sleep the thread briefly to give time to the other threads */
    RttUSleep(5000);
  }
}

void rKeyboard() {
  int bufSize = 10 * sizeof(char);
  char *buf = malloc(bufSize);
  int res = 0;

  /* Set to nonblocking */
  res = fcntl(0, F_GETFL);
  fcntl(0, F_SETFL, res | O_NONBLOCK);

  while (1) {
    int bufUsed = 0;
    int received = 0;
    int pos = 0;

    /* Get input from stdin for as long as it exists */
    while (1) {
      bufUsed += 1;
      /* Resize the buffer to account for new char */
      if (bufUsed >= bufSize) {
        bufSize += 10;
        buf = realloc(buf, bufSize);
      }
      res = read(0, &buf[pos], 1);
      if (res <= 0) {
        /* No input, bail out and try again next loop */
        break;
      }
      if (buf[pos] == '\n') {
        /* We've hit the end of the input */
        received = 1;
        buf[pos] = '\0';
        break;
      }
      pos++;
    }

    if (received) {
      /* Received input from stdin */
      char *msg = malloc(strlen(buf) + 1);
      memcpy(msg, buf, strlen(buf) + 1);
      RttP(sendSem);
      ListPrepend(sendQueue,(void*)msg);
      RttV(sendSem);
      RttV(sendSemHave);
    }

    RttUSleep(5000);
  }
}

void pStdout() {
  while (1) {
    char *msgToPrint = NULL;
    RttP(recSemHave);
    RttP(recSem);
    while (ListCount(receivedQueue) > 0) {
      msgToPrint = (char*)ListTrim(receivedQueue);
      printf("%s\n", msgToPrint);
    }
    RttV(recSem);
  }
}
