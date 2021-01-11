#pragma once

#include <unordered_map>
#include <vector>
#include <iostream>

#include "general.h"

typedef uint objectCode;

enum objLinkType{ADJOINS, WRAPS, WRAPPED_BY, ANY};

struct ObjectLink{
    enum objLinkType type;
    bool isFunctional;
    uint strength;
    ID subject;
};

struct Object{
    std::string name;
    objectCode objCode;
    std::vector<ObjectLink> linkedObjects;
    std::string materialName;
    double length,width,height; //current dimensions, ElementalObjects are roughly defined as a three-dimensional box (centimeters)
    double wrapThickness; //zero thickness means the object is solid, thickness higher than the total volume of the object will be ignored
    double integrity; //when this is reduced to 0, the object is destroyed
};

struct CmpMapLink{
    enum objLinkType type;
    bool isFunctional;
    uint strength;
    std::string subject;
};

struct CmpMapNode{
    //the set of objects that could fulfill this requirement
    std::vector<objectCode> alternativeComponents;
    std::vector<CmpMapLink> linkedObjects;
};

struct ObjectRule{
    std::string name;
    std::vector<std::string> materialTags;
    //default dimensions
    double defaultLength,defaultWidth,defaultHeight;
    //tags describing how this object can be used within the world
    std::vector<std::string> usageTags;
    double defaultWrapThickness;
};

struct ComponentMap{
    std::unordered_map<std::string, CmpMapNode> map;
};

void printObject(std::unordered_map<ID, Object> *objGroup, std::unordered_map<objectCode, ObjectRule> *objRules, ID id);
