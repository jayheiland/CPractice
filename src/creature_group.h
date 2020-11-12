#pragma once

#include <unordered_map>
#include <fstream>

#include "general.h"
#include "creature.h"
#include "object_group.h"
#include "json_parser.hpp"
#include "game_data.h"

Creature *ac(gameData *dt, ID crt);

void loadCreatureRules_Json(std::unordered_map<creatureCode, CreatureRule> *crtRules, std::string path);

void loadCreatureRules(std::unordered_map<creatureCode, CreatureRule> *crtRules, std::string path);

ID createCreature(gameData *dt, creatureCode crtCode, bool isPlayerCharacter, std::string name, factionCode fctCode);

void printCreatures(std::unordered_map<ID, Creature> *crtGroup);

void loadFactions_Json(std::unordered_map<factionCode, Faction> *fctGroup, std::string path);

void loadFactions(std::unordered_map<factionCode, Faction> *fctGroup, std::string path);

void setBattleTarget(std::unordered_map<ID, Creature> *crtGroup, ID aggressor, ID subject);