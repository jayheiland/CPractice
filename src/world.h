#pragma once

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <limits.h>

#include "golden_plains.h"

struct Vec2{
    int x;
    int y;
    bool operator==(const Vec2& a) const
    {
        return (x == a.x && y == a.y);
    }
};

struct Vec3{
    int x;
    int y;
    int z;
    bool operator==(const Vec3& a) const
    {
        return (x == a.x && y == a.y && z == a.z);
    }
};

typedef Vec3 Loc;

// struct Loc{
//     Vec3 inLoadZone;
//     Vec3 inChunk;
//     bool operator==(const Loc& a) const
//     {
//         return (inChunk == a.inChunk && inLoadZone.x == a.inLoadZone.x && inLoadZone.y == a.inLoadZone.y && inLoadZone.z == a.inLoadZone.z);
//     }
// };

//a piece of 3D world space
struct WorldNode{
    Vec3 loc;
    char nodeName[5];
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
};

//a 3D matrix of worldNodes
struct WorldChunk{
    Vec2 origin;
    Vec3 size;
    WorldNode ***nodes;
    struct WorldChunk* east;
    struct WorldChunk* west;
    struct WorldChunk* north;
    struct WorldChunk* south;
    struct WorldChunk* up;
    struct WorldChunk* down;
    GraphObjID model;
};