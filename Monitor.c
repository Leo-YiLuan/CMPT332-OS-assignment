/*
# NAME: Matthew Munro
# NSID: mam552
# STUDENT NUMBER: 11291769
# NAME: Yi Luan
# NSID: yil160
# STUDENT NUMBER: 11253856
# CMPT 332 2022
# A2
*/

#include "Monitor.h"

#include "list.h"
#include <os.h>
#include <standards.h>
#include <stdio.h>

enum MSGTYPE {
    REQUEST_ENTER,
    REQUEST_LEAVE,
    WAIT,
    SIGNAL
};

typedef struct Message Message;
struct Message {
    enum MSGTYPE type;
    int condition;
};

typedef struct Monitor Monitor;
struct Monitor {
    PID serverThread;
    LIST *enterQueue;
    LIST **waitQueues;
    LIST *urgentQueue;
};

Monitor monitor = {0};

void MonMain() {
    /* Basic structural layout for the server thread. */
    while (1) {
        PID sender = PNUL;
        int len = 0;
        Message *msg;
        msg = Receive(&sender, &len);

        switch (msg->type) {
            case REQUEST_ENTER:
                ListCount(monitor.enterQueue);
                ListAdd(monitor.enterQueue, (void*)sender);
                break;
            case REQUEST_LEAVE:
                break;
            case WAIT:
                ListAdd(monitor.waitQueues[msg->condition], (void*)sender);
                break;
            case SIGNAL:
                ListFirst(monitor.waitQueues[msg->condition]);
                ListRemove(monitor.waitQueues[msg->condition]);
                break;
        }

        Reply(sender, (void*)0, sizeof(int));
    }
}

void MonServer(size_t numConditions) {
    size_t i = 0;
    monitor.enterQueue = ListCreate();
    monitor.urgentQueue = ListCreate();

    monitor.waitQueues = malloc(numConditions * sizeof(LIST*));
    for (i = 0; i < numConditions; i++) {
        monitor.waitQueues[i] = ListCreate();
        if (!monitor.waitQueues[i]) {
            printf("Failed to acquire resource during Monitor init.\n");
            exit(0);
        }
    }

    monitor.serverThread = Create((void(*)()) MonMain, 16000, "Monitor", 
                                  (void*)100, HIGH, USR);
    if (monitor.serverThread == PNUL) {
        printf("Error attempting to construct thread during monitor init.\n");
        exit(0);
    }
}

void MonEnter() {
    int pLen = sizeof(Message);
    Message msg = {0};
    msg.type = REQUEST_ENTER;
    Send(monitor.serverThread, (void*)&msg, &pLen);
}

void MonLeave() {
    int pLen = sizeof(Message);
    Message msg = {0};
    msg.type = REQUEST_LEAVE;
    Send(monitor.serverThread, (void*)&msg, &pLen);
}

void MonWait(int condition) {
    int pLen = sizeof(Message);
    Message msg = {0};
    msg.type = WAIT;
    msg.condition = condition;
    Send(monitor.serverThread, (void*)&msg, &pLen);
}

void MonSignal(int condition) {
    int pLen = sizeof(Message);
    Message msg = {0};
    msg.type = SIGNAL;
    msg.condition = condition;
    Send(monitor.serverThread, (void*)&msg, &pLen);
}