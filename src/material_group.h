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

class MaterialHandler{
    public:
        std::unordered_map<std::string, Material> group;

        MaterialHandler();
        void loadMaterials(std::string path);
        //debug
        void printMaterials();
};