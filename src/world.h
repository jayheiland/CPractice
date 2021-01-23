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

struct WorldLoc{
    Vec3 chunk;
    Vec3 loc;
    bool operator==(const WorldLoc& a) const
    {
        return (loc == a.loc && chunk.x == a.chunk.x && chunk.y == a.chunk.y && chunk.z == a.chunk.z);
    }
};

//a piece of 3D world space
struct WorldNode{
    Vec3 loc;
    char nodeName[5];
    GraphObjID model;
    int visited_Pathing;
    double distance_Pathing;
    struct WorldNode* east;
    struct WorldNode* west;
    struct WorldNode* north;
    struct WorldNode* south;
    struct WorldNode* up;
    struct WorldNode* down;
    struct WorldNode* northeast;
    struct WorldNode* northwest;
    struct WorldNode* southeast;
    struct WorldNode* southwest;
};

struct NodeInfo{
    std::string material;
    TextureID texture;
};

//a 3D matrix of worldNodes
struct WorldChunk{
    Vec3 chunkLoc;
    Vec3 size;
    WorldNode ***nodes;
    struct WorldChunk* east;
    struct WorldChunk* west;
    struct WorldChunk* north;
    struct WorldChunk* south;
    struct WorldChunk* up;
    struct WorldChunk* down;
};