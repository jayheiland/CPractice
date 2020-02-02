#ifndef GENERAL_H
#define GENERAL_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define INT_MAX 2147483647

#define ID_BUF 16

void logError(char func[], char msg[]);
void generateID(char *id);

#endif