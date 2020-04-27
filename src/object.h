#ifndef OBJECT_H
#define OBJECT_H

#include <unordered_map>
#include <vector>
#include <string>
#include <iostream>

#include "general.h"
#include "material.h"

class Object{
    public:
        std::string name;
        objectCode objCode;
        double maxContainerVolume;
        ID equippedSite; //id list of objects that this object is currently equipped on
        std::vector<ID> equippedObjects; //id list of objects that are equipped on this object
        std::vector<ID> containedObjects; //id list of every object carried by this object

        virtual void printObject();
};

//MultiObjects are made up of MultiObjects and/or ElementalObjects
class MultiObject : public Object{
    public:
        std::vector<ID> components; //id list of every object that makes up this object
        
        MultiObject();
        void printObject();
};

//an ElementalObject is a continuous mass made up of a single Material; 
class ElementalObject : public Object{
    public:
        std::string materialName;
        double length,width,height; //ElementalObjects are roughly defined as a three-dimensional box (centimeters)

        ElementalObject();
        void printObject();
        double getVolume();
};

class MultiObjectRuleReq{
    public:
        //number of objects required
        int objectCount;
        //the set of objects that could fulfill this requirement
        std::vector<objectCode> alternativeObjects;
};

class MultiObjectRule{
    public: 
        std::string name;
        std::vector<MultiObjectRuleReq> requirements; 
        std::vector<objectCode> equippableSites; //id list of body part types/objects that this object can be equipped on
        double maxContainerVolume;

        void print();
};

class ElementalObjectRule{
    public:
        std::string name;
        //the set of Materials that could constitute this single-material object
        std::vector<std::string> alternativeMaterials;
        double length,width,height;
        std::vector<objectCode> equippableSites; //id list of body part types/objects that this object can be equipped on
        double maxContainerVolume;

        void print();
};

#endif