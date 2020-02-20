#ifndef GENERAL_H
#define GENERAL_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define INT_MAX 2147483647

typedef unsigned long int ID;

typedef struct idListNode{
    unsigned long int id;
    idListNode *prev;
    idListNode *next;
} idListNode;

void logError(const char func[], const char msg[]);
void generateID(unsigned long int *id);

#endif