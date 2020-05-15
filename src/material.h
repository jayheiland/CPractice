#pragma once

#include <vector>
#include <string>

typedef struct{
    std::string name;
    double density;
    std::vector<std::string> tags;
} Material;
