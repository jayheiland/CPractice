#pragma once

#include <unordered_map>
#include <fstream>
#include <iostream>
#include <stdio.h>
#include <sstream>
#include <string>
#include <vector>

#include "material.h"
#include "general.h"

class MaterialGroup{
    public:
        std::unordered_map<std::string, Material> group;

        MaterialGroup();
        void loadMaterials(std::string path);
        //debug
        void printMaterials();
};