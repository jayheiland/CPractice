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

class MultiObjectRuleGroup{
    public:
        std::unordered_map<objectCode, MultiObjectRule> group;
};

class ElementalObjectRuleGroup{
    public:
        std::unordered_map<objectCode, ElementalObjectRule> group;
};

class ObjectHandler{
    public:
        MultiObjectGroup multiObjGroup;
        ElementalObjectGroup elementalObjGroup;
        MultiObjectRuleGroup multiObjRules;
        ElementalObjectRuleGroup elemObjRules;

        void loadRules(std::string multiObjRulesPath, std::string elemObjRulesPath);
        ID createObject(objectCode objCode);
};