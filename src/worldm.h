#pragma once

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <limits.h>

#include "game_data.h"

int equal(Vec3 *vec1, Vec3 *vec2);
void printPath(Vec3 *path, int length);
WorldChunk loadChunk(std::string chunkPath, std::string nodeInfoPath, GraphicsLayer *grph, std::unordered_map<std::string, NodeInfo> *nodeInfoMap, std::unordered_map<GraphObjID, worldLoc> *boundingBoxToLocation);
void deleteChunk(WorldChunk *chunk);
Vec3 *worldPath(worldNode ***world, Vec3 *worldSize, Vec3 *start, Vec3 *end, int *pathLen, std::vector<std::string> mobilityTags);
worldNode *getNode(WorldChunk *chunk, Vec3 loc);