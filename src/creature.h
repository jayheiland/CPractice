#ifndef CREATURE_H
#define CREATURE_H

#include <stdlib.h>
#include <string.h>
#include <dirent.h>
#include <unordered_map>
#include <string>

#include "world.h"

/*IS_PLAYER tag allows creature to be controlled directly by the player, FRIENDLY means they are sympathetic to the player
creatures and may try to help*/
typedef enum {HOSTILE, NEUTRAL, FRIENDLY, IS_PLAYER} relationToPlyr;

class Creature{
    public:
        std::string name;
        std::string speciesName;
        ID body;
        creatureCode crtCode;
        relationToPlyr plyrRelation;
        //pathing data
        worldLoc loc;
        int currentlyPathing; //true if creature is actively following its given path
        Vec3 *path;
};

class CreatureRule{
    public:
        std::string speciesName;
        objectCode bodyCode;
};

#endif