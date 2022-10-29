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
#include <pthread.h>

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
    int MonBusy=0;
    /* Basic structural layout for the server thread. */
    while (1) {
        PID sender = PNUL;
        int len = 0;
        Message *msg;
        msg = Receive(&sender, &len);
        switch (msg->type) {
            case REQUEST_ENTER:
                if (MonBusy==0) {
                    MonBusy=1;
                    if (Reply(sender, (void*)0, sizeof(int))!=0) {
                        printf("Entering Filed replied\n");
                    }

                }else {
                    ListPrepend(monitor.enterQueue, (void*)sender);
                }
                break;
            case REQUEST_LEAVE:

                if (ListCount(monitor.urgentQueue)>0) {
                    PID id = (PID)ListTrim(monitor.urgentQueue);
                    if(Reply(id, (void*)0, sizeof(int))!=0){
                      printf("Leave urgent Failed replied\n");
                    }

                }else if(ListCount(monitor.enterQueue)>0){
                    PID id = (PID)ListTrim(monitor.enterQueue);
                    if(Reply(id, (void*)0, sizeof(int))!=0){
                      printf("Leave enter Failed replied\n");
                    }

                }else{
                    MonBusy = 0;
                }
                Reply(sender, (void*)0, sizeof(int));

                break;

            case WAIT:
                ListPrepend(monitor.waitQueues[msg->condition], (void*)sender);
                if (ListCount(monitor.urgentQueue) > 0) {
                    PID id = (PID)ListTrim(monitor.urgentQueue);
                    if(Reply(id, (void*)0, sizeof(int))!=0){
                      printf("Wait urgent Failed replied\n");
                    }
                }else if(ListCount(monitor.enterQueue) > 0){
                    PID id = (PID)ListTrim(monitor.enterQueue);
                    if(Reply(id, (void*)0, sizeof(int))!=0){
                      printf("Wait enter Failed replied\n");
                    }

                }else{
                    MonBusy = 0;
                }
                break;
            case SIGNAL:
                if (ListCount(monitor.waitQueues[msg->condition])>0) {
                    PID id = (PID)ListTrim(monitor.waitQueues[msg->condition]);
                    Reply(id, (void*)0, sizeof(int));
                    ListPrepend(monitor.urgentQueue, (void*)sender);

                }else{
                    Reply(sender,(void*)0, sizeof(int));
                }
                break;
        }
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
    /*printf("waitr conditions %d\n", condition);*/

    Send(monitor.serverThread, (void*)&msg, &pLen);
}

void MonSignal(int condition) {
    int pLen = sizeof(Message);
    Message msg = {0};
    msg.type = SIGNAL;
    msg.condition = condition;
    /*printf("sig conditions %d\n", condition);*/
    Send(monitor.serverThread, (void*)&msg, &pLen);
}
