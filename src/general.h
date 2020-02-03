#ifndef GENERAL_H
#define GENERAL_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define INT_MAX 2147483647

void logError(const char func[], const char msg[]);
void generateID(unsigned long int *id);

#endif