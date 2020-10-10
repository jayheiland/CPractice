#ifndef GENERAL_H
#define GENERAL_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <vector>
#include <sstream>
#include <algorithm>

#define NULL_ID 0

extern unsigned long int masterIDCounter;

typedef unsigned long int ID;

void logError(std::string msg);
ID genID();
void splitString(std::vector<std::string> *tokens, std::string str, char delimiter);
std::string stripChar(std::string str, char nix);
std::string stripCharAround(std::string str, char bookend);
bool strContains(std::string str, int num, char ch);
int roll(int numberDice, int numberSides);

#endif