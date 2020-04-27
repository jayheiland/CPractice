#pragma once

#include <unordered_map>
#include <string>
#include <fstream>

#include "object.h"
#include "general.h"

class MultiObjectGroup{
    public:
        std::unordered_map<ID, MultiObject> group;

        MultiObjectGroup();
        void addObject(MultiObject obj);
        void loadObjects(std::string path);
        //debug methods
        void printObjects();
};

class ElementalObjectGroup{
    public:
        std::unordered_map<ID, ElementalObject> group;

        ElementalObjectGroup();
        void addObject(ElementalObject obj);
        void loadObjects(std::string path);
        //debug methods
        void printObjects();
};

class ObjectHandler{
    public:
        MultiObjectGroup multiObjGroup;
        ElementalObjectGroup elementalObjGroup;
        std::unordered_map<objectCode, MultiObjectRule> multiObjRules;
        std::unordered_map<objectCode, ElementalObjectRule> elemObjRules;

        void loadRules(std::string multiObjRulesPath, std::string elemObjRulesPath);
        ID createObject(objectCode objCode);
        void removeObject(ID id_);
};