#pragma once

#include <unordered_map>
#include <fstream>
#include <iostream>

#include "game_data.h"
#include "material_group.h"

enum FunctionalLinkLimitation {FUNCTIONAL, NON_FUNCTIONAL, FUNC_OR_NONFUNC};

void addObject(Object *obj);
void loadObjects(std::string path);
//debug methods
void printObjects(std::unordered_map<ID, Object> *objGroup);

Object *ao(gamedata *dt, ID id);
ID createObject(gamedata *dt, objectCode objCode);
ID createObjectsFromComponentMap(gamedata *dt, std::string mapName);
void removeObject(std::unordered_map<ID, Object> *objGroup, ID id_);
void loadObjectRules_Json(std::unordered_map<objectCode, ObjectRule> *objRules, std::string objRulesPath);
void loadComponentMaps(std::unordered_map<std::string, ComponentMap> *componentMaps, std::string cmpMapsPath);
void linkObjects(gamedata *dt, ID obj1, objLinkType linkType, ID obj2, bool isFunctional, double strength);
void unlinkObjects(gamedata *dt, ID obj1, ID obj2);
std::vector<ID> getPhysWeapons(gamedata *dt, ID body);
bool objHasUsageTag(gamedata *dt, ID obj, std::string tag);
std::vector<ID> getLinkedObjs(gamedata *dt, ID obj, objLinkType linkType, enum FunctionalLinkLimitation funcLimit, std::string usageTag, bool immediateLinksOnly);
void attackObject(gamedata *dt, ID weapon, ID subject);
double getMass(gamedata *dt, ID subject);
std::vector<ID> getObjsWithCode(gamedata *dt, objectCode objCode);
void printObjsWithCode(gamedata *dt, objectCode objCode);