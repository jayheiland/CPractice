#pragma once

#include <unordered_map>
#include <fstream>
#include <iostream>

#include "object.h"
#include "general.h"
#include "material_group.h"
#include "creature_group.h"

struct gameData;

void addObject(Object *obj);
void loadObjects(std::string path);
//debug methods
void printObjects(std::unordered_map<ID, Object> *objGroup);

ID createObject(gameData *data, objectCode objCode);
void removeObject(std::unordered_map<ID, Object> *objGroup, ID id_);
void loadObjectRules(std::unordered_map<objectCode, ObjectRule> *objRules, std::string objRulesPath);
void equipObject(gameData *data, ID equipper, ID equipment);
void unequipObject(std::unordered_map<ID, Object> *objGroup, ID equipper, ID equipment);
