#ifndef CREATURE_H
#define CREATURE_H

#include <stdlib.h>
#include <string.h>

#include "world.h"

/*IS_PLAYER tag allows creature to be controlled directly by the player, FRIENDLY means they are sympathetic to the player
creatures and may try to help*/
typedef enum {HOSTILE, NEUTRAL, FRIENDLY, IS_PLAYER} relationToPlyrUnits; 

typedef struct{
    char id[ID_BUF];
    char name[10]; /*short species identifier, unused spaces filled with whitespace*/
    int lifespan;
} species;

typedef struct{
    char id[ID_BUF];
    int queuedForRemoval;
    relationToPlyrUnits plyrRelation;
    //pathing data
    int currentlyPathing; //true if creature is actively following its given path
    Vec3 *path;
    //personal data
    char speciesName[10];
    //attributes
    int strength;
    int agility;
    int vitality;
    int endurance;
} creature;

typedef struct{
    creature *creatures;
    int size;
} creatureGroup;

void updateCreatures(creatureGroup *group, unsigned long long int *clock);
void addCreature(creatureGroup *group, creature *newCreature);
//note: this does not "kill" a Creature, but queues it for removal from the given array of Creatures
void queueRemoveCreature(creatureGroup *group, char *id_);

//debug functions
void debug_printCreature();

#endif