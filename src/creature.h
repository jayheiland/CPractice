#ifndef CREATURE_H
#define CREATURE_H

#include <stdlib.h>
#include <string.h>

#include "world.h"

/*IS_PLAYER tag allows creature to be controlled directly by the player, FRIENDLY means they are sympathetic to the player
creatures and may try to help*/
typedef enum {HOSTILE, NEUTRAL, FRIENDLY, IS_PLAYER} relationToPlyrUnits; 

typedef struct{
    char name[10]; /*short species identifier, unused spaces filled with whitespace*/
    int lifespan;
} species;

typedef struct{
    int key;
    int queuedForRemoval;
    char speciesName[10];
    relationToPlyrUnits plyrRelation;
    //pathing data
    int currentlyPathing; //true if creature is actively following its given path
    Vec3 *path;
} creature;

typedef struct{
    creature *creatures;
    int size;
} creatureGroup;

void updateCreatures(creatureGroup *group, unsigned long long int *clock);
void addCreature(creatureGroup *group, creature *newCreature);
//note: this does not "kill" a Creature, but queues it for removal from the given array of Creatures
void queueRemoveCreature(creatureGroup *group, int key_);

#endif