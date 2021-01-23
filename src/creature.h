#pragma once

#include <stdlib.h>
#include <string.h>
#include <dirent.h>
#include <unordered_map>
#include <iostream>
#include <vector>

#include "general.h"
#include "world.h"

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
    WorldLoc loc;
    bool currentlyPathing; //true if creature is actively following its given path
    Vec3 *path;
    //graphics data
    GraphObjID model;
    //attributes
    uint att_vit; //vitality
    uint att_end; //endurance
    uint att_agi; //agility
    uint att_str; //strength
    uint att_dex; //dexterity
    uint att_int; //intelligence
    uint att_for; //fortitude
};

struct CreatureRule{
    std::string speciesName;
    std::string bodyMapName;
    std::string textureName;
};



void printCreature(Creature *crt);