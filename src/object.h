#ifndef OBJECT_H
#define OBJECT_H

#include <unordered_map>
#include <vector>
#include <iostream>

#include "general.h"
#include "material.h"

typedef uint objectCode;

enum objLinkType{_ADJOINS, _WRAPS, _WRAPPED_BY, _ANY};

typedef struct{
    enum objLinkType type;
    bool isFunctional;
    uint strength;
    ID subject;
} ObjectLink;

typedef struct{
    std::string name;
    objectCode objCode;
    std::vector<ObjectLink> linkedObjects;
    std::string materialName;
    double length,width,height; //current dimensions, ElementalObjects are roughly defined as a three-dimensional box (centimeters)
    double wrapThickness; //zero thickness means the object is solid, thickness higher than the total volume of the object will be ignored
    double integrity; //when this is reduced to 0, the object is destroyed
} Object;

typedef struct{
    enum objLinkType type;
    bool isFunctional;
    uint strength;
    std::string subject;
} CmpMapLink;

typedef struct{
    //the set of objects that could fulfill this requirement
    std::vector<objectCode> alternativeComponents;
    std::vector<CmpMapLink> linkedObjects;
} CmpMapNode;

typedef struct{
    std::string name;
    std::vector<std::string> materialTags;
    //default dimensions
    double defaultLength,defaultWidth,defaultHeight;
    //tags describing how this object can be used within the world
    std::vector<std::string> usageTags;
    double defaultWrapThickness;
} ObjectRule;

typedef struct{
    std::unordered_map<std::string, CmpMapNode> map;
} ComponentMap;

void printObject(std::unordered_map<ID, Object> *objGroup, std::unordered_map<objectCode, ObjectRule> *objRules, ID id);

#endif