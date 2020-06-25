#ifndef CREATURE_H
#define CREATURE_H

#include <stdlib.h>
#include <string.h>
#include <dirent.h>
#include <unordered_map>
#include <iostream>

#include "general.h"
#include "world.h"
#include "object.h"

typedef unsigned int creatureCode;
typedef unsigned int factionCode;

typedef struct{
    factionCode faction;
    int value; //-100 to 100
} FactionRelation;

typedef struct{
    std::string name;
    std::vector<factionCode> enemies;
} Faction;

typedef struct{
    std::string name;
    std::string speciesName;
    ID body;
    creatureCode crtCode;
    factionCode fctCode;
    //pathing data
    worldLoc loc;
    bool currentlyPathing; //true if creature is actively following its given path
    Vec3 *path;
} Creature;

typedef struct{
    std::string speciesName;
    objectCode bodyCode;
} CreatureRule;



void printCreature(Creature *crt);
ID getBody(std::unordered_map<ID, Creature> *crtGroup, ID crt);

#endif