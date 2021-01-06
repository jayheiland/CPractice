#pragma once

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <limits.h>

#include "golden_plains.h"

struct Vec3{
    int x;
    int y;
    int z;
    bool operator==(const Vec3& a) const
    {
        return (x == a.x && y == a.y && z == a.z);
    }
};

struct worldLoc{
    Vec3 chunk;
    Vec3 loc;
};

//a piece of 3D world space
struct worldNode{
    Vec3 loc;
    char nodeName[5];
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

struct NodeInfo{
    std::string material;
    TextureID texture;
};

//a 3D matrix of worldNodes
struct WorldChunk{
    Vec3 chunkLoc;
    Vec3 size;
    worldNode ***nodes;
    struct WorldChunk* east;
    struct WorldChunk* west;
    struct WorldChunk* north;
    struct WorldChunk* south;
    struct WorldChunk* up;
    struct WorldChunk* down;
};