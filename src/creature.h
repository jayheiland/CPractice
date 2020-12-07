#pragma once

#include <stdlib.h>
#include <string.h>
#include <dirent.h>
#include <unordered_map>
#include <iostream>

#include "general.h"
#include "world.h"
#include "object.h"

typedef uint creatureCode;
typedef uint factionCode;

struct FactionRelation{
    factionCode faction;
    int value; //-100 to 100
};

struct Faction{
    std::string name;
    std::vector<factionCode> enemies;
};

struct Creature{
    //creature data
    std::string name;
    ID body;
    creatureCode crtCode;
    factionCode fctCode;
    //battle data
    bool isPC;
    ID battleTarget;
    //pathing data
    worldLoc loc;
    bool currentlyPathing; //true if creature is actively following its given path
    Vec3 *path;
};

struct CreatureRule{
    std::string speciesName;
    std::string bodyMapName;
    std::string textureName;
};



void printCreature(Creature *crt);
ID getBody(std::unordered_map<ID, Creature> *crtGroup, ID crt);