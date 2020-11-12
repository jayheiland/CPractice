#pragma once

#include <vector>
#include <string>

struct Material{
    std::string name;
    double density; //grams per cubic centimeter
    int yieldPoint; //pressure at which this material deforms; higher is better
    int fracturePoint; //pressure at which this material fractures; higher is better
    int elasticity; //amount of deformation when yield point is overcome; also related to blunting of bladed weapons; lower is better
    int potentialSharpness;
    std::vector<std::string> tags;
};
