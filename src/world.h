#pragma once

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <limits.h>

#include "golden_plains.h"
#include "general.h"

struct Vec3{
    int x;
    int y;
    int z;
};

struct worldLoc{
    Vec3 chunk;
    Vec3 loc;
};

//a piece of 3D world space
struct worldNode{
    Vec3 loc;
    int nodeType;
    GraphObjID model;
    int visited_Pathing;
    uint distance_Pathing;
    struct worldNode* east;
    struct worldNode* west;
    struct worldNode* north;
    struct worldNode* south;
    struct worldNode* up;
    struct worldNode* down;
    struct worldNode* northeast;
    struct worldNode* northwest;
    struct worldNode* southeast;
    struct worldNode* southwest;
};

//a 3D matrix of worldNodes
struct worldChunk{
    Vec3 chunkLoc;
    Vec3 size;
    worldNode ***nodes;
    struct worldChunk* east;
    struct worldChunk* west;
    struct worldChunk* north;
    struct worldChunk* south;
    struct worldChunk* up;
    struct worldChunk* down;
};

int equal(Vec3 *vec1, Vec3 *vec2);
void printPath(Vec3 *path, int length);
worldNode ***newWorld(Vec3 *size, GraphicsLayer *grph);
void deleteChunk(worldChunk *chunk);
Vec3 *worldPath(worldNode ***world, Vec3 *worldSize, Vec3 *start, Vec3 *end, int *pathLen);