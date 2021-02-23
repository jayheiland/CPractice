#pragma once

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <limits.h>

#include "game_data.h"

int equal(Vec3 *vec1, Vec3 *vec2);
void printPath(Vec3 *path, int length);
// void setFocusedChunk(gamedata *dt, std::string chunkPath, std::string nodeInfoPath);
WorldChunk loadChunk(gamedata *dt, std::string chunkPath, std::string nodeInfoPath);
void deleteChunk(WorldChunk *chunk);
std::vector<Loc> worldPath(gamedata *dt, Loc *start, Loc *end, int maxDist, std::vector<std::string> mobilityTags);
std::vector<Loc> getPathingRange(gamedata *dt, Loc *start, double maxDist, std::vector<std::string> mobilityTags);
WorldNode *getNode(gamedata *dt, Loc loc);
