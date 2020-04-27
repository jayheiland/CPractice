#ifndef GENERAL_H
#define GENERAL_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <string>
#include <vector>
#include <sstream>

extern unsigned long int masterIDCounter;

typedef unsigned long int ID;
typedef unsigned int objectCode;
typedef unsigned int creatureCode;

void logError(std::string msg);
ID genID();
void splitString(std::vector<std::string> *tokens, std::string str, char delimiter);
std::string stripChar(std::string str, char nix);
std::string stripCharAround(std::string str, char bookend);
bool strContains(std::string str, int num, char ch);

#endif