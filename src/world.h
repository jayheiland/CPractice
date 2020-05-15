#ifndef WORLD_H
#define WORLD_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <limits.h>

#include "general.h"

typedef struct{
    int x;
    int y;
    int z;
} Vec3;

typedef struct{
    Vec3 chunk;
    Vec3 loc;
} worldLoc;

//a piece of 3D world space
typedef struct worldNode{
    Vec3 loc;
    int nodeType;
    int visited_Pathing;
    unsigned int distance_Pathing;
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
} worldNode;

//a 3D matrix of worldNodes
typedef struct worldChunk{
    Vec3 chunkLoc;
    worldNode ***nodes;
    struct worldChunk* east;
    struct worldChunk* west;
    struct worldChunk* north;
    struct worldChunk* south;
    struct worldChunk* up;
    struct worldChunk* down;
} worldChunk;

int equal(Vec3 *vec1, Vec3 *vec2);
void printPath(Vec3 *path, int length);
worldNode ***newWorld(Vec3 *size);
void delWorld(worldNode ***world, Vec3* size);
Vec3 *worldPath(worldNode ***world, Vec3 *worldSize, Vec3 *start, Vec3 *end, int *pathLen);

#endif