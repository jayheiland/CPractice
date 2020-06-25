#pragma once

#include <unordered_map>
#include <fstream>

#include "general.h"
#include "creature.h"
#include "object_group.h"

struct gameData{
    std::unordered_map<ID, Object> objGroup;
    std::unordered_map<objectCode, ObjectRule> objRules;
    std::unordered_map<ID, Creature> crtGroup;
    std::unordered_map<creatureCode, CreatureRule> crtRules;
    std::unordered_map<factionCode, Faction> fctGroup;
    std::unordered_map<std::string, Material> matGroup;
};

void loadCreatureRules(std::unordered_map<creatureCode, CreatureRule> *crtRules, std::string path);

ID createCreature(gameData *data, creatureCode crtCode, std::string name, factionCode factionName);

void printCreatures(std::unordered_map<ID, Creature> *crtGroup);

void loadFactions(std::unordered_map<factionCode, Faction> *fctGroup, std::string path);

void processCreatures(gameData *data);