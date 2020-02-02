#include "creature.h"

void updateCreatures(creatureGroup *group, unsigned long long int *clock){
    int idx;
    //remove any creatures queued for removal
    for(idx = 0; idx < group->size; idx++){
        if(group->creatures[idx].queuedForRemoval){
            if(idx != group->size-1){
                memcpy(&group->creatures[idx], &group->creatures[idx+1], (group->size-idx-1)*sizeof(creature));
            }
            group = realloc(group, (group->size-1)*sizeof(creature));
            group->size--;
            idx--;
        }
    }
}

void addCreature(creatureGroup *group, creature *newCreature){
    group->size++;
    group = realloc(group, group->size*sizeof(creature));
    memcpy(&group->creatures[group->size-1], newCreature, sizeof(creature));
}

void queueRemoveCreature(creatureGroup *group, int key_){
    int idx;
    for(idx = 0; idx < group->size; idx++){
        creature *current = &group->creatures[idx];
        if(current->key == key_){
            current->queuedForRemoval = 1;
        }
    }
}
