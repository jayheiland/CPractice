#pragma once

#include <unordered_map>
#include <fstream>

#include "object.h"
#include "general.h"

void addObject(Object *obj);
void loadObjects(std::string path);
//debug methods
void printObjects(std::unordered_map<ID, Object> *objGroup);

ID createObject(std::unordered_map<ID, Object> *objGroup, objectCode objCode);
void removeObject(std::unordered_map<ID, Object> *objGroup, ID id_);
void loadObjectRules(std::unordered_map<ID, Object> *objGroup, std::string multiObjRulesPath, std::string elemObjRulesPath);