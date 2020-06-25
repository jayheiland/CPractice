#pragma once

#include <unordered_map>
#include <fstream>
#include <iostream>
#include <stdio.h>
#include <sstream>
#include <vector>

#include "material.h"
#include "general.h"

void loadMaterials(std::unordered_map<std::string, Material> *matGroup, std::string path);
std::string getMaterialWithTag(std::unordered_map<std::string, Material> *matGroup, std::string desiredTag);
//debug
void printMaterials(std::unordered_map<std::string, Material> *matGroup);