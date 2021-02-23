#pragma once

#include <unordered_map>
#include <fstream>

#include "game_data.h"
#include "objectm.h"
#include "worldm.h"

Creature *ac(gamedata *dt, ID crt);

void loadCreatureRules_Json(gamedata *dt, std::string path);

void loadCreatureRules(std::unordered_map<creatureCode, CreatureRule> *crtRules, std::string path);

ID createCreature(gamedata *dt, creatureCode crtCode, bool isPlayerCharacter, std::string name, factionCode fctCode, Vec3 pos);

void printCreatures(std::unordered_map<ID, Creature> *crtGroup);

std::vector<std::string> getMobilityTags(gamedata *dt, ID crt);

void moveToLocation(gamedata *dt, ID creature, GraphObjID BoundingBox, Loc loc);

void loadFactions_Json(std::unordered_map<factionCode, Faction> *fctGroup, std::string path);

void loadFactions(std::unordered_map<factionCode, Faction> *fctGroup, std::string path);

void setBattleTarget(std::unordered_map<ID, Creature> *crtGroup, ID aggressor, ID subject);