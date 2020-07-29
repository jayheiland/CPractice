#ifndef OBJECT_H
#define OBJECT_H

#include <unordered_map>
#include <vector>
#include <iostream>

#include "general.h"
#include "material.h"

typedef unsigned int objectCode;

typedef struct{
    std::string name;
    objectCode objCode;
    double maxContainerVolume;
    std::vector<ID> equippedSites; //id of the object that this object is currently equipped on
    std::vector<ID> equippedObjects; //id list of objects that are equipped on this object
    std::vector<ID> containedObjects; //id list of every object carried by this object
    std::vector<ID> components; //id list of every object that makes up this object
    std::string materialName;
    double length,width,height; //ElementalObjects are roughly defined as a three-dimensional box (centimeters)
    double integrity; //when this is reduced to 0, the object is destroyed
} Object;

typedef struct{
    //number of objects required
    int count;
    //the set of objects that could fulfill this requirement
    std::vector<objectCode> alternativeComponents;
} ObjectRuleComponentReq;

typedef struct{
    std::string name;
    //the set of Materials that could constitute a single-material object
    std::vector<std::string> alternativeMaterials;
    //the set of component objects (if this is not a continuous object)
    std::vector<ObjectRuleComponentReq> components; 
    double length,width,height;
    std::vector<objectCode> equippableSites; //id list of body part types/objects that this object can be equipped on
    double maxContainerVolume;
}ObjectRule;

void printObject(std::unordered_map<ID, Object> *objGroup, Object *obj);
double getVolume();

#endif