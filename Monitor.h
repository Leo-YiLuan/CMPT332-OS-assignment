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

#ifndef MONITOR_H
#define MONITOR_H

#include <stddef.h>


void MonServer(size_t numConditions);

void MonEnter();

void MonLeave();

void MonWait(int condition);

void MonSignal(int condition);

#endif