#include "creature.h"

void printCreature(Creature *crt){
    std::cout << crt->name << "\n" << crt->speciesName << "\n\n";
}

ID getBody(std::unordered_map<ID, Creature> *crtGroup, ID crt){
    return crtGroup->at(crt).body;
}