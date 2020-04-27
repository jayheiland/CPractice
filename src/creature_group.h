#pragma once

#include <unordered_map>
#include <fstream>

#include "general.h"
#include "creature.h"

void loadCreatureRules(std::string path);

void addCreature(std::unordered_map<ID, Creature> *crtGroup, std::unordered_map<ID, Object> *objGroup, creatureCode crtCode, std::string name);