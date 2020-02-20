#pragma once

#include <unordered_map>
#include <string>
#include <fstream>

#include "thing.h"
#include "general.h"

class ThingGroup{
    private:
        std::unordered_map<ID, Thing> group;
    public:
        ThingGroup();
        void addThing(Thing tng);
        void loadThings(std::string path);
        //debug methods
        void printThings();
};