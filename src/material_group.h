#pragma once

#include <unordered_map>
#include <fstream>
#include <iostream>
#include <stdio.h>
#include <sstream>
#include <vector>

#include "material.h"
#include "general.h"
#include "json_parser.hpp"

void loadMaterials_Json(std::unordered_map<std::string, Material> *matGroup, std::string path);
void loadMaterials(std::unordered_map<std::string, Material> *matGroup, std::string path);
std::string getMaterialWithTag(std::unordered_map<std::string, Material> *matGroup, std::string desiredTag);
//debug
void printMaterials(std::unordered_map<std::string, Material> *matGroup);