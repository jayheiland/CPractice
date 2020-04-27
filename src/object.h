#ifndef OBJECT_H
#define OBJECT_H

#include <unordered_map>
#include <vector>
#include <iostream>

#include "general.h"
#include "material.h"

typedef struct{
    std::string name;
    bool isMulti;
    objectCode objCode;
    double maxContainerVolume;
    ID equippedSite; //id list of objects that this object is currently equipped on
    std::vector<ID> equippedObjects; //id list of objects that are equipped on this object
    std::vector<ID> containedObjects; //id list of every object carried by this object
    std::vector<ID> components; //id list of every object that makes up this object
    std::string materialName;
    double length,width,height; //ElementalObjects are roughly defined as a three-dimensional box (centimeters)
} Object;

void printObject(Object *obj);
double getVolume();

typedef struct{
    //number of objects required
    int objectCount;
    //the set of objects that could fulfill this requirement
    std::vector<objectCode> alternativeObjects;
} MultiObjectRuleReq;

typedef struct{
    std::string name;
    std::vector<MultiObjectRuleReq> requirements; 
    std::vector<objectCode> equippableSites; //id list of body part types/objects that this object can be equipped on
    double maxContainerVolume;
}MultiObjectRule;

typedef struct{
    std::string name;
    //the set of Materials that could constitute this single-material object
    std::vector<std::string> alternativeMaterials;
    double length,width,height;
    std::vector<objectCode> equippableSites; //id list of body part types/objects that this object can be equipped on
    double maxContainerVolume;
}ElementalObjectRule;

#endif