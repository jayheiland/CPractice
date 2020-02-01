#ifndef WORLD_H
#define WORLD_H

#include <stdio.h>
#include <stdlib.h>

#include "general.h"

typedef struct{
    int x;
    int y;
    int z;
} Vec3;

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

typedef struct worldNodeCollection{
    Vec3 loc;
    worldNode ***nodes;
    struct worldNodeCollection* east;
    struct worldNodeCollection* west;
    struct worldNodeCollection* north;
    struct worldNodeCollection* south;
    struct worldNodeCollection* up;
    struct worldNodeCollection* down;
} worldNodeCollection;

int equal(Vec3 *vec1, Vec3 *vec2);
void printPath(Vec3 *path, int length);
worldNode ***newWorld(Vec3 *size);
void delWorld(worldNode ***world, Vec3* size);
Vec3 *worldPath(worldNode ***world, Vec3 *worldSize, Vec3 *start, Vec3 *end, int *pathLen);

#endif