#pragma once

#include <unordered_map>
#include <fstream>
#include <iostream>
#include <stdio.h>
#include <sstream>
#include <vector>

#include "material.h"
#include "general.h"

void loadMaterials(std::string path);
//debug
void printMaterials();
