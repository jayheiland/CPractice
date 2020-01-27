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

struct worldNode{
    Vec3 loc;
    int processed;
    int nodeType;
    int visited_Pathing;
    unsigned int distance_Pathing;
    struct worldNode* east;
    struct worldNode* west;
    struct worldNode* north;
    struct worldNode* south;
    struct worldNode* up;
    struct worldNode* down;
};

int equal(Vec3 *vec1, Vec3 *vec2);
void printPath(Vec3 *path, int length);
struct worldNode ***newWorld(Vec3 *size);
void delWorld(struct worldNode ***world, Vec3* size);
Vec3 *worldPath(struct worldNode ***world, Vec3 *worldSize, Vec3 *start, Vec3 *end, int *pathLen);


#endif