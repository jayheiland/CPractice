#pragma once

#include <string>
#include <vector>

class Material{
    public:
        std::string name;
        double density;
        std::vector<std::string> tags;
};