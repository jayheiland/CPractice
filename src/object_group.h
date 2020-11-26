#pragma once

#include <unordered_map>
#include <fstream>
#include <iostream>

#include "object.h"
#include "general.h"
#include "material_group.h"
#include "creature_group.h"
#include "json_parser.hpp"

enum FunctionalLinkLimitation {FUNCTIONAL, NON_FUNCTIONAL, FUNC_OR_NONFUNC};

void addObject(Object *obj);
void loadObjects(std::string path);
//debug methods
void printObjects(std::unordered_map<ID, Object> *objGroup);

Object *ao(gameData *dt, ID id);
ID createObject(gameData *dt, objectCode objCode);
ID createObjectsFromComponentMap(gameData *dt, std::string mapName);
void removeObject(std::unordered_map<ID, Object> *objGroup, ID id_);
void loadObjectRules_Json(std::unordered_map<objectCode, ObjectRule> *objRules, std::string objRulesPath);
void loadComponentMaps(std::unordered_map<std::string, ComponentMap> *componentMaps, std::string cmpMapsPath);
void linkObjects(gameData *dt, ID obj1, objLinkType linkType, ID obj2, bool isFunctional, double strength);
void unlinkObjects(gameData *dt, ID obj1, ID obj2);
std::vector<ID> getPhysWeapons(gameData *dt, ID body);
bool objHasUsageTag(gameData *dt, ID obj, std::string tag);
std::vector<ID> getLinkedObjs(gameData *dt, ID obj, objLinkType linkType, enum FunctionalLinkLimitation funcLimit, std::string usageTag, bool immediateLinksOnly);
void attackObject(gameData *dt, ID weapon, ID subject);
double getMass(gameData *dt, ID subject);
std::vector<ID> getObjsWithCode(gameData *dt, objectCode objCode);
void printObjsWithCode(gameData *dt, objectCode objCode);