#pragma once

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <limits.h>

#include "game_data.h"

int equal(Vec3 *vec1, Vec3 *vec2);
void printPath(Vec3 *path, int length);
WorldChunk loadChunk(gameData *dt, std::string chunkPath, std::string nodeInfoPath);
void deleteChunk(WorldChunk *chunk);
Vec3 *worldPath(gameData *dt, Vec3 *start, Vec3 *end, int *pathLen, std::vector<std::string> mobilityTags);
std::vector<WorldLoc> getPathingRange(gameData *dt, Vec3 *start, double dist, std::vector<std::string> mobilityTags);
WorldNode *getNode(WorldChunk *chunk, Vec3 loc);