#pragma once

#include <unordered_map>
#include <string>
#include <fstream>
#include <iostream>
#include <stdio.h>

#include "material.h"

class MaterialGroup{
    public:
        std::unordered_map<std::string, Material> group;

        MaterialGroup();
        void loadMaterials(std::string path);
};