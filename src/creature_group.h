#pragma once

#include <unordered_map>
#include <fstream>


#include "general.h"
#include "creature.h"
#include "object_group.h"
#include "json_parser.hpp"

struct engineData {
    char debugConsoleStr[1024];
    int defaultGuiBkgColor[4];
    int windowWidth, windowHeight;
    int debugMode;
};

struct gameData{
    std::unordered_map<ID, Object> objGroup;
    std::unordered_map<objectCode, ObjectRule> objRules;
    std::unordered_map<std::string, ComponentMap> componentMaps;
    std::unordered_map<ID, Creature> crtGroup;
    std::unordered_map<creatureCode, CreatureRule> crtRules;
    std::unordered_map<factionCode, Faction> fctGroup;
    std::unordered_map<std::string, Material> matGroup;
};

Creature *ac(gameData *dt, ID crt);

void loadCreatureRules_Json(std::unordered_map<creatureCode, CreatureRule> *crtRules, std::string path);

void loadCreatureRules(std::unordered_map<creatureCode, CreatureRule> *crtRules, std::string path);

ID createCreature(gameData *dt, creatureCode crtCode, std::string name, factionCode factionName);

void printCreatures(std::unordered_map<ID, Creature> *crtGroup);

void loadFactions_Json(std::unordered_map<factionCode, Faction> *fctGroup, std::string path);

void loadFactions(std::unordered_map<factionCode, Faction> *fctGroup, std::string path);

void processCreatures(gameData *dt);

void determineBattleTargets(gameData *dt);

void processBattles(gameData *dt);

void setBattleTarget(std::unordered_map<ID, Creature> *crtGroup, ID aggressor, ID subject);