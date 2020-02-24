#ifndef GENERAL_H
#define GENERAL_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

extern unsigned long int masterIDCounter;

typedef unsigned long int ID;

void logError(const char func[], const char msg[]);
ID genID();

#endif