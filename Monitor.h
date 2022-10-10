#ifndef MONITOR_H
#define MONITOR_H

#include <stddef.h>


void MonServer(size_t numConditions);

void MonEnter();

void MonLeave();

void MonWait(int condition);

void MonSignal(int condition);

#endif