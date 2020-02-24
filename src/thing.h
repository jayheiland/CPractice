#ifndef THING_H
#define THING_H

#include <unordered_map>
#include <list>
#include <string>

#include "general.h"

class Thing{
    public:
        std::string name;
        ID id;
        std::list<ID> components; //id list of every thing that makes up this thing
        std::list<ID> equippableAreas; //id list of body part types/things that this thing can be equipped on
        std::list<ID> containedThings; //id list of every thing carried by this thing
        int maxContainerVolume; //max total volume of things that can be carried by this thing, 0 if this thing is not a container

        //std::list<ID> chemProperties;

        //methods
        void printThing();

};

#endif