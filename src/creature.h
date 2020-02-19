#ifndef CREATURE_H
#define CREATURE_H

#include <stdlib.h>
#include <string.h>
#include <dirent.h>
#include <unordered_map>
#include <string>

#include "world.h"

#define SPECIES_NAME_BUF 16

/*IS_PLAYER tag allows creature to be controlled directly by the player, FRIENDLY means they are sympathetic to the player
creatures and may try to help*/
typedef enum {HOSTILE, NEUTRAL, FRIENDLY, IS_PLAYER} relationToPlyrUnits; 

typedef struct{
    unsigned long int id;
    char name[10]; /*short species identifier, unused spaces filled with whitespace*/
} species;

typedef struct{
    char *name;
    unsigned long int id;
    relationToPlyrUnits plyrRelation;
    //pathing data
    Vec3 loc;
    int currentlyPathing; //true if creature is actively following its given path
    Vec3 *path;
    //personal data
    char speciesName[SPECIES_NAME_BUF];
    //attributes
    int strength;
    int agility;
    int vitality;
    int endurance;
} creature;

typedef std::unordered_map<unsigned long int, creature> creatureGroup;

void updateCreatures(creatureGroup *group, unsigned long long int *clock);
void addCreature(creatureGroup *group, creature *newCreature);
void removeCreature(creatureGroup *group, unsigned long int id_);
void loadCreatures(creatureGroup *group);

//debug functions
void debug_printCreature(creature *crt);
void debug_printCreatureGroup(creatureGroup *group);
void printFilesInDir(char *d);

#endif